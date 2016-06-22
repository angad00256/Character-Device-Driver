struct file_operations fops=
{
	open : dev_open,
	release : dev_release,
	write : dev_write,
	read : dev_read,
	llseek : dev_seek
};
