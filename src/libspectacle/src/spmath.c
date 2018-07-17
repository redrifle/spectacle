#include <stdio.h>
#include <string.h>
#include <math.h>
#include <GLFW/glfw3.h>
#include <libspectacle/engine.h>
#include <libspectacle/spmath.h>
#include <libspectacle/util.h>
#include <libspectacle/error.h>

sp_mat sp_mat4x4_identity()
{
    GLfloat identity[] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    sp_mat mat;
    mat.error = 0;

    mat.size = sizeof(identity);
    mat.data = sp_malloc(mat.size);
    memcpy(mat.data, identity, mat.size);

    if (!mat.data)
    {
        mat.error = 1;
        return mat;
    }

    return mat;
}

/*
sp_mat sp_mat4x4_view()
{
    sp_mat mat;
    return mat;
}
*/

sp_mat sp_mat4x4_perspective()
{
    float fov = 90.0f;
    GLfloat scale = 1.0f / tan(fov * 0.5f * M_PI / 180.0f);
    GLfloat near = 0.1f, far = 100.0f;

    GLfloat perspective[] = {
        scale, 0.0f, 0.0f, 0.0f,
        0.0f, scale, 0.0f, 0.0f,
        0.0f, 0.0f, -far / (far - near), -1.0f,
        0.0f, 0.0f, -far * near / (far - near), 0.0f
    };

    sp_mat mat;
    mat.error = 0;

    mat.size = sizeof(perspective);
    mat.data = sp_malloc(mat.size);
    memcpy(mat.data, perspective, mat.size);

    if (!mat.data)
    {
        mat.error = 1;
        return mat;
    }

    return mat;
}

sp_m_stack *sp_m_stack_init()
{
    sp_m_stack *m_stack = sp_malloc(sizeof(sp_m_stack));

    m_stack->model = sp_mat4x4_identity();
    if (m_stack->model.error)
    {
        ERR_LOG("Could not initialize matrix");
        return NULL;
    }

    m_stack->view = sp_mat4x4_identity();
    if (m_stack->view.error)
    {
        ERR_LOG("Could not initialize matrix");
        return NULL;
    }

    m_stack->proj = sp_mat4x4_perspective();
    if (m_stack->proj.error)
    {
        ERR_LOG("Could not initialize matrix");
        return NULL;
    }

    return m_stack;
}
