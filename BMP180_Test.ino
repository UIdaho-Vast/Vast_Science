
\\ Import Libraries
#include <Wire.h> // For I2C connection
#include <Adafruit_Sensor.h> // Unified Adafruit Sensor reader
#include <Adafruit_BMP085_U.h> // Specifies what sensor we are using


\\ no idea what this does
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

void setup(){

  Serial.begin(9600);
  while(!Serial){;}

  /* Initialise the sensor */
  if(!bmp.begin())
  {
    /* There was a problem detecting the BMP085 ... check your connections */
    Serial.print("Ooops, no BMP085 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

  Serial.print("Output of bmp.begin: ");
  Serial.print(bmp.begin);
}

void loop(){

  /* Get a new sensor event */
  sensors_event_t event;
  bmp.getEvent(&event);

  /* Display the results (barometric pressure is measure in hPa) */
  if (event.pressure)
  {
    /* Display atmospheric pressue in hPa */
    Serial.print("Pressure:    ");
    Serial.print(event.pressure);
    Serial.println(" hPa");

    float temperature;
    bmp.getTemperature(&temperature);
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" C");
}