#ifndef THRESHOLD_MODEL_H
#define THRESHOLD_MODEL_H

#include <buzz/argos/buzz_loop_functions.h>
#include <argos3/core/utility/math/rng.h>

class CThresholdModel : public CBuzzLoopFunctions {

public:

   CThresholdModel() {}
   virtual ~CThresholdModel() {}

   /**
    * Executes user-defined initialization logic.
    * @param t_tree The 'loop_functions' XML configuration tree.
    */
   virtual void Init(TConfigurationNode& t_tree);

   /**
    * Executes user-defined reset logic.
    * This method should restore the state of the simulation at it was right
    * after Init() was called.
    * @see Init()
    */
   virtual void Reset();

   /**
    * Executes user-defined logic right after a control step is executed.
    */
   virtual void PostStep();
   
   /**
    * Returns true if the experiment is finished, false otherwise.
    *
    * This method allows the user to specify experiment-specific ending
    * conditions. If this function returns false and a time limit is set in the
    * .argos file, the experiment will reach the time limit and end there. If no
    * time limit was set, then this function is the only ending condition.
    *
    * @return true if the experiment is finished.
    */
   virtual bool IsExperimentFinished();

   /**
    * Executes user-defined destruction logic.
    * This method should undo whatever is done in Init().
    * @see Init()
    */
   virtual void Destroy();

private:

   int GetNumRobots() const;

private:

   /** 'delta' parameter at slide 16 */
   Real m_fDelta;

   /** 'alpha' parameter at slide 16 */
   Real m_fAlpha;

   /** The stimuli associated to the tasks */
   std::vector<float> m_vecStimuli;

   /** The output file name */
   std::string m_strOutFile;

   /** The output file stream */
   std::ofstream m_cOutFile;

   /** Random number generator */
   CRandom::CRNG* m_pcRNG;
};

#endif
