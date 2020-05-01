#pragma once

#ifndef ALIGNMENT_H
#define ALIGNMENT_H

#include "NURBS.h"

class Alignment
{
public:
	NURBS path2Dh;	// Horizontal alignment
	NURBS path2Dv;	// Vertical alignment
	NURBS path3D;	// 3D alignment

	// DEFAULT CONSTRUCTOR
	Alignment();
	// DEFAULT CONSTRUCTOR
	Alignment(const std::vector<Segment*>& horizontal, const std::vector<Segment*>& vertical);
	// DESTRUCTOR
	~Alignment();

	// RETURN
	CRAB::Vector4Df getPosition(const float& t) const;
	CRAB::Vector4Df getTangent(const float& t) const;
	CRAB::Vector4Df getNormal(const float& t) const;
	CRAB::Vector4Df getNormalUp(const float& t) const;
	float getRadius(const float& t) const;
};

#endif