// Name: Mellanie Martin
// Class: CS 360 Prep Course
// Date: August 2023

// HOUSEKEEPING; imports, structs, function prototypes, etc
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include "waitlist.h" // header file with structs and function prototypes

// --------------- //

/*
Argument(s): N/A
Returns: A node with an individual with firstName, lastName, and issue all being set to "SENTINEL", and node -> next is NULL
Notes: Initializes a Sentinel Node for the queue structure
Status: COMPLETE
*/
struct node *queueInit() {

    struct node *pNode = malloc(sizeof(struct node));
    strcpy(pNode -> person.firstName, "SENTINEL"); strcpy(pNode -> person.lastName, "SENTINEL"); strcpy(pNode -> person.issue, "SENTINEL");
    pNode -> next = NULL;
    return pNode;
}

/*
Argument(s): The sentinel node of the queue, and the firstName, lastName, and issue of the individual
that is to be inserted in to the tail of queue
Returns: N/A
Notes: Insert the individual into the tail of the queue
Status: COMPLETE
*/
void queueAdd(struct node *queue, char *firstName, char *lastName, char *issue) {

    struct node *nextEntry = queue -> next;

    while (nextEntry != NULL) {
        queue = nextEntry;
        nextEntry = nextEntry -> next;
    }

    struct node *newNode;
    newNode = malloc(sizeof(struct node));
    strcpy(newNode -> person.firstName, firstName); strcpy(newNode -> person.lastName, lastName); strcpy(newNode -> person.issue, issue);

    queue -> next = newNode; newNode -> next = nextEntry;
}

/*
Argument(s): The sentinel node of the queue
Returns: A structure of the individual tied to the header node (note this should be the structure itself, not a pointer
to the structure)
Notes: Removes the head of the queue. If the passed queue is empty, return a struct individual with all empty strings for
each value. Free the removed node from memory
Status: COMPLETE
*/
struct individual queueDelete(struct node* queue) {

    struct individual newHead;
    struct node *deletedEntry = queue -> next;
    strcpy(newHead.firstName, ""); strcpy(newHead.lastName, ""); strcpy(newHead.issue, ""); 

    if (deletedEntry == NULL) {
        return newHead;
    }

    queue -> next = deletedEntry -> next;

    strcpy(newHead.firstName, deletedEntry -> person.firstName);
    strcpy(newHead.lastName, deletedEntry -> person.lastName);
    strcpy(newHead.issue, deletedEntry -> person.issue);

    free(deletedEntry);
    return newHead;
}

/*
Argument(s): The sentinel node of the queue
Returns: A struct individual of the person in the head of the queue
Notes: Takes the sentinel node of the queue and returns data on the head of the queue. You may assume an empty queue
will not be passed to this function
Status: COMPLETE
*/
struct individual queueHead(struct node* queue) {

    struct individual currentHead;
    struct node *head = queue -> next;

    strcpy(currentHead.firstName, head -> person.firstName);
    strcpy(currentHead.lastName, head -> person.lastName);
    strcpy(currentHead.issue, head -> person.issue);

    return currentHead;
}

/*
Argument(s): The sentinel node of the queue
Returns: A regular structure of the tail of the queue
Notes: Pulls data on the tail of the queue. You may assume no empty queues will be passed to this function
Status: COMPLETE
*/
struct individual queueTail(struct node* queue) {

    struct individual currentTail;
    struct node *nextEntry = queue -> next;

    while (nextEntry != NULL) {
        queue = nextEntry;
        nextEntry = nextEntry -> next;
    }

    strcpy(currentTail.firstName, queue -> person.firstName);
    strcpy(currentTail.lastName, queue -> person.lastName);
    strcpy(currentTail.issue, queue -> person.issue);

    return currentTail;
}

/*
Argument(s): The sentinel node of the queue
Returns: N/A
Notes: Frees each node in the queue
Status: COMPLETE
*/
void queueFree(struct node* queue) {
    struct node *nextEntry = queue -> next;
    while (nextEntry != NULL) {
        free(queue);
        queue = nextEntry;
        nextEntry = nextEntry -> next;
    }
    free(queue);
}
