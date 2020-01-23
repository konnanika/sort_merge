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
	while (queries[q].num_of_smjs != -1)
	{
	enqueue(&queries_queue,&(queries[q]),q);
	q++;
	}
	results = malloc(sizeof(int)*q);
	printqueue(&queries_queue);
	
/*	for(q=0; q<5; q++) {
		if (queries[q].num_of_smjs == -1)
			return 0;
		printf("The involved tables are: \n");
		for (i=0; i<queries[q].num_of_tables; i++){
			printf("%d ", queries[q].involved_tables[i]);
		}
		printf("\nThe joins that we need to do are: \n");
		for (i=0; i<queries[q].num_of_smjs; i++){
			printf("%d", queries[q].predicates_smj[i].table_1);
			printf(".%d=", queries[q].predicates_smj[i].key_1);
			printf("%d", queries[q].predicates_smj[i].table_2);	
			printf(".%d\n", queries[q].predicates_smj[i].key_2);
		}
		printf("\nThe filters that we need to do are: \n");
		for (i=0; i<queries[q].num_of_filters; i++){
			printf("%d", queries[q].predicates_filter[i].table);
			printf(".%d", queries[q].predicates_filter[i].key);
			printf("%c", queries[q].predicates_filter[i].symbol);	
			printf("%d\n", queries[q].predicates_filter[i].number);
		}
		printf("\nThe sums that we need to do are: \n");
		for (i=0; i<queries[q].num_of_sums; i++){
			printf("%d", queries[q].result_sum[i].table);
			printf(".%d\n", queries[q].result_sum[i].key);
		}
	}*/
    for(i=0; i<NUMOF_QUERY_THREADS; i++){
        pthread_create(&threadPool[i], NULL, QueryJob, NULL);
    }

    for(i=0; i<NUMOF_QUERY_THREADS; i++){
        printf("waiting for %d querries to finish.\n",NUMOF_QUERY_THREADS-i);
        pthread_join(threadPool[i], NULL);
    }
    printqueue(&queries_queue);

    for (i = 0; i < q; i++)
    {
        printf("Cell %d has value %d\n",i,results[i]);
    }
/*// Executing the queries
	printf("Executing the queries\n");
	queries_execution(queries, database);
// Shuting down
	free_database(database, files->total_tables);
	free_queries(queries);
	free(files);*/
	return 0;
}


//		0 1|0.1=1.1|0.1		0 1 2|0.1=1.1&1.0=2.0&0.1>4&1.1>10|0.0
//		0 1 2 3 4|3.1>101010&1.1=3.5&0.1>10&1.1>5&2.0>0&3.3>5&0.1=2.3&3.3>50574&3.1<5457|1.1 3.1
//		/home/nikitas/Desktop/small/r0

//		0 1 2 3 4 5|0.0=1.1&0.0=2.2&0.0=3.3&1.1=4.4&4.0=5.0&1.1>10|0.0

