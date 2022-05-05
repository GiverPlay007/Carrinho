#include <Arduino.h>
#include <ESP32Servo.h>

#define DIRECTION_CENTER 94
#define DIRECTION_LEFT 0
#define DIRECTION_RIGHT 180

Servo direction;
int angle = DIRECTION_CENTER;

void setup()
{
  Serial.begin(115200);

  pinMode(GPIO_NUM_14, OUTPUT);
  pinMode(GPIO_NUM_25, OUTPUT);
  pinMode(GPIO_NUM_26, OUTPUT);
  pinMode(GPIO_NUM_27, OUTPUT);

  ledcSetup(10, 30000, 8);
  ledcAttachPin(GPIO_NUM_25, 10);

  ledcWrite(10, 254);

  ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);

  direction.setPeriodHertz(50);
  direction.attach(GPIO_NUM_14, 500, 2400);
}

void loop()
{
  if(Serial.available())
  {
    int input = Serial.parseInt();

    switch(input) {
      case 1:
        digitalWrite(GPIO_NUM_26, LOW);
        digitalWrite(GPIO_NUM_27, LOW);
        Serial.println("STOP");
        break;
      case 2:
        digitalWrite(GPIO_NUM_26, HIGH);
        digitalWrite(GPIO_NUM_27, LOW);
        Serial.println("FORWARD");
        break;
      case 3:
        digitalWrite(GPIO_NUM_26, LOW);
        digitalWrite(GPIO_NUM_27, HIGH);
        Serial.println("BACKWARD");
        break;
      case 4:
        angle = DIRECTION_CENTER;
        Serial.println("CENTER");
        break;
      case 5:
        angle = DIRECTION_RIGHT;
        Serial.println("RIGHT");
        break;
      case 6:
        angle = DIRECTION_LEFT;
        Serial.println("LEFT");
        break;
    }
  }

  direction.write(angle);
}