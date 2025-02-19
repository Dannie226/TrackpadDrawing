#include <iostream>

#include <GLFW/glfw3.h>

int main() {
    std::cout << "Hello World!" << std::endl;

    glfwInit();
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Note Window", nullptr, nullptr);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}
