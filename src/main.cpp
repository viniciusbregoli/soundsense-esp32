#include <WiFi.h>

const char *ssid = "BREGOLI";
const char *password = "6b61746531323036";

WiFiServer server(80);

void setup()
{
    Serial.begin(9600);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.println("Connecting to WiFi...");
    }

    Serial.println("Connected to WiFi");
    server.begin();
}

void loop()
{
    WiFiClient client = server.available();

    if (client)
    {
        while (client.connected())
        {
            if (client.available())
            {
                // Read data from the ESP32
                String line = client.readStringUntil('\r');
                Serial.println(line);

                // Send data to the Flutter app
                client.println("Sending data to Flutter app");
            }
        }
        client.stop();
        Serial.println("Client Disconnected.");
    }
}
