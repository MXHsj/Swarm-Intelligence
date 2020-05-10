import numpy as np
import matplotlib.pyplot as plt

N = 10
data = np.genfromtxt("data.dat", delimiter='	')

positionX = data[:,2]   # x coordinate 
positionY = data[:,3]   #  y coordinate
current_role = data[:,1]   #current robot
m = positionX.shape[0]
n = positionY.shape[0]
p = current_role.shape[0]
task0 = positionX.reshape((int(m/N),N))        #reshape into x,10
task1 = positionY.reshape((int(n/N),N))        #reshape into y,10
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
   plt.plot(x, task0[:,i])  
plt.xlabel('timestep')
plt.ylabel('x coordinate')
plt.title("fig1")
plt.grid(True)
#plt.legend(bbox_to_anchor=(1.0, 1), loc=1, borderaxespad=0.)
plt.savefig('Figure1.png')
plt.show()


#plot figure for threshold
plt.figure()
for i in range(n):
   plt.plot(x, task1[:,i])  
plt.xlabel('timestep')
plt.ylabel('y coordinate')
plt.title("fig1")
plt.grid(True)
#plt.legend(bbox_to_anchor=(1.0, 1), loc=1, borderaxespad=0.)
plt.savefig('Figure2.png')
plt.show()

