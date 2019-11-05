#include <WiFi.h>
#include <PubSubClient.h>

#define pinEcho 22
#define pinTrig 23
float durasi, jarak;

//Replace the next variables with your SSID/Password combination
const char *ssid ="asesor1";
const char *password ="coomputerstore4.0";

//Add your MQTT Broker IP address, example:
//const char* mqtt_server = "192.168.137.1";

const char* mqtt_server ="192.168.1.9";
const char* topic ="hello2";

float temp;
char data[5];

WiFiClient espClient;
PubSubClient client(espClient);
/*
const int led1=LED_BUILTIN;
const int led2=36;
*/
long lastMsg =0;
char msg[50];
int value =0;

void setup() {
  Serial.begin(115200);

  pinMode(pinTrig, OUTPUT); 
  pinMode(pinEcho, INPUT);
  
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  /*
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  */
}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while(WiFi.status() !=WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.begin(115200);
    pinMode(36, INPUT);
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  for(int i =0; i <length; i++) {
    Serial.print((char)message[i]);
    messageTemp +=(char)message[i];}
    Serial.println();
    
    /*
    if(messageTemp=="1"){
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
    }else{
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
    }
    */

}

void reconnect() {
  // Loop until we're reconnected
  while(!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if(client.connect("ESP8266Client")) {
      Serial.println("connected");
      //Subscribe
      client.subscribe("hello");
      }
      else
      {
        Serial.print("failed, rc=");
        Serial.print(client.state());
        Serial.println(" try again in 5 seconds");
        // Wait 5 seconds before retrying
        delay(5000);
      }
    }
  }

void trying_to_publish(){
  if(client.publish(topic, data)) {
    //String hasiltemp=data;
    Serial.println("Publish ok, jarak sudah dikirim");
    }
    else {
      Serial.println("Publish failed");
      }
      delay(2000);
}

void loop() {
  if(!client.connected()) {
    reconnect();
    }

    digitalWrite(pinTrig, HIGH);
    delayMicroseconds(10);
    digitalWrite(pinTrig, LOW);
    delayMicroseconds(8);

    durasi = pulseIn(pinEcho, HIGH);
    jarak = durasi / 1000000 / 2 * 340 * 100;
    Serial.print("Jarak : ");
    Serial.print(jarak);
    Serial.println(" cm");

    if (jarak <= 60){
      snprintf(data, 5, "%f", jarak);
      delay(1000);
      Serial.println(data);

      trying_to_publish();
      //client.loop();
    }
    
    delay (2000);
    
    /*
    trying_to_publish();
    client.loop();

     long now = millis();
     if (now - lastMsg >5000){
      lastMsg =now;

      //fungsi temperatur
      float temp=(analogRead(36)*3.3/2046/0.01);
      snprintf(data, 5, "%f", temp);
      delay(1000);
      //Serial.println(data);
      //client.publish("temperature", data);
     }
     */    
}
