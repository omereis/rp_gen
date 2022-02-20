/*****************************************************************************\
|                                  rp_gen.h                                   |
\*****************************************************************************/
#ifndef	RP_GEN_INC
#define RP_GEN_INC
#endif

#include "signal_params.h"
#include "cli_options.h"

class TRpGen {
public:
    TRpGen ();
    TRpGen (const TRpGen &other);
    TRpGen operator= (const TRpGen &other);
    bool operator== (const TRpGen &other) const;
    bool operator!= (const TRpGen &other) const;
    void Clear ();
protected:
    void AssignAll (const TRpGen &other);
private:
    TSignalParams m_prmAlpha;
    TSignalParams m_prmBeta;
	TCliOptions m_options;
};
