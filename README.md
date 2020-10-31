# Thread Summary 

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

`pthread_create()` returns zero when the call completes successfully. Any other return value indicates that an error occurred. When any of the following conditions are detected, `pthread_create()` fails and returns the corresponding value.

`EAGAIN`  
A system limit is exceeded, such as when too many threads have been created.

`EINVAl`  
The value of attr is invalid.

`EPERM` 
The caller does not have appropriate permission to set the required scheduling parameters or scheduling policy.


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

It's worth being noted that mutex thread is locked not based on global variables, it's based on shared mutex variable mutex1 or mutex2... if both function used the same mutex initializer mutex1, then global variable which has the same scope as mutex will be locked and unlocked based upon function oepration and order sequence. But if function does not share the same mutex variable even though different function has the same global variable to be manipulated, it still could cause race conditions issue. Check output different from pthread_mutex/mutex_test.c:

setting different mutex variable on different functions:

```bash
Hadleys-MacBook-Pro:pthread_mutex hadley$ ./mutex_test 
counter valus is: 1 current thread is 2
counter valus is: 3 current thread is 3
counter valus is: 4 current thread is 4
counter valus is: 2 current thread is 1
counter valus is: 5 current thread is 5
```
setting same mutex variable on different functions:

```bash
Hadleys-MacBook-Pro:pthread_mutex hadley$ ./mutex_test 
counter valus is: 1 current thread is 1
counter valus is: 2 current thread is 1
counter valus is: 3 current thread is 1
counter valus is: 4 current thread is 1
counter valus is: 5 current thread is 1
```


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

check how c programming implement pthread join statement: [link]();

Output difference without joins and with joins:
```bash
hadley@hadley-MacBookPro:~/Developments/pthreads/pthread_join$ ./pthread_join 
counter valus is: 1
counter valus is: 2
counter valus is: 3
counter valus is: 4
counter valus is: 5
counter valus is: 6
counter valus is: 7
counter valus is: 8
counter valus is: 9
final counter value: 9
counter valus is: counter valus is: 10
hadley@hadley-MacBookPro:~/Developments/pthreads/pthread_join$ cc -o pthread_join -pthread pthread_join.c 
hadley@hadley-MacBookPro:~/Developments/pthreads/pthread_join$ ./pthread_join 
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
final counter value: 10
```


## Pthread Condition Variables

Condition variables provide yet another way for threads to synchronize. While mutexes implement synchronization by controlling thread access to data, condition variables allow threads to synchronize based upon the actual value of data.

* A condition variable is always used in conjunction with a mutex lock.

Main Thread:

* declare and initialize global data/variables which require synchronization
* declare and initialize a condition variable object
* declare and initialize an associated mutex
* create threads A and B to do work


Declaration:
```c
//mutex for global variable
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
//mutex for condition checking
pthread_mutex_t condition_mutex = PTHREAD_MUTEX_INITIALIZER;
//condition variable
pthread_cond_t condition_cond = PTHREAD_COND_INITIALIZER;
```

Condition variable allows threads to suspend execution and relinquish the processor. A condition variable must always be associated with a mutex to avoid a race condition. A dead lock could happend when one thread signals the condition before the first thread actually waits on it.

| Thread A    |  Thread B  |  
|-------------|:-------------:|
| 1.lock condition mutex |  3.lock condition mutex | 
| 2. if condition occurs, block Thread A, unlock condition mutex |    4.check if condition occurs, signal Thread A, unlock condition mutex, it could go step 5 or 6   |
| 5. When signalled, wake up. count_mutex is locked and continue | 6. Continue and count_mutex is locked |


### Mechnisms:

* pthread_cond_wait() blocks the calling thread until the specified condition is signalled. This routine should be called while mutex is locked and it will automatically release the mutex while it waits.  

* pthread_cond_signal() routine is used to signal another thread which is waiting on the condition variable. It should be called after mutex is locked, and must unlock mutex in order for pthread_cond_wait() routine to complete.  

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






