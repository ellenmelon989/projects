#include "list.h"
#include "lib.h"
#include "err.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef AUDIO_H
#define AUDIO_H

struct queueNode {
    char songName[50];
    struct queueNode* next;
};

struct queue {
    struct queueNode* front;
    struct queueNode* rear;
};

void play(char* songName);
struct queue* createQueue();
void enqueue(struct queue* queue, char* songName);
void dequeue(struct queue* queue);
void displayQueue(struct queue* queue);
void clearQueue(struct queue* queue);
void playQueue(struct queue* queue);

#endif