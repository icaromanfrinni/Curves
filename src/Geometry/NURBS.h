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
	// FIND THE ith KNOT SPAN
	int FindSpan(const float& t) const;
	// Degree of the basis function
	int p;

public:
	// Control Points
	std::vector<CRAB::Vector4Df> points;
	// Weights
	std::vector<float> w;
	// Knot vector
	std::vector<float> T;
	
	// DEFAULT CONSTRUCTOR
	NURBS();
	// OVERLOAD CONSTRUCTOR
	NURBS(const std::vector<CRAB::Vector4Df>& _points);
	NURBS(const std::vector<CRAB::Vector4Df>& _points, const int& _p);
	NURBS(const std::vector<CRAB::Vector4Df>& _points, const int& _p, const std::vector<float>& _w);
	NURBS(const std::vector<CRAB::Vector4Df>& _points, const int& _p, const std::vector<float>& _w, std::vector<float> _T);
	// DESTRUCTOR
	~NURBS();

	// RETURNS A POINT ON THE CURVE
	CRAB::Vector4Df getPosition(const float& t) const;
};