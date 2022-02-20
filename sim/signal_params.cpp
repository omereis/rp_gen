/******************************************************************************\
|                              SignalParams.cpp                                |
\******************************************************************************/
#include <stdio.h>
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
	m_dSignalLength = 2e14;
	m_dTau = 1;
	SetEnabled (false);
	SetAmplitudeMax(0.8);
	SetAmplitudeMin(0.6);
}
//-----------------------------------------------------------------------------
void TSignalParams::AssignAll (const TSignalParams &other)
{
	m_strName = other.m_strName;
	m_dSignalLength = other.m_dSignalLength;
	m_dTau = other.m_dTau;
	SetAmplitudeMax(other.GetAmplitudeMax());
	SetAmplitudeMin(other.GetAmplitudeMin);
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
bool TSignalParams::Generate(TFloatVev &vSignal, double dt)
{
	vSignal.clear ();
	vSignal.push_back(0);
	vSignal.push_back(GetAmplitudeMax());
	double t;
}
//-----------------------------------------------------------------------------

