#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
// Wi-Fi 및 MQTT 브로커 설정

const char* ssid = "WIFI_ID";    //wift 아이디
const char* password = "WIFI_PW";    // wifi 비번 
const char* mqtt_server = "MQTT_IP"; // MQTT 브로커 IP
const int mqtt_port = 0;                // MQTT 포트
const char* mqtt_user = "MQTT_USER";   // MQTT 사용자 이름
const char* mqtt_password = "MQTT_PW"; // MQTT 비밀번호
int LED_GPIO = 2;
WiFiClient espClient;
PubSubClient client(espClient);


void setup_wifi() {
  delay(10);
  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi Connected!");
}
void reconnect() {
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    if (client.connect("ESP32Client", mqtt_user, mqtt_password)) {  // ID와 비밀번호 인증
      Serial.println("Connected to MQTT broker!");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" Retrying in 5 seconds...");
      delay(5000);
    }
  }
}
void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port); // 브로커 IP와 포트 설정
  pinMode(LED_GPIO,OUTPUT);
  digitalWrite(LED_GPIO, HIGH);
  delay(2000);
  digitalWrite(LED_GPIO, LOW);
  delay(2000);
  digitalWrite(LED_GPIO, HIGH);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  if (Serial.available()) {
    String receivedData = Serial.readStringUntil('\n'); // Serial로 데이터 수신
    Serial.println("Received: " + receivedData);
    digitalWrite(LED_GPIO, LOW);
    // JSON으로 변환
    StaticJsonDocument<200> jsonDoc;
    int index;
    int temp, hud;
    char device_name[50];

    sscanf(receivedData.c_str(), "index:%d,temp:%d,hud:%d,device_name:%49s", &index, &temp, &hud, device_name);

    jsonDoc["index"] = index;
    jsonDoc["temp"] = temp;
    jsonDoc["hud"] = hud;
    jsonDoc["device_name"] = device_name;

    char buffer[256];
    serializeJson(jsonDoc, buffer);

    // MQTT 퍼블리시
    client.publish("test/topic", buffer);
    Serial.println("Published: " + String(buffer));
    delay(15000);
    digitalWrite(LED_GPIO, HIGH);
  }
}