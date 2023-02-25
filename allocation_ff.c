#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task.h"
#include "list.h"
#include "allocation_ff.h"

struct node *head = NULL;
struct node *tail = NULL;
struct node *newNode = NULL;

void add(int length, char *args[]){
    for(int i=0; i<length; i++){
        printf("I: %d      Element: %s\n", i, args[i]);
    }
}