/*
  "Username": "6EiMMOxwOEcW7Cn",
  "Password": "9rHrwHRdHIh2drstkZk5TBQWMQE=",
  "ClientId": "VENSIx6XGK1TauoK",
  "Prefix": "/CMMCxPaperSignals/gearname/",
  "Host": "gb.netpie.io",
  "Port": "1883"
 */

#include <Arduino.h> 

/* BOARD INFO */
String DEVICE_NAME      = "arrow-001"; 

/* WIFI INFO */ 
String WIFI_SSID        = "ampere";
String WIFI_PASSWORD    = "espertap";

/* MQTT INFO */ 
String MQTT_HOST        = "gb.netpie.io";
String MQTT_USERNAME    = "6EiMMOxwOEcW7Cn";
String MQTT_PASSWORD    = "9rHrwHRdHIh2drstkZk5TBQWMQE=";
String MQTT_CLIENT_ID   = "VENSIx6XGK1TauoK";
String MQTT_PREFIX      = "/CMMCxPaperSignals/gearname/";

int    MQTT_PORT        = 1883;
int PUBLISH_EVERY       = 10L * 1000;
int MQTT_CONNECT_TIMEOUT= 10; 
