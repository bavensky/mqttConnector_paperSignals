/*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>
unsigned long previousMillis = 0; 
Servo myservo;  // create servo object to control a servo

int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin

void setup() {
  myservo.attach(14);  // attaches the servo on pin 9 to the servo object
}
float xcv =0;
void loop() {
  
  //val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
  xcv = smooth(0.1f,analogRead(potpin),xcv);
  val = map(xcv, 30, 400, 180, 0);     // scale it to use it with the servo (value between 0 and 180)
 unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= 15) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
  myservo.write(val);                  // sets the servo position according to the scaled value
  delay(15);                           // waits for the servo to get there
  }
}
float smooth(float alfa, float new_data, float old_data)
{
  return (old_data + alfa * (new_data - old_data));
}
