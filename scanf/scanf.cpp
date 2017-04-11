#include <stdio.h>
int main(void)
{
	char str[80], str2[80];
	int i;
	unsigned char ch;

	printf("\nEnter char: ");
	scanf("%hhd", &ch);
	printf("\nch %x",ch);

	printf("\nEnter char: ");
	scanf("%hhu", &ch);

	/* читается строка и целое значение */
	 scanf("%s%d", str, &i);

 	/* в переменную str считывается не более 79 символов */
	scanf("%79s", str);

	/* целое, расположенное между двумя строками, пропускается */
	scanf("%s%*d%s", str, str2);

  return 0;
}

