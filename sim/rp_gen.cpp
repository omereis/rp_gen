/*****************************************************************************\
|                                 rp_gen.cpp                                  |
\*****************************************************************************/
#include <stdio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdexcept>
#include <iostream>
#include <getopt.h>
#include <string.h>

#ifdef	_RED_PITAYA
#include "rp.h"
#endif

#include "bd_types.h"
#include "rp_gen.h"
#include "misc.h"
#include "trim.h"

/*
	h - help
	i - input parameters file [.json]
	o - output file [.csv]
	r - start
	p - stop
	
*/
const char *szMenuMain[] = {
	"======================================",
	"q - quit",
	"a - alpha setup",
	"b - beta setup",
	"o - Output File",
	"p - print",
	"g - generate,",
	"d - debug,",
	"u - setup,",
	"start - start",
	"stop - stop",
	"======================================",
	""};

void get_command_line_options (int argc, char *argv[], TCliOptions &options);
void PrintHelp ();
void print_menu (const char *szMenuMain[]);
bool get_signal_params (TSignalParams &, const string &strSignal);
string ReadCommand (const string &strPrompt);
bool ReadDouble (double &dValue);
void StartGenerator (const TFloatVec &vBuffer);
void StopGenerator ();

void generate_signal (float x[], int buff_size);

static const char *g_szOptions = "hi:o:rsp";
void generate_from_file (const char szFile[]);

//-----------------------------------------------------------------------------
void generate_from_file (char szFile[]);

TRpGen::TRpGen ()
{
	Clear ();
}
//-----------------------------------------------------------------------------
TRpGen::TRpGen (const TRpGen &other)
{
	AssignAll (other);
}
//-----------------------------------------------------------------------------
TRpGen TRpGen::operator= (const TRpGen &other)
{
	AssignAll (other);
	return (*this);
}
//-----------------------------------------------------------------------------
bool TRpGen::operator== (const TRpGen &other) const
{
	return (true);
}
//-----------------------------------------------------------------------------
bool TRpGen::operator!= (const TRpGen &other) const
{
	return (!(*this == other));
}
//-----------------------------------------------------------------------------
void TRpGen::Clear ()
{
     m_prmAlpha.Clear();
    m_prmBeta.Clear();
}
//-----------------------------------------------------------------------------
void TRpGen::AssignAll (const TRpGen &other) {
    m_prmAlpha = other.m_prmAlpha;
    m_prmBeta = other.m_prmBeta;

}

//-----------------------------------------------------------------------------
int main (int argc, char *argv[])
{
	TCliOptions options;
	std::string strCommand;
	TSignalParams params;
	bool fCont=true;
	char *szBuf = new char[1024];
	TFloatVec vBuffer;
	
	printf ("\n\nDual Pulse Simulator\n");
	printf ("\tfor help type %s --help\n", argv[0]);
#ifdef	_RED_PITAYA
	if(rp_Init() != RP_OK){
		fprintf(stderr, "Rp api init failed!\n");
		exit (-1);
	}
	else
		printf ("Red Pitaya Initialized.\n");
#endif
	get_command_line_options (argc, argv, options);
	if (options.GetShowHelp())
		PrintHelp ();
	else {
		while (fCont) {
			print_menu (szMenuMain);
			szBuf = fgets(szBuf, 1024, stdin);
			strCommand = ToLower(string(szBuf));
			strCommand = trimString(strCommand);
			if (strCommand == "a") {
				params = options.GetParamsAlpha ();
				if (get_signal_params (params, "alpha"))
					options.SetParamsAlpha(params);
			}
			else if (strCommand == "b") {
				params = options.GetParamsBeta ();
				if (get_signal_params (params, "beta"))
					options.SetParamsBeta(params);
			}
			else if (strCommand == "q") {
				fCont = false;
			}
			else if (strCommand == "p") {
					options.PrintParams ();
			}
			else if (strCommand == "g") {
/*
				generate_from_file ("s.csv");
*/
				if (options.GenerateBuffer (vBuffer))
					printf ("File '%s' Generated\n", options.GetOutFileName ().c_str());
				else
					printf ("\nError generating buffer and file '%s'\n", options.GetOutFileName().c_str());
			}
			else if (strCommand == "d") {
				generate_from_file ("s.csv");
			}
			else if (strCommand == "o") {
				//printf ("Enter output file name ");
				string strFile = ReadCommand("Enter output file name ");
				options.SetOutFileName (strFile);
				options.PrintParams ();
			}
			else if (strCommand == "u") {
				//strCommand = ReadCommand("Parameters JSON file name ");
				if (options.LoadFromFile (ReadCommand("Parameters JSON file name ")))
					options.PrintParams ();
				else
					printf ("Error reading JSON file\n");
			}
			else if (strCommand == "start")
				StartGenerator (vBuffer);
			else if (strCommand == "stop")
				StopGenerator ();
			else
				printf ("unknown command\n");
		}
/*
		TFloatVec vAlpha;
		options.Print ();
		if (options.GetParmasAlpha().GetEnabled ()) {
			options.Generate(vAlpha);
			if (options.GetOutFileName().length() > 0)
				options.SaveToFile (vAlpha);
		}
*/
	}

#ifdef	_RED_PITAYA
	rp_Release();
#endif
	printf ("Bye\n");
	exit(0);
}

const char *szSignalMenu[] = {
		"======================================",
		"on - Enable",
		"off - Disable",
        "max - Amplitude Maximum",
        "min - Amplitude Minimum",
        "lmax - Length Maximum",
        "lmin - Length Minimum",
        "len  - Signal Length",
		"f - read from file",
		"q - quit signal setup",
		"======================================",
		""
		};

//-----------------------------------------------------------------------------
bool get_signal_params (TSignalParams &params, const string &strSignal)
{
	bool fCont=true;
	string strCommand;
	double dValue;

	while (fCont) {
		params.Print();
		print_menu (szSignalMenu);
		strCommand = ReadCommand ("Enter Command");
		if (strCommand == "max") {
			if (ReadDouble (dValue))
				params.SetAmplitudeMax (dValue);
		}
		else if (strCommand == "f") {
			//printf ("Enter file name ");
			strCommand = ReadCommand ("Enter file name ");
			if (!params.SignalSetupFromFile (strCommand, strSignal))
				fprintf (stderr, "Error loading from file:%s", params.GetErrorString().c_str());
		}
		else if (strCommand == "max") {
			if (ReadDouble (dValue))
				params.SetAmplitudeMin (dValue);
		}
		else if (strCommand == "q") {
			fprintf (stderr, "Quit Command\n");
			fCont = false;
		}
		else if (strCommand	== "on")
			params.SetEnabled (true);
		else if (strCommand	== "off")
			params.SetEnabled (false);
	}
	
	return (true);
}

//-----------------------------------------------------------------------------
bool ReadDouble (double &dValue)
{
	char *szBuf = new char[1024];
	double d=0;
	bool fRead;

	szBuf = fgets(szBuf, 1024, stdin);
	try {
		d = atof(szBuf);
		fRead = true;
	}
	catch (std::exception &e) {
		fRead = false;
	}
	delete[] szBuf;
	return (fRead);
}

//-----------------------------------------------------------------------------
string ReadCommand (const string &strPrompt)
{
	char *szBuf = new char[1024];
	string strCommand;
	
	printf ("%s ", strPrompt.c_str());
	szBuf = fgets(szBuf, 1024, stdin);
	strCommand = ToLower(string(szBuf));
	strCommand = trimString(strCommand);
	delete[] szBuf;
	return (strCommand);
}
//-----------------------------------------------------------------------------
void print_menu (const char *szMenuMain[])
{
	int len=1;

	for (int n=0 ; len > 0 ; n++) {
		printf ("%s\n", szMenuMain[n]);
		len = strlen(szMenuMain[n]);
	}
}

//-----------------------------------------------------------------------------
void get_command_line_options (int argc, char *argv[], TCliOptions &options)
{
	int c;
	
	while ((c = getopt(argc, argv, g_szOptions)) != -1) {
		if (c == 'h') {
			options.SetShowHelp (true);
			return;
		}
		if (c == 'i')
			options.LoadFromFile (optarg);
		if (c == 'o')
			options.SetOutFileName (optarg);
	}
}

//-----------------------------------------------------------------------------
void PrintHelp ()
{
	printf ("h - help\n");
	printf ("i - input parameters file [.json]\n");
	printf ("o - output file [.csv]\n");
	printf ("r - start\n");
	printf ("p - stop\n");
}

//-----------------------------------------------------------------------------
bool CopyFPGA ()
{
	bool fInit;

	try {
		printf ("Copying fpga file...");
		system ("cat /opt/redpitaya/fpga/fpga_0.94.bit > /dev/xdevcfg");
		printf ("...Copied\n");
		fInit = true;
	}
	catch (exception &e) {
		printf ("Runtime error\n%s", e.what());
		fInit = false;
	}
	return (fInit);
}
//-----------------------------------------------------------------------------
void StartGenerator (const TFloatVec &vBuffer)
{
#ifdef	_RED_PITAYA
	if (vBuffer.size() == 0) {
		printf ("no buffer to generate.\nAborting\n");
		return;
	}
	if (CopyFPGA ()) {
/*
		if(rp_Init() != RP_OK){
			fprintf(stderr, "Rp api init failed!\n");
		}
*/
		if (true) {
		//else {
			//fprintf(stderr, "RP init OK!\n");
			float *afBuffer=NULL;

			try {
				afBuffer = new float[vBuffer.size()];
				TFloatVec::const_iterator i;
				int n;
				for (i=vBuffer.begin(), n=0 ; (i != vBuffer.end()) && (n < 1000) ; i++, n++)
					afBuffer[n] = *i;
				generate_signal (afBuffer, 1000);
				return;
				printf("Buffer assigned %d items\n", n);
				rp_GenArbWaveform(RP_CH_1, afBuffer, vBuffer.size());
				printf ("rp_gen.cpp:346, rp_GenArbWaveform called\n");
				rp_GenWaveform(RP_CH_1, RP_WAVEFORM_ARBITRARY);
				if (rp_GenAmp(RP_CH_1, 1.0) != RP_OK)
					fprintf (stderr, "Error\n");
				if (rp_GenFreq(RP_CH_1, 100.0) != RP_OK)
					fprintf (stderr, "Error\n");
				if (rp_GenOutEnable(RP_CH_1) != RP_OK)
					fprintf (stderr, "Error\n");
				printf ("Buffer copied to generator: %d items\n", vBuffer.size());
				//rp_Release();
			}
			catch (std::exception &e) {
				fprintf (stderr, "Runtime error in StartGenerator:\n%s\n", e.what());
			}
			if (afBuffer != NULL)
				delete[] afBuffer;

		}
	}
#endif
}

//-----------------------------------------------------------------------------
void StopGenerator ()
{
#ifdef	_RED_PITAYA
/*
	if(rp_Init() != RP_OK){
		fprintf(stderr, "Rp api init failed!\n");
	}
	else {
*/
		fprintf(stderr, "RP init OK!\n");
		if (rp_GenOutDisable(RP_CH_1) != RP_OK)
			fprintf (stderr, "Error\n");
		//rp_Release();
//}
#endif
}

#define M_PI 3.14159265358979323846
#include <math.h>

//-----------------------------------------------------------------------------
void generate_from_file (const char szFile[])
{
	TFloatVec v;
	TFloatVec::iterator iter;
	char *szBuf = new char[128];
	FILE *file = fopen (szFile, "r");
    int buff_size = 1000;
    //int buff_size = 16384;
	int n;

	while (fgets (szBuf, 128, file) != NULL) {
		float fVal = (float) atof(szBuf);
		v.push_back (fVal);
	}
    float *t = new float[buff_size];//(float *)malloc(buff_size * sizeof(float));
    float *x = new float[buff_size];//(float *)malloc(buff_size * sizeof(float));
    for(n = 1; n < buff_size; n++)
        t[n] = (2 * M_PI) / buff_size * n;
    for (n = 0; n < buff_size; n++){
        x[n] = sin(t[n]) + ((1.0/3.0) * sin(t[n] * 3));
        //y[i] = (1.0/2.0) * sin(t[i]) + (1.0/4.0) * sin(t[i] * 4);
    }
	delete[] t;
	delete x;
	x = new float[v.size()];
	//fclose (file);
	//float *af = new float[v.size()];
	for (n=0, iter=v.begin() ; n < v.size() ; n++, iter++)
		x[n] = *iter;
	FILE *fout = fopen ("s_out.csv", "w+");
	for (iter=v.begin(), n=0 ; iter != v.end() ; iter++, n++)
		fprintf (fout, "%g,%g\n", x[n],*iter);
	fclose (fout);
	int nSize = (int) v.size();
	printf ("Generating %d items, \nbuff_size=%d\n", nSize, buff_size);
	generate_signal (x, 10000);//nSize);
	//generate_signal (x, (int) v.size());
	//generate_signal (x, buff_size);
	//generate_signal (af, (int) v.size());
	delete szBuf;
	delete x;
	//delete af;
}

//-----------------------------------------------------------------------------
void generate_signal (float x[], int buff_size)
{
	FILE *f = fopen("gaw.csv", "w+");
	for (int i=0 ; i < buff_size ; i++)
		fprintf (f, "%g\n", x[i]);
	fclose(f);
	int nRet;

#ifdef	_RED_PITAYA
    nRet = rp_GenSynchronise();
	printf ("rp_GenSynchronise, nRet=%d\n", nRet);
	//getchar();

    nRet = rp_GenWaveform(RP_CH_1, RP_WAVEFORM_ARBITRARY);
	printf ("GenWaveform, nRet=%d\n", nRet);
	//getchar();

    nRet = rp_GenArbWaveform(RP_CH_1, x, buff_size);
	printf ("rp_GenArbWaveform, nRet=%d\n", nRet);
	//getchar();

    nRet = rp_GenAmp(RP_CH_1, 1.0);
	printf ("rp_GenAmp, nRet=%d\n", nRet);
	//getchar();

    nRet = rp_GenFreq(RP_CH_1, 1000.0);
	//printf ("rp_GenFreq, nRet=%d\n", nRet);
	//getchar();

    nRet = rp_GenOutEnable(RP_CH_1);
	printf ("rp_GenOutEnable, nRet=%d\n", nRet);
	//getchar();

    nRet = rp_GenTriggerOnly(RP_CH_1);
	printf ("rp_GenTriggerOnly, nRet=%d\n", nRet);
	//getchar();
#endif

}
