#include <pthread.h>
#include <stdio.h>
#define NUM_THREADS 5

void *hello(void *arg){
	printf("hello thread\n");
	return 0;
}

int main(int argc, char const *argv[])
{
	pthread_t threads[NUM_THREADS];
	
	for (int i = 0; i<NUM_THREADS ; i++)
	{
		/* code */
		pthread_create(&threads[i],NULL,hello,NULL);

	}

	for(int i=0;i<NUM_THREADS;i++){
		pthread_join(threads[i],NULL);
	}
	return 0;
}