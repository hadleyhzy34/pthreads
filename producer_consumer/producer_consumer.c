#include <pthread.h>
#include <stdio.h>
#define NUM_THREADS 5

#define BUF_SIZE 3  //size of shared buffer

int buffer[BUF_SIZE];  //shared buffer
int add = 0;			//place to add next element
int rem = 0;			//place to remove next element
int num = 0;			//number elements in buffer

pthread_mutext_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c_cons = PTHREAD_COND_INITIALIZER;
pthread_cont_t c_prod = PTHREAD_COND_INITIALIZER;

void *producer(void *param);
void *consumer(void *param);


int main(int argc, char const *argv[])
{	
	//one thread for producer, one thread for consumer
	pthread_t thread1,thread2;

	int i;


	int lNum[NUM_THREADS];
	pthread_t threads[NUM_THREADS];
	
	for (int i = 0; i<NUM_THREADS ; i++)
	{
		lNum[i]=i;
		pthread_create(&threads[i],NULL,threadFunc,&lNum[i]);

	}

	for(int i=0;i<NUM_THREADS;i++){
		pthread_join(threads[i],NULL);
	}
	return 0;
}