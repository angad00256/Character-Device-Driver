#include"appheaders.h"

int main(int argc,char *argv[])
{
	if(argc!=2)
	{
		perror("Insufficient no. of arguments...");
		goto OUT;
	}

	int choice;

	while(1)
	{
		printf("\n.....Main Menu.....\n\n");

		printf("1. Writing \n");
		printf("2. Reading \n");
		printf("0. Exit \n\n");

		printf("Enter your choice : ");
		scanf("%d",&choice);

		switch(choice)
		{
			case 0: return 0;

			case 1: writerapp(argv[1]);
				break;

			case 2: readerapp(argv[1]);
				break;

			default: printf("Enter a valid choice... \n");
				 break;
		}
	}

	return 0;
OUT:
	return -1;
}
