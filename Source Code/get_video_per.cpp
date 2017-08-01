#include "all_defines.h"

struct VIDEO_PER get_video_per(struct VIDEO_PER video_per)
{

	FILE *file = fopen(FFPROBE_OUTPUT, "rb");

	char *linein;
	linein = (char *)calloc(MAX_STRING_SIZE, sizeof(char));

	char *frameratein1;
	char *frameratein2;
	char *widthin;
	char *heightin;
	frameratein1 = (char *)calloc(MAX_STRING_SIZE, sizeof(char));
	frameratein2 = (char *)calloc(MAX_STRING_SIZE, sizeof(char));
	widthin = (char *)calloc(MAX_STRING_SIZE, sizeof(char));
	heightin = (char *)calloc(MAX_STRING_SIZE, sizeof(char));

	char tem_RA[BUFFERSIZE];

	strcpy(frameratein1, "0/0");
	strcpy(frameratein2, "0/0");


	while (1)
	{
		if (fgets(linein, MAX_STRING_SIZE, file) == NULL) break ;
		else
		{
			if (strstr(linein, "width=") != NULL)
			{
				strcpy(widthin, linein);
			}

			if (strstr(linein, "height=") != NULL)
			{
				strcpy(heightin, linein);
			}

			if ((strstr(linein, "r_frame_rate=") != NULL) && (strstr(frameratein1, "0/0") != NULL))
			{
				strcpy(frameratein1, linein);
			}

			if (strstr(linein, "avg_frame_rate=") != NULL && (strstr(frameratein2, "0/0") != NULL))
			{
				strcpy(frameratein2, linein);
			}

		}

	}

	if (strstr(linein, "[/STREAM]") == NULL)
	{

		int err2 = fclose(file);
		// printf("\n\n close err: %d ... ", err2);

		free(linein);
		free(frameratein1);
		free(frameratein2);
		free(widthin);
		free(heightin);
		return(video_per);

	}
	else
	{

		video_per.ImageWidth = atoi(strstr(widthin, "width=") + SIZEOFWIDTH);
		video_per.ImageHeight = atoi(strstr(heightin, "height=") + SIZEOFHEIGHT);



		if (strstr(frameratein1, "0/0") == NULL)
		{
			strcpy(tem_RA, strstr(frameratein1, "rate=") + SIZEOFRATE);
		}
		else
		{
			strcpy(tem_RA, strstr(frameratein2, "rate=") + SIZEOFRATE);
		}



		char *s = strstr(tem_RA, "/") + 1;
		double b = atof(s);
		double a = atof(tem_RA);
		video_per.TimeGap = TIMESCALE  * (b / a);
		sprintf(video_per.FrameRate, "%f", (a / b));



		int err2 = fclose(file);
		// printf("\n\n close err: %d ... ", err2);

		free(linein);
		free(frameratein1);
		free(frameratein2);
		free(widthin);
		free(heightin);
		return(video_per);
	}


}
