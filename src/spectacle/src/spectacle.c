#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GLFW/glfw3.h>
#include <libspectacle/args.h>
#include <libspectacle/engine.h>
#include <libspectacle/io.h>
#include <libspectacle/util.h>
#include <libspectacle/error.h>

int main(int argc, char **argv)
{
    int rv;

    struct args args = sp_args_parse(argc, argv);

    if (args.error)
        return EXIT_FAILURE;

    printf("\033[33;5;7m%s\033[0m\n", "Spectacle - Free Your Soul");

    sp_state *state = sp_state_init();

    if (!state)
        return EXIT_FAILURE;

    rv = sp_engine_init(state);
    if (!rv)
    {
        sp_state_free(state);
        return EXIT_FAILURE;
    }

    rv = sp_engine_run(state);
    if (!rv)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
