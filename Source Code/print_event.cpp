#include "all_defines.h"

int print_event(FILE *event, float diff_frame, float threshold, int n_max, int i, int j, int id, double TimeGap, int ImageHeight, int p)
{
	int moddiff = diff_frame / threshold;
	int evenum;


	if (moddiff > n_max)
	{
		evenum = n_max;
	}
	else
	{
		evenum = moddiff;
	}

        // fprintf(event, "moddiff(preround) = %f ; threshold = %f ; diff_frame = %f ; Total events number: %d\n", diff_frame / threshold, threshold, diff_frame, evenum);

	for (int e = 0; e < evenum; e++)
	{

		fprintf(event, "%d ", i);
		fprintf(event, "%d ", ImageHeight - 1 -j);
		fprintf(event, "%d ", (int)round((TimeGap*(e + 1)*threshold) / (diff_frame)+(TimeGap) * (id - 1)));
		fprintf(event, "%d\n", p);
	}

	return(evenum);
}
