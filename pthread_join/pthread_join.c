#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 10

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int counter=0;

void *functionC(){
	pthread_mutex_lock( &mutex1 );
	counter++;
	printf("counter valus is: %d\n", counter);
	pthread_mutex_unlock( &mutex1 );
}

int main(int argc, char const *argv[])
{


	pthread_t thread_id[NUM_THREADS];

	//create independent threads each of which will execute functionc
	for(int i=0;i<NUM_THREADS;i++){
		pthread_create(&thread_id[i], NULL, &functionC, NULL);
	}

	for(int i=0;i<NUM_THREADS;i++){
		pthread_join(thread_id[i], NULL);
	}


	// now that all threads are complete, we can print the final result.
	// try comment pthread_join statement above and check if printf result order sequece
	// related to functionC 
	printf("final counter value: %d\n", counter);
	return 0;
}