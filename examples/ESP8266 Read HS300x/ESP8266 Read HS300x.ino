#include <Arduino.h>
#include <Wire.h>    // Using Wire Library
#include <HS300xlib.h>
#define SDA     12
#define SCL     2
#define UPDATE_TIME 10000    // get data every 10 sec

HS300xlib hs300x;  // create class

uint32_t CounterTemperature = 0;
void setup(){
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.println("Im Ready");

  Wire.begin(SDA,SCL); // begin I2C 
  // Wire.begin();  // use Wire.begin(); for AVR Base (Arduino mini, Uno)            
}

void loop(){

  uint32_t now = millis();
	if (now - CounterTemperature > UPDATE_TIME) {
    uint8 respon = hs300x.MeasurementReq();
    if(respon){
        CounterTemperature = now;
        //Serial.print("status ="); Serial.println(respon);  // respon to see Sensor condition
        Serial.print("Humidity ");Serial.print(hs300x.getHumidity());
        Serial.print("Temperature ");Serial.println(hs300x.getTemperatureC());
    }
  }
}
