#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>

int main() {
		const char *device_path = "/dev/shofer";
		int fd = open(device_path,O_RDONLY);

		if(file_descriptor == -1) {
				perror("Error opening the device");
				return errno;
		}

		close(file_descriptor);
		return 0;
		
}
