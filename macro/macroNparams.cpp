// @author Subbotin B.P.
// @see http://sbp-program.ru
#include <stdio.h>
#define mMyPrint(szFormat, ...) printf(szFormat, __VA_ARGS__)
#define mMyPrint2(...) printf("%s,%s",__VA_ARGS__)

int  main()
{
      	char *szFormat = "\n%s%s\n\n";
        char *szFirst = "This is ";
        char *szSecond = "a variadic macro with one named argument";
        mMyPrint(szFormat, szFirst, szSecond);

	mMyPrint2("aaa","bbb");

	return 0;
}
