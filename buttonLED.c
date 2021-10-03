#include <signal.h>
#include <math.h>
#include <stdbool.h>
#include <wiringPi.h>
#include <stdio.h>
#include <softTone.h>

const int BUZZER_PIN = 0;
const int BUTTON_PIN = 1;

static volatile sig_atomic_t running = true;

static void handleExit();

void alertor();

int main()
{
	int freqs[] = {50, 100, 500, 1000, 2000, 4000, 8000, 14000};
	int freqCount = 8;
	signal(SIGINT, handleExit);
	wiringPiSetup();
	pinMode(BUZZER_PIN, OUTPUT);
	pinMode(BUTTON_PIN, INPUT);
	softToneCreate(BUZZER_PIN);

	int i = 0;
	while (running)
	{
		if (digitalRead(BUTTON_PIN)) {
			printf("Wat");
			softToneWrite(BUZZER_PIN, freqs[i]);
			i = (i + 1) % freqCount;
			delay(2000);
		} else {
			softToneWrite(BUZZER_PIN, 0);
		}

	}

	softToneWrite(BUZZER_PIN, 0); // turn off buzzer
	pinMode(BUZZER_PIN, INPUT);
	pinMode(BUTTON_PIN, INPUT);
}

static void handleExit()
{
	running = false;
}



