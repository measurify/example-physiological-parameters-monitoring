
#define TOKEN "JWT eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJfaWQiOiI1ZGQyNWFjZmVkNzA2ODJhOGQxMTQzNGEiLCJ1c2VybmFtZSI6InB1bHNlLXNlbnNvci11c2VyLXVzZXJuYW1lIiwidHlwZSI6InByb3ZpZGVyIiwiaWF0IjoxNTc1NjQ3MDQ3LCJleHAiOjE1NzU2NDg4NDd9.WhzCsK2iX_sQ3Fsi0vEsP0wuhrK6r5BlqT1Up4SgeQI"


 
#include <HTTPClient.h>
#include <mySD.h>
#include <SPI.h>
#include <WiFi.h>
File BPMFile;
File IBIFile;
File PAFile; 

String BPMResult[10];
String IBIResult[10];
String PAResult[10];
const char* ssid = "TP-LINK_8798EC";
const char* password =  "34918951";
const char server[] = "http://test.atmosphere.tools/v1/measurements";
 
void setup() {
  Serial.begin(115200);
  Serial.print("Initializing SD card...");
  /* initialize SD library with SPI pins */
  if (!SD.begin(4, 23, 19, 18)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  /* Begin at the root "/" */
  BPMFile = SD.open("/");
  if (BPMFile) {    
    printDirectory(BPMFile, 0);
    delay(3000);
    BPMFile.close();
  } else {
    Serial.println("error opening root");
  }
  
  WiFi.begin(ssid, password); 
 
  while (WiFi.status() != WL_CONNECTED) { //Check for the connection
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
 
}
 
void loop() {
  
 
 if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
   BPMFgets();
   delay(3000);
   HTTPClient http;   
 
   http.begin(server);  //Specify destination for HTTP request
   http.addHeader("Content-Type", "application/json");//Specify content-type header
   http.addHeader("Authorization", TOKEN);
   String BPMbody = getBPMBody();
 
   int httpResponseCodeBPM = http.POST(BPMbody);   //Send the actual POST request
 
   if(httpResponseCodeBPM>0){
 
    String BPMresponse = http.getString();                       //Get the response to the request
 
    Serial.println(httpResponseCodeBPM);   //Print return code
    Serial.println(BPMresponse);           //Print request answer

   }else{
 
    Serial.print("Error on sending POST (BPM): ");
    Serial.println(httpResponseCodeBPM);
 
   }
 
   http.end();  //Free resources
   //------------------------

   IBIFgets();
   delay(3000);
 
   http.begin(server);  //Specify destination for HTTP request
   http.addHeader("Content-Type", "application/json");//Specify content-type header
   http.addHeader("Authorization", TOKEN);
   String IBIbody = getIBIBody();
 
   int httpResponseCodeIBI = http.POST(IBIbody);   //Send the actual POST request
 
   if(httpResponseCodeIBI>0){
 
    String IBIresponse = http.getString();                       //Get the response to the request
 
    Serial.println(httpResponseCodeIBI);   //Print return code
    Serial.println(IBIresponse);           //Print request answer

   }else{
 
    Serial.print("Error on sending POST (IBI): ");
    Serial.println(httpResponseCodeIBI);
 
   }
 
   http.end();  //Free resources
   //------------------------
   PAFgets();
   delay(3000);
 
   http.begin(server);  //Specify destination for HTTP request
   http.addHeader("Content-Type", "application/json");//Specify content-type header
   http.addHeader("Authorization", TOKEN);
   String PAbody = getPABody();
 
   int httpResponseCodePA = http.POST(PAbody);   //Send the actual POST request
 
   if(httpResponseCodePA>0){
 
    String PAresponse = http.getString();                       //Get the response to the request
 
    Serial.println(httpResponseCodePA);   //Print return code
    Serial.println(PAresponse);           //Print request answer

   }else{
 
    Serial.print("Error on sending POST (PA): ");
    Serial.println(httpResponseCodePA);
 
   }
 
   http.end();  //Free resources
   

 }else{
 
    Serial.println("Error in WiFi connection");   
 
 }
 
  delay(10000);  //Send a request every 10 seconds
  while(1);
}

String getBPMBody() {
  String body = "";
  body += " {\"thing\": \"mario.rossi\",";
  body += " \"feature\": \"heart-rate\",";
  body += " \"device\": \"pulse-sensor\",";
  body += " \"samples\": [ ";
  body +=     " { \"values\": [" + BPMResult[0] + "], \"delta\": 0 }, ";
  body +=     " { \"values\": [" + BPMResult[1] + "], \"delta\": 10 }, ";
  body +=     " { \"values\": [" + BPMResult[2] + "], \"delta\": 20 }, ";
  body +=     " { \"values\": [" + BPMResult[3] + "], \"delta\": 30 }, ";
  body +=     " { \"values\": [" + BPMResult[4] + "], \"delta\": 40 }, ";
  body +=     " { \"values\": [" + BPMResult[5] + "], \"delta\": 50 }, ";
  body +=     " { \"values\": [" + BPMResult[6] + "], \"delta\": 60 }, ";
  body +=     " { \"values\": [" + BPMResult[7] + "], \"delta\": 70 }, ";
  body +=     " { \"values\": [" + BPMResult[8] + "], \"delta\": 80 }, ";
  body +=     " { \"values\": [" + BPMResult[9] + "], \"delta\": 90 } ";
  body +=     " ] }";
  
//  Serial.println("Body = " + body);
  
  return body;
}

String getIBIBody() {
  String body = "";
  body += " {\"thing\": \"mario.rossi\",";
  body += " \"feature\": \"interbeat-interval\",";
  body += " \"device\": \"pulse-sensor\",";
  body += " \"samples\": [ ";
  body +=     " { \"values\": [" + IBIResult[0] + "], \"delta\": 0 }, ";
  body +=     " { \"values\": [" + IBIResult[1] + "], \"delta\": 10 }, ";
  body +=     " { \"values\": [" + IBIResult[2] + "], \"delta\": 20 }, ";
  body +=     " { \"values\": [" + IBIResult[3] + "], \"delta\": 30 }, ";
  body +=     " { \"values\": [" + IBIResult[4] + "], \"delta\": 40 }, ";
  body +=     " { \"values\": [" + IBIResult[5] + "], \"delta\": 50 }, ";
  body +=     " { \"values\": [" + IBIResult[6] + "], \"delta\": 60 }, ";
  body +=     " { \"values\": [" + IBIResult[7] + "], \"delta\": 70 }, ";
  body +=     " { \"values\": [" + IBIResult[8] + "], \"delta\": 80 }, ";  
  body +=     " { \"values\": [" + IBIResult[9] + "], \"delta\": 90 } ";
  body +=     " ] }";
  
//  Serial.println("Body = " + body);
  
  return body;
}

String getPABody() {
  String body = "";
  body += " {\"thing\": \"mario.rossi\",";
  body += " \"feature\": \"pulse-amplitude\",";
  body += " \"device\": \"pulse-sensor\",";
  body += " \"samples\": [ ";
  body +=     " { \"values\": [" + PAResult[0] + "], \"delta\": 0 }, ";
  body +=     " { \"values\": [" + PAResult[1] + "], \"delta\": 10 }, ";
  body +=     " { \"values\": [" + PAResult[2] + "], \"delta\": 20 }, ";
  body +=     " { \"values\": [" + PAResult[3] + "], \"delta\": 30 }, ";
  body +=     " { \"values\": [" + PAResult[4] + "], \"delta\": 40 }, ";
  body +=     " { \"values\": [" + PAResult[5] + "], \"delta\": 50 }, ";
  body +=     " { \"values\": [" + PAResult[6] + "], \"delta\": 60 }, ";
  body +=     " { \"values\": [" + PAResult[7] + "], \"delta\": 70 }, ";
  body +=     " { \"values\": [" + PAResult[8] + "], \"delta\": 80 }, ";
  body +=     " { \"values\": [" + PAResult[9] + "], \"delta\": 90 } ";
  body +=     " ] }";
  
//  Serial.println("Body = " + body);
  
  return body;
}

void BPMFgets() {
  String line;
  int i=0;
  // open test file    
  if (!SD.exists("BPM.txt")) {     
    Serial.println("BPM.txt FOUND");
    return; 
  }
  Serial.println("BPM.txt FOUND");
  File BPMFile = SD.open("BPM.txt",FILE_READ);      
  if (!BPMFile) {
    return;
  }
  Serial.println("BPM.txt open");
  
  // read lines from the file
   while (BPMFile.available() != 0) {     
    line = BPMFile.readStringUntil('\n');
    line.trim();      
    //Serial.println(line);
    if (i<= 9 && line != "") {
       
       BPMResult[i] = line;
       Serial.println(BPMResult[i]);
       i= i+1;
        }
     else {
      // no '\n' - line too long or missing '\n' at EOF
      // handle error
          }
      }
  }


void IBIFgets() {
  String line;
  int i=0;
  // open test file    
  if (!SD.exists("IBI.txt")) {     
    Serial.println("IBI.txt NOT FOUND");
    return; 
  }
  Serial.println("IBI.txt FOUND");
  File IBIFile = SD.open("IBI.txt",FILE_READ);      
  if (!IBIFile) {
    return;
  }
  Serial.println("IBI.txt open");
  
  // read lines from the file
   while (IBIFile.available() != 0) {     
    line = IBIFile.readStringUntil('\n');
    line.trim();      
    //Serial.println(line);
    if (i<= 9 && line != "") {
       
       IBIResult[i] = line;
       Serial.println(IBIResult[i]);
       i= i+1;
        }
     else {
      // no '\n' - line too long or missing '\n' at EOF
      // handle error
          }
      }
  }


void PAFgets() {
  String line;
  int i=0;
  // open test file    
  if (!SD.exists("PA.txt")) {     
    Serial.println("PA.txt NOT FOUND");
    return; 
  }
  Serial.println("PA.txt FOUND");
  File PAFile = SD.open("PA.txt",FILE_READ);      
  if (!PAFile) {
    return;
  }
  Serial.println("PA.txt open");
  
  // read lines from the file
   while (PAFile.available() != 0) {     
    line = PAFile.readStringUntil('\n');
    line.trim();      
    //Serial.println(line);
    if (i<= 9 && line != "") {
       
       PAResult[i] = line;
       Serial.println(PAResult[i]);
       i= i+1;
        }
     else {
      // no '\n' - line too long or missing '\n' at EOF
      // handle error
          }
      }
  }







void printDirectory(File dir, int numTabs) {
  
  while(true) {
     File entry =  dir.openNextFile();
     if (! entry) {
       break;
     }
     for (uint8_t i=0; i<numTabs; i++) {
       Serial.print('\t');   // we'll have a nice indentation
     }
     // Print the name
     Serial.print(entry.name());
     /* Recurse for directories, otherwise print the file size */
     if (entry.isDirectory()) {
       Serial.println("/");
       printDirectory(entry, numTabs+1);
     } else {
       /* files have sizes, directories do not */
       Serial.print("\t\t");
       Serial.println(entry.size());
     }
     entry.close();
   }
}
