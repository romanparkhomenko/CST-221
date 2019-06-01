// Roman Parkhomenko CST-221 05/30/19

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

// C doesn't have a built in monitor class. To implement a monitor and it's conditions in C,
// I'll be using the mutex object and different conditions to lock the buffer. When researching
// this topic, the example of accessing bank accounts seemed to make the most sense, which is the
// approach I took in implementing this logic.
pthread_mutex_t monitor_lock;
int bankAccount = 123456;
int bankBalance = 100;

// For this assignment, I have two spouses attempting to make deposits to their account
// simultaneously. When one spouse is making the deposit, the other spouse will get a message
// saying the account cannot be accessed. This is accomplished by monitoring the account number
// as well as setting a monitor lock on the thread with a mutex lock.
void *bank1(){
	for (int i = 1; i < 5; i++) {
		if (bankAccount == 123456) {
			pthread_mutex_lock(&monitor_lock);
			printf("Bank 1 Thread Started: Account# %d balance = $%d\n", bankAccount, bankBalance);
			bankBalance += 50;
			printf("$50 Deposited. Your balance is now $%d\n", bankBalance);
			printf("Bank 1 Thread Now Opened\n\n");
			pthread_mutex_unlock(&monitor_lock);
		} else {
			printf("Bank 1: The thread for Account %d is locked.\n", bankAccount);
		}
	}
}

void *bank2() {
	for (int i = 1; i < 5; i++){
		if (bankAccount == 123456) {
			pthread_mutex_lock(&monitor_lock);
			printf("Bank 2 Thread Started: Account# %d balance = $%d\n", bankAccount, bankBalance);
			bankBalance += 50;
			printf("$50 Deposited. Your balance is now $%d\n", bankBalance);
			printf("Bank 2 Thread Now Opened\n\n");
			pthread_mutex_unlock(&monitor_lock);
		} else {
			printf("Bank 2: The thread for Account %d is locked.\n", bankAccount);
		}
	}
}


int main() {
	pthread_t husband, wife;
	pthread_mutex_init(&monitor_lock, 0);
	pthread_create(&husband, 0, bank1, 0);
	pthread_create(&wife, 0, bank2, 0);

	printf("Starting threads\n");
	pthread_join(husband, 0);
	pthread_join(wife, 0);

	printf("After the two threads the balance is $%d", bankBalance);

	return 0;
}
