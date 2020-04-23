#pragma once

// B-SPLINE CURVES
// Reference:
/*
	Piegl, Les. Tiller, Wayne.
	The NURBS Book
	Chapters 2 and 3
	Springer, 1997
*/

#include <vector>
#include "Linear_Algebra.h"

class Bspline
{
private:
	// B-SPLINE BASIS FUNCTIONS
	float N(const int& i, const int& p, const float& t) const;
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
	Bspline();
	// DESTRUCTOR
	~Bspline();

	// RETURNS A POINT ON THE CURVE
	CRAB::Vector4Df getPosition(const float& t) const;
};