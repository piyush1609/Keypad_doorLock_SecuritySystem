#include <Wire.h>
#include <Servo.h>
#include <Keypad.h>

Servo ServoMotor;

int i =0, passwordLength = 7;
char password[7] = "123456";    // change the password here, just pick any 6 numbers
char userInput[7];
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};                    
bool status = true ;     
char key;                        
byte rowPins[ROWS] = { A2, 3, 4, 5 };
byte colPins[COLS] = { 6, 7, 8, 11 };
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
int RedpinLock = 12;
int GreenpinUnlock = 13;

void setup()
{Serial.begin(9600);
pinMode(RedpinLock, OUTPUT);
pinMode(GreenpinUnlock, OUTPUT);
pinMode(10,OUTPUT);
//pinMode(10, INPUT);
ServoMotor.attach(9);
LockedPosition(true);
Wire.begin();  
//pinMode(2,INPUT_PULLUP); //ig input pullup doesnt work during inrruppt
attachInterrupt(digitalPinToInterrupt(2), buttonPress, RISING);  
}

//piyush add "# " to reenter password....

void loop() 
{Wire.beginTransmission(8);
  key = keypad.getKey();
 //Serial.println(key);
  if (key!= NO_KEY) {
    // Enter keypress into array and increment counter
    if(key != '#'){
    userInput[i] = key;
    i++;
    }else{
        clearData();
    }
        Wire.write(key);

  }
 Wire.endTransmission();
/* if(key = '#'){
    LockedPosition(true);
    clearData();
    } */
 if (i == passwordLength-1) {
    //Serial.print("test1");
    if (!strcmp(userInput, password)) {
         delay(100);
      LockedPosition(false);
      Wire.beginTransmission(8);
    Wire.write("Welcome...");
      Wire.endTransmission();
    }
    else {
      delay(100);
      // Password is incorrect
      LockedPosition(true);
      Wire.beginTransmission(8);
      Wire.write("Try Again!");
      Wire.endTransmission();
    }
    clearData();
  }
  delay(20);
}

void clearData() {
  // clear data
  while (i != 0) {
    userInput[i--] = 0;
  }
  return;
}
  

void LockedPosition(bool locked)
{
if (locked)
{
digitalWrite(RedpinLock, HIGH);
digitalWrite(GreenpinUnlock, LOW);
ServoMotor.write(0);
//tone(10,233,200);  
}
else
{
digitalWrite(RedpinLock, LOW);
digitalWrite(GreenpinUnlock, HIGH);
ServoMotor.write(90);
tone(10,333,200);   
}
}
  
void  buttonPress() {
  
  LockedPosition(status);
  status = !status;
}  
