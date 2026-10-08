#include <WiFi.h>
#include <WebServer.h>
#include <Update.h>

const char* ssid = "ESP32_OTA";
const char* password = "12345678";

WebServer server(80);

const char* uploadPage =
"<form method='POST' action='/update' enctype='multipart/form-data'>"
"<input type='file' name='update'>"
"<input type='submit' value='Update'>"
"</form>";

void setup() {

  Serial.begin(115200);

  WiFi.softAP(ssid, password);

  Serial.println("Hotspot Started");
  Serial.println(WiFi.softAPIP());

  server.on("/", HTTP_GET, []() {
    server.send(200, "text/html", uploadPage);
  });

  server.on("/update", HTTP_POST, []() {
    server.send(200, "text/plain", Update.hasError() ? "Update Failed" : "Update Success! Rebooting...");
    delay(1000);
    ESP.restart();
  }, []() {

    HTTPUpload& upload = server.upload();

    if (upload.status == UPLOAD_FILE_START) {
      Update.begin(UPDATE_SIZE_UNKNOWN);
    }
    else if (upload.status == UPLOAD_FILE_WRITE) {
      Update.write(upload.buf, upload.currentSize);
    }
    else if (upload.status == UPLOAD_FILE_END) {
      Update.end(true);
    }

  });

  server.begin();
}

void loop() {

  server.handleClient();

}