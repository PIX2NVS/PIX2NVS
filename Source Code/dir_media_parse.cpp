#include "all_defines.h"
#include <iostream>

using namespace std ;

extern int tot_input; extern int tot_pic_input;

struct MEDIA_FILE *dir_media_parse(struct MEDIA_FILE *media_file, char *dir_query, const char *media_dir, bool inspect_frames)
{
	DIR *dp ;
	int *pti ; // Pointer to total input

	if (inspect_frames) { pti = &tot_pic_input ; } else { pti = &tot_input ; }
	struct dirent *ep ;
	dp = opendir(media_dir) ;

        int TOT_TYPES = (inspect_frames) ? TOT_FRAME_TYPES:TOT_VIDEO_TYPES ;

	char media_types[TOT_TYPES][EXT_SIZE] ;
	if (inspect_frames) { memcpy(media_types[0], FRAME_TYPES[0], TOT_TYPES * EXT_SIZE) ; }
	else { memcpy(media_types[0], VIDEO_TYPES[0], TOT_TYPES * EXT_SIZE) ; } 

	if (dp != NULL)
	{
		while (ep = readdir(dp))
		{
			for (int i = 0; i < TOT_TYPES ; i++)
			{
				int useful_file = 0;

				if (strstr(ep->d_name, media_types[i]) != NULL) { useful_file = 1 ; }

				if (useful_file)
				{
					media_file[*pti].filename = 
						(char *)calloc(MAX_STRING_SIZE, sizeof(char)) ;
					strcpy(media_file[*pti].filename, ep->d_name) ;
					media_file[*pti].extension = i ;
					if (*pti == MAX_FILES - 1)
					{
						printf("\nWarning: more than %d media files detected, " 
							"stopping the directory parsing to the first %d.\n", 
							MAX_FILES, MAX_FILES) ;
						break;
					}
					(*pti) = *pti + 1 ;
					break;
				}
			}
		}

		(void)closedir(dp);
	}
	else
		perror("Could not open ./input");

	return(media_file);
}
