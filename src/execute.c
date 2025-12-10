#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void execute_command(char **args, int background)
{
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        if (execvp(args[0], args) == -1) {
            perror("Command failed");
        }
        exit(1);
    }
    else if (pid > 0) {
        // Parent
        if (!background) {
            waitpid(pid, NULL, 0);
        }
    }
    else {
        perror("Fork failed");
    }
}
