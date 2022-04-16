int state = 0;

void setup() {
  Serial.begin(9600); // Default communication rate
}

void loop() {
// Checks if the data is coming from the serial port
  if(Serial.available() > 0){
    state = Serial.read(); // Read the data from the serial port
  }
  Serial.println(state+" dhruva");
  state = 0;
}
