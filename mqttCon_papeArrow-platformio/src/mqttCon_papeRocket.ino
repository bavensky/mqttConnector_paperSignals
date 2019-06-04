#include <Arduino.h>

#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#elif  ESP32
#include <WiFi.h>
#endif

#include <ArduinoJson.h>
#include <MqttConnector.h>
#include <Wire.h>
#include <SPI.h>

#ifdef ESP8266
#include <Servo.h>
#elif  ESP32
#include <ESP32Servo.h>
#endif
Servo myservo;

int servoPin = 14;
int pos = 0;

#include "init_mqtt.h"
#include "_publish.h"
#include "_receive.h"
#include "_config.h"

MqttConnector *mqtt;

int relayPin = 15;
int relayPinState = HIGH;
int LED_PIN = 2;


char myName[40];

void init_hardware()
{
  pinMode(relayPin, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(relayPin, relayPinState);;
  // serial port initialization
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println("Starting...");

#ifdef ESP8266
  myservo.attach(servoPin);
#elif  ESP32
  myservo.setPeriodHertz(50);    // standard 50 hz servo
  myservo.attach(servoPin, 1000, 2000);
#endif
  myservo.write(0); // arrow servo default
}

void init_wifi() {
  WiFi.disconnect();
  delay(20);
  WiFi.mode(WIFI_STA);
  delay(50);
  const char* ssid =  WIFI_SSID.c_str();
  const char* pass =  WIFI_PASSWORD.c_str();
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.printf ("Connecting to %s:%s\r\n", ssid, pass);
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
}
