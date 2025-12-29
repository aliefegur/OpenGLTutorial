#include <iostream>
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

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f( 0.5f, -0.5f);
        glVertex2f( 0.0f, 0.5f);
        glEnd();

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
