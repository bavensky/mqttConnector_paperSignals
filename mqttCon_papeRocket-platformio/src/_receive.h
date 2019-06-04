#include <Arduino.h>
#include <MqttConnector.h>

extern MqttConnector* mqtt;

extern String MQTT_CLIENT_ID;
extern String MQTT_PREFIX;

extern int relayPin;
extern int relayPinState;
extern char myName[];

extern int LED_PIN;
extern int pos;

void servoRocket() {
  myservo.write(170);
  for (pos = 170; pos >= 100; pos -= 1) {
    myservo.write(pos);
    delay(15);
  }
  for (pos = 100; pos <= 150; pos += 1) {
    myservo.write(pos);
    delay(15);
  }
  for (pos = 150; pos >= 100; pos -= 1) {
    myservo.write(pos);
    delay(15);
  }
  for (pos = 100; pos <= 130; pos += 1) {
    myservo.write(pos);
    delay(15);
  }
  for (pos = 130; pos >= 60; pos -= 1) {
    myservo.write(pos);
    delay(15);
  }
}

void register_receive_hooks() {
  mqtt->on_subscribe([&](MQTT::Subscribe * sub) -> void {
    Serial.printf("myName = %s \r\n", myName);
    sub->add_topic(MQTT_PREFIX + myName + "/$/+");
    sub->add_topic(MQTT_PREFIX + MQTT_CLIENT_ID + "/$/+");
  });

  mqtt->on_before_message_arrived_once([&](void) { });

  mqtt->on_message([&](const MQTT::Publish & pub) { });

  mqtt->on_after_message_arrived([&](String topic, String cmd, String payload) {
    Serial.printf("topic: %s\r\n", topic.c_str());
    Serial.printf("cmd: %s\r\n", cmd.c_str());
    Serial.printf("payload: %s\r\n", payload.c_str());
    if (cmd == "$/command") {
      if (payload == "ON") {
        digitalWrite(relayPin, HIGH);
        digitalWrite(LED_PIN, LOW);
        relayPinState = HIGH;
        servoRocket();
      }
      else if (payload == "OFF") {
        digitalWrite(relayPin, LOW);
        digitalWrite(LED_PIN, HIGH);
        relayPinState = LOW;
        for (pos = 60; pos <= 170; pos += 1) {
          myservo.write(pos);
          delay(15);
        }
      }
    }
    else if (cmd == "$/reboot") {
      ESP.restart();
    }
    else {
      // another message.
    }
  });
}
