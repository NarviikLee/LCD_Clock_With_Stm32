import paho.mqtt.client as mqtt

# --- Diagnostic Settings ---
broker = "YOUR_SERVER_IP"
port = 8883 # TLS 사용 시 보통 8883 포트를 사용합니다.

def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print(f" Connected successfully! (Result code: {rc})")
        client.subscribe("test/connection")
    else:
        print(f" Connection failed. (Result code: {rc})")

def on_message(client, userdata, msg):
    print(f" Received [Topic: {msg.topic}]: {msg.payload.decode()}")

client = mqtt.Client()

# --- Security (TLS/SSL) Setup ---
# ⚠️ 주의: 실제 .crt 및 .key 파일은 .gitignore를 통해 제외해야 합니다.
# client.tls_set(ca_certs="./certs/mosquitto.crt", certfile="./certs/client.crt", keyfile="./certs/client.key")
# client.tls_insecure_set(True) # 테스트 환경에서 호스트네임 검증 건너뛰기

client.on_connect = on_connect
client.on_message = on_message

print(f"⏳ Connecting to {broker}:{port}...")
client.connect(broker, port, 60)
client.loop_forever()

