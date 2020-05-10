#include "cell_lattic.h"
#include "buzz/buzzvm.h"




struct GetRobotData: public CBuzzLoopFunctions::COperation{


	// GetRobotData(int n_tasks) : m_vecTaskCounts(n_tasks, 0) {}

	float m_floatPositionX; 
	float m_floatPositionY; 
	float m_targetKin; 
	float m_targetNonKin;
	virtual void operator()(const std::string& str_robot_id, buzzvm_t t_vm){
		buzzobj_t positionX = BuzzGet(t_vm, "positionX");

		buzzobj_t positionY = BuzzGet(t_vm, "positionY");
		buzzobj_t targetKin = BuzzGet(t_vm, "TARGET_KIN"); 
		buzzobj_t targetNonKin = BuzzGet(t_vm, "TARGET_NONKIN"); 

		m_floatPositionX = buzzobj_getfloat(positionX);
		m_floatPositionY = buzzobj_getfloat(positionY);

		m_targetKin = buzzobj_getfloat(targetKin); 
		m_targetNonKin = buzzobj_getfloat(targetNonKin); 

		m_vecRobotsTasks[t_vm->robot] = m_floatPositionX;
		m_vecRobotsTasks2[t_vm->robot] = m_floatPositionY;



		// for(int i = 0; i < m_vecTaskCounts.size(); ++i) {
  //        /* Get the object */
  //      		buzzobj_t positionX = BuzzGet(t_vm, "positionX");
  //         Get the value 
		// 	m_floatPositionX = buzzobj_getfloat(positionX);
  //        /* Set the mapping */
  //       	m_vecRobotsThresholds[t_vm->robot][i] = m_floatPositionX;
         
  //     }

	}
	   std::map<int,float> m_vecRobotsTasks;
	   std::map<int,float> m_vecRobotsTasks2;


};

void CCellLattic::Init(TConfigurationNode& t_tree){
	CBuzzLoopFunctions::Init(t_tree); 
	GetNodeAttribute(t_tree, "outfile", m_strOutFile); 
   	/* Open the output file */
   	m_cOutFile.open(m_strOutFile.c_str(), std::ofstream::out | std::ofstream::trunc);
}

void CCellLattic::Reset(){
   	/* Reset the output file */
	m_cOutFile.open(m_strOutFile.c_str(), std::ofstream::out | std::ofstream::trunc);
}

void CCellLattic::Destroy(){
	m_cOutFile.close(); 
}
void CCellLattic::PostStep(){
	GetRobotData cGetRobotData;
	BuzzForeachVM(cGetRobotData);
	for(int i = 0; i<GetNumRobots(); ++i){
		m_cOutFile << GetSpace().GetSimulationClock() << "\t"
					<< i << "\t"
					<< cGetRobotData.m_vecRobotsTasks[i] << "\t"
					<< cGetRobotData.m_vecRobotsTasks2[i] << "\t"
					<< cGetRobotData.m_targetKin << "\t"
					<< cGetRobotData.m_targetNonKin;
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

