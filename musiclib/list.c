#include "list.h"

void printsong(struct node* t){
    printf("artist: %s, song: %s\n", t->artist, t->name);
}
struct node* makesong(char* song, char* singer, struct node* n){
    struct node* t = calloc(sizeof(struct node), 1);
    strcpy(t->name, song);
    strcpy(t->artist, singer);
    t->next = n;
    return t;
}
void print_list(struct node* t) {
    struct node* temp = t;
    int i = 0;
    while(temp != NULL) {
        printf("[%d] ", i);
        printsong(temp);
        i++;
        temp = temp->next;
    }
}
// void print_list(struct lists l){

// }
int compare_artist(struct node* one, struct node* two){
    if (strcmp(one->artist, two->artist) > 0){
        return 1;
    }
    else if (strcmp(one->artist, two->artist) < 0){
        return -1;
    }
    else {
        return 0;
    }
}//1 if one is later in alphabet
int compare_song(struct node* one, struct node* two){
    if (strcmp(one->name, two->name) > 0){
        return 1;
    }
    else if (strcmp(one->name, two->name) < 0){
        return -1;
    }
    else {
        return 0;
    }
}
struct node* insert_in_order(struct node* new, struct node* list){
    if (list == NULL) {
        return insert_front(NULL, new->name, new->artist);
    }
    else{
        struct node* prev = list;
        struct node* temp = list;
        while(compare_artist(temp, new)==-1){
            prev = temp;
            temp = temp -> next;
            if (temp == NULL){
                prev -> next = new;
                new -> next = NULL;
                return prev;
            }
        }//ends at i where it is start of same artists (first of artist)
        if (compare_artist(temp, new) == 0) {
            while (compare_song(temp, new)==-1){
                prev = temp;
                temp = temp -> next;
                if (temp == NULL){
                    prev -> next = new;
                    new -> next = NULL;
                    return list;
                }
            }
        }//first of same song
        new->next = temp;
        if (temp == prev){
            return new;
        }
        prev->next = new;
        //issue when putting in one that goes before the first sicne it loops the nexts 
        return list;
    }
}
struct node* insert_front(struct node* t, char* song, char* artist) {
    struct node* new = makesong(song, artist, t);
    // l->song = new;
    return new;
}
struct node* rand_song(struct node* t){
    srand(time(NULL));
    int len = 0;
    struct node* temp = t;
    while(temp != NULL){
        len++;  
        temp=temp->next;
    }
    int a = rand()%len;
    int count = 0;
    while(count < a){
        count++;
        t = t->next;
    }
    return t;
}
struct node* find_song_by_artist(char* singa, struct node* t){
    struct node* temp = t;
    while (temp != NULL){
        if (strcmp(temp->artist, singa)==0){
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}
struct node* find_song(char* singa, char*song, struct node* t) {
    struct node* temp = t;
    temp = find_song_by_artist(singa, t);
    while(temp != NULL){
        if (strcmp(temp->name, song)==0){
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}
struct node* free_list(struct node* t){
    struct node* new = t;
    while (t != NULL) {
        new = t;
        t = t->next;
        free(new);
    }
    return t;
}
struct node* remove_node_by_index(struct node *front, int index){
    struct node* new = front;
    int len = 0;
    while(new != NULL){
        len++;
        new = new->next;
    }
    int i = 0;
    new = front;
    if (index > 0 && index < len){
        while (i < index-1){
            new = new->next;
            i++;
        }
        struct node* temp = new->next;
        new->next = new->next->next;
        free(temp);
    }
    else if (index == 0){
        front = front->next;
        free(new);
    }
    return front;
}