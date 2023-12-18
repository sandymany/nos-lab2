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

	//time_t t;
	//srand((int) time(&t)%22);
	//const char charset[] = "1234567890abcdefghijklmnopqrstuvwxyz";
	//int upper = 30;
	//int lower = 0;
	//int rand_num = (rand()%(upper-lower+1))+lower;
	//return(charset[rand_num]);
}

int main() {
		
		const char *device0_path = "/dev/shofer0";
		const char *device1_path = "/dev/shofer1";
		
		int fd0 = open(device0_path,O_WRONLY);
		int fd1 = open(device1_path, O_WRONLY);
		
		//const int buffer_size = 1;
		
		if(fd0 == -1 || fd1 == -1) {
				perror("Error opening some of the device!");
				return errno;
		}

		struct pollfd fds[2];
		fds[0].fd = fd0;
		fds[1].fd = fd1;
		fds[0].events = POLLOUT;
		fds[1].events = POLLOUT;
		
		while(1) {
			int poll_result = poll(fds, 2, -1);
			if(poll_result == -1) {
				perror("Error in poll");
				break;
			}
			for(int i = 0; i < 2; i++) {
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
		//char buffer[buffer_size];
		//ssize_t bytes_read;
		//bytes_read=read(file_descriptor, buffer, sizeof(buffer));
		//write(STDOUT_FILENO, buffer, bytes_read);
		
		//close(file_descriptor);
		return 0;
		
}
