#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>
#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "wifissid";
const char* password = "wifipass";

const char* host = "ipaddresofyourhttpserver";
String nombreserver = "http://ipaddresofyourhttpserver:80/iot.php";



void setup() {
  
Serial.begin(115200);
delay(10);
//Wifi
 Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
//Temperature sensor
    dht.begin();
}

void loop() {

float h = dht.readHumidity();
float t = dht.readTemperature();

if (isnan(h) || isnan(t)) {
Serial.println(F("Failed to read from DHT sensor!"));
return;
}

Serial.print(F("Humedad: "));
Serial.println(h);
Serial.print(F("Temperatura: "));
Serial.print(t);
Serial.println(F("°C "));


//If wifi conected ejec this
if (WiFi.status()== WL_CONNECTED){
 HTTPClient http;
      //String in which we save the name of the server and the variables
      String serverPath = nombreserver + "?humedad=" + h + "&temperatura=" + t;
      
      // IP o URL whit the path
      http.begin(serverPath.c_str());
      
      // HTTP GET 
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
}
  delay(10000); //Delay 10 seconds
}
