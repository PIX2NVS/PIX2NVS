#include "all_defines.h"

int check_arguments(float d, int n_max, float fixed_thres, float adapt_thres_coef_shift, int  blocksize)
{
	if ((d != PREFRAME) && (d != UPWHENEVENT))
	{
		if((d<MIN_D)||(d>MAX_D))
		{
			printf("input invalid argument d, d shoule be 1 or 2 or [0.9,1]");
			exit(-1);
		}
	}

	if ((n_max < MIN_N_MAX) || (n_max > Max_N_MAX))
	{
		printf("input invalid argument n_max, n_max shoule be 1,2,3,4,5 ");
		exit(-1);
	}

	if ((fixed_thres < MIN_THRESHOLD) || (fixed_thres > MAX_THRESHOLD))
	{
		printf("input invalid argument fixed_thres, fixed_thres should be [0.2,0.7] ");
		exit(-1);
	}

	if ((adapt_thres_coef_shift < MIN__ADAPT_THRES_COEF_SHIFT) || (adapt_thres_coef_shift > MAX__ADAPT_THRES_COEF_SHIFT))
	{
		printf("input invalid argument adapt_thres_coef_shift,  adapt_thres_coef_shift should be [0,0.05] ");
		exit(-1);
	}

	if( (blocksize != BLOCKSIZE1)&& (blocksize != BLOCKSIZE2) && (blocksize != BLOCKSIZE3) )
	{
		printf("input invalid argument blocksize,  blocksize should be 1,2,4 ");
		exit(-1);
	}

	return(0);
}
