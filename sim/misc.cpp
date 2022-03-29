/******************************************************************************\
|                                  misc.cpp                                    |
\******************************************************************************/
//---------------------------------------------------------------------------

#include "misc.h"
#include "trim.h"

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
//---------------------------------------------------------------------------
