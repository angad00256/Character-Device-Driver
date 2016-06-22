#include"appheaders.h"

int writerapp(char *filename)
{
	int wfd;
	int count;
	char buff[]="My name is Oliver Queen. I was stranded on an island for five years with only one goal....SURVIVE!!!";
	int len;

	wfd = open(filename,O_WRONLY);

	if(wfd<0)
	{
		perror("open");
		goto OUT;
	}

	len = strlen(buff);

	printf("Number of bytes to be written : %d \n",len);

	count = write(wfd,buff,len);

	printf("Number of bytes written : %d \n",count);

	close(wfd);

	return 0;
OUT:
	return -1;
}
