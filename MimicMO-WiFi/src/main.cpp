#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoJson.h>

WiFiUDP UDPClient;
IPAddress localIP(192,168,1,1);
IPAddress gateway(192,168,1,0);
IPAddress subnet(255,255,255,0);
IPAddress broadcast(192,168,1,255);
int port = 80;

char payload[1024] = "";

const char* ssid     = "Mach One AP";
const char* password = "123456789";
int nBytes;

JsonDocument json;
float alt, lat, lon, aX, aY, aZ, gX, gY, gZ, RSSI, voltage; 
bool dM, dR, mM, ready;

// put function declarations here:
int myFunction(int, int);
void generateRandom();
void generateJson();
void sendPacket();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Starting AP...");
  WiFi.softAPConfig(localIP, gateway, subnet);
  WiFi.softAP(ssid, password);
  UDPClient.begin(80);
  Serial.print(WiFi.softAPIP());
}

void loop() {
  generateRandom();
  generateJson();
  sendPacket();
  delay(200);
  // put your main code here, to run repeatedly:
}


void generateRandom(){
  alt = random(0,3000);
  lat = -21.7785 + random(1000, 10000)/5000000.0;
  lon = -43.3731 + random(1000, 10000)/5000000.0;
  aX = random(-5000, 5000)/100.0;
  aY = random(-5000, 5000)/100.0;
  aZ = random(-5000, 5000)/100.0;
  gX = random(-1800, 1800)/10.0;
  gY = random(-1800, 1800)/10.0;
  gZ = random(-1800, 1800)/10.0;
  RSSI = random(600,1200)/10.0;
  voltage = random(300,420)/100.0;
  dM = random(0,2);
  dR = random(0,2);
  mM = random(0,2);
  ready = random(0,2);
}

void generateJson(){
  json["Alt"] = alt;
  json["Lat"] = lat;
  json["Long"] = lon;
  json["Acel(x)"] = aX;
  json["Acel(y)"] = aY;
  json["Acel(z)"] = aZ;
  json["Gyro(x)"] = gX;
  json["Gyro(y)"] = gY;
  json["Gyro(z)"] = gZ;
  json["RSSI"] = RSSI;
  json["Voltage"] = voltage;
  json["PPE"] = dM;
  json["Redundancia Paraquedas Estabilizador"] = dR;
  json["PPP"] = mM;
  json["ready"] = ready;
}

void sendPacket(){

  nBytes = serializeJson(json, payload);

  UDPClient.beginPacket(broadcast, port);
  UDPClient.write((uint8_t*) &payload, nBytes);
  UDPClient.endPacket();
  Serial.println("Message sended!");
  Serial.println(payload);
  // serializeJsonPretty(json, Serial);
  Serial.println("---------------");


}
