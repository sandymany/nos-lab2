#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>

int main() {
		
		const char *device_path = "/dev/shofer0";
		int file_descriptor = open(device_path,O_RDONLY);
		const int buffer_size = 1;

		if(file_descriptor == -1) {
				perror("Error opening the device");
				return errno;
		}
		
		char buffer[buffer_size];
		ssize_t bytes_read;
		bytes_read=read(file_descriptor, buffer, sizeof(buffer));
		write(STDOUT_FILENO, buffer, bytes_read);
		
		close(file_descriptor);
		return 0;
		
}
