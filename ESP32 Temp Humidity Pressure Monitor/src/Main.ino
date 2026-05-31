/*

ESP32 Environment Monitor

Reads temperature, humidity, and pressure from a BME280 sensor and
displays onto a 0.96" ST7735s TFT display.
Pressing the button activates the display for 10 seconds while sensor
reads 5x every 2 seconds.

Hardware:
Sunfounder ESP32 Dev Kit
BME280
0.96" ST7735s TFT display
LiPo battery (1000mAh)

Wiring:
BME280: VCC -> 3.3V, GND -> GND, SDA -> GPIO21, SCL -> GPIO22
TFT display: CS -> GPIO5, RST -> GPIO4, DC -> GPIO2, BLK -> GPIO15, SCL -> GPIO18, SDA -> GPIO23
Button: GPIO13, GND

*/

#include <Wire.h>
#include <Adafruit_BME280.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735

// ST7735 display pin definitions
#define TFT_CS 5
#define TFT_RST 4
#define TFT_DC 2
#define TFT_BL 15

// Push button pin
const int button = 13;

// functions
void printMeasurements();

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
Adafruit_BME280 bme;

void setup() 
{
  // button initialization
  pinMode(button, INPUT);

  Serial.begin(115200);
  delay(1000);
  
  // initialize display
  tft.initR(INITR_MINI160x80);
  tft.invertDisplay(true);
  tft.setRotation(1);
  tft.fillScreen(ST77XX_BLACK);

  // backlight will be kept low initially to save power consumption
  pinMode(TFT_BL,OUTPUT);
  digitalWrite(TFT_BL,LOW);

  // initialize sensor
  Wire.begin(21, 22);
  
  // BME not detected
  if (!bme.begin(0x76)) {
    tft.setTextColor(ST77XX_RED);
    tft.setTextSize(1);
    tft.setCursor(5,5);
    tft.println("BME not found!");
    while(1);
  }
}

// Initially the screen will be off until the button is pressed. When pressed the backlight of the lcd screen turns on and loops 
// 5x according to the for loop reading the measurements for temp, humidity, and pressure for a total of 10s before the lcd screen turns off.
void loop() 
{
  // Keep display off when button is not pressed
  tft.sendCommand(0x28);

  // When button is pushed enter if statement
  if(digitalRead(button) == LOW)
  {
    // Blacklight on
    digitalWrite(TFT_BL, HIGH);

    // Display on when button is pressed
    tft.sendCommand(0x29);
    tft.fillScreen(ST77XX_BLACK);
        
    // Updates reading 5x for total of 10s (5 x 2000 = 10000ms (10s))
    for (int i = 0; i < 5; ++i)
    {
    printMeasurements();
    delay(2000);
    }

    // turn off backlight
    digitalWrite(TFT_BL,LOW);
  }
}

// TFT prints sensor measurements
void printMeasurements()
{
  // variables for 3 measurements
  float temp = bme.readTemperature();
  float humidity = bme.readHumidity();
  float pressure = bme.readPressure() / 100.0F;

  // Prints temperature
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
  tft.setCursor(5,46);
  tft.print("Temp: ");
  tft.print(temp);
  tft.println(" C");

  // Prints humidity
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
  tft.setCursor(5,58);
  tft.print("Humidity: ");
  tft.print(humidity);
  tft.println(" %");
  
  // Prints pressure
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
  tft.setCursor(5,70);
  tft.print("Pressure: ");
  tft.print(pressure);
  tft.println(" hPa");
}