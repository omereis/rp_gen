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

	TSignalParams GetParamsAlpha() const;
	TSignalParams GetParamsBeta() const;
	void SetParamsAlpha(const TSignalParams &paramsAlpha);
	void SetParamsBeta(const TSignalParams &paramsBeta);

	bool LoadFromFile (const std::string &strFile);
	bool LoadFromFile (const char *szFile);
	void Print ();
	void PrintParams ();
	bool GenerateBuffer(TFloatVec &vBuffer);
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
	double GetPulseRate () const;
	void SetPulseRate (double dRate);
	int GetBufferSize() const;
	void SetBufferSize(int nSize);
	void SetNoise (double dNoise);
	double GetNoise () const;

	bool SaveSignal (const TFloatVec &vSignal, const string &strFileName);
	void AddNoise (TFloatVec &vSignal, double dNoise);
protected:
	void AssignAll (const TCliOptions &other);
private:
	TSignalParams m_paramAlpha;
	TSignalParams m_paramBeta;
	string m_strOutput;
	double m_dPulseRate;
	double m_dSignalLength;
	double m_dNoise;
	bool m_fShowHelp;
	double m_dSamplingRate;
	int m_nBufferSize;
};
#endif
