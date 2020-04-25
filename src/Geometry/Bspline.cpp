#include "Bspline.h"

#include <iostream>

// DEFAULT CONSTRUCTOR
// -------------------
Bspline::Bspline()
{
	// control points
	this->points.push_back(CRAB::Vector4Df{ 0.0f, 5.0f, 0.0f, 1.0f });
	this->points.push_back(CRAB::Vector4Df{ 1.0f, 1.0f, 0.0f, 1.0f });
	this->points.push_back(CRAB::Vector4Df{ 3.0f, 2.0f, 0.0f, 1.0f });
	this->points.push_back(CRAB::Vector4Df{ 4.0f, 1.0f, 0.0f, 1.0f });
	this->points.push_back(CRAB::Vector4Df{ 5.0f, -1.0f, 0.0f, 1.0f });

	// degree
	this->p = 4;

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

// DESTRUCTOR
// ----------
Bspline::~Bspline()
{
}

// BASIS FUNCTIONS
// ---------------
float Bspline::N(const int& i, const int& p, const float& t) const
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
	//std::cout << "N = " << left << " + ";
	if (isnan(left)) left = 0.0f;

	float right = this->N(i + 1, p - 1, t) * (this->T[i + p + 1] - t) / (this->T[i + p + 1] - this->T[i + 1]);
	//std::cout << right << std::endl;
	if (isnan(right)) right = 0.0f;

	return left + right;
}
float Bspline::dN(const int& i, const int& p, const float& t) const
{
	float left = this->N(i, p - 1, t) * p / (this->T[i + p] - this->T[i]);
	if (isnan(left)) left = 0.0f;

	float right = this->N(i + 1, p - 1, t) * p / (this->T[i + p + 1] - this->T[i + 1]);
	if (isnan(right)) right = 0.0f;

	return left - right;
}

// FIND THE ith KNOT SPAN
// ----------------------
int Bspline::FindSpan(const float& t) const
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
CRAB::Vector4Df Bspline::getPosition(const float& t) const
{
	CRAB::Vector4Df position = { 0.0f, 0.0f, 0.0f, 1.0f };
	int span = this->FindSpan(t);

	std::cout << "\nt = " << t << std::endl;

	for (int i = 0; i <= this->p; i++)
	{
		position += points[span - this->p + i] * this->N(span - this->p + i, this->p, t);
		std::cout << "P[" << span - this->p + i << "] * N[" << span - this->p + i << ", " << this->p << "](" << t << ") = " << this->N(span - this->p + i, this->p, t) << std::endl;
	}
	return position;
}

// RETURNS THE CURVE TANGENT
// -------------------------
CRAB::Vector4Df Bspline::getTangent(const float& t) const
{
	CRAB::Vector4Df tangent = { 0.0f, 0.0f, 0.0f, 1.0f };
	int span = this->FindSpan(t);

	for (int i = 0; i <= this->p; i++)
	{
		tangent += points[span - this->p + i] * this->dN(span - this->p + i, this->p, t);
	}

	return tangent.to_unitary();
}