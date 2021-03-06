#include <Keyboard.h>
#include <Mouse.h>
#define LED     13

char pins[16] = {A3, A2, A1, A0, 2, 3, 4, 5, 6, 7, 8, 9, 15, 14, 16, 10};
char keyCodes[16] = {0xB0,0xB2,'2','1','s','d','w','a','q','e','x','y',0xDA,0xD9,0xD8,0xD7};
//KEY_UP_ARROW           0xDA    218
//KEY_DOWN_ARROW    0xD9    217
//KEY_LEFT_ARROW    0xD8    216
//KEY_RIGHT_ARROW    0xD7    215
//KEY_BACKSPACE           0xB2    178
//KEY_RETURN           0xB0    176
//
//Nicht verwendet:
//     KEY_ESC           0xB1    177


int lastState[16];
int replaced = 15;

int deBounce(int button) {
  delay(20);
  if(!digitalRead(button)) {
    return true;
  }
  return false;
}

void setup() {
  Keyboard.begin();
  for(int i=0;i<16;i++) {
    pinMode(pins[i], INPUT);
    digitalWrite(pins[i], HIGH);
  }
  pinMode(LED, OUTPUT);
}

void loop() {
  for(int i=0;i<16;i++) {

  //Custom key pressed
  if(i==replaced){
  if(digitalRead(replaced)){
  //If pressed then release
  if(lastState[replaced]){
  Mouse.release();
        lastState[replaced] = false;
  }else{
  if(deBounce(pins[replaced])){
  Mouse.press();
        lastState[replaced] = true;
  }
}  
}
  }else{ //Normal code
    if(digitalRead(pins[i])) {
      if(lastState[i]) {
        Keyboard.release(keyCodes[i]);
        lastState[i] = false;
      }
    } else {
      if(!lastState[i] && deBounce(pins[i])) {
        Keyboard.press(keyCodes[i]);
        lastState[i] = true;
      }
    }
    }
  }
}
