compile shell.out: main.o shell.o pipes.o redirect.o err.o 
	@gcc -o shell.out main.o shell.o pipes.o redirect.o err.o 
run: shell.out
	@./shell.out
main.o: main.c shell.h pipes.h redirect.h err.h 
	@gcc -c main.c 
shell.o: shell.c
	@gcc -c shell.c
redirect.o: redirect.c
	@gcc -c redirect.c
pipes.o: pipes.c 
	@gcc -c pipes.c
err.o: err.c 
	@gcc -c err.c
clean:
	@rm -f *.o
	@rm -f *.out
	@rm -f tempfile
	@rm -f tempfilehello
	