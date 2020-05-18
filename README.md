# RBE595 Special Topics - Swarm Intelligence

1. **Schelling Model**
2. **Synchronizer**
3. **Quorum Sensing**
4. **Obstacle Avoidance**
5. **Shape Formation**
6. **Task Allocation**
7. **Collective Transport**
8. **Project**

python depenencies
- python3
- matplotlib
- numpy
 
buzz & argos installation
- see RBE595_ARGoS_Buzz_Installations.pdf

### Schelling Model
> Schelling.py

> Two types of agents allocated randomly on a grid are trying to rearrange themselves so that each agent has at least **t** same type of agents as neighbors. An agent first checks if the above condition is satisfied. If so, the agent remains unmoved, otherwise it moves to the nearest empty cell with **t** same agents using BFS. Pretty soon segregation will apear.

### Synchronizer
> synchronizer.py

> 100 agents are distributed on a 10x10 grid. Each agent has an initial state 0 and a counter that counts from 0 to 100. The counter value is assigned randomly at first and is added by 1 in each simulation step. If the counter value hits 100, the counter is reset to 0 and the agent changes state to 1 then immediately goes back the 0. (flash) If an agent has a neighbor flashed, there will be a boost in its own counter. At first the agents flash randomly but after a while they become synchronized.

### Quorum Sensing
> QuorumSensing.py

> Quorum Sensing is a strategy that bacteria uses to estimate the group size. Each agent has a probability to initiate a signal and can only initiate signal once. Its neighoring agents will detect the signal and keep spreading the signal. The agent either initiated a signal or passed a signal will go to "silent" state for some time step, during which it cannot initiate or pass signal. Upon initiating or receiving signal, the group size estimation for the agent will add by 1. The estimation finishes when all the agents have initiated signal.

### Shape Formation
> shape_formation.bzz

> Use Lennard Jones potential field to form a cell lattice using 20 Khepera robots.

### Obstacle Avoidace
> obstacle_avoidacen.bzz

> Use proximity sensors mounted on Khepera robot to perform obstacle avoidace.

### Task Allocation
> task_allocation.bzz

> Implement the Threshold Model proposed by Theraulaz et al. Two types of tasks (0,1) are allocated among 5 agents. The simulation is run for 3000 time steps where specialization on tasks can be observed.

### Collective Transport
> collective_transport.bzz

> A number of Khepera robots collectively transport a box initially located at the center of the arena to the light source. The robots move randomly when the light sensors detect light and move towards the light source position when the light sensors are blocked. Experiments are done with different group size and different box mass.

### Course Project
> A group of agents form cell-lattice formation and collectively traverse through a tunnel-like environment using modified Lennard-Jones potential approach. The distance between agents is dynamically changing according to the width of the tunnel: the swarm shrinks when encountering with narrow tunnel and expands when traveling through wide open area
