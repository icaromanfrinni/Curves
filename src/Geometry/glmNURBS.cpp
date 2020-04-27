#include "glmNURBS.h"

#include <iostream>

// DEFAULT CONSTRUCTOR
// -------------------
glmNURBS::glmNURBS()
{
	// control points
	//this->points.push_back({ 0.0f, -10.0f, 0.0f, 1.0f });
	this->points.push_back({ 0.0f, 0.0f, 0.0f });
	this->points.push_back({ 0.0f, 5.0f, 0.0f });
	this->points.push_back({ 5.0f, 5.0f, 0.0f });
	//this->points.push_back({ 15.0f, 5.0f, 0.0f, 1.0f });

	/*this->points.push_back({ -10.0f, 0.0f, 0.0f, 1.0f });
	this->points.push_back({ -5.0f, 0.0f, 0.0f, 1.0f });
	this->points.push_back({ -5.0f, 0.0f, 5.0f, 1.0f });
	this->points.push_back({ 0.0f, 0.0f, 5.0f, 1.0f });
	this->points.push_back({ 10.0f, 0.0f, -10.0f, 1.0f });*/

	/*this->points.push_back({ 0.0f, 0.0f, 0.0f });
	this->points.push_back({ 5.0f, 0.0f, 0.0f });
	this->points.push_back({ 5.0f, 10.0f, 0.0f });
	this->points.push_back({ 0.0f, 10.0f, 0.0f });
	this->points.push_back({ -5.0f, 10.0f, 0.0f });
	this->points.push_back({ -5.0f, 0.0f, 0.0f });
	this->points.push_back({ 0.0f, 0.0f, 0.0f });*/

	// weights
	//this->w = { 1.0f, 1.0f, 1.0f };
	this->w = { 1.0f, sinf(3.14159f / 4.0f), 1.0f };
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

// DESTRUCTOR
// ----------
glmNURBS::~glmNURBS()
{
}

// BASIS FUNCTIONS
// ---------------
float glmNURBS::N(const int& i, const int& p, const float& t) const
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
float glmNURBS::dN(const int& i, const int& p, const float& t) const
{
	float left = this->N(i, p - 1, t) * p / (this->T[i + p] - this->T[i]);
	if (isnan(left)) left = 0.0f;

	float right = this->N(i + 1, p - 1, t) * p / (this->T[i + p + 1] - this->T[i + 1]);
	if (isnan(right)) right = 0.0f;

	return left - right;
}
float glmNURBS::dN2(const int& i, const int& p, const float& t) const
{
	float left = this->dN(i, p - 1, t) * p / (this->T[i + p] - this->T[i]);
	if (isnan(left) || isinf(left)) left = 0.0f;

	float right = this->dN(i + 1, p - 1, t) * p / (this->T[i + p + 1] - this->T[i + 1]);
	if (isnan(right) || isinf(right)) right = 0.0f;

	return left - right;
}

// DERIVATIVES
// -----------
glm::vec3 glmNURBS::deriv(const float& t) const
{
	int span = this->FindSpan(t);

	glm::vec3 A = { 0.0f, 0.0f, 0.0f };
	for (int i = 0; i <= this->p; i++)
	{
		int index = span - this->p + i;
		A += (this->points[index] * this->w[index]) * this->N(index, this->p, t);
	}

	glm::vec3 derivA = { 0.0f, 0.0f, 0.0f };
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
glm::vec3 glmNURBS::deriv2(const float& t) const
{
	int span = this->FindSpan(t);

	glm::vec3 A = { 0.0f, 0.0f, 0.0f };
	for (int i = 0; i <= this->p; i++)
	{
		int index = span - this->p + i;
		A += (this->points[index] * this->w[index]) * this->N(index, this->p, t);
	}

	glm::vec3 derivA2 = { 0.0f, 0.0f, 0.0f };
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

		std::cout << "index = " << index << std::endl;
		std::cout << "dN2 = " << this->dN2(index, this->p, t) << std::endl;
	}

	std::cout << "D = " << D << std::endl;
	std::cout << "derivD = " << derivD << std::endl;
	std::cout << "derivD2 = " << derivD2 << std::endl;

	return ((derivA2 * D - A * derivD2) * (powf(D, 2.0f) - 2.0f * derivD)) / powf(D, 4.0f);
}

// FIND THE ith KNOT SPAN
// ----------------------
int glmNURBS::FindSpan(const float& t) const
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
glm::vec3 glmNURBS::getPosition(const float& t) const
{
	glm::vec3 position = { 0.0f, 0.0f, 0.0f };
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

	/*glm::vec3 result = position;
	std::cout << "pos = [" << result.x << "; " << result.y << "; " << result.z << "; " << result.w << "]" << std::endl;*/

	return position;

	////glm::vec3 result = this->Ck(0, t);
	//glm::vec3 result = { 0.0f, 0.0f, 0.0f, 1.0f };
	////std::cout << "pos = [" << result.x << "; " << result.y << "; " << result.z << "; " << result.w << "]" << std::endl;
	//return result;
}

// RETURNS THE CURVE TANGENT
// -------------------------
glm::vec3 glmNURBS::getTangent(const float& t) const
{
	/*glm::vec3 result = this->deriv(t).to_unitary();
	std::cout << "tan = [" << result.x << "; " << result.y << "; " << result.z << "; " << result.w << "]" << std::endl;
	return result;*/

	return glm::normalize(this->deriv(t));

	/*glm::vec3 result = this->Ck(1, t).to_unitary();
	std::cout << "tan = [" << result.x << "; " << result.y << "; " << result.z << "; " << result.w << "]" << std::endl;
	return result;*/
}

// RETURNS THE CURVE NORMAL
// ------------------------
glm::vec3 glmNURBS::getNormal(const float& t) const
{
	glm::vec3 d1 = this->deriv(t);
	glm::vec3 d2 = this->deriv2(t);
	glm::vec3 n = d2 - d1 * (glm::dot(d2, d1) / powf(glm::length(d1), 2.0f));

	std::cout << "\nglm::NURBS" << std::endl;
	std::cout << "glm::length(d1) = " << glm::length(d1) << std::endl;
	std::cout << "glm::length(d2) = " << glm::length(d2) << std::endl;

	/*glm::vec3 result = n.to_unitary();
	std::cout << "normal = [" << result.x << "; " << result.y << "; " << result.z << "; " << result.w << "]" << std::endl;
	return result;*/

	return glm::normalize(n);
}

// RETURNS THE CURVE NORMAL UP (Yaw vector)
// ----------------------------------------
glm::vec3 glmNURBS::getNormalUp(const float& t) const
{
	glm::vec3 tan = this->getTangent(t);
	glm::vec3 vUp = { 0.0f, 1.0f, 0.0f };
	glm::vec3 vAux = glm::normalize(glm::cross(vUp, tan));
	glm::vec3 n = glm::normalize(glm::cross(tan, vAux));
	return n;
}

// RETURNS THE CURVE BINORMAL
// --------------------------
glm::vec3 glmNURBS::getBinormal(const float& t) const
{
	/*glm::vec3 result1 = this->getTangent(t);
	glm::vec3 result2 = this->getNormal(t);
	glm::vec3 result3 = glm::cross(this->getTangent(t), this->getNormal(t));
	std::cout << "tan = [" << result1.x << "; " << result1.y << "; " << result1.z << "]" << std::endl;
	std::cout << "norm = [" << result2.x << "; " << result2.y << "; " << result2.z << "]" << std::endl;
	std::cout << "cross = [" << result3.x << "; " << result3.y << "; " << result3.z << "]" << std::endl;*/

	return glm::normalize(glm::cross(this->getTangent(t), this->getNormal(t)));
	//return glm::cross(this->getTangent(t), this->getNormal(t));
}

// RETURNS THE CURVATURE
// ---------------------
float glmNURBS::getCurvature(const float& t) const
{
	glm::vec3 d1 = this->deriv(t);
	glm::vec3 d2 = this->deriv2(t);
	float k = cross(d1, d2).length() / powf(d1.length(), 3.0f);

	return k;
}

// RETURNS THE RADIUS OF CURVATURE
// -------------------------------
float glmNURBS::getRadius(const float& t) const
{
	float r = 1.0f / this->getCurvature(t);

	//std::cout << "r = " << r << std::endl;
	if (r == INFINITY)
		return 0.0f;

	return r;
}

// CLOCKWISE CHECK
// ---------------
bool glmNURBS::isClockwise(const float& t) const
{
	glm::vec3 vup = glm::normalize(glm::cross(this->getNormal(t), this->getTangent(t)));
	float dotP = glm::dot(vup, this->getNormalUp(t));
	if (dotP > 0.0f)
		return true;
	else return false;
}