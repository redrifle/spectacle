#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include <libspectacle/spmath.h>
#include <libspectacle/io.h>

void glfw_key_callback(GLFWwindow* window,
        int key, int scancode, int action, int mods)
{

    if ((key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q)
            && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}
