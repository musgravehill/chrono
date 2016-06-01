void display_displayInfo() {
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
}

void display_init(){
  display.begin();
  display.setContrast(70); 
  display.clearDisplay(); 

  display.invertDisplay(true);
  display.setTextSize(2);
  display.setTextColor(BLACK);
  display.setCursor(0,0);
  display.println("Hello, world!");
  delay(1000); 
  
  display.invertDisplay(false);  
  
  display.display();  
  }
