/*
 * ControlEntity.h
 *
 *  Created on: 19.09.2016
 *      Author: imolcean
 */

#ifndef SRC_CONTROLENTITY_H_
#define SRC_CONTROLENTITY_H_

namespace marco
{

class ControlEntity
{
private:
	double m_x;
	double m_y;
	int m_time;

public:

	/**
	 * Default constructor.
	 */
	ControlEntity();

	/**
	 * Main constructor.
	 *
	 * @param x X value of the vector
	 * @param y Y value of the vector
	 * @param time execution time
	 */
	ControlEntity(double x, double y, int time);

	/**
	 * Copy constructor.
	 */
	ControlEntity(const ControlEntity& other);

	/**
	 * Assignment operator.
	 */
	ControlEntity& operator=(const ControlEntity& other);

	/**
	 * Returns X value of the vector.
	 */
	double getX() const;

	/**
	 * Returns Y value of the vector.
	 */
	double getY() const;

	/**
	 * Returns the remaining execution time.
	 */
	int getTime() const;

	/**
	 * Sets X value of the vector.
	 */
	void setX(double val);

	/**
	 * Sets Y value of the vector.
	 */
	void setY(double val);

	/**
	 * Sets the remaining execution time.
	 */
	void setTime(int val);

	/**
	 * Updates control entity by setting the new values.
	 */
	void update(double x, double y, int time);
};

} /* namespace marco */

#endif /* SRC_CONTROLENTITY_H_ */
