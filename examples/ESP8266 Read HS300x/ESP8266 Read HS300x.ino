#include <Arduino.h>
#include <Wire.h>
#include <HS300xlib.h>
#define SDA     12
#define SCL     2
#define UPDATE_TIME 10000

HS300xlib hs300x;

uint32_t CounterSuhu =0;


void setup(){
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.println("Im Ready");

  Wire.begin(SDA,SCL);
}

void loop(){

  uint32_t now = millis();
	if (now - CounterSuhu > UPDATE_TIME) {
    uint8 respon = hs300x.MeasurementReq();
    if(respon){
        CounterSuhu = now;
        //Serial.print("status ="); Serial.println(respon);
        Serial.print("Humidity ");Serial.print(hs300x.getHumidity());
        Serial.print(" Temperature ");Serial.println(hs300x.getTemperatureC());
    }
  }
}