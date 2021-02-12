/**************************************************************
* Class:  CSC-415-01 Fall 2020
* Name: Phyoe Thu
* Student ID: 918656575
* GitHub ID: phyoethu100
* Project: Assignment 3 - Simple Shell
*
* File: thu_phyoe_HW3_main.c 
*
* Description: This program creates a simple shell using fork(),
* execvp(), and wait(). 
**************************************************************/

#include <stdbool.h>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFFER_SIZE 512
#define MAX_ARGS 256

int main(int argc, char *argv[MAX_ARGS]) {

    bool start = true; // Start the new program
    char buffer[BUFFER_SIZE]; // Get user input from the command and store it in the buffer
    char *prompt = argv[1]; // Set second command line argument to prefix prompt 
    char *space = " "; // Create a space 
    char *token; // Breaks the string into a series of tokens 
    int length = 0; // Length of the buffer from user input
    pid_t pid; // For fork()
    pid_t returned; // Return the status of wait()
    pid_t status; // Status of wait()
    pid_t wait_pid; // For wait()
   
    while(start) {

        if (prompt == NULL) { // If no prompt value is specified, display ">" as a prompt
            printf("\n> ");
        }
        else { // Else display second command line argument as a prompt
            printf("\n%s ", prompt);
        }

        fgets(buffer, BUFFER_SIZE, stdin); // Read the user input from the command line
        fflush (stdin);

        length = strlen(buffer); // Length of the buffer, fgets() adds an extra \n 

        if ((length - 1) == 0) { // Check if buffer length is empty or not
            fprintf(stderr, "Empty string\n"); // Display error message
            continue; // Continue with next prompt 
        }

        if (length > BUFFER_SIZE) { // Check if buffer length is greater than given 512 bytes bufer
            length = BUFFER_SIZE; // Truncate the buffer length to 512 bytes 
        }

        if (buffer[length - 1] == '\n') { // Check for new line
            buffer[length - 1] = '\0'; // Terminate the buffer
        }

        if (strcmp(buffer, "exit") == 0) { // If the user enters exit, the program will go back to the original shell
            printf("Exit successfully...\n");
            exit(0);
        }

        token = strtok(buffer, space); // Split the buffer into different strings after each space

        int i = 0; // Set starting index to 0

        while (token != NULL) { // The token is not empty
            argv[i] = token; // Assign first argument to the token and keep incrementing
            token = strtok(NULL, space);
            i++; 
        }

        argv[i] = NULL; // Set argv[i] to null
        argc = i; // Get total number of arguments

        pid = fork(); // Create a new child process
       
        if (pid < 0) {
            perror("Failed to fork");
            exit(1);
        }

        else if (pid == 0) { // Child id
            execvp(argv[0], argv); // Replaces the current process with new process
            fprintf(stderr, "Child %d cannot be executed, exited with %d\n", wait_pid, returned);
        }

        else { // Parent id
            wait_pid = wait(&status); // Waits until child id exits 
            returned = WEXITSTATUS(status); // Return value of the status from the wait
            printf("Child %d, exited with %d\n", wait_pid, returned); 
        }
        
    }

}
