#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <libspectacle/engine.h>

void stateInit_success_returnNonNull(void **state)
{
    sp_state *engine_state;

    engine_state = sp_state_init();

    assert_non_null(engine_state);
}

int main(void)
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(stateInit_success_returnNonNull),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
