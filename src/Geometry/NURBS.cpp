#include "NURBS.h"

#include <iostream>

// DEFAULT CONSTRUCTOR
// -------------------
NURBS::NURBS()
{
	// control points
	//this->points.push_back({ 0.0f, -10.0f, 0.0f, 1.0f });
	this->points.push_back({ 0.0f, 0.0f, 2.0f, 1.0f });
	this->points.push_back({ 0.0f, 5.0f, 2.0f, 1.0f });
	this->points.push_back({ 5.0f, 5.0f, 2.0f, 1.0f });
	//this->points.push_back({ 15.0f, 5.0f, 0.0f, 1.0f });

	/*this->points.push_back({ -10.0f, 0.0f, 0.0f, 1.0f });
	this->points.push_back({ -5.0f, 0.0f, 0.0f, 1.0f });
	this->points.push_back({ -5.0f, 0.0f, 5.0f, 1.0f });
	this->points.push_back({ 0.0f, 0.0f, 5.0f, 1.0f });
	this->points.push_back({ 10.0f, 0.0f, -10.0f, 1.0f });*/

	/*this->points.push_back({ 0.0f, 0.0f, 0.0f, 1.0f });
	this->points.push_back({ 5.0f, 0.0f, 0.0f, 1.0f });
	this->points.push_back({ 5.0f, 10.0f, 0.0f, 1.0f });
	this->points.push_back({ 0.0f, 10.0f, 0.0f, 1.0f });
	this->points.push_back({ -5.0f, 10.0f, 0.0f, 1.0f });
	this->points.push_back({ -5.0f, 0.0f, 0.0f, 1.0f });
	this->points.push_back({ 0.0f, 0.0f, 0.0f, 1.0f });*/

	// weights
	this->w = { 1.0f, 1.0f, 1.0f };
	//this->w = { 1.0f, sinf(M_PI / 4.0f), 1.0f };
	//this->w = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
	//this->w = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
	//this->w = { 1.0f, 1.0f, sinf(M_PI / 4.0f), 1.0f, 1.0f };
	//this->w = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
	//this->w = { 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f };

	// degree
	//this->p = 2;
	this->p = this->points.size() - 1;

	// knot vector
	int m = points.size() + this->p;
	int n = points.size() - 1;
	for (int i = 0; i <= m; i++)
	{
		if (i <= p)
			this->T.push_back(0.0f);
		else if (i > n)
			this->T.push_back(1.0f);
		else
		{
			float u = float(i - p) / float(n - p + 1);
			this->T.push_back(u);
		}
	}
	//this->T = { 0.0f, 0.0f, 0.0f, 0.359f, 0.641f, 1.0f, 1.0f , 1.0f };
	//this->T = { 0.0f, 0.0f, 0.0f, 0.25f, 0.5f, 0.5f, 0.75f, 1.0f, 1.0f , 1.0f };
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
	if (isnan(left) || isinf(left)) left = 0.0f;

	float right = this->dN(i + 1, p - 1, t) * p / (this->T[i + p + 1] - this->T[i + 1]);
	if (isnan(right) || isinf(right)) right = 0.0f;

	return left - right;
}

// DERIVATIVES
// -----------
CRAB::Vector4Df NURBS::deriv(const float& t) const
{
	int span = this->FindSpan(t);

	CRAB::Vector4Df A = { 0.0f, 0.0f, 0.0f, 0.0f };
	for (int i = 0; i <= this->p; i++)
	{
		int index = span - this->p + i;
		A += (this->points[index] * this->w[index]) * this->N(index, this->p, t);
	}

	CRAB::Vector4Df derivA = { 0.0f, 0.0f, 0.0f, 0.0f };
	for (int i = 0; i <= this->p; i++)
	{
		int index = span - this->p + i;
		derivA += (this->points[index] * this->w[index]) * this->dN(index, this->p, t);
	}

	float D = 0.0f;
	for (int j = 0; j <= this->p; j++)
	{
		int index = span - this->p + j;
		D += this->w[index] * this->N(index, this->p, t);
	}

	float derivD = 0.0f;
	for (int j = 0; j <= this->p; j++)
	{
		int index = span - this->p + j;
		derivD += this->w[index] * this->dN(index, this->p, t);
	}

	return (derivA * D - A * derivD) / powf(D, 2.0f);
}
CRAB::Vector4Df NURBS::deriv2(const float& t) const
{
	int span = this->FindSpan(t);

	CRAB::Vector4Df A = { 0.0f, 0.0f, 0.0f, 0.0f };
	for (int i = 0; i <= this->p; i++)
	{
		int index = span - this->p + i;
		A += (this->points[index] * this->w[index]) * this->N(index, this->p, t);
	}

	CRAB::Vector4Df derivA2 = { 0.0f, 0.0f, 0.0f, 0.0f };
	for (int i = 0; i <= this->p; i++)
	{
		int index = span - this->p + i;
		derivA2 += (this->points[index] * this->w[index]) * this->dN2(index, this->p, t);
	}

	float D = 0.0f;
	for (int j = 0; j <= this->p; j++)
	{
		int index = span - this->p + j;
		D += this->w[index] * this->N(index, this->p, t);
	}

	float derivD = 0.0f;
	for (int j = 0; j <= this->p; j++)
	{
		int index = span - this->p + j;
		derivD += this->w[index] * this->dN(index, this->p, t);
	}

	float derivD2 = 0.0f;
	for (int j = 0; j <= this->p; j++)
	{
		int index = span - this->p + j;
		derivD2 += this->w[index] * this->dN2(index, this->p, t);
	}

	return ((derivA2 * D - A * derivD2) * (powf(D, 2.0f) - 2.0f * derivD)) / powf(D, 4.0f);
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
		position += (this->points[index] * this->w[index]) * this->N(index, this->p, t) / d;
	}

	/*CRAB::Vector4Df result = position;
	std::cout << "pos = [" << result.x << "; " << result.y << "; " << result.z << "; " << result.w << "]" << std::endl;*/

	return position;

	////CRAB::Vector4Df result = this->Ck(0, t);
	//CRAB::Vector4Df result = { 0.0f, 0.0f, 0.0f, 1.0f };
	////std::cout << "pos = [" << result.x << "; " << result.y << "; " << result.z << "; " << result.w << "]" << std::endl;
	//return result;
}

// RETURNS THE CURVE TANGENT
// -------------------------
CRAB::Vector4Df NURBS::getTangent(const float& t) const
{
	/*CRAB::Vector4Df result = this->deriv(t).to_unitary();
	std::cout << "tan = [" << result.x << "; " << result.y << "; " << result.z << "; " << result.w << "]" << std::endl;
	return result;*/

	return this->deriv(t).to_unitary();

	/*CRAB::Vector4Df result = this->Ck(1, t).to_unitary();
	std::cout << "tan = [" << result.x << "; " << result.y << "; " << result.z << "; " << result.w << "]" << std::endl;
	return result;*/
}

// RETURNS THE CURVE NORMAL
// ------------------------
CRAB::Vector4Df NURBS::getNormal(const float& t) const
{
	CRAB::Vector4Df d1 = this->deriv(t);
	CRAB::Vector4Df d2 = this->deriv2(t);
	CRAB::Vector4Df n = d2 - d1 * (dot(d2, d1) / d1.lengthsq());

	/*std::cout << "\nNURBS" << std::endl;
	std::cout << "d1.length() = " << d1.length() << std::endl;
	std::cout << "d2.length() = " << d2.length() << std::endl;*/

	/*CRAB::Vector4Df result = n.to_unitary();
	std::cout << "normal = [" << result.x << "; " << result.y << "; " << result.z << "; " << result.w << "]" << std::endl;
	return result;*/

	return n.to_unitary();
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
	CRAB::Vector4Df d1 = this->deriv(t);
	CRAB::Vector4Df d2 = this->deriv2(t);
	float k = cross(d1, d2).length() / powf(d1.length(), 3.0f);

	return k;
}

// RETURNS THE RADIUS OF CURVATURE
// -------------------------------
float NURBS::getRadius(const float& t) const
{
	float r = 1.0f / this->getCurvature(t);

	//std::cout << "r = " << r << std::endl;
	if (r == INFINITY)
		return 0.0f;

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


	// ********************************************* //
	// TESTES
	// ********************************************* //

float NURBS::Nk(const int& k, const int& i, const int& p, const float& t) const
{
	if (p == 0)
	{
		if (t >= this->T[i] && t < this->T[i + 1])
			return 1.0f;
		else if (t == this->T[i + 1] && t == this->T.back())
			return 1.0f;
		else return 0.0f;
	}
	else if (k >= p)
		return 0;

	float left = this->Nk(k, i, p - 1, t) * (t - this->T[i]) / (this->T[i + p] - this->T[i]);
	if (isnan(left)) left = 0.0f;

	float right = this->Nk(k, i + 1, p - 1, t) * (this->T[i + p + 1] - t) / (this->T[i + p + 1] - this->T[i + 1]);
	if (isnan(right)) right = 0.0f;

	return (left + right) * p / (p - k);
}

CRAB::Vector4Df NURBS::Ak(const int& k, const float& t, const int& span) const
{
	CRAB::Vector4Df ak = { 0.0f, 0.0f, 0.0f, 1.0f };
	for (int i = 0; i <= this->p; i++)
	{
		int index = span - this->p + i;
		ak += (this->points[index] * this->w[index]) * this->Nk(k, index, this->p, t) / this->Wk(0, t, span);
	}

	CRAB::Vector4Df result = ak;
	std::cout << "\tak = [" << result.x << "; " << result.y << "; " << result.z << "; " << result.w << "]" << std::endl;

	return ak;
}

float NURBS::Wk(const int& k, const float& t, const int& span) const
{
	float wk = 0.0f;
	for (int i = 0; i <= this->p; i++)
	{
		int index = span - this->p + i;
		wk += this->w[index] * this->Nk(k, index, this->p, t);

		std::cout << "Nk = " << this->Nk(k, index, this->p, t) << std::endl;
	}

	float result = wk;
	std::cout << "\twk = " << result << std::endl;

	return wk;
}

CRAB::Vector4Df NURBS::Ck(const int& k, const float& t) const
{
	int span = this->FindSpan(t);

	CRAB::Vector4Df right = { 0.0f, 0.0f, 0.0f, 0.0f };
	for (int i = 1; i <= k; i++)
	{
		right += this->Ck(k - i, t) * this->Wk(i, t, span) * this->binomialCoefficient(k, i) / this->Wk(0, t, span);
	}

	CRAB::Vector4Df result = right;
	std::cout << "\tright = [" << result.x << "; " << result.y << "; " << result.z << "; " << result.w << "]" << std::endl;

	return (this->Ak(k, t, span) - right)/* / this->Wk(0, t, span)*/;
}

int NURBS::binomialCoefficient(const int& n, const int& i) const
{
	if (i == 0 || i == n)
		return 1;
	return this->binomialCoefficient(n - 1, i - 1) + this->binomialCoefficient(n - 1, i);
}