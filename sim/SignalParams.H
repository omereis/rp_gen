class TSignalParams {
public:
	TSignalParams ();
	TSignalParams  (const TSignalParams &other);
	TSignalParams operator= (const TSignalParams  &other);
	bool operator== (const TSignalParams &other) const;
	bool operator!= (const TSignalParams &other) const;
	void Clear ();
protected:
	void AssignAll const TSignalParams &other);
private:
	double m_dSignalLength;
	double m_dMaxAmp;
};