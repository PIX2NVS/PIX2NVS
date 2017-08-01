
#include "all_defines.h"
using namespace std ;

int tot_input = 0 ; int tot_pic_input = 0 ;

float d = DEFAULT_D ; int n_max = DEFAULT_N_MAX ;
float fixed_thres = DEFAULT_THRESHOLD ; int blocksize = DEFAULT_BLOCKSIZE ;
float adapt_thres_coef_shift = DEFAULT_ADAPT_THRES_COEF_SHIFT ;


int main(int argc, char *argv[])
{

	int status ; char *cmd ; struct MEDIA_FILE *media_file ;

	/* Parse user input */
	Helper::parse_input(argc, argv, &d, &fixed_thres, 
		&adapt_thres_coef_shift, &n_max, &blocksize) ;
        check_arguments(d, n_max, fixed_thres, adapt_thres_coef_shift, blocksize);
        
	
	cmd = (char *)calloc(MAX_STRING_SIZE, sizeof(char));
	media_file = (struct MEDIA_FILE *)calloc(MAX_FILES, sizeof(struct MEDIA_FILE));

	/* Create a log file */
	char *logfileName = (char *)calloc(MAX_STRING_SIZE, sizeof(char)) ;
	sprintf(logfileName, LOG_NAME) ; FILE *logfile = Helper::openFile(logfileName) ;
	
	// Check whether input folder exists --
	// Helper::openFolder("input", false) ; 	

	/* Load input video details */

	media_file = dir_media_parse(media_file, NULL, INPUT_FOLDER, false) ;
	fprintf(logfile, "\nFound %d files in the ./input directory \n", tot_input);

	/* Generate events for each video */
	for (int ivid = 0; ivid < tot_input; ivid++)
	{
		clock_t begin_video = clock();
		printf("Processing video: %s ..\n", media_file[ivid].filename);

		struct MEDIA_FILE *pic_file;
		pic_file = (struct MEDIA_FILE *)calloc(MAX_FILES, sizeof(struct MEDIA_FILE));


		/* Check whether ffprobe exists and run */
		if (access("ffprobe", F_OK) == 0)
		{
			sprintf(cmd, "./ffprobe -show_streams \"%s%s\" > %s 2> err", 
					INPUT_FOLDER, media_file[ivid].filename, FFPROBE_OUTPUT) ;
			system(cmd);
		}
		else
		{
			printf("ffprobe binary does not exist.. refer to"
				       " the README file\n") ; exit(-1) ;
		}

		/* Get video parameters */
		struct VIDEO_PER video_per;
		video_per.FrameRate = (char *)calloc(MAX_STRING_SIZE, sizeof(char));
		video_per = get_video_per(video_per);


		/* Check temporary frames folder*/
		Helper::openFolder(FRAMES_FOLDER, false) ;

		sprintf(cmd, "./ffmpeg -i \"%s%s\" -r %s %s/frame%%d.bmp > null 2> err", 
				INPUT_FOLDER, media_file[ivid].filename, video_per.FrameRate, 
				FRAMES_FOLDER) ; system(cmd);

		/* Count the number of frames */
		pic_file = dir_media_parse(pic_file, NULL, FRAMES_FOLDER, true) ;

		/* Check whether video is corrupted or empty */
		if (tot_pic_input == 0)
		{
			printf("%s is corrupted or empty, this video will be skipped.\n", 
				media_file[ivid].filename);
		}
		else
		{

			/* Generate Events */
			status = generate_events(pic_file, video_per.TimeGap, media_file, 
					ivid, video_per.ImageWidth, video_per.ImageHeight);

		}

		// Clear frames folder
		Helper::openFolder(FRAMES_FOLDER, true) ;

		// Free memory
		for (int i = 0; i < MAX_FILES; i++)
		{
			free(pic_file[i].filename);
		}
		free(pic_file) ; free(video_per.FrameRate) ;

	}

	fclose(logfile);
	// Free memory
	for (int i = 0; i < MAX_FILES; i++)
	{
		free(media_file[i].filename);
	}
	free(media_file);
	
	free(cmd) ; printf("\n") ;

}

