/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// Pin 11 has the LED on Teensy 2.0
// Pin 6  has the LED on Teensy++ 2.0
// Pin 13 has the LED on Teensy 3.0
// give it a name:
int columns[9] = {12, 19, 16, 21, 18, 15, 20, 17, 14};
int rows[3] = {22, 11, 13};

// the setup routine runs once when you press reset:
void setup() {
  pinMode(11, OUTPUT);  
  pinMode(12, OUTPUT);  
  pinMode(13, OUTPUT);  
  pinMode(14, OUTPUT);  
  pinMode(15, OUTPUT);  
  pinMode(16, OUTPUT);
  pinMode(17, OUTPUT);  
  pinMode(18, OUTPUT);  
  pinMode(19, OUTPUT);  
  pinMode(20, OUTPUT);  
  pinMode(21, OUTPUT);  
  pinMode(22, OUTPUT);
  // Turn Transistors OFF
  digitalWrite(11, LOW);
  digitalWrite(13, LOW);
  digitalWrite(22, LOW);
}

// the loop routine runs over and over again forever:
void loop() {
  for(int i = 0; i < 3; i++) {
    digitalWrite(rows[i], HIGH);
    for(int j = 0; j < 9; j++) {
      digitalWrite(columns[j], HIGH);
      delay(1000);
      digitalWrite(columns[j], LOW); 
    }
    digitalWrite(rows[i], LOW);
  } 
}
