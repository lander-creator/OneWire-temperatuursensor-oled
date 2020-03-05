// Include the libraries we need
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_ADS1015.h>

Adafruit_ADS1115 ads(0x48);
float temp = 0.0;
float temp1 = 0.0;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


// Data wire is connected to GPIO15
#define ONE_WIRE_BUS 15
// Setup a oneWire instance to communicate with a OneWire device
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature sensors(&oneWire);

DeviceAddress sensor1 = { 0x28, 0x38, 0x44, 0x9B, 0xB, 0x0, 0x0, 0x10 };
DeviceAddress sensor2 = { 0x28, 0x85, 0x3C, 0x9B, 0xB, 0x0, 0x0, 0xE };

void setup() {

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  Serial.begin(115200);
  sensors.begin();
  ads.begin();
}

void loop () {
  Serial.println("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");

  Serial.print("Sensor 1(*C): ");
  Serial.println(sensors.getTempC(sensor1));


  Serial.print("Sensor 2(*C): ");
  Serial.println(sensors.getTempC(sensor2));

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  // Display static text
  display.println("Sensor 1 dallas:");

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  // Display static text
  display.println(sensors.getTempC(sensor1));
  display.display();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 20);
  // Display static text
  display.println("Sensor 2 Dallas:");

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 30);
  // Display static text
  display.println(sensors.getTempC(sensor2));
  display.display();

  int16_t adc0;

  adc0 = ads.readADC_SingleEnded(0);
  temp = (adc0 * 0.1875) / 1000; // convert ADC value into voltage
  temp1 = temp * 10;

  Serial.print("Sensor 3 KTY81: ");
  Serial.println(temp1, 7);
  Serial.println();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 40);
  // Display static text
  display.println("Sensor 3 KTY81:");

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 50);
  // Display static text
  display.println(temp1);
  display.display();


  delay(200);
}
