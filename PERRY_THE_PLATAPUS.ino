#include <Wire.h>
#include <Adafruit_MotorShield.h>

//This is where you should define variables.
//remember, because I just forgot and had to fix it, that every line of code needs a semicolon after it
//Heres a link for how to, its sort of weird and I still dont fully get it. https://docs.arduino.cc/learn/programming/variables/
//I would recomend defining the bounds of the servo in relation to the center of the servo.
//You should also define the center of the servo, we'll futz with these numbers later so just arbitrary works for now
//also, I highly recomend taking a look at the servo sweep example, you can look it up if you dont know how to get to it
//thats a lot of yapping, I hope its helpful

//defines the time at the start of the loop
int start_time = millis();
//defines how long one loop is suposed to last in ms
int loop_time = 20;
//here is the variable that controls whether the hat should come out or not, feel free to rename it and its calls
bool agentmode=false;
bool chatmode=false;
//

//DC Motor Section
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *Facemotor = AFMS.getMotor(1);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Iniatializing PERRY THE PLATAPUS");

  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
  // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");
  Facemotor->setSpeed(150);

}

void loop() {
  // put your main code here, to run repeatedly:
  //put sensing code here
  start_time = millis();
  //put
  if (agentmode == true){
    //put your agent servo code here
  }
  else if (chatmode==true){
    Facemotor -> run(FORWARD);
  }
  else if (chatmode == false){
    Facemotor -> run(RELEASE);
  }
  else{
    // put something else here or delete if we have nothing to do if none of these are true

  }
  
  
  Serial.print(start_time);
  Serial.print(millis());
  delay(loop_time-millis()+start_time);
}
