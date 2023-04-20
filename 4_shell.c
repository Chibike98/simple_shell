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
        char *args[4];
        int status;

        while (1)
        {
                printf(":) ");
                nread = getline(&buffer, &bufsize, stdin);
                if (nread == -1)
                {
                        printf("\n");
                        break;
                }
                command = strtok(buffer, " \n");
                args[0] = command;
                args[1] = strtok(NULL, " \n");
                args[2] = strtok(NULL, " \n");
                args[3] = NULL;

                if (strcmp(args[0], "exit") == 0) {
                    free(buffer);
                    exit(EXIT_SUCCESS);
                }

                pid_t pid = fork();
                if (pid == -1)
                {
                        perror("Error forking");
                        exit(EXIT_FAILURE);
                }
                else if (pid == 0)
                {
                        if (execve(args[0], args, NULL) == -1)
                        {
                                char *path = getenv("PATH");
                                char *token = strtok(path, ":");
                                while (token != NULL)
                                {
                                        char cmd_path[strlen(token) + strlen(args[0]) + 2];
                                        sprintf(cmd_path, "%s/%s", token, args[0]);

                                        if (execve(cmd_path, args, NULL) != -1)
                                        {
                                                break;
                                        }

                                        token = strtok(NULL, ":");
                                }

                                if (token == NULL)
                                {
                                        fprintf(stderr, "%s: command not found\n", args[0]);
                                        exit(EXIT_FAILURE);
                                }
                        }

                        exit(EXIT_SUCCESS);
                }
                else
                {
                        wait(&status);
                }
        }

        free(buffer);

        return (0);
}
