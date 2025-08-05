#include <Wire.h>
#include "../shared/constants.h"

const int PIN_MOTOR1 = 9;
const int PIN_MOTOR2 = 10;
const int PIN_ENABLE = 11;

const int PIN_ACCEL = A0;
const int PIN_BRAKE = A1;
const int PIN_ACCEL_ON = A2;
const int PIN_BRAKE_ON = A3;
const int PIN_GEAR = 7;

float n_rotor = 0;
int motorPWM = 0;
int marcha = 0;

void setup() {
  pinMode(PIN_ACCEL, INPUT);
  pinMode(PIN_BRAKE, INPUT);
  pinMode(PIN_ACCEL_ON, INPUT);
  pinMode(PIN_BRAKE_ON, INPUT);
  pinMode(PIN_GEAR, INPUT);

  pinMode(PIN_MOTOR1, OUTPUT);
  pinMode(PIN_MOTOR2, OUTPUT);
  pinMode(PIN_ENABLE, OUTPUT);

  digitalWrite(PIN_MOTOR1, LOW);
  digitalWrite(PIN_MOTOR2, LOW);
  digitalWrite(PIN_ENABLE, HIGH);

  Wire.onRequest(requestEvent);
  Wire.begin(PowerTrain);

  Serial.begin(9600);
}

void loop() {
  int accel_on = analogRead(PIN_ACCEL_ON);
  int brake_on = analogRead(PIN_BRAKE_ON);
  marcha = digitalRead(PIN_GEAR);

  if (marcha == 1) {
    if (accel_on == 1023) {
      float level = map(analogRead(PIN_ACCEL), 0, 1023, 0, 100);
      n_rotor += D2N_DT2 * level / 100.0;
      if (n_rotor > ROT_MAX) n_rotor = ROT_MAX;
    }

    if (brake_on == 1023) {
      float level = map(analogRead(PIN_BRAKE), 0, 1023, 0, 100);
      n_rotor -= D2N_DT2 * level / 100.0;
      if (n_rotor < 0) n_rotor = 0;
    }

    motorPWM = map(n_rotor, 0, ROT_MAX, 0, 255);
    setMotorForward(0, motorPWM);
  } else {
    if (accel_on == 1023) {
      float level = map(analogRead(PIN_ACCEL), 0, 1023, 0, 100);
      n_rotor -= D2N_DT2 * level / 100.0;
      if (n_rotor < -ROT_MAX) n_rotor = -ROT_MAX;
    }

    if (brake_on == 1023) {
      float level = map(analogRead(PIN_BRAKE), 0, 1023, 0, 100);
      n_rotor += D2N_DT2 * level / 100.0;
      if (n_rotor > 0) n_rotor = 0;
    }

    motorPWM = map(n_rotor, 0, -ROT_MAX, 0, 255);
    setMotorReverse(0, motorPWM);
  }

  delay(100);
}

void setMotorForward(int dir, int pwm) {
  digitalWrite(PIN_MOTOR2, dir);
  analogWrite(PIN_MOTOR1, pwm);
}

void setMotorReverse(int dir, int pwm) {
  digitalWrite(PIN_MOTOR1, dir);
  analogWrite(PIN_MOTOR2, pwm);
}

void requestEvent() {
  uint16_t n = abs(n_rotor);
  Wire.write((n >> 8) & 0xFF);
  Wire.write(n & 0xFF);
  Wire.write(marcha);
}
