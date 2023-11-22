#include <WiFi.h>
#include <ESPAsyncWebServer.h>

const char *ssid = "iPhone de vini (2)";
const char *password = "123456789";

bool campainhaAtivada = false;
const int botaoPin = 2; // Pino do botão (ajuste conforme necessário)
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
               void *arg, uint8_t *data, size_t len)
{
    if (type == WS_EVT_CONNECT)
    {
        Serial.println("Cliente WebSocket conectado");
        client->text("Conectado ao Sound Sense.");
    }
    else if (type == WS_EVT_DISCONNECT)
    {
        Serial.println("Cliente WebSocket desconectado");
    }
    else if (type == WS_EVT_DATA)
    {
        data[len] = 0;
        Serial.printf("Dados recebidos: %s\n", data);

        if (strcmp((char *)data, "heartbeat") == 0)
        {
            // Envia uma resposta de heartbeat
            client->text("heartbeat_ack");
        }
    }
}
void setup()
{
    Serial.begin(9600);
    pinMode(botaoPin, INPUT);

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
    // Verifica se o botão da campainha foi pressionado
    bool botaoPressionado = digitalRead(botaoPin);

    if (botaoPressionado && !campainhaAtivada)
    {
        campainhaAtivada = true;
        Serial.println("Campainha pressionada");
        ws.textAll("bell");
    }
    else if (!botaoPressionado)
    {
        campainhaAtivada = false;
    }
}
