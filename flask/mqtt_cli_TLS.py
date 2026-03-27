import paho.mqtt.client as mqtt

broker = "158.179.169.192"
port = 8883

def on_connect(client,userdata,flags,rc):
    print("connected with result code "+ str(rc))
    client.subscribe("test/topic")

def on_message(client,userdata,msg):
    print(f"Received message : {msg.payload.decode()}")

client = mqtt.Client()
client.tls_set(ca_certs="/etc/mosquitto/certs/mosquitto.crt", certfile="/etc/mosquitto/certs/mosquitto.crt", keyfile="/etc/mosquitto/certs/mosquitto.key")
client.tls_insecure_set(True)


client.on_connect = on_connect
client.on_message = on_message

client.connect(broker,port,60)
client.loop_forever()
