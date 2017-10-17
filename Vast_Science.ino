#include <SD.h>
#include <SPI.h>

#define lightpin 0
#define pressurepin 3
#define chipSelect 10

int geiger = 0;
char filename[]="data.csv";

void setup() {
  Serial.begin(9600);
  pinMode( chipSelect, OUTPUT );
  if (!SD.begin(chipSelect)) {
    Serial.println("Card init. failed!");
  }
}
void loop() {
  delay(1000);
  File dataFile = SD.open(filename,FILE_WRITE);
  uint32_t m=millis();
  int light = analogRead(lightpin);
  int pressure = analogRead(pressurepin);
 // if ( Serial.available() > 0 )
  //{
    geiger = Serial.read();
  //}
  
  dataFile.print(m);
  dataFile.print(",");
  dataFile.print(light);
  dataFile.print(",");
  dataFile.print(geiger);
  dataFile.print(",");
  dataFile.println(pressure);
  dataFile.close();
  Serial.println(geiger);
}

