// @author Subbotin B.P.
// @see http://sbp-program.ru
#include <stdio.h>
#define mFirstMacro(nVar) ((nVar) + mSecondMacro(nVar))
#define mSecondMacro(nVar) ((nVar) * 2)
int  main()
{
    	int nVar = 5;
	printf("\nnVar = %d\n\n", mFirstMacro(nVar));

	return 0;
}
