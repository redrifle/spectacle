#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <GLFW/glfw3.h>
#include <libspectacle/args.h>
#include <libspectacle/io.h>
#include <libspectacle/engine.h>
#include <libspectacle/spmath.h>
#include <libspectacle/error.h>

#ifdef __GNUC__
__attribute__((malloc))
#endif
void *sp_malloc(size_t n)
{
    errno = 0;
    void *p = malloc(n);

    if (!p)
    {
        perror(NULL);
        ERR_LOG("Could not allocate %zu bytes", n);
        return NULL;
    }

    return p;
}

void *sp_calloc(size_t nmemb, size_t n)
{
    errno = 0;
    void *p = calloc(nmemb, n);

    if (!p)
    {
        perror(NULL);
        ERR_LOG("Could not allocate %zu bytes", nmemb * n);
        return NULL;
    }

    return p;
}

void sp_freep(void **p)
{
    if (p && *p)
    {
        free(*p);
        *p = NULL;
    }
}

void sp_mat_free(sp_mat *mat)
{
    sp_freep((void**)&mat->data);
}

void sp_m_stack_free(sp_m_stack *m_stack)
{
    sp_mat_free(&m_stack->model);
    sp_mat_free(&m_stack->view);
    sp_mat_free(&m_stack->proj);
    sp_freep((void**)&m_stack);
}

void sp_state_free(sp_state *state)
{
    sp_freep((void**)&state->verts);
    sp_freep((void**)&state->color);
    sp_freep((void**)&state);
}

void sp_engine_free(sp_state *state)
{
    sp_m_stack_free(state->m_stack);
    sp_state_free(state);
}

/*
#ifdef __GNUC__
__attribute__((format(__printf__, 1, 2)))
#endif
char* sp_asprintf(const char *fmt, ...)
{
    char *p = NULL;
    va_list ap;
    int len;

    va_start(ap, fmt);
    len = vsnprintf(NULL, 0, fmt, ap);
    va_end(ap);

    if (len < 0)
        return NULL;

    p = safe_malloc(len + 1);

    va_start(ap, fmt);
    len = vsnprintf(p, len + 1, fmt, ap);
    va_end(ap);

    if (len < 0)
        sp_freep((void**) &p);

    return p;
}
*/
