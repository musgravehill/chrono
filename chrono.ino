#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <util/delay.h>

Adafruit_PCD8544 display = Adafruit_PCD8544(11, 10, 9, 8, 7);

volatile unsigned char bullet_is_start = 0;
volatile unsigned char bullet_is_end = 0;

// Timer/Counter 0 initialization
void Timer0_Init( void )
{
  TCNT0 = 0;

  // Bits: COM0A1 COM0A0 COM0B1 COM0B0 - - WGM01 WGM00
  TCCR0A = 0;

  // Bits: FOC0A FOC0B - - WGM02 CS02 CS01 CS00
  TCCR0B = 0;

  // Bits: - - - - - OCIE0B OCIE0A TOIE0
  TIMSK0 = 0;

  // Bits: - - - - - OCF0B OCF0A TOV0
  TIFR0 = 0;
}

// Timer/Counter 1 initialization
void Timer1_Init( void )
{
  TCNT1 = 0;

  // Bits: COM1A1 COM1A0 COM1B1 COM1B0 - - WGM11 WGM10
  TCCR1A = 0;

  // Bits: ICNC1 ICEbullet_is_start - WGM13 WGM12 CS12 CS11 CS10
  TCCR1B = 0;

  // Bits: FOC1A FOC1B - - - - - -
  TCCR1C = 0;

  // Bits: - - ICIE1 - - OCIE1B OCIE1A TOIE1
  TIMSK1 = 0;

  // Bits: – – ICF1 – - OCF1B OCF1A TOV1
  TIFR1 = 0;
}

void setup()
{
  Serial.begin(9600);

  //pinMode(13, OUTPUT); //LCD backlight
  //digitalWrite(13, HIGH);

  display.begin();
  display.setContrast(80);
  display.clearDisplay();
  display.setTextColor(BLACK);
  display.setCursor(0, 2);
  display.setTextSize(2);
  display.println("chrono v.2");
  display.display();

  // Global disable interrupts
  cli();

  // Timer/Counter 0 initialization
  Timer0_Init();

  // Timer/Counter 1 initialization
  Timer1_Init();

  // Global enable interrupts
  sei();

  attachInterrupt(0, sensor_1, FALLING);
  attachInterrupt(1, sensor_2, FALLING);
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

void sensor_1()
{
  if ( bullet_is_start == 0 )  {
    TCCR1B = (1 << CS10); // Timer/Counter 1 running (no prescaling)
    bullet_is_start = 1;
  }
}

void sensor_2()
{
  if ( bullet_is_end == 0 )  {
    TCCR1B = 0; // Timer/Counter 1 stopped (no clock source)
    bullet_is_end = 1;
  }
}
