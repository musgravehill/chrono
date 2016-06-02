
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <util/delay.h>

// Software SPI (slower updates, more flexible pin options):
// pin 9 - Serial clock out (SCLK)
// pin 8 - Serial data out (DIN)
// pin 7 - Data/Command select (D/C)
// pin 6 - LCD chip select (CS)
// pin 5 - LCD reset (RST)
Adafruit_PCD8544 display = Adafruit_PCD8544(9, 8, 7, 6, 5);

volatile bool bullet_is_start = false;
volatile bool bullet_is_end = false;
uint16_t bullet_v;
float bullet_j020 = 0;
float bullet_j025 = 0;

void setup()   {
  display_init();

  cli(); // Global disable interrupts
  Timer0_Init(); // Timer/Counter 0 initialization ( used for micros(), but we disabled timer0 => increase the accuracy )
  Timer1_Init(); // Timer/Counter 1 initialization  ( use this timer for chrono )
  sei(); // Global enable interrupts

  attachInterrupt(0, sensor_first, FALLING); //d2
  attachInterrupt(1, sensor_last, FALLING); //d3
}

void loop() {
  while ( !bullet_is_start && !bullet_is_end ) ;
  _delay_ms(800); // wait 800 ms

  if ( bullet_is_start && bullet_is_end )  {
    //TCNT1=clicks count in timer1, where prescaler=1  => 1 click time is 1/16MHz seconds for "16MHz arduino"
    bullet_v = 0.06 / (TCNT1 * (1.0 / 16000000.0)); // v = s / t,  s=60mm=0.06m
    bullet_j020 = 0.20 * bullet_v * bullet_v / 2000.0; // kg*V^2 / 2
    bullet_j025 = 0.25 * bullet_v * bullet_v / 2000.0; // kg*V^2 / 2

    display_displayInfo();
  }
  else  {
    bullet_v = 0;
    bullet_j020 = 0;
    bullet_j025 = 0;
  }

  TCCR1B = 0;
  TCNT1 = 0;
  bullet_is_start = false;
  bullet_is_end = false;
}

