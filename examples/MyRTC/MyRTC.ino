#include "MyDS1302.h"

// Définition des broches
#define CE_PIN   5    
#define IO_PIN   21  
#define SCLK_PIN 22 

MyDS1302 rtc(CE_PIN, IO_PIN, SCLK_PIN);

void setup() {
  Serial.begin(115200);
  delay(1000); 
  
  Serial.println("=== Test DS1302 ===");
  Serial.printf("Broches: CE=%d, IO=%d, SCLK=%d\n", CE_PIN, IO_PIN, SCLK_PIN);
  
  // Initialiser
  rtc.begin();
  
  // Tester la communication
  Serial.println("Test de communication...");
  if (rtc.testCommunication()) {
    Serial.println("✓ Communication OK");
  } else {
    Serial.println("✗ Communication échouée");
  }
  
  // Dumper les registres avant modification
  Serial.println("\nRegistres avant écriture:");
  rtc.dumpAllRegisters();
  
  // Régler l'heure
  // Serial.println("\nRéglage de l'heure...");
  // rtc.setDateTime(0, 30, 21, 7, 2, 24); // 20:00:05 07/02/2024
  
  delay(100);
  
  // Dumper après écriture
  Serial.println("\nRegistres après écriture:");
  rtc.dumpAllRegisters();
  
  Serial.println("\nLecture en continu:");
}

void loop() {
  // Lire et afficher avec debug
  uint8_t second, minute, hour, day, month, year;
  rtc.readDateTime(second, minute, hour, day, month, year);
  
  Serial.printf("Heure: %02d/%02d/%02d %02d:%02d:%02d\n", 
                day, month, year, hour, minute, second);
  
  delay(1000);
}