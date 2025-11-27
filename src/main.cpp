#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
// #include <SdFat.h>

#define SD_CS_PIN 10

class DualSD {

  private:
  
    File teensySDFile;
    File externalSDFile;

    char* teensyFileName;
    char* externalSDFileName;

    int teensy_cspin;
    int external_cspin;

  public:

    DualSD(char* teensyFileName, char* externalSDFileName) {

      teensySDFile = NULL;
      externalSDFile = NULL;

      teensy_cspin = NULL;
      external_cspin = NULL;

    }

    int begin(int teensy_cspin, int external_cspin) {

      if (SD.begin(teensy_cspin) && SD.begin(external_cspin)) {
        
        this->teensy_cspin = teensy_cspin;
        this->external_cspin = external_cspin;

        return 1;
      
      }

      return -1;
    
    };

    int exists(char* filename) {

      SD.exists(filename);

    };

    int initializeFiles(char* dataHeaders) {


      // get last created file id
      // (device)_data_log_(id)

      // this->teensyFileName = teensyFileName;
      // this->externalSDFileName = externalSDFileName;
      
      char* id = "00AA";
      // create file and have starter CSV line
      if (SD.exists())
      this->write(dataHeaders);

    };

    int write(char* data) {

      // ensure teensy sd card is selected and external sd is not
      // https://forum.arduino.cc/t/two-sd-cards-on-the-same-project/1012605
      digitalWrite(external_cspin, HIGH);
      digitalWrite(teensy_cspin, LOW);

      teensySDFile = SD.open(teensyFileName, FILE_WRITE);
      teensySDFile.write(data);
      teensySDFile.close();

      // ensure external sd card is selected and teensy sd is not
      digitalWrite(teensy_cspin, HIGH);
      digitalWrite(external_cspin, LOW);

      externalSDFile = SD.open(externalSDFileName, FILE_WRITE);
      externalSDFile.write(data);
      externalSDFile.close();

    }
  
};

const DualSD SDManager;

// put function declarations here:


void setup() {
  // put your setup code here, to run once:

  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(19200);

  Serial.println("Testing MicroSD");

  if (SD.begin(SD_CS_PIN)) {

    Serial.println("MicroSD Extension working.");

  } else {

    Serial.println("MicroSD Extension not working.");

  }



}

void loop() {

  
  // put your main code here, to run repeatedly:

  // digitalWrite(LED_BUILTIN, HIGH);

  // Serial.println("LED on.");

  // delay(500);

  // digitalWrite(LED_BUILTIN, LOW);

  // Serial.println("LED off.");

  // delay(500);

}

// put function definitions here:
