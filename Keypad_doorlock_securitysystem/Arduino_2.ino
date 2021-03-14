#include <LiquidCrystal.h>
#include <Wire.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
long Interval = 3000;
long PreviousMills= 0;
bool messAvailable = false;
void setup() {
  lcd.begin(16,2);
  Serial.begin(9600);
  //lcd.print("hello");
  //lcd.setCursor(1,0);
  Wire.begin(8);
  Wire.onReceive(dataReceived);

}

void loop() {
  delay(200);
}

void dataReceived(int howMany) {
      messAvailable = true;
  while (1 < Wire.available()) { 
    if(messAvailable){
      Serial.println("Inside Available");
      lcd.clear();
      messAvailable = false;
    }
    char c = Wire.read();
    lcd.print(c);
//  lcd.setCursor(1,0);
//    delay(2000);
//    lcd.clear();
    //unsigned long currentMills = millis();

    //if(currentMills - PreviousMills >= Interval)
    //{lcd.clear();
   //  Serial.print(currentMills - PreviousMills);
    // PreviousMills = currentMills;
    //}
  
  }
  int x = Wire.read(); 
  if(x != -1)
  {
      lcd.print(char(x));
    if(char(x) == '#'){
      lcd.clear();
    }
  }
  
}
