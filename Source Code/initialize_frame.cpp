#include "all_defines.h"
#include <iostream>
#include <fstream>

using namespace std;

float** initialize_frame(int ImageWidth, int ImageHeight, float init_value)
{       
        float **frame ;
        frame = (float **)calloc(ImageWidth, sizeof(float *));
        for (int i = 0; i < ImageWidth; i++)
        {       
                frame[i] = (float *)calloc(ImageHeight, sizeof(float));
        }

	// Initialize frame to init_value
	if (init_value != 0){
	   	for (int i = 0; i < ImageWidth; i++)
	   	{
	   		for (int j = 0; j < ImageHeight; j++)
	   		{
	   			frame[i][j] = init_value ;
	   		}
	   	}
	}

        return(frame) ;
}

