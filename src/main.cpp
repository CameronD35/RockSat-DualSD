#include <DualSD.h>

#define EXT_SD_CS_PIN 10
#define INT_SD_CS_PIN 13

DualSD SDManager;

void setup() {

  SDManager.begin(EXT_SD_CS_PIN, INT_SD_CS_PIN);

}

void loop() {

}

// put function definitions here: