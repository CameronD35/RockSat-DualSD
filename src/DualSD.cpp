#include <Arduino.h>
#include <SD.h>
#include <DualSD.h>
#include <string.h>

DualSD::DualSD() {
  
  // what's good, I do literally nothing rn
  
}

// returns 1 if successful on both SD cards, otherwise returns -1
int DualSD::begin(int teensy_cspin, int external_cspin) {

  if (SD.begin(teensy_cspin) && SD.begin(external_cspin)) {
        
    this->teensy_cspin = teensy_cspin;
    this->external_cspin = external_cspin;

    return 1;
      
  }

  return -1;

}

// returns 1 if a file exists on teensy or external, returns -1 if it doesn't exist
int DualSD::exists(char* filename) {

  digitalWrite(teensy_cspin, LOW);
  digitalWrite(external_cspin, HIGH);

  if (SD.exists(filename)) { return 1; }

  digitalWrite(teensy_cspin, HIGH);
  digitalWrite(external_cspin, LOW);

  if (SD.exists(filename)) { return 1; }

  return -1;

};

// initializes files with ehaders (used for CSV)
// returns 1 if successful, returns -1 if not
int DualSD::initializeFiles(const char* dataHeaders) {

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

// writes data to both sd cards
// returns 1 is successful
int DualSD::write(String data) {

  // ensure teensy sd card is selected and external sd is not
  // https://forum.arduino.cc/t/two-sd-cards-on-the-same-project/1012605
  digitalWrite(teensy_cspin, LOW);
  digitalWrite(external_cspin, HIGH);
  
  teensySDFile = SD.open(teensySDFileName, FILE_WRITE);
  if (!(teensySDFile.println(data) != sizeof(data))) { return -1; } ;
  teensySDFile.close();

  // ensure external sd card is selected and teensy sd is not
  digitalWrite(teensy_cspin, HIGH);
  digitalWrite(external_cspin, LOW);
  
  externalSDFile = SD.open(externalSDFileName, FILE_WRITE);
  if (!(externalSDFile.println(data) != sizeof(data))) { return -1; };
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