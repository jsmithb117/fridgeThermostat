#include <Wire.h>
#include <Adafruit_BMP085.h>

// Create an instance of the BMP085 sensor
Adafruit_BMP085 bmp;

// Define the relay pin
const int relayPin = 23; // Change to your desired pin

// Temperature thresholds in Fahrenheit
const float tempActivateRelay = 32.5;
const float tempDeactivateRelay = 34.0;

// Helper function to convert Celsius to Fahrenheit
float celsiusToFahrenheit(float celsius) {
  return (celsius * 9.0 / 5.0) + 32.0;
}

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  Serial.println("BMP085 Sensor and Relay Control");

  // Initialize the relay pin
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW); // Start with the relay off

  // Initialize the BMP085 sensor
  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP085 sensor, check wiring!");
    while (1); // Halt execution
  }
}

void loop() {
  // Read the temperature in Celsius
  float temperatureC = bmp.readTemperature();

  // Convert temperature to Fahrenheit
  float temperatureF = celsiusToFahrenheit(temperatureC);
  Serial.print("Temperature: ");
  Serial.print(temperatureF);
  Serial.println(" °F");

  // Relay control logic
  if (temperatureF < tempActivateRelay) {
    digitalWrite(relayPin, HIGH); // Enable the relay
    Serial.println("Relay ON");
  } else if (temperatureF > tempDeactivateRelay) {
    digitalWrite(relayPin, LOW); // Disable the relay
    Serial.println("Relay OFF");
  }

  delay(1000); // Delay 1 second between readings
}
