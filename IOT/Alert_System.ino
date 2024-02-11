#define BLYNK_TEMPLATE_ID "TMPL3e8SZFbkr"
#define BLYNK_TEMPLATE_NAME "Anti Ragging Notification Using ESP8266"
#define BLYNK_AUTH_TOKEN "75CKpnBN7e2YqnCfnhkEMlq6x_TnzmBE"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

const int switchPin = D7;
int switchState = 0;
char auth[] = "75CKpnBN7e2YqnCfnhkEMlq6x_TnzmBE";
char ssid[] = "Galaxy F41DBFB";
char pass[] = "MILKYBAR";

void setup()
{
    Serial.begin(115200);
    pinMode(switchPin, INPUT); 
    Blynk.begin(auth, ssid, pass);
}

void loop()
{
    Blynk.run();
    switchState = digitalRead(switchPin);

    if (switchState == LOW)
    {
        sendNotification();
        delay(3000);
    }
}

void sendNotification()
{
    Blynk.logEvent("Ragging_Alert", "Switch pressed! Help me!");
}