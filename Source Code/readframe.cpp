#include "all_defines.h"

using namespace std;

float** readframe(char *filename, float **frame, int ImageWidth, int ImageHeight)
{
        // Initialize buffer and Read file
        vector<char> buffer ; 
        std::ifstream file(filename);
            if (file) {
                file.seekg(0,std::ios::end);
                streampos length = file.tellg();
                file.seekg(0,std::ios::beg);
                buffer.resize(length);
                file.read(&buffer[0],length); }
        file.close() ; 
  
        // Get BMP header size
        PBITMAPFILEHEADER file_headeri ; PBITMAPINFOHEADER info_header;
	size_t header_size = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) ;

	// Load data into frame 
	PRGBDATA pixel ; int i_ ;
        PRGBDATA data = (PRGBDATA)(&buffer[0] + header_size);
	for (int i = ImageHeight - 1 ; i >= 0 ; i--)
	{
		for (int j = 0; j < ImageWidth; j++)
		{
		  pixel = data + (ImageWidth * i + j) ; i_ = ImageHeight - i - 1 ;
		  frame[j][i_] = RGB_R * pixel->rgbtRed  + RGB_G * pixel->rgbtGreen + RGB_B * pixel->rgbtBlue ;
		}
	}
       
	return(frame) ;

} 


