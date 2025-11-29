#include <Arduino.h>
#include <SD.h>
#include <DualSD.h>

DualSD::DualSD() {
  
  // what's good, I do literally nothing rn
  
}

int DualSD::begin(int teensy_cspin, int external_cspin) {

  if (SD.begin(teensy_cspin) && SD.begin(external_cspin)) {
        
    this->teensy_cspin = teensy_cspin;
    this->external_cspin = external_cspin;

    return 1;
      
  }

  return -1;

}

int DualSD::exists(char* filename) {

  if (SD.exists(filename)) { return 1; }

  return -1;

};

int DualSD::initializeFiles(char* dataHeaders) {

  const char* id = "00AAF";

  // 19 and 18 are exactly enough to fit the file
  char teensyFileName[19];
  char externalFileName[18];

  strcpy(teensyFileName, "tnsy_data_log");
  strcpy(externalFileName, "ext_data_log");

  strcat(teensyFileName, id);
  strcat(externalFileName, id);

  // create file and have starter CSV line
  // checks to see if the files already exist
  // if they do, we don't need to initialize
  if ( (SD.exists(teensyFileName) && SD.exists(externalFileName)) ) { return -1; }      
      
  this->write(dataHeaders);

  return 1;

}

int DualSD::write(char* data) {

  // ensure teensy sd card is selected and external sd is not
  // https://forum.arduino.cc/t/two-sd-cards-on-the-same-project/1012605
  digitalWrite(teensy_cspin, LOW);
  digitalWrite(external_cspin, HIGH);
  
  teensySDFile = SD.open(teensySDFileName, FILE_WRITE);
  teensySDFile.write(data);
  teensySDFile.close();

  // ensure external sd card is selected and teensy sd is not
  digitalWrite(teensy_cspin, HIGH);
  digitalWrite(external_cspin, LOW);
  
  externalSDFile = SD.open(externalSDFileName, FILE_WRITE);
  externalSDFile.write(data);
  externalSDFile.close();

  return 1;

}

int DualSD::read(char* teensyOutput, char* extOutput) {

  // file is not opened or does not exist
  if (!teensySDFile) { return -1; }

  // outputs for whatever is read
  *teensyOutput = teensySDFile.read();
  *extOutput = externalSDFile.read();
  
  return 1;

}
