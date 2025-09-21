#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "lib.h"
#include "err.h"

#ifndef PLAYLIST_H
#define PLAYLIST_H
// struct lists{
//     struct node** song;
//     char pname[100]; 
// };
struct lists* createPlaylist(char* playlistName, struct node* t, struct lists*);
struct lists* findPlaylist(char* playlistName, struct lists* );
struct lists* insertplaylist(struct lists* new, struct lists* existing);
void addSong2Playlistsc(struct node* song, char* playlistName, struct lists* playlist);
void printPlaylist(char* playlistName, struct lists** playlist);
void printallplaylist(struct lists** playlist);
struct lists* deletesong(struct lists** lib, char*, char* name, char* singa);
void deletePlaylistsc(char* playlistName, struct lists* playlist);
void printAllPlaylists(struct lists* playlists);
void addSong2Playlist(struct lists** playlist);
void deleteFromPlaylist(struct lists** playlist);
void deletePlaylist(struct lists** playlist);
void alphabetizePlaylists(char* playlistName, struct lists* playlist, struct node** library);

#endif