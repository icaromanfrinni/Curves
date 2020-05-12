#pragma once
#ifndef CLOTHOID_H
#define CLOTHOID_H

#include <vector>

#include "Line.h"
#include "CircularArc.h"

class Clothoid
{
public:
	std::vector<Geometry*> segments;

	// DEFAULT CONSTRUCTOR
	Clothoid();
	// DESTRUCTOR
	~Clothoid();
};

#endif // CLOTHOID_H