// Author: Esther Lieu,  Emma Reynoso, Alexa Nanevicz, and Matthew Fisher
// Net ID: elieu
// Date: 10/22/2026
// Assignment: Lab 4
//----------------------------------------------------------------------//

#include <avr/io.h>
#include "pwm.h"

#define PWM_TOP 799

void initPWM() {
  // Set PE3 (OC1A) as output
  DDRE |= (1 << PE3);
  
  //Reset Timer 3 registers
    TCCR3A = 0;
    TCCR3B = 0;
    TCNT3 = 0;

  // Set Fast PWM mode with ICR1 as TOP
  TCCR3A |= (1 << WGM31);
  TCCR3B |= (1 << WGM32) | (1 << WGM33);

  // Set non-inverting mode for OC1A
  TCCR3A |= (1 << COM3A1);

  // Set prescaler to 1 and start the timer
  TCCR3B |= (1 << CS30);

  OCR3A = 0; // Initialize duty cycle to 0%

  // Set TOP value for 50Hz PWM frequency
  ICR1 = PWM_TOP; // For a 20MHz clock and prescaler of 8, TOP = (16,000,000 / (50 * 8)) - 1
}

void setPWMDutyCycle(uint8_t dutyCycle) {
  if (dutyCycle > 100) {
    dutyCycle = 100; // Cap the duty cycle at 100%
  }
  
  // Calculate the OCR3A value based on the desired duty cycle
  uint16_t ocrValue = (PWM_TOP * dutyCycle) / 1023;
  
  OCR3A = ocrValue; // Set the new duty cycle
}