// Roman Parkhomenko CST-221 05/30/19

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>


#define bufferSize 5

// Thread Handling
pthread_mutex_t bufferAccess;
pthread_cond_t conSleep, proSleep;

// Declare Global variables
static int buffer[bufferSize];
int inIndex = 0;
int outIndex = 0;
int theProduct;

//////////////// Put and Get Functions

// For the put function, we first lock the stack to be only accessed by this thread.
// When the producer hits the buffer limit, it goes to sleep.
// Otherwise, we place theProduct inside the index, and raise the counter
// on the inIndex. Once the buffer size is greater than 0, we wake up the Consumer
// thread to clear it out. After waking up the consumer, we unlock the mutex object so the
// consumer thread can actually access the buffer;
void put(int i) {
	pthread_mutex_lock(&bufferAccess);

	if (inIndex == bufferSize) {
		pthread_cond_wait(&proSleep, &bufferAccess);
	}

	buffer[inIndex] = i;
	inIndex += 1;

	if(inIndex > 0) {
			pthread_cond_signal(&conSleep);
	}

	pthread_mutex_unlock(&bufferAccess);
}

//  For the get function, we lock the stack be only accessed by this thread.
// If the buffer is empty, we put the consumer to sleep. We set the outIndex counter to 0
// and increment it everytime the consumer takes something out of the buffer. Once the inIndex
// and outIndex both equal the bufferSize limit of 20, we reset the process and wake up the
// producer to start filling the stack again. If the consumer outIndex tries to get ahead of the
// producer inIndex, we put the consumer thread to sleep. After this executes, we unlock the mutex
// onject so the next thread can enter the buffer.
int get() {
	pthread_mutex_lock(&bufferAccess);

	if (inIndex == 0) {
		pthread_cond_wait(&conSleep, &bufferAccess);
	}

	int i = buffer[outIndex];
	outIndex += 1;

	if (inIndex == bufferSize && outIndex == bufferSize) {
		inIndex = 0;
		outIndex = 0;
		pthread_cond_signal(&proSleep);
	}

	if(outIndex == inIndex) {
			pthread_cond_wait(&conSleep, &bufferAccess);
	}

	pthread_mutex_unlock(&bufferAccess);

	return i;
}

//////////////// Producer and Consumer functions from assignment.
int produce() {
	theProduct++;
	printf("Produced: %i\n", theProduct);
	return theProduct;
}

void consume(int i){
	printf("Consumed: %i\n", i);
}

void *producer() {
	int i;
	while(1) {
		i = produce();
		put(i);
	}
}

void *consumer() {
	int i;
	while(1) {
		i = get();
		consume(i);
	}
}


//Main Function
int main(){
	pthread_t con, pro;
	pthread_mutex_init(&bufferAccess, 0);
	pthread_cond_init(&conSleep, 0);
	pthread_cond_init(&proSleep, 0);
	pthread_create(&con, 0, consumer, 0);
	pthread_create(&pro, 0, producer, 0);
	pthread_join(pro, 0);
	pthread_join(con, 0);

	return 0;
}
