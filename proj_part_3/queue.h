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
void enqueue(struct queuestruct *queries,struct query* data, int id);
void dequeue(struct queuestruct *queries);
int isempty(struct queuestruct* queries);

//sort stuff
typedef struct sort_node
{
    struct unsorted_record *unsortedtable;
    struct histogram *hist;
    struct sort_node  *next;
    int hist_pos;
}sort_node;

typedef struct sort_queuestruct{
int numofrecords;
int byte;
pthread_mutex_t *sort_dequeue_mutex;
struct sort_node *front;
struct sort_node *end;
}sort_queuestruct;

int sort_isempty(struct sort_queuestruct* sortstruct);
void sort_enqueue(struct sort_queuestruct* sortstruct, sort_node data);
void sort_dequeue(struct sort_queuestruct* sortstruct);
void sort_printqueue(struct sort_queuestruct* sortstruct);



#endif 
