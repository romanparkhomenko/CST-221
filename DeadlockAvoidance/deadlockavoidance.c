// Roman Parkhomenko CST-221 06/08/19
// The purpose of this program is to exemplify ability to use a mutex
// lock and a timer to prevent process deadlocking. I create 4 different
// threads and give them a single resource in the form of a processFunction.

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

// Create mutex object.
pthread_mutex_t lock;

// Thread Process Function: The purpose of this function is to emulate a 
// a thread performing a task. In this function, we have the thread loop
// through and print a number 5 times. When a thread enters the function and
// the mutex is locked, we print that the thread is locked. If accessible, we 
// loop through 5 numbers and print the thread and increment number. In each 
// loop iteration, we unlock the mutex and put the thread to sleep for 1 second
// to ensure another thread can access the function.
void *processFunction (void *myvar) {
	char *msg;
	msg = (char *) myvar;

	if (pthread_mutex_lock(&lock) == 0) {
		printf("%s has lock\n", msg);

		for (int i=0; i < 10; i++) {
			printf("%s = %d\n", msg, i);
			pthread_mutex_unlock(&lock);
			sleep(1);
		}
	}

	return NULL;
}

int main(int argc, char *argv[]){
	// Define threads and variables.
	pthread_t thread1, thread2, thread3, thread4;
	char *msg1 = "First Thread";
	char *msg2 = "Second Thread";
	char *msg3 = "Third Thread";
	char *msg4 = "Fourth Thread";
	int ret1, ret2, ret3, ret4;

	// Create the four threads and run a process function.
	ret1 = pthread_create(&thread1, NULL, processFunction, (void *) msg1);
	ret2 = pthread_create(&thread2, NULL, processFunction, (void *) msg2);
	ret3 = pthread_create(&thread3, NULL, processFunction, (void *) msg3);
	ret4 = pthread_create(&thread4, NULL, processFunction, (void *) msg4);

	printf("Main function after pthread_create:\n");

	// Join threads back into main.
	pthread_join(thread1, NULL);
	printf("First thread returns = %d\n", ret1);
	pthread_join(thread2, NULL);
	printf("Second thread returns = %d\n", ret2);
	pthread_join(thread3, NULL);
	printf("Third thread returns = %d\n", ret3);
	pthread_join(thread4, NULL);
	printf("Fourth thread returns = %d\n", ret4);

	return 0;
}