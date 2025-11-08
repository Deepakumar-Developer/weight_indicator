#include "HX711.h"

const int LOADCELL_DOUT_PIN = 4; // Connect to HX711 DOUT (Data)
const int LOADCELL_SCK_PIN = 3;  // Connect to HX711 SCK (Clock)
const int green_pin = 12;
const int yellow_pin = 11;
const int red_pin = 10;

const int constantWeight = 100;
const int diffValue = 20;
const int uptoValue = 30;

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
    // If this error shows, check your VCC/GND/DOUT/SCK wiring
    Serial.println("ERROR: HX711 not found. Check your wiring.");
  }

  // STEP 1: Taring (Zeroing the scale)
  // This takes an average of readings to set the current weight as the zero point (offset).
  Serial.print("Taring... Please remove all weight from the sensor.");
  scale.tare();
  Serial.println(" Done. The scale is now zeroed.");
  pinMode(green_pin,OUTPUT);
  pinMode(red_pin,OUTPUT);
  pinMode(yellow_pin,OUTPUT);

  // STEP 2: Setting the Scale Factor (Crucial for calibration)
  // *** This value MUST be found via calibration (see notes below). ***
  // The value 2280.0 is a common starting point, but yours will be different.
  scale.set_scale(374.9705882352941);
  Serial.println("----------------------------------------------");
  Serial.println("Place a known weight on the sensor for reading...");
}

void loop() {
  // get_units(int times) returns a stable reading (average of 'times' readings)
  // which is already converted using the scale factor and offset (tare).
  float weight = scale.get_units(10); // Average 10 readings for stability

  // Print the final weight reading
  Serial.print("Weight (Units/Grams): ");
  Serial.println(weight, 0); 
  if(weight >= (constantWeight-diffValue) && weight <= (constantWeight+diffValue)) {
    digitalWrite(green_pin, HIGH);
    digitalWrite(yellow_pin,LOW);
    digitalWrite(red_pin,LOW);
  } else if(weight < (constantWeight-diffValue) && weight >= (constantWeight-(diffValue+uptoValue))) {
    digitalWrite(yellow_pin, HIGH);
    digitalWrite(green_pin,LOW);
    digitalWrite(red_pin,LOW);
  } else if(weight > (constantWeight+diffValue) && weight <= (constantWeight+(diffValue+uptoValue))) {
    digitalWrite(red_pin, HIGH);
    digitalWrite(green_pin,LOW);
    digitalWrite(yellow_pin,LOW);
  } else {
    digitalWrite(green_pin,LOW);
    digitalWrite(yellow_pin,LOW);
    digitalWrite(red_pin,LOW);
  }

}
