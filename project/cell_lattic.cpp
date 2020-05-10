#include "cell_lattic.h"
#include "buzz/buzzvm.h"




struct GetRobotData: public CBuzzLoopFunctions::COperation{
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

		m_vecRobotsX[t_vm->robot] = m_floatPositionX;
		m_vecRobotsY[t_vm->robot] = m_floatPositionY;
		m_vecRobotsKin[t_vm->robot] = m_targetKin;
		m_vecRobotsNonKin[t_vm->robot] = m_targetNonKin;
	}
	   std::map<int,float> m_vecRobotsX;
	   std::map<int,float> m_vecRobotsY;
	   std::map<int,float> m_vecRobotsKin;
	   std::map<int,float> m_vecRobotsNonKin;


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
					<< cGetRobotData.m_vecRobotsX[i] << "\t"
					<< cGetRobotData.m_vecRobotsY[i] << "\t"
					<< cGetRobotData.m_vecRobotsKin[i] << "\t"
					<< cGetRobotData.m_vecRobotsNonKin[i];
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

