#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum TokenType { PIPE, AMPERSAND, GTGT, LT, STRING, ARG, END };

struct Token {
    enum TokenType tt;
    char *literal;
};

void print_token(struct Token *t) {
	printf("TokenType: %d, Literal: %s\n", t->tt, t->literal);
}

char advance(char *input, int *pos, const int input_size) {
    if (*pos > input_size) {
        return 0;
    }
    return input[(*pos)++];
}

int tokenize(struct Token *dest, ssize_t size, char *input, int input_size) {
    int input_pos;
    int dest_pos;
    char cur_char;
    int tok_lit_size;
    char tok_lit_buffer[1024];
	int tokens_added;

    input_pos = 0;
    dest_pos = 0;
    tok_lit_size = 0;
	tokens_added = 0;

    while (true) {
        cur_char = advance(input, &input_pos, input_size);
        if (cur_char == 0) {
            break;
        }

        if (isalpha(cur_char)) {
            // ARG
            tok_lit_buffer[tok_lit_size++] = cur_char;
            while (isalnum(cur_char)) {
                cur_char = advance(input, &input_pos, input_size);
                tok_lit_buffer[tok_lit_size++] = cur_char;
            }

            struct Token t = {.tt = ARG, .literal = malloc(tok_lit_size)};
            strncpy(t.literal, tok_lit_buffer, tok_lit_size);
            tok_lit_size = 0;
            dest[dest_pos++] = t;
			tokens_added++;
        }

        if (isspace(cur_char)) {
            continue;
        }
    }
	return tokens_added;
}

int main(int argc, char *argv[]) {
    size_t BUFFER_LENGTH = 1024;
    size_t TOKENS_LENGTH = 1024;
    char *user_input;
    int token_counter;
    ssize_t bytes_read;
    struct Token tokens[TOKENS_LENGTH];

    user_input = malloc(BUFFER_LENGTH);
    token_counter = 0;

    while (true) {
        token_counter = 0;
        bytes_read = getline(&user_input, &BUFFER_LENGTH, stdin);
        if (bytes_read < 0) {
            printf("BREAK\n");
            break;
        }
        user_input[bytes_read - 1] = '\0';
        token_counter= tokenize(tokens, TOKENS_LENGTH, user_input, bytes_read);

		for (int i = 0; i < token_counter; i++) {
			print_token(&tokens[i]);
		}
		
	
    }
}
