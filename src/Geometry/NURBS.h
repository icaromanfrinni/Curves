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
	float dN(const int& i, const int& p, const float& t) const;
	float dN2(const int& i, const int& p, const float& t) const;
	// DERIVATIVES
	CRAB::Vector4Df deriv(const float& t) const;
	CRAB::Vector4Df deriv2(const float& t) const;
	// FIND THE ith KNOT SPAN
	int FindSpan(const float& t) const;
	// Degree of the basis function
	int p;
	// Knot vector
	std::vector<float> T;

	// ********************************************* //
	// TESTES
	// ------
	float Nk(const int& k, const int& i, const int& p, const float& t) const;
	CRAB::Vector4Df Ck(const int& k, const float& t) const;
	CRAB::Vector4Df Ak(const int& k, const float& t, const int& span) const;
	float Wk(const int& k, const float& t, const int& span) const;
	int binomialCoefficient(const int& n, const int& i) const;
	// ********************************************* //

public:
	// Control Points
	std::vector<CRAB::Vector4Df> points;
	// Weights
	std::vector<float> w;
	
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
	// RETURNS THE CURVE TANGENT
	CRAB::Vector4Df getTangent(const float& t) const;
	// RETURNS THE CURVE NORMAL
	CRAB::Vector4Df getNormal(const float& t) const;
	// RETURNS THE CURVE NORMAL UP (Yaw vector)
	CRAB::Vector4Df getNormalUp(const float& t) const;
	// RETURNS THE CURVE BINORMAL
	CRAB::Vector4Df getBinormal(const float& t) const;
	// RETURNS THE CURVATURE
	float getCurvature(const float& t) const;
	// RETURNS THE RADIUS OF CURVATURE
	float getRadius(const float& t) const;
	// CLOCKWISE CHECK
	bool isClockwise(const float& t) const;
};