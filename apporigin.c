#include"appheaders.h"

int app_origin()
{
	int origin;
UP:
	printf("\n...ORIGINS...\n\n");

	printf("0. SEEK_SET \n");
	printf("1. SEEK_CUR \n");
	printf("2. SEEK_END \n\n");

	printf("Select the origin : ");
	scanf("%d",&origin);

	if((origin<0)||(origin>2))
	{
		printf("Select a valid origin... \n");
		goto UP;
	}

	return origin;
}
