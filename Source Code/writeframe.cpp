#include "all_defines.h"
#include <iostream>
#include <fstream>
using namespace std;

float** writeframe(char *filename, float **frame, int ImageWidth, int ImageHeight)
{
        // fprintf(stdout,"Writing frame to %s ..\n", filename) ;
        FILE * ofile ; ofile = fopen(filename, "wb") ; 

        for (int i = 0 ; i < ImageWidth ; i++){
          fwrite(frame[i], sizeof(float), ImageHeight, ofile) ;
        }
}


