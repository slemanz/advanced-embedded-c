#include "unity_fixture.h"

TEST_GROUP_RUNNER(sprintf)
{
    RUN_TEST_CASE(sprintf, NoFormatOperations);
    RUN_TEST_CASE(sprintf, InsertString);
}

static void RunAllTests(void)
{
    RUN_TEST_GROUP(sprintf);
}

int main(int argc, const char * argv[])
{
    return UnityMain(argc, argv, RunAllTests);
}