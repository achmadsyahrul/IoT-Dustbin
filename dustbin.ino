#define BLYNK_PRINT Serial


#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
//sKv2RCkQ8nYy0tuYMuyrQSlDdIDQJ1S9
//XvC-ObzuTQg4zwoqmXHFpzF8WWumFNGj
char auth[] = "XvC-ObzuTQg4zwoqmXHFpzF8WWumFNGj";
char ssid[] = "realmeC15";
char pass[] = "xxxxxxxx";

#include <SoftwareSerial.h>
SoftwareSerial EspSerial(2,3); // RX, TX

#define ESP8266_BAUD 9600

ESP8266 wifi(&EspSerial);

BlynkTimer timer;

#include <Servo.h>

int time, waktu;
int distance, jarak;

int pos = 0;

int on = 1;

Servo servo_5;

void setup()
{
  // Debug console
  Serial.begin(9600);

  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

//  Blynk.begin(auth, wifi, ssid, pass);
  // You can also specify server:
  Blynk.begin(auth, wifi, ssid, pass, "blynk-cloud.com", 8080);

  timer.setInterval(1000L, myTimerEvent);

  pinMode(9, OUTPUT);
  pinMode(8, INPUT);
  pinMode(13, OUTPUT);
  pinMode(12, INPUT); 
  servo_5.attach(5, 500, 2500);

  pinMode(10,OUTPUT);
}

BLYNK_WRITE(V0){
  int pinValue = param.asInt();
  if(pinValue == 1){
    on = 1;
  }
  if(pinValue == 0){
    digitalWrite(10,LOW);
    on = 0;
    Blynk.virtualWrite(V0, 0);
  }
}

void myTimerEvent()
{
  digitalWrite(9, HIGH);
  delayMicroseconds(10);
  digitalWrite(9, LOW);
  time = pulseIn(8, HIGH);
  distance = (time * 0.034) / 2;
  int persen = 11 - distance;
  if(persen<0) persen = 0;
  else if(persen>10) persen = 10;
  persen = persen * 10;
  String persentase;
  if(persen==0)
  persentase = "0%";
  if(persen==10)
  persentase = "10%";
  if(persen==20)
  persentase = "20%"; 
  if(persen==30)
  persentase = "30%";
  if(persen==40)
  persentase = "40%";
  if(persen==50)
  persentase = "50%";
  if(persen==60)
  persentase = "60%"; 
  if(persen==70)
  persentase = "70%";
  if(persen==80)
  persentase = "80%";  
  if(persen==90)
  persentase = "90%";
  if(persen==100)
  persentase = "100%";
  if(persen>70 && on==1){
      digitalWrite(10,HIGH);
      Blynk.virtualWrite(V0, 1);
  }
  else{
      digitalWrite(10,LOW);
      Blynk.virtualWrite(V0, 0);
  }
  Blynk.virtualWrite(V5, distance);
  Blynk.virtualWrite(V1, distance);
  Blynk.virtualWrite(V2, "Kapasitas");
  Blynk.virtualWrite(V3, persentase);
}

void loop()
{
  digitalWrite(13, HIGH);
  delayMicroseconds(10);
  digitalWrite(13, LOW);
  waktu = pulseIn(12, HIGH);
  jarak = (waktu * 0.034) / 2;
  if(jarak <= 10){
    for (pos = 90; pos >= 0; pos -= 1) {
    servo_5.write(pos);
    delay(5);
  }
  delay(3000);
  for (pos = 0; pos <= 90
  ; pos += 1) {
    servo_5.write(pos);
    delay(5);
  }

    delay(1000);
  }

    delay(1000);
  Blynk.run();
  timer.run();
  
}
