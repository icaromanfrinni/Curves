#include "Alignment.h"


// DEFAULT CONSTRUCTOR
// -------------------
Alignment::Alignment()
{
}

// DEFAULT CONSTRUCTOR
// -------------------
Alignment::Alignment(const std::vector<Segment*>& horizontal, const std::vector<Segment*>& vertical)
{
	this->path2Dh = NURBS(horizontal);
	this->path2Dv = NURBS(vertical);
	this->path3D = NURBS(this->path2Dh, this->path2Dv);
}

// DESTRUCTOR
// ----------
Alignment::~Alignment()
{
}

// RETURN
// ------
CRAB::Vector4Df Alignment::getPosition(const float& t) const
{
	glm::vec3 p = this->path3D.getPosition(t);
	return CRAB::Vector4Df{ p.x, p.y, p.z, 1.0f };
}
CRAB::Vector4Df Alignment::getTangent(const float& t) const
{
	glm::vec3 tan = this->path3D.getTangent(t);
	return CRAB::Vector4Df{ tan.x, tan.y, tan.z, 0.0f };
}
CRAB::Vector4Df Alignment::getNormalUp(const float& t) const
{
	//std::cout << "\n\tt = " << t << std::endl;

	glm::vec3 pTarget = this->path3D.getPosition(t);
	pTarget.y = 0.0f; // plane-XZ

	float low = 0.0f;
	float mid = 0.5f;
	float high = 1.0f;
	glm::vec3 pTest = this->path2Dh.getPosition(mid);
	while (glm::distance(pTarget, pTest) > SMALL_NUMBER && fabsf(low - high) > SMALL_NUMBER)
	{
		if (mid < t)
			low = mid;
		else high = mid;
		mid = (high + low) / 2.0f;

		pTest = this->path2Dh.getPosition(mid);

		/*std::cout << "low = " << low << std::endl;
		std::cout << "mid = " << mid << std::endl;
		std::cout << "high = " << high << std::endl;
		std::cout << "glm::distance(pTarget, pTest) = " << glm::distance(pTarget, pTest) << std::endl;*/
		//system("pause");
	}

	glm::vec3 glm_n = this->path3D.getNormalUp(t);
	CRAB::Vector4Df n = { glm_n.x, glm_n.y, glm_n.z, 0.0f };

	float hor_radius = this->path2Dh.getRadius(mid);
	if (hor_radius == 0.0f)
		return n;

	float tan_alfa = 0.0044f * powf(60.0f, 2.0f) / hor_radius;
	if (tan_alfa > SLOPE_MAX)
		tan_alfa = SLOPE_MAX;
	float alfa = atanf(tan_alfa) * 180.0f / M_PI;
	if (this->path2Dh.isClockwise(mid))
		alfa = alfa * (-1.0f);
	CRAB::Matrix4 R = CRAB::rotateArbitrary(alfa, this->getTangent(t));
	return (R * n).to_unitary() * hor_radius;
}