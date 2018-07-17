#ifndef ENGINE_H
#define ENGINE_H
#include <GLFW/glfw3.h>
#include "spmath.h"
typedef struct sp_engine_state_struct
{
    int err;
    GLFWwindow *window;
    sp_m_stack *m_stack;
    GLfloat *verts, *color;
    size_t verts_size, color_size;
} sp_state;
sp_state *sp_state_init(void);
int sp_engine_init(sp_state*);
int sp_engine_run(sp_state*);
void glfw_framebuffer_size_callback(GLFWwindow*, int, int);
#endif /* ENGINE_H */
