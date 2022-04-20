int state = 0; //bluetooth state

int motorleftpin2 = 11; //left motor pin 2 (counetr clockwise)
int motorleftpin1 = 10; //left motor pin 1 (clockwise)

int motorrightpin2 = 13; //right motor pin 2 (counterclockwise)
int motorrightpin1 = 12; //right motor pin 1 (clockwise)

void setup()
{
  pinMode(motorleftpin1, OUTPUT);
  pinMode(motorleftpin2, OUTPUT);
  pinMode(motorrightpin1, OUTPUT);
  pinMode(motorrightpin2, OUTPUT);
  Serial.begin(9600);
  digitalWrite(motorleftpin1, LOW);
  digitalWrite(motorrightpin1, LOW);
  digitalWrite(motorrightpin2, LOW);
  digitalWrite(motorleftpin2, LOW);
}

void loop()
{
  if(Serial.available()){
    state = Serial.read(); // Read the data from the serial port
    Serial.println(state);
  }

  //Deciding functions for motor
  if (state == 'F') {
    Serial.println("Moving Forward");
    digitalWrite(motorleftpin1, HIGH);
    digitalWrite(motorrightpin1, HIGH);
    state = 0;

  }
  else if (state == 'B') {
    Serial.println("Moving Backwards");
    digitalWrite(motorrightpin2, HIGH);
    digitalWrite(motorleftpin2, HIGH);
    state = 0;

  }else if (state == 'R') {
    digitalWrite(motorrightpin1, HIGH);
    Serial.println("Moving Right");
    state = 0;

  }else if (state == 'L') {
    Serial.println("Moving Left");
    digitalWrite(motorleftpin1, HIGH);
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
}
