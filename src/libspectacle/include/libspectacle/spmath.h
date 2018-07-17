#ifndef MATH_H
#define MATH_H
#include <GLFW/glfw3.h>
typedef struct sp_matrix
{
    int size, error;
    GLint id;
    GLfloat *data;
} sp_mat;

typedef struct sp_matrix_stack
{
    sp_mat model, view, proj;
} sp_m_stack;
sp_m_stack *sp_m_stack_init(void);
#endif /* MATH_H */
