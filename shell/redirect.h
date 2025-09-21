#ifndef REDIRECT_H
#define REDIRECT_H

void redirect(char* command, char** args);
// executes commands with input/output redirection
// char* command    the command to be executed
// char** args      an array of strings with the command and its arguments
// returns void
/* 
redirect forks a new process that executes the specified command with '<' or '>'
'<' opens the specified reading file and sets it as stdin for the command
opened input redirection file is duplicated and stdin is redirected to the duplicated file
'>' opens or creates the specified writing file and sets it as stdout
opened output redirection file is duplicated and stdout is redirected to the duplicated file
corresponding command and argument elements are set to NULL
err() is called if file does not exist, cannot be found, cannot be opened or created, or if execvp fails
original stdin and stdout are restored after execution
*/

#endif