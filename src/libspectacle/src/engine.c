#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <libspectacle/args.h>
#include <libspectacle/engine.h>
#include <libspectacle/glfw.h>
#include <libspectacle/glew.h>
#include <libspectacle/io.h>
#include <libspectacle/spmath.h>
#include <libspectacle/util.h>
#include <libspectacle/error.h>

void glfw_framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void sp_gl_version_print()
{
    printf("OpenGL %s\nGLSL %s\n",
            glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));
}

GLuint sp_vao_new()
{
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    return vao;
}

GLuint sp_buffer_new(GLenum target, GLvoid *data, size_t size)
{
    GLuint bo;
    glGenBuffers(1, &bo);
    glBindBuffer(target, bo);
    glBufferData(target, size, data, GL_STATIC_DRAW);

    return bo;
}

int sp_shader_compile(GLuint shader, GLuint program)
{
    GLint compile_ok = GL_FALSE;
    GLsizei logsize = 0;

    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_ok);
    if (compile_ok == GL_FALSE)
    {
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logsize);
        GLchar log[logsize];
        glGetShaderInfoLog(shader, logsize, 0, log);
        glDeleteShader(shader);
        fprintf(stderr, "[ SHADER ] %s", log);
        return 0;
    }

    glAttachShader(program, shader);

    return 1;
}

GLuint sp_shader_load(GLenum shader_type, const GLchar *source)
{
    GLuint shader = glCreateShader(shader_type);
    if (!shader)
    {
        ERR_LOG("Could not create shader program");
        sp_err_check();
        return 0;
    }

    glShaderSource(shader, 1, &source, NULL);

    return shader;
}

int sp_engine_init(sp_state *state)
{
    int rv = sp_glfw_init();

    if (!rv)
        return 0;

    rv = sp_glfw_create_window(&state->window);

    if (!rv)
        return 0;

    rv = sp_glew_init();

    if (!rv)
        return 0;

    sp_gl_version_print();

    return 1;
}

sp_state *sp_state_init()
{
    sp_state *state = sp_malloc(sizeof(sp_state));

    if (!state)
    {
        ERR_LOG("Could not inizialize state data");
        return NULL;
    }

    GLfloat verts[] = {
       -1.0f, -1.0f,  -1.0f, 1.0f,
        0.0f,  1.0f,  -1.0f, 1.0f,
        1.0f, -1.0f,  -1.0f, 1.0f
    };

    GLfloat color[] = {
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f
    };

    state->verts_size = sizeof(verts);
    state->color_size = sizeof(color);
    state->verts = sp_malloc(state->verts_size);

    if (!state->verts)
    {
        ERR_LOG("Could not inizialize vertex data");
        return NULL;
    }

    state->color = sp_malloc(state->color_size);

    if (!state->color)
    {
        ERR_LOG("Could not inizialize color data");
        return NULL;
    }

    memcpy(state->verts, verts, state->verts_size);
    memcpy(state->color, color, state->color_size);

    return state;
}

void update(sp_state *state)
{
    glfwPollEvents();

    GLfloat time = glfwGetTime();

    state->color[5] = cos(time);
    state->color[6] = sin(time);
    state->color[7] = tan(time);


    if (glfwGetKey(state->window, GLFW_KEY_W) == GLFW_PRESS)
        state->m_stack->model.data[11] += 0.01f;

    if (glfwGetKey(state->window, GLFW_KEY_A) == GLFW_PRESS)
        state->m_stack->model.data[12] += 0.01f;

    if (glfwGetKey(state->window, GLFW_KEY_S) == GLFW_PRESS)
        state->m_stack->model.data[11] -= 0.01f;

    if (glfwGetKey(state->window, GLFW_KEY_D) == GLFW_PRESS)
        state->m_stack->model.data[12] -= 0.01f;

    glBufferData(
            GL_ARRAY_BUFFER,
            state->verts_size,
            state->verts,
            GL_STATIC_DRAW);

    glBufferData(
            GL_ARRAY_BUFFER,
            state->color_size,
            state->color,
            GL_STATIC_DRAW);

    glUniformMatrix4fv(
            state->m_stack->model.id,
            1,
            GL_FALSE,
            state->m_stack->model.data);

    glUniformMatrix4fv(
            state->m_stack->view.id,
            1,
            GL_FALSE,
            state->m_stack->view.data);

    glUniformMatrix4fv(
            state->m_stack->proj.id,
            1, GL_FALSE,
            state->m_stack->proj.data);

}

void render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

int sp_engine_run(sp_state *state)
{
    sp_vao_new();

    GLuint sp_buf_verts = sp_buffer_new(
            GL_ARRAY_BUFFER,
            state->verts,
            state->verts_size);

    GLuint sp_buf_color = sp_buffer_new(
            GL_ARRAY_BUFFER,
            state->color,
            state->color_size);

    const GLchar *v_shader_source =
        "#version 330 core\n"
        "in vec4 vcoords;"
        "in vec4 color;"
        "out vec4 frag_color;"
        "uniform mat4 model, view, proj;"
        "void main() { gl_Position = proj * view * model * vcoords;"
        "frag_color = color; }";

    const GLchar *f_shader_source =
        "#version 330 core\n"
        "in vec4 frag_color;"
        "out vec4 final_color;"
        "void main() { final_color = frag_color; }";

    GLuint vs = sp_shader_load(GL_VERTEX_SHADER, v_shader_source);
    GLuint fs = sp_shader_load(GL_FRAGMENT_SHADER, f_shader_source);
    GLuint shader_program = glCreateProgram();
    sp_shader_compile(vs, shader_program);
    sp_shader_compile(fs, shader_program);
    glLinkProgram(shader_program);
    glDeleteShader(vs);
    glDeleteShader(fs);

    state->m_stack = sp_m_stack_init();

    if (!state->m_stack)
        return 0;

    glUseProgram(shader_program);

    state->m_stack->model.id = glGetUniformLocation(shader_program, "model");
    state->m_stack->view.id = glGetUniformLocation(shader_program, "view");
    state->m_stack->proj.id = glGetUniformLocation(shader_program, "proj");

    GLuint verts_index = glGetAttribLocation(shader_program, "vcoords");
    glEnableVertexAttribArray(verts_index);
    glBindBuffer(GL_ARRAY_BUFFER, sp_buf_verts);
    glVertexAttribPointer(verts_index, 4, GL_FLOAT, GL_FALSE, 0, NULL);

    GLuint color_index = glGetAttribLocation(shader_program, "color");
    glEnableVertexAttribArray(color_index);
    glBindBuffer(GL_ARRAY_BUFFER, sp_buf_color);
    glVertexAttribPointer(color_index, 4, GL_FLOAT, GL_FALSE, 0, NULL);

    static double rate = 1.0f / 60.0f;
    double last_time = glfwGetTime(), delta = 0, now_time = 0;
    sp_err_check();
    while (!glfwWindowShouldClose(state->window))
    {
        now_time = glfwGetTime();
        delta += (now_time - last_time) / rate;
        last_time = now_time;

        while(delta >= 1.0f)
        {
            update(state);
            render();
            --delta;
        }

        glfwSwapBuffers(state->window);
    }

    glDeleteProgram(shader_program);
    glfwTerminate();
    sp_engine_free(state);
    return 1;
}
