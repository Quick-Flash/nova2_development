#include "SDLogger.hh"

SDLogger::SDLogger(){

}


SDLogger::SDLogger(String newFileName){

}

void SDLogger::openFile(){
  if(Serial) Serial.println("Initializing SD card...");
  if (!SD.begin()) {
    if(Serial) Serial.println("initialization failed!");
    while (1) {
      digitalWrite(RED, HIGH);
      delay(1000);
      digitalWrite(RED, LOW);
      delay(1000);
    }
  } else {
    if(Serial) Serial.println("SD Initialized");
  }
  //less stupid naming convention - 0000.csv to 9999.csv
  //look through SD card, find the next available filename
  bool fileavail = false;
  int i = 0;
  while (!fileavail) {  
    if (i < 10)
      fileName = String("000" + String(i) + ".csv");
    else if (i < 100)
      fileName = String("00" + String(i) + ".csv");
    else if (i < 1000)
      fileName = String("0" + String(i) + ".csv");
    else
      fileName = String(String(i) + ".csv");
    fileavail = !SD.exists(fileName);
    i++;
  }
  flightData = SD.open(fileName, FILE_WRITE);
  if(Serial) Serial.println("Writing to File: " + fileName);
  // Write the headers:
  if (flightData) {
    if(Serial) Serial.print("Writing to " + fileName);
    flightData.print("RawA_x(ms2),RawA_y(ms2),RawA_z,(ms2)");
    flightData.print("SAAM_A_x(ms2),SAAM_A_y(ms2),SAAM_A_z(ms2)");
    flightData.print("Mag_x(mT),Mag_y(mT),Mag_z(mT)");
    flightData.println("Angle(rad),Altitude(m),Time(s)");
    flightData.flush();
    if(Serial) Serial.println("...headers done.");
    fileName = flightData.name();
  } else {
    if(Serial) Serial.println("error opening " + fileName);
    //red light means stop
    while (1) {
      digitalWrite(RED, HIGH);
      delay(500);
      digitalWrite(RED, LOW);
      delay(500);
    }
  }
}

void SDLogger::openFile(String newFileName){
  if(Serial) Serial.println("Initializing SD card...");
  if (!SD.begin()) {
    if(Serial) Serial.println("initialization failed!");
    while (1) {
      digitalWrite(RED, HIGH);
      delay(1000);
      digitalWrite(RED, LOW);
      delay(1000);
    }
  } else {
    if(Serial) Serial.println("SD Initialized");
  }
  fileName = newFileName;
  flightData = SD.open(fileName, FILE_WRITE);
  if(Serial) Serial.println("Writing to File: " + fileName);
  // Write the headers:
  if (flightData) {
    if(Serial) Serial.print("Writing to " + fileName);
    flightData.print("Time[us], Temp[C], Pressure[hPa],");
    flightData.print(" Omega_1[rad/s], Omega_2[rad/s], Omega_3[rad/s], acc_1[g], acc_2[g], acc_3[g],");
    flightData.println(" mag_1[uT], mag_2[uT], mag_3[uT]");
    flightData.flush();
    if(Serial) Serial.println("...headers done.");
    fileName = flightData.name();
  } else {
    if(Serial) Serial.println("error opening " + fileName);
    //red light means stop
    while (1) {
      digitalWrite(RED, HIGH);
      delay(500);
      digitalWrite(RED, LOW);
      delay(500);
    }
  }
}

void SDLogger::writeLog(float acc1, float acc2, float acc3, float saam1, float saam2, float saam3, float mag1, float mag2, float mag3, float ang, float alt, float t_now){
  if(Serial) Serial.println("Logging");
  flightData.print(acc1);flightData.print(',');
  flightData.print(acc2);flightData.print(',');
  flightData.print(acc3);flightData.print(',');
  flightData.print(saam1);flightData.print(',');
  flightData.print(saam2);flightData.print(',');
  flightData.print(saam3);flightData.print(',');
  flightData.print(mag1);flightData.print(',');
  flightData.print(mag2);flightData.print(',');
  flightData.print(mag3);flightData.print(',');
  flightData.print(ang);flightData.print(',');
  flightData.print(alt);flightData.print(',');
  flightData.println(t_now);

  flightData.flush();
}

void SDLogger::closeFile(){
    if (flightData.peek()!=0){
        flightData.close();
    }
}

void SDLogger::writeLog(){}

void SDLogger::writeLog(float accel, float vel, float h, float ang){
  flightData.print("Acc:");
  flightData.print(accel);
  flightData.print(",Vel:");
  flightData.print(vel);
  flightData.print(",H:");
  flightData.print(h);
  flightData.print(",Ang:");
  flightData.println(ang);

  flightData.flush();
}

void SDLogger::writeLog(float a_raw[], float m[], float a[]){
  flightData.print("a_raw[0]:");
  flightData.print(a_raw[0]);
  flightData.print("a_raw[1]:");
  flightData.print(a_raw[1]);
  flightData.print("a_raw[2]:");
  flightData.print(a_raw[2]);

  flightData.print("m[0]:");
  flightData.print(m[0]);
  flightData.print("m[1]:");
  flightData.print(m[1]);
  flightData.print("m[2]:");
  flightData.print(m[2]);

  flightData.print("a[0]:");
  flightData.print(a[0]);
  flightData.print("a[1]:");
  flightData.print(a[1]);
  flightData.print("a[2]:");
  flightData.print(a[2]);

  flightData.println();
  flightData.flush();
}