// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 6);

//Pin Variable
int Submit_Button = 9;
int Input_Button = 8;

//Global Variable
int END;
int A,B,OP,R;

//functions & procedures
int LED(int pin, int logic) {
  //LED turned on when logic = 0;
  //LED turned off when logic = 1; 
  digitalWrite(pin, logic);
  return 0;
}

/*void result(int Operator,int  Result,int N1,int N2) {
   int OP, R, A, B;
   OP = Operator;
   R = Result;
   A = N1;
   B = N2;
   switch(OP){
    case 1 :
      R = A+B;
      break;
    case 2 :
      R = A-B;
      break;
    case 3 :
      R = A*B;
      break;
    case 4 :
      R = A/B;
      break;
    lcd.clear();
    lcd.setCursor (0,0);
    lcd.print("RESULT");
    lcd.setCursor (0,1);
    lcd.print(R);
  }
}*/

int STATE(int st){
  int state;
  state = st;
  //state 0 : WSCalc Screen
  //state 1 : A input
  //state 2 : B input
  //state 3 : Operator input
  //state 4 : lcd put on result
  switch(state){
    case 0 :
    //state 0;
      LED(0,0); LED(1,0); LED(2,0);
      do {
        //loop();
      } while(digitalRead(Submit_Button) == 0);
      STATE(1);
      break;
      
    case 1 :
    //state 1;
      LED(0,0); LED(1,1); LED(2,1);
      delay(1000);
      while(digitalRead(Submit_Button) != 1){
        if (digitalRead(Input_Button) == 1){
          A++;
          lcd.clear();
          lcd.print(A);
          delay(500);
        }
      }
      STATE(2);
      break;

    case 2 :
    //state 2;
      LED(0,1); LED(1,0); LED(2,1);
      delay(1000);
      while(digitalRead(Submit_Button) != 1){
        delay(500);
        if (digitalRead(Input_Button) == 1){
          B++;
          lcd.clear();
          lcd.print(B);
          delay(500);
        }
      }
      STATE(3);
      break;
      
    case 3 :
    //state 3;
      LED(0,1); LED(1,1); LED(2,0);
      delay(1000);
      while(digitalRead(Submit_Button) != 1){
        delay(500);
        if (digitalRead(Input_Button) == 1){
          OP++;
          lcd.clear();
          lcd.print(OP);
          delay(500);
        }
      }
      STATE(4);
      break;

    case 4 :
    //state 4;
      switch(OP){
        case 1 :
          R = A+B;
          break;
        case 2 :
          R = A-B;
          break;
        case 3 :
          R = A*B;
          break;
        case 4 :
          R = A/B;
          break;
      }
      lcd.clear();
      lcd.setCursor (0,0);
      lcd.print("RESULT");
      lcd.setCursor (0,1);
      lcd.print(R);
      delay(1000);
      while(digitalRead(Submit_Button) != 1){
        delay(500);
         LED(0,1); LED(1,1); LED(2,1);
         LED(0,0); delay(100); LED(0,1);
         LED(1,0); delay(100); LED(1,1);
         LED(2,0); delay(100); LED(2,1);
      }
      setup();
      break;
  }
}

//programs
void setup() {
  //Initialize Variable 
  OP = 0; A = 0; B = 0;
  
  //Pin Config
  pinMode(Submit_Button,INPUT); pinMode(Input_Button,INPUT);
  pinMode(0,OUTPUT); pinMode(1,OUTPUT); pinMode(2,OUTPUT);
  
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("WSCalc 20160 Calculator");
  // Print a message to the LCD.
  lcd.setCursor(0, 1);
  lcd.print("  Made by Kelompok 11");
  STATE(0);
}

void loop() {
    // scroll 23 positions (string length) to the left
    // to move it offscreen left:
    for (int positionCounter = 0; positionCounter < 23; positionCounter++) {
      // scroll one position left:
      lcd.scrollDisplayLeft();
      // wait a bit:
      delay(150);
    }
  
    // scroll 39 positions (string length + display length) to the right
    // to move it offscreen right:
    for (int positionCounter = 0; positionCounter < 39; positionCounter++) {
      // scroll one position right:
      lcd.scrollDisplayRight();
      // wait a bit:
      delay(200);
    }
  
    // scroll 16 positions (display length + string length) to the left
    // to move it back to center:
    for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
      // scroll one position left:
      lcd.scrollDisplayLeft();
      // wait a bit:
      delay(200);
    }
  
    // delay at the end of the full loop:
    delay(1000);
}
