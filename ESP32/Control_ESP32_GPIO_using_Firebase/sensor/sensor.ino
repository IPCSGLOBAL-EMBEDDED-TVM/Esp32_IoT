#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <FirebaseClient.h>

#define WIFI_SSID "IPCS,3FLOOR"
#define WIFI_PASSWORD "Ipcs@2026"

#define Web_API_KEY "AIzaSyB50YFeVpn9PGPlBV8HfMq81kTEiUkcYwE"
#define DATABASE_URL "https://sensor-6e53c-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define USER_EMAIL "westfordin7@gmail.com"
#define USER_PASS "Jokuttan@1234"

#define TRIG_PIN 5
#define ECHO_PIN 18

UserAuth user_auth(Web_API_KEY, USER_EMAIL, USER_PASS);

SSL_CLIENT ssl_client;
FirebaseApp app;
AsyncClientClass aClient(ssl_client);
RealtimeDatabase Database;

unsigned long lastSendTime = 0;

float getDistance()
{
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration == 0)
    return -1;

  return duration * 0.034 / 2.0;
}

void processData(AsyncResult &aResult)
{
  if (!aResult.isResult())
    return;

  if (aResult.isError())
  {
    Serial.printf("Error: %s\n",
                  aResult.error().message().c_str());
  }
}

void setup()
{
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println("WiFi Connected");
  Serial.println(WiFi.localIP());

  ssl_client.setInsecure();

  initializeApp(aClient, app, getAuth(user_auth), processData, "authTask");

  app.getApp<RealtimeDatabase>(Database);

  Database.url(DATABASE_URL);
}

void loop()
{
  app.loop();

  if (app.ready() && millis() - lastSendTime > 2000)
  {
    lastSendTime = millis();

    float distance = getDistance();

    Serial.print("Distance: ");
    Serial.println(distance);

    Database.set<float>(
      aClient,
      "/Sensors/Ultrasonic/distance_cm",
      distance,
      processData);

    Database.set<String>(
      aClient,
      "/Sensors/Ultrasonic/status",
      (distance < 20) ? "Object Detected" : "Clear",
      processData);

    Database.set<int>(
      aClient,
      "/Sensors/Ultrasonic/timestamp",
      millis(),
      processData);
  }
}
