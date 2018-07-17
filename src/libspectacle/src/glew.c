#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <libspectacle/error.h>

int sp_glew_init()
{
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();

    if (err != GLEW_OK)
    {
        glfwTerminate();
        fprintf(stderr, "[ GLEW ] %s\n", glewGetErrorString(err));
        ERR_LOG("Could not load OpenGL extensions");
        return 0;
    }
    return 1;
}
