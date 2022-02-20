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
	m_strName = "";
	m_dSignalLength = 2e14;
	m_dMaxAmp = 1;
	m_dTau = 1;
}
//-----------------------------------------------------------------------------
void TSignalParams::AssignAll (const TSignalParams &other)
{
	m_strName = other.m_strName;
	m_dSignalLength = other.m_dSignalLength;
	m_dMaxAmp = other.m_dMaxAmp;
	m_dTau = other.m_dTau;
}

//-----------------------------------------------------------------------------

