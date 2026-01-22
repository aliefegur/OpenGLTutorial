#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>

#include "Core/ShaderProgram.h"
#include "Utils/File.h"
#include "Core/Vertex.h"

int main(int argc, char** argv)
{
    if (!glfwInit())
    {
        std::cout << "Failed to initialize!" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Tutorial", nullptr, nullptr);
    if (!window)
    {
        std::cout << "Failed to create window!" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::cout << "Failed to initialize GLAD!" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    ShaderProgram shaderProgram("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");

    const Vertex vertices[] = {
        { -0.5, -0.5, 0.0f, 1.0f, 1.0f, 1.0f },
        { 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f },
        { 0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f }
    };

    float color[] = { 0.0f, 0.0f, 0.0f };

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    while (!glfwWindowShouldClose(window))
    {
        double time = glfwGetTime();

        // Update shape color
        color[0] = std::sin(time);
        color[1] = std::cos(time / 3.0f);
        color[2] = std::sin(time / 5.0f);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.Use();

        // Pass color to the uniform in shader
        unsigned int uColorLocation = glGetUniformLocation(shaderProgram, "uColor");
        glUniform3f(uColorLocation, color[0], color[1], color[2]);

        glBindVertexArray(VAO);
        
        glDrawArrays(GL_TRIANGLES, 0, std::size(vertices));

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
