compile: lib.o list.o err.o playlist.o 
runme: main.o lib.o list.o err.o audio.o playlist.o
	@gcc -o runme lib.o list.o err.o audio.o playlist.o main.o
main.o: main.c lib.h list.h err.h audio.h playlist.h
	@gcc -c -o main.o main.c
run: runme
	@./runme
_server: server.o connect.o lib.o list.o err.o audio.o playlist.o
	gcc -o server server.o connect.o lib.o list.o err.o audio.o playlist.o
_client: client.o connect.o err.o
	@gcc -o client client.o connect.o err.o 
server: _server	
	@./server
client: _client
	@./client 
audio.o: audio.c err.h
	@gcc -c audio.c -I/SDL/include/SDL3
connect.o: connect.c err.h 
	@gcc -c connect.c
server.o: server.c err.h lib.h list.h
	@gcc -c server.c 
client.o: client.c err.h list.h lib.h
	@gcc -c client.c 
lib.o: lib.c list.h err.h
	@gcc -c lib.c list.c
list.o: list.c err.h
	@gcc -c list.c 
err.o: err.c err.h
	@gcc -c err.c 
playlist.o: playlist.c playlist.h
	@gcc -c playlist.c
clean:
	@rm -f *.o
	@rm -f runme
	@rm -f *.h.gch
	@rm -f server
	@rm -f client
	@rm -f tempfile