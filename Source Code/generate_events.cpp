#include "all_defines.h"
using namespace std ;

extern int tot_pic_input ; extern float d ;
extern int n_max ; extern int blocksize ;
extern float fixed_thres ; extern float adapt_thres_coef_shift ;

int generate_events(struct MEDIA_FILE *pic_file, double TimeGap, MEDIA_FILE *media_file, int ivid, int ImageWidth, int ImageHeight)
{

	// Allocate memory for reference frame, input frame, and threshold map
	float **reference    = initialize_frame(ImageWidth, ImageHeight, 0) ;
	float **input        = initialize_frame(ImageWidth, ImageHeight, 0) ;
        float **thresholdmap = initialize_frame(ImageWidth, ImageHeight, fixed_thres) ;
 
	// cmd: System command and filename buffer
	char *cmd = (char *)calloc(MAX_STRING_SIZE, sizeof(char));
	char *filename = (char *)calloc(MAX_STRING_SIZE, sizeof(char)) ;

	// Create events directory
	Helper::openFolder(EVENT_FOLDER, false) ;

	// Create event file
	sprintf(filename, "%s%s.txt", EVENT_FOLDER, media_file[ivid].filename) ;
	FILE *event = Helper::openFile(filename) ;

	if (d != 3){
	   int id_ = 1 ; sprintf(filename, "%sframe%d.bmp", TMP_FOLDER, id_) ;
	   reference = readframe(filename, reference, ImageWidth, ImageHeight) ; 
	   log_frame(reference, ImageWidth, ImageHeight) ; }


	// id: Frame ID
	for (int id = 2; id < tot_pic_input + 1; id++)
	{
		// Read frame
		sprintf(filename, "%sframe%d.bmp", TMP_FOLDER, id) ;
		input = readframe(filename, input, ImageWidth, ImageHeight);

		// Write frame 
		sprintf(filename, "%sframe%d.gs", TMP_FOLDER, id) ;
		writeframe(filename, input, ImageWidth, ImageHeight) ;
		
		log_frame(input, ImageWidth, ImageHeight) ;

		// Local inhibition
		for (int i = 0; i < ImageWidth; i = i + blocksize)
		{
			for (int j = 0; j < ImageHeight; j = j + blocksize)
			{
				// Find local maxima --
				// Set blocksize to 0 to disable Local Inhibition
				float diff ; float diff_ = 0 ; int i_shift = 0; int j_shift = 0;
				for (int ii = 0; ii < blocksize; ii++)
				{
					for (int jj = 0; jj < blocksize; jj++)
					{
						diff = abs(input[i + ii][j + jj] - reference[i + ii][j + jj]);
						if (diff > diff_)
						{
							diff_   = diff ;
							i_shift = ii ;
							j_shift = jj ;
						}
					}
				}


				// delta_B: Brightness Difference
				float delta_B = input[i + i_shift][j + j_shift] - reference[i + i_shift][j + j_shift];

				if (delta_B > thresholdmap[i + i_shift][j + j_shift])
				{
					// p: Polarity
					int p = ON ;
					int event_num = print_event(event, delta_B, 
					    thresholdmap[i + i_shift][j + j_shift], n_max, 
					    i + i_shift, j + j_shift, id, TimeGap, ImageHeight, p);

			        	// Update reference
                                        if (d == 2) { reference[i][j] = input[i][j]; }
					if (d == 3) { reference[i][j] = reference[i][j] + 
						      event_num * thresholdmap[i][j] ;  }

                                        // Update threshold map (Increase)
                                        thresholdmap[i][j] = (1 + adapt_thres_coef_shift) * 
								thresholdmap[i][j];

				}


				else if (delta_B < -thresholdmap[i + i_shift][j + j_shift])
				{
					delta_B = -delta_B;
					// p: Polarity
					int p = OFF;
					int event_num = print_event(event, delta_B, 
					    thresholdmap[i + i_shift][j + j_shift], n_max, 
					    i + i_shift, j + j_shift, id, TimeGap, ImageHeight, p);


				        // Update reference
                                        if (d == 2) { reference[i][j] = input[i][j]; }
					if (d == 3) { reference[i][j] = reference[i][j] - 
						      event_num * thresholdmap[i][j] ;  }

                                        // Update threshold map (Increase)
                                        thresholdmap[i][j] = (1 + adapt_thres_coef_shift) * 
								thresholdmap[i][j]; }

				else
				{
					// Update threshold map (Decrease)
					thresholdmap[i][j] = (1 - adapt_thres_coef_shift) * 
								thresholdmap[i][j];
				}


				// Update reference (Copy Input)
				if (d == 1)
				{
					for (int m = 0; m < blocksize; m++)
					{
						for (int n = 0; n < blocksize; n++)
						{
							reference[i + m][j + n] = input[i + m][j + n];
						}
					}
				}

			}
		}
	}

	fclose(event) ; 
	free(cmd) ; free(filename) ;

	// Necessary (External Variable)
	tot_pic_input = 0 ; 

	// Free allocated memory
	for (int i = 0; i < ImageWidth; i++)
	{
		free(reference[i]);
	}
	free(reference);

	for (int i = 0; i < ImageWidth; i++)
	{
		free(input[i]);
	}
	free(input);

	for (int i = 0; i < ImageWidth; i++)
	{
		free(thresholdmap[i]);
	}
	free(thresholdmap);

	return(1);
}
