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
        mat.error = 1;

    return mat;
}

sp_mat sp_mat4x4_view()
{
    GLfloat view[] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    sp_mat mat;
    mat.error = 0;

    mat.size = sizeof(view);
    mat.data = sp_malloc(mat.size);
    memcpy(mat.data, view, mat.size);

    if (!mat.data)
        mat.error = 1;

    return mat;
}

sp_mat sp_mat4x4_model()
{
    GLfloat model[] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    sp_mat mat;
    mat.error = 0;

    mat.size = sizeof(model);
    mat.data = sp_malloc(mat.size);
    memcpy(mat.data, model, mat.size);

    if (!mat.data)
        mat.error = 1;

    return mat;
}

sp_mat sp_mat4x4_ortho(GLfloat b,   GLfloat t,
                       GLfloat l,   GLfloat r,
                       GLfloat n,   GLfloat f)
{
    sp_mat mat;
    mat.error = 0;

    GLfloat ortho[] = {
        2.0f / (r - l), 0.0f,           0.0f,           -(r + l) / (r - l),
        0.0f,           2.0f / (t - b), 0.0f,           -(t + b) / (t - b),
        0.0f,           0.0f,          -2.0f / (f - n), -(f + n) / (f - n),
        0.0f,           0.0f,           0.0f,            1.0f
    };

    mat.size = sizeof(ortho);
    mat.data = sp_malloc(mat.size);
    memcpy(mat.data, ortho, mat.size);

    if (!mat.data)
        mat.error = 1;

    return mat;
}

sp_mat sp_mat4x4_perspective()
{
    /* FIX THIS */
    float fov = 90.0f;
    GLfloat scale = 1.0f;
    GLfloat D2R = M_PI / 180.0f;
    GLfloat yscale = 1.0f;
    GLfloat xscale = yscale / 1.0f;
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
        mat.error = 1;

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

    m_stack->view = sp_mat4x4_view();
    if (m_stack->view.error)
    {
        ERR_LOG("Could not initialize matrix");
        return NULL;
    }

    m_stack->proj = sp_mat4x4_ortho(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 10.0f);
    if (m_stack->proj.error)
    {
        ERR_LOG("Could not initialize matrix");
        return NULL;
    }

    return m_stack;
}
