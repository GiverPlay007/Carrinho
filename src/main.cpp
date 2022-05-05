#include <Arduino.h>

void setup()
{
  Serial.begin(115200);

  pinMode(GPIO_NUM_25, OUTPUT);
  pinMode(GPIO_NUM_26, OUTPUT);
  pinMode(GPIO_NUM_27, OUTPUT);

  ledcSetup(0, 30000, 8);
  ledcAttachPin(GPIO_NUM_25, 0);

  ledcWrite(0, 254);
}

void loop()
{
  if(Serial.available())
  {
    int input = Serial.parseInt();

    switch(input) {
      case 1:
        digitalWrite(GPIO_NUM_26, HIGH);
        digitalWrite(GPIO_NUM_27, LOW);
        Serial.println("C 1");
        break;
      case 2:
        digitalWrite(GPIO_NUM_27, HIGH);
        digitalWrite(GPIO_NUM_26, LOW);
        Serial.println("C 2");
        break;
      case 3:
        digitalWrite(GPIO_NUM_26, LOW);
        digitalWrite(GPIO_NUM_27, LOW);
        Serial.println("C 3");
        break;
    }
  }
}