import paho.mqtt.client as mqtt
from pymongo import MongoClient
from datetime import datetime
import json
import os # 환경 변수 사용 시 필요

# --- 설정값 (Config) ---
# 깃허브 업로드 시에는 아래처럼 가이드만 남겨두는 것이 좋습니다.
broker = "YOUR_CLOUD_IP" 
port = 1883 # 포트는 보통 숫자형태입니다.
username = "YOUR_MQTT_USERNAME"
password = "YOUR_MQTT_PASSWORD"

mongo_client = MongoClient("mongodb://YOUR_MONGO_IP:27017")
db = mongo_client["your_db_name"]
collection = db["your_collection_name"]

# --- 콜백 함수 (Callbacks) ---
def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print(" MQTT 브로커 연결 성공!")
        client.subscribe("your/topic/here") # 구독할 토픽 설정
    else:
        print(f" 연결 실패 (결과 코드: {rc})")

def on_message(client, userdata, msg):
    try:
        payload = msg.payload.decode()
        print(f"📩 메시지 수신: {payload}")
        
        data = json.loads(payload)
        
        # 필수 키 검증 (실제 데이터 구조에 맞게 수정하세요)
        required_keys = {"device_name", "temp", "hud", "index"}
        if not required_keys.issubset(data.keys()):
            print(f" 유효하지 않은 포맷: {payload}")
            return

        # 날짜 데이터 생성 (주석 풀고 활성화)
        current_date = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

        # MongoDB 업데이트 (upsert=True로 장치가 없으면 자동 생성)
        collection.update_one(
            {"device_name": data["device_name"]},
            {
                "$push": {
                    "records": {
                        "date": current_date,
                        "index": data["index"],
                        "temperature": data["temp"],
                        "humidity": data["hud"],
                    }
                }
            },
            upsert=True
        )
        print(f"DB 저장 완료: {data['device_name']}")

    except Exception as e:
        print(f" 메시지 처리 중 오류 발생: {e}")

# --- 실행부 (Main) ---
client = mqtt.Client()
client.username_pw_set(username, password)
client.on_connect = on_connect
client.on_message = on_message

print("⏳ 브로커 연결 시도 중...")
client.connect(broker, port, 60)

# 백그라운드에서 계속 실행
client.loop_forever()