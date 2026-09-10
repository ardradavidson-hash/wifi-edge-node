#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <DHT.h>

#define DHTPIN D4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  delay(2000);

  Serial.println();
  Serial.println("================================");
  Serial.println("       DAY 2 ENVIRONMENT CHECK");
  Serial.println("================================");

  Serial.println("Library check:");
  Serial.println("DHT sensor library: OK");
  Serial.println("PubSubClient: OK");
  Serial.println("ArduinoJson: OK");
  Serial.println("ESP8266 WiFi: OK");
  Serial.println("ESP8266 HTTPClient: OK");

  dht.begin();
  Serial.println("DHT22 initialized");

  Serial.println();
  Serial.println("SDK and memory information:");

  Serial.print("SDK version: ");
  Serial.println(ESP.getSdkVersion());

  Serial.print("Chip ID: ");
  Serial.println(ESP.getChipId(), HEX);

  Serial.print("CPU frequency: ");
  Serial.print(ESP.getCpuFreqMHz());
  Serial.println(" MHz");

  Serial.print("Flash chip size: ");
  Serial.print(ESP.getFlashChipSize());
  Serial.println(" bytes");

  Serial.print("Free heap: ");
  Serial.print(ESP.getFreeHeap());
  Serial.println(" bytes");

  Serial.print("Heap fragmentation: ");
  Serial.print(ESP.getHeapFragmentation());
  Serial.println("%");

  Serial.print("Maximum free block: ");
  Serial.print(ESP.getMaxFreeBlockSize());
  Serial.println(" bytes");

  Serial.println("================================");
}

void loop() {
  Serial.print("Free heap: ");
  Serial.print(ESP.getFreeHeap());
  Serial.println(" bytes");

  delay(3000);
}
