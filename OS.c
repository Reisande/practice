#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

int test_fork() {
	int pid = fork();

	volatile int x = 0;
	
	if(pid < 0) {
		perror("Fork failed\n\n");
	} else if(pid == 0) {
		// child process
		printf("hello\n", x);
	} else {
		// parent process
		sleep(1);
		printf("goodbye\n", x);
	}
}

int main() {
	test_fork();
	
	return 0;
}
