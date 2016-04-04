#include <Servo.h>
#include <Keypad.h>

/*  //////////////////////////////////////////////////////////////////
 this is the code... change it... but not the last character...
    possible codes:   {'1','2','3','4','\0'};   --> 1234
                      {'5','A','3','*','\0'};   --> 5A3*
                      {'0','2','7','6','\0'};   --> 276
                      {'0','0','5','6','\0'};   --> 56
                      {'0','0','0','1','\0'};   --> 1
/////////////////////////////////////////////////////////////////////*/                      
char code[5] = {'1','2','3','A','\0'};  
char pressed[5] = {'0','0','0','0','\0'};  //storage array for entered values
int i = 0;
bool toggle = 1;
bool debug = 1;

const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns
// Define the Keymap
char keys[ROWS][COLS] = {
  {'A','3','2','1'},
  {'B','6','5','4'},
  {'C','9','8','7'},
  {'D','#','0','*'}
};
// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = { 5, 6, 8, 9 };
// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[COLS] = { 13, 12, 11, 10 }; 

// Create the Keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

// Define an instance of class servo
Servo myservo;

void setup()
{
  pinMode(A0, OUTPUT);  //LED
  digitalWrite(A0, LOW);
  myservo.attach(3);
  myservo.writeMicroseconds(2200);  //Unlocked position
  if(debug) {Serial.begin(9600);}
}

void loop()
{
  char key = kpd.getKey();
  if(key)  // Check for a valid key.
  {
    if(key == '#')
    {
      if(pressed[0] == code[0] && pressed[1] == code[1] && pressed[2] == code[2] && pressed[3] == code[3])  //correct sequence was entered
      {  
         if(toggle) {
           myservo.writeMicroseconds(1300);
           digitalWrite(A0, HIGH);}
         else {
           myservo.writeMicroseconds(2200); 
           digitalWrite(A0, LOW);}
           toggle = 1-toggle;
       }
    } 
    else
    {
      for(i = 0; i<3; i++)
      {  
        pressed[i] = pressed[i+1];  //shift all the stored values to the left to make room for newly pressed button, discarding first value
      }
      pressed[3]=key;  //store the newly pressed button
      if(debug) {Serial.println(pressed);}
    }
  }
}




