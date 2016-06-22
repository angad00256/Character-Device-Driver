#include"headers.h"
#include"declarations.h"

static void __exit cleanup(void)
{
	int l;

	#ifdef DEBUG
		printk(KERN_ALERT"Bye Kernel \n");
	#endif

	for(l=0;l<nod;l++)
	{
		cdev_del(&dev[l].c_dev);
	}

	kfree(dev);

	unregister_chrdev_region(devid,nod);

	#ifdef DEBUG
		printk(KERN_ALERT"Unregisteration Successful!! \n");
	#endif
}

module_exit(cleanup);
