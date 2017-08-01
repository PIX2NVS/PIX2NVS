#include "all_defines.h"
struct stat info ;

void Helper::openFolder(const char *fn, bool clear){
        char* cmd ; cmd = (char *)calloc(MAX_STRING_SIZE, sizeof(char)) ;
	// Create directory if not found ; Clear if specified
        if(stat(fn, &info) != 0){ 
		fprintf(stderr, "Creating folder %s ..", fn) ;
		sprintf(cmd, "mkdir %s", fn) ; system(cmd) ; }
	else if (clear) { sprintf(cmd, "rm -rf %s/*", fn) ; system(cmd) ; }
        }

FILE *Helper::openFile(char *fn){
        FILE *f = fopen(fn, "wt") ;
        if (f == NULL) { printf("File %s could not be created.\n", fn) ; exit(-1) ; }
	else { return f ; }
	}

void Helper::parse_input(int argc, char *argv[], float *d, float *fixed_thres,   
                    float *adapt_thres_coef_shift, int *n_max, int *blocksize) {
	
	if (argc < 3) printf("\nRunning with default parameters..\n\n") ;

	for (int i = 1; i < argc; i++) {
		if      (strcmp(argv[i], "-r") == 0 )*d = atof(argv[(++i)]) ;
		else if (strcmp(argv[i], "-n") == 0) *n_max = atoi(argv[(++i)]) ;
		else if (strcmp(argv[i], "-b") == 0) *blocksize = atoi(argv[(++i)]) ;
		else if (strcmp(argv[i], "-f") == 0) *fixed_thres = atof(argv[(++i)]) ;
		else if (strcmp(argv[i], "-a") == 0) *adapt_thres_coef_shift = atof(argv[(++i)]) ;
		}
	
	}
