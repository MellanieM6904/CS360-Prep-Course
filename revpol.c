// Name: Mellanie Martin
// Class: CS 360 Prep Course
// Date: August 2023

// Status: N/A

// Notes: When a number is read, push to stack. When an operator is read, pop the top 2 numbers in the stack, perform the operation
// and push the new value to stack. The numbers will be 1-9, and operators will be +, *, -, and /

// HOUSEKEEPING; imports, structs, function prototypes, etc
# include <stdio.h>
# include <stdlib.h>

typedef struct calcStack {
    int num;
    struct calcStack* next;
} RPN;

void push(RPN *numStack, int num); // prototypes
int pop(RPN *numStack);
int performOp(int n1, int n2, char operator);
void cleanup(RPN *numStack);

// --------------- //
// main function

int main(int argc, char **argv) {
    // declarations
    char *filename;
    char c;
    int num1, num2, result, input;
    char op;

    // stack init
    RPN* numStack;
    numStack = malloc(sizeof(RPN));
    numStack -> num = -1; // Sentinel Node
    numStack -> next = NULL;

    // CLA handling
    filename = argv[1];
    // File handling
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) return -1; // file cannot be opened

    while (1 == 1) {
        // if a number is read
        if (fscanf(fp, "%d", &input) == 1) { // fscanf returns 1 when the input is matched with the format specifier
            push(numStack, input); // push any encountered number to stack
        // if an operator is read
        } else if (fscanf(fp, "%c", &op) == 1) {
            // if there is less than 2 numbers in the stack when an operator is encountered
            if (numStack -> next == NULL || numStack -> next -> next == NULL) {
                printf("INVALID");
                cleanup(numStack);
                return 0;
            }

            num2 = pop(numStack); // get values of popped stack nodes
            num1 = pop(numStack);
            
            result = performOp(num1, num2, op); // performs the operation determined by the encountered operator

            push(numStack, result); // push result to stack
        } else break; // if a number or operator is not found, EOF
    }

    if (numStack -> next -> next != NULL) { // if there is only one number left in stack at EOF
        printf("INVALID");
        cleanup(numStack);
        return 0;
    }

    printf("%i", numStack -> next -> num); // print result of expression
}

// --------------- //
// Non-main Functions

/*
Argument(s): An already existing RPN struct
Returns: N/A
Notes: Pushes to the stack
Status: COMPLETE
*/
void push(RPN *numStack, int num) {
    RPN *newEntry = malloc(sizeof(RPN));
    RPN *currentEntry = numStack;
    RPN *nextEntry = numStack -> next;
    newEntry -> num = num;

    currentEntry -> next = newEntry;
    newEntry -> next = nextEntry;
}

/*
Argument(s): An already existing RPN struct
Returns: The popped value
Notes: Pops from stack
Status: COMPLETE
*/
int pop(RPN *numStack) {
    RPN *currentEntry = numStack;
    RPN *nextEntry = numStack -> next;
    int poppedValue = nextEntry -> num;

    currentEntry -> next = nextEntry -> next;

    return poppedValue;
}

/*
Argument(s): 2 integers and a char
Returns: The result of the operation
Notes: Performs the operation dictated by the passed operator
Status: COMPLETE
*/
int performOp(int n1, int n2, char operator) {
    if (operator == '+') {
        return n1 + n2;
    } else if (operator == '-') {
        return n1 - n2;
    } else if (operator == '*') {
        return n1 * n2;
    } else if (operator == '/') {
        return n1 / n2;
    }

    return -1;
}

/*
Argument(s): An already existing RPN struct
Returns: N/A
Notes: Frees all memory
Status: COMPLETE
*/
void cleanup(RPN *numStack) {
    RPN *nextEntry = numStack -> next;
    while (nextEntry != NULL) {
        free(numStack);
        numStack = nextEntry;
        nextEntry = nextEntry->next;
    }
    free(numStack);
}