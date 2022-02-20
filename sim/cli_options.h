/*****************************************************************************\
|                               cli_options.h                                 |
\*****************************************************************************/

#ifndef	CLI_OPTIONS_INC
#define	CLI_OPTIONS_INC

using namespace std;
#include <string>
#include "signal_params.h"

class TCliOptions {
public:
	TCliOptions (const TCliOptions &other);
	TCliOptions ();
	TCliOptions operator= (const TCliOptions &other);
	bool operator== (const TCliOptions &other) const;
	bool operator!= (const TCliOptions &other) const;
	void Clear ();
protected:
	void AssignAll (const TCliOptions &other);
private:
	TSignalParams m_paramAlpha;
	TSignalParams m_paramBeta;
	string m_strOutput;
	double m_dPulseRate;
};
#endif
