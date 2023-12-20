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
		
		const char *device0_path = "/dev/shofer";		
		int fd = open(device0_path,O_WRONLY);
		
		if(fd == -1) {
			perror("Error opening some of the device!");
			return errno;
		}

		struct pollfd fds[1];
		fds[0].fd = fd;
		fds[0].events = POLLOUT;
		
		while(1) {
			int poll_result = poll(fds, 1, -1);
			if(poll_result == -1) {
				perror("Error in poll");
				break;
			}
			if(fds[0].revents & POLLOUT) {
				char buffer[1];

				// populate buffer with 1 char:
				buffer[0] = getRandomChar();
				sleep(2); // sleep for 2 secs as if something is being processed.
				ssize_t bytes_written = write(fds[0].fd, buffer, sizeof(buffer));
				if(bytes_written == -1) {
					perror("Error writing to device!");
					break;
				}
			}
		}
		// close file descriptors:
		close(fd);

		return 0;
		
}
