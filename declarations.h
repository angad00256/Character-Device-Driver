extern dev_t devid;
extern int nod;
extern struct Dev *dev;

struct Dev
{
	struct Qset *item;
	int devsize;
	int datasize;
	int qsetsize;
	int quantumsize;
	struct cdev c_dev;
};

struct Qset
{
	struct Qset *itemnext;
	char **data;
};

int device_initialization(void);
int dev_open(struct inode*,struct file*); 
int dev_trim(struct Dev*); 
int dev_release(struct inode*,struct file*); 

ssize_t dev_write(struct file *,const char __user *,size_t,loff_t *);
struct Qset* create_scull(struct Dev*,int);
struct Qset* create_array(struct Qset*,struct Dev*);
struct Qset* create_quantums(struct Qset*,struct Dev*,int);

ssize_t dev_read(struct file *,char __user *,size_t,loff_t *);
	
loff_t dev_seek(struct file *,loff_t,int);
