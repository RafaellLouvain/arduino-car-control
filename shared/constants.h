#ifndef CONSTANTS_H
#define CONSTANTS_H

#define PowerTrain 0x08
#define Seguranca 0x09

const int ROT_MAX = 1621;
const int D2N_DT2 = 200;

// Pinos - Dashboard
const int PIN_LED_VERDE = 3;
const int PIN_LED_AMARELO = 5;
const int PIN_LED_VERMELHO = 6;
const int PIN_BUZZER = 4;
const int PIN_LED_RE = 9;
const int PIN_LED_CINTO = 8;
const int PIN_LED_PORTA = 7;
const int PIN_SERVO = 10;

// Endereços I2C
#define Seguranca 0x09

// Pinos - Safety
const int PIN_SENSOR_CADEIRA = A0;
const int PIN_SENSOR_CINTO = A1;
const int PIN_SENSOR_PORTA = A2;
const int PIN_ULTRASSONIC = 7;

#endif
