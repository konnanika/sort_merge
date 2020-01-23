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
    int f = 0;
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
// Print all the statistics
    while (queries[q].num_of_smjs != -1) {
        for (f=0; f<queries[q].num_of_filters; f++) {
            printf("I = ");
            printf("%" PRIu64 "\n", queries[q].predicates_filter[f].I_small);
            printf("U = ");
            printf("%" PRIu64 "\n", queries[q].predicates_filter[f].U_big);
            printf("F = ");
            printf("%" PRIu64 "\n", queries[q].predicates_filter[f].F_count);
            printf("D = ");
            printf("%" PRIu64 "\n", queries[q].predicates_filter[f].D_distinct);
        }
        for (f=0; f<queries[q].num_of_smjs; f++) {
            printf("I_a = ");
            printf("%" PRIu64 "\n", queries[q].predicates_smj[f].I_small_1);
            printf("U_a = ");
            printf("%" PRIu64 "\n", queries[q].predicates_smj[f].U_big_1);
            printf("F_a = ");
            printf("%" PRIu64 "\n", queries[q].predicates_smj[f].F_count_1);
            printf("D_a = ");
            printf("%" PRIu64 "\n", queries[q].predicates_smj[f].D_distinct_1);
            printf("I_b = ");
            printf("%" PRIu64 "\n", queries[q].predicates_smj[f].I_small_2);
            printf("U_b = ");
            printf("%" PRIu64 "\n", queries[q].predicates_smj[f].U_big_2);
            printf("F_b = ");
            printf("%" PRIu64 "\n", queries[q].predicates_smj[f].F_count_2);
            printf("D_b = ");
            printf("%" PRIu64 "\n", queries[q].predicates_smj[f].D_distinct_2);                                         
        }
        q++;
    }
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
