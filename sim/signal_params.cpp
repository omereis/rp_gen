/******************************************************************************\
|                              SignalParams.cpp                                |
\******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "misc.h"
#include "signal_params.h"

//-----------------------------------------------------------------------------
TSignalParams::TSignalParams ()
{
	Clear ();
}
//-----------------------------------------------------------------------------
TSignalParams::TSignalParams (const TSignalParams &other)
{
	AssignAll (other);
}
//-----------------------------------------------------------------------------
TSignalParams TSignalParams::operator= (const TSignalParams  &other)
{
	AssignAll (other);
	return (*this);
}
//-----------------------------------------------------------------------------
bool TSignalParams::operator== (const TSignalParams &other) const
{
	return (true);
}
//-----------------------------------------------------------------------------
bool TSignalParams::operator!= (const TSignalParams &other) const
{
	return (!(*this == other));
}
//-----------------------------------------------------------------------------
void TSignalParams::Clear ()
{
	SetName ("");
	SetSignalLength (1e-3);
	m_dTau = 1;
	SetEnabled (false);
	SetAmplitudeMax(0.8);
	SetAmplitudeMin(0.6);
	SetEnabled (false);
	SetTauMax (100e-9);
	SetTauMin (40e-9);
}
//-----------------------------------------------------------------------------
void TSignalParams::AssignAll (const TSignalParams &other)
{
	m_strName = other.m_strName;
	SetSignalLength (other.GetSignalLength());
	SetTau (other.GetTau());
	SetAmplitudeMax(other.GetAmplitudeMax());
	SetAmplitudeMin(other.GetAmplitudeMin());
	SetEnabled (other.GetEnabled());
	SetTauMax (other.GetTauMax());
	SetTauMin (other.GetTauMin());
}

//-----------------------------------------------------------------------------
string TSignalParams::GetAsString ()
{
	string strParams="";

	strParams = GetParamAsString ("Name", GetName());
	strParams += GetParamAsString ("Enabled", GetEnabled());
	strParams += GetParamAsString ("Amplitude Max.", GetAmplitudeMax());
	strParams += GetParamAsString ("Amplitude Min.", GetAmplitudeMin());
	strParams += GetParamAsString ("Length", GetSignalLength());
	strParams += GetParamAsString ("Tau Max.", 1e6 * GetTauMax());
	strParams += GetParamAsString ("Tau Min.", 1e6 * GetTauMin());
	//strParams = GetName ();
	//strParams += "\n" + GetEnabled() ? "Enabled" : "Disabled";
	//strParams += "\nAmplitudeMax: %g\n", GetAmplitudeMax());
		//printf ("Pulse Time: %g micro seconds\n", 5.0 * GetTau() * 1e6);
	return (strParams);
}
//-----------------------------------------------------------------------------
void TSignalParams::Print ()
{
	printf ("%s\n", GetAsString().c_str());
	/*printf ("Signal %s\n", GetName ().c_str());*/
	/*if (GetEnabled()) {*/
		/*printf ("AmplitudeMax: %g\n", GetAmplitudeMax());*/
		/*printf ("Pulse Time: %g micro seconds\n", 5.0 * GetTau() * 1e6);*/
	/*}*/
	/*else*/
		/*printf ("Disabled\n");*/
}
//-----------------------------------------------------------------------------
string TSignalParams::GetName () const
{
	return (m_strName);
}
//-----------------------------------------------------------------------------
void TSignalParams::SetName (const string &str)
{
	m_strName = str;
}
//-----------------------------------------------------------------------------
double TSignalParams::GetAmplitudeMax() const
{
	return (m_dAmpMax);
}
//-----------------------------------------------------------------------------
void TSignalParams::SetAmplitudeMax(double dAmp)
{
	m_dAmpMax = dAmp;
}
//-----------------------------------------------------------------------------
double TSignalParams::GetAmplitudeMin() const
{
	return (m_dAmpMin);
}
//-----------------------------------------------------------------------------
void TSignalParams::SetAmplitudeMin(double dAmp)
{
	m_dAmpMin = dAmp;
}
//-----------------------------------------------------------------------------
double TSignalParams::GetTau() const
{
	return (m_dTau);
}
//-----------------------------------------------------------------------------
void TSignalParams::SetTau(double dTau)
{
	m_dTau = dTau;
}
//-----------------------------------------------------------------------------
void TSignalParams::SetEnabled (bool f)
{
	m_fEnabled = f;
}
//-----------------------------------------------------------------------------
bool TSignalParams::GetEnabled () const
{
	return (m_fEnabled);
}
//-----------------------------------------------------------------------------
bool TSignalParams::Generate(TFloatVec &vSignal, double dt, double dSignalTime)
{
	bool fGen;
	double dExp;

	try {
		vSignal.clear ();
		vSignal.push_back(0);
		double d, t, dTau = GetTauMin();
		double dAmp, dAmpMax = GetAmplitudeMax(), dAmpMin = GetAmplitudeMin(), r = (double) rand();
		/*dAmp = () (dAmpMax - dAmpMin) * r / RAND_MAX + dAmpMin; */
		dAmp = (GetAmplitudeMax() + GetAmplitudeMin()) / 2.0;
		for (t=dt ; t < dSignalTime ; t += dt) {
			double dExp = t / dTau;
			d = dAmp * exp (-dExp);
			//d = dAmp * exp (-t / dTau);
			vSignal.push_back (d);
		}
		fGen = true;
	}
	catch (std::exception exp) {
		fprintf (stderr, "%s\n", exp.what());
		fGen = false;
	}
	return (fGen);
}
//-----------------------------------------------------------------------------
void TSignalParams::SetSignalLength (double dLength)
{
	m_dSignalLength = dLength;
}
//-----------------------------------------------------------------------------
double TSignalParams::GetSignalLength () const
{
	return (m_dSignalLength);
}

//-----------------------------------------------------------------------------
bool TSignalParams::SignalSetupFromFile (std::string &strFile, const string &strSignal)
{
	Json::Value root;
	Json::Reader reader;
	bool fLoad = false;

	if (FileExists (strFile)) {
		string strContent = ReadFileAsString (strFile);
		if (reader.parse (strContent, root))
			fLoad = LoadFromJson (root[strSignal], strSignal);
	}
	return (fLoad);
}

//-----------------------------------------------------------------------------
bool TSignalParams::LoadFromJson(Json::Value jSignal, const string &strName)
{
	try {
		if (jSignal.isNull())
			SetEnabled (false);
		else {
			//Json::Value jTau = jAlpha["length_max"];
			SetName (strName);
			//SetTau (StrToDouble(jSignal["length_max"].asString()));
			//SetTauMax (StrToDouble(jSignal["length_max"].asString()));
			//SetTauMin (StrToDouble(jSignal["length_min"].asString()));
			SetAmplitudeMax (StrToDouble(jSignal["AmpMax"].asString()));
			SetAmplitudeMin (StrToDouble(jSignal["AmpMin"].asString()));
			SetEnabled (true);
			SetTauMin (jSignal["tau_min"].asDouble());
			SetTauMax (jSignal["tau_max"].asDouble());
			SetEnabled (jSignal["enabled"].asBool());
		}
	}
	catch (std::exception &exp) {
		SetEnabled (false);
		fprintf (stderr, "Runtime error in TSignalParams::LoadFromJsonn\n%s\n", exp.what());
	}
	return (GetEnabled ());
}
//-----------------------------------------------------------------------------
double TSignalParams::GetTauMin () const
{
	return (m_dTauMin);
}
//-----------------------------------------------------------------------------
void TSignalParams::SetTauMin (double dTau)
{
	m_dTauMin = dTau;
}
//-----------------------------------------------------------------------------
double TSignalParams::GetTauMax () const
{
	return (m_dTauMax);
}
//-----------------------------------------------------------------------------
void TSignalParams::SetTauMax (double dTau)
{
	m_dTauMax = dTau;
}
//-----------------------------------------------------------------------------

