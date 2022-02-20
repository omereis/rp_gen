/*****************************************************************************\
|                              cli_options.cpp                                |
\*****************************************************************************/

#include "cli_options.h"
#include "misc.h"

//-----------------------------------------------------------------------------
TCliOptions::TCliOptions ()
{
	Clear ();
}
//-----------------------------------------------------------------------------
TCliOptions::TCliOptions (const TCliOptions &other)
{
	AssignAll (other);
}
//-----------------------------------------------------------------------------
TCliOptions TCliOptions::operator= (const TCliOptions &other)
{
	AssignAll (other);
	return (*this);
}
//-----------------------------------------------------------------------------
bool TCliOptions::operator== (const TCliOptions &other) const
{
	if (m_paramAlpha != other.m_paramAlpha)
		return (false);
	if (m_paramBeta  != other.m_paramBeta)
		return (false);
	if (m_strOutput  != other.m_strOutput)
		return (false);
	if (m_dPulseRate != other.m_dPulseRate)
		return (false);
	if (m_fShowHelp  != other.m_fShowHelp)
		return (false);
	if (GetSmaplingRate () != other.GetSmaplingRate())
		return (false);
	return (true);
}
//-----------------------------------------------------------------------------
bool TCliOptions::operator!= (const TCliOptions &other) const
{
	return (!(*this == other));
}
//-----------------------------------------------------------------------------
void TCliOptions::Clear ()
{
	m_paramAlpha.Clear ();
	m_paramAlpha.SetName ("Alpha");
	m_paramBeta.Clear ();
	m_paramBeta.SetName ("Beta");
	m_strOutput = "";
	m_dPulseRate = 1e-3;
	m_fShowHelp = false;
	SetSamplingRate (8e-9);
}
//-----------------------------------------------------------------------------
void TCliOptions::AssignAll (const TCliOptions &other)
{
	m_paramAlpha = other.m_paramAlpha;
	m_paramBeta = other.m_paramBeta;
	m_strOutput = other.m_strOutput;
	m_dPulseRate = other.m_dPulseRate;
	m_fShowHelp = other.m_fShowHelp;
	SetSamplingRate (other.GetSmaplingRate());
}
//-----------------------------------------------------------------------------
void TCliOptions::SetShowHelp (bool f)
{
	m_fShowHelp = f;
}
//-----------------------------------------------------------------------------
bool TCliOptions::GetShowHelp ()
{
	return (m_fShowHelp);
}
//-----------------------------------------------------------------------------
void TCliOptions::Print ()
{
	m_paramAlpha.Print ();
	m_paramAlpha.Print ();
	printf ("Output file: %s\n", m_strOutput.c_str());
	printf ("Pulse Rate: %g miliseconds\n", m_dPulseRate * 1e3);
}
//-----------------------------------------------------------------------------
string ExtractFileExtension (string strFile)
{
	string strExt = "";
	int nDot = strFile.rfind(".");

	strFile.length();
	if (nDot >= 0)
		strExt = strFile.substr (nDot + 1, strFile.length() - nDot + 1);
	return (strExt);
	
}
//-----------------------------------------------------------------------------
string ToLower (string strSrc)
{
	string strLower = strSrc;
	
	for (int n=0 ; n < strSrc.length() ; n++)
		strLower[n] = tolower(strSrc[n]);
	return (strLower);
}
//-----------------------------------------------------------------------------
void TCliOptions::LoadFromFile (const char *szFile)
{
	Json::Value root, jAlpha, jBeta;
	Json::Reader reader;
	
	string strFile, strExt = ExtractFileExtension (string (szFile));
	if (strExt.length() == 0)
		strFile = string(szFile) + string(".json");
	else
		strFile = string (szFile);
	printf ("Reading from %s\n", strFile.c_str());
	string strJson = ReadFileAsString (strFile);
	if (reader.parse (strJson, root)) {
		jAlpha = root["Alpha"];
		if (jAlpha.isNull())
			m_paramAlpha.SetEnabled (false);
		else {
			m_paramAlpha.SetEnabled (true);
		}
	}
}
//-----------------------------------------------------------------------------
TSignalParams TCliOptions::GetParmasAlpha() const
{
	return (m_paramAlpha);
}
//-----------------------------------------------------------------------------
TSignalParams TCliOptions::GetParmasbeta() const
{
	return (m_paramBeta);
}
//-----------------------------------------------------------------------------
double TCliOptions::GetSmaplingRate () const
{
	return (m_dSamplingRate);
}
//-----------------------------------------------------------------------------
void TCliOptions::SetSamplingRate (double d)
{
	m_dSamplingRate = d;
}
//-----------------------------------------------------------------------------
bool TCliOptions::Generate()
{
	TFloatVev vSignal;
	return (m_paramAlpha.Generate(vSignal, GetSammplingRate());
}
//-----------------------------------------------------------------------------
string TCliOptions::GetOutFileName () const
{
	return (m_strOutput);
}
//-----------------------------------------------------------------------------
void TCliOptions::SetOutFileName (const string &strFileName)
{
	m_strOutput = strFileName);
}
//-----------------------------------------------------------------------------
void TCliOptions::SaveToFile (const TFloatVec &vAlpha)
{
	FILE *file = fopen (GetOutFileName ());
	if (file != null) {
		TFloatVec cosnt_iterator iFile;
		for (iFile = vAlpha.begin() ; iFile != vAlpha.end() ; iFile++)
			fprintf (file, "%g\n", *iFile);
		fclose (file);
	}
}
//-----------------------------------------------------------------------------


