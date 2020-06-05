//Demarzi Giorgio S4227621 
//Arduino Code to store Pulse Sensor data into the Wifi Shield's microSD 


#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.   
#include <SPI.h>
#include "SdFat.h"
SdFat SD;

//  Variables
const int PulseWire = 0;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED13 = 13;          // The on-board Arduino LED, close to PIN 13.
int Threshold = 550;           // Determine which Signal to "count as a beat" and which to ignore.
                               // Use the "Gettting Started Project" to fine-tune Threshold Value beyond default setting.
                               // Otherwise leave the default "550" value. 
PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"

File BPMFile;
File IBIFile;
File PAFile;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

//Creating files
  Serial.println("BPM.txt...");
  BPMFile = SD.open("BPM.txt", FILE_WRITE);
  BPMFile.close();

  Serial.println("IBI.txt...");
  IBIFile = SD.open("IBI.txt", FILE_WRITE);
  IBIFile.close();

  Serial.println("PA.txt...");
  PAFile = SD.open("PA.txt", FILE_WRITE);
  PAFile.close();

  // Check to see if the files exist:
  if (SD.exists("BPM.txt")) {
    Serial.println("BPM.txt exists.");
  } else {
    Serial.println("BPM.txt doesn't exist.");
  }

  if (SD.exists("IBI.txt")) {
    Serial.println("IBI.txt exists.");
  } else {
    Serial.println("IBI.txt doesn't exist.");
  }

  if (SD.exists("PA.txt")) {
    Serial.println("PA.txt exists.");
  } else {
    Serial.println("PA.txt doesn't exist.");
  }

  // Configure the PulseSensor object, by assigning our variables to it. 
  pulseSensor.analogInput(PulseWire);   
  pulseSensor.setThreshold(Threshold);   

  // Double-check the "pulseSensor" object was created and "began" seeing a signal. 
   if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset.  
  }



}
void loop() {

  
 int myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".
                                               // "myBPM" hold this BPM value now. 
 int myIBI = pulseSensor.getInterBeatIntervalMs();
 int myPA = pulseSensor.getPulseAmplitude();

if (pulseSensor.sawStartOfBeat()) {            // Constantly test to see if "a beat happened". 
 Serial.println("♥  A HeartBeat Happened ! "); // If test is "true", print a message "a heartbeat happened".
 Serial.print("BPM: ");                        // Print phrase "BPM: " 
 Serial.println(myBPM);                       // Print the value inside of myBPM.
 Serial.print("IBI: ");
 Serial.println(myIBI);
 Serial.print("Pulse Amplitude: ");
 Serial.println(myPA);
 String stringBPM = "";
 String stringIBI = "";
 String stringPA = "";
 stringBPM = String(myBPM);
 stringIBI = String(myIBI);
 stringPA = String(myPA);
 BPMFile = SD.open("BPM.txt", FILE_WRITE);
 IBIFile = SD.open("IBI.txt", FILE_WRITE);
 PAFile = SD.open("PA.txt", FILE_WRITE);
  if (BPMFile && IBIFile && PAFile) {
     Serial.println("Writing to BPM.txt...");
     BPMFile.println(stringBPM + "\n");
     delay(50);
     Serial.println("Writing to IBI.txt...");
     IBIFile.println(stringIBI + "\n");
     delay(50);
     Serial.println("Writing to PA.txt...");
     PAFile.println(stringPA + "\n");
     delay(500);
    // close the files:
    BPMFile.close();
    IBIFile.close();
    PAFile.close();
    delay(500);
    Serial.println("done.");
    delay(500);
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening BPM.txt");
}
}
  delay(500);                    // considered best practice in a simple sketch.
  
}

