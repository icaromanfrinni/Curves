#pragma once

// RATIONAL B-SPLINE CURVES
// Reference:
/*
	Piegl, Les. Tiller, Wayne.
	The NURBS Book
	Chapter 4
	Springer, 1997
*/

#include <vector>
#include "Linear_Algebra.h"

class NURBS
{
private:
	// B-SPLINE BASIS FUNCTIONS
	float N(const int& i, const int& p, const float& t) const;
	float R(const int& i, const int& p, const float& t) const;
	// FIND THE ith KNOT SPAN
	int FindSpan(const float& t) const;
	// Degree of the basis function
	int p;
	// Knot vector
	std::vector <float> T;

public:
	// Control Points
	std::vector<CRAB::Vector4Df> points;
	
	// DEFAULT CONSTRUCTOR
	NURBS();
	// DESTRUCTOR
	~NURBS();

	// RETURNS A POINT ON THE CURVE
	CRAB::Vector4Df getPosition(const float& t) const;

	/* --------------- DEBUG --------------- */
	void Debug();
};