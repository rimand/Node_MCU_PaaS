#include <ESP8266WiFi.h>
#include <DHT.h>

#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT11   // DHT 22  (AM2302)
#define DELAY 100

const char *ssid = "RimadStudio_Wifi";
const char *pass = "a1321";
const char *host_thingspeak = "api.thingspeak.com";
const char *host_dweet = "dweet.io";
const char *host_sparkfun = "data.sparkfun.com";
const char *API_KEY = "34OLZ3ADTX9S7FY6";
const char *thing_name = "Rimand-Node-Red";

DHT dht(DHTPIN,DHTTYPE,30);
float t;

String getData();

void setup() {
  pinMode(16,OUTPUT);
  delay(2000);
  Serial.begin(9600);
  dht.begin();
  //-------------------------------------
  Serial.print("\n\n");
  Serial.print("Connecting to ");
  Serial.print(ssid);
  //-------------------------------------
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.println("IP Address");
  Serial.println(WiFi.localIP());
}

void uploadThingspeak() {
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host_thingspeak, httpPort)) {
    Serial.print("\nDisconnect");
    return;
  }
  Serial.print("thingspeak : ");

  String url = "/update/";
  url += "?api_key=";
  url += API_KEY;
  url += "&field2=";
  //url += random(0, 100);
  url += getData();
  
  Serial.print(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host_thingspeak + "\r\n" +
               "Connection: close\r\n\r\n");
  Serial.println(" >> GET");
}

void uploadSparkfun() {
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host_sparkfun, httpPort)) {
    Serial.print("\nDisconnect");
    return;
  }
  Serial.print("Sparkfun : ");

  String url = "/input/";
  url += "JxEx0M1rrYc2jL2y7aOn?private_key=gzpzjEWBBoh4b54Xz80j";
  url += "&value=";
  //url += random(0, 100);
  url += getData();
  
  Serial.print(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host_sparkfun + "\r\n" +
               "Connection: close\r\n\r\n");
  Serial.println(" >> GET");
}

void uploadDweet() {
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host_dweet, httpPort)) {
    Serial.print("\nDisconnect");
    return;
  }
  Serial.print("dweet : ");

  String url = "/dweet/for/";
  url += thing_name;
  url += "?Value=";
  //url += random(0, 100);
  url += getData();
  
  Serial.print(url);

  client.print(String("GET ") + url +
               " HTTP/1.1\r\n" +
               "Host: " + host_dweet + "\r\n" +
               "Connection: close\r\n\r\n");
  Serial.println(" >> GET");
}

void blinks(){
  digitalWrite(16,LOW);
  delay(100);
  digitalWrite(16,HIGH);
  delay(100);
}

void reconnectWifiIfLinkDown() {
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("\nWiFi connected");
    Serial.println("IP Address");
    Serial.println(WiFi.localIP());
  }
}

String getData(){
 String data = "";
  data += t;
  return data;
}

void loop() {
  t = dht.readTemperature();
  
  delay(DELAY);
  uploadThingspeak();
  blinks();
  
  delay(DELAY);
  uploadDweet();
  blinks();
  
  delay(DELAY);
  uploadSparkfun();
  blinks();
  
  reconnectWifiIfLinkDown();
}
