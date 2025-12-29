#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
