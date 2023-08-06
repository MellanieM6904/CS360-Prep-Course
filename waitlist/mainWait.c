// Name: Mellanie Martin
// Class: CS 360 Prep Course
// Date: August 2023

// Notes: testbed for waitlist.c

// HOUSEKEEPING; imports, structs, function prototypes, etc
# include <stdio.h>
# include "waitlist.h" // header file that contains structs and function prototypes
# include "waitlist.c" // file containing all functions

void main() {
    // test queueInit and queueAdd
    struct node *queue = queueInit();
    queueAdd(queue, "Georgie", "Martin", "Too many siblings");
    queueAdd(queue, "Buttercup", "Martin", "harness :(");
    queueAdd(queue, "Indy", "Martin", "Not enough rugs. 1/5 stars.");
    printf("%s\n", queue -> next -> next -> person.firstName); // should print Buttercup; it does!

    // test queueDelete
    queueDelete(queue);
    printf("%s\n", queue -> next -> person.firstName); // should print Buttercup; it does !

    // test queueHead
    struct individual head = queueHead(queue);
    printf("Name: %s %s; issue: %s\n", head.firstName, head.lastName, head.issue); // should print Name: Buttercup Martin; issue: harness :(; it does!

    // test queueTail
    struct individual tail = queueTail(queue);
    printf("Name: %s %s; issue: %s\n", tail.firstName, tail.lastName, tail.issue); // should print Name: Indy Martin; issue: Not enough rugs. 1/5 stars; it does!

    // test queueFree
    queueFree(queue);
}