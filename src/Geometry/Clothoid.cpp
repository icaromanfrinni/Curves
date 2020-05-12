#include "Clothoid.h"

// DEFAULT CONSTRUCTOR
// -------------------
Clothoid::Clothoid()
{
	// INPUT
	int n = 5;
	float kA = 1.0f / 15.0f;
	float kB = 1.0f / 10.0f;
	CRAB::Vector4Df A = { 0.0f, 0.0f, 0.0f, 1.0f };
	CRAB::Vector4Df B = { 20.0f, 10.0f, 0.0f, 1.0f };
	CRAB::Vector4Df PI = { 10.0f, 0.0f, 0.0f, 1.0f };
	//float S = 20.0;

	// AUXILIARY CALCULATIONS
	CRAB::Vector4Df tanA = (PI - A).to_unitary();
	CRAB::Vector4Df tanB = (B - PI).to_unitary();
	float tetaB = acosf(CRAB::dot(tanA, tanB));
	CRAB::Vector4Df AB = (B - A).to_unitary();
	CRAB::Vector4Df normal = CRAB::cross(tanA, AB).to_unitary();
	
	float S = 2.0f * tetaB / (kA + kB);
	std::cout << "S = " << S << std::endl;
	float h = (kB - kA) / n;
	float coef = S * h / ((kB - kA) * 2.0f);

	// INITIALIZE
	CRAB::Vector4Df p0, p1, p2;
	p0 = A;

	// DISCRETE CLOTHOID
	for (int i = 0; i <= n; i++)
	{
		if (i == 0 && kA == 0.0f)
		{
			p2 = p0 + (tanA * (S / (2.0f * n)));
			// Output
			glm::vec3 start_point = { p0.x, p0.y, p0.z };
			glm::vec3 end_point = { p2.x, p2.y, p2.z };
			segments.push_back(new Line(start_point, end_point));
			p0 = p2;
			i++;
		}

		// Local parameters
		float k = kA + i * h;
		float w = S * k / (n * 2.0f);
		float teta = coef * (2.0f * i * kA + powf(i, 2.0f) * h);
		if (i > 0) {
			teta -= w;
			if (i < n)
				w = w * 2.0f;
		}
		teta = (teta * 180.0f) / M_PI;
		
		// Tangent
		CRAB::Matrix4 R_tan = CRAB::rotateArbitrary(-teta, normal);
		CRAB::Vector4Df tan = R_tan * tanA;

		// Radius
		float R = 1.0f / k;
		CRAB::Vector4Df r = CRAB::cross(normal, tan).to_unitary();
		
		// Center
		CRAB::Vector4Df center = p0 + (r * R);

		// Mid point
		float T = R * tanf(w / 2.0f);
		p1 = p0 + (tan * T);

		// End point
		w = (w * 180.0f) / M_PI;
		CRAB::Matrix4 R_radius = CRAB::rotateArbitrary(-w, normal);
		r = R_radius * r;
		p2 = center - (r * R);

		// Output
		glm::vec3 start_point = { p0.x, p0.y, p0.z };
		glm::vec3 mid_point = { p1.x, p1.y, p1.z };
		glm::vec3 end_point = { p2.x, p2.y, p2.z };
		segments.push_back(new CircularArc(start_point, mid_point, end_point));
		p0 = p2;
	}

	// DEBUG
	CRAB::Vector4Df tanFinal = (p2 - p1).to_unitary();
	std::cout << "tan final = [" << tanFinal.x << "; " << tanFinal.y << "; " << tanFinal.z << "]" << std::endl;
	std::cout << "tanB = [" << tanB.x << "; " << tanB.y << "; " << tanB.z << "]" << std::endl;
	std::cout << "B = [" << p2.x << "; " << p2.y << "; " << p2.z << "]" << std::endl;
}
// DESTRUCTOR
// ----------
Clothoid::~Clothoid()
{
}