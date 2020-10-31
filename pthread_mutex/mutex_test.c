#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 10

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex3 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex4 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex5 = PTHREAD_MUTEX_INITIALIZER;
int counter=0;

void *function1(){
	pthread_mutex_lock( &mutex1 );
	counter++;
	printf("counter valus is: %d current thread is 1\n", counter);
	pthread_mutex_unlock( &mutex1 );
	return 0;
}

void *function2(){
	pthread_mutex_lock( &mutex2 );
	counter++;
	printf("counter valus is: %d current thread is 2\n", counter);
	pthread_mutex_unlock( &mutex2 );
	return 0;
}

void *function3(){
	pthread_mutex_lock( &mutex3 );
	counter++;
	printf("counter valus is: %d current thread is 3\n", counter);
	pthread_mutex_unlock( &mutex3 );
	return 0;
}

void *function4(){
	pthread_mutex_lock( &mutex4 );
	counter++;
	printf("counter valus is: %d current thread is 4\n", counter);
	pthread_mutex_unlock( &mutex4 );
	return 0;
}

void *function5(){
	pthread_mutex_lock( &mutex5 );
	counter++;
	printf("counter valus is: %d current thread is 5\n", counter);
	pthread_mutex_unlock( &mutex5 );
	return 0;
}


int main(int argc, char const *argv[])
{


	// pthread_t thread_id[NUM_THREADS];

	pthread_t thread1;
	pthread_t thread2;
	pthread_t thread3;
	pthread_t thread4;
	pthread_t thread5;

	// pthread_create(&thread1, NULL, &function1, NULL);
	// pthread_create(&thread2, NULL, &function2, NULL);
	// pthread_create(&thread3, NULL, &function3, NULL);
	// pthread_create(&thread4, NULL, &function4, NULL);
	// pthread_create(&thread5, NULL, &function5, NULL);

	pthread_create(&thread1, NULL, &function1, NULL);
	pthread_create(&thread2, NULL, &function1, NULL);
	pthread_create(&thread3, NULL, &function1, NULL);
	pthread_create(&thread4, NULL, &function1, NULL);
	pthread_create(&thread5, NULL, &function1, NULL);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);
	pthread_join(thread4, NULL);
	pthread_join(thread5, NULL);


	//create independent threads each of which will execute functionc
	// for(int i=0;i<NUM_THREADS;i++){
	// 	pthread_create(&thread_id[i], NULL, &functionC, NULL);
	// }

	// for(int i=0;i<NUM_THREADS;i++){
	// 	pthread_join(thread_id[i], NULL);
	// }
	return 0;
}