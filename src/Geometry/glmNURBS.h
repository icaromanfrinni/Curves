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
#include <glm/glm.hpp>

#include "Linear_Algebra.h"
#include "Segment.h"

#define ELEMENTS 100

class glmNURBS
{
private:
	// B-SPLINE BASIS FUNCTIONS
	float N(const int& i, const int& p, const float& t) const;
	float dN(const int& i, const int& p, const float& t) const;
	float dN2(const int& i, const int& p, const float& t) const;
	// DERIVATIVES
	glm::vec3 deriv(const float& t) const;
	glm::vec3 deriv2(const float& t) const;
	// FIND THE ith KNOT SPAN
	int FindSpan(const float& t) const;
	
	// Weights
	std::vector<float> w;
	// Degree of the basis function
	int P;
	// Knot vector
	std::vector<float> T;

public:
	// Control Points
	std::vector<glm::vec3> points;

	// DEFAULT CONSTRUCTOR
	glmNURBS();
	// OVERLOAD CONSTRUCTOR (from Segments)
	glmNURBS(const std::vector<Segment*>& segments);
	// OVERLOAD CONSTRUCTOR (from two curves)
	glmNURBS(const glmNURBS& horizontal_curve, const glmNURBS& vertical_curve);
	// DESTRUCTOR
	~glmNURBS();

	// RETURNS A POINT ON THE CURVE
	glm::vec3 getPosition(const float& t) const;
	// RETURNS THE CURVE TANGENT
	glm::vec3 getTangent(const float& t) const;
	// RETURNS THE CURVE NORMAL
	glm::vec3 getNormal(const float& t) const;
	// RETURNS THE CURVE NORMAL UP (Yaw vector)
	glm::vec3 getNormalUp(const float& t) const;
	// RETURNS THE CURVE BINORMAL
	glm::vec3 getBinormal(const float& t) const;
	// RETURNS THE CURVATURE
	float getCurvature(const float& t) const;
	// RETURNS THE RADIUS OF CURVATURE
	float getRadius(const float& t) const;
	// RETURNS THE LENGTH OF CURVE
	float getLength() const;
	// CLOCKWISE CHECK
	bool isClockwise(const float& t) const;
};