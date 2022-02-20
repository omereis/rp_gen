/******************************************************************************\
|                            signal_params.h                                   |
\******************************************************************************/

#ifndef	SIGNAL_PARAMS_INC
#define	SIGNAL_PARAMS_INC

#include "bd_types.h"

using namespace std;

#include <string>

class TSignalParams {
public:
	TSignalParams ();
	TSignalParams  (const TSignalParams &other);
	TSignalParams operator= (const TSignalParams  &other);
	bool operator== (const TSignalParams &other) const;
	bool operator!= (const TSignalParams &other) const;
	void Clear ();

	void Print ();
	string GetName () const;
	void  SetName (const string &str);
	double GetAmplitudeMax() const;
	void SetAmplitudeMax(double dAmp);
	double GetAmplitudeMin() const;
	void SetAmplitudeMin(double dAmp);
	double GetTau() const;
	void SetTau(double dTau);
	void SetEnabled (bool f);
	bool GetEnabled () const;
protected:
	void AssignAll (const TSignalParams &other);
private:
	string m_strName;
	double m_dSignalLength;
	double m_dAmpMax;
	double m_dAmpMin;
	double m_dTau;
	bool m_fEnabled;
};

#endif
