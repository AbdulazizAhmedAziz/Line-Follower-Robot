#include <reg51.h>

// Define pins
sbit sensor1     = P2^0;  // IR Sensor 1 (active low)
sbit sensor2     = P2^1;  // IR Sensor 2 (active low)
sbit Stop_Signal = P1^0;  // LED (active high)

void delay_1ms(void);
void delay_ms(unsigned int ms);

void main(void) {
    unsigned int time_count;

    // Setup
    Stop_Signal = 0;
    sensor1 = 1;
    sensor2 = 1;

    while (1) {
        // Wait for first sensor to be triggered
        if (sensor1 == 0) {
            time_count = 0;

            // Measure delay until sensor2 is triggered
            while (sensor2 == 1) {
                delay_1ms();
                time_count++;

                // Timeout safeguard (1 second max wait)
                if (time_count > 1000) break;
            }

            // If time between sensors is ≈180 ms, light up LED
            if (time_count < 180) {
                Stop_Signal = 1;
                delay_ms(500);   // LED ON for 500 ms
                Stop_Signal = 0;
            }

            // Wait until car leaves both sensors
            while (sensor1 == 0 || sensor2 == 0);
        }
    }
}

// ~1 ms delay at 12 MHz
void delay_1ms(void) {
    unsigned int i;
    for (i = 0; i < 1275; i++);
}

// General delay function
void delay_ms(unsigned int ms) {
    unsigned int i;
    for (i = 0; i < ms; i++) {
        delay_1ms();
    }
}
