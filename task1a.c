#include "shell.h"

int main() {
    char input[MAX_INPUT_LENGTH];
    char* args[] = {NULL};

    while(1) {
        printf("> ");

        if(fgets(input, MAX_INPUT_LENGTH, stdin) == NULL) {
            break;
        }

        // Remove trailing newline character
        input[strcspn(input, "\n")] = '\0';

        if(strlen(input) == 0) {
            continue;
        }

        pid_t pid = fork();

        if(pid == -1) {
            perror("fork failed");
            exit(1);
        } else if(pid == 0) {
            // Child process
            if(execvp(input, args) == -1) {
                printf("%s: command not found\n", input);
                exit(1);
            }
        } else {
            // Parent process
            wait(NULL);
        }
    }

    printf("\n");
    return 0;
}
