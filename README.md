# Datalogger for monitoring heart parameters

This project is a module designed to monitor heart parameters such as:

- Number of heartbeats per minute (Beats Per Minute - BPM)
- The time interval between two beats (Interbeat interval - IBI) 
- Maximum amplitude of the pulse waveform (Pulse Amplitude - PA)

These values are saved on a memory card and at a later time are sent to an API (Application Programming Interface) called "Measurify" that allows to manage large quantities of measurements coming from sensors. Finally, the data are ordered and embedded in a web interface based on HTML, CSS and Javascript.

The project consists of two physical modules and a Web interface:
- Arduino UNO module with pulse sensor and microsd card adaptor for detection and
storage of data

 ![Arduino UNO with sensor](images/figure1.png?raw=true "Figure 1”)
- ESP32 module with microsd card adaptor in order to establish an HTTP communication between the
device and the Web API "Measurify"

 ![ESP32 and MicroSD Card Adaptor](images/figure2.png?raw=true "Figure 2”)
- HTML, CSS and Javascript-based web interface to sort data in a table

 ![Web Application](images/figure3.png?raw=true "Figure 3”)

## Quick start

- Connect the pulse sensor and the microsd card adaptor (with empty microsd inserted) to the Arduino UNO and load the code Pulsetosd.ino. After data acquisition the microsd contains three files called BPM.txt, IBI.txt and PA.txt that contain the values of interest

- Connect the microsd card adaptor (with microsd containing the data) to the ESP32 and load the Httppostpulse code.ino. You can change the HTTP requests by going to change the code: you can change the user (default thing:"mario.rossi") and the number of measures to post (default number=10)
```
String BPMResult[10];
String IBIResult[10];
String PAResult[10];
```
```
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
```

- To observe the data in the web application it is necessary to open index.html. The page shows the user of the measurements. The values BPM, IBI and Pulse Amplitude are shown from left to right. Each row shows the values corresponding to each recorded heartbeat. You can change the user (default thing:"mario.rossi") and the number of measures to post (default number=10) by going to edit the file data.js

```
 data: {filter: "{\"thing\":\"mario.rossi\"}", page : 1, limit :10},
```
```
       $('.value0PA').append(o.docs[0].samples[0].values[0]);
       $('.value1PA').append(o.docs[0].samples[1].values[0]);
       $('.value2PA').append(o.docs[0].samples[2].values[0]);
       (...)
       $('.value9PA').append(o.docs[0].samples[9].values[0]);
       $('.value0IBI').append(o.docs[1].samples[0].values[0]);
       $('.value1IBI').append(o.docs[1].samples[1].values[0]);
       $('.value2IBI').append(o.docs[1].samples[2].values[0]);
       (...)
       $('.value9IBI').append(o.docs[1].samples[9].values[0]);
       $('.value0BPM').append(o.docs[2].samples[0].values[0]);
       $('.value1BPM').append(o.docs[2].samples[1].values[0]);
       $('.value2BPM').append(o.docs[2].samples[2].values[0]);
       (...)
       $('.value9BPM').append(o.docs[2].samples[9].values[0]);
```


