#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include<linux/fs.h>
#include<linux/slab.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Angad");

#ifndef DEBUG
	#define DEBUG
#endif

#ifndef DEVNAME
	#define DEVNAME "mydriver"
#endif

#ifndef MAJORNO 
	#define MAJORNO 0
#endif

#ifndef MINORNO
	#define MINORNO 0
#endif

#ifndef DEVSIZE
	#define DEVSIZE 1024
#endif

#ifndef DATASIZE
	#define DATASIZE 0
#endif

#ifndef QSETSIZE
	#define QSETSIZE 8	//Qset size = No. of quantums
#endif

#ifndef QUANTUMSIZE
	#define QUANTUMSIZE 8	//Quantum size = Register size
#endif

