// Name: Mellanie Martin
// Class: CS 360 Prep Course
// Date: August 2023

// Status: All tests passed, memory leaks still present (-20 pts). Score: 80

// HOUSEKEEPING; imports, structs, function prototypes, etc
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct bStack {
    char bracket;
    struct bStack* next;
};

void push(struct bStack *bracketStack, char bracket); // prototypes
void pop(struct bStack *bracketStack);

// --------------- //

void main(int argc, char **argv) {
    // declarations
    char *filename;
    char c;
    int balVal = 1; // Initialize balVal to 1

    // stack init
    struct bStack *bracketStack;
    bracketStack = malloc(sizeof(struct bStack));
    bracketStack->bracket = 'S'; // Sentinel Node
    bracketStack->next = NULL;

    // CLA handling
    filename = argv[1];
    // File handling
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) return; // file cannot be opened

    while ((c = fgetc(fp)) != EOF) {

        if (c == '{' || c == '[' || c == '(') {
            push(bracketStack, c);
        }

        if (c == '}' || c == ']' || c == ')') {
            if (bracketStack->next == NULL) {
                balVal = 0;
                break; // Break the loop if unbalanced bracket found
            }
            if (c == ']') {
                if (bracketStack->next->bracket == '[') {
                    pop(bracketStack);
                } else {
                    balVal = 0;
                    break; // Break the loop if unbalanced bracket found
                }
            }
            if (c == '}') {
                if (bracketStack->next->bracket == '{') {
                    pop(bracketStack);
                } else {
                    balVal = 0;
                    break; // Break the loop if unbalanced bracket found
                }
            }
            if (c == ')') {
                if (bracketStack->next->bracket == '(') {
                    pop(bracketStack);
                } else {
                    balVal = 0;
                    break; // Break the loop if unbalanced bracket found
                }
            }
        }
    }

    if (balVal == 1 && bracketStack->next == NULL) {
        printf("BALANCED");
    } else {
        printf("UNBALANCED");
    }

    // cleanup, free memory!
    struct bStack *nextEntry = bracketStack->next;
    while (nextEntry != NULL) {
        free(bracketStack);
        bracketStack = nextEntry;
        nextEntry = nextEntry->next;
    }
    free(bracketStack);
    //
}

void push(struct bStack *bracketStack, char bracket) {
    struct bStack *newEntry = malloc(sizeof(struct bStack));
    struct bStack *currentEntry = bracketStack;
    struct bStack *nextEntry = bracketStack->next;
    newEntry->bracket = bracket;

    currentEntry->next = newEntry;
    newEntry->next = nextEntry;
}

void pop(struct bStack *bracketStack) {
    struct bStack *currentEntry = bracketStack;
    struct bStack *nextEntry = bracketStack->next;

    currentEntry->next = nextEntry->next;
    free(nextEntry);
}