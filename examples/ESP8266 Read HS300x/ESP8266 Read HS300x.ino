#include <Arduino.h>
#include <Wire.h>
#include <HS300xlib.h>
#define SDA     12
#define SCL     2

HS300xlib hs300x;


void setup(){
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.println("Im Ready");

  Wire.begin(SDA,SCL);
}

void loop(){

    uint8 respon = hs300x.MeasurementReq();
    if(respon){
        Serial.print("Humidity ");Serial.print(hs300x.getHumidity());
        Serial.print(" Temperature ");Serial.println(hs300x.getTemperatureC());
    }
    //Serial.print("Respon ");Serial.println(respon);
    delay(100);
}
