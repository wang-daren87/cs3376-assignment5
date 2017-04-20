// Daren Wang
// SE3376.502
//
// Assignment 5 Part 1-2
// TwoPipesThreeChildren.cpp
//
// This program executes "ls -ltr | grep 3376 | wc -l", by dividing the commands
// among three children processes.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
// Ignore compiler warning
#pragma GCC diagnostic ignored "-Wwrite-strings"

int main(int argc, char ** argv) {
	int childpid;
	int childpid2;
	int childpid3;

	char *ls_args[] = {"ls", "-ltr", NULL};
	char *grep_args[] = {"grep", "3376", NULL};
	char *wc_args[] = {"wc", "-l", NULL};

	int pipe1[2];
	int pipe2[2];
	pipe(pipe1);
	pipe(pipe2);
	// Parent creates first child
	if ((childpid = fork()) == -1) {
		perror("Error creating first child process");
		exit(1);
	}
	// First child executes ls -ltr
	// write to pipe1
	if (childpid == 0) {
		dup2(pipe1[1], 1);
		close(pipe1[0]);
		close(pipe1[1]);
		close(pipe2[0]);
		close(pipe2[1]);
		execvp(*ls_args, ls_args);
		exit(0);
	}
	// Parent creates second child
	if ((childpid2 = fork()) == -1) {
		perror("Error creating second child process");
		exit(1);
	}
	// Second child executes grep 3376
	// read from pipe1
	// write to pipe2
	if (childpid2 == 0) {
		dup2(pipe1[0], 0);
		dup2(pipe2[1], 1);
		close(pipe1[0]);
		close(pipe1[1]);
		close(pipe2[0]);
		close(pipe2[1]);
		execvp(*grep_args, grep_args);
		exit(0);
	}
	// Parent creates third child
	if ((childpid3 = fork()) == -1) {
		perror("error creating third child process");
		exit(1);
	}
	// Third child executes wc -l
	// read from pipe2
	if (childpid3 == 0) {
		dup2(pipe2[0], 0);
		close(pipe1[0]);
		close(pipe1[1]);
		close(pipe2[0]);
		close(pipe2[1]);
		execvp(*wc_args, wc_args);
		exit(0);
	}
	// remainder of Parent code body
	// sleep(2) to wait for children to finish executing
	sleep(2);
	return(0);
}
