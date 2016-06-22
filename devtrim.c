#include"headers.h"
#include"declarations.h"

int dev_trim(struct Dev *ldev)
{
	if(!ldev)
	{
		#ifdef DEBUG
			printk(KERN_ALERT"Device Not Found!!");
		#endif
	}

	else if(!ldev->item)
	{
		#ifdef DEBUG
			printk(KERN_ALERT"Nothing To Trim!!");
		#endif
	}

	else
	{		
		#ifdef DEBUG
			printk(KERN_ALERT"Device Trimming Begins!!");
		#endif
	}

	return 0;
}
