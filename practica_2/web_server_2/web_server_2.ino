#include <WiFi.h>
WiFiServer server(80);
WiFiClient client;

const char* ssid = "IoT";
const char* password = "1t3s0IoT23";
String estado = "";
#define LED 15
#define LED_INTERNO 2

void setup() {
  Serial.begin(9600);

  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  pinMode(LED_INTERNO, OUTPUT);
  digitalWrite(LED_INTERNO, LOW);
  
  WiFi.disconnect();
  delay(3000);
  Serial.println("Iniciando");
  WiFi.begin(ssid, password);
  while ((!(WiFi.status() == WL_CONNECTED))){
    Serial.print("......");
    delay(300);
  }
  Serial.println("Conexion establecida con el SSDI!");
  Serial.println((WiFi.localIP()));
  server.begin();
}

void loop() {
  // Consulta si se ha conectado algún cliente.
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  Serial.print("Nuevo cliente: ");
  Serial.println(client.remoteIP());
  // Espera hasta que el cliente envíe datos.
  while(!client.available()){
    delay(1);
  }
  /////////////////////////////////////////////////////
  // Lee la información enviada por el cliente.
  String req = client.readStringUntil('\r');
  Serial.println(req);
  // Realiza la petición del cliente.
  
  if (req.indexOf("on2") != -1){
    digitalWrite(LED, HIGH);
    digitalWrite(LED_INTERNO, HIGH);
    estado = "Encendido";
  }
  
  if (req.indexOf("off2") != -1){
    digitalWrite(LED, LOW);
    digitalWrite(LED_INTERNO, LOW);
    estado = "Apagado";
  }
  //////////////////////////////////////////////
  // Página WEB. ////////////////////////////
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); // Importante.
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head><meta charset=utf-8></head>");
  client.println("<body><center><font face='Arial'>");
  client.println("<h1>Servidor web con ESP32.</h1>");
  client.println("<h1>Alberto Romano</h1>");
  client.println("<h2><font color='#009900'>Webserver 1.0</font></h2>");
  client.println("<h3>Práctica boton</h3>");
  client.println("<br><br>");
  client.println("<a href='on2'><button>Enciende LED</button></a>");
  client.println("<a href='off2'><button>Apaga LED</button></a>");
  client.println("<br><br>");
  client.println(estado);
  client.println("</font></center></body></html>");
  Serial.print("Cliente desconectado: ");
  Serial.println(client.remoteIP());
  client.flush();
  client.stop();
}
