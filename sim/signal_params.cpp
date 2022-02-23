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
}
//-----------------------------------------------------------------------------
void TSignalParams::Print ()
{
	printf ("Signal %s\n", GetName ().c_str());
	if (GetEnabled()) {
		printf ("AmplitudeMax: %g\n", GetAmplitudeMax());
		printf ("Pulse Time: %g micro seconds\n", 5.0 * GetTau() * 1e6);
	}
	else
		printf ("Disabled\n");
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

	try {
		vSignal.clear ();
		vSignal.push_back(0);
		double d, t, dTau = GetTau();
		double dAmp, dAmpMax = GetAmplitudeMax(), dAmpMin = GetAmplitudeMin(), r = (double) rand();
		dAmp = (dAmpMax - dAmpMin) * r / RAND_MAX + dAmpMin;
		for (t=dt ; t < dSignalTime ; t += dt) {
			d = dAmp * exp (-t / dTau);
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
bool TSignalParams::LoadFromJson(Json::Value jAlpha)
{
	try {
		if (jAlpha.isNull())
			SetEnabled (false);
		else {
			Json::Value jTau = jAlpha["length_max"];
			SetTau (StrToDouble(jAlpha["length_max"].asString()));
			SetAmplitudeMax (StrToDouble(jAlpha["AmpMax"].asString()));
			SetAmplitudeMin (StrToDouble(jAlpha["AmpMin"].asString()));
			SetEnabled (true);
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

