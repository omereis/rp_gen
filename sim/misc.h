/******************************************************************************\
|                                   misc.h                                     |
\******************************************************************************/
//---------------------------------------------------------------------------

#ifndef miscH
#define miscH
//---------------------------------------------------------------------------
#include <string>
#include "bd_types.h"
#include "jsoncpp/json/json.h"

//---------------------------------------------------------------------------
std::string StringifyJson (const Json::Value &val);
std::string read_file_as_line(const std::string &strFile);
std::string ReadFileAsString (const std::string &strFile);
std::string ToLower (const std::string &str);
bool ReadVectorFromFile (const std::string &strFile, TFloatVec &vDate);
double StrToDouble (const std::string &str, double dDef=0);

string GetParamAsString (const string &strTitle, bool fValue, const string &strUnits="");
string GetParamAsString (const string &strTitle, double dValue, const string &strUnits="");
string GetParamAsString (const string &strTitle, const string &strValue, const string &strUnits="");

bool FileExists (const std::string &strFile);
#endif
