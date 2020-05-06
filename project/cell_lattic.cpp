#include "cell_lattic.h"
#include "buzz/buzzvm.h"


static CRange<Real> STIMULUS_RANGE(0.0, 1000.0);


struct GetRobotData: public CBuzzLoopFunctions::COperation{
	GetRobotData(int n_tasks):m_vecTaskCounts(n_tasks, 0){}
	float m_floatPositionX; 
	float m_floatPositionY; 
	virtual void operator()(const std::string& str_robot_id, buzzvm_t t_vm){
		buzzobj_t positionX = BuzzGet(t_vm, "positionX");
		buzzobj_t positionY = BuzzGet(t_vm, "positionY");
		buzzobj_t tTask = BuzzGet(t_vm, "tasks");
		int nTask = buzzobj_getint(tTask);
		m_floatPositionX = buzzobj_getfloat(positionX);
		m_floatPositionY = buzzobj_getfloat(positionY);

		++m_vecTaskCounts[nTask]; 
		m_vecRobotsTasks[t_vm->robot] = nTask; 
	}
	std::vector<int> m_vecTaskCounts;
   	/* Task-robot mapping */
   	std::map<int,int> m_vecRobotsTasks;
   	/* Robot-threshold mapping */
   	std::map<int,std::vector<float> > m_vecRobotsThresholds;
};

void CCellLattic::Init(TConfigurationNode& t_tree){
	CBuzzLoopFunctions::Init(t_tree); 
	GetNodeAttribute(t_tree, "outfile", m_strOutFile); 
	int nTasks; 
	GetNodeAttribute(t_tree, "tasks", nTasks); 
	/* Create a new RNG */
   	m_pcRNG = CRandom::CreateRNG("argos");
   	/* Initialize the stimuli */
   	m_vecStimuli.resize(nTasks);
   	for(int i = 0; i < m_vecStimuli.size(); ++i) {
    	m_vecStimuli[i] = m_pcRNG->Uniform(STIMULUS_RANGE);
   	}
   	/* Open the output file */
   	m_cOutFile.open(m_strOutFile.c_str(), std::ofstream::out | std::ofstream::trunc);
}

void CCellLattic::Reset(){
	/* Reset the stimuli */
	for(int i = 0; i < m_vecStimuli.size(); ++i) {
 		m_vecStimuli[i] = m_pcRNG->Uniform(STIMULUS_RANGE);
 	}
   	/* Reset the output file */
	m_cOutFile.open(m_strOutFile.c_str(), std::ofstream::out | std::ofstream::trunc);
}

void CCellLattic::Destroy(){
	m_cOutFile.close(); 
}
void CCellLattic::PostStep(){
	GetRobotData cGetRobotData(m_vecStimuli.size());
	BuzzForeachVM(cGetRobotData);
	for(int i = 0; i<GetNumRobots(); ++i){
		m_cOutFile << GetSpace().GetSimulationClock() << "\t"
					<< i << "\t"
					<< cGetRobotData.m_floatPositionX << "\t"
					<< cGetRobotData.m_floatPositionY;
		m_cOutFile << std::endl; 
	}
}

bool CCellLattic::IsExperimentFinished(){
	return false;
}

int CCellLattic::GetNumRobots() const{
	return m_mapBuzzVMs.size(); 
}

REGISTER_LOOP_FUNCTIONS(CCellLattic, "cell_lattic");

