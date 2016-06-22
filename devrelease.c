#include"headers.h"
#include"declarations.h"

int dev_release(struct inode *inodeptr,struct file *fileptr) 
{
	#ifdef DEBUG
		printk(KERN_ALERT"Releasing Device Begins!!");
	#endif

	return 0;
}
