#include <WiFi.h>
#include <ESPAsyncWebServer.h>

const char *ssid = "BREGOLI";
const char *password = "123456789";

unsigned long lastHeartbeatTime = 0;
const unsigned long heartbeatInterval = 1000;

bool campainhaAtivada = false;
const int botaoPin = 2;
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
               void *arg, uint8_t *data, size_t len)
{
    if (type == WS_EVT_CONNECT)
    {
        Serial.println("Cliente WebSocket conectado");
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
    pinMode(botaoPin, OUTPUT);
    digitalWrite(botaoPin, HIGH);

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
    unsigned long currentTime = millis();
    int estadoPino = digitalRead(botaoPin);
    if (estadoPino && !campainhaAtivada)
    {
        ws.textAll("campainha");
        Serial.println("Mensagem enviada");
        campainhaAtivada = true;
    }

    // Verifique se o tempo desde o último heartbeat é maior que o intervalo desejado
    if (currentTime - lastHeartbeatTime >= heartbeatInterval)
    {
        
        ws.textAll("heartbeat");
        lastHeartbeatTime = currentTime;
    }
}
