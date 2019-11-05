import paho.mqtt.client as mqtt
import time

def on_message(client, userdata, message):
    print("message Jarak", str(message.payload.decode("utf-8")))
    print("message topic=", message.topic)
    print("message qos=", message.qos)
    print("message retain flag=", message.retain)
    print(message.topic, payload)

broker_address="192.168.1.9"

print("creating new instance")
client=mqtt.Client("P1")
client.on_message=on_message

print("connecting to broker")
client.connect(broker_address)

print("Subcribing to topic", "hello2")
client.subscribe("hello2")

try: 
    client.loop_start() #start the loop  
    print("Publishing message to topic","hello")
    client.publish("hello","Hai Hai")
    time.sleep(10) # wait 
except KeyboardInterrupt:  
    client.loop_stop()
