// Daren Wang
// SE3376.502
//
// Assignment 5 Part 2
// DynPipe.cpp
//
// This program executes shell commands passed as arguments. It accepts between
// 2 and 5 total commands with options. Options must be included, or empty
// string placeholder.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
// Ignore compiler warnings
#pragma GCC diagnostic ignored "-Wwrite-strings"
#pragma GCC diagnostic ignored "-Wunused-variable"

int main(int argc, char ** argv) {
	// Check for valid argument count
	if (argc < 3 || argc > 6) {
		perror("Invalid \"command options\" count. Min 2, max 5.");
		exit(1);
	}

	int childpid;
	int childpid2;
	int childpid3;
	int childpid4;
	int childpid5;
	
	// Extract first "command -options"
	// Assume maximum 4 options per command
	char *first_args[5];
	int i = 0;
	char s[2] = " ";
	first_args[i] = strtok(argv[1],s);
	while(first_args[i] != NULL) {
		i++;
		first_args[i] = strtok(NULL,s);
	}

	// Extract second "command -options"
	// Assume maximum 4 options per command
	char *second_args[5];
	i = 0;
	second_args[i] = strtok(argv[2],s);
	while(second_args[i] != NULL) {
		i++;
		second_args[i] = strtok(NULL,s);
	}
	char *third_args[5];
	char *fourth_args[5];
	char *fifth_args[5];

	int pipe1[2];
	int pipe2[2];
	int pipe3[2];
	int pipe4[2];
	pipe(pipe1);
	pipe(pipe2);
	pipe(pipe3);
	pipe(pipe4);
	if (argc > 3) {
		// Extract third "command -options"
		// Assume maximum 4 options per command
		i = 0;
		third_args[i] = strtok(argv[3],s);
		while(third_args[i] != NULL) {
			i++;
			third_args[i] = strtok(NULL,s);
		}
	}
	if (argc > 4) {
		// Extract fourth "command -options"
		// Assume maximum 4 options per command
		i = 0;
		fourth_args[i] = strtok(argv[4],s);
		while(fourth_args[i] != NULL) {
			i++;
			fourth_args[i] = strtok(NULL,s);
		}
	}
	if (argc > 5) {
		// Extract fifth "command -options"
		// Assume maximum 4 options per command
		i = 0;
		fifth_args[i] = strtok(argv[5],s);
		while(fifth_args[i] != NULL) {
			i++;
			fifth_args[i] = strtok(NULL,s);
		}
	}
	// Parent creates first child
	if((childpid = fork()) == -1) {
		perror("Error creating first child process");
		exit(1);
	}
	// First child execute first command
	// write to pipe1
	if (childpid == 0) {
		dup2(pipe1[1], 1);
		close(pipe1[0]);
		close(pipe1[1]);
		close(pipe2[0]);
		close(pipe2[1]);
		close(pipe3[0]);
		close(pipe3[1]);
		close(pipe4[0]);
		close(pipe4[1]);
		execvp(*first_args, first_args);
		exit(0);
	}
	// Parent creates second child
	if((childpid2 = fork()) == -1) {
		perror("Error creating second child process");
		exit(1);
	}
	// Second child executes second command
	// read from pipe1
	// write to pipe2 if more than two commands
	if (childpid2 == 0) {
		dup2(pipe1[0], 0);
		if (argc > 3) {
			dup2(pipe2[1], 1);
		}
		close(pipe1[0]);
		close(pipe1[1]);
		close(pipe2[0]);
		close(pipe2[1]);
		close(pipe3[0]);
		close(pipe3[1]);
		close(pipe4[0]);
		close(pipe4[1]);
		execvp(*second_args, second_args);
		exit(0);
	}
	// If more than two commands
	if (argc > 3) {
		// Parent creates third child
		if((childpid3 = fork()) == -1) {
			perror("Error creating third child process");
			exit(1);
		}
		// Third child executes third command
		// read from pipe2
		// write to pipe3 if more than three commands
		if (childpid3 == 0) {
			dup2(pipe2[0], 0);
			if (argc > 4) {
				dup2(pipe3[1], 1);
			}
			close(pipe1[0]);
			close(pipe1[1]);
			close(pipe2[0]);
			close(pipe2[1]);
			close(pipe3[0]);
			close(pipe3[1]);
			close(pipe4[0]);
			close(pipe4[1]);
			execvp(*third_args, third_args);
			exit(0);
		}
	}
	// If more than three commands
	if (argc > 4) {
		// Parent creates fourth child
		if((childpid4 = fork()) == -1) {
			perror("Error creating fourth child process");
			exit(1);
		}
		// Fourth child executes fourth command
		// read from pipe3
		// write to pipe4 if more than four commands
		if (childpid4 == 0) {
			dup2(pipe3[0], 0);
			if (argc > 5) {
				dup2(pipe4[1], 1);
			}
			close(pipe1[0]);
			close(pipe1[1]);
			close(pipe2[0]);
			close(pipe2[1]);
			close(pipe3[0]);
			close(pipe3[1]);
			close(pipe4[0]);
			close(pipe4[1]);
			execvp(*fourth_args, fourth_args);
			exit(0);
		}
	}
	// If more than four commands
	if (argc > 5) {
		// Parent creates fifth child
		if((childpid5 = fork()) == -1) {
			perror("Error creating fifth child process");
			exit(1);
		}
		// Fifth child executes fifth command
		// read from pipe4
		if (childpid5 == 0) {
			dup2(pipe4[0], 0);
			close(pipe1[0]);
			close(pipe1[1]);
			close(pipe2[0]);
			close(pipe2[1]);
			close(pipe3[0]);
			close(pipe3[1]);
			close(pipe4[0]);
			close(pipe4[1]);
			execvp(*fifth_args, fifth_args);
			exit(0);
		}
	}
	close(pipe1[0]);
	close(pipe1[1]);
	close(pipe2[0]);
	close(pipe2[1]);
	close(pipe3[0]);
	close(pipe3[1]);
	close(pipe4[0]);
	close(pipe4[1]);
	// sleep(2) to wait for children to complete
	sleep(2);
	return(0);
}
