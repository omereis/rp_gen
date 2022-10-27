#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "rp.h"
#include <stdio.h>

#define M_PI 3.14159265358979323846

void generate_signal (float x[], int buff_size);

int main(int argc, char **argv){

    int i;
    int buff_size = 16384;

    /* Print error, if rp_Init() function failed */
    if(rp_Init() != RP_OK){
        fprintf(stderr, "Rp api init failed!\n");
    }

    float *t = (float *)malloc(buff_size * sizeof(float));
    float *x = (float *)malloc(buff_size * sizeof(float));
    float *y = (float *)malloc(buff_size * sizeof(float));

    for(i = 1; i < buff_size; i++){
        t[i] = (2 * M_PI) / buff_size * i;
    }

    for (int i = 0; i < buff_size; ++i){
        x[i] = sin(t[i]) + ((1.0/3.0) * sin(t[i] * 3));
        y[i] = (1.0/2.0) * sin(t[i]) + (1.0/4.0) * sin(t[i] * 4);
    }

	generate_signal (x, buff_size);
/*
    rp_GenSynchronise();

    rp_GenWaveform(RP_CH_1, RP_WAVEFORM_ARBITRARY);
    //rp_GenWaveform(RP_CH_2, RP_WAVEFORM_ARBITRARY);

    rp_GenArbWaveform(RP_CH_1, x, buff_size);
    //rp_GenArbWaveform(RP_CH_2, y, buff_size);

	FILE *f = fopen("gaw.csv", "w+");
	for (i=0 ; i < buff_size ; i++)
		fprintf (f, "%g\n", x[i]);
	fclose(f);

    rp_GenAmp(RP_CH_1, 0.7);
    //rp_GenAmp(RP_CH_2, 1.0);

    rp_GenFreq(RP_CH_1, 4000.0);
	printf ("GenFreq\n");
	getchar();
    //rp_GenFreq(RP_CH_2, 4000.0);

    rp_GenOutEnable(RP_CH_1);
	printf ("rp_GenOutEnable\n");
	//getchar();
    //rp_GenOutEnable(RP_CH_2);
    rp_GenTriggerOnly(RP_CH_1);
    //rp_GenTriggerOnly(RP_CH_2);
*/

    /* Releasing resources */
    free(y);
    free(x);
    free(t);
    rp_Release();
}

void generate_signal (float x[], int buff_size)
{
	FILE *f = fopen("gaw.csv", "w+");
	for (int i=0 ; i < buff_size ; i++)
		fprintf (f, "%g\n", x[i]);
	fclose(f);

    rp_GenSynchronise();
    rp_GenWaveform(RP_CH_1, RP_WAVEFORM_ARBITRARY);
    rp_GenArbWaveform(RP_CH_1, x, buff_size);
    rp_GenAmp(RP_CH_1, 0.7);
    rp_GenFreq(RP_CH_1, 4000.0);
    rp_GenOutEnable(RP_CH_1);
	printf ("rp_GenOutEnable\n");
    rp_GenTriggerOnly(RP_CH_1);
}
