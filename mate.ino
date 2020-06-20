#include "mate_var.h"

ESP8266WiFiMulti WiFiMulti;

void setup() {

  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
     Serial.println(F("SSD1306 allocation failed"));
     for (;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Booting ...");
  display.display();

  pinMode(btn, INPUT);

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(wifi_AP, wifi_pass);

  delay(5000);

  if ((WiFiMulti.run() == WL_CONNECTED)) {
    std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
    client->setFingerprint(fingerprint);

    HTTPClient https;

    if (https.begin(*client, app_URL)) {
      int httpCode = https.GET();

      if (httpCode > 0) {
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = https.getString();
          int number = payload.toInt();

          if (number > 0) {
            displayStock();
            display.println(payload);
            display.display();
          } else {
            displayWarning();
          }
        }
      }
      https.end();
    }
  }
}


void loop() {
  int button_chk = digitalRead(btn);

  if ((WiFiMulti.run() == WL_CONNECTED)) {
    if (button_chk == HIGH) {
      std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
      client->setFingerprint(fingerprint);

      HTTPClient https;

      if (https.begin(*client, counter_URL)) {
        int httpCode = https.GET();
        if (httpCode > 0) {
          https.end();
        }
      }

      if (https.begin(*client, app_URL)) {
        int httpCode = https.GET();
        if (httpCode > 0) {
          if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
            String payload = https.getString();
            int number = payload.toInt();
            if (number > 0) {
              displayStock();
              display.println(payload);
              display.display();
            } else {
              displayWarning();
            }
          }
        }
        https.end();
      }
    }
  }
}

void displayStock() {
  display.clearDisplay();
  display.display();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Mate left:");
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(0, 16);
}

void displayWarning() {
  display.clearDisplay();
  display.display();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("There's no mate!");
  display.display();
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(0, 16);
  display.println("WE ARE DOOMED!");
  display.display();
}
