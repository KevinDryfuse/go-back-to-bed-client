// LCD
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);

// WIFI
#include <ArduinoHttpClient.h>
#include <SPI.h>
#include <WiFiNINA.h>
#include <ArduinoJson.h>

#include "arduino_secrets.h"
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

WiFiClient wifi;
int status = WL_IDLE_STATUS;

void setup() {
  Serial.begin(9600);
  lcd.init();  //initialize the lcd
  lcd.backlight();  //open the backlight

  while (!Serial);
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);     // print the network name (SSID);
    Serial.println(pass);     // print the network name (SSID);
    delay(1000);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);
  }

  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

}

void loop() {
  Serial.println("20x4 LCD Base Setup");
  delay(10000);
}

void lcd_print(int row, String message) {
  message = message.substring(0, 20);
  lcd.setCursor(0,row - 1);
  lcd.print(pad_with_spaces(message));
}

String pad_with_spaces(String output_to_pad) {
  String empty_screen = "                    ";
  int whitespace_size = empty_screen.length() - output_to_pad.length();
  return output_to_pad + empty_screen.substring(0, whitespace_size);
}
