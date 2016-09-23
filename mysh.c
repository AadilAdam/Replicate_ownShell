/*---------------------------------------------------------------------------------*/
/* NAME:      AADIL AHMED ADAM
   CLASS:     CS590 
   SECTION:   01
   DESC:      PROGRAMMING ASSIGNMENT 2
   create our own shell in linux to imitate all the commands as executed by the existing shell. */
/*-----------------------------------------------------------------------------------*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#define MAX_LENGTH_COMMAND 200
#define MAX_NUMBER_OF_ARGS 15

void read_command(char* command, char* args[]);
int myshell_execCommand(char* args[]);

// Split the input command into array of arguments
void read_command(char* command, char* args[])
{       
    int i;
     for(i = 0; i < MAX_NUMBER_OF_ARGS; i++) {
        args[i] = strsep(&command, " ");
        if(args[i] == NULL) break;
    }
}


int myshell_execCommand(char* args[])
{
    pid_t pid;
	pid = fork(); //fork process

    if (pid == -1) {    //check if the child process is not created
        char* error = strerror(errno);
        printf("fork: %s\n", error);
        return 1;
    }
    // Child process
    else if (pid == 0) {
        execvp(args[0], args);   //exec function to the execute the entered command.  

        // check error when wrong input command is passed as arguments.
        char* error = strerror(errno);
        printf("shell: %s: %s\n", args[0], error);
        return 0;
    }
    // Parent process
    else {
        // Wait for child process to finish
        int childStatus;
        waitpid(pid, &childStatus, 0);
        return 1;
    }
}

int main()
{
    char command[MAX_LENGTH_COMMAND + 1];   // to store the command line arguments and the null character
    char* args[MAX_NUMBER_OF_ARGS + 1];

    while(1) {
        
        printf("aadil@shell > ");  //print prompt of the shell.

        // Read command from standard input, exit on Ctrl+D
        if(fgets(command, sizeof(command), stdin) == NULL) break;

        // Remove trailing newline character.
        if(command[strlen(command)-1] == '\n') {
            command[strlen(command)-1] = '\0';
        }
        read_command(command, args);

        // Exit my shell if "exit" is given.
        if(strcmp(args[0], "exit") == 0) break;
        if(myshell_execCommand(args) == 0) break;
    }
    return 0;
}

