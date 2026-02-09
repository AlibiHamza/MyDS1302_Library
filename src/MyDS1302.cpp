#include "MyDS1302.h"

MyDS1302::MyDS1302(uint8_t cePin, uint8_t ioPin, uint8_t sclkPin) {
  _cePin = cePin;
  _ioPin = ioPin;
  _sclkPin = sclkPin;    
}

void MyDS1302::begin(){
  pinMode(_cePin, OUTPUT);
  pinMode(_sclkPin, OUTPUT);
  pinMode(_ioPin, INPUT_PULLUP);
  digitalWrite(_cePin, LOW);
  digitalWrite(_sclkPin, LOW);  
  delay(10); 
}

uint8_t MyDS1302::_bcdToDec(uint8_t bcd) {
  return ((bcd / 16) * 10) + (bcd % 16);
}

uint8_t MyDS1302::_decToBcd(uint8_t dec) {
  return ((dec / 10) << 4) | (dec % 10);
}

void MyDS1302::_writeByte(uint8_t data) {
  pinMode(_ioPin, OUTPUT);
  for (int i = 0; i < 8; i++) {
    digitalWrite(_ioPin, data & 0x01);
    digitalWrite(_sclkPin, HIGH);
    delayMicroseconds(1);
    digitalWrite(_sclkPin, LOW);
    delayMicroseconds(1);
    data >>= 1;
  }
  pinMode(_ioPin, INPUT_PULLUP); // Retour en entrée
}

void MyDS1302::_writeRegister(uint8_t reg, uint8_t data) {
  digitalWrite(_cePin, HIGH);  // Active le DS1302
  _writeByte(reg);             // Adresse du registre
  _writeByte(data);            // Donnée à écrire
  digitalWrite(_cePin, LOW);   // Désactive
}

void MyDS1302::setDateTime(uint8_t second, uint8_t minute, uint8_t hour,
                           uint8_t day, uint8_t month, uint8_t year) {
  // Désactiver la protection en écriture
  _writeRegister(0x8E, 0x00);
  
  // Démarrer l'horloge (bit CH=0)
  _writeRegister(0x80, _decToBcd(second) & 0x7F);
  
  // Écrire les autres registres
  _writeRegister(0x82, _decToBcd(minute));
  _writeRegister(0x84, _decToBcd(hour));
  _writeRegister(0x86, _decToBcd(day));
  _writeRegister(0x88, _decToBcd(month));
  _writeRegister(0x8A, 0x01); 
  _writeRegister(0x8C, _decToBcd(year));
  
  // Réactiver la protection
  _writeRegister(0x8E, 0x80);

  delay(10); // Délai pour s'assurer de l'écriture
}

uint8_t MyDS1302::_readByte() {
  uint8_t data = 0;
  pinMode(_ioPin, INPUT_PULLUP);
  
  for (int i = 0; i < 8; i++) {
    data >>= 1;  // Décale pour préparer le prochain bit
    if (digitalRead(_ioPin)) {
      data |= 0x80;  // Met le bit MSB à 1 si IO=HIGH
    }
    digitalWrite(_sclkPin, HIGH);
    delayMicroseconds(1);
    digitalWrite(_sclkPin, LOW);
    delayMicroseconds(1);
  }
  return data;
}

uint8_t MyDS1302::_readRegister(uint8_t reg) {
  digitalWrite(_cePin, HIGH);
  _writeByte(reg | 0x01);  // Adresse + bit READ (1)
  uint8_t data = _readByte();
  digitalWrite(_cePin, LOW);
  return data;
}

void MyDS1302::readDateTime(uint8_t &second, uint8_t &minute, uint8_t &hour,
                            uint8_t &day, uint8_t &month, uint8_t &year) {

  // Lire tous les registres
  uint8_t sec_reg = _readRegister(0x81);
  uint8_t min_reg = _readRegister(0x83);
  uint8_t hour_reg = _readRegister(0x85);
  uint8_t day_reg = _readRegister(0x87);
  uint8_t month_reg = _readRegister(0x89);
  uint8_t year_reg = _readRegister(0x8D);

  second = _bcdToDec(_readRegister(0x81) & 0x7F);
  minute = _bcdToDec(_readRegister(0x83));
  hour = _bcdToDec(_readRegister(0x85) & 0x3F);
  day = _bcdToDec(_readRegister(0x87));
  month = _bcdToDec(_readRegister(0x89));
  year = _bcdToDec(_readRegister(0x8D));

  // Debug: afficher les valeurs brutes
  Serial.printf("Debug - Raw: sec=0x%02X min=0x%02X hour=0x%02X day=0x%02X month=0x%02X year=0x%02X\n",
                sec_reg, min_reg, hour_reg, day_reg, month_reg, year_reg);
}

String MyDS1302::getDateTimeString() {
  uint8_t second, minute, hour, day, month, year;
  readDateTime(second, minute, hour, day, month, year);
  
  char buffer[20];
  sprintf(buffer, "%02d/%02d/%02d %02d:%02d:%02d", 
          day, month, year, hour, minute, second);
  return String(buffer);
}

// Ajout de fonctions de debug
bool MyDS1302::testCommunication() {
  // Essayer de lire le registre de contrôle
  uint8_t control = _readRegister(0x8E);
  Serial.printf("Registre contrôle (0x8E): 0x%02X\n", control);
  return (control == 0x80 || control == 0x00); // Accepte protégé ou non protégé
}

void MyDS1302::dumpAllRegisters() {
  Serial.println("Dump de tous les registres:");
  for (uint8_t i = 0x80; i <= 0x8F; i++) {
    if (i % 2 == 1) { // Seulement les registres impairs (lecture)
      uint8_t val = _readRegister(i & 0xFE); // Convertir en adresse paire
      Serial.printf("0x%02X: 0x%02X ", i, val);
      if ((i - 0x80) % 4 == 3) Serial.println();
    }
  }
  Serial.println();
}