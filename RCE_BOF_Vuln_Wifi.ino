#include <WiFi.h>
#include <WebServer.h>
#include <esp_wifi.h>

const char* ssid = "Vuln_WiFi";
const char* password = "Vuln@12345";

WebServer server(80);
char buffer[64]; // Buffer with limited size to demonstrate buffer overflow

void handleRoot() {
  String payload = server.arg(0); // Get data from the first argument
  Serial.print("Data Received: ");
  Serial.println(payload);

  if (payload.length() > sizeof(buffer)) {
    Serial.println("Warning: Possible buffer overflow attempt detected!");
  }

  payload.toCharArray(buffer, sizeof(buffer)); // Potential overflow if payload is too large

  server.send(200, "text/plain", "Received: " + String(buffer));
}

void printConnectedDevices() {
  wifi_sta_list_t wifi_sta_list;
  esp_wifi_ap_get_sta_list(&wifi_sta_list);

  Serial.println("Connected devices:");
  for (int i = 0; i < wifi_sta_list.num; i++) {
    wifi_sta_info_t station = wifi_sta_list.sta[i];
    Serial.print("MAC Address: ");
    for (int j = 0; j < 6; j++) {
      Serial.print(String(station.mac[j], HEX));
      if (j < 5) Serial.print(":");
    }
    Serial.print(" | IP Address: ");
    Serial.println(WiFi.softAPIP());
  }
}

void setup() {
  Serial.begin(115200);

  // Set up the ESP32 as an access point
  WiFi.softAP(ssid, password);

  Serial.println("Access Point started");
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.softAPIP());
  Serial.print("ESP32 MAC Address: ");
  Serial.println(WiFi.softAPmacAddress());

  server.on("/", handleRoot); // Handle requests to the root URL
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  printConnectedDevices(); // Print connected devices
  delay(5000); // Print every 5 seconds
}
