#ifndef CELL_LATTIC_H
#define CELL_LATTIC_H

#include <buzz/argos/buzz_loop_functions.h>
#include <argos3/core/utility/math/rng.h>

class CCellLattic : public CBuzzLoopFunctions {

public: 
	CCellLattic(){}
	virtual ~CCellLattic(){}

	virtual void Init(TConfigurationNode& t_tree); 
	virtual void Reset();
	virtual void PostStep(); 
	virtual bool IsExperimentFinished(); 
	virtual void Destroy(); 

private: 
	int GetNumRobots() const; 
private:
	std::string m_strOutFile;
	std::ofstream m_cOutFile; 
	std::vector<float> m_vecStimuli;
	CRandom::CRNG* m_pcRNG;
};
#endif
