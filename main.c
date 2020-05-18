#include"bitmap.h"
#include<stdlib.h>
#include<stdio.h>
#include<omp.h>

int writeOutput(int num, int imgSz, double time);

int main(int argc, char *argv[])
{
	if(argc != 4){
		fprintf(stderr, "Usage: program <# of threads> <inputFile> <outputFile>\n");
		exit(1);
	}

	Image *colorImg;
	int nThread = atoi(argv[1]);

	if((colorImg = Read_Bmp(argv[2])) == NULL){
		exit(1);
	}

	// In colorImag, upperLeft (0,0),
	// lowerRight (colorImg->width-1,colorImg->height-1)
	// For position (i,j), colorImg->data[j*colorImg->width+i]
	int i, maxP = colorImg->height * colorImg->width;
	double st, en, ti;

	omp_set_num_threads(nThread);
	st = omp_get_wtime();
#pragma omp parallel for
	for(i=0; i < maxP; i++){
		colorImg->data[i].b = 255 - colorImg->data[i].b;
		colorImg->data[i].g = 255 - colorImg->data[i].g;
		colorImg->data[i].r = 255 - colorImg->data[i].r;
	}
	en = omp_get_wtime();
	ti = (en-st)*1000.0;

	if(Write_Bmp(argv[3], colorImg)){
		exit(1);
	}

	Free_Image(colorImg);

	printf("# of threads: %d\n", nThread);
	printf("# of processors: %d\n", omp_get_num_procs());
	printf("Elapsed time: %g [ms]\n", ti);

	return writeOutput(nThread, maxP, ti);
}

int writeOutput(int num, int imgSz, double time)
{
    const char *fileName = "data.csv";
    FILE *fWriter = fopen(fileName, "a");
    if(NULL == fWriter)
    {
        printf("error");
        return 1;
    }
    fprintf(fWriter, "%d,%d,%g \n",num, imgSz, time);
    return 0;
}

