#ifndef MyDS1302_h
#define MyDS1302_h

#include <stdint.h>
#include <Arduino.h>

class MyDS1302 {
    public:        
        // Constructor with pins
        MyDS1302(uint8_t cePin, uint8_t ioPin, uint8_t sclkPin);
        // Public method
        void begin();
        void setDateTime(uint8_t second, uint8_t minute, uint8_t hour,
                     uint8_t day, uint8_t month, uint8_t year);
        void readDateTime(uint8_t &second, uint8_t &minute, uint8_t &hour,
                      uint8_t &day, uint8_t &month, uint8_t &year);
        String getDateTimeString();
        bool testCommunication();
        void dumpAllRegisters();

    private:
        // Private methods
        uint8_t _decToBcd(uint8_t dec);
        uint8_t _bcdToDec(uint8_t bcd);
        void _writeByte(uint8_t data);
        uint8_t _readByte();
        void _writeRegister(uint8_t reg, uint8_t data);
        uint8_t _readRegister(uint8_t reg);

        // Pins
        uint8_t _cePin;
        uint8_t _ioPin;
        uint8_t _sclkPin; 
};
#endif