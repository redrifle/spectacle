#include <stdio.h>
#include <GLFW/glfw3.h>
#include <libspectacle/engine.h>
#include <libspectacle/io.h>
#include <libspectacle/error.h>

int sp_glfw_init()
{
    int rv, major, minor, rev;
    glfwSetErrorCallback(glfw_error_callback);

    rv = glfwInit();
    if (rv == GLFW_FALSE)
    {
        ERR_LOG("Could not initialize glfw");
        return 0;
    }

    glfwGetVersion(&major, &minor, &rev);
    puts(glfwGetVersionString());
    printf("Compiled against GLFW %i.%i.%i\nRunning against GLFW %i.%i.%i\n",
            GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR, GLFW_VERSION_REVISION,
            major, minor, rev);

    return 1;
}

int sp_glfw_create_window(GLFWwindow **window)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_SAMPLES, 4);

    *window = glfwCreateWindow(640, 480, "Spectacle", NULL, NULL);
    if (!*window)
    {
        glfwTerminate();
        ERR_LOG("Could not create window");
        return 0;
    }

    glfwMakeContextCurrent(*window);
    glfwSetKeyCallback(*window, glfw_key_callback);
    glfwSetFramebufferSizeCallback(*window, glfw_framebuffer_size_callback);
    glfwSwapInterval(1);

    return 1;
}
