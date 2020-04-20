#include "threshold_model.h"
#include "buzz/buzzvm.h"

static CRange<Real> STIMULUS_RANGE(0.0, 1000.0);

/****************************************/
/****************************************/

/**
 * Functor to get data from the robots
 */
struct GetRobotData : public CBuzzLoopFunctions::COperation {

   /** Constructor */
   GetRobotData(int n_tasks) : m_vecTaskCounts(n_tasks, 0) {}

   /** The action happens here */
   virtual void operator()(const std::string& str_robot_id,
                           buzzvm_t t_vm) {
      /* Get the current task */
      buzzobj_t tTask = BuzzGet(t_vm, "task");
      /* Make sure it's the type we expect (an integer) */
      if(!buzzobj_isint(tTask)) {
         LOGERR << str_robot_id << ": variable 'task' has wrong type " << buzztype_desc[tTask->o.type] << std::endl;
         return;
      }
      /* Get the value */
      int nTask = buzzobj_getint(tTask);
      /* Make sure its value is correct */
      if(nTask >= m_vecTaskCounts.size()) {
         LOGERR << str_robot_id << ": variable 'task' has wrong value " << nTask << std::endl;
         return;
      }
      /* Increase the task counter */
      ++m_vecTaskCounts[nTask];
      /* Set the mapping */
      m_vecRobotsTasks[t_vm->robot] = nTask;
      /* Get the current thresholds */
      BuzzTableOpen(t_vm, "threshold");
      buzzobj_t tThreshold = BuzzGet(t_vm, "threshold");
      /* Make sure it's the type we expect (a table) */
      if(!buzzobj_istable(tThreshold)) {
         LOGERR << str_robot_id << ": variable 'threshold' has wrong type " << buzztype_desc[tThreshold->o.type] << std::endl;
         return;
      }
      /* Get the values */
      m_vecRobotsThresholds[t_vm->robot].resize(m_vecTaskCounts.size(), 0.0);
      for(int i = 0; i < m_vecTaskCounts.size(); ++i) {
         /* Get the object */
         buzzobj_t tThresholdValue = BuzzTableGet(t_vm, i);
         /* Make sure it's the type we expect (a float) */
         if(!buzzobj_isfloat(tThresholdValue)) {
            LOGERR << str_robot_id << ": element 'threshold[" << i << "]' has wrong type " << buzztype_desc[tThresholdValue->o.type] << std::endl;
         }
         else {
            /* Get the value */
            float fThresholdValue = buzzobj_getfloat(tThresholdValue);
            /* Set the mapping */
            m_vecRobotsThresholds[t_vm->robot][i] = fThresholdValue;
         }
      }
   }

   /** Task counter */
   std::vector<int> m_vecTaskCounts;
   /* Task-robot mapping */
   std::map<int,int> m_vecRobotsTasks;
   /* Robot-threshold mapping */
   std::map<int,std::vector<float> > m_vecRobotsThresholds;
};

/****************************************/
/****************************************/

/**
 * Functor to put the stimulus in the Buzz VMs.
 */
struct PutStimuli : public CBuzzLoopFunctions::COperation {

   /** Constructor */
   PutStimuli(const std::vector<float>& vec_stimuli) : m_vecStimuli(vec_stimuli) {}
   
   /** The action happens here */
   virtual void operator()(const std::string& str_robot_id,
                           buzzvm_t t_vm) {
      /* Set the values of the table 'stimulus' in the Buzz VM */
      BuzzTableOpen(t_vm, "stimulus");
      for(int i = 0; i < m_vecStimuli.size(); ++i) {
         BuzzTablePut(t_vm, i, m_vecStimuli[i]);
      }
      BuzzTableClose(t_vm);
   }

   /** Calculated stimuli */
   const std::vector<float>& m_vecStimuli;
};

/****************************************/
/****************************************/

void CThresholdModel::Init(TConfigurationNode& t_tree) {
   /* Call parent Init() */
   CBuzzLoopFunctions::Init(t_tree);
   /* Parse XML tree */
   GetNodeAttribute(t_tree, "outfile", m_strOutFile);
   GetNodeAttribute(t_tree, "delta", m_fDelta);
   GetNodeAttribute(t_tree, "alpha", m_fAlpha);
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
   m_cOutFile.open(m_strOutFile.c_str(),
                   std::ofstream::out | std::ofstream::trunc);
}

/****************************************/
/****************************************/

void CThresholdModel::Reset() {
   /* Reset the stimuli */
   for(int i = 0; i < m_vecStimuli.size(); ++i) {
      m_vecStimuli[i] = m_pcRNG->Uniform(STIMULUS_RANGE);
   }
   /* Reset the output file */
   m_cOutFile.open(m_strOutFile.c_str(),
                   std::ofstream::out | std::ofstream::trunc);

}

/****************************************/
/****************************************/

void CThresholdModel::Destroy() {
   m_cOutFile.close();
}

/****************************************/
/****************************************/

void CThresholdModel::PostStep() {
   /* Get robot data */
   GetRobotData cGetRobotData(m_vecStimuli.size());
   BuzzForeachVM(cGetRobotData);
   /* Update the stimuli */
   for(int i = 0; i < m_vecStimuli.size(); ++i) {
      m_vecStimuli[i] += m_fDelta - m_fAlpha / GetNumRobots() * cGetRobotData.m_vecTaskCounts[i];
   }
   /* Convey the stimuli to every robot */
   BuzzForeachVM(PutStimuli(m_vecStimuli));
   /* Flush data to the output file */
   for(int i = 0; i < GetNumRobots(); ++i) {
      m_cOutFile << GetSpace().GetSimulationClock() << "\t"
                 << i << "\t"
                 << cGetRobotData.m_vecRobotsTasks[i];
      for(int j = 0; j < m_vecStimuli.size(); ++j) {
         m_cOutFile << "\t" << cGetRobotData.m_vecRobotsThresholds[i][j];
      }
      m_cOutFile << std::endl;
   }
}

/****************************************/
/****************************************/

bool CThresholdModel::IsExperimentFinished() {
   /* Feel free to try out custom ending conditions */
   return false;
}

/****************************************/
/****************************************/

int CThresholdModel::GetNumRobots() const {
   return m_mapBuzzVMs.size();
}

/****************************************/
/****************************************/

REGISTER_LOOP_FUNCTIONS(CThresholdModel, "threshold_model");
