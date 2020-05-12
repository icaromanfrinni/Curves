#pragma once
#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <iostream>
#include <glm/glm.hpp>
#include "Linear_Algebra.h"

class Geometry
{
public:
	// DEFAULT CONSTRUCTOR
	Geometry();
	// DESTRUCTOR
	virtual ~Geometry() = 0;

	// RETURN
	virtual glm::vec3 getStartPoint() const = 0;
	virtual glm::vec3 getMidPoint() const = 0;
	virtual glm::vec3 getEndPoint() const = 0;
	virtual CRAB::Vector4Df getStart4DPoint() const = 0;
	virtual CRAB::Vector4Df getMid4DPoint() const = 0;
	virtual CRAB::Vector4Df getEnd4DPoint() const = 0;
	virtual float getLength() const = 0;
	virtual float getY(const float& x) const = 0;
	virtual float midPointWeight() const = 0;
};

#endif // GEOMETRY_H