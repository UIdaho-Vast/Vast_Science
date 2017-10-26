/*
Written By: Seth Berryhill
October 2017

Arduino Uno
http://www.ladyada.net/make/gpsshield
  -----------------------------------------------------*/

#include <SD.h>
#include <SPI.h>

#define greenled 5
#define redled 6
#define pressurepin 7
#define temppin 8
#define voltagepin 9
#define sd 10
#define humiditypin 11
#define magnetpin 12

char filename[]="data.csv";

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }

  pinMode( sd, OUTPUT );
  if (!SD.begin(sd)) {
    Serial.println("Card init. failed!");
  }
}

void loop() {
  delay(2800);
  File dataFile  = SD.open(filename,FILE_WRITE);
  uint32_t t   = millis();
  int pressure  = analogRead(pressurepin);
  int temp      = analogRead(temppin);
  int volt        = analogRead(voltagepin);
  int humidity = analogRead(humiditypin);
  int magnet   = analogRead(magnetpin);

  digitalWrite(redled, HIGH);
  dataFile.print(t);
  dataFile.print(",");
  dataFile.print(pressure);
  dataFile.print(",");
  dataFile.print(temp);
  dataFile.print(",");
  dataFile.print(volt);
  dataFile.print(",");
  dataFile.print(humidity);
  dataFile.print(",");
  dataFile.println(magnet);
  dataFile.close();
  Serial.println(t);
  delay(200);
  digitalWrite(redled,LOW);
}