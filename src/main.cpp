#include <DualSD.h>

#define EXT_SD_CS_PIN 10
#define INT_SD_CS_PIN BUILTIN_SDCARD

DualSD SDManager;

int test;

void setup() {

  Serial.begin(19200);

  if (SDManager.begin(EXT_SD_CS_PIN, INT_SD_CS_PIN)) {

    Serial.println("I'm working!!!!!!!!!");
    test = 1;

  } else { Serial.println("Me no work :(((((("); test = 0; }

}

void loop() {

  delay(500);
  Serial.println(test);
  
}

// put function definitions here: