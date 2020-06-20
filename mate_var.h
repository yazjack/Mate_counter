#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);

#define btn D0 //button pin
#define led_red D4 //led pin
#define led_grn D3 //led pin

String payload;

//20 digit SSL fingerprint goes here, valid through September 6, 2019
const uint8_t fingerprint[20] = {0x0F, 0x78, 0xD8, 0x8D, 0x26, 0xE4, 0x58, 0xB8, 0xDB, 0x2B, 0x60, 0x2E, 0xBB, 0xEC, 0x1B, 0xCB, 0xC1, 0x2D, 0x5A, 0x7D};
char wifi_AP[] = "hacker:space:public"; //name of AP
char wifi_pass[] = "przyjmujemy_datki_x86"; //password for AP
char counter_URL[] = "https://mate.at.hs3.pl/one"; //URL used for counting
char app_URL[] = "https://mate.at.hs3.pl"; //URL that returns stock ammount
