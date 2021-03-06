#include "NURBS.h"

#include <iostream>

// DEFAULT CONSTRUCTOR
// -------------------
NURBS::NURBS()
{
	// ***********************************************************************************
	// TESTE DE CURVA VERTICAL
	
	/*this->points.push_back({ 0.0f, 0.0f, 0.0f });
	this->points.push_back({ 5.0f, 0.0f, 0.0f });
	this->points.push_back({ 7.5f, 4.3301f, 0.0f });
	this->points.push_back({ 8.75f, 6.4952f, 0.0f });
	this->points.push_back({ 10.0f, 8.6603f, 0.0f });
	this->points.push_back({ 12.5f, 12.9904f, 0.0f });
	this->points.push_back({ 17.5f, 12.9904f, 0.0f });

	this->w = { 1.0f, sqrtf(3.0f) / 2.0f, 1.0f, 1.0f, 1.0f, sqrtf(3.0f) / 2.0f, 1.0f };
	this->P = 2;
	this->T = { 0.0f, 0.0f, 0.0f, 0.392f, 0.392f, 0.608f, 0.608f, 1.0f, 1.0f, 1.0f };

	std::cout << "L = " << this->getLength() << " m" << std::endl;*/

	// ***********************************************************************************
	// TESTE C�RCULO

	/*this->points.push_back({ 0.0f, 0.0f, 0.0f });
	this->points.push_back({ 5.0f, 0.0f, 0.0f });
	this->points.push_back({ 5.0f, 10.0f, 0.0f });
	this->points.push_back({ 0.0f, 10.0f, 0.0f });
	this->points.push_back({ -5.0f, 10.0f, 0.0f });
	this->points.push_back({ -5.0f, 0.0f, 0.0f });
	this->points.push_back({ 0.0f, 0.0f, 0.0f });

	this->w = { 1.0f, 0.5f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f };
	this->P = 2;
	this->T = { 0.0f, 0.0f, 0.0f, 0.25f, 0.5f, 0.5f, 0.75f, 1.0f, 1.0f, 1.0f };

	std::cout << "L = " << this->getLength() << " m" << std::endl;*/

	// ***********************************************************************************
	// TESTE CLOT�IDE

	/*this->points.push_back({ 30.0f, 0.0f, 0.0f });
	this->points.push_back({ 30.0f, 15.0f, 0.0f });
	this->points.push_back({ 0.0f, 15.0f, 0.0f });*/

	/*this->points.push_back({ 1.75f, 2.75f, 0.0f });
	this->points.push_back({ 1.75f, 4.0f, 0.0f });
	this->points.push_back({ 3.0f, 5.0f, 0.0f });
	this->points.push_back({ 5.0f, 5.0f, 0.0f });
	this->points.push_back({ 5.75f, 3.5f, 0.0f });
	this->points.push_back({ 6.5f, 4.75f, 0.0f });*/

	/*this->points.push_back({ 0.0f, 0.0f, 0.0f });
	this->points.push_back({ 0.0f, 2.0f, 0.0f });
	this->points.push_back({ 0.0f, 4.0f, 0.0f });
	this->points.push_back({ 0.0f, 6.0f, 0.0f });
	this->points.push_back({ 1.0f, 7.0f, 0.0f });
	this->points.push_back({ 3.8284f, 9.8284f, 0.0f });
	this->points.push_back({ 6.6569f, 7.0f, 0.0f });*/

	// ***********************************************************************************
	// TESTE CONTINUIDADE

	this->points.push_back({ 0.0f, 0.0f, 0.0f });
	this->points.push_back({ 0.0f, 10.0f, 0.0f });
	this->points.push_back({ 0.0f, 10.0f, 0.0f });
	this->points.push_back({ 0.0f, 10.0f, 0.0f });
	this->points.push_back({ 0.0f, 15.0f, 0.0f });
	this->points.push_back({ 5.0f, 15.0f, 0.0f });
	this->points.push_back({ 5.0f, 15.0f, 0.0f });
	this->points.push_back({ 5.0f, 15.0f, 0.0f });
	this->points.push_back({ 15.0f, 15.0f, 0.0f });

	// weights
	for (int i = 0; i < this->points.size(); i++)
		this->w.push_back(1.0f);

	//this->w = { 1.0f, 1.0f, 1.0f };
	//this->w = { 2.0f, 1.0f, 1.0f };
	//this->w = { 1.0f, cosf(70.0f * M_PI / 180.0f), 1.0f };
	//this->w = { 1.0f, h, 1.0f };
	//this->w = { 1.0f, sinf(3.14159f / 4.0f), 1.0f };
	//this->w = { 1.0f, 1.0f, 1.0f, 1.0f };
	//this->w = { 1.0f, 0.5f, 0.5f, 1.0f };
	//this->w = { 1.0f, sinf(3.14159f / 4.0f) / 2.0f, sinf(3.14159f / 4.0f) / 2.0f, 1.0f };
	//this->w = { 1.0f, 0.7f, 1.0f, 0.7f, 1.0f };
	//this->w = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
	//this->w = { 1.0f, sinf(M_PI / 4.0f), 0.5f, sinf(M_PI / 4.0f), 1.0f };
	//this->w = { 1.0f, 1.0f, sinf(3.14159f / 4.0f), 1.0f, 1.0f };
	//this->w = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
	//this->w = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
	//this->w = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, sinf(M_PI / 4.0f), 1.0f };
	//this->w = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };

	// degree
	this->P = this->points.size() - 1;

	// knot vector
	int m = points.size() + this->P;
	int n = points.size() - 1;
	for (int i = 0; i <= m; i++)
	{
		if (i <= this->P)
			this->T.push_back(0.0f);
		else if (i > n)
			this->T.push_back(1.0f);
		else
		{
			float u = float(i - this->P) / float(n - this->P + 1);
			this->T.push_back(u);
		}
	}
	//this->T = { 0.0f, 0.0f, 0.0f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f };
	//this->T = { 0.0f, 0.0f, 0.0f, 0.359f, 0.641f, 1.0f, 1.0f , 1.0f };
	//this->T = { 0.0f, 0.0f, 0.0f, 0.25f, 0.5f, 0.75f, 1.0f, 1.0f, 1.0f };
	//this->T = { 0.0f, 0.0f, 0.0f, 0.2957f, 0.2957f, 0.5356f, 0.5356f, 1.0f, 1.0f, 1.0f };
	//this->T = { 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f };
	
	// SEGMENTOS DE ARCOS
	/*this->points.push_back({ 0.0f, 0.0f, 0.0f });
	this->points.push_back({ 1.7633f, 0.0f, 0.0f });
	this->points.push_back({ 3.4204f, 0.6031f, 0.0f });
	this->points.push_back({ 4.5424f, 1.0115f, 0.0f });
	this->points.push_back({ 5.4572f, 1.7791f, 0.0f });
	this->points.push_back({ 6.0850f, 2.3059f, 0.0f });
	this->points.push_back({ 6.4947f, 3.0156f, 0.0f });
	this->points.push_back({ 6.7513f, 3.4600f, 0.0f });
	this->points.push_back({ 6.8404f, 3.9654f, 0.0f });
	this->w = { 1.0f, 0.95f, 1.0f, 0.95f, 1.0f, 0.95f, 1.0f, 0.95f, 1.0f };
	this->P = 2;
	this->T = { 0.0f, 0.0f, 0.0f, 0.411f, 0.411f, 0.6893f, 0.6893f, 0.8803f, 0.8803f, 1.0f, 1.0f, 1.0f };*/
}

// OVERLOAD CONSTRUCTOR (from Points)
// ----------------------------------
NURBS::NURBS(const std::vector<glm::vec3>& _points)
	: points(_points)
{
	// weights
	for (int i = 0; i < this->points.size(); i++)
		this->w.push_back(1.0f);

	// degree
	//this->P = this->points.size() - 1;
	this->P = 2;

	// knot vector
	int m = points.size() + this->P;
	int n = points.size() - 1;
	for (int i = 0; i <= m; i++)
	{
		if (i <= this->P)
			this->T.push_back(0.0f);
		else if (i > n)
			this->T.push_back(1.0f);
		else
		{
			float u = float(i - this->P) / float(n - this->P + 1);
			this->T.push_back(u);
		}
	}
}

// OVERLOAD CONSTRUCTOR (from Segments)
// ------------------------------------
NURBS::NURBS(const std::vector<Geometry*> &segments)
{
	//std::cout << "segments.size() = " << segments.size() << std::endl;

	this->P = 2;
	float distance = 0.0;
	this->T = { 0.0f, 0.0f, 0.0f };
	for (int i = 0; i < segments.size(); i++)
	{
		if (i == 0)
		{
			this->points.push_back(segments[i]->getStartPoint());
			this->w.push_back(1.0f);
		}
		this->points.push_back(segments[i]->getMidPoint());
		this->w.push_back(segments[i]->midPointWeight());
		this->points.push_back(segments[i]->getEndPoint());
		this->w.push_back(1.0f);
		distance += segments[i]->getLength();
		this->T.insert(T.end(), 2, distance);
	}
	this->T.insert(T.end(), 1, distance);
	for (int i = 0; i < this->T.size(); i++)
		this->T[i] = this->T[i] / distance;
}

// OVERLOAD CONSTRUCTOR (from two curves)
// --------------------------------------
NURBS::NURBS(const NURBS& horizontal_curve, const NURBS& vertical_curve)
{
	/* ----------------------- DEGREE ----------------------- */
	
	this->P = 2;

	/* ------------------- CONTROL POINTS ------------------- */

	// ALGORITHM 1
	// Varredura nas duas curvas (n�o funciona, pois o ponto na horizontal n�o corresponde com a proje��o do ponto na vertical)

	/*for (int i = 0; i <= ELEMENTS; i++)
	{
		float t = float(i) / ELEMENTS;
		this->points.push_back(horizontal_curve.getPosition(t));
		this->points.back().y = vertical_curve.getPosition(t).y;
	}*/

	// ALGORITHM 2
	// Binaty Search: qual o ponto na vertical q sua proje��o corresponde com o ponto da horizontal?

	// PROJE��O DOS PONTOS EXTREMOS S�O COINCIDENTES

	// First control point
	this->points.push_back(horizontal_curve.points.front());
	this->points.back().y = vertical_curve.points.front().y;

	// PARA OS DEMAIS PONTOS:
	float Lx = (vertical_curve.points.back() - vertical_curve.points.front()).x; // comprimento da proje��o na horizontal
	float low = 0.0f; // par�metro t,min (a cada intera��o, o m�nimo caminho em dire��o ao m�ximo, diminuindo a regi�o de busca)
	for (int i = 1; i < ELEMENTS; i++)
	{
		float t = float(i) / ELEMENTS;
		this->points.push_back(horizontal_curve.getPosition(t)); // coordenadas em planta (UTM)
		float high = 1.0f; // atualiza o t,m�x
		float mid = (low + high) / 2.0f; // t,med = par�metro do ponto "teste"
		float dX = (vertical_curve.getPosition(mid) - vertical_curve.points.front()).x / Lx; // proje��o da curva na horizontal at� o ponto "teste"
		while (fabsf(dX - t) > SMALL_NUMBER) // enquanto o delta_X obtido for diferente do 't' corrente
		{
			if (dX < t)
				low = mid; // atualiza t,min
			else high = mid; // atualiza t,max
			mid = (low + high) / 2.0f; // calcula novo t.med
			dX = (vertical_curve.getPosition(mid) - vertical_curve.points.front()).x / Lx; // delta_X correspondente ao t,med
		}
		this->points.back().y = vertical_curve.getPosition(mid).y; // cota de eleva��o (Z)
		low = mid; // atualiza t,min: n�o realiza busca na regi�o anterior, j� percorrida
	}

	// Last control point
	this->points.push_back(horizontal_curve.points.back());
	this->points.back().y = vertical_curve.points.back().y;

	/* ---------------------- WEIGHTS ---------------------- */

	for (int i = 0; i < this->points.size(); i++)
		this->w.push_back(1.0f);

	/* -------------------- KNOT VECTOR -------------------- */

	int m = points.size() + this->P;
	int n = points.size() - 1;
	for (int i = 0; i <= m; i++)
	{
		if (i <= this->P)
			this->T.push_back(0.0f);
		else if (i > n)
			this->T.push_back(1.0f);
		else
		{
			float u = float(i - this->P) / float(n - this->P + 1);
			this->T.push_back(u);
		}
	}
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
glm::vec3 NURBS::deriv(const float& t) const
{
	//std::cout << "\nDERIV 1" << std::endl;

	/*if (this->P <= 1)
		return glm::vec3(0.0f);*/

	int span = this->FindSpan(t);

	/*glm::vec3 A = { 0.0f, 0.0f, 0.0f };
	for (int i = 0; i <= this->P; i++)
	{
		int index = span - this->P + i;
		A += (this->points[index] * this->w[index]) * this->N(index, this->P, t);
	}

	glm::vec3 derivA = { 0.0f, 0.0f, 0.0f };
	for (int i = 0; i <= this->P; i++)
	{
		int index = span - this->P + i;
		derivA += (this->points[index] * this->w[index]) * this->dN(index, this->P, t);
	}

	float D = 0.0f;
	for (int j = 0; j <= this->P; j++)
	{
		int index = span - this->P + j;
		D += this->w[index] * this->N(index, this->P, t);
	}

	float derivD = 0.0f;
	for (int j = 0; j <= this->P; j++)
	{
		int index = span - this->P + j;
		derivD += this->w[index] * this->dN(index, this->P, t);
	}*/

	glm::vec3 A = { 0.0f, 0.0f, 0.0f };
	glm::vec3 dA = { 0.0f, 0.0f, 0.0f };
	float W = 0.0f;
	float dW = 0.0f;
	for (int i = 0; i <= this->P; i++)
	{
		int index = span - this->P + i;
		float Base = this->N(index, this->P, t);
		float dBase = this->dN(index, this->P, t);
		A += (this->points[index] * this->w[index]) * Base;
		dA += (this->points[index] * this->w[index]) * dBase;
		W += this->w[index] * Base;
		dW += this->w[index] * dBase;
	}

	return (dA * W - A * dW) / powf(W, 2.0f);
}
glm::vec3 NURBS::deriv2(const float& t) const
{
	//std::cout << "\nDERIV 2" << std::endl;

	/*if (this->P <= 2)
		return glm::vec3(0.0f);*/

	int span = this->FindSpan(t);

	//glm::vec3 A = { 0.0f, 0.0f, 0.0f };
	//for (int i = 0; i <= this->P; i++)
	//{
	//	int index = span - this->P + i;
	//	A += (this->points[index] * this->w[index]) * this->N(index, this->P, t);
	//}

	//glm::vec3 derivA = { 0.0f, 0.0f, 0.0f };
	//for (int i = 0; i <= this->P; i++)
	//{
	//	int index = span - this->P + i;
	//	derivA += (this->points[index] * this->w[index]) * this->dN(index, this->P, t);
	//}

	//glm::vec3 derivA2 = { 0.0f, 0.0f, 0.0f };
	//for (int i = 0; i <= this->P; i++)
	//{
	//	int index = span - this->P + i;
	//	derivA2 += (this->points[index] * this->w[index]) * this->dN2(index, this->P, t);
	//}

	//float D = 0.0f;
	//for (int j = 0; j <= this->P; j++)
	//{
	//	int index = span - this->P + j;
	//	D += this->w[index] * this->N(index, this->P, t);
	//}

	//float derivD = 0.0f;
	//for (int j = 0; j <= this->P; j++)
	//{
	//	int index = span - this->P + j;
	//	derivD += this->w[index] * this->dN(index, this->P, t);
	//}

	//float derivD2 = 0.0f;
	//for (int j = 0; j <= this->P; j++)
	//{
	//	int index = span - this->P + j;
	//	derivD2 += this->w[index] * this->dN2(index, this->P, t);

	//	/*std::cout << "index = " << index << std::endl;
	//	std::cout << "dN2 = " << this->dN2(index, this->P, t) << std::endl;*/
	//}

	glm::vec3 A = { 0.0f, 0.0f, 0.0f };
	glm::vec3 dA = { 0.0f, 0.0f, 0.0f };
	glm::vec3 dA2 = { 0.0f, 0.0f, 0.0f };
	float W = 0.0f;
	float dW = 0.0f;
	float dW2 = 0.0f;
	for (int i = 0; i <= this->P; i++)
	{
		int index = span - this->P + i;
		float Base = this->N(index, this->P, t);
		float dBase = this->dN(index, this->P, t);
		float dBase2 = this->dN2(index, this->P, t);
		A += (this->points[index] * this->w[index]) * Base;
		dA += (this->points[index] * this->w[index]) * dBase;
		dA2 += (this->points[index] * this->w[index]) * dBase2;
		W += this->w[index] * Base;
		dW += this->w[index] * dBase;
		dW2 += this->w[index] * dBase2;
	}

	/*std::cout << "A = [" << A.x << "; " << A.y << "; " << A.z << "]" << std::endl;
	std::cout << "derivA2 = [" << derivA2.x << "; " << derivA2.y << "; " << derivA2.z << "]" << std::endl;*/

	/*std::cout << "D = " << D << std::endl;
	std::cout << "derivD = " << derivD << std::endl;
	std::cout << "derivD2 = " << derivD2 << std::endl;*/

	//return (((derivA2 * D) - (A * derivD2)) * (powf(D, 2.0f) - 2.0f * derivD)) / powf(D, 4.0f);
	return (((dA2 * W) - (A * dW2)) * W - ((dA * W) - (A * dW)) * 2.0f) / powf(W, 3.0f);
}

// FIND THE ith KNOT SPAN
// ----------------------
int NURBS::FindSpan(const float& t) const
{
	int n = points.size() - 1;
	if (t == T[n + 1])
		return n;

	int low = this->P;
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
glm::vec3 NURBS::getPosition(const float& t) const
{
	//std::cout << "t = " << t << std::endl;

	glm::vec3 position = { 0.0f, 0.0f, 0.0f };
	int span = this->FindSpan(t);

	// denominator
	float d = 0.0f;
	for (int j = 0; j <= this->P; j++)
	{
		int index = span - this->P + j;
		d += this->w[index] * this->N(index, this->P, t);
	}

	for (int i = 0; i <= this->P; i++)
	{
		int index = span - this->P + i;
		position += (this->points[index] * this->w[index]) * this->N(index, this->P, t) / d;
	}

	//glm::vec3 result = position;
	//std::cout << "pos = [" << result.x << "; " << result.y << "; " << result.z << "]" << std::endl;

	return position;

	////glm::vec3 result = this->Ck(0, t);
	//glm::vec3 result = { 0.0f, 0.0f, 0.0f, 1.0f };
	////std::cout << "pos = [" << result.x << "; " << result.y << "; " << result.z << "; " << result.w << "]" << std::endl;
	//return result;
}

// RETURNS THE CURVE TANGENT
// -------------------------
glm::vec3 NURBS::getTangent(const float& t) const
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
glm::vec3 NURBS::getNormal(const float& t) const
{
	//std::cout << "\tt = " << t << std::endl;

	glm::vec3 d1 = this->deriv(t);
	glm::vec3 d2 = this->deriv2(t);
	glm::vec3 n = d2 - d1 * (glm::dot(d2, d1) / powf(glm::length(d1), 2.0f));

	//std::cout << "d1 = [" << d1.x << "; " << d1.y << "; " << d1.z << "]" << std::endl;
	//std::cout << "d2 = [" << d2.x << "; " << d2.y << "; " << d2.z << "]" << std::endl;

	/*std::cout << "\nglm::NURBS" << std::endl;
	std::cout << "glm::length(d1) = " << glm::length(d1) << std::endl;
	std::cout << "glm::length(d2) = " << glm::length(d2) << std::endl;*/

	//glm::vec3 result = glm::normalize(n);
	//std::cout << "normal = [" << result.x << "; " << result.y << "; " << result.z << "]\n" << std::endl;
	//return result;

	return glm::normalize(n);
}

// RETURNS THE CURVE NORMAL UP (Yaw vector)
// ----------------------------------------
glm::vec3 NURBS::getNormalUp(const float& t) const
{
	glm::vec3 tan = this->getTangent(t);
	glm::vec3 vUp = { 0.0f, 1.0f, 0.0f };
	glm::vec3 vAux = glm::normalize(glm::cross(vUp, tan));
	glm::vec3 n = glm::normalize(glm::cross(tan, vAux));
	return n;
}

// RETURNS THE CURVE BINORMAL
// --------------------------
glm::vec3 NURBS::getBinormal(const float& t) const
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
float NURBS::getCurvature(const float& t) const
{
	glm::vec3 d1 = this->deriv(t);
	glm::vec3 d2 = this->deriv2(t);
	float k = glm::length(glm::cross(d1, d2)) / powf(glm::length(d1), 3.0f);

	return k;
}

// RETURNS THE RADIUS OF CURVATURE
// -------------------------------
float NURBS::getRadius(const float& t) const
{
	float c = this->getCurvature(t);	
	if (c < SMALL_NUMBER)
		return 0.0f;

	float r = 1.0f / this->getCurvature(t);
	std::cout << "\n" << std::endl;
	std::cout << "R(" << t << ") = " << r << std::endl;
	std::cout << "L(" << t << ") = " << this->getDistance(t) << std::endl;
	return r;
}

// RETURNS THE LENGTH OF CURVE
// ---------------------------
float NURBS::getLength() const
{
	float L = 0.0f;
	
	glm::vec3 A = this->getPosition(0.0f);
	for (int i = 1; i <= ELEMENTS; i++)
	{
		float t = float(i) / ELEMENTS;
		glm::vec3 B = this->getPosition(t);
		L += glm::distance(A, B);
		A = B;
	}
	return L;
}

// RETURNS THE DISTANCE FROM START
// -------------------------------
float NURBS::getDistance(const float& t) const
{
	float D = 0.0f;
	
	glm::vec3 A = this->getPosition(0.0f);
	for (int i = 1; i <= ELEMENTS; i++)
	{
		float u = t * float(i) / ELEMENTS;
		glm::vec3 B = this->getPosition(u);
		D += glm::distance(A, B);
		A = B;
	}

	//std::cout << "distance = " << D << std::endl;

	return D;
}

// CLOCKWISE CHECK
// ---------------
bool NURBS::isClockwise(const float& t) const
{
	glm::vec3 vup = glm::normalize(glm::cross(this->getNormal(t), this->getTangent(t)));
	float dotP = glm::dot(vup, this->getNormalUp(t));
	if (dotP > 0.0f)
		return true;
	else return false;
}

// RETURNS THE PARAMETER
// ---------------------
float NURBS::findParameter(const glm::vec3& P) const
{
	// Initial parameter
	float u = 0.0f;

	// Test point
	glm::vec3 C = this->getPosition(u);
	glm::vec3 PC = C - P;
	glm::vec3 dC = this->deriv(u);
	glm::vec3 d2C = this->deriv2(u);

	// Euclidean distance
	float distance = glm::distance(P, C);
	// Cosine
	float cosine = fabsf(glm::dot(dC, PC)) / (glm::length(dC) * distance);

	// Newton interaction
	while (distance > SMALL_NUMBER/* || cosine > SMALL_NUMBER*/)
	{
		float f = glm::dot(dC, PC);
		float df = glm::dot(d2C, PC) + powf(glm::length(dC), 2.0f);
		float new_u = u - f / df;

		// Criteria 3: in the range
		/*if (new_u < 0.0f) new_u = 0.0f;
		if (new_u > 1.0f) new_u = 1.0f;*/
		// Criteria 4: does not change significantly
		float e = glm::length(dC * (new_u - u));
		if (e <= SMALL_NUMBER) break;

		// update
		C = this->getPosition(new_u);
		PC = C - P;
		dC = this->deriv(new_u);
		d2C = this->deriv2(new_u);
		u = new_u;

		std::cout << "u = " << u << std::endl;

		// Criteria 1: point coincidence
		distance = glm::distance(P, C);
		// Criteria 2: zero cosine
		cosine = fabsf(glm::dot(dC, PC)) / (glm::length(dC) * distance);
		
		
		std::cout << "distance = " << distance << std::endl;
		std::cout << "cosine = " << cosine << std::endl;
	}

	return u;
}