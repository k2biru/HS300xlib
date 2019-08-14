#include "HS300xlib.h"

uint8 HS300xlib::MeasurementReq(){
    do
    {
        Wire.beginTransmission(HS300X_ADR);
        if (Wire.endTransmission(true) != 0) {
        return HS300X_ERROR_COLLISION_I2C;
        }
        if (_iteration>HS300X_MAX_ITERATION) return HS300X_ERROR_SENSOR_BUSY;
        _iteration++;
    } while (!_readSensor());
    _iteration=0;
    return HS300X_OK;
}
uint8_t HS300xlib::_readSensor(){
    uint16_t _rawTempMSB;
    uint16_t _rawTemp;
    uint16_t _rawHumMSB;
    uint16_t _rawHum;
    uint8_t  _rawStatus;
  
    Wire.requestFrom(HS300X_ADR, 4, true);        //true, stop message after transmission & releas the I2C bus
    if (Wire.available() != 4) {
        return 0;   
        }
    _rawHumMSB = Wire.read()<<8;  // MSB
    _rawHum  = Wire.read();       // LSB
    _rawTempMSB = Wire.read()<<8;
    _rawTemp= Wire.read();

    _rawHum |= _rawHumMSB;
    _rawTemp |= _rawTempMSB;
  
    _rawStatus = _rawTemp>>14;
    _rawHum = _rawHum& 0x3FFF; // mask 2 bit first
    _rawTemp = _rawTemp>>2;     // mask 2 bit last  
    _temperature = (_rawTemp* HS300X_TEMP_MULTY) - HS300X_TEMP_MIN;
    _humidity = _rawHum * HS300X_HUMD_MULTY;
    return _rawStatus+1;
}

float HS300xlib::getHumidity(){
    _iteration=0;
    return _humidity;
}
float HS300xlib::getTemperatureC(){
    _iteration=0;
    return _temperature;
}