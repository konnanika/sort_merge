#ifndef queue_h
#define queue_h

#include "queries.h"
#include <errno.h>
#include <stdlib.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <pthread.h>



typedef struct node
{
    struct query *query;
    struct node  *next;
    int queryid;
}node;

typedef struct queuestruct{
struct node *front;
struct node *end;
}queuestruct;


void printqueue(struct queuestruct *queries);
void enqueue(struct queuestruct *queries, query* data, int id);
void dequeue(struct queuestruct *queries);
int isempty(queuestruct* queries);





#endif 
