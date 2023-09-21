#include <math.h>

char STATE='S'; //bluetooth state
int MOTOR_SPEED = 10; //initial at max speed

#define motorleftpin2 9 //left motor pin 2 (counetr clockwise)
#define motorleftpin1 8 //left motor pin 1 (clockwise)

#define motorrightpin2 11 //right motor pin 2 (counterclockwise)
#define motorrightpin1 10 //right motor pin 1 (clockwise)

#if DRV8833
#define MAX_SPEED  pow(2, 16) //max speed
#else
#define MAX_SPEED  pow(2, 10) //max speed
#endif

#if DRV8833
#define EEP 34
#define ULT 18
#define buzzer 3
#endif

int return_speed(void){
  return map(MOTOR_SPEED,0,MAX_SPEED,1,10);
};


void setup() {
  Serial.begin(9600);

  #if DRV8833
    analogWriteResolution(16);
  #endif

  pinMode(motorrightpin1, OUTPUT);
  pinMode(motorrightpin2, OUTPUT);
  pinMode(motorleftpin1, OUTPUT);
  pinMode(motorleftpin2, OUTPUT);
  #if DRV8833
    pinMode(EEP, OUTPUT);
    pinMode(ULT, INPUT_PULLUP);
    digitalWrite(EEP, HIGH);
    digitalWrite(buzzer, LOW);
  #endif

  digitalWrite(motorrightpin1, LOW);
  digitalWrite(motorrightpin2, LOW);
  digitalWrite(motorleftpin1, LOW);
  digitalWrite(motorleftpin2, LOW);

  digitalWrite(LED_BUILTIN, LOW);
  
}

void forward(void){
  //moves the motor forward
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(motorleftpin1, HIGH);
  digitalWrite(motorrightpin1, HIGH);
  #if DRV8833
    analogWrite(motorleftpin1, return_speed());
    analogWrite(motorrightpin1, return_speed());
  #endif
};

void backward(void){
  //moves the motor backward
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(motorrightpin2, HIGH);
  digitalWrite(motorleftpin2, HIGH);
  #if DRV8833
    analogWrite(motorrightpin2, return_speed());
    analogWrite(motorleftpin2, return_speed());
  #endif
};

void right(void){
  //moves the motor towards right
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(motorleftpin1, HIGH);
  digitalWrite(motorrightpin2, HIGH);
  digitalWrite(motorrightpin1, LOW);
  digitalWrite(motorleftpin2, LOW);
  #if DRV8833
    analogWrite(motorleftpin1, return_speed());
    analogWrite(motorrightpin2, return_speed());
  #endif
};

void left(void){
  //moves the motor towards left
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(motorrightpin1, HIGH);
  digitalWrite(motorleftpin2, HIGH);
  #if DRV8833
    analogWrite(motorrightpin1, return_speed());
    analogWrite(motorleftpin2, return_speed());
  #endif
}

void loop() {
  #if DRV8833
  if (digitalRead(ULT)==LOW){
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(buzzer, HIGH);
    digitalWrite(EEP, LOW);
  }
  #endif
  if (!Serial.available()) {
    return;
  };
  STATE = Serial.read();
  Serial.println(STATE);

  #if DRV8833
    if (STATE == '1'){
      MOTOR_SPEED = 1;
    }else if (STATE = '2'){
      MOTOR_SPEED = 2;
    }else if (STATE = '3'){
      MOTOR_SPEED = 3;
    }else if (STATE = '4'){
      MOTOR_SPEED = 4;
    }else if (STATE = '5'){
      MOTOR_SPEED = 5;
    }else if (STATE = '6'){
      MOTOR_SPEED = 6;
    }else if (STATE = '7'){
      MOTOR_SPEED = 7;
    }else if (STATE = '8'){
      MOTOR_SPEED = 8;
    }else if (STATE = '9'){
      MOTOR_SPEED = 9;
    }else if (STATE = 'q'){
      MOTOR_SPEED = 10;
    }
  #endif

  //Deciding functions for motor
  if (STATE == 'F') {
    forward();

  }
  else if (STATE == 'B') {
    backward();

  }else if (STATE == 'R') {
    right();

  }else if (STATE == 'L') {
    left();

  }else if (STATE == 'G' or STATE == 'J') {
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(motorrightpin1, HIGH);
    #if DRV8833
      analogWrite(motorrightpin1, return_speed());
    #endif
    digitalWrite(motorleftpin2, LOW);
    digitalWrite(motorleftpin1, LOW);
    digitalWrite(motorrightpin2, LOW);

  }else if (STATE == 'I' or STATE == 'H') {
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(motorleftpin1, HIGH);
    #if DRV8833
      analogWrite(motorleftpin1, return_speed());
    #endif
    digitalWrite(motorrightpin1, LOW);
    digitalWrite(motorleftpin2, LOW);
    digitalWrite(motorrightpin2, LOW);

  }else if (STATE == 'S'){
    digitalWrite(LED_BUILTIN, HIGH);
    #if DRV8833
      digitalWrite(buzzer, HIGH);
    #endif
    digitalWrite(motorleftpin1, LOW);
    digitalWrite(motorrightpin1, LOW);
    digitalWrite(motorrightpin2, LOW);
    digitalWrite(motorleftpin2, LOW);
  }

  STATE = 'S';
  delay(20);
  digitalWrite(LED_BUILTIN, LOW);
  #if DRV8833
    digitalWrite(buzzer, HIGH);
  #endif
}