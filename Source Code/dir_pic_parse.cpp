#include "all_defines.h"


extern int tot_pic_input;


struct MEDIA_FILE *dir_pic_parse(struct MEDIA_FILE *pic_file, char *dir_query)
{

	DIR *dp;
	struct dirent *ep;
	dp = opendir(TMP_FOLDER);

	if (dp != NULL)
	{
		while (ep = readdir(dp))
		{
			for (int i = 0; i < TOT_PIC_TYPES; i++)
			{
				int useful_file = 0;

				if (dir_query == NULL)
				{
					if (strstr(ep->d_name, pic_type[i]) != NULL)
						useful_file = 1;
				}
				else
					if ((strstr(ep->d_name, pic_type[i]) != NULL) && ((strstr(ep->d_name, dir_query) != NULL)))
						useful_file = 1;

				if (useful_file)
				{
					pic_file[tot_pic_input].filename = (char *)calloc(MAX_STRING_SIZE, sizeof(char));
					strcpy(pic_file[tot_pic_input].filename, ep->d_name);
					pic_file[tot_pic_input].extension = i;
					if (tot_pic_input == MAX_FILES - 1)
					{
						printf("\n\n Warning: more than %d media files detected, stopping the directory parsing to the first %d. \n\n", MAX_FILES, MAX_FILES);
						break;
					}
					tot_pic_input++;
					break;
				}
			}
		}

		(void)closedir(dp);
	}
	else
		perror("Couldn't open the ./output directory");

	return(pic_file);
}
