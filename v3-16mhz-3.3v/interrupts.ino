void sensor_first() {
  if ( bullet_is_start == 0 )  {
    TCCR1B = (1 << CS10); // Timer/Counter 1 running (no prescaling)
    bullet_is_start = true;
  }
}

void sensor_last() {
  if ( bullet_is_end == 0 )  {
    TCCR1B = 0; // Timer/Counter 1 stopped (no clock source)
    bullet_is_end = true;
  }
}
