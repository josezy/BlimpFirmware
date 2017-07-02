#include <SoftwareSerial.h>

#define RIGHT_PROP 8
#define LEFT_PROP  11

#define INPUT_SIZE 64

SoftwareSerial bt_serial(2, 3);

char input[INPUT_SIZE + 1];
byte sz=0;

void setup(){
  Serial.begin(9600);
  bt_serial.begin(9600);
  pinMode(RIGHT_PROP, OUTPUT);
  pinMode(LEFT_PROP, OUTPUT);
  analogWrite(RIGHT_PROP, 0);
  analogWrite(LEFT_PROP, 0);
}

void loop(){
  if(bt_serial.available()){
    softSerialEvent();
  }

}

void softSerialEvent(){
  sz = 0;
  while(bt_serial.available() > 0){
    input[sz++] = (char)bt_serial.read();
  }
  input[sz] = 0;
  if(input[0] == 'A')takeAction();
}

void takeAction(){
  char joystick = input[1];
  char js_position = input[2];
  
  switch(joystick){
    case 'R':{
      switch(js_position){
        case 'S':{
          go_forward();
          break;
        }case 'I':{
          go_backwards();
          break;
        }
      }
      break;
    }case 'L':{
      switch(js_position){
        case 'L':{
          turn_left();
          break;
        }case 'R':{
          turn_right();
          break;
        }
      }
      break;
    }default:{break;}
  }
}

void go_forward(){
  analogWrite(RIGHT_PROP, 200);
  analogWrite(LEFT_PROP, 200);
}

void go_backwards(){
  analogWrite(RIGHT_PROP, 0);
  analogWrite(LEFT_PROP, 0);
}

void turn_left(){
  analogWrite(RIGHT_PROP, 200);
  analogWrite(LEFT_PROP, 80);
}

void turn_right(){
  analogWrite(RIGHT_PROP, 80);
  analogWrite(LEFT_PROP, 200);
}
