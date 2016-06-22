#include"appheaders.h"

int readerapp(char *filename)
{
	int rfd;
	int count;
	int len;
	char *buff;
	int origin;
	
	rfd = open(filename,O_RDONLY);

	if(rfd<0)
	{
		perror("open");
		goto OUT;
	}

	printf("Enter the number of bytes to be read : ");
	scanf("%d",&len);

	buff=(char*)malloc(sizeof(char)*len);

	origin = app_origin();

	lseek(rfd,18,origin);

	count = read(rfd,buff,len);

	printf("Number of bytes read : %d \n",count);

	printf("Data read from the device : %s \n",buff);

	close(rfd);

	return 0;
OUT:
	return -1;
}
