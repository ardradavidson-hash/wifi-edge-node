#include <WiFi.h>
#include "secrets.h"

// --------------------------------------------------
// Wi-Fi states
// --------------------------------------------------

enum WifiState {
  WIFI_DISCONNECTED,
  WIFI_CONNECTING,
  WIFI_CONNECTED
};

WifiState wifiState = WIFI_DISCONNECTED;

// --------------------------------------------------
// Timing configuration
// --------------------------------------------------

const unsigned long CONNECT_TIMEOUT_MS = 15000;
const unsigned long HEALTH_CHECK_INTERVAL_MS = 5000;

const unsigned long INITIAL_BACKOFF_MS = 2000;
const unsigned long MAX_BACKOFF_MS = 60000;

// --------------------------------------------------
// Connection manager variables
// --------------------------------------------------

unsigned long connectStarted = 0;
unsigned long lastHealthCheck = 0;
unsigned long nextRetryTime = 0;

uint8_t retryAttempt = 0;


// --------------------------------------------------
// Start a Wi-Fi connection attempt
// --------------------------------------------------

void startWifiConnect() {

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  connectStarted = millis();
  wifiState = WIFI_CONNECTING;

  Serial.printf("Connecting to %s ...\n", WIFI_SSID);
}


// --------------------------------------------------
// Calculate exponential backoff
// --------------------------------------------------

unsigned long getBackoffTime() {

  unsigned long backoff =
      INITIAL_BACKOFF_MS * (1UL << retryAttempt);

  if (backoff > MAX_BACKOFF_MS) {
    backoff = MAX_BACKOFF_MS;
  }

  return backoff;
}


// --------------------------------------------------
// Print connection information
// --------------------------------------------------

void printWifiInfo() {

  Serial.println();
  Serial.println("===== Wi-Fi Connected =====");

  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  Serial.print("RSSI: ");
  Serial.print(WiFi.RSSI());
  Serial.println(" dBm");

  Serial.print("BSSID: ");
  Serial.println(WiFi.BSSIDstr());

  Serial.print("Channel: ");
  Serial.println(WiFi.channel());

  Serial.println("============================");
  Serial.println();
}


// --------------------------------------------------
// Handle connection failure
// --------------------------------------------------

void handleConnectionFailure() {

  WiFi.disconnect();

  retryAttempt++;

  if (retryAttempt > 5) {
    retryAttempt = 5;
  }

  unsigned long backoff = getBackoffTime();

  nextRetryTime = millis() + backoff;

  wifiState = WIFI_DISCONNECTED;

  Serial.printf(
    "Connection failed. Retry in %lu ms\n",
    backoff
  );
}


// --------------------------------------------------
// Wi-Fi connection manager
// --------------------------------------------------

void loopWifiManager() {

  unsigned long now = millis();


  // -----------------------------------------------
  // DISCONNECTED
  // -----------------------------------------------

  if (wifiState == WIFI_DISCONNECTED) {

    if (now >= nextRetryTime) {
      startWifiConnect();
    }

    return;
  }


  // -----------------------------------------------
  // CONNECTING
  // -----------------------------------------------

  if (wifiState == WIFI_CONNECTING) {

    // Connection succeeded
    if (WiFi.status() == WL_CONNECTED) {

      wifiState = WIFI_CONNECTED;

      retryAttempt = 0;

      lastHealthCheck = now;

      printWifiInfo();

      return;
    }


    // Connection timed out
    if (now - connectStarted >= CONNECT_TIMEOUT_MS) {

      Serial.println("Wi-Fi connection timeout.");

      handleConnectionFailure();

      return;
    }

    return;
  }


  // -----------------------------------------------
  // CONNECTED
  // -----------------------------------------------

  if (wifiState == WIFI_CONNECTED) {

    if (now - lastHealthCheck >= HEALTH_CHECK_INTERVAL_MS) {

      lastHealthCheck = now;

      if (WiFi.status() == WL_CONNECTED) {

        Serial.printf(
          "Wi-Fi OK | RSSI: %d dBm | IP: %s\n",
          WiFi.RSSI(),
          WiFi.localIP().toString().c_str()
        );

      } else {

        Serial.println("Wi-Fi lost. Starting reconnection.");

        wifiState = WIFI_DISCONNECTED;

        retryAttempt = 0;

        nextRetryTime = now;
      }
    }

    return;
  }
}


// --------------------------------------------------
// Setup
// --------------------------------------------------

void setup() {

  Serial.begin(115200);

  delay(500);

  Serial.println();
  Serial.println("Polyhouse Wi-Fi Manager");
  Serial.println("-----------------------");

  WiFi.mode(WIFI_STA);

  // Start immediately
  nextRetryTime = millis();
}


// --------------------------------------------------
// Main loop
// --------------------------------------------------

void loop() {

  loopWifiManager();

  // Your sensor code can run here
  // without being blocked by Wi-Fi retries.

  delay(10);
}
