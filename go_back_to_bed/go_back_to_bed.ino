// LCD
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);

// LED RING
#include <Adafruit_NeoPixel.h>
#define PIN 12
#define STRIPSIZE 24
#define MAX_BRIGHTNESS 100

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(STRIPSIZE, PIN, NEO_GRB + NEO_KHZ800);

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

// API
const char serverAddress[] = "go-back-to-bed.herokuapp.com";  // server address
int port = 80;
HttpClient client = HttpClient(wifi, serverAddress, port);


void setup() {
  Serial.begin(9600);
  lcd.init();  //initialize the lcd
  lcd.backlight();  //open the backlight

  strip.begin();
  strip.setBrightness(100);
  strip.show(); // Initialize all pixels to 'off'

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
  // assemble the path for the GET message:
  String path = "/api/v1/test";
  client.sendHeader("Cache-Control", "no-cache");
  
  // send the GET request
  Serial.println("making GET request");
  client.get(path);

  // read the status code and body of the response
  int statusCode = client.responseStatusCode();
  String response = client.responseBody();
  Serial.print("Status code: ");
  Serial.println(statusCode);
  DynamicJsonDocument doc(2000);
  deserializeJson(doc, response);
  
  String test_value = doc[F("test")];

  Serial.print(response);
  
  // Print values.
  Serial.print("test value: ");
  Serial.println(test_value);

  for (int pixel = 0; pixel < STRIPSIZE; pixel++) {
    strip.setPixelColor(pixel, strip.Color(0,0,255));
  }
  strip.show();

  for (int brightness = 0; brightness <= MAX_BRIGHTNESS; brightness++) {
    strip.setBrightness(brightness);
    for (int pixel = 0; pixel < STRIPSIZE; pixel++) {
      strip.setPixelColor(pixel, strip.Color(0,0,255));
    }
    strip.show();
    if (brightness == MAX_BRIGHTNESS) {
      delay(100);
    }
    else {
      delay(50);
    }
  }

  for (int brightness = MAX_BRIGHTNESS; brightness >= 0; brightness--) {
    strip.setBrightness(brightness);  
    strip.show();
    if (brightness == 0) {
      delay(100);
    }
    else {
      delay(50);
    }
  }
  delay(1000);
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
