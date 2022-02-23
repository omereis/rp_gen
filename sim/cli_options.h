/*****************************************************************************\
|                               cli_options.h                                 |
\*****************************************************************************/

#ifndef	CLI_OPTIONS_INC
#define	CLI_OPTIONS_INC

using namespace std;
#include <string>
#include "signal_params.h"
#include "bd_types.h"

class TCliOptions {
public:
	TCliOptions (const TCliOptions &other);
	TCliOptions ();
	TCliOptions operator= (const TCliOptions &other);
	bool operator== (const TCliOptions &other) const;
	bool operator!= (const TCliOptions &other) const;
	void Clear ();

	TSignalParams GetParmasAlpha() const;
	TSignalParams GetParmasbeta() const;
	void LoadFromFile (const char *szFile);
	void Print ();
	bool Generate(TFloatVec &vSignal);

	void SetShowHelp (bool f);
	bool GetShowHelp ();
	double GetSmaplingRate () const;
	void SetSamplingRate (double d);
	string GetOutFileName () const;
	void SetOutFileName (const string &strFileName);

	void GetSamplingRate(double dRate);
	double GetSamplingRate();
	void SaveToFile (const TFloatVec &vAlpha);
	void SetSignalLength (double dSignalLen);
	double GetSignalLength () const;
protected:
	void AssignAll (const TCliOptions &other);
private:
	TSignalParams m_paramAlpha;
	TSignalParams m_paramBeta;
	string m_strOutput;
	double m_dPulseRate;
	double m_dSignalLength;
	bool m_fShowHelp;
	double m_dSamplingRate;
};
#endif