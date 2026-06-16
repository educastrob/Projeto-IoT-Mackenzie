#include <WiFi.h>
#include <PubSubClient.h>

// Configurações de Rede
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// Configurações do Broker MQTT Público
const char* mqtt_server = "broker.hivemq.com";
const char* topic_publish = "cidade/mobilidade/estacionamento/vaga01";
const char* topic_subscribe = "cidade/mobilidade/estacionamento/vaga01/cmd";

// Pinos dos Periféricos
const int SENSOR_PIN = 12;
const int LED_VERDE = 22;
const int LED_VERMELHO = 16;

WiFiClient espClient;
PubSubClient client(espClient);

int ultimoEstado = -1;
unsigned long tempoInicioOcupado = 0;

// Função de Callback: Executada automaticamente quando uma mensagem chega ao ESP32
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println("\n--------------------------------------------");
  Serial.print("📥 Mensagem MQTT Recebida no Tópico: ");
  Serial.println(topic);
  
  String mensagem = "";
  for (int i = 0; i < length; i++) {
    mensagem += (char)payload[i];
  }
  Serial.print("💬 Conteúdo do Comando: ");
  Serial.println(mensagem);

  if (mensagem == "LED_VERMELHO_ON") {
    digitalWrite(LED_VERMELHO, HIGH);
    Serial.println("⚙️ Ação: LED Vermelho ativado via comando remoto MQTT.");
  } else if (mensagem == "LED_VERMELHO_OFF") {
    digitalWrite(LED_VERMELHO, LOW);
    Serial.println("⚙️ Ação: LED Vermelho desativado via comando remoto MQTT.");
  }
  Serial.println("--------------------------------------------\n");
}

void setup_wifi() {
  delay(10);
  Serial.println("\n============================================");
  Serial.print("📡 Inicializando Conexão Wi-Fi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ Wi-Fi conectado com sucesso!");
  Serial.print("📍 Endereço IP do ESP32: ");
  Serial.println(WiFi.localIP());
  Serial.println("============================================\n");
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("🔄 Tentando estabelecer conexão MQTT com o Broker... ");
    String clientId = "ESP32Client-Vaga01-" + String(random(0, 9999));
    
    if (client.connect(clientId.c_str())) {
      Serial.println("✅ Conectado!");
      client.subscribe(topic_subscribe);
      Serial.print("📌 Inscrito com sucesso no tópico: ");
      Serial.println(topic_subscribe);
    } else {
      Serial.print("❌ Falhou. Código de erro (rc)=");
      Serial.print(client.state());
      Serial.println(" | Nova tentativa em 5 segundos.");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(SENSOR_PIN, INPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  int estadoAtual = digitalRead(SENSOR_PIN);

  if (estadoAtual != ultimoEstado) {
    unsigned long uptimeSegundos = millis() / 1000;
    
    if (estadoAtual == HIGH) {
      // ESTADO: Vaga Livre
      digitalWrite(LED_VERDE, HIGH);       
      digitalWrite(LED_VERMELHO, LOW);     
      
      unsigned long tempoPermanenciaSegundos = 0;
      if (ultimoEstado == LOW) {
        tempoPermanenciaSegundos = (millis() - tempoInicioOcupado) / 1000;
      }

      String payload = "{\"vaga_id\": 1, \"status\": \"LIVRE\", \"metricas\": {\"permanencia_segundos\": " + 
                       String(tempoPermanenciaSegundos) + ", \"uptime_segundos\": " + String(uptimeSegundos) + "}}";
      
      client.publish(topic_publish, payload.c_str());
      
      Serial.print("🔹 Status: LIVRE | ⏱️ Permanência: ");
      Serial.print(tempoPermanenciaSegundos);
      Serial.println("s");
    } 
    else {
      // ESTADO: Vaga Ocupada
      digitalWrite(LED_VERDE, LOW);        
      digitalWrite(LED_VERMELHO, HIGH);    
      
      tempoInicioOcupado = millis();

      String payload = "{\"vaga_id\": 1, \"status\": \"OCUPADA\", \"metricas\": {\"permanencia_segundos\": 0, \"uptime_segundos\": " + 
                       String(uptimeSegundos) + "}}";
      
      client.publish(topic_publish, payload.c_str());
      
      Serial.println("🔹 Status: OCUPADA | ⏳ Cronômetro iniciado.");
    }
    ultimoEstado = estadoAtual;
  }
  delay(250);
}
