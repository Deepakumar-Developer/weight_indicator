#include "HX711.h"

const int LOADCELL_DOUT_PIN = 4; // Connect to HX711 DOUT (Data)
const int LOADCELL_SCK_PIN = 3;  // Connect to HX711 SCK (Clock)
// Pin Configuration 
const int green_pin = 12;
const int yellow_pin = 11;
const int red_pin = 10;
// Weight Configuration 
const int constantWeight = 100; 
const int diffValue = 2;
const int uptoValue = 10;

// Initialize the HX711 library object
HX711 scale;

void setup() {
  // Start serial communication for monitor output
  Serial.begin(9600);
  Serial.println("--- HX711 Load Cell Reader Initialized ---");

  // Start communication with the sensor
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  // Check if the sensor is recognized
  if (scale.is_ready()) {
    Serial.println("HX711 is connected and ready.");
  } else {
    Serial.println("ERROR: HX711 not found. Check your wiring.");
  }

  Serial.print("Taring... Please remove all weight from the sensor.");
  scale.tare();
  Serial.println(" Done. The scale is now zeroed.");
  pinMode(green_pin,OUTPUT);
  pinMode(red_pin,OUTPUT);
  pinMode(yellow_pin,OUTPUT);

  scale.set_scale(374.9705882352941);
  Serial.println("----------------------------------------------");
  Serial.println("Place a known weight on the sensor for reading...");
}

void loop() {
  float weight = scale.get_units(10); // Average 10 readings for stability

  // Print the final weight reading
  Serial.print("Weight (Units/Grams): ");
  Serial.println(weight, 0); 

  if(weight >= (constantWeight-diffValue) && weight <= (constantWeight+diffValue)) {
    // Green Glow -> 98 to 102
    digitalWrite(green_pin, HIGH);
    digitalWrite(yellow_pin,LOW);
    digitalWrite(red_pin,LOW);
  } else if(weight < (constantWeight-diffValue) && weight >= (constantWeight-(diffValue+uptoValue))) {
		// Yello Glow -> 88 to 97
		digitalWrite(yellow_pin, HIGH);
    digitalWrite(green_pin,LOW);
    digitalWrite(red_pin,LOW);
  } else if(weight > (constantWeight+diffValue) && weight <= (constantWeight+(diffValue+uptoValue))) {
		// Red Glow -> 103 to 112
		digitalWrite(red_pin, HIGH);
    digitalWrite(green_pin,LOW);
    digitalWrite(yellow_pin,LOW);
  } else {
		// All Light off when the weight not in 88 to 112
    digitalWrite(green_pin,LOW);
    digitalWrite(yellow_pin,LOW);
    digitalWrite(red_pin,LOW);
  }
}
