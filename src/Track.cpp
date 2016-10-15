/*
 * Track.cpp
 *
 *  Created on: 01.09.2016
 *      Author: imolcean
 */

#include "Track.h"
#include <bcm2835.h>

#include "easylogging++.h"

namespace marco {

Track::Track(unsigned int pinA, unsigned int pinB, unsigned int pinE) :
		m_pinA(pinA),
		m_pinB(pinB),
		m_pinE(pinE),
		m_pwm("/dev/pi-blaster")
{
	bcm2835_gpio_fsel(m_pinA, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(m_pinB, BCM2835_GPIO_FSEL_OUTP);
//	bcm2835_gpio_fsel(m_pinE, BCM2835_GPIO_FSEL_OUTP); // Pi-Blaster does it by itself

	move(0);
}

void Track::setDirection(bool forward)
{
	if(forward)
	{
		bcm2835_gpio_set(m_pinA);
		bcm2835_gpio_clr(m_pinB);
	}
	else
	{
		bcm2835_gpio_set(m_pinB);
		bcm2835_gpio_clr(m_pinA);
	}
}

void Track::setVelocity(double value)
{
	m_pwm << m_pinE << "=" << fabs(value) << std::endl;

	LOG(DEBUG) << "Track writes: " << m_pinE << "=" << fabs(value) << std::endl;
}

void Track::move(double value)
{
	// DIRECTION

	if(value < 0)
	{
		setDirection(false);
	}
	else
	{
		setDirection(true);
	}

	// VELOCITY

	setVelocity(fabs(value));
}

void Track::stop()
{
	move(0);
}

Track::~Track()
{
	move(0);
	m_pwm.close();
}

} /* namespace marco */
