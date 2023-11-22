#include <WiFi.h>
#include <ESPAsyncWebServer.h>

const char *ssid = "Redmi Note 11";
const char *password = "123@gabriel";

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
               void *arg, uint8_t *data, size_t len)
{
    if (type == WS_EVT_CONNECT)
    {
        Serial.println("Cliente WebSocket conectado");
        client->text("Bem-vindo ao servidor WebSocket ESP32!");
    }
    else if (type == WS_EVT_DISCONNECT)
    {
        Serial.println("Cliente WebSocket desconectado");
    }
    else if (type == WS_EVT_DATA)
    {
        data[len] = 0;
        Serial.printf("Dados recebidos: %s\n", data);
    }
}

void setup()
{
    Serial.begin(9600);

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

    ws.onEvent(onWsEvent);
    server.addHandler(&ws);
    server.begin();
}

void loop()
{
    delay(5000);
    ws.textAll("bell");
}
