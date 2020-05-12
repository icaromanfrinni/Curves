#pragma once

#ifndef ALIGNMENT_H
#define ALIGNMENT_H

#include "NURBS.h"
#include "HorSegment.h"
#include "VerSegment.h"

// MAX Transverse Slope
const float SLOPE_MAX = 0.10f;

class Alignment
{
private:
	float findProjection(const float& t) const;
	//// GET ELEVATION FROM VERTICAL ALIGNMENT
	//int findSpan(const float& dx) const;
	//float getElevation(const float& distance) const;
	int findSegment(const float& station) const;

public:
	std::vector<HorSegment*> plan;		// Horizontal alignment
	std::vector<VerSegment*> profile;	// Vertical alignment

	NURBS path2Dh;	// 2D horizontal curve
	NURBS path3D;	// 3D curve

	// DEFAULT CONSTRUCTOR
	Alignment();
	// DEFAULT CONSTRUCTOR
	Alignment(const std::vector<HorSegment*>& _plan, const std::vector<VerSegment*>& _profile);
	// DESTRUCTOR
	~Alignment();

	// RETURN
	CRAB::Vector4Df getPosition(const float& t) const;
	CRAB::Vector4Df getTangent(const float& t) const;
	CRAB::Vector4Df getNormal(const float& t) const;
	CRAB::Vector4Df getNormalUp(const float& t) const;
};

#endif