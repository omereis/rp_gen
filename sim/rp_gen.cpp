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


#include "bd_types.h"
#include "rp_gen.h"
/*
	h - help
	i - input parameters file [.json]
	o - output file [.csv]
	r - start
	p - stop
	
*/
void get_command_line_options (int argc, char *argv[], TCliOptions &options);
void PrintHelp ();

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
	
	printf ("\n\nDual Pulse Simulator\n");
	printf ("\tfor help type %s --help\n", argv[0]);
	get_command_line_options (argc, argv, options);
	if (options.GetShowHelp())
		PrintHelp ();
	else {
		TFloatVec vAlpha;
		options.Print ();
		if (options.GetParmasAlpha().GetEnabled ()) {
			options.Generate(vAlpha);
			if (options.GetOutFileName().length() > 0)
				options.SaveToFile (vAlpha);
		}
	}
	printf ("Bye\n");
	exit(0);
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
