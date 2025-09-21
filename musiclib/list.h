#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "err.h"

#ifndef LIST_H
#define LIST_H

struct node {
    char name[100]; 
    char artist[100]; 
    struct node *next;
};
struct lists{
    struct node* song;
    struct lists* next;
    char pname[100]; 
};
void printsong(struct node* t);
struct node* makesong(char* song, char* singer, struct node* n);
int compare_artist(struct node* one, struct node* two);
int compare_song(struct node* one, struct node* two);
struct node* insert_in_order(struct node* new, struct node* list);
void print_list(struct node* );
struct node* insert_front(struct node* t, char* song, char* artist);
struct node* find_song_by_artist(char* artist, struct node* t);
struct node* find_song(char* singa, char*song, struct node* t);
struct node* rand_song(struct node* t);
struct node * free_list(struct node *);
struct node * remove_node_by_index(struct node *front, int index);

#endif