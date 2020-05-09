import numpy as np
import matplotlib.pyplot as plt

N = 5
data = np.genfromtxt("data_with2515.dat", delimiter='	')
#data = np.genfromtxt("data_backup.dat", delimiter='	')

task0 = data[:,3]   #threshold for task0
task1 = data[:,4]   #threshold for task1
current_role = data[:,2]   #current role
m = task0.shape[0]
n = task1.shape[0]
p = current_role.shape[0]
task0 = task0.reshape((int(m/N),N))        #reshape into 3000,20
task1 = task1.reshape((int(n/N),N))        #reshape into 3000,20
role = current_role.reshape((int(p/N),N))  #reshape into 3000,20
m = task0.shape[0]
n = task0.shape[1]
p = task1.shape[0]
q = task1.shape[1]
print (m,n,p,q)  #print shape

x = [a for a in range(m)]  #create x for plot 

#plot figure for threshold
plt.figure()
for i in range(n):
   plt.plot(x,task0[:,i],label= str(i)+'_task0')  
   plt.plot(x,task1[:,i],label= str(i)+'_task1')
plt.xlabel('timestep')
plt.ylabel('theta')
plt.title("fig1")
plt.grid(True)
#plt.legend(bbox_to_anchor=(1.0, 1), loc=1, borderaxespad=0.)
plt.savefig('Figure1.png')
plt.show()

t_task0 =  np.zeros((m,n))   #store time fraction of task0 for each timestep 
t_task1 =  np.zeros((m,n))   #store time fraction of task1 for each timestep 
#array = np.arange(20).reshape(4,5)  a problem remains for arrange array cannot feed in values

#consider time fraction in a global way 
#time fraction of task i is the time agent takes task i in recent 200 timesteps
for i in range(n):
   for t in range(m):   
      if t < 200:
         t_task1[t][i] = sum(role[0:t,i])/(t+1)
         #print(t_task1[t][i])
         t_task0[t][i] = 1 - t_task1[t][i]
      else:
         t_task1[t][i] = sum(role[t-199:t,i])/(200)
         #print(t_task1[t][i])
         t_task0[t][i] = 1 - t_task1[t][i]
      # t_task1[t][i] = sum(role[0:t,i])/(t+1)
      # t_task0[t][i] = 1 - t_task1[t][i]

#plot figure for x_ij
plt.figure()
for i in range(n):
   plt.plot(x,t_task1[:,i])
   plt.plot(x,t_task0[:,i])
plt.xlabel('timestep')
plt.ylabel('x_ij')
plt.title("fig2")
plt.grid(True)
#plt.legend(bbox_to_anchor=(1.0, 1), loc=1, borderaxespad=0.)
plt.savefig('Figure2.png')
plt.show()