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

static const char *g_szOptions = "hi:o:rsp"; //-----------------------------------------------------------------------------
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
					if (options.Generate (vBuffer))
						printf ("File '%s' Generated\n", options.GetOutFileName ().c_str());
			}
			else if (strCommand == "o") {
				//printf ("Enter output file name ");
				string strFile = ReadCommand("Enter output file name ");
				options.SetOutFileName (strFile);
				options.PrintParams ();
			}
			else if (strCommand == "u") {
				strCommand = ReadCommand("Parameters JSON file name ");
				options.LoadFromFile (strCommand);
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
			params.SignalSetupFromFile (strCommand, strSignal);
		}
		else if (strCommand == "max") {
			if (ReadDouble (dValue))
				params.SetAmplitudeMin (dValue);
		}
		else if (strCommand == "q")
			fCont = false;
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
void StartGenerator (const TFloatVec &vBuffer)
{

}

//-----------------------------------------------------------------------------
void StopGenerator ()
{

}
