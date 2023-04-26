#include "simple_shell.h"
/**
 * execute_input - executes the command entered by user
 * @user_input: the input supplied
 *
 * Return: Nothing.
 */

void execute_input(char *user_input)
{
	char input_copy[MAX_USER_INPUT_LENGTH];
	char *space_pos;

	strcpy(input_copy, user_input);
	space_pos = _strchr(input_copy, ' ');
	if (space_pos != NULL)
	{
		execute_command_with_args(input_copy);
	}
	else
	{
		execute_command_without_args(input_copy);
	}
}

/**
 *execute_command_with_args - executes inputs without arguments
 *@user_input: the input supplied
 *
 * Return: Nothing.
 */

void execute_command_with_args(char *user_input)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
	}
	else if (pid == 0)
	{
		char *args[MAX_ARGUMENTS + 1];
		char *full_path;
		char arg_str[MAX_USER_INPUT_LENGTH];
		int num_args = 0;
		char *token;

		strtok(user_input, " \n");
		full_path = find_command(user_input);
		args[0] = full_path;
		_strcpy(arg_str, user_input + _strlen(user_input) + 1);
		token = strtok(arg_str, " \n");
		while (token != NULL && num_args < MAX_ARGUMENTS)
		{
			args[++num_args] = token;
			token = strtok(NULL, " \n");
		}
		args[num_args + 1] = NULL;
		if (execve(args[0], args, NULL) == -1)
		{
			write(STDERR_FILENO, args[0], _strlen(args[0]));
			write(STDERR_FILENO, ": Could not execute command\n", 28);
		}
	}
	else
	{
		int status;

		waitpid(pid, &status, 0);
	}
}

/**
 *execute_command_without_args - executes inputs that have no arguments
 *@user_input: the input supplied
 *
 * Return: Nothing.
 */

void execute_command_without_args(char *user_input)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		/* Child process */
		char *args[MAX_ARGUMENTS + 1];
		char *full_path;

		full_path = find_command(user_input);
		if (full_path == NULL)
		{
			write(STDERR_FILENO, user_input, _strlen(user_input));
			write(STDERR_FILENO, ": Command not found\n", 20);
			exit(EXIT_FAILURE);
		}
		args[0] = full_path;
		args[1] = NULL;
		if (execve(args[0], args, NULL) == -1)
		{
			write(STDERR_FILENO, args[0], _strlen(args[0]));
			write(STDERR_FILENO, ": Could not execute the command\n", 28);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Parent process */
		int status;

		waitpid(pid, &status, 0);
	}
}
