#include "NURBS.h"

#include <iostream>

// DEFAULT CONSTRUCTOR
// -------------------
NURBS::NURBS()
{
	// control points
	this->points.push_back(CRAB::Vector4Df{ -5.0f, 0.0f, 1.0f, 1.0f });
	this->points.push_back(CRAB::Vector4Df{ 0.0f, 5.0f, 1.0f, 1.0f });
	this->points.push_back(CRAB::Vector4Df{ 5.0f, 0.0f, 1.0f, 1.0f });

	// weights
	/*for (int i = 0; i < this->points.size(); i++)
		this->w.push_back(1.0f);*/
	CRAB::Vector4Df p0p1 = (this->points[1] - this->points[0]).to_unitary();
	CRAB::Vector4Df p0p2 = (this->points[2] - this->points[0]).to_unitary();
	this->w = { 1.0f, CRAB::dot(p0p1, p0p2), 1.0f };

	// degree
	this->p = this->points.size() - 1;

	// knot vector
	int m = points.size() + this->p;
	int n = points.size() - 1;
	for (int i = 0; i <= m; i++)
	{
		if (i <= p)
			T.push_back(0.0f);
		else if (i > n)
			T.push_back(1.0f);
		else
		{
			float u = float(i - p) / float(n - p + 1);
			T.push_back(u);
		}
	}
}
// OVERLOAD CONSTRUCTOR
// --------------------
NURBS::NURBS(const std::vector<CRAB::Vector4Df>& _points)
	: points(_points)
{
	// degree
	this->p = this->points.size() - 1;

	// weights
	for (int i = 0; i < this->points.size(); i++)
		this->w.push_back(1.0f);
	
	// uniform knot vector
	int m = points.size() + this->p;
	int n = points.size() - 1;
	for (int i = 0; i <= m; i++)
	{
		if (i <= this->p)
			this->T.push_back(0.0f);
		else if (i > n)
			this->T.push_back(1.0f);
		else
		{
			float u = float(i - this->p) / float(n - this->p + 1);
			this->T.push_back(u);
		}
	}
}
NURBS::NURBS(const std::vector<CRAB::Vector4Df>& _points, const int& _p)
	: points(_points), p(_p)
{
	// weights
	for (int i = 0; i < this->points.size(); i++)
		this->w.push_back(1.0f);

	// uniform knot vector
	int m = points.size() + this->p;
	int n = points.size() - 1;
	for (int i = 0; i <= m; i++)
	{
		if (i <= this->p)
			this->T.push_back(0.0f);
		else if (i > n)
			this->T.push_back(1.0f);
		else
		{
			float u = float(i - this->p) / float(n - this->p + 1);
			this->T.push_back(u);
		}
	}
}
NURBS::NURBS(const std::vector<CRAB::Vector4Df>& _points, const int& _p, const std::vector<float>& _w)
	: points(_points), p(_p), w(_w)
{
	// uniform knot vector
	int m = points.size() + this->p;
	int n = points.size() - 1;
	for (int i = 0; i <= m; i++)
	{
		if (i <= this->p)
			this->T.push_back(0.0f);
		else if (i > n)
			this->T.push_back(1.0f);
		else
		{
			float u = float(i - this->p) / float(n - this->p + 1);
			this->T.push_back(u);
		}
	}
}
NURBS::NURBS(const std::vector<CRAB::Vector4Df>& _points, const int& _p, const std::vector<float>& _w, std::vector<float> _T)
	: points(_points), p(_p), w(_w), T(_T)
{
}

// DESTRUCTOR
// ----------
NURBS::~NURBS()
{
}

// BASIS FUNCTIONS
// ---------------
float NURBS::N(const int& i, const int& p, const float& t) const
{
	if (p == 0)
	{
		if (t >= this->T[i] && t < this->T[i + 1])
			return 1.0f;
		else if (t == this->T[i + 1] && t == this->T.back())
			return 1.0f;
		else return 0.0f;
	}

	float left = this->N(i, p - 1, t) * (t - this->T[i]) / (this->T[i + p] - this->T[i]);
	if (isnan(left)) left = 0.0f;

	float right = this->N(i + 1, p - 1, t) * (this->T[i + p + 1] - t) / (this->T[i + p + 1] - this->T[i + 1]);
	if (isnan(right)) right = 0.0f;

	return left + right;
}

// ****************************************************************************************************

float NURBS::dN(const int& i, const int& p, const float& t) const
{
	float left = this->N(i, p - 1, t) * p / (this->T[i + p] - this->T[i]);
	if (isnan(left)) left = 0.0f;

	float right = this->N(i + 1, p - 1, t) * p / (this->T[i + p + 1] - this->T[i + 1]);
	if (isnan(right)) right = 0.0f;

	return left - right;
}
float NURBS::dN2(const int& i, const int& p, const float& t) const
{
	float left = this->dN(i, p - 1, t) * p / (this->T[i + p] - this->T[i]);
	if (isnan(left)) left = 0.0f;

	float right = this->dN(i + 1, p - 1, t) * p / (this->T[i + p + 1] - this->T[i + 1]);
	if (isnan(right)) right = 0.0f;

	return left - right;
}

// DERIVATIVES
// -----------
CRAB::Vector4Df NURBS::deriv(const float& t) const
{
	CRAB::Vector4Df deriv = { 0.0f, 0.0f, 0.0f, 0.0f };
	int span = this->FindSpan(t);

	for (int i = 0; i <= this->p; i++)
	{
		int index = span - this->p + i;
		deriv += points[index] * this->dN(index, this->p, t);
	}

	return deriv;
}
CRAB::Vector4Df NURBS::deriv2(const float& t) const
{
	CRAB::Vector4Df deriv2 = { 0.0f, 0.0f, 0.0f, 0.0f };
	int span = this->FindSpan(t);

	for (int i = 0; i <= this->p; i++)
	{
		int index = span - this->p + i;
		deriv2 += points[index] * this->dN2(index, this->p, t);
	}

	return deriv2;
}

// ****************************************************************************************************

// FIND THE ith KNOT SPAN
// ----------------------
int NURBS::FindSpan(const float& t) const
{
	int n = points.size() - 1;
	if (t == T[n + 1])
		return n;

	int low = this->p;
	int high = n + 1;
	int mid = (low + high) / 2;

	while (t < T[mid] || t >= T[mid + 1])
	{
		if (t < T[mid])
			high = mid;
		else low = mid;
		
		mid = (low + high) / 2;
	}
	
	return mid;
}

// RETURNS A POINT ON THE CURVE
// ----------------------------
CRAB::Vector4Df NURBS::getPosition(const float& t) const
{
	CRAB::Vector4Df position = { 0.0f, 0.0f, 0.0f, 1.0f };
	int span = this->FindSpan(t);

	// denominator
	float d = 0.0f;
	for (int j = 0; j <= this->p; j++)
	{
		int index = span - this->p + j;
		d += this->w[index] * this->N(index, this->p, t);
	}

	for (int i = 0; i <= this->p; i++)
	{	
		int index = span - this->p + i;
		position += this->points[index] * (this->w[index] * this->N(index, this->p, t) / d);
	}

	return position;
}

// **********************************************************************************************************

// RETURNS THE CURVE TANGENT
// -------------------------
CRAB::Vector4Df NURBS::getTangent(const float& t) const
{
	return this->deriv(t).to_unitary();
}

// RETURNS THE CURVE NORMAL
// ------------------------
CRAB::Vector4Df NURBS::getNormal(const float& t) const
{
	CRAB::Vector4Df deriv = this->deriv(t).to_unitary();
	CRAB::Vector4Df deriv2 = this->deriv2(t).to_unitary();
	CRAB::Vector4Df normal = deriv2 - deriv * (dot(deriv2, deriv) / deriv.lengthsq());
	return normal.to_unitary();
}

// RETURNS THE CURVE NORMAL UP (Yaw vector)
// ----------------------------------------
CRAB::Vector4Df NURBS::getNormalUp(const float& t) const
{
	CRAB::Vector4Df tan = this->getTangent(t);
	CRAB::Vector4Df vUp = { 0.0f, 1.0f, 0.0f, 0.0f };
	CRAB::Vector4Df vAux = CRAB::cross(vUp, tan).to_unitary();
	CRAB::Vector4Df n = CRAB::cross(tan, vAux).to_unitary();
	return n;
}

// RETURNS THE CURVE BINORMAL
// --------------------------
CRAB::Vector4Df NURBS::getBinormal(const float& t) const
{
	return CRAB::cross(getTangent(t), getNormal(t)).to_unitary();
}

// RETURNS THE CURVATURE
// ---------------------
float NURBS::getCurvature(const float& t) const
{
	CRAB::Vector4Df deriv = this->deriv(t);
	CRAB::Vector4Df deriv2 = this->deriv2(t);
	float k = cross(deriv, deriv2).length() / powf(deriv.length(), 3.0f);
	return k;
}

// RETURNS THE RADIUS OF CURVATURE
// -------------------------------
float NURBS::getRadius(const float& t) const
{
	float r = 1.0f / this->getCurvature(t);
	return r;
}

// CLOCKWISE CHECK
// ---------------
bool NURBS::isClockwise(const float& t) const
{
	CRAB::Vector4Df vup = cross(this->getNormal(t), this->getTangent(t)).to_unitary();
	float dotP = dot(vup, this->getNormalUp(t));
	if (dotP > 0.0f)
		return true;
	else return false;
}