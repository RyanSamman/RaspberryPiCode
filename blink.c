#include <signal.h>
#include <stdbool.h>
#include <wiringPi.h>

static volatile sig_atomic_t running = true;

static void handleExit()
{
    running = false;
}

// The PIN we will be using to control the LED
const int LED_PIN = 0;

/*
	Sets up the wiringPi Library
	and configures the GPIO pin to 
*/
void setup() {
	wiringPiSetup();
	pinMode(LED_PIN, OUTPUT);
}

/*
	Revert the GPIO pin to it's original INPUT state
*/
void cleanup() {
	digitalWrite(LED_PIN, false);
	pinMode(LED_PIN, INPUT);
}

int main() {

	signal(SIGINT, handleExit);

	setup();

	bool toggle = true;
	
	while (running) {
		digitalWrite(LED_PIN, toggle);
		toggle = !toggle;
		delay(1000);
	}

	cleanup();
	
}
