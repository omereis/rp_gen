/******************************************************************************\
|                            signal_params.h                                   |
\******************************************************************************/

#ifndef	SIGNAL_PARAMS_INC
#define	SIGNAL_PARAMS_INC

#include "bd_types.h"
#include "jsoncpp/json/json.h"

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
	bool Generate(TFloatVec &vSignal, double dt, double dSignalTime);

	bool LoadFromJson(Json::Value jSignal, const string &strName="");
	bool SignalSetupFromFile (std::string &strFile, const string &strSignal);
	string GetAsString ();
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
	void SetSignalLength (double dLength);
	double GetSignalLength () const;
	double GetTauMin () const;
	double GetTauMax () const;
	void SetTauMin (double dTau);
	void SetTauMax (double dTau);

	string GetErrorString() const;
protected:
	void AssignAll (const TSignalParams &other);
	double AditiveNoise (double dValue);
private:
	string m_strErr;
	string m_strName;
	double m_dSignalLength;
	double m_dAmpMax;
	double m_dAmpMin;
	double m_dTau;
	double m_dTauMin;
	double m_dTauMax;
	bool m_fEnabled;
};

#endif
