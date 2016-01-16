/*Arduino code to turn stepper motor one rotation when a digital input is read
  from pin 8
  
  Created using EasyDriver with the following connections:
  pin 2 to 'dir'
  pin 3 to 'step'
  pin 7 to 'enable'

  driver connected to NEMA 23 4-wire stepper motor
  Known issue: stepper won't spin at >0.7 speed setting
  Possible causes: not enough current or not enough load on motor (needs inertia to spin)
  
  Known issue: infrequent false input reading
  Possible causes: Noise on input pin. Inadvertant pulse from RPi. Ghosts.*/

int dirPin = 2; //direction pin (CW or CCW)
int stepPin = 3; //Stepper pin
int enablePin = 7; //Enable pin (Rest motor)
int inputPin = 8;//digital input pin (digital input)
 
void setup(){
  /*Setup executes once when Arduino is turned on
  set 3 outputs to stepper driver, 1 digital input from RPi*/
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  pinMode(inputPin, INPUT); 
 
  digitalWrite(enablePin, HIGH); //rests motor
 
  Serial.begin(9600); //initiate use of serial output
}
 
void loop(){
  /*main loop runs repeatedly while Arduino is on
  when input is detected, print to serial and spin that b*tch*/
  if (digitalRead(inputPin) == HIGH) {
    Serial.write("digital input read");
    rotate(1600, 0.25); //spin motor one rotation @ .25 speed
    delay(3000); //wait 3 seconds so digital input can rest
  }
  
}
 

void rotate(int steps, float speed){
  /*Function to spin motor. 
  Accepts two arguments: int 'steps' and float 'speed'
  1600 steps in one rotation, positive for CW, negative for CCW
  speed is a float between 0 (off) and 1 (fast)*/
  digitalWrite(enablePin, LOW); //wake up motor
 
  int dir; //initialize dir (used for driver "dir" pin) 

  if (steps > 0){  // if positive, set dir pin to high logic (CW)
    dir = HIGH;
  }else{          //otherwise, set dir pin to low logic (CCW)
    dir = LOW;
  }
 
  speed = 1/speed * 70; //Calculate speed from step size
  steps = abs(steps); //No negatives, direction already saved
 
  digitalWrite(dirPin, dir); //turn dir pin on or off
 
  for (int i = 0; i < steps; i++){ //stepping loop
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(speed);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(speed);
  }
 
  digitalWrite(enablePin, HIGH); //put the motor back to sleep
}
