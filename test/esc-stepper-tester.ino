#include <Arduino.h>
#include <Servo.h>
#include <AccelStepper.h>

Servo ESC1;
int pot1;
int pot2;

#define DIR 10
#define PUL 11
AccelStepper STEPPER1(1, PUL, DIR);

void setup() {
	ESC1.attach(9, 1000, 2000);
	STEPPER1.setMaxSpeed(1000);
}

void loop() {
	pot1 = analogRead(A1);
	pot1 = map(pot1, 0, 1023, 0, 180);
	ESC1.write(pot1);

	pot2 = analogRead(A2);
	STEPPER1.setSpeed(pot2*2 - 512);
	STEPPER1.runSpeed();
}

