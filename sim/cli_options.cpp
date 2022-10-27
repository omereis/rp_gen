/*****************************************************************************\
|                              cli_options.cpp                                |
\*****************************************************************************/

#include "cli_options.h"
#include "misc.h"

#include <sys/param.h>
#include <stdlib.h>
#include <math.h>

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
	SetNoise (0);
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
	SetNoise (other.GetNoise());
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
	printf ("Buffer Size: %d\n", GetBufferSize());
	printf ("Noise: %g\n", GetNoise());
}
//-----------------------------------------------------------------------------
void TCliOptions::Print ()
{
	m_paramAlpha.Print ();
	m_paramAlpha.Print ();
	printf ("Output file: %s\n", m_strOutput.c_str());
	printf ("Pulse Rate: %g miliseconds\n", m_dPulseRate * 1e3);
	printf ("Noise: %g\n", GetNoise());
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
bool TCliOptions::LoadFromFile (const std::string &strFile)
{
	return (LoadFromFile (strFile.c_str()));
}

//-----------------------------------------------------------------------------
bool TCliOptions::LoadFromFile (const char *szFile)
{
	Json::Value root, jAlpha, jBeta;
	Json::Reader reader;
	bool fLoad = false;
	
	string strTau, strFile, strExt = ExtractFileExtension (string (szFile));
	if (strExt.length() == 0)
		strFile = string(szFile) + string(".json");
	else
		strFile = string (szFile);
	try {
		if (FileExists (strFile)) {
			printf ("Reading from %s\n", strFile.c_str());
			string strJson = ReadFileAsString (strFile);
			if (reader.parse (strJson, root)) {
				m_paramAlpha.LoadFromJson(root["alpha"], "Alpha");
				m_paramBeta.LoadFromJson(root["beta"], "Beta");
				strFile += "";
				SetPulseRate (root["pulse_rate"].asDouble());
				SetBufferSize (root["buffer_size"].asInt());
				SetOutFileName (root["out_file"].asString());
				SetNoise (root["noise"].asDouble());
				fLoad = true;
			}
		}
		else
			printf ("File '%s' does not exists\n", strFile.c_str());
	}
	catch (std::exception &e) {
		fprintf (stderr, "%s\n", e.what());
	}
	return (fLoad);
}

//-----------------------------------------------------------------------------
TSignalParams TCliOptions::GetParamsAlpha() const
{
	return (m_paramAlpha);
}

//-----------------------------------------------------------------------------
TSignalParams TCliOptions::GetParamsBeta() const
{
	return (m_paramBeta);
}

//-----------------------------------------------------------------------------
void TCliOptions::SetParamsAlpha(const TSignalParams &paramsAlpha)
{
	m_paramAlpha = paramsAlpha;
}

//-----------------------------------------------------------------------------
void TCliOptions::SetParamsBeta(const TSignalParams &paramsBeta)
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
bool TCliOptions::GenerateBuffer(TFloatVec &vBuffer)
{
	bool f;
	TFloatVec vSignal;
	TFloatVec::iterator iSignal;
	size_t sz=0, szBuffer = GetBufferSize();

	for (f=true ; (f == true) && (sz < GetBufferSize()) ; ) {
		vSignal.clear();
		Generate(vSignal);
		vBuffer.insert (vBuffer.end(), vSignal.begin(), vSignal.end());
		sz = vBuffer.size();
	}
	if (GetNoise() > 0)
		AddNoise (vBuffer, GetNoise());
	if (vBuffer.size() > 0)
		f = SaveSignal (vBuffer, GetOutFileName ());
	return (f);
}

//-----------------------------------------------------------------------------
bool TCliOptions::Generate(TFloatVec &vSignal)
{
	bool fGen;

	try {
		TFloatVec vAlpha, vBeta;

		if (m_paramAlpha.GetEnabled()) {
			m_paramAlpha.Generate(vAlpha, GetSamplingRate(), GetSignalLength());
			while (vAlpha.size() * 8e-9 < GetSignalLength())
				vSignal.push_back (0);
		}
		if (m_paramBeta.GetEnabled()) {
			m_paramBeta.Generate(vBeta, GetSamplingRate(), GetSignalLength());
			while (vBeta.size() * 8e-9 < GetSignalLength())
				vSignal.push_back (0);
		}
		if (vAlpha.size() > 0)
			vSignal.insert(vSignal.begin(), vAlpha.begin(), vAlpha.end());
		if (vBeta.size() > 0)
			vSignal.insert(vSignal.begin(), vBeta.begin(), vBeta.end());
		fGen = true;
	}
	catch (std::exception &exp) {
		fGen = false;
		fprintf (stderr, "Runtime err in 'TCliOptions::Generate':\n%s\n", exp.what());
	}
	return (fGen);
}

//-----------------------------------------------------------------------------
bool TCliOptions::SaveSignal (const TFloatVec &vSignal, const string &strFileName)
{
	bool fSave = false;
	TFloatVec::const_iterator i;
	string strFile(strFileName);
	if (strFile.length() == 0)
		strFile = SetDefaultOutputName ();
	FILE *file = fopen (strFile.c_str(), "w+");

	if (file != NULL) {
		for (i=vSignal.begin() ; i != vSignal.end() ; i++)
			fprintf (file, "%g\n", *i);
		fclose (file);
		fSave = true;
	}
	return (fSave);
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
string TCliOptions::SetDefaultOutputName ()
{
	SetOutFileName ("output.csv");
	return (GetOutFileName ());

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

//-----------------------------------------------------------------------------
void TCliOptions::SetNoise (double dNoise)
{
	m_dNoise = dNoise;
}

//-----------------------------------------------------------------------------
double TCliOptions::GetNoise () const
{
	return (m_dNoise);
}
//-----------------------------------------------------------------------------
void TCliOptions::AddNoise (TFloatVec &vSignal, double dNoise)
{
	TFloatVec::iterator i, iSignal;
	TFloatVec vNoise;
	double dMax, dAverage;

	if ((vSignal.size() > 0) && (dNoise > 0)) {
		RandomVector (vNoise, vSignal.size());
		NormalizeVector (vNoise);
		dMax = VectorMax (vSignal);
		VectorMultiplyConst (vNoise, dMax * dNoise / 100.0);
		//for (i=vNoise.begin() ; i != vNoise.end() ; i++)
			//*i = (*i) * dNoise;
		PrintVector (vSignal, "signal.csv");
		PrintVector (vNoise, "noise.csv");
		for (i=vNoise.begin(), iSignal=vSignal.begin() ; (i != vNoise.end()) && (iSignal != vSignal.end()) ; i++, iSignal++)
			*iSignal = *iSignal + *i;
		PrintVector (vNoise, "sn.csv");
/*
		vNoise.resize(vSignal.size());
		for (i=vNoise.begin() ; i != vNoise.end() ; i++) {
			*i = rand();
		}
		for (i=vNoise.begin() ; i != vNoise.end() ; i++)
			*i = (*i / dMax);
		PrintVector (vNoise, "noise_n.csv");
		dAverage = VectorAverage (vNoise);
		for (i=vNoise.begin() ; i != vNoise.end() ; i++)
			*i -= dAverage;
		PrintVector (vNoise, "noise_z.csv");
		double dVariance = VectorVariance (vNoise);
		dVariance = sqrt(dVariance);
		for (i=vNoise.begin() ; i != vNoise.end() ; i++)
			*i /= dVariance;
		PrintVector (vNoise, "noise_norm.csv");
		printf ("Variance: %g\n", dVariance);
		//for (i=vNoise.begin() ; i != vNoise.end() ; i++)
			//*i /= dMax;
		//PrintVector (vSignal, "signal.csv");
		PrintVector (vNoise, "noise.csv");
*/
	}
}

