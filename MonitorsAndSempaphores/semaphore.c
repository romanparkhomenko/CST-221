// Roman Parkhomenko CST-221 05/30/19
// The semaphore is similiar to a monitor in the sense that it allows for process synchronization.
// A semaphore basically acts as a counter to the buffer, allowing thread access only if the buffer
// is empty.

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

//Define a Semaphore
typedef int semaphore;
semaphore lock = 0;
int bankAccount = 123456;
int bankBalance = 100;

// For this assignment, I have two spouses attempting to make deposits to their account
// simultaneously. When one spouse is making the deposit, the other spouse will get a message
// saying the account cannot be accessed. This is because the semaphore is set to 1. Once the
// transaction is complete, the semaphore is set to 0 so the other account can be accessed.
void *bank1() {
	for (int i = 1; i < 5; i++){
		if (bankAccount == 123456 && lock != 1) {
			lock = 1;
			printf("Bank 1 Thread Started: Account# %d balance = $%d\n", bankAccount, bankBalance);
			bankBalance += 50;
			printf("$50 Deposited. Your balance is now $%d\n", bankBalance);
			printf("Bank 1 Thread Now Unlocked\n\n");
			lock = 0;
		} else {
			printf("Bank 1: The Account %d cannot be accessed right now try again later\n", bankAccount);
		}
	}
}

void *bank2() {
	for (int i = 1; i < 5; i++){
		if (bankAccount == 123456 && lock != 1) {
			lock = 1;
			printf("Bank 2 Thread Started: Account# %d balance = $%d\n", bankAccount, bankBalance);
			bankBalance += 50;
			printf("$50 Deposited. Your balance is now $%d\n", bankBalance);
			printf("Bank 2 Thread Now Unlocked\n\n");
			lock = 0;
		} else {
			printf("Bank 2: The Account %d cannot be accessed right now try again later\n", bankAccount);
		}
	}
}


int main(){

	pthread_t husband, wife;
	pthread_create(&husband, 0, bank1, 0);
	pthread_create(&wife, 0, bank2, 0);

	printf("Starting threads\n");
	pthread_join(husband, 0);
	pthread_join(wife, 0);

	printf("After the two threads the balance is $%d", bankBalance);

	return 0;
}
