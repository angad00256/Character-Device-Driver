#include"headers.h"
#include"declarations.h"
#include"operations.h"

dev_t devid;
int nod;
struct Dev *dev;

module_param(nod,int,S_IRUGO);

int dev_size;
int data_size;
int qset_size;
int quantum_size;

static int __init initfunc(void)
{
	int ret1;
	int minorno;	
	int l;
	dev_t devno;
	int ret2;

	minorno=MINORNO;

	#ifdef DEBUG 
		printk(KERN_ALERT"Hello Kernel \n");
	#endif

	ret1=alloc_chrdev_region(&devid,minorno,nod,DEVNAME);

	if(ret1<0)
	{
		#ifdef DEBUG
			printk(KERN_ERR"Error : alloc_chrdev_region failed!!");
			goto OUT;
		#endif
	}

	#ifdef DEBUG 
		printk(KERN_ALERT"Registration Successful!! \n");
	#endif

	dev=kmalloc(sizeof(struct Dev)*nod,GFP_KERNEL);
	
	if(!dev)
	{
		#ifdef DEBUG
			printk(KERN_ERR"Error : kmalloc failed!!");
			goto OUT;
		#endif
	}

	memset(dev,'\0',sizeof(struct Dev)*nod);

	#ifdef DEBUG
		printk(KERN_ALERT"Memory Allocation Successful!!");
	#endif

	device_initialization();

	for(l=0;l<nod;l++)
	{
		devno = MKDEV(MAJOR(devid),l);

		cdev_init(&dev[l].c_dev,&fops);

		dev[l].c_dev.owner = THIS_MODULE;
		dev[l].c_dev.ops = &fops;

		dev[l].devsize = dev_size;
		dev[l].datasize = data_size;
		dev[l].qsetsize = qset_size;
		dev[l].quantumsize = quantum_size;

		ret2=cdev_add(&dev[l].c_dev,devno,1);
	
		if(ret2<0)
		{
			#ifdef DEBUG
			printk(KERN_ERR"Error : cdev_add failed!!");
			goto OUT;
			#endif
		}

		#ifdef DEBUG
			printk(KERN_ALERT"Device%d (Major = %d,Minor = %d)",l+1,MAJOR(devno),MINOR(devno));
		#endif
	}

	return 0;
OUT:
	return -1;
}

module_init(initfunc);

int device_initialization(void)
{
	#ifdef DEBUG
		printk(KERN_ALERT"Device Initialization Begins!!");
	#endif
	
	dev_size = DEVSIZE;
	data_size = DATASIZE;
	qset_size = QSETSIZE;
	quantum_size = QUANTUMSIZE;
		
	#ifdef DEBUG
		printk(KERN_ALERT"Device Initialization Successful!!");
	#endif

	return 0;
}
