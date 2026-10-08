#include <WiFi.h>

const char* ssid = "IPCS,3FLOOR";
const char* password = "Ipcs@2026";

WiFiServer server(80);          // its an object. Its creates an object on port 80. It is an open port(it creates server on port 80 as http)
int led = 2;

void setup() {
  Serial.begin(115200);
  pinMode(led, OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);                      // if not connect .... will be shown nd if conneted ip address will be shown

  Serial.println(WiFi.localIP());   // print IP
  server.begin();                   // server starts
}

void loop() {
  WiFiClient client = server.available();            // checking client connection

  if (client) {
    String req = client.readStringUntil('\r');            // carrier
    client.flush();                                        //for resetting the values in client

    if (req.indexOf("/on") != -1) digitalWrite(led, HIGH);
    if (req.indexOf("/off") != -1) digitalWrite(led, LOW);

    client.println("HTTP/1.1 200 OK");                 // for checking http link
    client.println("Content-type:text/html\n");            //startinh html
  
    client.println("<head><title>Controlling led with local server</title></head>");
    client.println("<body><h2>Control LED</h2><p>To turn on the LED click <em>ON</em>.To turn off the LED click <em>OFF</em></p></body>");
    client.println("<a href='/on'>ON</a><br>");
    client.println("<a href='/off'>OFF</a><br>");

    client.stop();
  }
}
