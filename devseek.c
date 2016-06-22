#include"headers.h"
#include"declarations.h"

loff_t dev_seek(struct file *fileptr,loff_t offset,int origin)
{
	switch(origin)
	{
		case 0: fileptr->f_pos = offset; 
			break;

/*		case 1: fileptr->f_pos = fileptr->f_pos + pos;
			break;

		case 2: fileptr->f_pos = 
			break;
*/	}

	return 0;
}  

