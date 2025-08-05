#include <Wire.h>
#include <Servo.h>
#include <Adafruit_LiquidCrystal.h>
#include "../shared/constants.h"

float distancia = 99.0;
float velocidade = 0;
int marcha = 1;
int cadeira = 0;
int cinto = 0;
int porta = 0;

Servo portaServo;
Adafruit_LiquidCrystal lcd(0);

void setup()
{
    Serial.begin(9600);

    pinMode(PIN_LED_VERMELHO, OUTPUT);
    pinMode(PIN_LED_AMARELO, OUTPUT);
    pinMode(PIN_LED_VERDE, OUTPUT);
    pinMode(PIN_BUZZER, OUTPUT);
    pinMode(PIN_LED_RE, OUTPUT);
    pinMode(PIN_LED_CINTO, OUTPUT);
    pinMode(PIN_LED_PORTA, OUTPUT);

    portaServo.attach(PIN_SERVO, 500, 2500);

    Wire.begin();
    lcd.begin(11, 2);
    lcd.print("Velocidade:");
}

void loop()
{
    readPowertrain();
    readSafety();
    updateLCD();
    logicMarchaRe();
    logicCinto();
    logicPorta();
    delay(100);
}

void readPowertrain()
{
    Wire.requestFrom(PowerTrain, 3);
    if (Wire.available() == 3)
    {
        uint8_t high = Wire.read();
        uint8_t low = Wire.read();
        marcha = Wire.read();
        uint16_t n_rotor = (high << 8) | low;

        velocidade = (marcha == 1) ? 0.12 * n_rotor : -0.12 * n_rotor;

        if (marcha == 0 && velocidade > 0)
        {
            tone(PIN_BUZZER, 330, 100);
        }
    }
}

void readSafety()
{
    Wire.requestFrom(Seguranca, 4);
    if (Wire.available() == 4)
    {
        cadeira = Wire.read();
        cinto = Wire.read();
        porta = Wire.read();
        uint8_t d_byte = Wire.read();
        distancia = d_byte * (2.5 / 255.0);
    }
}

void updateLCD()
{
    lcd.setCursor(0, 1);
    lcd.print("           ");
    lcd.setCursor(0, 1);
    lcd.print(velocidade);
}

void logicMarchaRe()
{
    if (marcha == 0)
    {
        analogWrite(PIN_LED_RE, 255);
        if (distancia < 1.5)
        {
            analogWrite(PIN_LED_VERDE, 255);
            tone(PIN_BUZZER, 440, 20);
            if (distancia < 1.0)
            {
                analogWrite(PIN_LED_AMARELO, 255);
                tone(PIN_BUZZER, 494, 20);
                if (distancia < 0.5)
                {
                    analogWrite(PIN_LED_VERMELHO, 255);
                    tone(PIN_BUZZER, 523, 20);
                }
                else
                {
                    analogWrite(PIN_LED_VERMELHO, 0);
                }
            }
            else
            {
                analogWrite(PIN_LED_AMARELO, 0);
            }
        }
        else
        {
            analogWrite(PIN_LED_VERDE, 0);
        }
    }
    else
    {
        analogWrite(PIN_LED_RE, 0);
    }
}

void logicCinto()
{
    if (cadeira == 1 && cinto == 0)
    {
        analogWrite(PIN_LED_CINTO, 255);
        if (velocidade >= 20)
        {
            tone(PIN_BUZZER, 700, 20);
        }
    }
    else
    {
        analogWrite(PIN_LED_CINTO, 0);
    }
}

void logicPorta()
{
    if (porta == 0)
    {
        analogWrite(PIN_LED_PORTA, 255);
        if (velocidade > 10)
        {
            tone(PIN_BUZZER, 800, 20);
        }
    }
    else
    {
        analogWrite(PIN_LED_PORTA, 0);
        if (abs(velocidade) > 10)
        {
            portaServo.write(90);
        }
        else
        {
            portaServo.write(0);
        }
    }
}
