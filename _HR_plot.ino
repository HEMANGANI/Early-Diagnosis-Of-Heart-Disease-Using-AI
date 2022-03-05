#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.   

//  Variables
int PulseSensorPurplePin = 0;                   // Pulse Sensor PURPLE WIRE connected to ANALOG PIN 0.
int LED13 = 13;                                 //  The on-board Arduion LED.
int Signal;                                     // holds the incoming raw data. Signal value can range from 0-1024.
int Threshold = 550;                            // Determine which Signal to "count as a beat", and which to ingore.

PulseSensorPlayground pulseSensor;              // Creates an instance of the PulseSensorPlayground object called "pulseSensor"

// The SetUp Function:
void setup() {
  pinMode(LED13,OUTPUT);                        // pin that will blink to the heartbeat.
  Serial.begin(9600);                           // Set's up Serial Communication at certain speed.
  // Configure the PulseSensor object, by assigning our variables to it. 
  pulseSensor.analogInput(PulseSensorPurplePin);   
  pulseSensor.blinkOnPulse(LED13);              // auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(Threshold);   

  // Double-check the "pulseSensor" object was created and "began" seeing a signal. 
  if (pulseSensor.begin()) {
    //Serial.println("We created a pulseSensor Object !");  // This prints one time at Arduino power-up,  or on Arduino reset.  
  }
}

// The Main Loop Function
void loop() {

  Signal = analogRead(PulseSensorPurplePin);  // Read the PulseSensor's value.
                                              // Assign this value to the "Signal" variable.

   Serial.println(Signal);                    // Send the Signal value to Serial Plotter.

   if(Signal > Threshold){                    // If the signal is above "550", then "turn-on" Arduino's on-Board LED.
     digitalWrite(LED13,HIGH);
   } else {
     digitalWrite(LED13,LOW);                 //  Else, the sigal must be below "550", so "turn-off" this LED.
   }
  int myBPM = pulseSensor.getBeatsPerMinute(); // Calls function on our pulseSensor object that returns BPM as an "int".
                                               // "myBPM" hold this BPM value now. 

/*if (pulseSensor.sawStartOfBeat()) {            // Constantly test to see if "a beat happened". 
 //Serial.println("♥  A HeartBeat Happened ! "); // If test is "true", print a message "a heartbeat happened".
 Serial.print("♥ BPM: ");                        // Print phrase "BPM: " 
 Serial.println(myBPM);                        // Print the value inside of myBPM. 
}//*/

delay(10);

}
