/*
 * @title Nixie Clock ESP32
 * @version 0.1.0
 * @author: Tobias Wagner
 * @ide: Arduino 1.8.9
 * 
 * NTP time
 */

//#include <FastLED.h>
#include <Time.h>
#include <TimeLib.h>
#include <NTPClient.h>
#include <WiFi.h>
#include <Wire.h>

#define LED_PIN     2
#define NUM_LEDS    4
#define A1 25
#define B1 26
#define C1 27
#define D1 14
#define A2 12
#define B2 13
#define C2 15
#define D2 4
#define A3 16
#define B3 17
#define C3 5
#define D3 18
#define A4 19
#define B4 21
#define C4 22
#define D4 23
#define AUX_1 32
#define AUX_2 33

char A[4] = {A1, A2, A3, A4};
char B[4] = {B1, B2, B3, B4};
char C[4] = {C1, C2, C3, C4};
char D[4] = {D1, D2, D3, D4};

const char *ssid     = "YOUR_SSID";
const char *password = "YOUR_PW";

int zero;
int one;
int two;
int three;
int epochhour = 0;
int epochminute = 0;
int epochsec = 0;
unsigned long epoch = 1571270400;
unsigned long fetchedTime = 0;

int every_min = 0;

WiFiUDP udp;

NTPClient timeClient(udp, "europe.pool.ntp.org", 1*3600, 60000); //1* = GMT:+1

//CRGB leds[NUM_LEDS];
//CHSV colour( 0, 255, 180);


void setup(){
  pinMode(LED_PIN, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(B1, OUTPUT);
  pinMode(C1, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(B2, OUTPUT);
  pinMode(C2, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(B3, OUTPUT);
  pinMode(C3, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(B4, OUTPUT);
  pinMode(C4, OUTPUT);
  pinMode(D4, OUTPUT);
  for (char i = 0; i < 4; i++) {
    digitalWrite(A[i], HIGH);
    digitalWrite(B[i], HIGH);
    digitalWrite(C[i], HIGH);
    digitalWrite(D[i], HIGH);
  }
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  //FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  //FastLED.setBrightness(255);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("connected");

  timeClient.begin();
}


boolean summertime_EU(int year, byte month, byte day, byte hour, byte tzHours)
// European Daylight Savings Time calculation by "jurs" for German Arduino Forum
// input parameters: "normal time" for year, month, day, hour and tzHours (0=UTC, 1=MEZ)
// return value: returns true during Daylight Saving Time, false otherwise
{
  if (month<3 || month>10) return false; // keine Sommerzeit in Jan, Feb, Nov, Dez
  if (month>3 && month<10) return true; // Sommerzeit in Apr, Mai, Jun, Jul, Aug, Sep
  if (month==3 && (hour + 24 * day)>=(1 + tzHours + 24*(31 - (5 * year /4 + 4) % 7)) || month==10 && (hour + 24 * day)<(1 + tzHours + 24*(31 - (5 * year /4 + 1) % 7)))
    return true;
  else
    return false;
}


void loop() {

  //get time 
  timeClient.update();
  epoch = timeClient.getEpochTime();
  if (summertime_EU(year(epoch), month(epoch), day(epoch), hour(epoch), 1) == true)
  {
    epoch += 3600;
  }
  epochhour = (epoch  % 86400L) / 3600;
  epochminute =(epoch % 3600) / 60;
  epochsec =(epoch % 60);

  zero = (epochhour / 10) % 10;
  one = epochhour % 10;
  two =  (epochminute / 10) % 10;
  three = epochminute % 10;

  
  if (every_min != epochminute)
  {
    writenumber(0, zero);
    writenumber(1, one);
    writenumber(2, two);
    writenumber(3, three);
    Serial.print(zero);
    Serial.print(one);
    Serial.print(":");
    Serial.print(two);
    Serial.println(three);
    every_min = epochminute;
  }
  
  //FastLED.show();
  
}

void writenumber(int a, int b) {
  switch (b) {
    case 0:
      digitalWrite(A[a], LOW);
      digitalWrite(B[a], LOW);
      digitalWrite(C[a], LOW);
      digitalWrite(D[a], LOW);
      break;
    case 1:
      digitalWrite(A[a], HIGH);
      digitalWrite(B[a], LOW);
      digitalWrite(C[a], LOW);
      digitalWrite(D[a], LOW);
      break;
    case 2:
      digitalWrite(A[a], LOW);
      digitalWrite(B[a], HIGH);
      digitalWrite(C[a], LOW);
      digitalWrite(D[a], LOW);
      break;
    case 3:
      digitalWrite(A[a], HIGH);
      digitalWrite(B[a], HIGH);
      digitalWrite(C[a], LOW);
      digitalWrite(D[a], LOW);
      break;
    case 4:
      digitalWrite(A[a], LOW);
      digitalWrite(B[a], LOW);
      digitalWrite(C[a], HIGH);
      digitalWrite(D[a], LOW);
      break;
    case 5:
      digitalWrite(A[a], HIGH);
      digitalWrite(B[a], LOW);
      digitalWrite(C[a], HIGH);
      digitalWrite(D[a], LOW);
      break;
    case 6:
      digitalWrite(A[a], LOW);
      digitalWrite(B[a], HIGH);
      digitalWrite(C[a], HIGH);
      digitalWrite(D[a], LOW);
      break;
    case 7:
      digitalWrite(A[a], HIGH);
      digitalWrite(B[a], HIGH);
      digitalWrite(C[a], HIGH);
      digitalWrite(D[a], LOW);
      break;
    case 8:
      digitalWrite(A[a], LOW);
      digitalWrite(B[a], LOW);
      digitalWrite(C[a], LOW);
      digitalWrite(D[a], HIGH);
      break;
    case 9:
      digitalWrite(A[a], HIGH);
      digitalWrite(B[a], LOW);
      digitalWrite(C[a], LOW);
      digitalWrite(D[a], HIGH);
      break;
  }
}

void off(int a) {
  digitalWrite(A[a], HIGH);
  digitalWrite(B[a], HIGH);
  digitalWrite(C[a], HIGH);
  digitalWrite(D[a], HIGH);
}
