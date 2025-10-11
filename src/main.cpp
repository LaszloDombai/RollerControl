#include <Arduino.h>
#include "MultiMap.h"

// Define pins
const u8_t u8_HallPin = A0; // Potentiometer connected to GPIO34 (ADC1_CH6)
const u8_t u8_PwmPin = 5;
const u8_t u8_FullPowerPin = 6;
// PWM settings
const u32_t u32_PwmFreq = 3500;   // PWM frequency in Hz
const u8_t u8_PwmResolution = 10; // 10-bit resolution (0-1023)

u8_t u8_FullPowerOn = 0;
u32_t u32_LoopCntr = 0;
u16_t u16_HallValue = 0;
u32_t u32_PwmVal = 0;

/* Hall sensor */
// Low = 765 mV
// High = 2.4 V
// Vcc = 3.15 V
// AD_low = 765 * 4096 / 3.15 = 994
// AD_high = 2400 * 4096 / 3.15 = 3120

float af32_HallSensorSax[] = {1250, 1293, 1586, 1879, 2171, 2464, 2757, 3500};
float af32_PwmOutCrv[] =     {1023, 877, 731, 585, 438, 292, 146, 0};

u8_t u8_CrvSize = 8;

void setup()
{
  // Configure PWM
  ledcAttach(u8_PwmPin, u32_PwmFreq, u8_PwmResolution);
  // Set full power pin as output
  pinMode(u8_FullPowerPin, OUTPUT);
  digitalWrite(u8_FullPowerPin, LOW); // Ensure full power is off initially
  // Set potentiometer pin as input
  pinMode(u8_HallPin, INPUT);

  // Initialize serial for debugging
   Serial.begin(115200);
}

void loop()
{

  u32_LoopCntr++;

  u16_HallValue = analogRead(u8_HallPin);

  u32_PwmVal = (u32_t)multiMap<float>((float)u16_HallValue, af32_HallSensorSax, af32_PwmOutCrv, u8_CrvSize);

  ledcWrite(u8_PwmPin, u32_PwmVal);

  // Set full power pin applying a hysteresis
  if (u32_PwmVal <= 0)
  {
    u8_FullPowerOn = 1;
  }

  if (u32_PwmVal > 3)
  {
    u8_FullPowerOn = 0;
  }

  digitalWrite(u8_FullPowerPin, u8_FullPowerOn);

  if (0 == (u32_LoopCntr % 16))
  {
    u32_LoopCntr = 0;
    // Debug output
    Serial.print("Potentiometer: ");
    Serial.print(u16_HallValue);
    Serial.print(" | PWM Value: ");
    Serial.println(u32_PwmVal);
  }
  // Small delay for stability
  delay(100);
}