#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Ticker.h>

#include <TM1637Display.h> //https://github.com/avishorp/TM1637
#include <NTPClient.h> //https://github.com/arduino-libraries/NTPClient
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager

// Module connection pins (Digital Pins)
#define CLK D2
#define DIO D1

// The amount of time (in milliseconds) between tests
#define TEST_DELAY   2000

const uint8_t SEG_DONE[] = {
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,           // d
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
  SEG_C | SEG_E | SEG_G,                           // n
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G            // E
  };

const uint8_t SEG_Err[] = {
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G,            // E
  SEG_E | SEG_G,           // r
  SEG_E | SEG_G,           // r
  0
  };

const uint8_t SEG_Underscore[] = {
  SEG_D ,           // _
  SEG_D ,           // _
  SEG_D ,           // _
  SEG_D ,           // _
};

TM1637Display display(CLK, DIO);
Ticker clockInterrupt;
WiFiUDP ntpUDP;
// By default 'pool.ntp.org' is used with 60 seconds update interval and
// no offset
//NTPClient timeClient(ntpUDP);
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 60*60*1000);
char dots = 0b0;

void setup(){  
  display.setBrightness(0x0f);
  display.setSegments(SEG_Underscore);
  
  Serial.begin(115200);
  Serial.println ( "start");

  //WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wm;
  
  //reset settings - wipe credentials for testing
  //wm.resetSettings();

  // Automatically connect using saved credentials,
  // if connection fails, it starts an access point with the specified name,
  // then goes into a blocking loop awaiting configuration and will return success result
  bool res;
  res = wm.autoConnect("miniclock"); // open AP

  if(!res) {
    Serial.println("Failed to connect");
    wm.resetSettings();
    display.setSegments(SEG_Err);  
  } else {
    //if you get here you have connected to the WiFi    
    Serial.println ( "wifi connected !");
    display.setSegments(SEG_DONE);  
    timeClient.begin();
    timeClient.forceUpdate();
    clockInterrupt.attach(1, updateClock); 
  }
}

void updateClock(){
  timeClient.update();
  int t = timeClient.getHours() * 100 + timeClient.getMinutes();
  display.showNumberDecEx(t,  dots, true);
  dots = dots^  0b01000000;

  // poor man's brightness adjustment
  int k=7;
  switch (timeClient.getHours()){
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
      k=2;
      break;
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
      k=7;
      break;
    case 20:
    case 21:
    case 22:
    case 23:
      k=2;
      break;    
  }
  display.setBrightness(k);
  delay(1000);
}

void loop(){ }
