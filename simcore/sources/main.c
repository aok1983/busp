#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include "cmocka.h"


int main(int argc, char const *argv[])
{
	const struct CMUnitTest tests[] = 
	{
		cmocka_unit_test(null_test_success),
	};
	return cmocka_run_group_tests(tests, NULL, NULL);
}

