#include <Arduino.h>
#include <ArduinoJson.h>

JsonDocument json;
float alt, lat, lon, aX, aY, aZ, gX, gY, gZ, RSSI, voltage; 
bool dM, dR, mM, ready;

// put function declarations here:
void generateRandom();
void generateJson();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Starting UART...");
}

void loop() {
  // put your main code here, to run repeatedly:
  generateRandom();
  generateJson();
  serializeJson(json, Serial);
  Serial.println();
  delay(20);
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