#include <Arduino.h>

#ifdef ARROW
String DEVICE_NAME = "arrow";
String MQTT_HOST = "gb.netpie.io";
String MQTT_USERNAME = "6EiMMOxwOEcW7Cn";
String MQTT_PASSWORD = "9CcfbdKEX0dC7D53NEXnPwBpsWU=";
String MQTT_CLIENT_ID = "R8pNYOhHTsXiFwR9";
String MQTT_PREFIX = "/CMMCxPaperSignals/gearname/";
// mosquitto_sub -t "/CMMCxPaperSignals/gearname/#" -h gb.netpie.io -i R8pNYOhHTsXiFwR9 -u "6EiMMOxwOEcW7Cn" -P "9CcfbdKEX0dC7D53NEXnPwBpsWU=" -p 1883 -d
#elif ROCKET
String DEVICE_NAME = "rocket";
String MQTT_HOST = "gb.netpie.io";
String MQTT_USERNAME = "6EiMMOxwOEcW7Cn";
String MQTT_PASSWORD = "gzaY6JlJ+0pl9xKJ3gTMo9gNOP8=";
String MQTT_CLIENT_ID = "HSTPpOpb5wzGqNsU";
String MQTT_PREFIX = "/CMMCxPaperSignals/gearname/";
// mosquitto_sub - t "/CMMCxPaperSignals/gearname/#" - h gb.netpie.io - i HSTPpOpb5wzGqNsU - u "6EiMMOxwOEcW7Cn" - P "gzaY6JlJ+0pl9xKJ3gTMo9gNOP8=" - p 1883 - d
#elif STRERCH
String DEVICE_NAME = "stretch";
String MQTT_HOST = "gb.netpie.io";
String MQTT_USERNAME = "6EiMMOxwOEcW7Cn";
String MQTT_PASSWORD = "+5/PkWnVFXyDIAYL/v9egCWzDXU=";
String MQTT_CLIENT_ID = "TdYl5qA5Y5swF3eG";
String MQTT_PREFIX = "/CMMCxPaperSignals/gearname/";
// mosquitto_sub - t "/CMMCxPaperSignals/gearname/#" - h gb.netpie.io - i TdYl5qA5Y5swF3eG - u "6EiMMOxwOEcW7Cn" - P "+5/PkWnVFXyDIAYL/v9egCWzDXU=" - p 1883 - d
#elif PANTS
String DEVICE_NAME = "pants";
String MQTT_HOST = "gb.netpie.io";
String MQTT_USERNAME = "6EiMMOxwOEcW7Cn";
String MQTT_PASSWORD = "gMOQoRYSCxzykmliRxxjOiSivb8=";
String MQTT_CLIENT_ID = "3NbBZk1qX8OKCUrx";
String MQTT_PREFIX = "/CMMCxPaperSignals/gearname/";
// mosquitto_sub - t "/CMMCxPaperSignals/gearname/#" - h gb.netpie.io - i 3NbBZk1qX8OKCUrx - u "6EiMMOxwOEcW7Cn" - P "gMOQoRYSCxzykmliRxxjOiSivb8=" - p 1883 - d
#elif COUNTDOWN
String DEVICE_NAME = "count";
String MQTT_HOST = "gb.netpie.io";
String MQTT_USERNAME = "6EiMMOxwOEcW7Cn";
String MQTT_PASSWORD = "ZDx9WRIjNAZGmUtSVRVr8M3htTw=";
String MQTT_CLIENT_ID = "zX1qQbCZoKKBXI5b";
String MQTT_PREFIX = "/CMMCxPaperSignals/gearname/";
// mosquitto_sub - t "/CMMCxPaperSignals/gearname/#" - h gb.netpie.io - i zX1qQbCZoKKBXI5b - u "6EiMMOxwOEcW7Cn" - P "ZDx9WRIjNAZGmUtSVRVr8M3htTw=" - p 1883 - d
#endif

/* WIFI INFO */
String WIFI_SSID = "ampere";
String WIFI_PASSWORD = "espertap";

int MQTT_PORT = 1883;
int PUBLISH_EVERY = 10L * 1000;
int MQTT_CONNECT_TIMEOUT = 10;
