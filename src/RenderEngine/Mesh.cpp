#include "Mesh.h"

// constructor
Mesh::Mesh(std::vector<Mesh::Vertex> vertices)
{
    this->vertices = vertices;
    this->primitive_type = GL_LINES;
    this->with_points = true;
    // now that we have all the required data, set the vertex buffers and its attribute pointers.
    setupMesh();
}
// overload constructor (from Bézier curve)
Mesh::Mesh(const Bezier& curve)
{
    this->primitive_type = GL_LINE_STRIP;
    this->with_points = false;
    
    Mesh::Vertex v;
    v.Color = { 1.0f, 1.0f, 1.0f };

    for (int i = 0; i <= STEPS; i++)
    {
        float t = float(i) / STEPS;
        CRAB::Vector4Df position = curve.getPosition(t);
        v.Position = { position.x, position.y, position.z };
        this->vertices.push_back(v);
    }

    setupMesh();
}
// overload constructor (from Bspline curve)
Mesh::Mesh(const Bspline& curve)
{
    this->primitive_type = GL_LINE_STRIP;
    this->with_points = true;

    Mesh::Vertex v;
    v.Color = { 1.0f, 1.0f, 0.0f };

    for (int i = 0; i <= STEPS; i++)
    {
        float t = float(i) / STEPS;
        CRAB::Vector4Df position = curve.getPosition(t);
        v.Position = { position.x, position.y, position.z };
        this->vertices.push_back(v);
    }

    setupMesh();
}
// overload constructor (from NURBS curve)
Mesh::Mesh(const NURBS& curve)
{
    this->primitive_type = GL_LINE_STRIP;
    this->with_points = false;

    Mesh::Vertex v;
    v.Color = { 1.0f, 0.0f, 1.0f };

    for (int i = 0; i <= STEPS; i++)
    {
        float t = float(i) / STEPS;
        CRAB::Vector4Df position = curve.getPosition(t);
        v.Position = { position.x, position.y, position.z };
        this->vertices.push_back(v);
    }

    setupMesh();
}
// overload constructor (from glmNURBS curve)
Mesh::Mesh(const glmNURBS& curve)
{
    this->primitive_type = GL_LINE_STRIP;
    this->with_points = false;

    Mesh::Vertex v;
    v.Color = { 1.0f, 0.0f, 1.0f };

    for (int i = 0; i <= STEPS; i++)
    {
        float t = float(i) / STEPS;
        v.Position = curve.getPosition(t);
        this->vertices.push_back(v);
    }

    setupMesh();
}
// overload constructor (from Control points)
Mesh::Mesh(const std::vector<CRAB::Vector4Df> &points)
{
    this->primitive_type = GL_LINE_STRIP;
    this->with_points = true;

    Mesh::Vertex v;
    v.Color = { 0.2f, 0.2f, 0.2f };

    for (int i = 0; i < points.size(); i++)
    {
        v.Position = { points[i].x, points[i].y, points[i].z };
        this->vertices.push_back(v);
    }

    setupMesh();
}
// overload constructor (from glm::Control points)
Mesh::Mesh(const std::vector<glm::vec3>& points)
{
    this->primitive_type = GL_LINE_STRIP;
    this->with_points = true;

    Mesh::Vertex v;
    v.Color = { 0.8f, 0.8f, 0.8f };

    for (int i = 0; i < points.size(); i++)
    {
        v.Position = points[i];
        this->vertices.push_back(v);
    }

    setupMesh();
}
// destructor
Mesh::~Mesh()
{
}

// render the mesh
void Mesh::Draw(Shader shader)
{
    // draw mesh
    glBindVertexArray(VAO);
    glDrawArrays(this->primitive_type, 0, vertices.size());
    if (this->with_points)
        glDrawArrays(GL_POINTS, 0, vertices.size());
}

// initializes all the buffer objects/arrays
void Mesh::setupMesh()
{
    // create buffers/arrays
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    // load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // A great thing about structs is that their memory layout is sequential for all its items.
    // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
    // again translates to 3/2 floats which translates to a byte array.
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    // set the vertex attribute pointers
    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex Color
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));

    glBindVertexArray(0);
}
