#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

    // Transformation data
    glm::mat4 model{ 1.0f };
    glm::vec3 position{ 0.0f };
    glm::vec3 scale{ 1.0f };
    float rotation = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        double time = glfwGetTime();

        // Update transformations
        position.x = sinf(static_cast<float>(time));
        scale.x = scale.y = scale.z = abs(cosf(static_cast<float>(time)));
        rotation = static_cast<float>(time) * 50.0f;

        // Calculate model matrix
        model = glm::scale(
            glm::rotate(
                glm::translate(glm::mat4(1.0f), position), 
                glm::radians(rotation), { 0.0f, 0.0f, 1.0f }
            ),
            scale
        );

        // Update shape color
        color[0] = std::sin(time);
        color[1] = std::cos(time / 3.0f);
        color[2] = std::sin(time / 5.0f);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.Use();

        // Pass model matrix to the uniform
        unsigned uModelLocation = glGetUniformLocation(shaderProgram, "uModel");
        glUniformMatrix4fv(uModelLocation, 1, GL_FALSE, &model[0][0]);

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
