#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Keypad.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1  // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {2, 3, 4, 5};  
byte colPins[COLS] = {6, 7, 8, 9};  

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String distance = "";

void setup() {
    Serial.begin(9600);

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // I2C Address 0x3C
        Serial.println(F("SSD1306 allocation failed"));
        for (;;);
    }
    
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 10);
    display.println("Enter Distance:");
    display.display();
}

void loop() {
    char key = keypad.getKey();

    if (key) {
        if (key >= '0' && key <= '9') {
            distance += key;
        } else if (key == '*') {
            distance = "";  // Clear input
        } else if (key == '#') {
            Serial.println(distance);  // Transmit via TX
            distance = "";  // Reset after transmission
        }

        updateDisplay();
    }
}

void updateDisplay() {
    display.clearDisplay();
    display.setCursor(0, 10);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.println("Enter Distance:");
    display.setTextSize(2);
    display.setCursor(0, 30);
    display.print("Dist: ");
    display.print(distance);
    display.display(); 
}
