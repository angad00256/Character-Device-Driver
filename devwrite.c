#include"headers.h"
#include"declarations.h"

ssize_t dev_write(struct file *fileptr, const char __user *ubuff, size_t size, loff_t *pos)
{
	struct Dev *ldev;
	int noctw;
	int tnoctw;
	int ret;
	struct Qset *temp;
	int i;
	int nocpq;
	int nocsw;
	int count;

	noctw=0;
	tnoctw=0;
	ret=0;
	i=0;
	nocpq=0;
	nocsw=0;
	count=1;

	ldev = fileptr->private_data; 

	if(!ldev)
	{
		#ifdef DEBUG
			printk(KERN_ERR"Device Not Found!!");
		#endif
		goto OUT;
	}
	
	#ifdef DEBUG
		printk(KERN_ALERT"Data To Be Written : %s",ubuff);
		printk(KERN_ALERT"f_pos : %ld",(long)fileptr->f_pos);
		printk(KERN_ALERT"Write Operation Begins!!");
	#endif

	if(size>ldev->devsize)
	{
		noctw = ldev->devsize;
	}

	if(size<=ldev->devsize)
	{
		noctw = size;
	}

	ldev->item = create_scull(ldev,noctw);

	tnoctw = noctw;
	temp = ldev->item;

	while(1)
	{
UP:
		if(tnoctw > (ldev->quantumsize))
		{
			nocpq = (ldev->quantumsize);
		}

		if(tnoctw <= (ldev->quantumsize))
		{
			nocpq = tnoctw;
		}
		
		ret = copy_from_user(temp->data[i],(ubuff+nocsw),nocpq);

		if(ret)
		{
			#ifdef DEBUG
				printk(KERN_ALERT"Quantum No. : %d of Item No. : %d is partially written!!",i,count);
				printk(KERN_ALERT"Number Of Bytes Written In Last Quantum : %d",(ldev->quantumsize)-ret);	
			#endif
		}

		*pos = *pos + (nocpq-ret);
		
		#ifdef DEBUG
			printk(KERN_ALERT"Quantum%d of Item%d : %s",i,count,temp->data[i]);
			printk(KERN_ALERT"pos : %ld",(long)*pos);
		#endif

		nocsw = nocsw + (nocpq-ret);
		tnoctw = tnoctw - nocpq;
		
		if(nocsw==noctw)
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

				ldev->datasize = nocsw;

				return nocsw;
			}
		}

		if(i != ((ldev->qsetsize)-1))
		{
			i++;
		}
	}	

	ldev->datasize = nocsw;
	fileptr->f_pos = *pos;

	#ifdef DEBUG
		printk(KERN_ALERT"f_pos : %ld",(long)fileptr->f_pos);
		printk(KERN_ALERT"Writing Done Successfully!!");
	#endif

	return nocsw;
OUT:
	return -1;	
}

struct Qset* create_scull(struct Dev *ldev,int noctw)
{
	int noi;
	int noq;
	struct Qset *start;
 	struct Qset *next;
 	struct Qset *temp;
	int i;

	start=NULL;
	next=NULL;
	temp=NULL;
	
	#ifdef DEBUG
		printk(KERN_ALERT"Creating Skull Begins!!");
	#endif
	
	if(!noctw)
	{
		#ifdef DEBUG
			printk(KERN_ALERT"Nothing To Write!!");
		#endif
		
		return 0;
	}

	noi = noctw / ((ldev->qsetsize)*(ldev->quantumsize));

	if(noctw % ((ldev->qsetsize)*(ldev->quantumsize)))
	{
		noi++;
	}

	#ifdef DEBUG
		printk(KERN_ALERT"Number Of Bytes : %d",noctw);
		printk(KERN_ALERT"Number Of Items Required : %d",noi);
	#endif

	for(i=0;i<noi;i++)
	{
		if(!start)
		{
			start=temp=kmalloc(sizeof(struct Qset),GFP_KERNEL);
			
			if(!start)
			{
				#ifdef DEBUG
					printk(KERN_ERR"kmalloc failed!!");
				#endif

				goto OUT;
			}

			start->itemnext=NULL;
		}

		else
		{
			next=kmalloc(sizeof(struct Qset),GFP_KERNEL);
			next->itemnext=NULL;

			while(temp->itemnext)
			{
				temp=temp->itemnext;
			}

			temp->itemnext=next;
		}
	}


	#ifdef DEBUG
		printk(KERN_ALERT"Items Successfully Created!!");
	#endif

	start = create_array(start,ldev);

	noq = noctw / ldev->quantumsize;

	if(noctw % ldev->quantumsize)
	{
		noq++;
	}

	#ifdef DEBUG
		printk(KERN_ALERT"Number Of Quantums Required : %d",noq);
	#endif

	start = create_quantums(start,ldev,noq);
		
	#ifdef DEBUG
		printk(KERN_ALERT"Skull Created Successfully!!");
	#endif

	return start;
OUT:
	return 0;
}

struct Qset* create_array(struct Qset *start,struct Dev *ldev)
{
	struct Qset *temp;

	temp=start;

	#ifdef DEBUG
		printk(KERN_ALERT"Creating Arrays Begins!!");
	#endif

	while(1)
	{
		temp->data = kmalloc(sizeof(char*)*(ldev->qsetsize),GFP_KERNEL);

		if(!temp->itemnext)
		{
			break;
		}

		temp=temp->itemnext;
	}

	#ifdef DEBUG
		printk(KERN_ALERT"Arrays Created Successfully!!");
	#endif

	return start;
}

struct Qset* create_quantums(struct Qset *start,struct Dev *ldev,int noq)
{
	struct Qset *temp;
	int i;
	int noqmade;

	temp=start;
	i=0;
	noqmade=0;

	#ifdef DEBUG
		printk(KERN_ALERT"Creating Quantums Begins!!");
	#endif

	while(1)
	{
		temp->data[i]=kmalloc(sizeof(char)*(ldev->quantumsize),GFP_KERNEL);

		noqmade++;

		if(noqmade==noq)
		{
			break;
		}
	
		if(i==(ldev->qsetsize)-1)
		{
			if(temp->itemnext)
			{
				temp=temp->itemnext;
				i=0;
			}

			else
			{
				#ifdef DEBUG
					printk(KERN_ERR"Error In Finding Next Item!!");
				#endif

				return 0;
			}
		}

		else
		{
			i++;
		}
	}

	#ifdef DEBUG
		printk(KERN_ALERT"Number Of Quantums Made : %d",noqmade);
		printk(KERN_ALERT"Quantums Created Successfully!!");
	#endif

	return start;
}
