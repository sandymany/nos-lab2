#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<unistd.h>
#include<poll.h>

// otvara sve naprave za citanje (od 0 do 5 shofer)
// s poll cekanje da se na bilo kojoj pojavi znak
// ispisuje znak

int main() {
		
		const char *device0_path = "/dev/shofer0";
		const char *device1_path = "/dev/shofer1";
		
		int fd0 = open(device0_path,O_RDONLY);
		int fd1 = open(device1_path, O_RDONLY);
		
		const int buffer_size = 1;
		
		if(fd0 == -1 || fd1 == -1) {
				perror("Error opening the device");
				return errno;
		}

		struct pollfd fds[2];
		fds[0].fd = fd0;
		fds[1].fd = fd1;
		fds[0].events = POLLIN;
		fds[1].events = POLLIN;
		
		while(1) {
			int poll_result = poll(fds, 2, -1);
			if(poll_result == -1) {
				perror("Error in poll");
				break;
			}
			for(int i = 0; i < 2; i++) {
				if(fds[i].revents & POLLIN) {
					char buffer[1];
					ssize_t bytes_read = read(fds[i].fd, buffer, sizeof(buffer));
					if(bytes_read == -1) {
						perror("Error reading from device!");
						break;
					}
					// process data from device:
					printf("Reading data from shofer%d\n", i);
					write(STDOUT_FILENO, buffer, bytes_read);
					printf("\n");
					}
			}
		}
		// close file descriptors:
		close(fd0);
		close(fd1);
		//char buffer[buffer_size];
		//ssize_t bytes_read;
		//bytes_read=read(file_descriptor, buffer, sizeof(buffer));
		//write(STDOUT_FILENO, buffer, bytes_read);
		
		//close(file_descriptor);
		return 0;
		
}
