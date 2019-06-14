#include <Arduino.h>
#include <MqttConnector.h>

extern MqttConnector *mqtt;

extern String MQTT_CLIENT_ID;
extern String MQTT_PREFIX;

extern int relayPin;
extern int relayPinState;
extern char myName[];

extern int LED_PIN;
extern int pos;
extern int servoDegree;

void servoArrow_ON();
void servoArrow_OFF();
void servoRocket_ON();
void servoRocket_OFF();
void servoStrerch_ON();
void servoStrerch_OFF();
void servoPants_ON();
void servoPants_OFF();

/* RECEIVE FUNCTION */
void register_receive_hooks()
{
  mqtt->on_subscribe([&](MQTT::Subscribe *sub) -> void {
    Serial.printf("myName = %s \r\n", myName);
    sub->add_topic(MQTT_PREFIX + myName + "/$/+");
    sub->add_topic(MQTT_PREFIX + MQTT_CLIENT_ID + "/$/+");
  });

  mqtt->on_before_message_arrived_once([&](void) {});

  mqtt->on_message([&](const MQTT::Publish &pub) {});

  mqtt->on_after_message_arrived([&](String topic, String cmd, String payload) {
    Serial.printf("topic: %s\r\n", topic.c_str());
    Serial.printf("cmd: %s\r\n", cmd.c_str());
    Serial.printf("payload: %s\r\n", payload.c_str());

    if (cmd == "$/command")
    {
      if (payload == "ON")
      {
#ifdef ARROW
        servoArrow_ON(); // swing up
#elif ROCKET
        servoRocket_ON();
#elif STRERCH
        myservo.write(140); // set default of strerch servo
#elif PANTS
        servoPants_ON(); 
#elif COUNTDOWN
        myservo.write(90); // set default of count down servo
#endif
      }
      else if (payload == "OFF")
      {
#ifdef ARROW
        servoArrow_OFF(); // swing down
#elif ROCKET
        servoRocket_OFF();
#elif STRERCH
        myservo.write(140); // set default of strerch servo
#elif PANTS
        servoPants_OFF();
#elif COUNTDOWN
        myservo.write(90); // set default of count down servo
#endif
      }
    }

#ifdef ARROW
    if (cmd == "$/direction")
    {

      uint16_t direc = payload.toInt();
      if (direc <= 0)
      {
        direc = 0;
      }
      else if (direc >= 180)
      {
        direc = 180;
      }
      myservo.write(direc);
      servoDegree = direc;
    }
#endif

#ifdef STRERCH
    if (cmd == "$/time")
    {

      uint16_t time2move = payload.toInt();
      if (time2move <= 0)
      {
        time2move = 0;
      }
      else if (time2move >= 5)
      {
        time2move = 5;
      }
      // myservo.write(time2move);
    }
#endif

#ifdef COUNTDOWN
    if (cmd == "$/value")
    {

      uint16_t countDownTime = payload.toInt();
      if (countDownTime <= 0)
      {
        countDownTime = 0;
      }
      else if (countDownTime >= 100)
      {
        countDownTime = 100;
      }
      myservo.write(countDownTime);
    }
#endif

  });
}

/* ACTION */
void servoRocket_ON()
{
  myservo.write(150);
  for (pos = 150; pos >= 100; pos -= 1)
  {
    myservo.write(pos);
    delay(15);
  }
  for (pos = 100; pos <= 130; pos += 1)
  {
    myservo.write(pos);
    delay(15);
  }
  for (pos = 130; pos >= 80; pos -= 1)
  {
    myservo.write(pos);
    delay(15);
  }
  for (pos = 80; pos <= 100; pos += 1)
  {
    myservo.write(pos);
    delay(15);
  }
  for (pos = 100; pos >= 70; pos -= 1)
  {
    myservo.write(pos);
    delay(15);
  }
}

void servoRocket_OFF()
{
  for (pos = 70; pos <= 150; pos += 1)
  {
    myservo.write(pos);
    delay(15);
  }
}

void servoArrow_ON()
{
  if (servoDegree >= arrowServoUP)
  {
  }
  else
  {
    for (pos = servoDegree; pos <= 175; pos += 1)
    {
      myservo.write(pos);
      delay(15);
    }
    servoDegree = pos;
  }
}

void servoArrow_OFF()
{
  if (servoDegree <= 0)
  {
  }
  else
  {
    for (pos = servoDegree; pos >= 0; pos -= 1)
    {
      myservo.write(pos);
      delay(15);
    }
    servoDegree = pos;
  }
}

void servoStrerch_ON()
{
}

void servoStrerch_OFF()
{
}

void servoPants_ON()
{
  myservo.write(180);
}

void servoPants_OFF()
{
  myservo.write(100);
}
