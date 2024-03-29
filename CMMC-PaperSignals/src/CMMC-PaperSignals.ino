#include <Arduino.h>

// SELECT YOUR PAPER SIGNALS HERE !!!
// #define ARROW       true
// #define ROCKET      true
// #define STRERCH     true
// #define PANTS       true
#define COUNTDOWN true

#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#elif ESP32
#include <WiFi.h>
#endif

#include <ArduinoJson.h>
#include <MqttConnector.h>
#include <Wire.h>
#include <SPI.h>

#ifdef ESP8266
#include <Servo.h>
#elif ESP32
#include <ESP32Servo.h>
#endif
Servo myservo;

int servoPin = 14;
int pos = 0;
int relayPin = 15;
int relayPinState = HIGH;
int LED_PIN = 2;
int servoDegree = 0;
uint32_t pevTime_Count = 0;
int timeMax = 0;
bool countState = false;
int countTimer = 0;

char myName[40];

#include "init_mqtt.h"
#include "_publish.h"
#include "_receive.h"
#include "_config.h"

MqttConnector *mqtt;

void servoCountDown_TIME(int timer);

void init_hardware()
{
  pinMode(relayPin, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(relayPin, relayPinState);
  ;
  // serial port initialization
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println("Starting...");

#ifdef ESP8266
  myservo.attach(servoPin);
#elif ESP32
  myservo.setPeriodHertz(50); // standard 50 hz servo
  myservo.attach(servoPin, 1000, 2000);
#endif

#ifdef ARROW
  myservo.write(0); // set default of arrow servo
  servoDegree = 0;
#elif ROCKET
  myservo.write(150); // set default of rocket servo
  servoDegree = 150;
#elif STRERCH
  myservo.write(140); // set default of strerch servo
  servoDegree = 140;
#elif PANTS
  myservo.write(180); // set default of pants servo
  servoDegree = 180;
#elif COUNTDOWN
  myservo.write(0); // set default of count down servo
  delay(500);
  myservo.write(150);
  servoDegree = 150;
#endif
}

void init_wifi()
{
  WiFi.disconnect();
  delay(20);
  WiFi.mode(WIFI_STA);
  delay(50);
  const char *ssid = WIFI_SSID.c_str();
  const char *pass = WIFI_PASSWORD.c_str();
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.printf("Connecting to %s:%s\r\n", ssid, pass);
    delay(300);
  }
  Serial.println("WiFi Connected.");
  digitalWrite(2, HIGH);
}

void setup()
{
  init_hardware();
  init_wifi();
  init_mqtt();
}

void loop()
{
  mqtt->loop();
  if (countState == true)
  {
    servoCountDown_TIME();
  }
}

void servoCountDown_TIME()
{
  uint32_t curTime_Count = millis();
  if (curTime_Count - pevTime_Count >= 1000)
  {
    countTimer -= 1;
    pevTime_Count = curTime_Count;
  }

  if (countTimer >= 0)
  {
    myservo.write(map(countTimer, 0, timeMax, 150, 0));
  }

  if (countTimer < 0)
  {
    countState = false;
    myservo.write(150);
  }

  if (countTimer < 0 && countState == false)
  {
    for (int i = 1; i <= 3; i++)
    {
      myservo.write(0);
      delay(500);
      myservo.write(150);
      delay(500);
    }
  }
}