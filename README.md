# RBE595 Special Topics - Swarm Intelligence

- **Schelling Model**
- **Synchronizer**
- **Quorum Sensing**
- **Shape Formation**

dependencies:
1. python3
2. matplotlib
3. numpy

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

> Use Lennard Jones potential field to form a cell lattice using 20 khepera robots under a light source.
