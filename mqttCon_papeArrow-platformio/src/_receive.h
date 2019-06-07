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

void servoArrow()
{
  myservo.write(0);
  for (pos = 0; pos >= 180; pos -= 1)
  {
    myservo.write(pos);
    delay(15);
  }
}

int dataA, dataB, dataC;
void multiSlider(String revData) {
  String headString, tailString;
  revData.trim();  // remove leading&trailing whitespace, if any
  int dataIndex = revData.indexOf('=');
  headString = revData.substring(0, dataIndex);
  tailString = revData.substring(dataIndex + 1);

  if (headString.equalsIgnoreCase("A")) {
    dataA = tailString.toInt();
  } else if (headString.equalsIgnoreCase("B")) {
    dataB = tailString.toInt();
  } else if (headString.equalsIgnoreCase("C")) {
    dataC = tailString.toInt();
  }
}


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
        digitalWrite(relayPin, HIGH);
        digitalWrite(LED_PIN, LOW);
        relayPinState = HIGH;
        for (pos = 0; pos <= 180; pos += 1)
        {
          myservo.write(pos);
          delay(15);
        }
      }
      else if (payload == "OFF")
      {
        digitalWrite(relayPin, LOW);
        digitalWrite(LED_PIN, HIGH);
        relayPinState = LOW;
        for (pos = 180; pos >= 0; pos -= 1)
        {
          myservo.write(pos);
          delay(15);
        }
      }
    }
    else if (cmd == "$/reboot")
    {
      ESP.restart();
    }
    else if (cmd == "$/direction")
    {
      //uint16_t direc = payload.toInt();
      multiSlider(payload);
      Serial.print("dataA: ");
      Serial.println(dataA);
      myservo.write(dataA);
    }
    else
    {
      // another message.
    }
  });
}
