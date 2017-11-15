#define LEFT_AHEAD 10
#define LEFT_BACK 9
#define RIGHT_AHEAD 12
#define RIGHT_BACK 13
#define STEER 14

#include <Servo.h>
Servo servo_pin_14;


int duty = 1200;
String inString="";
float RunInit = 3.0;
float RUN_LEFT = 3.0;
float RUN_RIGHT = 3.0;
int TURN = 120;
int RUN1 = 255;
int CYC = 5;
float calibrateNum = 0;
void stopBack();
void turnLeft();
void turnRight();
void goAhead();
void park();
void goBack();



void setup(){
  Serial.begin(9600);
  pinMode(LEFT_AHEAD,OUTPUT);
  pinMode(LEFT_BACK, OUTPUT);
  pinMode(RIGHT_AHEAD, OUTPUT);
  pinMode(RIGHT_BACK, OUTPUT);
  digitalWrite(LEFT_AHEAD, LOW);
  digitalWrite(LEFT_BACK, LOW);
  digitalWrite(RIGHT_AHEAD, LOW);
  digitalWrite(RIGHT_BACK, LOW);
  servo_pin_14.attach(14);


}



char incomingByte = ' ';
void loop(){
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
    if (incomingByte == 'L') {
      Serial.println("TURN LEFT");
      turnLeft();
      Serial.read();
    }
    else if (incomingByte == 'R'){
      Serial.println("TURN RIGHT");
      turnRight();
      Serial.read();
    }
    else if (incomingByte == 'A'){
      Serial.println("GO AHEAD");
      goAhead();
      Serial.read();
    }
    else if (incomingByte == 'B'){
      Serial.println("GO BACK");
      goBack();
      Serial.read();
    }
    else if (incomingByte == 'P'){
      Serial.println("PARK");
      park();
      Serial.read();
    }
    else if (incomingByte == 'C'){
      calib();
    }
    else if (incomingByte == 'K'){
      changeP();
    }
    else if (incomingByte == 'S'){
      changeS();
    }
    else if (incomingByte == 'D'){
      changeD();
    }
  }
}



void steer(float x){



  // digitalWrite(STEER,LOW);
}



void goAhead(){
  stopBack();
  analogWrite(LEFT_AHEAD,RUN1);
  analogWrite(RIGHT_AHEAD,RUN1);
  servo_pin_14.write(50);
}




void turnLeft(){
  stopBack();
  analogWrite(RIGHT_AHEAD,RUN1);
  analogWrite(LEFT_AHEAD,TURN);
   servo_pin_14.write(70 );
}
void turnRight(){
  stopBack();
  analogWrite(LEFT_AHEAD,RUN1);
  analogWrite(RIGHT_AHEAD,TURN);
   servo_pin_14.write(30 );
}


void park(){
  stopBack();
  digitalWrite(LEFT_AHEAD, LOW);
  digitalWrite(RIGHT_AHEAD, LOW);
  servo_pin_14.write(50 );
}



void goBack(){
  // stopBack();
  digitalWrite(LEFT_AHEAD,LOW);
  digitalWrite(RIGHT_AHEAD,LOW);
  analogWrite(LEFT_BACK,RUN1);
  analogWrite(RIGHT_BACK,RUN1);
  steer(0);
}
void stopBack(){
  digitalWrite(LEFT_BACK, LOW);
  digitalWrite(RIGHT_BACK, LOW);
}
int readInt(){
  int x;
  int flag=1;
  while(flag){
    while (Serial.available() > 0) {
      int inChar = Serial.read();
      if (isDigit(inChar)) {
        // convert the incoming byte to a char
        // and add it to the string:
        inString += (char)inChar;
      }
      // if you get a newline, print the string,
      // then the string's value:
      if (inChar == '\n') {
        x=inString.toInt();
        flag=0;
        // clear the string for new input:
        inString = "";
      }
    }
  }
  return x;
}
void calib(){
  TURN = readInt();
  Serial.println("calibrate:");
  Serial.println(TURN,DEC);
}
void changeP(){
  CYC = readInt();
  Serial.println("DELAY(ms):");
  Serial.println(CYC*2,DEC);
}
void changeS(){
  RUN1 = readInt();
  Serial.println("new spead:");
  Serial.println(RUN1,DEC);
}
void changeD(){
  duty = readInt();
  Serial.println("new duty:");
  Serial.println(duty,DEC);
}


