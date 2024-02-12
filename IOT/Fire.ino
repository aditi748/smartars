#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#define DATABASE_URL "https://smartantiragging-default-rtdb.firebaseio.com/"
#define API_KEY "AIzaSyBoWTjHfXefLrgiDNl6eN5KaHmRjGVn890"
#define WIFI_SSID "Galaxy F41DBFB"
#define WIFI_PASSWORD "MILKYBAR"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
bool signupOK = false;

#define LED D5
#define touchPin D7

void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(touchPin, INPUT);
  Serial.begin(9600);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.print("Connected to- ");
  Serial.println(WIFI_SSID);

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  if (Firebase.signUp(&config, &auth, "", ""))
  {
    Serial.println("ok");
    signupOK = true;
  }
  else
  {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  config.token_status_callback = tokenStatusCallback;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop()
{
  int touchState = digitalRead(touchPin); // Reads the status of the touch sensor.
  int data = 0;

  if (touchState == HIGH) // If the touch sensor is touched
  {
    Firebase.RTDB.setInt(&fbdo, "/POST", 1);
    digitalWrite(LED, HIGH); // LED ON
  }
  else
  {
    Firebase.RTDB.setInt(&fbdo, "/POST", 0);
    digitalWrite(LED, LOW);
  }

  Serial.println(data);
}
