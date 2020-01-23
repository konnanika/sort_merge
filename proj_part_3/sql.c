#include "sql.h"

queuestruct queries_queue;
pthread_t threadPool[NUMOF_QUERY_THREADS];
pthread_mutex_t dequeue_mutex;
pthread_cond_t dequeue_cond;
int *results;

void* QueryJob(){
    //take query
	int id;
    query* q = malloc(sizeof(query));
    while(1){
        pthread_mutex_lock(&dequeue_mutex);
        if (queries_queue.front == NULL && queries_queue.end == NULL){
        pthread_mutex_unlock(&dequeue_mutex);
            break;
        }
        //take query and free the node from the queue
        id = queries_queue.end->queryid;

        dequeue(&queries_queue);
        printf("removing querry %d from the queue\n",id);
        pthread_mutex_unlock(&dequeue_mutex);

        sleep(rand()%10);
        results[id] = rand()%25;
    }
	/*
    edw ektelesi tou query me orisma to q
    void init_unsorted_tables (unsorted_tables *unsorted_tables, database *database, query *queries, int q);
    void init_sorted_tables (sorted_tables *sorted_tables, uint64_t size_1, uint64_t size_2);
    sort (unsorted_record *unsorted_table, sorted_record *sorted_table, int position, int records, 7) {
    */ 
    printf("peace out\n");
    pthread_exit(NULL);
    return NULL;
}

int main(int argc, char **argv) {
	time_t t;
    srand((unsigned)time(&t));
//mutexes
	pthread_mutex_init(&dequeue_mutex,NULL);
    pthread_cond_init(&dequeue_cond, NULL);
// Random Variables
	int i = 0;
	int q = 0;
// Database Variables
	input *files = malloc(sizeof(input));
	database *database = malloc(sizeof(struct database));
	query *queries = malloc(MAX_NUM_OF_QUERIES * sizeof(struct query));
// Reading the input filenames
	input_menu(files);
	database->tables = malloc(files->total_tables * sizeof(struct table));
// Reading the binary files
	read_binary_files (files, database);
// Reading the queries
	queries_menu(queries);
	queries_statistics(database, queries);
	while (queries[q].num_of_smjs != -1) {
		enqueue(&queries_queue,&(queries[q]),q);
		q++;
	}
	results = malloc(sizeof(int)*q);
	printqueue(&queries_queue);
    for(i=0; i<NUMOF_QUERY_THREADS; i++) {
        pthread_create(&threadPool[i], NULL, QueryJob, NULL);
    }

    for(i=0; i<NUMOF_QUERY_THREADS; i++) {
        printf("waiting for %d querries to finish.\n",NUMOF_QUERY_THREADS-i);
        pthread_join(threadPool[i], NULL);
    }
    printqueue(&queries_queue);
    for (i = 0; i < q; i++)
        printf("Cell %d has value %d\n",i,results[i]);
/*// Executing the queries
	printf("Executing the queries\n");
	queries_execution(queries, database);
// Shuting down
	free_database(database, files->total_tables);
	free_queries(queries);
	free(files);*/
	return 0;
}
