#include "M5StickCPlus.h"
#include <WiFi.h>
#include <HTTPClient.h>

// Update these with values suitable for your network.
const char* ssid = "<Enter your WiFi SSID (name)>";
const char* password = "<WiFi Password>";

WiFiClient espClient;

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.println();
  M5.Lcd.setTextSize(1.5);
  M5.Lcd.setCursor(0, 50);
  M5.Lcd.print("Connecting to ");
  M5.Lcd.println(ssid);

  //WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    M5.Lcd.print(".");
  }

  randomSeed(micros());

  M5.Lcd.println("");
  M5.Lcd.println("WiFi connected");
  M5.Lcd.println("IP address:");
  M5.Lcd.println(WiFi.localIP());

  // Set BLACK to the background color.
  M5.Lcd.fillScreen(BLACK);  
  M5.Lcd.setCursor(0, 0);

  display_bell();
}

void setup() {
  delay(500);
  // When opening the Serial Monitor, select 9600 Baud
  M5.begin();
  delay(500);
  setup_wifi();
}

void display_bell()
{
    // Adding Graphics
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0, 50);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(3);
    M5.Lcd.printf("Press\nButton\nto\nRing\nBell");

}

void loop() {

    if (WiFi.status() != WL_CONNECTED){
      setup_wifi();
    }

    M5.update();  // Read the press state of the key.
    if (M5.BtnA.wasReleased()) { 

          //IFTT - Slack Post Request
          HTTPClient http;
          http.begin("<ENTER THE IFTTT WebHook URL HERE>");
          http.GET();
          http.end();

          M5.Lcd.fillScreen(BLACK);
          M5.Lcd.setTextSize(2.8);
          M5.Lcd.setCursor(0, 50);
          M5.Lcd.println("\nNotified!\nPlease\nwait..");
          delay(5000);
          display_bell();
    }
}
