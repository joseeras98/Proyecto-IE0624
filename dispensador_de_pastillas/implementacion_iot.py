import serial
import paho.mqtt.client as mqtt
import json
import re
import sys
import select

ser = serial.Serial("COM7", 115200, timeout = 1) 
print("Se ha conectado al puerto serial COM7")

client = mqtt.Client()
server = "iot.eie.ucr.ac.cr"
port = 1883
topic = "v1/devices/me/telemetry"
token = "ysuyuy140yvasraycviv"  # Tu token real
device_id = "68094000-93e3-11ee-9eb1-4f281083cad4"  # Tu Device ID

client.username_pw_set(token)
client.connect(server, port)
client.loop_start()


def on_publish(client, userdata, result):
    print("data published to thingsboard")
    pass

client.on_publish = on_publish

while True:
    if ser.in_waiting > 0:
        line = serial_port.readline().decode('utf-8').strip()
        values = line.split("\t")  # Dividir los datos por tabulaciones

        if line == "LED ON":
            client.publish(topic, json.dumps({"LED_status": "on"}), 1)
        elif line == "LED OFF":
            client.publish(topic, json.dumps({"LED_status": "off"}), 1)
        else:
            # Si no es "LED ON" ni "LED OFF", podrías enviar los datos recibidos tal como están
            client.publish(topic, json.dumps({"serial_data": line}), 1)


        client.publish("v1/devices/me/telemetry", json.dumps(data), 1)
        time.sleep(1)


ser.close()
client.loop_stop()
client.disconnect()
