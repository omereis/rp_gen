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

double VectorAverage (const TFloatVec &v);
double VectorVariance (const TFloatVec &v);
double VectorVariance (const TFloatVec &v, double dAverage);

void PrintVector (const TFloatVec &v, const std::string &str);
double VectorMax (const TFloatVec &v);
double VectorMin (const TFloatVec &vec);
void  VectorAddConst (TFloatVec &vec, double d);
void  VectorMultiplyConst (TFloatVec &vec, double d);
void RandomVector (TFloatVec &vNoise, size_t s);
void NormalizeVector (TFloatVec &vec);

bool print_vector (TFloatVec &vBuffer, const char *szFile);
#endif
