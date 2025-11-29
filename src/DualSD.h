#include <SD.h>

#ifndef DUALSD_H
#define DUALSD_H

class DualSD {

    private:

        File teensySDFile;
        File externalSDFile;

        char* teensySDFileName;
        char* externalSDFileName;

        int teensy_cspin;
        int external_cspin;

    public:

        DualSD();

        int begin(int teensy_cspin, int external_cspin);

        int exists(char* filename);

        int initializeFiles(char* dataHeaders);

        int write(char* data);

        int read(char* teensyOutput, char* extOutput);


};

#endif