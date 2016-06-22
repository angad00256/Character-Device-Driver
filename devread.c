#include"headers.h"
#include"declarations.h"

ssize_t dev_read(struct file *fileptr,char __user *ubuff,size_t size,loff_t *pos)
{
	struct Dev *ldev;
	int noctr;
	int tnoctr;
	struct Qset *temp;
	int nocpq;
	int ret;
	int i;
	int oiq;
	int nocsr;
	int count;
	int itemsize;

	noctr=0;
	tnoctr=0;
	nocpq=0;
	ret=0;
	nocsr=0;

	ldev = fileptr->private_data; 

	if(!ldev)
	{
		#ifdef DEBUG
			printk(KERN_ERR"Device Not Found!!");
		#endif
		goto OUT;
	}

	#ifdef DEBUG
		printk(KERN_ALERT"f_pos : %ld",(long)fileptr->f_pos);
		printk(KERN_ALERT"pos : %ld",(long)*pos);
		printk(KERN_ALERT"Read Operation Begins!!");
	#endif

	if(size > ((ldev->datasize) - *pos))
	{
		noctr = (ldev->datasize) - *pos;
	}

	if(size <= ((ldev->datasize) - *pos))
	{
		noctr = size;
	}

	itemsize = (ldev->qsetsize)*(ldev->quantumsize);

	count = (long)*pos / itemsize;

	if((long)*pos % itemsize)
	{
		count++;
	}
	
	tnoctr = noctr;
	temp = ldev->item;

	for(i=1;i<count;i++)
	{
		if(temp->itemnext)
		{
			temp = temp->itemnext;
		}
	}
	
	i = ((long)*pos % itemsize) / ldev->qsetsize;
	
	oiq = (long)*pos % ldev->qsetsize;
	
	#ifdef DEBUG
		printk(KERN_ALERT"Item : %d",count);
		printk(KERN_ALERT"Quantum : %d",i);
		printk(KERN_ALERT"Oiq : %d",oiq);
	#endif

	while(1)
	{
UP:
		if(tnoctr > (ldev->quantumsize))
		{
			nocpq = (ldev->quantumsize);
		}

		if(tnoctr <= (ldev->quantumsize))
		{
			nocpq = tnoctr;
		}
		
		ret = copy_to_user((ubuff+nocsr),temp->data[i]+oiq,nocpq-oiq);

		if(ret)
		{
			#ifdef DEBUG
				printk(KERN_ALERT"Quantum No. : %d of Item No. : %d is partially read!!",i,count);
				printk(KERN_ALERT"Number of bytes read from last quantum : %d",(ldev->quantumsize)-ret);	
			#endif
		}

		*pos = *pos + (nocpq-oiq-ret);
		
		#ifdef DEBUG
			printk(KERN_ALERT"Quantum%d of Item%d : %s",i,count,temp->data[i]);
			printk(KERN_ALERT"pos : %ld",(long)*pos);
		#endif
		
		nocsr = nocsr + (nocpq-oiq-ret);
		tnoctr = tnoctr - (nocpq - oiq);
		
		if(nocsr==noctr)
		{
			break;
		}

		if(i == ((ldev->qsetsize)-1))
		{
			if(temp->itemnext)
			{
				temp=temp->itemnext;
				i=0;
				count++;
				goto UP;			
			}

			else
			{
				#ifdef DEBUG
					printk(KERN_ERR"Error In Finding Next Item!!");
				#endif

				return nocsr;
			}
		}

		if(i != ((ldev->qsetsize)-1))
		{
			i++;
		}

		oiq=0;
	}	

	fileptr->f_pos = *pos;

	#ifdef DEBUG
		printk(KERN_ALERT"f_pos : %ld",(long)fileptr->f_pos);
		printk(KERN_ALERT"Reading Done Successfully!!");
	#endif

	return nocsr;
OUT:
	return -1;	
}


