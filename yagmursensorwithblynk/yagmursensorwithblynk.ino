/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on ESP8266 chip.

  Note: This requires ESP8266 support package:
    https://github.com/esp8266/Arduino

  Please be sure to select the right ESP8266 module
  in the Tools -> Board menu!

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

/* Fill-in your Template ID (only if using Blynk.Cloud) */
#define BLYNK_TEMPLATE_ID   "TMPLO7zaat_c"

#include <Servo.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
// Your WiFi credentials.
// Set password to "" for open networks.

Servo sg90;
char auth[] = "aJ0d2gd2kiVQhq4RzbJhgTMyKRLiWhYZ";//Enter your Auth token
char ssid[] = "Redmi Note 7";//Enter your WIFI name
char pass[] = "derssifresi";//Enter your WIFI password

BlynkTimer timer;
int rainSensor;
const byte d1=5;
const byte d0=16;
const byte d3=0;
int s0=180;
BLYNK_WRITE(V1){
  s0 = param.asInt();
  sg90.write(s0);
  Blynk.virtualWrite(V1,s0);
  }

void moisture() {
  rainSensor = analogRead(A0);
  rainSensor = map(rainSensor, 0, 1023, 0, 1023);
  Blynk.virtualWrite(V0, rainSensor);
  Serial.println(rainSensor);
}

int sayac=0;
int sayac2=0;
bool flag;

void setup()
{
  flag = true;
  // Debug console
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(100L, moisture);
  sg90.attach(D2);//servoyu bağladığın pin
  sg90.write(s0);
  pinMode(d0,OUTPUT);
  pinMode(d1,OUTPUT);
  pinMode(d3,OUTPUT);
}
bool isRain=false;
void loop()
{
 Blynk.run();
  timer.run();
  
  if(rainSensor<=500){
     isRain=true;
    if(sayac<5 && s0>150){
      sayac++;
      digitalWrite(d1,HIGH);
      digitalWrite(d3,HIGH);
      delay(500);
     digitalWrite(d3,LOW);
     digitalWrite(d1,LOW);
      delay(500);
      }
    }else{
      isRain=false;
        sayac=0;
        digitalWrite(d1,LOW);
        flag=true;
        }
      
     if(s0<30 && sayac2<2){
      sayac2++;
      digitalWrite(d0,HIGH);
      delay(500);
      digitalWrite(d0,LOW);
      delay(500);
      }else if(!isRain){
        sayac2=0;
        digitalWrite(d0,LOW);
        flag=false;        
        }   
      
}
