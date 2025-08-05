#include <Wire.h>
#include "../shared/constants.h"

float distancia_m = 0.0;
int cadeira = 0;
int cinto = 0;
int porta = 0;

void setup()
{
    Serial.begin(9600);

    pinMode(PIN_SENSOR_CADEIRA, INPUT);
    pinMode(PIN_SENSOR_CINTO, INPUT);
    pinMode(PIN_SENSOR_PORTA, INPUT);

    Wire.onRequest(requestEvent);
    Wire.begin(Seguranca);
}

void loop()
{
    distancia_m = 0.01723 * readUltrasonicDistance(PIN_ULTRASSONIC, PIN_ULTRASSONIC) / 100.0;

    cadeira = analogRead(PIN_SENSOR_CADEIRA) > 512 ? 1 : 0;
    cinto = analogRead(PIN_SENSOR_CINTO) > 512 ? 1 : 0;
    porta = analogRead(PIN_SENSOR_PORTA) > 512 ? 1 : 0;

    delay(100);
}

long readUltrasonicDistance(int triggerPin, int echoPin)
{
    pinMode(triggerPin, OUTPUT);
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    pinMode(echoPin, INPUT);
    return pulseIn(echoPin, HIGH);
}

void requestEvent()
{
    uint8_t d = distancia_m > 2.5 ? 255 : static_cast<uint8_t>(distancia_m * 255.0 / 2.5);
    Wire.write(cadeira);
    Wire.write(cinto);
    Wire.write(porta);
    Wire.write(d);
}
