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

extern bool countState;
extern int countTimer;
extern int timeMax;

void servoArrow_ON();
void servoArrow_OFF();
void servoRocket_ON();
void servoRocket_OFF();
void servoStrerch_ON();
void servoStrerch_OFF();
void servoStrerch_MOVE(int time2move);
void servoPants_ON();
void servoPants_OFF();
void servoCountDown_ON();
void servoCountDown_OFF();
void servoCountDown_TIME(int timer);

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
        servoStrerch_ON();
#elif PANTS
        servoPants_ON();
#elif COUNTDOWN
        servoCountDown_ON();
#endif
      }
      else if (payload == "OFF")
      {
#ifdef ARROW
        servoArrow_OFF(); // swing down
#elif ROCKET
        servoRocket_OFF();
#elif STRERCH
        servoStrerch_OFF();
#elif PANTS
        servoPants_OFF();
#elif COUNTDOWN
        servoCountDown_OFF();
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
      else if (time2move >= 10)
      {
        time2move = 10;
      }
      servoStrerch_MOVE(time2move);
    }
#endif

#ifdef COUNTDOWN
    if (cmd == "$/value")
    {
      // uint16_t countDownTime = payload.toInt();
      // servoCountDown_TIME(countDownTime);
      countTimer = payload.toInt();
      timeMax = countTimer;
      countState = true;
      myservo.write(0);
      delay(1000);
      Serial.print("countState: ");
      Serial.println(countState);
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
  if (servoDegree >= 175)
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
  myservo.write(80);
}

void servoStrerch_OFF()
{
  myservo.write(140);
}

int timeCount = 1000;

void servoStrerch_MOVE(int time2move)
{
  for (int i = 1; i <= time2move; i++)
  {
    myservo.write(80);
    delay(timeCount);
    myservo.write(140);
    delay(timeCount);

    timeCount -= 200;
    if (timeCount <= 100)
    {
      timeCount = 100;
    }
  }
  timeCount = 1000;
}

void servoPants_ON()
{
  myservo.write(100);
}

void servoPants_OFF()
{
  myservo.write(180);
}

void servoCountDown_ON()
{
  countState = false;
  myservo.write(0);
}
void servoCountDown_OFF()
{
  countState = false;
  myservo.write(150);
}

// uint32_t pevTime_Count = 0;
// void servoCountDown_TIME(int timer)
// {
//   myservo.write(0);
//   delay(1000);

//   int timeMax = timer;
//   if(timer > 0)
//   {
//     myservo.write(map(timer, 0, timeMax, 150, 0));
//     delay(1);

//     uint32_t curTime_Count = millis();
//     if (curTime_Count - pevTime_Count >= 1000)
//     {
//       timer -= 1;
//       pevTime_Count = curTime_Count;
//     }
//   }

//   for (int i = 1; i <= 3; i++)
//   {
//     myservo.write(0);
//     delay(500);
//     myservo.write(150);
//     delay(500);
//   }
// }