#include <Arduino.h>

#include <credentials.h>

#include <TM1638.h>

// define a module on data pin 12, clock pin 13 and strobe pin 11
TM1638 module(12, 13, 11, true, 1);

byte buttons;

int Players = 1;
int Cards = 5;

unsigned long Time;

void setup()
{

  Serial.begin(9600);
}

void loop()
{

  Time = millis();
  // display a variables at 1st and 5th position
  module.setDisplayDigit(Players, 0, false);
  module.setDisplayDigit(Cards, 4, false);

  buttons = module.getButtons();

  Serial.print(Time);
  Serial.print(",");
  Serial.print(Players);
  Serial.print(",");
  Serial.println(Cards);
  delay(100);

  if (buttons != 0)
  {
    delay(300);

    switch (buttons)
    {
    case 1:
      Players = Players + 1;
      Cards = Cards + Players;
      buttons = 0;
      break;
    case 2:
      Players = Players - 1;
      Cards = Cards - Players;
      buttons = 0;
      break;
    }
  }
}