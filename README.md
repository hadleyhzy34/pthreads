---
layout: post
title: Threas&Concurrency
key: 20201027
tags:
  - OS
  - Linux
  - Ubuntu
  - Threas
  - Concurrency
---

## Compiling Pthreads
* `#include <pthread.h>`
```bash
gcc -o main main.c -lpthread
gcc -o main main.c -pthread

cc -o thread -pthread thread_creation.c
```
`-o` outfile


## pthread creation
```c
int pthread_create(pthread_t * thread,
					const pthread_attr_t * attr,
					void *(*start_routine)(void *),
					void *arg);
```

* thread - returns the thread id
* attr - Set to NULL if default thread attributes are used.
* void * (\*start_routine) - pointer to the functions to be threaded
* arg - pointer to argument of function. To pass multiple arguments, send a pointer to a structure.

It's worth being noted that pthread_create function starts creating a new thread which runs function of start_routine, this instruction is not finished when function returns, it is finished when the thread is created and function starts running.
{:.warning}

Data race or race condition:
```c
pthread_t threads[NUM_THREADS];
	
	for (int i = 0; i<NUM_THREADS ; i++)
	{
		pthread_create(&threads[i],NULL,threadFunc,&i);

	}
```

since `i` is defined in main->it's globally visible variable. When it changes in one thread, all other threads see new value! This situation is called a data race or a race condition, it occurs when one thread tries to read a value where the other thread tries to modify it.

Solution to this problem:
create local storage variables that are not shared among other threads.
```c
int lNum[NUM_THREADS];
pthread_t threads[NUM_THREADS];
	
	for (int i = 0; i<NUM_THREADS ; i++)
	{
		lNum[i]=i;
		pthread_create(&threads[i],NULL,threadFunc,&lNum[i]);

	}
```

## Pthread Mutexes
Mutexes are used to prevent data inconsistencies due to race conditions as we discussed above. A race condition often occurs when two or more threads need to perform operations on the same memory area, but the results of computations depends on the order in which these operations are performed. Mutexes are used for serializing shared resources. Anytime a global resource is accessed by more than one thread the resource should have a Mutex associated with it. Once can apply a mutex to protect a segment of memory("critical region") from toher threads. Mutexes can be applied only to threads in a single process and do not work between processes as do semaphores.


### Expresssions
```c
//without mutex
int counter=0;

//function c
void functionC(){
	counter++;
}

//with mutex
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int counter=0;

void functionC(){
	pthread_mutex_lock( &mutex1 );
	counter++;
	pthread_mutext_unlock( &mutex1 );
}
```

Output difference:
```bash
hadley@hadley-MacBookPro:~/Developments/pthreads/pthread_mutex$ ./mutex
counter valus is: 1
counter valus is: 2
counter valus is: 5
counter valus is: 4
counter valus is: 3
counter valus is: 6
counter valus is: 7
counter valus is: 8
counter valus is: 9
counter valus is: 10
hadley@hadley-MacBookPro:~/Developments/pthreads/pthread_mutex$ cc -o mutex -pthread mutex.c 
hadley@hadley-MacBookPro:~/Developments/pthreads/pthread_mutex$ ./mutex
counter valus is: 1
counter valus is: 2
counter valus is: 3
counter valus is: 4
counter valus is: 5
counter valus is: 6
counter valus is: 7
counter valus is: 8
counter valus is: 9
counter valus is: 10
```

When a mutex lock is attempted against a mutex which is held by another thread, the thread is blocked until the mutex is unlocked. When a thread terminates, the mutex does not unless explicitly unlocked. Nothing happens by default.


### Mechanisms:  
* Pthread mutex type:
`pthread_mutex_t aMutex;`

* Lock(mutex)
Lock(mutext){}->:
```c
//explicit lock
int pthread_mutext_lock(pthread_mutex_t *mutext);

//explicit unlock
int pthread_mutext_unlock(pthread_mutext_t *mutext);
```

### Other operations
* initialize mutex


* trylock, destroy

1. shared data should always be accessed through a single mutex 
2. mutex scope must be visible to all, global variable  
3. for all threads, lock mutexes in order
4. always unlock a mutex


## Joins
A join is performed when one wants to wait for a thread to finish. Instructions that should be executed after join statement could be excuted only after thread with join statement finished, including main exit. A thread calling routine may launch multiple threads then wait for them to finish to get the results. One wait for the completion of the threads with a join.


## Pthread Condition Variables
### Mechnisms:
* Condition

* Wait

* Signal

* Broadcast

### Other Condition variable operations
int pthread_cond_init(pthread_cond_t \* cond,
					const pthread_condattr)


1. do not forget to notify waiting threads
2. whe






## Reference







