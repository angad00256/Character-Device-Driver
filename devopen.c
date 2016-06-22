#include"headers.h"
#include"declarations.h"

int dev_open(struct inode *inodeptr,struct file *fileptr) 
{
	struct Dev *ldev;

	#ifdef DEBUG
		printk(KERN_ALERT"Device Opening Begins!!");
	#endif

	ldev = container_of(inodeptr->i_cdev,struct Dev,c_dev);

	if(!ldev)
	{
		#ifdef DEBUG
			printk(KERN_ERR"container_of failed!!");
		#endif
	}	

	if((fileptr->f_flags & O_ACCMODE) == O_WRONLY)	
	{
		dev_trim(ldev);
	}

	fileptr->private_data = ldev;
		
	#ifdef DEBUG
		printk(KERN_ALERT"Device Opened Successfully!!");
	#endif

	return 0;
}
