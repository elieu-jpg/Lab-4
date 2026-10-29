// Author: Esther Lieu,  Emma Reynoso, Alexa Nanevicz, and Matthew Fisher
// Net ID: elieu
// Date: 10/22/2026
// Assignment: Lab 4
//----------------------------------------------------------------------//

 // Author: Esther Lieu, Emma Reynoso, Alexa Nanevicz, and Matthew Fisher
 // Net ID: elieu
 // Date: 10/22/2026
 // Assignment: Lab 4
 //----------------------------------------------------------------------//

#include <avr/io.h>
#include "pwm.h"

#define PWM_TOP 799

void initPWM() {
    // Set PE3 (OC3A) as output for Timer 3 PWM
    DDRE |= (1 << PE3);

    // Reset Timer 3 control registers and counter
    TCCR3A = 0;
    TCCR3B = 0;
    TCNT3 = 0;

    // Set Fast PWM mode 14 with ICR3 as TOP
    TCCR3A |= (1 << WGM31);
    TCCR3B |= (1 << WGM32) | (1 << WGM33);

    // Set non-inverting mode for OC3A
    TCCR3A |= (1 << COM3A1);

    // Set TOP value for 20 kHz PWM frequency
    // With a 16 MHz clock and prescaler of 1
    ICR3 = PWM_TOP;

    // Initialize duty cycle to 0%
    OCR3A = 0;

    // Set prescaler to 1 and start Timer 3
    TCCR3B |= (1 << CS30);
}

void changeDutyCycle(unsigned int adcValue) {
    // Limit ADC value to the 10-bit maximum
    if (adcValue > 1023) {
        adcValue = 1023;
    }

    // Convert the 10-bit ADC value (0-1023)
    // into a PWM compare value (0-799)
    unsigned long ocrValue =
        ((unsigned long)adcValue * PWM_TOP) / 1023;

    // Update OCR3A to change the PWM duty cycle
    OCR3A = ocrValue;
}
