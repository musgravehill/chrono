
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

volatile unsigned char bullet_is_start = 0;
volatile unsigned char bullet_is_end = 0;

void setup()   {  
  

  attachInterrupt(0, sensor_first, FALLING); //d2
  attachInterrupt(1, sensor_last, FALLING); //d3
  
  display.begin();
  display.setContrast(70); 
  display.clearDisplay(); 
 
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0,0);
  display.println("Hello, world!");
  display.setTextColor(WHITE, BLACK); // 'inverted' text
  display.println(3.141592);
  display.setTextSize(2);
  display.setTextColor(BLACK);
  display.print("0x"); display.println(0xDEADBEEF, HEX);
  display.display();  

  cli(); // Global disable interrupts 
  Timer0_Init(); // Timer/Counter 0 initialization  - IS NEED?  It used for micros()
  Timer1_Init(); // Timer/Counter 1 initialization  
  sei(); // Global enable interrupts
 
}


void loop() {
   float bullet_j020 = 0;
  float bullet_j025 = 0;
  double bullet_v;  

  while ( bullet_is_start == 0 && bullet_is_end == 0 ) ;
  _delay_ms(800); // wait 800 ms

  if ( bullet_is_start != 0 && bullet_is_end != 0)  {
    bullet_v = 0.06 / (TCNT1 * (1.0 / 16000000.0)); // v = s / t,  s=60mm=0.06m
    bullet_j020 = 0.20 * bullet_v * bullet_v / 2000; // kg*V^2 / 2
    bullet_j025 = 0.25 * bullet_v * bullet_v / 2000; // kg*V^2 / 2  
  }
  else  {
    bullet_v = 0;
    bullet_j020 = 0;
    bullet_j025 = 0;    
  }

  display.clearDisplay();
  display.setTextColor(BLACK);
  display.setTextSize(1);

  display.setCursor(0, 3);
  display.print("M/S");
  display.setCursor(44, 3); //hor,ver
  display.print((int)bullet_v, DEC);

  display.setCursor(0, 15);
  display.print("J.20");
  display.setCursor(44, 15);
  display.println((float)bullet_j020, 2);

  display.setCursor(0, 27);
  display.print("J.25");
  display.setCursor(44, 27);
  display.println((float)bullet_j025, 2);

  display.display();

  TCCR1B = 0;
  TCNT1 = 0;

  bullet_is_start = 0;
  bullet_is_end = 0;
}

