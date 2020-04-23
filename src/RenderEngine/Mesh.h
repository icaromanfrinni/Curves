#pragma once

#ifndef MESH_H
#define MESH_H

#include <glad\glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include "Shader.h"
#include "Bezier.h"
#include "Bspline.h"
#include "NURBS.h"

#define STEPS 50

class Mesh
{
public:

    struct Vertex {
        // position
        glm::vec3 Position;
        // color
        glm::vec3 Color;
    };

    /*  Mesh Data  */
    std::vector<Vertex> vertices;
    unsigned int VAO;

    /*  Functions  */
    // constructor
    Mesh(std::vector<Vertex> vertices);
    // overload constructor (from Bézier curve)
    Mesh(const Bezier& curve);
    // overload constructor (from Bspline curve)
    Mesh(const Bspline& curve);
    // overload constructor (from NURBS curve)
    Mesh(const NURBS& curve);
    // overload constructor (from Control points)
    Mesh(const std::vector<CRAB::Vector4Df> &points);
	// destructor
	~Mesh();

    // render the mesh
    void Draw(Shader shader);

private:
    /*  Render data  */
    unsigned int VBO/*, EBO*/;

    // OpenGL primitive type
    GLenum primitive_type;

    // With points
    bool with_points;

    /*  Functions    */
    
    // initializes all the buffer objects/arrays
    void setupMesh();
};

#endif