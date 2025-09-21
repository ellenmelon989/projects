#include "audio.h"
#include "list.h"
#include "connect.h"

void play(char* songName) {
    pid_t pid = fork();

    if (pid == -1) {
        err(errno, "error forking process \n");
    } 
    else if (pid == 0) {
        chdir("./music");
        char filePath[256];
        snprintf(filePath, sizeof(filePath), "%s.mp3", songName);
        char* command[] = {"mpg123", filePath, NULL};
        execvp("mpg123", command);
        err(errno, "error executing command \n");
    }
    else {
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            err(errno, "error waiting for child process \n");
        }
    }
}

struct queue* createQueue() {
    struct queue* queue = (struct queue*)malloc(sizeof(struct queue));
    queue->front = queue->rear = NULL;
    return queue;
}

void enqueue(struct queue* queue, char* songName) {
    struct queueNode* newNode = (struct queueNode*)malloc(sizeof(struct queueNode));
    strncpy(newNode->songName, songName, sizeof(newNode->songName));
    newNode->next = NULL;

    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

void dequeue(struct queue* queue) {
    if (queue->front == NULL) {
        printf("queue is empty\n");
        return;
    }

    struct queueNode* temp = queue->front;
    queue->front = temp->next;

    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
}

void displayQueue(struct queue* queue) {
    struct queueNode* current = queue->front;
    int songCount = 1;
    while (current != NULL) {
        printf("[%d] %s \n", songCount, current->songName);
        current = current->next;
        songCount++;
    }
}

void clearQueue(struct queue* queue) {
    while (queue->front != NULL) {
        dequeue(queue);
    }
    printf("there is nothing in queue \n");
}

void playQueue(struct queue* queue) {
    while (queue->front != NULL) {
        char* songName = queue->front->songName;
        play(songName);
        dequeue(queue);
    }    
}