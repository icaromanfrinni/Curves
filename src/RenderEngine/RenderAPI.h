
#pragma once

#include <iostream>
#include <Windows.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION

#include "Skybox.h"
#include "Shader.h"
#include "Camera.h"
#include "Mesh.h"

#include "Line.h"
#include "CircularArc.h"
#include "Alignment.h"

#define DEBUG 0

namespace CRAB
{
    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    void processInput(GLFWwindow* window);

    // settings
    const unsigned int SCR_WIDTH = 1280;
    const unsigned int SCR_HEIGHT = 720;

    // camera
    Camera camera;
    float lastX = SCR_WIDTH / 2.0f;
    float lastY = SCR_HEIGHT / 2.0f;
    bool firstMouse = true;

    // projection matrix
    glm::mat4 projection = glm::mat4(1.0f);

    // timing
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    // mouse event handlers
    int TheKeyState = GLFW_KEY_LEFT_CONTROL;

    // List of Meshes
    std::vector<Mesh> ourMesh_List;

    int main()
    {
        // glfw: initialize and configure
        // ------------------------------
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
        GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CRAB::BRIDGE", NULL, NULL);
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetScrollCallback(window, scroll_callback);

        // tell GLFW to capture our mouse
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        // glad: load all OpenGL function pointers
        // ---------------------------------------
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
        }

        // configure global opengl state
        // -----------------------------
        glEnable(GL_DEPTH_TEST);

        // build and compile our shader zprogram
        // -------------------------------------
        Shader ourShader("shaders/shader.vs", "shaders/shader.fs");

        // load grid
        // ---------
        std::vector<Mesh::Vertex> grid;
        {
            Mesh::Vertex p;
            glm::vec3 color;
            // XZ-axis
            for (int i = -5; i < 6; i++)
                for (int k = -5; k < 6; k++)
                {
                    if (i == 0) color = { 0.0f, 0.0f, 0.5f };
                    else if (k == 0) color = { 0.5f, 0.0f, 0.0f };
                    else color = { 0.2f, 0.2f, 0.2f };

                    p.Position = { i, 0.0f, -5.0f };  p.Color = color;
                    grid.push_back(p);
                    p.Position = { i, 0.0f, 5.0f };  p.Color = color;
                    grid.push_back(p);
                    p.Position = { -5.0f, 0.0f, k };  p.Color = color;
                    grid.push_back(p);
                    p.Position = { 5.0f, 0.0f, k };  p.Color = color;
                    grid.push_back(p);
                }
            // Y-axis
            color = { 0.0f, 0.5f, 0.0f };
            p.Position = { 0.0f, 0.0f, 0.0f };  p.Color = color;
            grid.push_back(p);
            p.Position = { 0.0f, 1.0f, 0.0f };  p.Color = color;
            grid.push_back(p);
        }
        Mesh grid_Mesh(grid);

        // load curves
        // -----------

#if DEBUG == 1

        Bspline c1;
        ourMesh_List.push_back(Mesh(c1));
        ourMesh_List.push_back(Mesh(c1.points));

        Bezier c2;
        ourMesh_List.push_back(Mesh(c2));
        ourMesh_List.push_back(Mesh(c2.points));

        NURBS c3;
        ourMesh_List.push_back(Mesh(c3));
        ourMesh_List.push_back(Mesh(c3.points));

        NURBS c4;
        ourMesh_List.push_back(Mesh(c4));
        ourMesh_List.push_back(Mesh(c4.points));

         Bezier
        std::vector<Mesh::Vertex> bezier_vector;
        for (int i = 0; i <= STEPS; i++)
        {
            float t = float(i) / STEPS;
            CRAB::Vector4Df tail = c2.getPosition(t);
            CRAB::Vector4Df head;
            Mesh::Vertex v;

            // tangent
            head = tail + c2.getTangent(t);
            v.Color = { 1.0f, 1.0f, 1.0f };
            v.Position = { tail.x, tail.y, tail.z };
            bezier_vector.push_back(v);
            v.Color = { 0.5f, 0.5f, 1.0f };
            v.Position = { head.x, head.y, head.z };
            bezier_vector.push_back(v);

            // normal
            head = tail + c2.getNormal(t) * c2.getRadius(t);
            v.Color = { 1.0f, 1.0f, 1.0f };
            v.Position = { tail.x, tail.y, tail.z };
            bezier_vector.push_back(v);
            v.Color = { 0.5f, 1.0f, 0.5f };
            v.Position = { head.x, head.y, head.z };
            bezier_vector.push_back(v);

            // binormal
            head = tail + c2.getBinormal(t);
            v.Color = { 1.0f, 1.0f, 1.0f };
            v.Position = { tail.x, tail.y, tail.z };
            bezier_vector.push_back(v);
            v.Color = { 0.5f, 1.0f, 1.0f };
            v.Position = { head.x, head.y, head.z };
            bezier_vector.push_back(v);
        }
        ourMesh_List.push_back(Mesh(bezier_vector));

        // NURBS
        std::vector<Mesh::Vertex> nurbs_vector;
        for (int i = 0; i <= STEPS; i++)
        {
            float t = float(i) / STEPS;
            CRAB::Vector4Df tail = c3.getPosition(t);
            CRAB::Vector4Df head;
            Mesh::Vertex v;

            if (c3.isClockwise(t))
                std::cout << "RIGHT" << std::endl;
            else std::cout << "LEFT" << std::endl;
            
            // tangent
            head = tail + c3.getTangent(t);
            v.Color = { 1.0f, 0.0f, 1.0f };
            v.Position = { tail.x, tail.y, tail.z };
            nurbs_vector.push_back(v);
            v.Color = { 0.5f, 0.0f, 1.0f };
            v.Position = { head.x, head.y, head.z };
            nurbs_vector.push_back(v);

            // normal
            head = tail + c3.getNormal(t) * c3.getRadius(t);
            v.Color = { 1.0f, 0.0f, 1.0f };
            v.Position = { tail.x, tail.y, tail.z };
            nurbs_vector.push_back(v);
            v.Color = { 0.5f, 1.0f, 0.5f };
            v.Position = { head.x, head.y, head.z };
            nurbs_vector.push_back(v);

            // normal up
            head = tail + c3.getNormalUp(t);
            v.Color = { 1.0f, 0.0f, 1.0f };
            v.Position = { tail.x, tail.y, tail.z };
            nurbs_vector.push_back(v);
            v.Color = { 1.0f, 0.0f, 0.5f };
            v.Position = { head.x, head.y, head.z };
            nurbs_vector.push_back(v);

            // binormal
            head = tail + c3.getBinormal(t);
            v.Color = { 1.0f, 0.0f, 1.0f };
            v.Position = { tail.x, tail.y, tail.z };
            nurbs_vector.push_back(v);
            v.Color = { 0.5f, 1.0f, 1.0f };
            v.Position = { head.x, head.y, head.z };
            nurbs_vector.push_back(v);
        }
        ourMesh_List.push_back(Mesh(nurbs_vector));

        // NURBS
        std::vector<Mesh::Vertex> NURBS_vector;
        for (int i = 0; i <= STEPS; i++)
        {
            float t = float(i) / STEPS;
            glm::vec3 tail = c4.getPosition(t);
            glm::vec3 head;
            Mesh::Vertex v;

            if (c4.isClockwise(t))
                std::cout << "RIGHT" << std::endl;
            else std::cout << "LEFT" << std::endl;
            
            // tangent
            head = tail + c4.getTangent(t);
            v.Color = { 1.0f, 0.0f, 1.0f };
            v.Position = tail;
            NURBS_vector.push_back(v);
            v.Color = { 0.5f, 0.0f, 1.0f };
            v.Position = head;
            NURBS_vector.push_back(v);

            // normal
            head = tail + c4.getNormal(t) *c4.getRadius(t);
            v.Color = { 1.0f, 0.0f, 1.0f };
            v.Position = tail;
            NURBS_vector.push_back(v);
            v.Color = { 0.5f, 1.0f, 0.5f };
            v.Position = head;
            NURBS_vector.push_back(v);

            // normal up
            head = tail + c4.getNormalUp(t);
            v.Color = { 1.0f, 0.0f, 1.0f };
            v.Position = tail;
            NURBS_vector.push_back(v);
            v.Color = { 1.0f, 0.0f, 0.5f };
            v.Position = head;
            NURBS_vector.push_back(v);

            // binormal
            head = tail + c4.getBinormal(t);
            v.Color = { 1.0f, 0.0f, 1.0f };
            v.Position = tail;
            NURBS_vector.push_back(v);
            v.Color = { 0.5f, 1.0f, 1.0f };
            v.Position = head;
            NURBS_vector.push_back(v);
        }
        ourMesh_List.push_back(Mesh(NURBS_vector));

#endif

        // load Alignments
        // ---------------
        
        // *********************************
        // ******* VIADUTO ANT SALES *******
        // *********************************

        /*std::vector<Segment*> grade;
        grade.push_back(new Line(glm::vec3(0.0f, 1.259f, 0.0f), glm::vec3(20.0f, 1.129f, 0.0f)));
        grade.push_back(new CircularArc(glm::vec3(20.0f, 1.129f, 0.0f), glm::vec3(39.82f, 1.00f, 0.0f), glm::vec3(60.0f, 2.259f, 0.0f)));
        grade.push_back(new Line(glm::vec3(60.0f, 2.259f, 0.0f), glm::vec3(167.04f, 8.935f, 0.0f)));
        grade.push_back(new CircularArc(glm::vec3(167.04f, 8.935f, 0.0f), glm::vec3(207.04f, 11.430f, 0.0f), glm::vec3(247.04f, 8.926f, 0.0f)));
        grade.push_back(new Line(glm::vec3(247.04f, 8.926f, 0.0f), glm::vec3(320.0f, 4.359f, 0.0f)));
        grade.push_back(new CircularArc(glm::vec3(320.0f, 4.359f, 0.0f), glm::vec3(350.0f, 2.481f, 0.0f), glm::vec3(380.0f, 3.429f, 0.0f)));
        grade.push_back(new Line(glm::vec3(380.0f, 3.429f, 0.0f), glm::vec3(400.0f, 4.061f, 0.0f)));
        
        std::vector<Segment*> road;
        road.push_back(new Line(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(22.44f, 0.0f, 50.44f)));
        road.push_back(new CircularArc(glm::vec3(22.44f, 0.0f, 50.44f), glm::vec3(53.60f, 0.0f, 120.46f), glm::vec3(120.52f, 0.0f, 83.10f)));
        road.push_back(new Line(glm::vec3(120.52f, 0.0f, 83.10f), glm::vec3(202.16f, 0.0f, 37.52f)));*/

        // *******************************************************
        // *********************** EXEMPLO ***********************
        // *******************************************************

        std::vector<Segment*> grade;
        grade.push_back(new Line(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(20.0f, 5.359f, 0.0f)));
        grade.push_back(new CircularArc(glm::vec3(20.0f, 5.359f, 0.0f), glm::vec3(38.208f, 10.2378f, 0.0f), glm::vec3(56.416f, 5.359f, 0.0f)));
        grade.push_back(new Line(glm::vec3(56.416f, 5.359f, 0.0f), glm::vec3(76.416f, 0.0f, 0.0f)));

        std::vector<Segment*> road;
        road.push_back(new Line(glm::vec3(0.0f, 0.0f, 25.0f), glm::vec3(20.0f, 0.0f, 25.0f)));
        road.push_back(new CircularArc(glm::vec3(20.0f, 0.0f, 25.0f), glm::vec3(30.0f, 0.0f, 25.0f), glm::vec3(30.0f, 0.0f, 15.0f)));
        road.push_back(new Line(glm::vec3(30.0f, 0.0f, 15.0f), glm::vec3(30.0f, 0.0f, 10.0f)));
        road.push_back(new CircularArc(glm::vec3(30.0f, 0.0f, 10.0f), glm::vec3(30.0f, 0.0f, 0.0f), glm::vec3(40.0f, 0.0f, 0.0f)));
        road.push_back(new Line(glm::vec3(40.0f, 0.0f, 0.0f), glm::vec3(60.0f, 0.0f, 0.0f)));

        // *******************************************************

#if DEBUG == 2

        NURBS vertical(grade);
        //ourMesh_List.push_back(Mesh(vertical));
        //ourMesh_List.push_back(Mesh(vertical.points));

        NURBS horizontal(road);
        ourMesh_List.push_back(Mesh(horizontal));
        ourMesh_List.push_back(Mesh(horizontal.points));

        NURBS alignment(horizontal, vertical);
        ourMesh_List.push_back(Mesh(alignment));

        //std::vector<Mesh::Vertex> vertical_vectors;
        //for (int i = 0; i <= STEPS; i++)
        //{
        //    float t = float(i) / STEPS;
        //    glm::vec3 tail = vertical.getPosition(t);
        //    glm::vec3 head;
        //    Mesh::Vertex v;
        //
        //    // tangent
        //    head = tail + vertical.getTangent(t);
        //    v.Color = { 1.0f, 0.0f, 1.0f };
        //    v.Position = tail;
        //    vertical_vectors.push_back(v);
        //    v.Color = { 0.5f, 0.0f, 1.0f };
        //    v.Position = head;
        //    vertical_vectors.push_back(v);
        //
        //    // normal
        //    head = tail + vertical.getNormal(t) * vertical.getRadius(t);
        //    v.Color = { 1.0f, 0.0f, 1.0f };
        //    v.Position = tail;
        //    vertical_vectors.push_back(v);
        //    v.Color = { 0.5f, 1.0f, 0.5f };
        //    v.Position = head;
        //    vertical_vectors.push_back(v);
        //
        //    // normal up
        //    head = tail + vertical.getNormalUp(t);
        //    v.Color = { 1.0f, 0.0f, 1.0f };
        //    v.Position = tail;
        //    vertical_vectors.push_back(v);
        //    v.Color = { 1.0f, 0.0f, 0.5f };
        //    v.Position = head;
        //    vertical_vectors.push_back(v);
        //}
        //ourMesh_List.push_back(Mesh(vertical_vectors));

        std::vector<Mesh::Vertex> horizontal_vectors;
        for (int i = 0; i <= STEPS; i++)
        {
            float t = float(i) / STEPS;
            glm::vec3 tail = horizontal.getPosition(t);
            glm::vec3 head;
            Mesh::Vertex v;

            // tangent
            head = tail + horizontal.getTangent(t);
            v.Color = { 1.0f, 0.0f, 1.0f };
            v.Position = tail;
            horizontal_vectors.push_back(v);
            v.Color = { 0.5f, 0.0f, 1.0f };
            v.Position = head;
            horizontal_vectors.push_back(v);

            // normal
            head = tail + horizontal.getNormal(t) * horizontal.getRadius(t);
            v.Color = { 1.0f, 0.0f, 1.0f };
            v.Position = tail;
            horizontal_vectors.push_back(v);
            v.Color = { 0.5f, 1.0f, 0.5f };
            v.Position = head;
            horizontal_vectors.push_back(v);

            // normal up
            head = tail + horizontal.getNormalUp(t);
            v.Color = { 1.0f, 0.0f, 1.0f };
            v.Position = tail;
            horizontal_vectors.push_back(v);
            v.Color = { 1.0f, 0.0f, 0.5f };
            v.Position = head;
            horizontal_vectors.push_back(v);
        }
        ourMesh_List.push_back(Mesh(horizontal_vectors));

        std::vector<Mesh::Vertex> alignment_vectors;
        for (int i = 0; i <= STEPS; i++)
        {
            float t = float(i) / STEPS;
            glm::vec3 tail = alignment.getPosition(t);
            glm::vec3 head;
            Mesh::Vertex v;

            // tangent
            head = tail + alignment.getTangent(t);
            v.Color = { 1.0f, 0.0f, 1.0f };
            v.Position = tail;
            alignment_vectors.push_back(v);
            v.Color = { 0.5f, 0.0f, 1.0f };
            v.Position = head;
            alignment_vectors.push_back(v);

            // normal
            //head = tail + alignment.getNormal(t);// *alignment.getRadius(t);
            //v.Color = { 1.0f, 0.0f, 1.0f };
            //v.Position = tail;
            //alignment_vectors.push_back(v);
            //v.Color = { 0.5f, 1.0f, 0.5f };
            //v.Position = head;
            //alignment_vectors.push_back(v);

            // normal up
            head = tail + alignment.getNormalUp(t);
            v.Color = { 1.0f, 0.0f, 1.0f };
            v.Position = tail;
            alignment_vectors.push_back(v);
            v.Color = { 1.0f, 0.0f, 0.5f };
            v.Position = head;
            alignment_vectors.push_back(v);
        }
        ourMesh_List.push_back(Mesh(alignment_vectors));

#endif

        Alignment rodovia001(road, grade);

        ourMesh_List.push_back(Mesh(rodovia001.path2Dh));
        ourMesh_List.push_back(Mesh(rodovia001.path3D));

        std::vector<Mesh::Vertex> alignment_vectors;
        for (int i = 0; i <= STEPS; i++)
        {
            float t = float(i) / STEPS;
            CRAB::Vector4Df tail = rodovia001.getPosition(t);
            CRAB::Vector4Df head;

            // tangent
            head = tail + rodovia001.getTangent(t);
            Mesh::Vertex tan_tail(tail, { 1.0f, 0.0f, 1.0f });
            alignment_vectors.push_back(tan_tail);
            Mesh::Vertex tan_head(head, { 0.5f, 0.0f, 1.0f });
            alignment_vectors.push_back(tan_head);

            // normal horizontal 
            head = tail + rodovia001.getNormal(t) * rodovia001.getRadius(t);
            Mesh::Vertex n_tail(tail, { 1.0f, 0.0f, 1.0f });
            alignment_vectors.push_back(n_tail);
            Mesh::Vertex n_head(head, { 0.5f, 1.0f, 0.5f });
            alignment_vectors.push_back(n_head);

            // normal up 
            head = tail + rodovia001.getNormalUp(t);
            Mesh::Vertex nup_tail(tail, { 1.0f, 0.0f, 1.0f });
            alignment_vectors.push_back(nup_tail);
            Mesh::Vertex nup_head(head, { 1.0f, 0.0f, 0.5f });
            alignment_vectors.push_back(nup_head);
        }
        ourMesh_List.push_back(Mesh(alignment_vectors));

        // pass projection matrix to shader (as projection matrix rarely changes there's no need to do this per frame)
        // -----------------------------------------------------------------------------------------------------------
        projection = glm::perspective(glm::radians(camera.FieldOfView), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.10f, 1000.0f);
        //projection = glm::ortho(-100.0f, 100.0f, -100.0f, 100.0f, 0.10f, 1000.0f);

        // render loop
        // -----------
        while (!glfwWindowShouldClose(window))
        {
            // per-frame time logic
            // --------------------
            float currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            // input
            // -----
            processInput(window);

            // render
            // ------
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            ourShader.use();

            // view/projection transformations
            glm::mat4 view = camera.GetViewMatrix();
            ourShader.setMat4("projection", projection);
            ourShader.setMat4("view", view);

            // world transformation
            glm::mat4 model = glm::mat4(1.0f);
            ourShader.setMat4("model", model);

            // draw grid
            grid_Mesh.Draw(ourShader);

            // render
            glPointSize(5.0f);
            for (int i = 0; i < ourMesh_List.size(); i++)
            {
                ourMesh_List[i].Draw(ourShader);
            }

            // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
            // -------------------------------------------------------------------------------
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        // glfw: terminate, clearing all previously allocated GLFW resources.
        // ------------------------------------------------------------------
        glfwTerminate();
        return 0;
    }

    // process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
    // ---------------------------------------------------------------------------------------------------------
    void processInput(GLFWwindow* window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera.ProcessKeyboard(UP, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera.ProcessKeyboard(DOWN, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera.ProcessKeyboard(LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera.ProcessKeyboard(RIGHT, deltaTime);

        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            TheKeyState = GLFW_KEY_LEFT_CONTROL;
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            TheKeyState = GLFW_KEY_LEFT_SHIFT;
    }

    // glfw: whenever the window size changed (by OS or user resize) this callback function executes
    // ---------------------------------------------------------------------------------------------
    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        // make sure the viewport matches the new window dimensions; note that width and 
        // height will be significantly larger than specified on retina displays.
        glViewport(0, 0, width, height);

        // update
        projection = glm::perspective(glm::radians(camera.FieldOfView), (float)width / (float)height, 0.1f, 1000.0f);
        //projection = glm::ortho(-100.0f, 100.0f, -100.0f, 100.0f, 0.10f, 1000.0f);
    }

    // glfw: whenever the mouse moves, this callback is called
    // -------------------------------------------------------
    void mouse_callback(GLFWwindow* window, double xpos, double ypos)
    {
        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

        lastX = xpos;
        lastY = ypos;

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS)
        {
            if (TheKeyState == GLFW_KEY_LEFT_SHIFT)
            {
                float radius = glm::length(camera.View - camera.Position);
                camera.ProcessMouseMovement(xoffset, yoffset);
                camera.View = camera.Position + camera.LookAt * radius;
            }
            if (TheKeyState == GLFW_KEY_LEFT_CONTROL)
            {
                float radius = glm::length(camera.View - camera.Position);
                camera.ProcessMouseMovement(xoffset, yoffset);
                camera.Position = camera.View - camera.LookAt * radius;
            }
        }
    }

    // glfw: whenever the mouse scroll wheel scrolls, this callback is called
    // ----------------------------------------------------------------------
    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
    {
        camera.ProcessMouseScroll(yoffset);
    }
}