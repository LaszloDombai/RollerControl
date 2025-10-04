#include <Arduino.h>

// Define pins
const int potPin = A0;    // Potentiometer connected to GPIO34 (ADC1_CH6)
const int pwmPin = 5;    
const int fullPowerPin = 6;
// PWM settings
const int pwmFreq = 3500; // PWM frequency in Hz
const int pwmResolution = 10; // 10-bit resolution (0-1023)

// Variables
int potValue = 0;
int pwmValue = 0;


void setup() {
  // Configure PWM
  ledcAttach(pwmPin, pwmFreq, pwmResolution);
  // Set full power pin as output
  pinMode(fullPowerPin, OUTPUT);
  digitalWrite(fullPowerPin, LOW); // Ensure full power is off initially
  // Set potentiometer pin as input    
  pinMode(potPin, INPUT);

  // Initialize serial for debugging
  // Serial.begin(115200);
}

void loop() {
  // Read potentiometer value (0-4095 for ESP32 ADC)
  potValue = analogRead(potPin);
  
  // Map potentiometer value to PWM duty cycle (0-255)
  pwmValue = map(potValue, 0, 4095, 0, 1023);
  
  // Set PWM duty cycle
  ledcWrite(pwmPin, pwmValue);
  
  // Set full power pin based on potentiometer value
  if (potValue > 3800) { 
    digitalWrite(fullPowerPin, HIGH); // Full power ON
  } else {
    digitalWrite(fullPowerPin, LOW);  // Full power OFF
  } 

  // Print values for debugging
  // Serial.print("Potentiometer: ");
  // Serial.print(potValue);
  // Serial.print(" | PWM Value: ");
  // Serial.println(pwmValue);
  
  // Small delay for stability
  delay(100);
}