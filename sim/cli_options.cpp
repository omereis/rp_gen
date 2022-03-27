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
	if (GetPulseRate () != other.GetPulseRate ())
		return (false);
	if (m_dPulseRate != other.m_dPulseRate)
		return (false);
	if (m_fShowHelp  != other.m_fShowHelp)
		return (false);
	if (GetSmaplingRate () != other.GetSmaplingRate())
		return (false);
	if (GetSignalLength () != other.GetSignalLength ())
		return (false);
	if (GetBufferSize() != other.GetBufferSize())
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
	SetPulseRate (1e-3);
	m_fShowHelp = false;
	SetSamplingRate (8e-9);
	SetSignalLength (1e-6);
	SetBufferSize(16384);
}
//-----------------------------------------------------------------------------
void TCliOptions::AssignAll (const TCliOptions &other)
{
	m_paramAlpha = other.m_paramAlpha;
	m_paramBeta = other.m_paramBeta;
	m_strOutput = other.m_strOutput;
	m_fShowHelp = other.m_fShowHelp;
	SetSamplingRate (other.GetSmaplingRate());
	SetSignalLength (other.GetSignalLength ());
	SetPulseRate (other.GetPulseRate ());
	SetBufferSize(other.GetBufferSize());
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
void TCliOptions::PrintParams ()
{
	string strAlpha = m_paramAlpha.GetAsString ();
	string strBeta = m_paramBeta.GetAsString ();
	printf ("%s\n", strAlpha.c_str());
	printf ("%s\n", strBeta.c_str());
	printf ("Output file: %s\n", m_strOutput.c_str());
	printf ("Pulse Rate: %g miliseconds\n", m_dPulseRate * 1e3);
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
	
	string strTau, strFile, strExt = ExtractFileExtension (string (szFile));
	if (strExt.length() == 0)
		strFile = string(szFile) + string(".json");
	else
		strFile = string (szFile);
	printf ("Reading from %s\n", strFile.c_str());
	string strJson = ReadFileAsString (strFile);
	if (reader.parse (strJson, root)) {
		m_paramAlpha.LoadFromJson(root["alpha"]);
		m_paramBeta.LoadFromJson(root["beta"]);
		strFile += "";
		SetPulseRate (root["pulse_rate"].asDouble());
		SetBufferSize (root["buffer_size"].asInt());
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
void TCliOptions::SetParmasAlpha(const TSignalParams &paramsAlpha)
{
	m_paramAlpha = paramsAlpha;
}

//-----------------------------------------------------------------------------
void TCliOptions::SetParmasBeta(const TSignalParams &paramsBeta)
{
	m_paramBeta = paramsBeta;
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
	bool f = false;

	TFloatVec vSignal;
	if (Generate(vSignal))
		f = SaveSignal (vSignal, GetOutFileName ());
	return (f);
}

//-----------------------------------------------------------------------------
bool TCliOptions::SaveSignal (const TFloatVec &vSignal, const string &strFileName)
{
	bool fSave = false;
	TFloatVec::const_iterator i;
	FILE *file = fopen (strFileName.c_str(), "w+");

	if (file != NULL) {
		for (i=vSignal.begin() ; i != vSignal.end() ; i++)
			fprintf (file, "%g\n", *i);
		fclose (file);
		fSave = true;
	}
	return (fSave);
}
//-----------------------------------------------------------------------------
bool TCliOptions::Generate(TFloatVec &vSignal)
{
	bool fGen;

	try {
		TFloatVec vPulse;

		if (m_paramAlpha.GetEnabled())
			m_paramAlpha.Generate(vSignal, GetSamplingRate(), GetSignalLength());
		if (m_paramBeta.GetEnabled())
			m_paramAlpha.Generate(vPulse, GetSamplingRate(), GetSignalLength());
		vSignal.insert(vSignal.begin(), vPulse.begin(), vPulse.end());
		fGen = true;
	}
	catch (std::exception &exp) {
		fGen = false;
		fprintf (stderr, "Runtime err in 'TCliOptions::Generate':\n%s\n", exp.what());
	}
	return (fGen);
}
//-----------------------------------------------------------------------------
void TCliOptions::GetSamplingRate(double dRate)
{
	m_dSamplingRate = dRate;
}
//-----------------------------------------------------------------------------
double TCliOptions::GetSamplingRate()
{
	return (m_dSamplingRate);
}
//-----------------------------------------------------------------------------
string TCliOptions::GetOutFileName () const
{
	return (m_strOutput);
}
//-----------------------------------------------------------------------------
void TCliOptions::SetOutFileName (const string &strFileName)
{
	m_strOutput = strFileName;
}
//-----------------------------------------------------------------------------
void TCliOptions::SaveToFile (const TFloatVec &vAlpha)
{
	FILE *file = fopen (GetOutFileName ().c_str(), "w");
	if (file != NULL) {
		TFloatVec::const_iterator iFile;
		for (iFile = vAlpha.begin() ; iFile != vAlpha.end() ; iFile++)
			fprintf (file, "%g\n", *iFile);
		fclose (file);
	}
}
//-----------------------------------------------------------------------------
void TCliOptions::SetSignalLength (double dSignalLen)
{
	m_dSignalLength = dSignalLen;
}
//-----------------------------------------------------------------------------
double  TCliOptions::GetSignalLength () const
{
	return (m_dSignalLength);
}
//-----------------------------------------------------------------------------
double TCliOptions::GetPulseRate () const
{
	return (m_dPulseRate);
}
//-----------------------------------------------------------------------------
void TCliOptions::SetPulseRate (double dRate)
{
	m_dPulseRate = dRate;
}
//-----------------------------------------------------------------------------
int TCliOptions::GetBufferSize() const
{
	return (m_nBufferSize);
}
//-----------------------------------------------------------------------------
void TCliOptions::SetBufferSize(int nSize)
{
	m_nBufferSize = nSize;
}


