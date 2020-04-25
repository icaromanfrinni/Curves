#include "NURBS.h"

#include <iostream>

// DEFAULT CONSTRUCTOR
// -------------------
NURBS::NURBS()
{
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
		if (t >= this->T[i] && t < this->T[i + 1])
			return 1.0f;
		else return 0.0f;

	float N1 = N(i, p - 1, t) * (t - this->T[i]) / (this->T[i + p] - this->T[i]);
	if (isnan(N1)) N1 = 0.0f;

	float N2 = N(i + 1, p - 1, t) * (this->T[i + p + 1] - t) / (this->T[i + p + 1] - this->T[i + 1]);
	if (isnan(N2)) N2 = 0.0f;

	return N1 + N2;
}

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
	// Endpoint interpolation
	if (t == 0.0f)
		return this->points.front();
	if (t == 1.0f)
		return this->points.back();

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