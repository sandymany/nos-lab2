#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<unistd.h>
#include<poll.h>
#include<time.h>
#include<stdlib.h>

// otvara sve naprave za pisanje (od 0 do 5 shofer)
// s poll cekanje da se na bilo kojoj pojavi mjesta za pisanje
// upisuje znak


char getRandomChar() {
	srand((unsigned int) time(NULL));
	const char charRangeStart = 'A';
	const char charRangeEnd = 'Z';
	int charRangeSize = charRangeEnd - charRangeStart + 1;
	int randomIndex = rand() % charRangeSize;
	char randomChar = charRangeStart + randomIndex;
	return(randomChar);
}

int main() {
		
		const char *device0_path = "/dev/shofer0";
		const char *device1_path = "/dev/shofer1";
		const char *device2_path = "/dev/shofer2";
		const char *device3_path = "/dev/shofer3";
		const char *device4_path = "/dev/shofer4";
		const char *device5_path = "/dev/shofer5";		
		int fd0 = open(device0_path,O_WRONLY);
		int fd1 = open(device1_path, O_WRONLY);
		int fd2 = open(device2_path, O_WRONLY);
		int fd3 = open(device3_path, O_WRONLY);
		int fd4 = open(device4_path, O_WRONLY);
		int fd5 = open(device5_path, O_WRONLY);
		
		if(fd0 == -1 || fd1 == -1 || fd2 == -1 || fd3 == -1 || fd4 == -1 || fd5 == -1) {
				perror("Error opening some of the device!");
				return errno;
		}

		struct pollfd fds[6];
		fds[0].fd = fd0;
		fds[1].fd = fd1;
		fds[2].fd = fd2;
		fds[3].fd = fd3;
		fds[4].fd = fd4;
		fds[5].fd = fd5;
		
		fds[0].events = POLLOUT;
		fds[1].events = POLLOUT;
		fds[2].events = POLLOUT;
		fds[3].events = POLLOUT;
		fds[4].events = POLLOUT;
		fds[5].events = POLLOUT;
		
		while(1) {
			int poll_result = poll(fds, 6, -1);
			if(poll_result == -1) {
				perror("Error in poll");
				break;
			}
			for(int i = 0; i < 7; i++) {
				if(fds[i].revents & POLLOUT) {
					char buffer[1];

					// populate buffer with 1 char:
					buffer[0] = getRandomChar();
					sleep(2); // sleep for 2 secs as if something is being processed.

					ssize_t bytes_written = write(fds[i].fd, buffer, sizeof(buffer));
					if(bytes_written == -1) {
						perror("Error reading from device!");
						break;
					}
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
