#define ESP32

#define LED_BUILTIN 2

void setup() {
  Serial.begin(115200);
  delay(500);

  Serial.println("Board: ESP32");

  Serial.printf("Chip model: %s\n", ESP.getChipModel());
  Serial.printf("Chip revision: %d\n", ESP.getChipRevision());
  Serial.printf("Cores: %d\n", ESP.getChipCores());
  Serial.printf("Flash: %u bytes\n", ESP.getFlashChipSize());
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("Polyhouse edge node heartbeat");
  delay(500);

  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
}
