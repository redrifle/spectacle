#ifndef UTIL_H
#define UTIL_H
#include <stdlib.h>
struct args;
typedef struct sp_matrix_stack sp_m_stack;
typedef struct sp_engine_state_struct sp_state;
void *sp_malloc(size_t);
void *sp_calloc(size_t, size_t);
void sp_freep(void**);
void sp_engine_free(sp_state*);
void sp_args_free(struct args*);
void sp_state_free(sp_state*);
void sp_m_stack_free(sp_m_stack*);
#endif /* UTIL_H */
