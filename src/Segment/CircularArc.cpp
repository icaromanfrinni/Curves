#include "CircularArc.h"

// DEFAULT CONSTRUCTOR
// -------------------
CircularArc::CircularArc()
{
}
// OVERLOAD CONSTRUCTOR
// --------------------
CircularArc::CircularArc(const glm::vec3 &_p0, const glm::vec3 &_p1, const glm::vec3 &_p2)
	: p0(_p0), p1(_p1), p2(_p2)
{
}
// DESTRUCTOR
// ----------
CircularArc::~CircularArc()
{
}

// RETURN
// ------
glm::vec3 CircularArc::getStartPoint() const
{
	return p0;
}
glm::vec3 CircularArc::getMidPoint() const
{
	return p1;
}
glm::vec3 CircularArc::getEndPoint() const
{
	return p2;
}
float CircularArc::getLength() const
{
	glm::vec3 tan1 = p1 - p0;
	glm::vec3 tan2 = p2 - p1;
	float AC = acosf(glm::dot(glm::normalize(tan1), glm::normalize(tan2)));
	float R = glm::length(tan1) / tanf(AC / 2.0f);
	return AC * R;
}

// RETURN THE WEIGHT OF THE CONTROL POINT
// --------------------------------------
float CircularArc::midPointWeight() const
{
	glm::vec3 p0p1 = p1 - p0;
	glm::vec3 p0p2 = p2 - p0;
	return glm::dot(glm::normalize(p0p1), glm::normalize(p0p2));
}