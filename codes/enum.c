#include<stdio.h>

int main()
{
	/*enum month{
		jan,
		feb,
		mar
	};

	enum month rmonth;
	rmonth = jan;
	printf("%d",rmonth);
	*/

	char l[5] = "ninad";
	switch(l[2])
	{
		case 'n':
			printf("\nn found\n");
			break;

		case 'i':
			printf("\ni found\n");
			break;
	}
	return 0;
}
