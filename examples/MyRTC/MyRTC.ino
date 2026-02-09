#include "MyDS1302.h"

//Pin definition
#define CE_PIN   5    
#define IO_PIN   21  
#define SCLK_PIN 22 

MyDS1302 rtc(CE_PIN, IO_PIN, SCLK_PIN);

void setup() {
  Serial.begin(115200);
  delay(1000); 
  
  Serial.println("=== Test DS1302 ===");
  Serial.printf("Pin: CE=%d, IO=%d, SCLK=%d\n", CE_PIN, IO_PIN, SCLK_PIN);
  
  // Initialize
  rtc.begin();
  
  // Test communication
  Serial.println("Test communication...");
  if (rtc.testCommunication()) {
    Serial.println("✓ Communication OK");
  } else {
    Serial.println("✗ Communication failed");
  }
  
  // Dump registers before modification
  Serial.println("\nPre-writing registers:");
  rtc.dumpAllRegisters();
  
  // Set the time
  // Serial.println("\nSetting the time...");
  // rtc.setDateTime(0, 30, 21, 7, 2, 24); // 20:00:05 07/02/2024
  
  delay(100);
  
  // Dump after writing
  Serial.println("\nRegistres après écriture:");
  rtc.dumpAllRegisters();
  
  Serial.println("\nLecture en continu:");
}

void loop() {
  // Read and display with debug
  uint8_t second, minute, hour, day, month, year;
  rtc.readDateTime(second, minute, hour, day, month, year);
  
  Serial.printf("Heure: %02d/%02d/%02d %02d:%02d:%02d\n", 
                day, month, year, hour, minute, second);
  
  delay(1000);
}