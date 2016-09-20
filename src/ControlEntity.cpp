/*
 * ControlEntity.cpp
 *
 *  Created on: 19.09.2016
 *      Author: imolcean
 */

#include "ControlEntity.h"

namespace marco {

ControlEntity::ControlEntity() : m_x(0), m_y(0), m_time(0) {}

ControlEntity::ControlEntity(double x, double y, int time) : m_x(x), m_y(y), m_time(time) {}

ControlEntity::ControlEntity(const ControlEntity& other)
{
	*this = other;
}

ControlEntity& ControlEntity::operator=(const ControlEntity& other)
{
	if(&other == this)
	{
		return *this;
	}

	m_x = other.getX();
	m_y = other.getY();
	m_time = other.getTime();

	return *this;
}

double ControlEntity::getX() const
{
	return m_x;
}

double ControlEntity::getY() const
{
	return m_y;
}

int ControlEntity::getTime() const
{
	return m_time;
}

} /* namespace marco */
