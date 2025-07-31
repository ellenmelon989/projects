#ifndef SHELL_H
#define SHELL_H

void parse(char* line, char** argArray);
// parses the input line into an array of arguments
// char* line: the input line to be parsed 
// char** argArray: an array of strings that stores the parsed arguments; last element set to NULL
// returns void 

void exitCom();
//exits the shell and returns to normal terminal
//returns void

void changeDir(char* input);
// changes the current working directory using chDir
// char* input: the target directory path; if NULL, change to parent directory ("..")
// returns void

#endif