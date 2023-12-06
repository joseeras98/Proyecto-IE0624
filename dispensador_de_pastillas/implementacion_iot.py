import serial
import paho.mqtt.client as mqtt
import json

ser = serial.Serial("/dev/ttyACM0", 115200, timeout = 1) 
print("Se ha conectado al puerto serial /dev/ttyACM0")

client = mqtt.Client("AGREGAR")

server = "iot.eie.ucr.ac.cr"
port = 1883
topic = "v1/devices/me/telemetry"
token = "ysuyuy140yvasraycviv"

client.username_pw_set(token)
client.connect(server, port)

dictionary = dict()

while True:
	line = ser.readline().decode("utf-8")
	line = line.replace("\r", "").replace("\n", "")
	line = line.split(",")
	if len(line) == 4:
		dictionary["alarma"] = line[0]
		dictionary["alarma1"] = line[1]
		dictionary["alatma2"] = line[2]
		dictionary["Battery"] = line[3]
		msg = json.dumps(dictionary)
		print(msg)
		client.publish(topic, msg)
