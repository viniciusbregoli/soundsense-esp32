#include <WiFi.h>
#include <ESPAsyncWebServer.h>

// Substitua com suas configurações de rede
const char *ssid = "BREGOLI";
const char *password = "123456789";

// Pino do LED
const int ledPin = 2;

// Cria objeto do servidor na porta 80
AsyncWebServer server(80);

void setup()
{
    // Inicia o Serial
    Serial.begin(9600);

    // Inicia o LED como desligado
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);

    // Conecta ao Wi-Fi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Conectando ao WiFi...");
        Serial.println(WiFi.status());
    }

    Serial.println("Conectado ao WiFi");
    Serial.print("Endereço IP: ");
    Serial.println(WiFi.localIP());

    // Rota para acionar o LED
    server.on("/led", HTTP_GET, [](AsyncWebServerRequest *request)
              {
    digitalWrite(ledPin, HIGH); // Liga o LED
    request->send(200, "text/plain", "LED ligado"); });

    // Inicia o servidor
    server.begin();
}

void loop()
{
}
