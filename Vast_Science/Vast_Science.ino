/*
Written By: Seth Berryhill
October 2017

Arduino Uno
http://www.ladyada.net/make/gpsshield
  -----------------------------------------------------*/

#include <Servo.h>
#include <SD.h> // SD read-write
#include <SPI.h> // Master-Slave; NOT USED
#include <Wire.h> // For I2C connection
#include <Adafruit_Sensor.h> // Unified Adafruit Sensor reader
#include <Adafruit_BMP085_U.h> // Specifies what sensor we are using

// Servo variables
Servo servo;
#define SERVOPIN 6
unsigned long time, refreshtime;

// creates an object for the sensor
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

// Defining pins for GPS Shield functions
#define greenled 5
#define redled 6
#define sd 10

// defining Sensor Pins
#define voltagepin 0
#define humiditypin 1

//I2C Pins are defined by the board
//SDA -> A4
//SCL -> A5

char filename[]="data.csv";

void setup() {
  Serial.begin(9600);
  // For some reason it kept hanging here, but works fine without it
  /*while (!Serial) {
    ;
  }*/

  // Servo delay variables
servo.attach(SERVOPIN);
time=millis();
refreshtime=millis();

  /* Initialise BMP180 */
  if(!bmp.begin())
  {
    /* There was a problem detecting the BMP085 ... check your connections */
    Serial.print("Ooops, no BMP085 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

  // Initialise SD card
  pinMode( sd, OUTPUT );
  if (!SD.begin(sd)) {
    Serial.println("Card init. failed!");
  }
}

void loop() {

  // Getting some sensor data
  File dataFile  = SD.open(filename,FILE_WRITE);
  uint32_t t   = millis();
    int volt        = analogRead(voltagepin);
  int humidity = analogRead(humiditypin);

  /* Get a new sensor event */
  sensors_event_t event;
  bmp.getEvent(&event);

  //Getting I2C Data
  // This is the example syntax, maybe works
  //if(event.pressure){
  float pressure = event.pressure;
  float temperature;
  bmp.getTemperature(&temperature);
  //}

  dataFile.print(t);
  dataFile.print(",");
  dataFile.print(pressure);
  dataFile.print(",");
  dataFile.print(temperature);
  dataFile.print(",");
  dataFile.print(volt);
  dataFile.print(",");
  dataFile.println(humidity);
  dataFile.close();

  Serial.print(t);
  Serial.print(",");
  Serial.print(pressure);
  Serial.print(",");
  Serial.print(temperature);
  Serial.print(",");
  Serial.print(volt);
  Serial.print(",");
  Serial.println(humidity);

  delay(1000);

  imaging();

}

void imaging() {

 if((millis()-time)<10000)
{
   servo.write(0);
}

else if(((millis()-time)>10000)&&((millis()-time)<20000))
{
   servo.write(90);
}

else if(((millis()-time)>20000)&&((millis()-time)<30000))
{
   servo.write(180);
}

else
{
   time=millis();
}

}