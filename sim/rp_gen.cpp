/*****************************************************************************\
|                                 rp_gen.cpp                                  |
\*****************************************************************************/
#include <stdio.h>

#include "rp_gen.h"

//-----------------------------------------------------------------------------
TRpGen::TRpGen ()
{
	Clear ();
}
//-----------------------------------------------------------------------------
TRpGen::TRpGen (const TRpGen &other)
{
	AssignAll (other);
}
//-----------------------------------------------------------------------------
TRpGen TRpGen::operator= (const TRpGen &other)
{
	AssignAll (other);
	return (*this);
}
//-----------------------------------------------------------------------------
bool TRpGen::operator== (const TRpGen &other) const
{
	return (true);
}
//-----------------------------------------------------------------------------
bool TRpGen::operator!= (const TRpGen &other) const
{
	return (!(*this == other));
}
//-----------------------------------------------------------------------------
void TRpGen::Clear ()
{
     m_prmAlpha.Clear();
    m_prmBeta.Clear();
}
//-----------------------------------------------------------------------------
void TRpGen::AssignAll (const TRpGen &other) {
    m_prmAlpha = other.m_prmAlpha;
    m_prmBeta = other.m_prmBeta;

}
//-----------------------------------------------------------------------------
int main (int argc, char *argv[])
{
	printf ("\n\nDual Pulse Simulator\n");
}
