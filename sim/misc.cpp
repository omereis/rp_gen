/******************************************************************************\
|                                  misc.cpp                                    |
\******************************************************************************/
//---------------------------------------------------------------------------

#include "misc.h"
#include "trim.h"

#include <stdio.h>
#include <math.h>
using namespace std;

//-----------------------------------------------------------------------------

std::string StringifyJson (const Json::Value &val)
{
	std::string strJson;
	Json::FastWriter fastWriter;
	
	strJson = fastWriter.write(val);
	return (strJson);
}
//-----------------------------------------------------------------------------

std::string read_file_as_line (const std::string &strFile)
{
	FILE *file=NULL;
	char *szLine, szBuf[1024];
	TStringVec vstr;
	TStringVec::iterator i;
	string strLine;

	try {
		file = fopen (strFile.c_str(), "r");
		while ((szLine = fgets (szBuf, 1024, file)) != NULL) {
			strLine = string(szLine);
			strLine = trimString(strLine);
			if (strLine.length() > 0)
				vstr.push_back (strLine);
		}
        strLine = "";
        for (i=vstr.begin() ; i != vstr.end() ; i++)
            strLine += trimString (*i);
		fclose (file);
	}
	catch (std::exception &exp) {
		fprintf (stderr, "Runtime error in ReadJson:\n%s\n", exp.what());
        if (file != NULL)
		    fclose (file);
        strLine = "";
	}
    return (strLine);
}
//-----------------------------------------------------------------------------

std::string ReadFileAsString (const std::string &strFile)
{
	FILE *file=NULL;
	char *szLine, szBuf[1024];
	TStringVec vstr;
	TStringVec::iterator i;
	string strLine;

	try {
		file = fopen (strFile.c_str(), "r");
		while ((szLine = fgets (szBuf, 1024, file)) != NULL) {
			strLine = string(szLine);
			strLine = trimString(strLine);
			if (strLine.length() > 0)
				vstr.push_back (strLine);
		}
        strLine = "";
        for (i=vstr.begin() ; i != vstr.end() ; i++)
            strLine += trimString (*i);
		fclose (file);
	}
	catch (std::exception &exp) {
		fprintf (stderr, "Runtime error in ReadJson:\n%s\n", exp.what());
        if (file != NULL)
		    fclose (file);
        strLine = "";
	}
    return (strLine);
}
//-----------------------------------------------------------------------------

string ToLower (const std::string &str)
{
	string strLower;

	for (int n=0 ; n < str.size() ; n++)
		strLower += tolower(str[n]);
	return (strLower);
}
//-----------------------------------------------------------------------------

bool ReadVectorFromFile (const std::string &strFile, TFloatVec &vDate)
{
	bool fRead;

	try {
		vDate.clear();
		char *szLine, szBuf[1024];
		FILE *file = fopen (strFile.c_str(), "r");
		if (file != NULL) {
			while ((szLine = fgets(szBuf, 1024, file)) != NULL) {
				float r = (float) atof (szLine);
				vDate.push_back (r);
			}
			fRead = true;
		}
		else {
			fprintf (stderr, "Could not open file %s\n", strFile.c_str());
			fRead = false;
		}
	}
	catch (std::exception &exp) {
		fprintf (stderr, "Runtime error in 'ReadVectorFromFile':\n%s\n", exp.what());
		fRead = false;
	}
	return (fRead);
}
//-----------------------------------------------------------------------------

double StrToDouble (const std::string &str, double dDef)
{
	double dValue;

	try {
		dValue = atof(str.c_str());
	}
	catch (std::exception &exp) {
		dValue = dDef;
	}
	return (dValue);
}

//-----------------------------------------------------------------------------
string GetParamAsString (const string &strTitle, bool fValue, const string &strUnits)
{
	string strValue = (fValue ? "True" : "False");

	return (GetParamAsString (strTitle, strValue, strUnits));
}

//-----------------------------------------------------------------------------
string GetParamAsString (const string &strTitle, double dValue, const string &strUnits)
{
	return (GetParamAsString (strTitle, std::to_string(dValue), strUnits));
}

//-----------------------------------------------------------------------------
string GetParamAsString (const string &strTitle, const string &strValue, const string &strUnits)
{
	char *szBuf = new char [strTitle.length() + 50];
	sprintf (szBuf, "\n%s - %s", strTitle.c_str(), strValue.c_str());
	string strParam = string(szBuf);
	if (strUnits.length() > 0)
		strParam += " [" + strUnits + "]";
	delete[] szBuf;
	return (strParam);
}

//-----------------------------------------------------------------------------
bool FileExists (const std::string &strFile)
{
	bool fExists;
	FILE *file = NULL;

	try {
		file = fopen(strFile.c_str(), "r");
		fExists = (file != NULL ? true : false);
	}
	catch (std::exception &e) {
		fExists = false;
	}
	if (file != NULL)
		fclose (file);
	return (fExists);
}

//-----------------------------------------------------------------------------
double VectorAverage (const TFloatVec &v)
{
	TFloatVec::const_iterator i;
	double dSum=0, dAverage=0;

	if (v.size() > 0) {
		for (i=v.begin() ; i != v.end() ; i++)
			dSum += (double) *i;
		dAverage = dSum / (double) v.size();
	}
	return (dAverage);
}

//-----------------------------------------------------------------------------
double VectorVariance (const TFloatVec &v)
{
	return (VectorVariance (v, VectorAverage (v)));
}

//-----------------------------------------------------------------------------
double VectorVariance (const TFloatVec &v, double dAverage)
{
	TFloatVec::const_iterator i;
	double dVar=0, dSum=0;

	if (v.size()  > 0) {
		for (i=v.begin() ; i != v.end() ; i++) {
			dSum += (pow(*i - dAverage, 2));
		}
		dVar = dSum / (double) v.size();
	}
	return (dVar);
}

//---------------------------------------------------------------------------
void PrintVector (const TFloatVec &v, const std::string &str)
{
	FILE *file;
	TFloatVec::const_iterator i;

	try {
		file = fopen (str.c_str(), "w+");
		for (i=v.begin() ; i != v.end() ; i++)
			fprintf (file, "%g\n", *i);
		fclose (file);
	}
	catch (...) {
	}
}

//-----------------------------------------------------------------------------
double VectorMax (const TFloatVec &v)
{
	TFloatVec::const_iterator i;
	double dMax;

	for (i=v.begin() ; i != v.end() ; i++) {
		if (i == v.begin())
			dMax = *i;
		else
			dMax = max (dMax, (double) *i);
	}
	return (dMax);
}

//-----------------------------------------------------------------------------
double VectorMin (const TFloatVec &vec)
{
	TFloatVec::const_iterator i;
	double dMin;

	for (i=vec.begin() ; i != vec.end() ; i++) {
		if (i == vec.begin())
			dMin = *i;
		else
			dMin = min (dMin, (double) *i);
	}
	return (dMin);
}

//-----------------------------------------------------------------------------
void  VectorAddConst (TFloatVec &vec, double d)
{
	TFloatVec::iterator i;

	for (i=vec.begin() ; i != vec.end() ; i++)
		*i += (float) d;
}

//-----------------------------------------------------------------------------
void  VectorMultiplyConst (TFloatVec &vec, double d)
{
	TFloatVec::iterator i;

	for (i=vec.begin() ; i != vec.end() ; i++)
		*i *= (float) d;
}
//-----------------------------------------------------------------------------
void NormalizeVector (TFloatVec &vec)
{
	TFloatVec::iterator i;
	double dAverage, dVar, dMin, dMax;

	dMin = VectorMin (vec);
	VectorAddConst (vec, -dMin);
	dMax = VectorMax (vec);
	VectorMultiplyConst (vec, 2.0/dMax);
	VectorAddConst (vec, -1);
}

//-----------------------------------------------------------------------------
void RandomVector (TFloatVec &vNoise, size_t s)
{
	TFloatVec::iterator i;

	if (s > 0) {
		vNoise.resize(s);
		for (i=vNoise.begin() ; i != vNoise.end() ; i++)
			*i = rand();
	}
}

//-----------------------------------------------------------------------------
bool print_vector (TFloatVec &vBuffer, const char *szFileName)
{
	bool fPrint = false;
	TFloatVec::iterator i;

	try {
		FILE *file = fopen (szFileName, "w+");
		if (file != NULL) {
			for (i=vBuffer.begin() ; i != vBuffer.end() ; i++)
				fprintf (file, "%g\n", *i);
			fclose (file);
			fPrint = true;
		}
	}
	catch (std::exception &std) {
		fprintf (stderr, "Runtime error in print_vector:\n%s\n", std.what());
	}
	return (fPrint);
}
//---------------------------------------------------------------------------
