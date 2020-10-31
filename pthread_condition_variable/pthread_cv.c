#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 10

pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t condition_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition_cond = PTHREAD_COND_INITIALIZER;

int counter=0;
#define COUNT_DONE 20
#define COUNT_HALT1 5
#define COUNT_HALT2 15

void *function1(){
	while(1){
		printf("counter begin from function1 is: %d\n", counter);

		pthread_mutex_lock(&condition_mutex);
		printf("counter after condition is locked from function1 is: %d\n", counter);
		while( counter >= COUNT_HALT1 && counter <= COUNT_HALT2 )
		{
			printf("counter condition from function1 is: %d\n", counter);
			pthread_cond_wait( &condition_cond, &condition_mutex );
		}
		pthread_mutex_unlock(&condition_mutex);

		pthread_mutex_lock( &count_mutex );
		counter++;
		printf("counter value from function1 is: %d\n", counter);
		pthread_mutex_unlock( &count_mutex );

		printf("counter unlocked from function1 is: %d\n", counter);

		if(counter >= COUNT_DONE) return 0;
	}
}

void *function2(){
	while(1){
		printf("counter begin from function2 is: %d\n", counter);

		pthread_mutex_lock(&condition_mutex);
		printf("counter after condition is locked from function2 is: %d\n", counter);
		if( counter < COUNT_HALT1 || counter > COUNT_HALT2 )
		{
			printf("counter condition from function2 is: %d\n", counter);
			pthread_cond_signal( &condition_cond );
		}
		pthread_mutex_unlock(&condition_mutex);

		pthread_mutex_lock( &count_mutex );
		counter++;
		printf("counter value from function2 is: %d\n", counter);
		pthread_mutex_unlock( &count_mutex );

		printf("counter unlocked from function2 is: %d\n", counter);

		if(counter >= COUNT_DONE) return 0;
	}
}


int main(int argc, char const *argv[])
{


	// pthread_t thread_id[NUM_THREADS];

	pthread_t thread1;
	pthread_t thread2;

	pthread_create(&thread1, NULL, &function1, NULL);
	pthread_create(&thread2, NULL, &function2, NULL);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	return 0;
}