#include "NURBS.h"

namespace Primitive
{
    // Full circle with a square
    NURBS Circle(const float& radius)
    {
        // control points
        std::vector<CRAB::Vector4Df> control_points;
        control_points.push_back(CRAB::Vector4Df{ 0.0f, -radius, 0.0f, 1.0f });
        control_points.push_back(CRAB::Vector4Df{ radius, -radius, 0.0f, 1.0f });
        control_points.push_back(CRAB::Vector4Df{ radius, 0.0f, 0.0f, 1.0f });
        control_points.push_back(CRAB::Vector4Df{ radius, radius, 0.0f, 1.0f });
        control_points.push_back(CRAB::Vector4Df{ 0.0f, radius, 0.0f, 1.0f });
        control_points.push_back(CRAB::Vector4Df{ -radius, radius, 0.0f, 1.0f });
        control_points.push_back(CRAB::Vector4Df{ -radius, 0.0f, 0.0f, 1.0f });
        control_points.push_back(CRAB::Vector4Df{ -radius, -radius, 0.0f, 1.0f });
        control_points.push_back(CRAB::Vector4Df{ 0.0f, -radius, 0.0f, 1.0f });

        // weights
        float w = exp2f(0.5f) / 2.0f;
        std::vector<float> weights = { 1.0f, w, 1.0f, w, 1.0f, w, 1.0f, w, 1.0f };

        // knot vector
        std::vector<float> knot_vector = { 0.0f, 0.0f, 0.0f, 0.25f, 0.25f, 0.5f, 0.5f, 0.75f, 0.75f, 1.0f, 1.0f, 1.0f };

        return NURBS(control_points, 2, weights, knot_vector);
    }

    NURBS CircularArc(const CRAB::Vector4Df& p0, const CRAB::Vector4Df& p1, const CRAB::Vector4Df& p2)
    {
        // control points
        std::vector<CRAB::Vector4Df> control_points;
        control_points.push_back(p0);
        control_points.push_back(p1);
        control_points.push_back(p2);

        // weights
        CRAB::Vector4Df p0p1 = (p1 - p0).to_unitary();
        CRAB::Vector4Df p0p2 = (p2 - p0).to_unitary();
        float w = CRAB::dot(p0p1, p0p2);
        std::vector<float> weights = { 1.0f, w, 1.0f};

        // knot vector
        std::vector<float> knot_vector = { 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f };

        return NURBS(control_points, 2, weights, knot_vector);
    }
}