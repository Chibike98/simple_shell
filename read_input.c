i#include "simple_shell.h"

/**
 *read_input - function to read user input on the command line
 *@user_input: Command entered by the user
 *
 * Return: Nothing.
 */

void read_input(char *user_input)
{
	ssize_t bytes_read;

	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, "$ ", 3);
	}
	bytes_read = read(STDIN_FILENO, user_input, MAX_USER_INPUT_LENGTH);

	if (bytes_read == -1)
	{
		perror("read");
		exit(EXIT_FAILURE);
	}
	else if (bytes_read == 0)
	{
		exit(EXIT_SUCCESS);
	}
	user_input[bytes_read - 1] = '\0';
}
