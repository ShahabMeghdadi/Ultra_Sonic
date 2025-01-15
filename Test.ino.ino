#include <TimerOne.h>
#include <Wire.h>
#include <MultiFuncShield.h>
#include <Ultrasonic.h>

const int EchoPin = 6;
const int TrigPin = 5;

void setup ()
{}
 
void loop()
{
  Ultrasonic ultrasonic(9, 5);
  int distance;
  Timer1.initialize();
  MFS.initialize(&Timer1);
  int dist0 = 0;
  bool stat = 0;
  while (1)
  {
    byte btn = MFS.getButton(); 
    distance = ultrasonic.read();
    if (distance == 357 && dist0 <100){
      distance = 0;
    }
    int speed = distance - dist0;
    if(speed < 0){
      speed = -speed;
    }
    if(btn){
      byte buttonNumber = btn & B00111111;
      byte buttonAction = btn & B11000000;
      if(buttonAction == BUTTON_PRESSED_IND){
        stat = !stat;
      }
    }
    if(stat == 0){
      MFS.write(distance);
      MFS.writeLeds(LED_1, ON);
      MFS.writeLeds(LED_2, OFF);
    }
    else{
      MFS.write(speed);
      MFS.writeLeds(LED_1, OFF);
      MFS.writeLeds(LED_2, ON);
    }
    dist0 = distance;
    delay(200);
  }  
}
