// Author: Esther Lieu,  Emma Reynoso, Alexa Nanevicz, and Matthew Fisher
// Net ID: elieu
// Date: 10/22/2026
// Assignment: Lab 4
//----------------------------------------------------------------------//

#ifndef PWM_H
#define PWM_H

// Initialize Timer 3 for PWM output
void initPWM();

// Change PWM duty cycle based on ADC reading
void changeDutyCycle(unsigned int adcValue);

#endif
