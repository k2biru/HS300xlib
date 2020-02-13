/*
 *  HS300x Relative Humidity and Temperature Sensor 
 *  datasheet : https://www.idt.com/document/dst/hs300x-datasheet
 *  Fahrizal Hari Utama
 *  Wednesday Legi [2019.08.14]
 *  board ESP8266
*/
#ifndef DEF_HS300X_H
#define DEF_HS300X_H

#define HS300X_ADR  0x44                        // look at datasheet
#define HS300X_TEMP_MULTY           0.010071415 // look at datasheet
#define HS300X_TEMP_MIN             40          // look at datasheet
#define HS300X_HUMD_MULTY           0.006163516 // look at datasheet
#define HS300X_MAX_ITERATION        100
#define HS300X_DELAY_MEASUREMENT    35          // typical on datasheet 16.90 ms, rounded up a little (35ms = 1 try)
#define HS300X_DELAY_ITERATION      1

#define HS300X_STALE_DATA           2
#define HS300X_OK                   1
#define HS300X_ERROR_SENSOR_BUSY    0
#define HS300X_ERROR_COLLISION_I2C  -1


#include <Arduino.h>
#include <Wire.h>

class HS300xlib {
    private :
    float _humidity;
    float _temperature;
    uint8_t _status;
    uint8_t _readSensor();


    public:
    int8_t MeasurementReq();
    const float getTemperatureC();
    const float getHumidity();
};

#endif //DEF_HS300X_H
