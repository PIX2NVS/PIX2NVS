#include "all_defines.h"

void log_frame(float **frame, int ImageWidth, int ImageHeight)
{
  
       for (int i = 0; i < ImageWidth; i++)
       {
               for (int j = 0; j < ImageHeight; j++)
               {
                       frame[i][j] = log(frame[i][j]) ;
               }
       }

}


