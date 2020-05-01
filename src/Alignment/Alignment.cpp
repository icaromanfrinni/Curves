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
CRAB::Vector4Df Alignment::getNormal(const float& t) const
{
	glm::vec3 n = this->path3D.getNormal(t);
	return CRAB::Vector4Df{ n.x, 0.0f, n.z, 0.0f }.to_unitary(); // horizontal (y = 0)
}
CRAB::Vector4Df Alignment::getNormalUp(const float& t) const
{
	glm::vec3 n = this->path3D.getNormalUp(t);
	return CRAB::Vector4Df{ n.x, n.y, n.z, 0.0f };
}
float Alignment::getRadius(const float& t) const
{
	return this->path3D.getRadius(t);
}