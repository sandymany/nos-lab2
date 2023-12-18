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
		const char *device2_path = "/dev/shofer2";
		const char *device3_path = "/dev/shofer3";
		const char *device4_path = "/dev/shofer4";
		const char *device5_path = "/dev/shofer5";
		
		int fd0 = open(device0_path,O_RDONLY);
		int fd1 = open(device1_path, O_RDONLY);
		int fd2 = open(device2_path, O_RDONLY);
		int fd3 = open(device3_path, O_RDONLY);
		int fd4 = open(device4_path, O_RDONLY);
		int fd5 = open(device5_path, O_RDONLY);
		
		const int buffer_size = 1;
		
		if(fd0 == -1 || fd1 == -1 || fd2 == -1 || fd3 == -1 || fd4 == -1 || fd5 == -1) {
				perror("Error opening the device");
				return errno;
		}

		struct pollfd fds[6];
		fds[0].fd = fd0;
		fds[1].fd = fd1;
		fds[2].fd = fd2;
		fds[3].fd = fd3;
		fds[4].fd = fd4;
		fds[5].fd = fd5;
		fds[0].events = POLLIN;
		fds[1].events = POLLIN;
		fds[2].events = POLLIN;
		fds[3].events = POLLIN;
		fds[4].events = POLLIN;
		fds[5].events = POLLIN;
		
		while(1) {
			int poll_result = poll(fds, 6, -1);
			if(poll_result == -1) {
				perror("Error in poll");
				break;
			}
			for(int i = 0; i < 7; i++) {
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
		close(fd2);
		close(fd3);
		close(fd4);
		close(fd5);
		return 0;
		
}
