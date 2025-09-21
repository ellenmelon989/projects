#include "list.h"
#include "lib.h"
#include "connect.h"
#include "audio.h"
#include "playlist.h"
#include "err.h"
#include <sys/shm.h>
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/sem.h>
#define key 111111
#define key1 111112
#define semkey 101010
struct queue* songQueue;

static void sighandler(int signo) {
    if (signo == SIGINT){
        // ctrl c
        printf("\n %d exiting music player\n", getpid());
        exit(0);
    }
}

struct lists* subserver_logic(int client_socket, struct lists** lib, int i, int count) {
    char input[BUFFER_SIZE];
    read(client_socket, input, sizeof(input)); 

    if (i == 0) {
        char* song = strtok(input, ",");
        char* artist = strtok(NULL, ",");
        char* playlistname = strtok(NULL, "\n");
        if (*artist==' '){
            for (int k = 1; k<strlen(artist); k++){
                *(artist+k-1)=*(artist+k);
            }
        }
        *(artist+strlen(artist)-1)='\0';
        if (*playlistname==' '){
            for (int k = 1; k<strlen(playlistname); k++){
                *(playlistname+k-1)=*(playlistname+k);
            }
        }
        *(playlistname+strlen(playlistname)-1)='\0';
        printf("adding %s by %s to -%s-\n", song, artist, playlistname);
        addSong2Playlistsc(makesong(song, artist, NULL), playlistname, *lib);
        printf("song added: %s, %s\n", song, artist);
        printPlaylist(playlistname, lib);
    } 
    else if(i==1){//view
        char* playlistname = strtok(input, "\n");
        printf("%s\n", playlistname);
        struct lists* temp = findPlaylist(playlistname, *lib);
        if (temp != NULL){
            printf("%s\n", temp->pname);
            printPlaylist(playlistname, lib);
        }
        else printf("doesn't exist!\n");
    }
    else if (i==2){//delete
        char* pOrS = strtok(input, "\n");
        char* playlistname = strtok(NULL, "\n");
        struct lists* temp = findPlaylist(playlistname, *lib); 
        if(strcmp(pOrS, "playlist")==0){
            if (temp != NULL && temp->song != NULL){
                printf("temp song %s\n", temp->song->name);
                deletePlaylistsc(playlistname, *lib);
                count--;//if playlist
            }
            else if(temp->song == NULL){
                printf("no songs in this playlist\n");
            }
            else {
                printf("playlist not found\n");
            }
        }
        else if (strcmp(pOrS, "song")==0){
            char* song = strtok(NULL, "\n");
            char* artist = strtok(NULL, "\n");
            printf("deleting song %s by artist %s from playlist %s\n", song, artist, playlistname);
            if (temp!= NULL){
                struct node* t = find_song(artist, song, temp->song);
                if (t != NULL){
                    deletesong(lib, playlistname, song, artist);
                    printf("new:\n");
                    printPlaylist(playlistname, lib);
                }
                else {
                    printf("song not found\n");
                }
            }        
            else {
                printf("doesn't exist\n");
            }
        }
    }
    else if (i == 3) {
        printf("asking for playlist info \n");
        char* playlistName = strtok(input, "\n");
        char* num = strtok(input+strlen(playlistName)+1, "\n");
        int songnum = atoi(num);
        char* song[songnum];
        char* artist[songnum];
        for (int k = 0; k < songnum; k++) {
            song[k] = strtok(NULL, ",");
            printf("song %s\n", song[k]);
            artist[k] = strtok(NULL, "\n");
            if (*(artist[k])==' '){
                for (int j = 1; j<strlen(artist[k]); j++){
                    *(artist[k]+j-1)=*(artist[k]+j);
                }
            }
            *(artist[k]+strlen(artist[k])-1)='\0';
            printf("artist %s\n", artist[k]);
        }
        if (count==0){
            *lib = createPlaylist(playlistName, makesong(song[0], artist[0], NULL), NULL);
        }
        else *lib = insertplaylist(createPlaylist(playlistName, makesong(song[0], artist[0], NULL), NULL), *lib);
        for (int k = 1; k<songnum; k++){
            addSong2Playlistsc(makesong(song[k], artist[k], NULL), playlistName, *lib);
        }
        printf("name of playlist: %s\n", (*lib)->pname);
        printPlaylist(playlistName, lib);
    }
    else if (i==4){//view lib
        int stdoutcopy = dup(STDOUT_FILENO);//only does all this after client exits
        int temp = open("tempfile", O_RDWR | O_CREAT | O_TRUNC, 0777);
        dup2(temp, STDOUT_FILENO);
        printallplaylist(lib);
        char contents[2*BUFFER_SIZE];
        read(temp, contents, sizeof(contents));
        dup2(stdoutcopy, STDOUT_FILENO);
        printf("%s\n", contents);
        write(client_socket, contents, sizeof(contents));
    }
    else {
        err(errno, "invalid command \n");
    }
    // write(client_socket, input, sizeof(input));
    return *lib;
}

int main(int argc, char* argv[]) { 
    signal(SIGINT, sighandler);
    signal(SIGQUIT, sighandler);

    int listen_socket = server_setup();

    struct node** library = makelib();
    add_song(makesong("505", "arctic monkeys", NULL), library);
    add_song(makesong("agora hills", "doja cat", NULL), library);
    add_song(makesong("awkward", "sza", NULL), library);
    add_song(makesong("delicate", "taylor swift", NULL), library);
    add_song(makesong("die for you", "the weeknd", NULL), library);
    add_song(makesong("maniac", "conan gray", NULL), library);
    add_song(makesong("miracle aligner", "the last shadow puppets", NULL), library);
    add_song(makesong("obsessed", "mariah carey", NULL), library);
    add_song(makesong("sugar", "maroon 5", NULL), library);
    add_song(makesong("this side of paradise", "coyote theory", NULL), library);

    int pcount = 0;
    struct lists** LSp;
    LSp = calloc(50, sizeof(struct lists*));

    songQueue = createQueue();

    while (1) {
        printf("\nwaiting for client\n\n");
        int client_socket = server_tcp_handshake(listen_socket);
        
        // printf("\nKEYBOARD COMMANDS: 'ctrl+c' to exit, 'ctrl+q' to play, 'ctrl+z' to pause, 'ctrl+s' to rewind, 'ctrl+\\' to skip\n \n");
        printf("press 'm' to make a playlist, 'vplaylist' to view a specific playlist, 'vlib' to view library, 'a' to add a song, 'd' to delete song or playlist\n \n");
        printf("type 'play' to play a song, 'q' to add a song to the queue', 'v' to view the queue', or 'c' to clear the queue\n \n");
        char in[32];
        read(client_socket, in, sizeof(in));
        if (in[strlen(in) - 1] == '\n') {
            in[strlen(in) - 1] = '\0';
        }
        if (strcmp(in, "a") == 0) {
            printf("asking for song info to add \n");
            *LSp = subserver_logic(client_socket, LSp, 0, pcount);
        }
        if (strcmp(in, "vplaylist")==0){
            printf("printing playlist ");
            *LSp = subserver_logic(client_socket, LSp, 1, pcount);
        }
        if (strcmp(in, "d")==0){
            *LSp = subserver_logic(client_socket, LSp, 2, pcount);
        }
        if (strcmp(in, "m")==0){
            *LSp = subserver_logic(client_socket, LSp, 3, pcount);
            pcount++;
        }
        if (strcmp(in, "vlib")==0){
            print_lib(library);
        }
        if (strcmp(in, "play") == 0) {
            char songName[50];
            read(client_socket, songName, sizeof(songName));
            play(songName);
        }
        if (strcmp(in, "q") == 0) {
            char songName[50];
            read(client_socket, songName, sizeof(songName));
            enqueue(songQueue, songName);
            printf("song '%s' added to queue! \n", songName);
        }
        if (strcmp(in, "v") == 0) {
            displayQueue(songQueue);
        }
        if (strcmp(in, "p") == 0) {
            playQueue(songQueue);
        }
        if (strcmp(in, "c") == 0) {
            clearQueue(songQueue);
        }
        close(client_socket);
    }
}
