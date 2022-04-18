int state = 0; //bluetooth state

int motorleftpin1 = 1; //left motor pin 1
int motorleftpin2 = 2; //left motor pin 2

int motorrightpin1 = 3; //right motor pin 1
int motorrightpin2 = 4; //right motor pin 2

void setup()
{
  Serial.begin(9600);
}

void right(){
}

void left(){
}

void forward(){
}

void backward(){
}

void loop()
{
  if(Serial.available() > 0){
    state = Serial.read(); // Read the data from the serial port
  }
 
}
