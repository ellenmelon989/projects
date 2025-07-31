#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"
#include "redirect.h"
#include "err.h"

void redirect(char* command, char** args) {
    int input = -1; 
    int output = -1;
    int stdincopy = dup(STDIN_FILENO);
    int stdoutcopy = dup(STDOUT_FILENO);

    pid_t child = fork();
    if (child == -1) {
        err();
        close(stdincopy);
        close(stdoutcopy);
        return;
    }

    if (child == 0) {
        for (int i = 0; args[i] != NULL; i++) {
            if (strcmp(args[i], "<") == 0) {
                FILE* file = fopen(args[i + 1], "r");
                if (file == NULL) {
                    err();
                    close(stdincopy);
                    return;
                }
                input = fileno(file);
                dup2(input, STDIN_FILENO);
                args[i] = NULL;
                args[i + 1] = NULL;

                fclose(file);
            }
            else if (strcmp(args[i], ">") == 0) {
                output = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (output == -1) {
                    err();
                    close(stdoutcopy);
                    return;
                }
                dup2(output, STDOUT_FILENO);
                close(output);
                args[i] = NULL;
                args[i + 1] = NULL;
            }
        }   
        if (execvp(command, args) == -1) {
            err();
        }
    }
    else {
        int status;
        waitpid(child, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
            err();
        }   
    }
    dup2(stdincopy, STDIN_FILENO);
    dup2(stdoutcopy, STDOUT_FILENO);
}