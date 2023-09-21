#include <Arduino.h>
#include <math.h>
#include "BluetoothSerial.h"

#define USE_PIN
const char *pin = "7842";

String device_name = "HOKAGE RC CAR";

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;

char STATE='S'; //bluetooth state
int MOTOR_SPEED = 10; //initial at max speed

#if DRV8833
#define MAX_SPEED  pow(2, 16) //max speed
#else
#define MAX_SPEED  pow(2, 10) //max speed
#endif

#define motorrightpin1 GPIO_NUM_19 //left motor pin 2 (counetr clockwise)
#define motorrightpin2 GPIO_NUM_21 //left motor pin 1 (clockwise)

#define motorleftpin2 GPIO_NUM_2 //right motor pin 2 (counterclockwise)
#define motorleftpin1 GPIO_NUM_15 //right motor pin 1 (clockwise)

#if DRV8833
#define EEP GPIO_NUM_34
#define ULT GPIO_NUM_18
#define buzzer GPIO_NUM_23
#endif

int return_speed(void){
  return map(MOTOR_SPEED,0,MAX_SPEED,1,10);
};


void setup() {
  Serial.begin(9600);
  SerialBT.begin(device_name); //Bluetooth device name
  Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());
  //Serial.printf("The device with name \"%s\" and MAC address %s is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str(), SerialBT.getMacString()); // Use this after the MAC method is implemented
  #ifdef USE_PIN
    SerialBT.setPin(pin);
    Serial.println("Using PIN");
  #endif

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

  digitalWrite(BUILTIN_LED, LOW);
  
}

void backward(void){
  //moves the motor forward
  digitalWrite(BUILTIN_LED, HIGH);
  digitalWrite(motorleftpin1, HIGH);
  digitalWrite(motorrightpin1, HIGH);
  #if DRV8833
    analogWrite(motorleftpin1, return_speed());
    analogWrite(motorrightpin1, return_speed());
  #endif
};

void forward(void){
  //moves the motor backward
  digitalWrite(BUILTIN_LED, HIGH);
  digitalWrite(motorrightpin2, HIGH);
  digitalWrite(motorleftpin2, HIGH);
  #if DRV8833
    analogWrite(motorrightpin2, return_speed());
    analogWrite(motorleftpin2, return_speed());
  #endif
};

void left(void){
  //moves the motor towards right
  digitalWrite(BUILTIN_LED, HIGH);
  digitalWrite(motorleftpin1, HIGH);
  digitalWrite(motorrightpin2, HIGH);
  digitalWrite(motorrightpin1, LOW);
  digitalWrite(motorleftpin2, LOW);
  #if DRV8833
    analogWrite(motorleftpin1, return_speed());
    analogWrite(motorrightpin2, return_speed());
  #endif
};

void right(void){
  //moves the motor towards left
  digitalWrite(BUILTIN_LED, HIGH);
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
    digitalWrite(BUILTIN_LED, HIGH);
    digitalWrite(buzzer, HIGH);
    digitalWrite(EEP, LOW);
    Serial.println("Stopping");
  }
  #endif
  if (!SerialBT.available()) {
    return;
  };
  STATE = SerialBT.read();

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
    Serial.println('h');
    Serial.println("Moving Forward");
    forward();

  }
  else if (STATE == 'B') {
    Serial.println("Moving Backwards");
    backward();

  }else if (STATE == 'R') {
    Serial.println("Moving Right");
    right();

  }else if (STATE == 'L') {
    Serial.println("Moving Left");
    left();

  }else if (STATE == 'G' or STATE == 'J') {
    digitalWrite(BUILTIN_LED, HIGH);
    Serial.println("Forward Left");
    digitalWrite(motorrightpin1, HIGH);
    #if DRV8833
      analogWrite(motorrightpin1, return_speed());
    #endif
    digitalWrite(motorleftpin2, LOW);
    digitalWrite(motorleftpin1, LOW);
    digitalWrite(motorrightpin2, LOW);

  }else if (STATE == 'I' or STATE == 'H') {
    digitalWrite(BUILTIN_LED, HIGH);
    Serial.println("Forward Right");
    digitalWrite(motorleftpin1, HIGH);
    #if DRV8833
      analogWrite(motorleftpin1, return_speed());
    #endif
    digitalWrite(motorrightpin1, LOW);
    digitalWrite(motorleftpin2, LOW);
    digitalWrite(motorrightpin2, LOW);

  }else if (STATE == 'S'){
    digitalWrite(BUILTIN_LED, HIGH);
    #if DRV8833
      digitalWrite(buzzer, HIGH);
    #endif
    Serial.println("Stopping");
    digitalWrite(motorleftpin1, LOW);
    digitalWrite(motorrightpin1, LOW);
    digitalWrite(motorrightpin2, LOW);
    digitalWrite(motorleftpin2, LOW);
  }

  STATE = 'S';
  delay(20);
  digitalWrite(BUILTIN_LED, LOW);
  #if DRV8833
    digitalWrite(buzzer, HIGH);
  #endif
}