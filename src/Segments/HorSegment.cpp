#include "HorSegment.h"
#include "Line.h"
#include "CircularArc.h"

// DEFAULT CONSTRUCTOR
HorSegment::HorSegment()
{
}

// OVERLOAD CONSTRUCTOR (Straight Line)
// ------------------------------------
HorSegment::HorSegment(const glm::vec3& _p0, const glm::vec3& _p1)
{
	this->segment = new Line(_p0, _p1);
	this->transition = false;
}
// OVERLOAD CONSTRUCTOR (Horizontal Curve)
// ---------------------------------------
HorSegment::HorSegment(const glm::vec3& _p0, const glm::vec3& _p1, const glm::vec3& _p2)
{
	this->segment = new CircularArc(_p0, _p1, _p2);
	this->transition = false;
}

// OVERLOAD CONSTRUCTOR (Circular Arc with Transition Curve)
// ---------------------------------------------------------
HorSegment::HorSegment(const glm::vec3& _p0, const glm::vec3& _p1, const glm::vec3& _p2, const float& _kB)
{
	this->segment = new CircularArc(_p0, _p1, _p2);
	this->transition = true;
	this->spiral.kA = 0.0f;
	this->spiral.kB = _kB;
	//this->spiral.S = _S;
	// Comprimento mínimo do trecho em espiral (critério dinâmico)
	float Vp = 80.0f; // km/h
	float Rc = 1.0f / _kB;
	this->spiral.S = 0.036 * powf(Vp, 3.0f) / Rc;
}

// DESTRUCTOR
// ----------
HorSegment::~HorSegment()
{
}

// RETURN DISCRETIZED HORIZONTAL CURVE WITH SPIRAL TRANSITION SYMMETRIC
// --------------------------------------------------------------------
std::vector<Geometry*> HorSegment::HorizontalCurve() const
{
	std::vector<Geometry*> StartSpiral;
	std::vector<Geometry*> EndSpiral;
	std::vector<Geometry*> FinalCurve;

	// Circular Curve
	CRAB::Vector4Df SC, PI, CS;

	// Normal total
	CRAB::Vector4Df N;
	
	/* -------------- * Start Spiral * -------------- */
	{
		// INPUT
		CRAB::Vector4Df A = segment->getStart4DPoint();
		CRAB::Vector4Df B = segment->getEnd4DPoint();
		CRAB::Vector4Df V = segment->getMid4DPoint();

		// AUXILIARY CALCULATIONS
		CRAB::Vector4Df tanA = (V - A).to_unitary();
		CRAB::Vector4Df AB = (B - A).to_unitary();
		CRAB::Vector4Df normal = CRAB::cross(tanA, AB).to_unitary();
		N = normal;

		float h = (spiral.kB - spiral.kA) / spiral.n;
		float coef = spiral.S * h / ((spiral.kB - spiral.kA) * 2.0f);

		// INITIALIZE
		CRAB::Vector4Df p0, p1, p2;
		p0 = A;

		// DISCRETE CLOTHOID
		for (int i = 0; i <= spiral.n; i++)
		{
			if (i == 0 && spiral.kA == 0.0f)
			{
				p2 = p0 + (tanA * (spiral.S / (2.0f * spiral.n)));
				// Output
				glm::vec3 start_point = { p0.x, p0.y, p0.z };
				glm::vec3 end_point = { p2.x, p2.y, p2.z };
				StartSpiral.push_back(new Line(start_point, end_point));
				p0 = p2;
				i++;
			}

			// Local parameters
			float k = spiral.kA + i * h;
			float w = spiral.S * k / (spiral.n * 2.0f);
			float teta = coef * (2.0f * i * spiral.kA + powf(i, 2.0f) * h);
			if (i > 0) {
				teta -= w;
				if (i < spiral.n)
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
			StartSpiral.push_back(new CircularArc(p0, p1, p2));
			p0 = p2;
		}
		SC = StartSpiral.back()->getEnd4DPoint();
	}
	
	/* -------------- * End Spiral * -------------- */
	{
		// INPUT
		CRAB::Vector4Df A = segment->getEnd4DPoint();
		CRAB::Vector4Df B = segment->getStart4DPoint();
		CRAB::Vector4Df V = segment->getMid4DPoint();

		// AUXILIARY CALCULATIONS
		CRAB::Vector4Df tanA = (V - A).to_unitary();
		CRAB::Vector4Df AB = (B - A).to_unitary();
		CRAB::Vector4Df normal = CRAB::cross(tanA, AB).to_unitary();

		float h = (spiral.kB - spiral.kA) / spiral.n;
		float coef = spiral.S * h / ((spiral.kB - spiral.kA) * 2.0f);

		// INITIALIZE
		CRAB::Vector4Df p0, p1, p2;
		p0 = A;

		// DISCRETE CLOTHOID
		for (int i = 0; i <= spiral.n; i++)
		{
			if (i == 0 && spiral.kA == 0.0f)
			{
				p2 = p0 + (tanA * (spiral.S / (2.0f * spiral.n)));
				// Output
				glm::vec3 start_point = { p0.x, p0.y, p0.z };
				glm::vec3 end_point = { p2.x, p2.y, p2.z };
				EndSpiral.push_back(new Line(start_point, end_point));
				p0 = p2;
				i++;
			}

			// Local parameters
			float k = spiral.kA + i * h;
			float w = spiral.S * k / (spiral.n * 2.0f);
			float teta = coef * (2.0f * i * spiral.kA + powf(i, 2.0f) * h);
			if (i > 0) {
				teta -= w;
				if (i < spiral.n)
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
			EndSpiral.push_back(new CircularArc(p2, p1, p0)); // inverted
			p0 = p2;
		}
		CS = EndSpiral.back()->getStart4DPoint();
	}

	/* -------------- * Circular Curve * -------------- */
	{
		// Raio da curva circular
		float Rc = 1.0f / this->spiral.kB;
		// Corda da curva circular
		CRAB::Vector4Df Chord = CS - SC;
		// Ângulo central circular / 2.0f
		float w = asinf(Chord.length() / (2.0f * Rc));
		// Tangente
		float T = Rc * tanf(w);
		// Matriz de rotação da corda
		w = (w * 180.0f) / M_PI;
		CRAB::Matrix4 R_chord = CRAB::rotateArbitrary(w, N);
		// Ponto de interseção das tangentes
		PI = SC + ((R_chord * Chord).to_unitary() * T);
	}
	
	/* -------------- * Final Curve * -------------- */
	{
		FinalCurve = StartSpiral;
		FinalCurve.push_back(new CircularArc(SC, PI, CS));
		for (int i = EndSpiral.size() - 1; i >= 0; i--)
			FinalCurve.push_back(EndSpiral[i]);
	}

	return FinalCurve;
}