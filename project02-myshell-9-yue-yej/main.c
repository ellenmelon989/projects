#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include "shell.h"
#include "pipes.h"
#include "redirect.h"
#include "err.h"

int main() {
    while (1) {
        if (feof(stdin)) {
            break;
        }

        char input[1024];
        char* argArray[64];
        char* check;
        char** carr = NULL;

        printf("command: ");
        fflush(stdout);
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }
        char* ip = input;
        // printf("%s", input);

        if (input[strlen(input) - 1] == '\n') {
            input[strlen(input) - 1] = '\0';
        }

        int i = 0;
        while ((check = strsep(&ip, ";"))!=NULL) {
            carr = (char**)realloc(carr, (i+1)*sizeof(char*));
            carr[i] = check;
            i++;
        }

        for (int j = 0; j<i; j++) {
            char* lcopy = strdup(carr[j]);
            parse(carr[j], argArray);
            if (strcmp(carr[j], "exit")==0) {
                printf("\n%s\n", lcopy);
                exitCom();
                break;
            }
            else if (strcmp(carr[j], "cd")==0) {
                printf("\n%s\n", lcopy);
                changeDir(argArray[1]);
                printf("\n");
            }
            else if (strchr(lcopy, '|') != NULL){
                printf("\n%s\n", lcopy);
                pipee(lcopy);
                printf("\n");
            }
            else if (strchr(lcopy, '<') != NULL || strchr(lcopy, '>') != NULL) {
                redirect(argArray[0], argArray);
                printf("\n");
            }
            else {
                printf("\n%s\n", lcopy);
                pid_t child = fork();
                int status;
                if(child<0) {
                    err();
                } else if (child == 0) {
                    if (execvp(carr[j], argArray)==-1) err();
                } 
                waitpid(child, &status, 0);
                printf("\n");
            }
        }
    }
    return 0;
}