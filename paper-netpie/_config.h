#include <Arduino.h> 

/* BOARD INFO */
String DEVICE_NAME      = "rocket-001"; 

/* WIFI INFO */ 
String WIFI_SSID        = "T123456";
String WIFI_PASSWORD    = "V4bTaMaTo";

/* MQTT INFO */ 
String MQTT_HOST        = "gb.netpie.io";
String MQTT_USERNAME    = "6EiMMOxwOEcW7Cn";
String MQTT_PASSWORD    = "G6uhhuzuzPch9NjAIJoubqHvDQc=";
String MQTT_CLIENT_ID   = "xvRigCxG1atM5ufU";
String MQTT_PREFIX      = "/CMMCxPaperSignals/gearname/";

int    MQTT_PORT        = 1883;
int PUBLISH_EVERY       = 10L * 1000;
int MQTT_CONNECT_TIMEOUT= 10; 
