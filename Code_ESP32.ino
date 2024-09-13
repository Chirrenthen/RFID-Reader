// Code written by Chirrenthen P
// Connect the components according to the schematic given in the repository
// Upload the code into Doit Esp32 Devkit V1 
// Test the setup and enjoy!

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 5    // SDA pin connected to GPIO 5 (D5)
#define RST_PIN 22  // RST pin connected to GPIO 22 (D22)

MFRC522 rfid(SS_PIN, RST_PIN);  // Create MFRC522 instance

void setup() {
  Serial.begin(115200);   // Initialize serial communications
  SPI.begin();            // Init SPI bus
  rfid.PCD_Init();        // Init MFRC522
  Serial.println("Scan your RFID card/tag...");
}

void loop() {
  // Look for new cards
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    delay(50);
    return;
  }

  // Show UID on serial monitor
  Serial.print("UID: ");
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(rfid.uid.uidByte[i], HEX);
  }
  Serial.println();

  // Halt PICC
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
}