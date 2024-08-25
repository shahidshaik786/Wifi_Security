#include <WiFi.h>

const char* ssid = "Vuln_wifi";
const char* password = "Vuln@12345";

WiFiServer server(80); // Create a server that listens on port 80

void setup() {
  Serial.begin(115200);

  // Set up the ESP32 as an access point
  WiFi.softAP(ssid, password);

  Serial.println("Access Point started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP()); // Print IP address of the ESP32
  Serial.print("MAC Address: ");
  Serial.println(WiFi.softAPmacAddress()); // Print MAC address of the ESP32

  server.begin(); // Start the server
}

void loop() {
  WiFiClient client = server.available(); // Check if a client has connected

  if (client) {
    Serial.println("Client connected");

    // Print client information
    Serial.print("Client IP: ");
    Serial.println(client.remoteIP());

    String incomingData;
    int dataSize = 0;

    // Read incoming data
    while (client.available()) {
      char c = client.read();
      incomingData += c;
      dataSize++;
    }

    // Print data size and received data
    Serial.print("Data Size: ");
    Serial.println(dataSize);
    Serial.println("Received Data:");
    Serial.println(incomingData);

    // Vulnerable code: copying 128 bytes to a 64-byte buffer
    char buffer[64];
    incomingData.toCharArray(buffer, sizeof(buffer));

    Serial.println("Processed Data:");
    Serial.println(buffer);

    client.stop(); // Close the connection
  }

  delay(1000);
}
