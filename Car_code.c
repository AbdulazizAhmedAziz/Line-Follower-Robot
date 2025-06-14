#include <reg51.h>

// Define bit addresses using sbit
sbit MOT1    = P2^0;   // Motor 1
sbit MOT2    = P2^1;   // Motor 2
sbit MOT3    = P2^2;   // Motor 3
sbit MOT4    = P2^3;   // Motor 4
sbit S_LEFT  = P2^4;   // Left Sensor
sbit S_RIGHT = P2^5;   // Right Sensor
sbit RADAR   = P1^0;   // RADAR STATE

// Function prototypes
void forward(void);
void left(void);
void right(void);
void stop(void);

void main(void) {
    // Initialize ports with pull-ups
    S_LEFT  = 1;  // Enable pull-up for left sensor
    S_RIGHT = 1;  // Enable pull-up for right sensor
    RADAR   = 1;  // Enable pull-up for radar

    while (1) {  // Infinite loop
        if (RADAR) {
            stop();  // If radar detects obstacle
        } else {
            if (S_LEFT) {
                if (S_RIGHT) {
                    stop();  // Both sensors activated
                } else {
                    left();  // Only left sensor activated
                }
            } else {
                if (S_RIGHT) {
                    right();  // Only right sensor activated
                } else {
                    forward();  // No sensors activated
                }
            }
        }
    }
}

// Motor control functions
void forward(void) {
    MOT1 = 0;
    MOT2 = 1;
    MOT3 = 1;
    MOT4 = 0;
}

void left(void) {
    MOT1 = 0;
    MOT2 = 1;
    MOT3 = 0;
    MOT4 = 0;
}

void right(void) {
    MOT1 = 0;
    MOT2 = 0;
    MOT3 = 1;
    MOT4 = 0;
}

void stop(void) {
    MOT1 = 0;
    MOT2 = 0;
    MOT3 = 0;
    MOT4 = 0;
}
