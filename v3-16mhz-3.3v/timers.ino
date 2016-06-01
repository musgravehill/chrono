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
