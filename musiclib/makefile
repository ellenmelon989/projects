compile: lib.o list.o err.o playlist.o audio.o
runme: main.o lib.o list.o err.o audio.o playlist.o
	@gcc -o runme lib.o list.o err.o audio.o playlist.o main.o
main.o: main.c lib.h list.h err.h audio.h playlist.h
	@gcc -c -o main.o main.c
run: runme
	@./runme
_server: server.o connect.o lib.o list.o err.o audio.o playlist.o
	@gcc -o server server.o connect.o lib.o list.o err.o audio.o playlist.o
_client: client.o connect.o err.o
	@gcc -o client client.o connect.o err.o 
server: _server	
	@./server
client: _client
	@./client 
audio.o: audio.c err.h
	@gcc -c audio.c -I/SDL_mixer-main/include/SDL3_mixer -I/SDL/include -L/SDL_mixer-main/lib -lSDL3_mixer -lSDL3
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

# SDL_DIR = SDL
# SDL_MIXER_DIR = SDL_mixer-main
# SDL_BUILD = $(SDL_DIR)/build
# SDL_MIXER_BUILD = $(SDL_MIXER_DIR)/build
# CFLAGS = -I/SDL_mixer-main/include/SDL3_mixer -I/SDL/include
# LDFLAGS = -L/SDL_mixer-main/lib -lSDL3_mixer -lSDL3

# OBJS = lib.o list.o err.o playlist.o audio.o
# MAIN_OBJS = main.o $(OBJS)
# SERVER_OBJS = server.o connect.o $(OBJS)
# CLIENT_OBJS = client.o connect.o err.o

# sdl:
# 	@if [ ! -d "$(SDL_BUILD)" ]; then \
# 		echo "=== Building SDL3 ==="; \
# 		mkdir -p $(SDL_BUILD); \
# 		cd $(SDL_BUILD) && cmake .. && make -j4; \
# 	fi

# # Build SDL_mixer from source
# sdl_mixer: sdl
# 	@if [ ! -d "$(SDL_MIXER_BUILD)" ]; then \
# 		echo "=== Building SDL_mixer ==="; \
# 		mkdir -p $(SDL_MIXER_BUILD); \
# 		cd $(SDL_MIXER_BUILD) && cmake .. -DSDL3_DIR=$(abspath $(SDL_BUILD)) && make -j4; \
# 	fi

# compile: $(OBJS) 

# runme: $(MAIN_OBJS)
# 	@gcc -o $@ $^ $(LDFLAGS)

# _server: $(SERVER_OBJS)
# 	@gcc -o $@ $^ $(LDFLAGS)

# _client: $(CLIENT_OBJS)
# 	@gcc -o $@ $^ $(LDFLAGS)

# main.o: main.c lib.h list.h err.h audio.h playlist.h
# audio.o: audio.c err.h
# 	@gcc -c audio.c $(CFLAGS) $(LDFLAGS)
# connect.o: connect.c err.h 
# 	@gcc -c connect.c
# server.o: server.c err.h lib.h list.h
# 	@gcc -c server.c 
# client.o: client.c err.h list.h lib.h
# 	@gcc -c client.c 
# lib.o: lib.c list.h err.h
# 	@gcc -c lib.c list.c
# list.o: list.c err.h
# 	@gcc -c list.c 
# err.o: err.c err.h
# 	@gcc -c err.c 
# playlist.o: playlist.c playlist.h
# 	@gcc -c playlist.c

# run: runme
# 	@./runme

# server: _server
# 	@./server

# client: _client
# 	@./client

# clean:
# 	@rm -f *.o runme server client *.h.gch tempfile
