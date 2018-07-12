#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include<sys/wait.h>
/*
Recursive definition of the number of forks
f(n) = 2^n+2^(n-1)+2^(n-2)....+2^(1)

ASCII diagram for processes

4 -> 118 -> 119 -> 121 -> 125 -> 133
		   121 -> 132
            119 -> 124 -> 131
            119 -> 129
     118 -> 120 -> 123 -> 130
	    120 -> 127
     118 -> 122 -> 128
     118 -> 126
 

*/
int main(int argc, char **argv) {
    int i;
    int iterations;

    if (argc != 2) {
        fprintf(stderr, "Usage: forkloop <iterations>\n");
        exit(1);
    }

    iterations = strtol(argv[1], NULL, 10);

    for (i = 0; i < iterations; i++) {
        int n = fork();
	wait(NULL);
        if (n != 0){
		break;
	}
        if (n < 0) {
            perror("fork");
            exit(1);
        }
        printf("ppid = %d, pid = %d, i = %d\n", getppid(), getpid(), i);
    }

    return 0;
}
