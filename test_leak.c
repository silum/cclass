#include <stdlib.h>
#include <xmalloc.h>
#include <xassert.h>

void
test_func()
{
	char *p = xmalloc(1);
	*p = 0;
}


int
main()
{
	return debug_test(test_func);
}
