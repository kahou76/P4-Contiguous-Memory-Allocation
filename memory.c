#include <stdio.h>    //perror
#include <stdlib.h>   //exit
#include <string.h>
#include <fcntl.h>

#include "task.h"
#include "list.h"
// #include "allocation_ff.h"

#define SIZE    100
#define MAX_LINE 80 /* The maximum length command */
int should_run = 1;

struct node *head = NULL;
struct node *tail = NULL;
struct node *newNode = NULL;

int takeInput(char input[]);
void printList();
void firstFit(char *name, int space);


//function to take user input
int takeInput(char input[]){
    printf("enter>");
    fflush(stdout);
    //get user input
    fgets(input, MAX_LINE, stdin);
    // check if the last character of the input is '\n', if so, replace it with '\0'
    if(input[strlen(input) - 1] == '\n'){
        input[strlen(input) - 1] = '\0';
    }
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
    args[i] = token;
    token = strtok(NULL, " ");
    i++;
  }
  args[i] = NULL;
  return i;
}

void printList(){
    struct node *curr = head;
    while(curr != NULL){
        
        int currSize = curr->task->availableSpace;
        
        printf("CURR NODE: %s %d", curr->task->letter, currSize);
        while(currSize-->0){
            printf("%s",curr->task->letter);
        }
        curr = curr->next;
    }
    printf("\n");
}

void firstFit(char *name, int space){
    printf("DOING FIRST FIT %s  %d\n", name, space);

    //if head is . && space is 80
    if(strcmp(head->task->letter, ".") == 0 && head->task->availableSpace == 80){
        newNode = malloc(sizeof(struct node));
        newNode->task = malloc(sizeof(struct task));
        newNode->task->letter = name;
        newNode->task->availableSpace = space;
        head->task->availableSpace -= space;
        newNode->next = head;
        head = newNode;
    }else{
        //insert it between tail
        struct node * curr = head;
        while(curr != NULL && curr->next != NULL){
            if(strcmp(curr->next->task->letter, ".") == 0 && curr->next->task->availableSpace >= space){
                newNode = malloc(sizeof(struct node));
                newNode->task = malloc(sizeof(struct task));
                newNode->task->letter = name;
                newNode->task->availableSpace = space;
                curr->next->task->availableSpace -= space;
                newNode->next = curr->next;
                curr->next = newNode->next;
                printf("DONE\n");
                break;
            }
            curr = curr->next;
        }
    }

    //print it out
    struct node *curr = head;
    int count = 0;
    while(curr != NULL){
        count++;
        int currSize = curr->task->availableSpace;
        char *currName = curr->task->letter;
        printf("CURR NODE: %s %d\n", currName, currSize);
        while(currSize-->0){
            printf("%s",currName);
        }
        printf("\n");
        curr = curr->next;
    }
    printf("\n");
    printf("COUNT: %d\n", count);



}

void bestFit(char *name, int space){
    printf("DOING BEST FIT %s  %d\n", name, space);

    //if head is . && space is 80
    if(strcmp(head->task->letter, ".") == 0 && head->task->availableSpace == 80){
        newNode = malloc(sizeof(struct node));
        newNode->task = malloc(sizeof(struct task));
        newNode->task->letter = name;
        newNode->task->availableSpace = space;
        head->task->availableSpace -= space;
        newNode->next = head;
        head = newNode;
    }
    else{
        //find the closet first
        int min = 80;
        struct node* curr = head;
        while( curr != NULL){
            if(strcmp(curr->task->letter, ".") == 0 && curr->task->availableSpace < min && min >= space){
                min = curr->task->availableSpace;
            }
            curr = curr->next;
        }
        //then insert it
        curr = head;
        while(curr != NULL && curr->next != NULL){
            if(strcmp(curr->next->task->letter, ".") == 0 && curr->next->task->availableSpace == min){
                newNode = malloc(sizeof(struct node));
                newNode->task = malloc(sizeof(struct task));
                newNode->task->letter = name;
                newNode->task->availableSpace = space;
                curr->next->task->availableSpace -= space;
                newNode->next = curr->next;
                curr->next = newNode->next;
                printf("BEST FIT DONE\n");
                break;
            }
            curr = curr->next;
        }

    }
}

void worstFit(char *name, int space){
    printf("DOING WORST FIT %s  %d\n", name, space);

    //if head is . && space is 80
    if(strcmp(head->task->letter, ".") == 0 && head->task->availableSpace == 80){
        newNode = malloc(sizeof(struct node));
        newNode->task = malloc(sizeof(struct task));
        newNode->task->letter = name;
        newNode->task->availableSpace = space;
        head->task->availableSpace -= space;
        newNode->next = head;
        head = newNode;
    }
    else{
        //find the max first
        int max = 0;
        struct node* curr = head;
        while( curr != NULL){
            if(strcmp(curr->task->letter, ".") == 0 && max < curr->task->availableSpace && max >= space){
                max = curr->task->availableSpace;
            }
            curr = curr->next;
        }
        //then insert it
        curr = head;
        while(curr != NULL && curr->next != NULL){
            if(strcmp(curr->next->task->letter, ".") == 0 && curr->next->task->availableSpace == max){
                newNode = malloc(sizeof(struct node));
                newNode->task = malloc(sizeof(struct task));
                newNode->task->letter = name;
                newNode->task->availableSpace = space;
                curr->next->task->availableSpace -= space;
                newNode->next = curr->next;
                curr->next = newNode->next;
                printf("WORST FIT DONE\n");
                break;
            }
            curr = curr->next;
        }

    }
} 

void allocate(int length, char *args[]){
    if(strcmp(args[3], "F") == 0){
        //First fit
        firstFit(args[1],atoi(args[2]));
        
    }
    else if(args[3] == "B"){
        //Best fit
        bestFit(args[1],atoi(args[2]));
    }
    else if(args[3] == "W"){
        //Worst fit
        worstFit(args[1],atoi(args[2]));
    }
}

void freeSpace(char* name){
    struct node* curr = head;
    while(curr != NULL){
        if(strcmp(curr->task->letter, name) == 0){
            curr->task->letter = ".";
        }
        curr = curr->next;
    }
}

void compactList(){
    struct node* curr = head;
    while(curr != tail && curr->next != NULL){
        if(strcmp(curr->next->task->letter, ".") == 0 && curr->next->next != NULL){
            tail->task->availableSpace += curr->next->task->availableSpace;
            curr->next = curr->next->next;
        }
    }
}

void readFile(char* file){
    FILE *in;
    char *temp;
    char task[SIZE];
    char *args[MAX_LINE/2 + 1];

    in = fopen(file, "r");
    while(fgets(task,SIZE,in) != NULL){
        //process each row
        temp = strdup(task);
        //print out the input first
        printf("enter>%s\n", temp);
        //then execute it
        int length = tokenFunction(temp, args);
        executeCommand(length, args);
    }
}

void executeCommand(int length, char *args[]){

    if(strcmp(args[0], "A") == 0){
        //allocation
        allocate(length, args);
    }

    if(strcmp(args[0], "F") == 0){
        //free
        freeSpace(args[1]);
    }

    if(strcmp(args[0], "S") == 0){
        //print
        printList();
    }

    if(strcmp(args[0], "C") == 0){
        //compact
        compactList();
    }

    if(strcmp(args[0], "R") == 0){
        //read
        readFile(args[1]);
    }

    if(strcmp(args[0], "E") == 0){
        //Exit
        should_run = -1;
    }

}

void initalHead(){
    head = malloc(sizeof(struct node));
    tail = malloc(sizeof(struct node));
    head->task = malloc(sizeof(struct task));

    head->task->letter = ".";
    head->task->availableSpace = 80;
    head->next = NULL;
    tail = head;
}


int main(void){
    char *args[MAX_LINE/2 + 1]; /* command input arguments */
     /* flag to determine when to exit program */
    //user input is the destination buffer to store the read input
    char input[MAX_LINE];
    //inital list first
    initalHead();
    while(should_run){
        int runInput = takeInput(input);
        if(runInput == 1){
            int length = tokenFunction(input, args);
            executeCommand(length, args);
        }else{
            should_run = 0;
        }
    }
    return 0;
}