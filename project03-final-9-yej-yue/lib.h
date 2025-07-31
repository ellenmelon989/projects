#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifndef LIB_H
#define LIB_H
struct node** makelib();
struct node* search_song(char* singa, char* song, struct node** lib);
struct node* search_artist(char* singa, struct node** lib);
void add_song(struct node* t, struct node** lib);
void print_lib(struct node** lib);
void print_letter(struct node** lib, char letter);
void print_artist(struct node** lib, char* artist);
void shuffle(struct node** lib, int n);
void clear_lib(struct node** lib);
struct node* delete_song(struct node** lib, char* name, char* singa);
#endif