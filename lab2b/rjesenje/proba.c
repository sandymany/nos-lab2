#include<fcntl.h>
#include<stdio.h>
#include<sys/ioctl.h>
#include<errno.h>
#include<unistd.h>

int main() {
	const char *dev_in_path = "/dev/shofer_in";
	int fd_in = open(dev_in_path, O_RDWR);
	if(fd_in == -1) {
		perror("Error while opening device!");
		return errno;
	}
	
	if(ioctl(fd_in, 5) == -1) {
		perror("Error sending ioctl command.");
		return errno;
	}
	close(fd_in);
	return 0;
}
