int state = 0; //bluetooth state

int motorpin1 = 1; //motor1 pin1


int motorpin2 = 2; //motor2 pin1


int motorpin3 = 3; //motor3 pin1


int motorpin4 = 4; //motor4 pin1



void setup()
{
  Serial.begin(9600);
}

void loop()
{
  if(Serial.available() > 0){
    state = Serial.read(); // Read the data from the serial port
  }
 
}
