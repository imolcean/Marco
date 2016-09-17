/*
 * test-config.cpp
 *
 *  Created on: 17.09.2016
 *      Author: imolcean
 *
 *      Test for the algorithms for the transformation
 *      of control vector to the track velocities.
 */

#include <iostream>
#include <math.h>
#include <array>

typedef std::array<double, 2> arr;
typedef arr (*algorithm)(arr args);

void call(arr args, algorithm f)
{
	arr res = f(args);

	std::cout << "x: " << args[0] << " y: " << args[1];
	std::cout << " | ";
	std::cout << "l: " << res[0] << " r: " << res[1];
	std::cout << std::endl;
}

arr norm(arr args)
{
	double vLeft = args[0];
	double vRight = args[1];

	double t = std::max(fabs(vLeft), fabs(vRight));

	if(t > 1)
	{
		vLeft = vLeft / t;
		vRight = vRight / t;
	}

	return {vLeft, vRight};
}

arr lmy(arr args)
{
	// Velocity of the tracks
	double vLeft;
	double vRight;

	// Control vector
	double x = args[0];
	double y = args[1];

	// Dead zone close to zero
	if(fabs(x) < 0.1)
	{
		x = 0;
	}

	if(fabs(y) < 0.1)
	{
		y = 0;
	}

	// Normal speed is the length of the vector
	// Turn speed is the speed of the inner track
	double vNorm = sqrt(pow(x, 2) + pow(y, 2));
	double vTurn = vNorm - fabs(y);

	// Moving backwards
	if(x < 0)
	{
		vNorm = -vNorm;
		vTurn = -vTurn;
	}

	// Turning around
	//
	// When x is zero and y is not
	// robot will turn around it's center
	// and not around the track
	//
	// Comment the block out if you
	// don't want this functionality
	if(x == 0)
	{
		if(y != 0)
		{
			vTurn = -vNorm;
		}
	}

	// Determine direction of the turn
	if(y < 0)
	{
		vLeft = vNorm;
		vRight = vTurn;
	}
	else
	{
		vLeft = vTurn;
		vRight = vNorm;
	}

	arr res = {vLeft, vRight};

	// Normalize the values
	//
	// If values are bigger than 1.0
	// they will be scaled so the
	// biggest one will be 1.0
	//
	// Comment the line out if you
	// don't want this functionality
	res = norm(res);

	return res;
}

int main(int argc, char **argv)
{
	call({ 0,  0}, &lmy);
	call({ 1,  0}, &lmy);
	call({ 1, -1}, &lmy);
	call({ 0, -1}, &lmy);
	call({-1, -1}, &lmy);
	call({-1,  0}, &lmy);
	call({-1,  1}, &lmy);
	call({ 0,  1}, &lmy);
	call({ 1,  1}, &lmy);

	double x;
	double y;

	while(true)
	{
		std::cout << std::endl << "Put your x and y..." << std::endl;

		std::cin >> x;
		std::cin >> y;

		call({x, y}, &lmy);
	}

	return 0;
}
