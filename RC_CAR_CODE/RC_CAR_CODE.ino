int state = 0; //bluetooth state
int motor_speed = 10; //initial at max speed

int motorleftpin2 11 //left motor pin 2 (counetr clockwise)
int motorleftpin1 10 //left motor pin 1 (clockwise)
int pwm1 3

int motorrightpin2 8 //right motor pin 2 (counterclockwise)
int motorrightpin1 9 //right motor pin 1 (clockwise)
int pwm2 5

int return_speed(void){
  return map(motor_speed,0,255,1,10);
};

void setup()
{
  //Setting the pin mode
  pinMode(motorleftpin1, OUTPUT);
  pinMode(motorleftpin2, OUTPUT);
  pinMode(motorrightpin1, OUTPUT);
  pinMode(motorrightpin2, OUTPUT);
  pinMode(pwm1, OUTPUT);
  pinMode(pwm2, OUTPUT);

  //Establishing connection with bluetoth
  Serial.begin(9600);

  //Initially stopping all the motors
  digitalWrite(motorleftpin1, LOW);
  digitalWrite(motorrightpin1, LOW);
  digitalWrite(motorrightpin2, LOW);
  digitalWrite(motorleftpin2, LOW);
};

void set_speed(void){
  //Set the speed for the motor
  analogWrite(pwm1,return_speed());
  analogWrite(pwm2,return_speed());
};

void forward(void){
  //moves the motor forward
  digitalWrite(motorleftpin1, HIGH);
  digitalWrite(motorrightpin1, HIGH);
  // set_speed();
};

void backward(void){
  //moves the motor backward
  digitalWrite(motorrightpin2, HIGH);
  digitalWrite(motorleftpin2, HIGH);
  // set_speed();
};

void right(void){
  //moves the motor towards right
  digitalWrite(motorleftpin1, HIGH);
  digitalWrite(motorrightpin2, HIGH);
  digitalWrite(motorrightpin1, LOW);
  digitalWrite(motorleftpin2, LOW);
  // set_speed();
};

void left(void){
  //moves the motor towards left
  digitalWrite(motorrightpin1, HIGH);
  digitalWrite(motorleftpin2, HIGH);
  // set_speed();
}

void loop()
{
  if(Serial.available()){
    state = Serial.read(); // Read the data from the serial port
    Serial.println(state);
  }
Serial.println(map(motor_speed,0,255,1,10));
  if (state == '1'){
    motor_speed = 1;
  }else if (state = '2'){
    motor_speed = 2;
  }else if (state = '3'){
    motor_speed = 3;
  }else if (state = '4'){
    motor_speed = 4;
  }else if (state = '5'){
    motor_speed = 5;
  }else if (state = '6'){
    motor_speed = 6;
  }else if (state = '7'){
    motor_speed = 7;
  }else if (state = '8'){
    motor_speed = 8;
  }else if (state = '9'){
    motor_speed = 9;
  }else if (state = 'q'){
    motor_speed = 10;
  }

  //Deciding functions for motor
  if (state == 'F') {
    Serial.println("Moving Forward");
    forward();
    state = 0;

  }
  else if (state == 'B') {
    Serial.println("Moving Backwards");
    backward();
    state = 0;

  }else if (state == 'R') {
    Serial.println("Moving Right");
    right();
    state = 0;

  }else if (state == 'L') {
    Serial.println("Moving Left");
    left();
    state = 0;

  }else if (state == 'G' or state == 'J') {
    Serial.println("Forward Left");
    digitalWrite(motorrightpin1, HIGH);
    digitalWrite(motorleftpin2, LOW);
    digitalWrite(motorleftpin1, LOW);
    digitalWrite(motorrightpin2, LOW);
    // set_speed();
    state = 0;

  }else if (state == 'I' or state == 'H') {
    Serial.println("Forward Right");
    digitalWrite(motorleftpin1, HIGH);
    digitalWrite(motorrightpin1, LOW);
    digitalWrite(motorleftpin2, LOW);
    digitalWrite(motorrightpin2, LOW);
    // set_speed();
    state = 0;

  }else if (state == 'S'){
    Serial.println("Stopping");
    digitalWrite(motorleftpin1, LOW);
    digitalWrite(motorrightpin1, LOW);
    digitalWrite(motorrightpin2, LOW);
    digitalWrite(motorleftpin2, LOW);
    state = 0;
  }
 delay(100);
};
