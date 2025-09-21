[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/77as2zNO)

# Systems Project2 - MyShell

# 9-YuE-YeJ

## function headers

void parse(char* line, char** argArray);

void exitCom();

void changeDir(char* input);

void err();

void redirect(char* command, char** args);

void pipee(char* comm);

## description of features

*parse:* 
this takes in an input line and parses it into an array of arguments, using the strsep function to tokenize the input based on spaces within the input line. our parsed arguments are stored in an array with the last element set to NULL.

*exitCom:*
this function exits the program with no issues, so an exit status of 0, and prints a message stating it is exiting normally. 

*changeDir:*
this changes the current working directory using chdir. if a target directory path is provided, the current working directory changes to the target, else it will change to the parent directory (".."). our changeDir function prints a message confirming that the directory has been changed. 

*err:*
this prints out an error message in the stdout and exits with an exit status of 1.

*redirect:*
this enables input and output redirection for commands. our redirect function forks a new process, sets up file descriptors for input and output based on whether it's accounting for input '<' or output '<' respectively, and executes the specified command. error handling is included for potential file-related and execvp issues. 

*pipee:*
this mimics the pipe ability in the bash terminal, where the output of the left side of the pipe is the input of the right side of the pipe. our pipee function accounts for commands and commands with redirection.

## bugs
