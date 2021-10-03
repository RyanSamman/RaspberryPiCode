#include <signal.h>
#include <math.h>
#include <stdbool.h>
#include <wiringPi.h>
#include <softTone.h>

const int BUZZER_PIN = 0;

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
	softToneCreate(BUZZER_PIN);

	int i = 0;
	while (running)
	{
		softToneWrite(BUZZER_PIN, freqs[i]);
		i = (i + 1) % freqCount;
		delay(2000);
	}

	softToneWrite(BUZZER_PIN, 0); // turn off buzzer
	pinMode(BUZZER_PIN, INPUT);
}

static void handleExit()
{
	running = false;
}

void alertor(int pin)
{
	int x;
	double sinVal, toneVal;
	for (x = 0; x < 360; x++)
	{									// frequency of the alertor is consistent with the sine wave
		sinVal = sin(x * (M_PI / 180)); //Calculate the sine value
		toneVal = 14000 + sinVal * 50;	//Add the resonant frequency and weighted sine value
		softToneWrite(pin, toneVal);
		delay(1);
	}
}