import matplotlib.pyplot as plt
import numpy as np
import random as rdm


class grid:
    def __init__(self, W, H, P, R):
        self.row = H                # grid size
        self.col = W
        self.P = P                  # initiation probability
        self.R = R                  # refractory timer

        # state matrix: 0 -> suseptible; 1 -> refractory
        self.state = np.zeros(self.col*self.row).reshape(self.row, self.col)
        # initiated flag: 1 -> initiated; 0 -> not initiated
        self.initFlag = np.zeros(self.col*self.row).reshape(self.row, self.col)
        # group size estimation
        self.size = np.zeros(self.col*self.row).reshape(self.row, self.col)
        # emit signal: 0 -> not emitted, 1 -> emitted
        self.signal = np.zeros(self.col*self.row).reshape(self.row, self.col)
        # matrix to store old signal
        self.signal_old = np.zeros(
            self.col*self.row).reshape(self.row, self.col)
        # refractory timer for each cell
        self.refractorytimer = np.zeros(
            self.col*self.row).reshape(self.row, self.col)
        # num of steps receiving no signal
        self.isDone_count = np.zeros(
            self.col*self.row).reshape(self.row, self.col)
        # "done" flag
        self.isDone_flag = np.zeros(
            self.col*self.row).reshape(self.row, self.col)

        # display properties
        self.img = plt.imshow(self.signal, 'gray',
                              extent=(0, self.col, self.row, 0))
        self.ax = plt.gca()

    def find4neighbor(self, grid, i, j):
        count = 0
        if i > 0:
            if grid[i-1][j]:              # NORTH
                count += 1
        if j > 0:
            if grid[i][j-1]:              # WEST
                count += 1
        if i < self.row-1:
            if grid[i+1][j]:              # SOUTH
                count += 1
        if j < self.col-1:
            if grid[i][j+1]:              # EAST
                count += 1
        return count

    def find8neighbor(self, grid, i, j):
        count = 0
        if i > 0:
            if grid[i-1][j]:              # NORTH
                count += 1
        if j > 0:
            if grid[i][j-1]:              # WEST
                count += 1
        if i < self.row-1:
            if grid[i+1][j]:              # SOUTH
                count += 1
        if j < self.col-1:
            if grid[i][j+1]:              # EAST
                count += 1
        if i > 0 and j > 0:
            if grid[i-1][j-1]:            # NORTH-WEST
                count += 1
        if i > 0 and j < self.col-1:
            if grid[i-1][j+1]:            # NORTH-EAST
                count += 1
        if i < self.row-1 and j > 0:
            if grid[i+1][j-1]:            # SOUTH-WEST
                count += 1
        if i < self.row-1 and j < self.col-1:
            if grid[i+1][j+1]:            # SOUTH-EAST
                count += 1
        return count

    def update_map(self):
        # initiate signal
        for i in range(self.row):
            for j in range(self.col):
                if not self.state[i][j]:
                    if (not self.initFlag[i][j]) and (rdm.random() < self.P):
                        self.signal[i][j] = 1       # emit signal
                        self.state[i][j] = 1        # switch to refractory
                        self.refractorytimer[i][j] = self.R
                        self.initFlag[i][j] = 1     # initiated
                        self.size[i][j] += 1
                        self.isDone_count[i][j] = 0
        self.visualize(self.signal)
        self.signal_old = self.signal
        self.signal = np.multiply(0, self.signal)   # reset signal
        # spread signal
        for i in range(self.row):
            for j in range(self.col):
                if not self.state[i][j]:            # if susceptible
                    if self.find4neighbor(self.signal_old, i, j):
                        self.signal[i][j] = 1       # emit signal
                        self.state[i][j] = 1        # switch to refractory
                        self.refractorytimer[i][j] = self.R
                        self.size[i][j] += 1
                        self.isDone_count[i][j] = 0
                    else:
                        self.isDone_count[i][j] += 1
                else:                               # if refractory
                    self.refractorytimer[i][j] -= 1
                    if self.refractorytimer[i][j] <= 0:
                        self.state[i][j] = 0        # switch to susceptible
                if self.isDone_count[i][j] > (1/self.P):
                    self.isDone_flag[i][j] = 1

    def visualize(self, grid2visualize):
        # update plot
        self.img.set_data(grid2visualize)
        self.ax.grid(color='w', linestyle='-', linewidth=2)
        self.ax.set_xticks(np.arange(0, self.col, 1))
        self.ax.set_yticks(np.arange(0, self.row, 1))
        self.img.autoscale()
        plt.pause(0.01)


def main():
    Mygrid = grid(10, 10, 0.01, 20)     # W H P R
    n = 0
    nmax = 2000
    while True:
        Mygrid.update_map()
        n += 1
        print("step:", n, " finished cells:", np.sum(Mygrid.isDone_flag))
        if np.sum(Mygrid.isDone_flag) >= Mygrid.row*Mygrid.col:    # if all agents are done
            break
        if n > nmax:
            print("Time out")
            break
    print("Finish.")
    print(Mygrid.size)
    # plt.show()


if __name__ == "__main__":
    main()
