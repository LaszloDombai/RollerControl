#include <Arduino.h>
#include "MultiMap.h"

// Define pins
const u8_t u8_potPin = A0; // Potentiometer connected to GPIO34 (ADC1_CH6)
const u8_t u8_PwmPin = 5;
const u8_t u8_FullPowerPin = 6;
// PWM settings
const u32_t u32_PwmFreq = 3500;   // PWM frequency in Hz
const u8_t u8_PwmResolution = 10; // 10-bit resolution (0-1023)

u8_t u8_FullPowerOn = 0;
u32_t u32_LoopCntr = 0;
u16_t u16_PotValue = 0;
u32_t u32_PwmVal = 0;

float af32_potValInX[] = {0, 500, 1000, 1500, 2000, 2500, 3000, 3500, 4096};
float af32_PwmOutY[] = {0, 50, 100, 200, 300, 400, 500, 750, 1023};
u8_t u8_MapSize = 9;

void setup()
{
  // Configure PWM
  ledcAttach(u8_PwmPin, u32_PwmFreq, u8_PwmResolution);
  // Set full power pin as output
  pinMode(u8_FullPowerPin, OUTPUT);
  digitalWrite(u8_FullPowerPin, LOW); // Ensure full power is off initially
  // Set potentiometer pin as input
  pinMode(u8_potPin, INPUT);

  // Initialize serial for debugging
  // Serial.begin(115200);
}

void loop()
{

  u32_LoopCntr++;

  // Read potentiometer value (0-4095 for ESP32 ADC)
  u16_PotValue = analogRead(u8_potPin);

  u32_PwmVal = (u32_t)multiMap<float>((float)u16_PotValue, af32_potValInX, af32_PwmOutY, u8_MapSize);

  // Map potentiometer value to PWM duty cycle (0-255)
  // u32_PwmVal = map(u16_PotValue, 0, 4095, 0, 1023);

  // Set PWM duty cycle
  ledcWrite(u8_PwmPin, u32_PwmVal);

  // Set full power pin applying a hysteresis
  if (u16_PotValue < 200)
  {
    u8_FullPowerOn = 1;
  }

  if (u16_PotValue > 350)
  {
    u8_FullPowerOn = 0;
  }

  digitalWrite(u8_FullPowerPin, u8_FullPowerOn);

  // if (0 == (u32_LoopCntr % 16))
  // {
  //   u32_LoopCntr = 0;
  //   // Debug output
  //   Serial.print("Potentiometer: ");
  //   Serial.print(u16_PotValue);
  //   Serial.print(" | PWM Value: ");
  //   Serial.println(u32_PwmVal);
  // }
  // Small delay for stability
  delay(100);
}