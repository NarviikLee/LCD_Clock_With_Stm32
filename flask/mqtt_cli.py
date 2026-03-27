import paho.mqtt.client as mqtt
from pymongo import MongoClient
from datetime import datetime
import json
import re

broker = "158.179.169.192"
port = 1883
username = "Narviik"
password="freshwaterlee12"

mongo_client = MongoClient("mongodb://localhost:27017/")
db = mongo_client["mqtt_data"]
collection=db["iot_devices"]


def on_connect(client,userdata,flags,rc):
    print("connected with result code "+ str(rc))
    client.subscribe("test/topic")

def on_message(client,userdata,msg):
    try:
        payload = msg.payload.decode()
        print(f"Received message : {payload}")
        data = json.loads(payload)
        required_keys = {"index", "temp", "hud", "device_name"}
        if not required_keys.issubset(data.keys()):
            print(f"Invalid payload format: Missing keys in {payload}")
            return

        print(f"received{data}")
        now = datetime.now()
        current_date = now.strftime("%Y-%m-%d")
        data["date"] = current_date
        collection.update_one(
            {"device_name":data["device_name"]},
            {
                "$push":{
                    "records":{
                        "date":current_date,
                        "index":data["index"],
                        "temperature":data["temp"],
                        "humidity":data["hud"],
                    }
                }
            },
            upsert=True
        )
        print(f"Inserted data into MongoDB: {data}")
    except Exception as e:
        print(f"Error processing message: {e}")

def on_connect(client, userdata, flags ,rc):
    if rc == 0:
        print("Connected to MQTT broker!")
        client.subscribe("test/topic")
    else:
        print(f"Failed to connect, return code{rc}")



client = mqtt.Client()

client.username_pw_set(username,password)

client.on_connect = on_connect
client.on_message = on_message

client.connect(broker,port,60)
client.publish("test/topic", "Hello, MQTT with Auth!")

#client.loop_start()
client.loop_forever()
