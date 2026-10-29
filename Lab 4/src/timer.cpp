// Author: Esther Lieu,  Emma Reynoso, Alexa Nanevicz, and Matthew Fisher
// Net ID: elieu
// Date: 10/22/2026
// Assignment: Lab 4
//----------------------------------------------------------------------//
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"

// Flag to indicate when button debouncing is complete
volatile unsigned char debounceComplete = 0;

// Tracks the number of seconds during countdown
volatile unsigned char secondsElapsed = 0;

// Counter for the 20 ms debounce delay
volatile unsigned char debounceCount = 0;

// Initialize Timer 0 for button debouncing
void initTimer0() {
    // Reset Timer 0 registers
    TCCR0A = 0;
    TCCR0B = 0;
    TCNT0 = 0;

    // Set Timer 0 to CTC mode
    TCCR0A |= (1 << WGM01);

    // Set compare value for 1 ms
    // 16 MHz / 64 / 1000 - 1 = 249
    OCR0A = 249;

    // Enable Timer 0 compare match A interrupt
    TIMSK0 |= (1 << OCIE0A);
}

// Start Timer 0 for button debouncing
void startTimer0() {
    // Reset debounce counter and flag
    debounceCount = 0;
    debounceComplete = 0;

    // Reset Timer 0 counter
    TCNT0 = 0;

    // Clear any pending compare match interrupt
    TIFR0 = (1 << OCF0A);

    // Set prescaler to 64 and start Timer 0
    TCCR0B |= (1 << CS01) | (1 << CS00);
}

// Stop Timer 0
void stopTimer0() {
    // Clear clock select bits to stop timer
    TCCR0B &= ~((1 << CS02) | (1 << CS01) | (1 << CS00));
}

// Timer 0 interrupt occurs every 1 ms
ISR(TIMER0_COMPA_vect) {
    // Increment debounce counter
    debounceCount++;

    // Check if 20 ms has passed
    if (debounceCount >= 20) {
        // Stop Timer 0 after debouncing
        stopTimer0();

        // Set flag to indicate debouncing is complete
        debounceComplete = 1;
    }
}
