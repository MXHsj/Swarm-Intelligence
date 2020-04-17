import matplotlib.pyplot as plt
import numpy as np


class map:
    def __init__(self, row, col, T, k):
        self.row = row          # grid size
        self.col = col
        self.T = T              # maximum counter value
        self.k = k              # booster

        # initial state matrix
        self.state = np.zeros(self.col*self.row).reshape(self.row, self.col)
        # initial counter matrix
        self.c = np.random.randint(self.T, size=(self.row, self.col))
        # display initial map
        self.img = plt.imshow(self.state, 'gray')

    def find_neighbor(self, i, j):
        count = 0
        if i > 0:
            if self.state[i-1][j]:              # NORTH
                count += 1
        else:
            if self.state[i-1+self.row][j]:
                count += 1

        if j > 0:
            if self.state[i][j-1]:              # WEST
                count += 1
        else:
            if self.state[i][j-1+self.col]:
                count += 1

        if i < self.row-1:
            if self.state[i+1][j]:              # SOUTH
                count += 1
        else:
            if self.state[i+1-self.row][j]:
                count += 1

        if j < self.col-1:
            if self.state[i][j+1]:              # EAST
                count += 1
        else:
            if self.state[i][j+1-self.col]:
                count += 1

        return count

    def update_map(self):
        for i in range(self.row):
            for j in range(self.col):
                self.c[i][j] += 1
                count = self.find_neighbor(i, j)
                self.c[i][j] += count*round(self.k*self.c[i][j])
                if self.c[i][j] >= self.T:
                    self.state[i][j] = 1
                    self.c[i][j] = 0
                else:
                    self.state[i][j] = 0

    def visualize(self, grid2visualize):
        # update plot
        self.img.set_data(grid2visualize)
        self.img.autoscale()
        plt.pause(0.05)


def main():
    flash_map = map(10, 10, 100, 0.85)
    iteration = 500
    for n in range(iteration+1):
        flash_map.visualize(flash_map.state)
        flash_map.update_map()
        print("step: ", n, "/", iteration)
    print("Finish.")
    plt.show()


if __name__ == "__main__":
    main()
