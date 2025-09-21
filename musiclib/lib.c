#include "lib.h"

struct node** makelib(){
    struct node** library = calloc(sizeof(struct node), 27);
    return library;
}
void add_song(struct node* t, struct node** lib){
    int i = (t->artist)[0] - 97;
    if (i<0 || i>26){
        i = 26;
    }
    *(lib+i) = insert_in_order(t, *(lib+i));
}
void print_lib(struct node** lib){
    char a = 'a';
    while (a < 'a' + 26){
        printf("songs by artist starting with %c:\n", a);
        if(*(lib+a-97) != NULL){
            print_list(*(lib+a-97));
            printf("\n");
        }
        a++;
    }
    if (a == 'a' + 26) {
        printf("songs by artist starting with symbols:\n");
        if (*(lib + a - 97) != NULL) {
            print_list(*(lib + a - 97));
            printf("\n");
        }
    }
}
struct node* search_song(char* singa, char* song, struct node** lib){
    struct node* l = search_artist(singa, lib);
    struct node* forcmp = makesong(song, singa, NULL);
    while (l->next != NULL){
        if (compare_song(l, forcmp)==-1){
            l = l->next;
        }
        if (compare_song(l, forcmp)==0){
            return l;
        }
        if (compare_song(l, forcmp) == 1){
            return NULL;
        }
    }
    return NULL;
}
struct node* search_artist(char* singa, struct node** lib){
    int i = singa[0] - 97;
    if (i<0 || i>26){
        i = 26;
    }
    struct node* temp = *(lib+i);
    struct node* forcmp = makesong("song", singa, NULL);
    while (temp->next != NULL) {
        if (compare_artist(temp, forcmp)==-1){
            temp = temp->next;
        }
        if (compare_artist(temp, forcmp)==0){
            return temp;
        }
        if (compare_artist(temp, forcmp) == 1){
            return NULL;
        }
    }
    return NULL;
}
void print_letter(struct node** lib, char letter){
    struct node* l = *(lib+letter-97);
    printf("list for %c: \n", letter);
    print_list(l);
}
void print_artist(struct node** lib, char* singa){
    printf("songs by %s:\n", singa);
    struct node* l = search_artist(singa, lib);
    if (l == NULL){
        printf("no songs \n");
    }
    int i = 0;
    while (l != NULL){
        printf("[%d] ", i);
        i++;
        printsong(l);
        l = l -> next;
    }
}
void shuffle(struct node** lib, int n){
    printf("shuffling %d songs: \n", n);
    for (int i = 0; i < n ; i++){
        int c = rand() % 26;
        struct node* temp = *(lib+c);
        int len = 0;
        if (temp == NULL){
            i--;
        }
        else {
            struct node * other = temp;
            while (other != NULL){
                len++;
                other = other->next;
            }
            int r = rand() % len-1;
            for(int j = 0; j<r; j++){
                temp = temp->next;
            }
            printsong((temp));
        }
    }
}
void clear_lib(struct node** lib){
   for (int i = 0; i < 27; i++) {
        struct node* curr = *(lib+i);
        while (curr != NULL) {
            struct node* temp = curr;
            curr = curr-> next;
            free(temp);
        }
        *(lib+i) = NULL; 
   }
}
struct node* delete_song(struct node** lib, char* name, char* singa){
    int i = singa[0] - 97;
    if (i<0 || i>26){
        i = 26;
    }
    struct node* l = *(lib+i);
    struct node* prev = l;
    struct node* tocmp = makesong(name, singa, NULL);
    while (l != NULL){
        if(compare_artist(l, tocmp)==0){
            if (compare_song(l, tocmp)==0){
                struct node* tofree = l;
                free(tofree);
                l = l ->next;
                prev -> next = l;
            }
            else{
                prev = l;
                l = l -> next;
            }
        }
        else{
            prev = l;
            l = l -> next;
        }
    }
    return (*(lib+i));
}