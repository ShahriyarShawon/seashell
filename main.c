#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void print_str_array(char *arr[], size_t n)
{
	int i;

	for (i = 0; i < n; i++) {
		printf("%d) %s\n", i, arr[i]);
	}
}

int main(int argc, char *argv[])
{
	size_t BUFFER_LENGTH = 1024;
	int MAX_TOKENS = 1024;
	char *prompt = "->";
	char *user_input;
	char *executable;
	char *tokens[MAX_TOKENS];
	char *cur_tok;
	int token_counter;
	ssize_t bytes_read;
	pid_t pid;
	int wstatus;

	user_input = malloc(BUFFER_LENGTH);
	token_counter = 0;

	while (true) {
		token_counter = 0;
		printf("%s ", prompt);
		bytes_read = getline(&user_input, &BUFFER_LENGTH, stdin);
		if (bytes_read < 0) {
			printf("BREAK\n");
			break;
		}
		user_input[bytes_read-1] = '\0';
	
		executable = strtok(user_input, " ");
		tokens[token_counter++] = executable;
		while ((cur_tok = strtok(NULL, " ")) != NULL) {
			tokens[token_counter++] = cur_tok;
		}
		tokens[token_counter] = NULL;
		pid = fork();
		if (pid == 0) {
			execvp(executable, tokens);
		}
		wait(&wstatus);
		
	}

	return 0;
}
