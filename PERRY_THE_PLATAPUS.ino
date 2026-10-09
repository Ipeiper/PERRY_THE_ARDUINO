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
int start_time = 0;
//How long delay should last
int del_time=0;
//defines how long one loop is suposed to last in ms
int loop_time = 20;
//here is the variable that controls whether the hat should come out or not, feel free to rename it and its calls
bool agent_mode=false;
bool chat_mode=false;
//Pin setup
const int PIN_MAG = 5;
const int PIN_LIM = A1;
const int PIN_SER = 6;
int magon=0;
int V_lim=0;

//Sensing Bounds
// value out of 1023, so this is about 0.1v
const int LIM_THRESH = 100;
//Sensor Previous State bools
bool prev_mag = false;
bool prev_lim = false;


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
  pinMode(PIN_MAG, INPUT_PULLUP);
  magon = digitalRead(PIN_MAG);   
  V_lim=analogRead(PIN_LIM);
  //put servo setup code here
}

void loop() {
  // put your main code here, to run repeatedly:
  //put sensing code here
  start_time = millis();
  //limit switch is connected from 5v to A0
  //mag switch is also from 5v to Analog pin. seems like the source might decay over time so maybe code to see initial spike? also set dection threshold as a variable so I can change later
  
  //update values
  magon = digitalRead(PIN_MAG);
  V_lim = analogRead(PIN_LIM);

  //Mag switch detection and toggle
  //magon is 1 if no magnet is present
  //and 0 if there is one 
  if (magon == LOW && !prev_mag){
    agent_mode=true;
    prev_mag= true;
  }
  else if (magon == LOW  && prev_mag){
    //do nothing
  }
  else{
    //if magon == HIGH
    agent_mode=false;
    prev_mag = false;
  }

  //Lim switch detection and toggle
  if (V_lim >= LIM_THRESH && !prev_lim ){
    chat_mode = true;
    prev_lim = true;
  }
  else if (V_lim>= LIM_THRESH && prev_lim){
    //basically just do nothing
  }
  else{
    chat_mode = false;
    prev_lim = false;
  }
  
  //put
  if (agent_mode == true){
    //put your agent servo code here
  }
  else if (chat_mode==true){
    Facemotor -> run(FORWARD);
  }
  else if (chat_mode == false){
    Facemotor -> run(RELEASE);
  }
  else{
    // put something else here or delete if we have nothing to do if none of these are true

  }
  
  
  Serial.print(start_time);
  Serial.print(",");
  Serial.print(millis());
  Serial.print(",");
  Serial.print(magon);
  Serial.print(",");
  Serial.print(V_lim);
  Serial.print(",");
  Serial.print(agent_mode);
  Serial.print(",");
  Serial.println(chat_mode);
  
  del_time=millis()-start_time;
  if (del_time<loop_time){
    delay(loop_time-del_time);
  }
}
