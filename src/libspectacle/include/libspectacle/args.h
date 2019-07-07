#ifndef ARGS_H
#define ARGS_H
#include <argp.h>
struct args
{
    int silent, verbose, error;
    char *output_file;
};
error_t parse_opt(int, char*, struct argp_state*);
struct args sp_args_parse(int, char**);
#endif /* ARGS_H */
