/****************************************
 * Include Libraries and defines
 ****************************************/
#include "Ubidots.h"
#include "DHT.h"
#define pin1 15
/****************************************
 * Define Instances and Constants
 ****************************************/
const char* UBIDOTS_TOKEN = "BBFF-v8jOOiuNXLnyLKLajo6YFFBaZHkvYQ";  // Put here your Ubidots TOKEN
const char* UBIDOTS_DEVICELABEL = "http-esp32"; // Device label to use
const char* WIFI_SSID = "Temp";      // Put here your Wi-Fi SSID
const char* WIFI_PASS = "HolaPau1";      // Put here your Wi-Fi password
Ubidots ubidots(UBIDOTS_TOKEN, UBI_HTTP);
// Ubidots ubidots(UBIDOTS_TOKEN, UBI_TCP); // Uncomment to use TCP
// Ubidots ubidots(UBIDOTS_TOKEN, UBI_UDP); // Uncomment to use UDP
// Space to store values to send
char str_temp[10];
char str_hum[10];
DHT dht1(pin1, DHT11);    //El sensor de temp y humedad azul.
/****************************************
 * Main Functions
 ****************************************/
void setup() {
  Serial.begin(115200);
  ubidots.wifiConnect(WIFI_SSID, WIFI_PASS);
  // ubidots.setDebug(true);  // Uncomment this line for printing debug messages
  // Sensor de temp y humedad
  dht1.begin();
}
void loop() {
  float t1 = dht1.readTemperature();
  float h1 = dht1.readHumidity();
  Serial.print("  1. La temperatura detectada en el sensor es de: ");
  Serial.println(t1); // Imprime temperatura en el serial monitor
  Serial.print("  2. La humedad detectada por el sensor es de: ");
  Serial.println(h1); // Imprime la humedad en el monitor serial
  Serial.println("  Enviando Temperatura al disp virtual en ubidots via HTTP....");
  ubidots.add("temperatura", t1);  // Change for your variable name
  Serial.println("  Enviando Humedad al dispositivo virtual en ubidots via HTTP....");
  ubidots.add("humedad", h1);
  bool bufferSent = false;
  bufferSent = ubidots.send(UBIDOTS_DEVICELABEL);  // Will send data to a device label that matches the device Id
  if (bufferSent) {
    // Do something if values were sent properly
    Serial.println("Valores enviados al dispositivo en ubidots");
  }
  Serial.println("Esperare unos segundos para volver a leer y enviar....");
  Serial.println(".....................................................");
  delay(8000);
}
