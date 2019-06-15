// Roman Parkhomenko CST-221 06/14/19
// The purpose of this program is to perform a series of manipulations
// to a number given by the user. We will print the number in decimal form
// and then change it to binary and hexadecimal formats in addition to shifting
// the number by 16 bits left and masking the bottom 16 bits.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// Declare variables and 32 bit binary array.
int i, j, x, final;
unsigned int decimal = -1, transform;
char binary_array [32];

// Function to print to console.
void* printMessage(char message []){
	printf("%s", message);
}

// Function to read input from console and clear input buffer.
void* readInput(){
	scanf("%d", &decimal);
	while ((getchar()) != '\n');
}

// Function to take the user input and transform it to binary.
void* calculateBinaryNumber() {
	if (decimal >= 0 && decimal < 4096){
		unsigned int mask = 1<<31;
		for (i = 0; i < 8; i++){
			for (j = 0; j < 4; j++){
				char c = (decimal & mask) == 0 ? '0' : '1';
				binary_array[x++] = c;
				putchar(c);
				mask >>= 1;
			}
			putchar(' ');
		}
		putchar('\n');
	}
}

// Function to convert the input to hexadecimal format and print to console.
void* printHexadecimalNumber(){
	printf("%04x\n", decimal);
}

void* calculateDecimalNumber(){
	printMessage("The result in binary: ");
	calculateBinaryNumber();
	printMessage("The result in hexadecimal: ");
	printHexadecimalNumber();
}

// This function shifts the decimal variable 16 bits to the left and then
// masks out the bottom 16 bits. It then adds the new hex number and prints all
// all the results to the console.
void* transformNumber(){
	transform = decimal << 16;
	final = transform & decimal;
	unsigned int addition = 0x07FF;
	final = final | addition;
	printf("The new decimal value is: %d\n", final);
	decimal = final;
	calculateDecimalNumber();
}

int main (void){
	while (decimal < 0 || decimal > 4095){
		printMessage("Hello! Please print an integer between 0 and 4095: ");
		readInput();
		if (decimal < 0 || decimal > 4095){
			printMessage("Whoops, please make sure your number is between 0 and 4095!\n");
		}
	}

	calculateDecimalNumber();
	transformNumber();

	return 0;
}
