#include "HS300xlib.h"

int8_t HS300xlib::MeasurementReq(){
    int8_t _status = 0;
    uint8_t _iteration = 0;
    Wire.beginTransmission(HS300X_ADR);
    if (Wire.endTransmission(true) != 0) {
        return HS300X_ERROR_COLLISION_I2C;
    }
    delay(HS300X_DELAY_MEASUREMENT);
    do {
       _status = _readSensor();     
       _iteration ++;
       if (_iteration > HS300X_MAX_ITERATION) return HS300X_ERROR_SENSOR_BUSY;   
       delay(HS300X_DELAY_ITERATION);
    } while (!_status);
    return _status;
}
uint8_t HS300xlib::_readSensor(){
    uint16_t _rawTempMSB;
    uint16_t _rawTemp;
    uint16_t _rawHumMSB;
    uint16_t _rawHum;
    uint8_t  _rawStatus;
  
    Wire.requestFrom(HS300X_ADR, 4, 1);        //true, stop message after transmission & releas the I2C bus
    if (Wire.available() != 4) {
        return 0;   
        }
    _rawHumMSB = Wire.read() << 8;  // MSB
    _rawHum  = Wire.read();       // LSB
    _rawTempMSB = Wire.read() << 8;
    _rawTemp= Wire.read();

    _rawHum |= _rawHumMSB;
    _rawTemp |= _rawTempMSB;
  
    _rawStatus = _rawTemp >> 14;
    _rawHum = _rawHum & 0x3FFF; // mask 2 bit first
    _rawTemp = _rawTemp >>2;     // mask 2 bit last  
    if (_rawHum == 0x3FFF) return 0;
    if (_rawTemp == 0x3FFF) return 0;
    _temperature = (_rawTemp* HS300X_TEMP_MULTY) - HS300X_TEMP_MIN;
    _humidity = _rawHum * HS300X_HUMD_MULTY;
    return _rawStatus + 1;
}

const float HS300xlib::getHumidity(){
    return _humidity;
}
const float HS300xlib::getTemperatureC(){
    return _temperature;
}
