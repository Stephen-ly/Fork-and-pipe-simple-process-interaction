#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXLINE 256
#define MAX_PASSWORD 10

#define SUCCESS "Password verified\n"
#define INVALID "Invalid password\n"
#define NO_USER "No such user\n"

int main(void) {
  char user_id[MAXLINE];
  char password[MAXLINE];
  int     fd[2];
  pid_t   childpid;
  pipe(fd);

  if(fgets(user_id, MAXLINE, stdin) == NULL) {
      perror("fgets");
      exit(1);
  }
  if(fgets(password, MAXLINE, stdin) == NULL) {
      perror("fgets");
      exit(1);
  }
  int n =  fork();
 
  if (n!=0){
	close(fd[0]);
        write(fd[1], user_id, MAX_PASSWORD);
        write(fd[1], password, MAX_PASSWORD);
	close(fd[1]);
	int status;
        if ( waitpid(n, &status, 0) == -1 ) {
        perror("waitpid failed");
        return EXIT_FAILURE;
        }

        if ( WIFEXITED(status) ) {
        const int es = WEXITSTATUS(status);
       	if (es == 0)
		printf("Password verified\n");
	else if (es == 2)
		printf("Invalid	password\n");
	else if (es == 3)
		printf("No such user\n");
    }
  }
 
  if (n==0){
 	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
        printf("this is what's in STDIN: %i", STDIN_FILENO);
        execl("./validate","validate", NULL);	
	close(fd[0]);  
}


  return 0;
}
