#include "queue.h"
#include "queries.h"



int isempty(queuestruct* queries){
    if (queries->front == NULL && queries->end == NULL)
    {
        return 1;
    }
    else{
        return 0;
    }
}
void enqueue(queuestruct* queries, query *data, int id){
   
    if (queries->front == NULL && queries->end == NULL){
    node* a = malloc(sizeof(node));
        a->query = data;
        a->queryid = id;
        a->next = queries->front;
        queries->front = a; 
        queries->end = a;   
    }
    else{
        node* a = malloc(sizeof(node));
        a->query = data;
        a->queryid = id;
        a->next = queries->front;
        queries->front = a;
    } 
}
void dequeue(struct queuestruct* queries){
    if (isempty(queries) == 1)
    {
        return;
    }
    
    node* a = queries->front;
    if (a == queries->end){
        free (a);
        queries->front = NULL;
        queries->end = NULL;
    return;
    }
    while (a->next != queries->end){
        a = a->next;
    }
    free(queries->end->query);
    free(queries->end);
    queries->end = a;
    queries->end->next = NULL;
}
void printqueue( queuestruct* queries){
    if (isempty(queries)==1)
    {
    printf("queue empty cant print\n");
    return;        
    }
    node* a = queries->front;
    while (a!=NULL)
    {   printf("Queryid: %d\n",a->queryid);
        a = a->next;
    }
}

int sort_isempty(sort_queuestruct* sortstruct){
    if (sortstruct->front == NULL && sortstruct->end == NULL)
    {
        return 1;
    }
    else{
        return 0;
    }
}
void sort_enqueue(sort_queuestruct* sortstruct, sort_node data){
   
    if (sortstruct->front == NULL && sortstruct->end == NULL){
        data.next = sortstruct->front;
        sortstruct->front = &data; 
        sortstruct->end = &data;   
    }
    else{
        data.next = sortstruct->front;
        sortstruct->front = &data; 
    } 
}
void sort_dequeue(struct sort_queuestruct* sortstruct){
    if (sort_isempty(sortstruct) == 1)
    {
        return;
    }
    
    sort_node* a = sortstruct->front;
    if (a == sortstruct->end){
        free (a);
        sortstruct->front = NULL;
        sortstruct->end = NULL;
    return;
    }
    while (a->next != sortstruct->end){
        a = a->next;
    }
    free(sortstruct->end);
    sortstruct->end = a;
    sortstruct->end->next = NULL;
}
void sort_printqueue( sort_queuestruct* sortstruct){
    if (sort_isempty(sortstruct)==1)
    {
    printf("queue empty cant print\n");
    return;        
    }
    sort_node* a = sortstruct->front;
    while (a!=NULL)
    {   printf("Hist pos: %d\n",a->hist_pos);
        a = a->next;
    }
}
/*void* QueryJob(){
    //take query
    query* q = malloc(sizeof(query));
    q->name = malloc(sizeof(char)*BUFFER);
    while(1){
        pthread_mutex_lock(&dequeue_mutex);
        if (queries_queue.front == NULL && queries_queue.end == NULL){
        pthread_mutex_unlock(&dequeue_mutex);
            break;
        }
        //take query and free the node from the queue
        strcpy(q->name, queries_queue.end->query->name);
        q->id =  queries_queue.end->query->id;

        dequeue(&queries_queue);
        printf("removing querry %s from the queue\n",q->name);
        pthread_mutex_unlock(&dequeue_mutex);

        sleep(rand()%10);
        results[q->id] = rand()%25;
    }

    
    /*
    edw ektelesi tou query me orisma to q
    void init_unsorted_tables (unsorted_tables *unsorted_tables, database *database, query *queries, int q);
    void init_sorted_tables (sorted_tables *sorted_tables, uint64_t size_1, uint64_t size_2);
    sort (unsorted_record *unsorted_table, sorted_record *sorted_table, int position, int records, 7) {
    
    free(q);
    printf("peace out\n");
    pthread_exit(NULL);
    return NULL;
}
int main(int argc, const char * argv[]) {

    queries_queue.front=NULL;
    queries_queue.end=NULL;
    query buffquery;
    buffquery.name = malloc(sizeof(BUFFER));
    time_t t;
    srand((unsigned)time(&t));

    pthread_mutex_init(&dequeue_mutex,NULL);
    pthread_cond_init(&dequeue_cond, NULL);

    strcpy(buffquery.name,"q0");
    buffquery.id = 0;
    enqueue(&queries_queue,&buffquery);
    strcpy(buffquery.name,"q1");
    buffquery.id = 1;
    enqueue(&queries_queue,&buffquery);
    strcpy(buffquery.name,"q2");
    buffquery.id = 2;
    enqueue(&queries_queue,&buffquery);
    strcpy(buffquery.name,"q3");
    buffquery.id = 3;
    enqueue(&queries_queue,&buffquery);
    strcpy(buffquery.name,"q4");
    buffquery.id = 4;
    enqueue(&queries_queue,&buffquery);
    printqueue(&queries_queue);
    printf("\n");


    int i=0;
    for(i=0; i<NUMOF_QUERY_THREADS; i++){
        pthread_create(&threadPool[i], NULL, QueryJob, NULL);
    }

    for(i=0; i<NUMOF_QUERY_THREADS; i++){
        printf("waiting for %d querries to finish.\n",NUMOF_QUERY_THREADS-i);
        pthread_join(threadPool[i], NULL);
    }
    printqueue(&queries_queue);

    for (i = 0; i < NUMOF_QUERIES; i++)
    {
        printf("Cell %d has value %d\n",i,results[i]);
    }
    

    
    
    }
    */
    