#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "execute.h"

#define MAX_INPUT 1024
#define MAX_ARGS 64

void parse_input(char *input, char **args, int *background)
{
    *background = 0;
    char *token = strtok(input, " \n");

    int index = 0;

    while (token != NULL) {
        if (strcmp(token, "&") == 0) {
            *background = 1;
        } else {
            args[index++] = token;
        }
        token = strtok(NULL, " \n");
    }

    args[index] = NULL;
}

int main()
{
    char input[MAX_INPUT];
    char *args[MAX_ARGS];
    int background;

    while (1) {
        // shell prompt
        printf("mysh> ");
        fflush(stdout);

        if (!fgets(input, sizeof(input), stdin)) {
            break;
        }

        parse_input(input, args, &background);

        if (args[0] == NULL) {
            continue;  // Empty input
        }

        // built-in exit
        if (strcmp(args[0], "exit") == 0) {
            break;
        }

        // built-in cd
        if (strcmp(args[0], "cd") == 0) {
            if (args[1] == NULL) {
                fprintf(stderr, "cd: missing directory\n");
            } else if (chdir(args[1]) != 0) {
                perror("cd failed");
            }
            continue;
        }

        execute_command(args, background);
    }

    return 0;
}
