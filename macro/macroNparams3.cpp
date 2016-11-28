// @author Subbotin B.P.
// @see http://sbp-program.ru
#include <stdio.h>
#define mMyPrint(...) printf(__VA_ARGS__)

int main()
{
    	char *szFirst = "This is ";
    	char *szSecond = "a variadic macro";
	mMyPrint("\n%s%s\n\n", szFirst, szSecond);

	return 0;
}
