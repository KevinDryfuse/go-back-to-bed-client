// LCD
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);

void setup() {
  Serial.begin(9600);
  lcd.init();  //initialize the lcd
  lcd.backlight();  //open the backlight
  lcd_print(1, "Line 1 1234567890123");
  lcd_print(2, "Line 2 1234567890123");
  lcd_print(3, "Line 3 1234567890123");
  lcd_print(4, "Line 4 1234567890123");
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
