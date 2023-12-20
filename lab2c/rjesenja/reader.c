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
		
		const char *device0_path = "/dev/shofer";
		
		int fd = open(device0_path,O_RDONLY);
		
		const int buffer_size = 1;
		
		if(fd == -1) {
				perror("Error opening the device");
				return errno;
		}

		struct pollfd fds[1];
		fds[0].fd = fd;
		fds[0].events = POLLIN;
		
		while(1) {
			int poll_result = poll(fds, 1, -1);
			if(poll_result == -1) {
				perror("Error in poll");
				break;
			}
			if(fds[0].revents & POLLIN) {
				char buffer[1];
				ssize_t bytes_read = read(fds[0].fd, buffer, sizeof(buffer));
				if(bytes_read == -1) {
					perror("Error reading from device!");
					break;
				}
				else if(bytes_read != 0) {
					write(STDOUT_FILENO, buffer, bytes_read);
					printf("\n");	
				}
			}
		}
		// close file descriptors:
		close(fd);
		return 0;
		
}
