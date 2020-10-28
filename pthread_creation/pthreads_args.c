#include <pthread.h>
#include <stdio.h>
#define NUM_THREADS 5

void *hello(void *arg){
	printf("hello thread\n");
	return 0;
}

void *threadFunc(void *pArg){
	int *p=(int*)pArg;
	int myNum=*p;
	printf("thread number %d\n", myNum);
	return 0;
}

int main(int argc, char const *argv[])
{
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