
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
 
 
/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "Krishna"
#define WLAN_PASS       "123456789"

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "krishna_123"
#define AIO_KEY         "7f258d8d1eb24130b48e844be1f41542"

/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/

// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
Adafruit_MQTT_Subscribe front = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Front");
Adafruit_MQTT_Subscribe back = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/backward");
Adafruit_MQTT_Subscribe left = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/left");
Adafruit_MQTT_Subscribe right = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Right");
Adafruit_MQTT_Subscribe hello = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Pump");
/*************************** Sketch Code ************************************/

// Bug workaround for Arduino 1.6.6, it seems to need a function declaration
// for some reason (only affects ESP8266, likely an arduino-builder bug).
void MQTT_connect();
void setup() {
  Serial.begin(115200);
  pinMode(D0,OUTPUT);
  pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);
  pinMode(D3,OUTPUT);
  pinMode(D4,OUTPUT);
  pinMode(D5,OUTPUT);
  pinMode(D6,OUTPUT);
  pinMode(D7,INPUT);
  pinMode(D8,OUTPUT);
 // pinMode(D9,OUTPUT);
  //pinMode(D10,OUTPUT);
        digitalWrite(D3,0);
        digitalWrite(D4,0);
        digitalWrite(D5,0);
        digitalWrite(D6,0);
        //digitalWrite(D7,0);
        digitalWrite(D8,0);
        digitalWrite(D1,0);
        digitalWrite(D2,0);
        digitalWrite(D0,1);
  Serial.println(F("Adafruit MQTT demo"));
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(400);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  // Setup MQTT subscription for onoff feed.
  mqtt.subscribe(&front);
  mqtt.subscribe(&back);
  mqtt.subscribe(&left);
  mqtt.subscribe(&right);
   mqtt.subscribe(&hello);
}

uint32_t x=0;

void loop() {
  
  if(D7==1)
  {
    Serial.println("detected!");
    digitalWrite(D8,HIGH);
    delay(3000);
    digitalWrite(D8,LOW);
  }
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below .
  MQTT_connect();

  // this is our 'wait for incoming subscription packets' busy subloop
  // try to spend your time here

  Adafruit_MQTT_Subscribe *subscription;

  while ((subscription = mqtt.readSubscription(4000))) {
    if (subscription == &front) {
      Serial.print(F("Got front: "));
      Serial.println((char *)front.lastread);
      uint16_t num=atoi((char *)front.lastread);
      Serial.println(num);
      if(num==0)
      {
       digitalWrite(D3,1);
       digitalWrite(D4,0);
       digitalWrite(D6,0);
       digitalWrite(D5,1);
       delay(6000);
       digitalWrite(D3,0);
       digitalWrite(D4,0);
       digitalWrite(D5,0);
       digitalWrite(D6,0);
        
       Serial.println("forward");
      }
      else
      {
        digitalWrite(D3,0);
        digitalWrite(D4,0);
        digitalWrite(D5,0);
        digitalWrite(D6,0);
        //digitalWrite(D7,0);
        digitalWrite(D8,0);
        digitalWrite(D1,0);
        digitalWrite(D2,0);
        Serial.println("no forward");
      }
    }
      else if(subscription == &back)
      {
         Serial.print(F("Got back: "));
      Serial.println((char *)back.lastread);
      uint16_t num=atoi((char *)back.lastread);
      Serial.println(num);
     if(num==0)
     {
       digitalWrite(D3,0);
       digitalWrite(D4,1);
       digitalWrite(D5,0);
       digitalWrite(D6,1);
       delay(6000);
       digitalWrite(D3,0);
       digitalWrite(D4,0);
       digitalWrite(D5,0);
       digitalWrite(D6,0);  
      }
     else
     {
       digitalWrite(D0,0);
       digitalWrite(D1,0);
       digitalWrite(D2,0);
       digitalWrite(D3,0);
       digitalWrite(D4,0);
       digitalWrite(D5,0);
       digitalWrite(D6,0);
       digitalWrite(D7,0);
       delay(4000);
     }
     }
    
      
       else if(subscription == &left)
      {
         Serial.print(F("Got left: "));
      Serial.println((char *)left.lastread);
      uint16_t num=atoi((char *)left.lastread);
      Serial.println(num);
      if(num==0)
      {
       analogWrite(D3,270);
      digitalWrite(D4,0);
       digitalWrite(D5,0);
      analogWrite(D6,270);
      delay(7000);
       digitalWrite(D3,0);
      digitalWrite(D4,0);
       digitalWrite(D5,0);
      digitalWrite(D6,0);
      Serial.println("left");
      
      /*digitalWrite(D3,1);
      digitalWrite(D4,0);
       digitalWrite(D5,1);
      digitalWrite(D6,0);
      digitalWrite(D7,0);
      digitalWrite(D8,400); 
        delay(400);
        digitalWrite(D1,400);
        digitalWrite(D2,0);
        delay(400);
        digitalWrite(D7,400);
        digitalWrite(D8,0); 
        delay(400);
        digitalWrite(D7,0);
        digitalWrite(D8,400); 
        delay(400);
      */
      }
      else
      {
        digitalWrite(D3,0);
        digitalWrite(D4,0);
        digitalWrite(D5,0);
        digitalWrite(D6,0);
         digitalWrite(D7,0);
        digitalWrite(D8,0);
        digitalWrite(D1,0);
        digitalWrite(D2,0);
     delay(4000);
      }
     
      }
       else if(subscription == &right)
      {
         Serial.print(F("Got Right: "));
      Serial.println((char *)right.lastread);
      uint16_t num=atoi((char *)right.lastread);
       Serial.println(num);
       if(num==0)
       {
        digitalWrite(D3,0);
        analogWrite(D4,270);
        analogWrite(D5,270);
        digitalWrite(D6,0);
        delay(5000);
        digitalWrite(D3,0);
        digitalWrite(D4,0);
        digitalWrite(D5,0);
        digitalWrite(D6,0);
      
       }
       else
       {
        digitalWrite(D3,0);
        digitalWrite(D4,0);
        digitalWrite(D5,0);
        digitalWrite(D6,0);
         digitalWrite(D7,0);
        digitalWrite(D8,0);
        digitalWrite(D1,0);
        digitalWrite(D2,0);
       delay(4000);
      
       }
       
}
     else if(subscription == &hello)
      {
         Serial.print(F("Got Hello: "));
      Serial.println((char *)hello.lastread);
      uint16_t num=atoi((char *)hello.lastread);
      Serial.println(num);
      if(num==1)
      {
       Serial.println("pump on");
       digitalWrite(D0,0);
       delay(3000);
      }
      else
      {
          digitalWrite(D0,1);
      }
          
      }
  }
}

void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(4000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically  die and wait for WDT to reset me
         while (1);
       }
  }

  
  Serial.println("MQTT Connected!");
 
}
