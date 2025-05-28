#include <OneWire.h>
#include <DallasTemperature.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <time.h>

// → Definição de pinos
#define PIN_PH        34
#define PIN_TURB      35
#define PIN_COND      32
#define ONE_WIRE_PIN  33
#define LED_PIN       2

// → Credenciais Wi-Fi
const char* ssid     = "Wokwi-GUEST";
const char* password = "";

// → Broker MQTT
const char*    mqtt_server = "broker.hivemq.com";
const uint16_t mqtt_port   = 1883;
const char*    mqtt_user   = "aquasense-esp32";
const char*    mqtt_topic   = "aquasense/dados";

// → Configuração NTP
const char* ntpServer        = "pool.ntp.org";
const long  gmtOffset_sec    = -3 * 3600;  // UTC–3
const int   daylightOffset_s = 0;

WiFiClient         wifiClient;
PubSubClient       mqtt(wifiClient);
OneWire            oneWire(ONE_WIRE_PIN);
DallasTemperature  sensors(&oneWire);

void conectaWiFi() {
  Serial.print("Conectando WiFi");
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Conectado: " + WiFi.localIP().toString());
}

void conectaMQTT() {
  mqtt.setServer(mqtt_server, mqtt_port);
  Serial.print("Conectando MQTT");

  while (!mqtt.connected()) {
    if (mqtt.connect(mqtt_user)) {
      Serial.println(" → OK");
    } else {
      Serial.print(" falhou, rc=");
      Serial.print(mqtt.state());
      Serial.println(" tentando de novo em 2s");

      delay(2000);
    }
  }
}

void conectaNTP() {
  configTime(gmtOffset_sec, daylightOffset_s, ntpServer);
  Serial.print("Sincronizando hora");

  time_t now = time(nullptr);
  while (now < 8 * 3600 * 2) {
    delay(500);
    Serial.print(".");

    now = time(nullptr);
  }

  Serial.println("\nHora NTP OK: " + String(ctime(&now)));
}

/// Gera timestamp ISO 8601 e escreve em 'outBuf' (tamanho mínimo 25 bytes)
void gerarTimestamp(char *outBuf, size_t bufSize) {
  time_t now = time(nullptr);
  struct tm *ti = gmtime(&now);
  strftime(outBuf, bufSize, "%Y-%m-%dT%H:%M:%SZ", ti);
}

void setup() {
  Serial.begin(115200);
  sensors.begin();

  pinMode(PIN_PH,   INPUT);
  pinMode(PIN_TURB, INPUT);
  pinMode(PIN_COND, INPUT);
  pinMode(LED_PIN,  OUTPUT);

  conectaWiFi();
  conectaNTP();
  conectaMQTT();
}

void loop() {
  if (!mqtt.connected()) {
    conectaMQTT();
  }
  mqtt.loop();

  // → Leitura de dados
  char timestamp[25];
  gerarTimestamp(timestamp, sizeof(timestamp));
  
  float vTurb = analogRead(PIN_TURB) * (3.3 / 4095.0);
  float turbidezNTU = (vTurb / 3.3) * 10.0;
  float vCond = analogRead(PIN_COND) * (3.3 / 4095.0);
  float condutividade = (vCond / 3.3) * 5000.0;
  float vPh   = analogRead(PIN_PH)   * (3.3 / 4095.0); 
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);
  
  bool alerta = (vPh < 6.5 || vPh > 8.5)
             || (turbidezNTU > 5.0)
             || (condutividade > 1500.0);

  // → Monta payload JSON incluindo timestamp
  String payload = String("{\"timestamp\":\"") + timestamp + "\"" +
                   ",\"pH\":" + String(vPh, 2) +
                   ",\"turbidez\":" + String(turbidezNTU, 2) +
                   ",\"temperatura\":" + String(tempC, 1) +
                   ",\"condutividade\":" + String(condutividade) +
                   ",\"alerta\":" + String(alerta ? "true" : "false") +
                   "}";

  // → Envia e loga
  mqtt.publish(mqtt_topic, payload.c_str());
  Serial.println(payload);

  // → Threshold do LED
  digitalWrite(LED_PIN, alerta ? HIGH : LOW);

  delay(2000);
}
