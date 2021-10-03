// LED Bar
#include <wiringPi.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define LED_COUNT 8
const int pins[LED_COUNT] = {0, 1, 2, 3, 4, 5, 6, 8};
	
void printBin(int val, int bits);

void main(void)
{
	// Maximum Number in 8 bits
	int MAX_NUM_8 = (int) powl(2, 8);
		
	
	wiringPiSetup();

	for (int i = 0; i < LED_COUNT; i++)
	{ 
		pinMode(pins[i], OUTPUT);
		digitalWrite(pins[i], 1);
	}

	delay(2000);

	int i = 0;
	while (true) 
	{
		printf("%i - ", i);
		printBin(i, LED_COUNT);
		i++;
		i %= (int) powl(2, 8);
		delay(100);
	}
}

void printBin(int val, int bits) {
	int i = bits - 1;
	while (i >= 0) {
		printf("%i", (val >> i) & 1);
		digitalWrite(pins[i], (val >> i) & 1 ? 0 : 1);
		i--;
	}

	printf("\n");
}