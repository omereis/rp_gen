/*****************************************************************************\
|                              cli_options.cpp                                |
\*****************************************************************************/

#include "cli_options.h"

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
	m_paramBeta.Clear ();
	m_strOutput = "";
	m_dPulseRate = 1e-3;
}
//-----------------------------------------------------------------------------
void TCliOptions::AssignAll (const TCliOptions &other)
{
	m_paramAlpha = other.m_paramAlpha;
	m_paramBeta = other.m_paramBeta;
	m_strOutput = other.m_strOutput;
	m_dPulseRate = other.m_dPulseRate;
}
//-----------------------------------------------------------------------------
