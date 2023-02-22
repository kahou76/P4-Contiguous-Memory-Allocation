#include <stdio.h>    //perror
#include <stdlib.h>   //exit
#include <sys/wait.h> //wait
#include <unistd.h>   //fork, pipe
#include <string.h>
#include <fcntl.h>

#define MAX_LINE 80 /* The maximum length command */

int takeInput(char input[]);


//function to take user input
int takeInput(char input[]){
    printf("osh>");
    fflush(stdout);
    //get user input
    fgets(input, MAX_LINE, stdin);
    // check if the last character of the input is '\n', if so, replace it with '\0'
    if(input[strlen(input) - 1] == '\n'){
        input[strlen(input) - 1] = '\0';
    }
    //set tail
    // input[strlen(input)-1] = '\0';
    //check if user entered "exit" to exit the program
    if(strcmp(input, "E") == 0){
        return -1;
    }
    return 1;
}

//tokenize the input
int tokenFunction(char input[], char *args[]){
  //function to parse user input into tokens
  //separate each word with space
  char *token = strtok(input, " ");
  int i=0;
  while(token != NULL){
    printf("Token %d: %s \n", i, token);
    args[i] = token;
    token = strtok(NULL, " ");
    i++;
  }
  args[i] = NULL;
  return i;
}

void executeTemplate(char *args[]){
    int pid = fork();
    if(pid < 0){
        // error occurred
        fprintf(stderr, "Error: Fork Failed\n");
        exit(EXIT_FAILURE);
    }else if(pid == 0){
        //child process
        execvp(args[0], args);
    }else{
        //parent process
        int wait_status;
        waitpid(pid, &wait_status, 0);
    }
}


int main(void){
    char *args[MAX_LINE/2 + 1]; /* command input arguments */
    int should_run = 1; /* flag to determine when to exit program */
    //user input is the destination buffer to store the read input
    char input[MAX_LINE];
    while(should_run){
        int runInput = takeInput(input);
        if(runInput == 1){
            int length = tokenFunction(input, args);
            
                // execute(args, length);
        }else{
            should_run = 0;
        }
    }
    return 0;
}