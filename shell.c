#include "main.h"

/**
 * main - Entry point of the program
 *
 * Return: 0 on success, 1 on failure
 */
int main(void)
{
        char *buffer = NULL;
        size_t bufsize = 0;
        ssize_t nread;
        char *command;
        char *args[10];
        int status;

        while (1)
        {
                printf("#cisfun$ ");
                nread = getline(&buffer, &bufsize, stdin);
                if (nread == -1)
                {
                        printf("\n");
                        break;
                }
                command = strtok(buffer, " \n");
                args[0] = command;
                int i = 1;
                while ((args[i] = strtok(NULL, " \n")) != NULL)
                        i++;
                if (fork() == 0)
                {
                        if (execve(args[0], args, NULL) == -1)
                        {
                                fprintf(stderr, "%s: ", command);
                                perror("");
                                exit(1);
                        }
                }
                else
                {
                        wait(&status);
                }
        }

        free(buffer);

        return (0);
}
