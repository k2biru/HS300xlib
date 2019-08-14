/*
 *  HS300x Relative Humidity and Temperature Sensor 
 *  datasheet : https://www.idt.com/document/dst/hs300x-datasheet
 *  Fahrizal Hari Utama
 *  Wednesday Legi [2019.08.14]
 *  board ESP8266
*/
#define HS300X_ADR  0x44
#define HS300X_TEMP_MULTY  0.010071415
#define HS300X_TEMP_MIN  40
#define HS300X_HUMD_MULTY  0.006163516
#define HS300X_MAX_ITERATION     10

#define HS300X_OK    1
#define HS300X_ERROR_SENSOR_BUSY    0
#define HS300X_ERROR_COLLISION_I2C  -1


#include <Arduino.h>
#include <Wire.h>

class HS300xlib {
    private :
    float _humidity;
    float _temperature;
    uint8_t _iteration;
    uint8_t _status;
    uint8_t _readSensor();


    public:
    uint8 MeasurementReq();
    float getTemperatureC();
    float getHumidity();
};
