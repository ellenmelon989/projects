#ifndef PIPES_H
#define PIPES_H

void pipee(char* comm);
//separates the two sides of the pipe in string comm and runs the first side, outputting into a tempfile 
//we created or redirecting if the first side has < or >, then using that tempfile for the second side's command or
//redirecting if second side has < or >
//char* comm: the full command line to run, with the pipe and both sides of the pipe 
//returns void

#endif