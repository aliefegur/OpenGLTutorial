#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb/stb_image.h>

#include "Core/ShaderProgram.h"
#include "Core/Vertex.h"
#include "Core/Viewport.h"
#include "Core/OrthographicCamera.h"

Viewport viewport;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

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

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    viewport.Update(0, 0, 800, 600);

    const ShaderProgram shaderProgram("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");

    constexpr Vertex vertices[] = {
        { {-0.5, -0.5, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f} },
        { {0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f} },
        { {0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f} },
        { {-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f} },
    };

    constexpr unsigned short indices[] = {
        0, 1, 2,    // Lower triangle
        0, 2, 3     // Upper triangle
    };

    float color[] = { 0.0f, 0.0f, 0.0f };

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*>(0));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*>(3 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*>(6 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    // Load texture image
    int width, height, channelCount;
    unsigned char* pixelData = stbi_load("textures/wall.jpg", &width, &height, &channelCount, 0);

    // Texture generation
    unsigned int texture;
    glGenTextures(1, &texture);

    // Bind texture
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixelData);

    // Generate mipmaps
    glGenerateMipmap(GL_TEXTURE_2D);

    // Texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Clear image
    stbi_image_free(pixelData);

    // Transformation data
    glm::vec3 position{ 0.0f };
    glm::vec3 scale{ 1.0f };
    float rotation = 0.0f;

    OrthographicCamera camera;
    camera.SetNear(0.0f);
    camera.SetSize(2.0f);
    camera.SetRotation(30.0f);

    while (!glfwWindowShouldClose(window))
    {
        const auto time = static_cast<float>(glfwGetTime());

        camera.SetPosition({cosf(time), sinf(time), 0.0f});

        // Update transformations
        /*position.x = sinf(time);
        scale.x = scale.y = scale.z = fabsf(cosf(time));
        rotation = time * 50.0f;
*/
        // Update camera
        camera.Update(viewport.GetAspectRatio());

        // Calculate model matrix
        glm::mat4 model = glm::scale(
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

        // Pass combined camera matrix to the shader
        const int uViewProjection = glGetUniformLocation(shaderProgram, "uViewProjection");
        glUniformMatrix4fv(uViewProjection, 1, GL_FALSE, glm::value_ptr(camera.GetCombinedMatrix()));

        // Pass model matrix to the uniform
        const int uModelLocation = glGetUniformLocation(shaderProgram, "uModel");
        glUniformMatrix4fv(uModelLocation, 1, GL_FALSE, glm::value_ptr(model));

        // Pass color to the uniform in shader
        const int uColorLocation = glGetUniformLocation(shaderProgram, "uColor");
        glUniform3f(uColorLocation, color[0], color[1], color[2]);

        glBindVertexArray(VAO);

        glBindTexture(GL_TEXTURE_2D, texture);

        // Wireframe
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, std::size(indices), GL_UNSIGNED_SHORT, reinterpret_cast<void*>(0));

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    viewport.Update(0, 0, width, height);
}
