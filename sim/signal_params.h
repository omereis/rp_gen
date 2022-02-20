/******************************************************************************\
|                            signal_params.h                                   |
\******************************************************************************/

#ifndef	SIGNAL_PARAMS_INC
#define	SIGNAL_PARAMS_INC

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
protected:
	void AssignAll (const TSignalParams &other);
private:
	string m_strName;
	double m_dSignalLength;
	double m_dMaxAmp;
	double m_dTau;
};

#endif
