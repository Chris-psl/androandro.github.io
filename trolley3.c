#include <stdio.h>
#include <stdlib.h>

int main() {

    char input[100];
    int left, right;

    while (1) {

        // Asks for the left value input
        printf("Enter left value or press Ctrl+D to exit:");

        // Reads the input from the user
        if (fgets(input, sizeof(input), stdin) == NULL) {
            // If EOF is encountered, break the loop
            break;
        }

        // Parse the input to get the left number
        if (sscanf(input, "%d", &left) != 1) {
            printf("No left cost provided.\n");
            return 1;
        }

        //Asks for the right value input
        printf("Enter right value or press Cntrl+D to exit:");
        
        // Reads the input from the user
        if (fgets(input, sizeof(input), stdin) == NULL) {
            // If EOF is encountered, break the loop
            break;
        }

        // Parse the input to get the right number
        if (sscanf(input, "%d", &right) != 1) {
            printf("No right cost provided.\n");
            return 1;
        }

        // Compare the numbers and print the result
        if (left <= right) {
            printf("go left\n");
        } else {
            printf("go right\n");
        }
    }
    //Prints Exiting message and then terminates the program with code 0
    printf("\nExiting...\n");
    return 0;
}
