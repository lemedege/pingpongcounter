//We always have to include the library
#include "LedControl.h"
#include <Button.h>


/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 10 is connected to LOAD 
 We have only a single MAX72XX.
 */
LedControl lc=LedControl(12,11,10,2);

const int leftButton = 4;
const int rightButton = 6;
const int middleButton = 5;

int leftScore = 0;
int rightScore = 0;


Button lbutton(leftButton); // Connect your button between pin 2 and GND
Button rbutton(rightButton); // Connect your button between pin 3 and GND
Button mbutton(middleButton); // Connect your button between pin 4 and GND





/* we always wait a bit between updates of the display */
unsigned long delaytime=250;

void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  /* and clear the display */
  lc.clearDisplay(0);

//pinMode(leftButton, INPUT_PULLUP);
//pinMode(rightButton, INPUT_PULLUP);
//pinMode(middleButton, INPUT_PULLUP);

lbutton.begin();
rbutton.begin();
mbutton.begin();

 clearScore();

//  Serial.begin(115200);
 
}


/*
 This method will display the characters for the
 word "Arduino" one after the other on digit 0. 
 */
void writeArduinoOn7Segment() {
  lc.setChar(0,0,'a',false);
  delay(delaytime);
  lc.setRow(0,0,0x05);
  delay(delaytime);
  lc.setChar(0,0,'d',false);
  delay(delaytime);
  lc.setRow(0,0,0x1c);
  delay(delaytime);
  lc.setRow(0,0,B00010000);
  delay(delaytime);
  lc.setRow(0,0,0x15);
  delay(delaytime);
  lc.setRow(0,0,0x1D);
  delay(delaytime);
  lc.clearDisplay(0);
  delay(delaytime);
} 

/*
 * 
  This method will scroll all the hexa-decimal
 numbers and letters on the display. You will need at least
 four 7-Segment digits. otherwise it won't really look that good.
 */
void scrollDigits() {
  for(int i=0;i<13;i++) {
    lc.setDigit(0,3,i,false);
    lc.setDigit(0,2,i+1,false);
    lc.setDigit(0,1,i+2,false);
    lc.setDigit(0,0,i+3,false);
    lc.setDigit(0,4,i,false);
    delay(delaytime);
  }
  lc.clearDisplay(0);
  delay(delaytime);
}

void clearScore(){
  lc.setDigit(0,6,0,false);
  lc.setDigit(0,5,0,false);
  lc.setDigit(0,1,0,false);
  lc.setDigit(0,2,0,false);
}

void updateScore(){
  char LS[2] = {char(leftScore % 10), char((leftScore/10) %10)};
  char RS[2] = {char(rightScore % 10), char((rightScore/10) %10)};
  lc.setDigit(0,6,LS[1],false);
  lc.setDigit(0,5,LS[0],false);
  lc.setDigit(0,2,RS[1],false);
  lc.setDigit(0,1,RS[0],false);
  
  
}

void loop() { 
  
if (lbutton.released() && mbutton.read() != Button::PRESSED){
  leftScore ++;
updateScore();
}

else if (rbutton.released() && mbutton.read() != Button::PRESSED){
  rightScore++;
updateScore();

}

else if (mbutton.read() == Button::PRESSED && lbutton.read() == Button::PRESSED && rbutton.read() == Button::PRESSED){
 delay(1500);
 leftScore = 0;
rightScore = 0;
 clearScore();
}

else if (mbutton.read() == Button::PRESSED && lbutton.released()){
    leftScore--;
    updateScore(); 
    //Serial.println(leftScore);
  }


else if (mbutton.read() == Button::PRESSED && rbutton.released()){
    rightScore--;
    updateScore(); 
    //Serial.println(rightScore);
  }
}
