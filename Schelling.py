import matplotlib.pyplot as plt
import numpy as np
import random

# constant variables
col = 50                                                # size of the grid
row = 50
t = 3                                                   # satisfactory threshold
t_biased = 5
P_rate = 0.6
P = round(P_rate*col*row)                               # population
biased_rate = 0.0                                       # biased population
iteration = 20

# pre-allocation
grid = np.empty(col*row).reshape(row, col)
occ_idx = random.sample(range(1, col*row), P)
agentX_idx = random.sample(occ_idx, round(P/2))
agentO_idx = [x for x in occ_idx if x not in agentX_idx]
biasedX_idx = [random.sample(agentX_idx, round(biased_rate*len(agentX_idx)))]
biasedO_idx = [random.sample(agentO_idx, round(biased_rate*len(agentO_idx)))]


def check_neighbor(grid, i, j):
    homophily = 0
    if i > 0:
        if grid[i-1][j] == grid[i][j]:              # NORTH
            homophily += 1
    else:
        if grid[i-1+row][j] == grid[i][j]:
            homophily += 1

    if j > 0:
        if grid[i][j-1] == grid[i][j]:              # WEST
            homophily += 1
    else:
        if grid[i][j-1+col] == grid[i][j]:
            homophily += 1

    if i < row-1:
        if grid[i+1][j] == grid[i][j]:              # SOUTH
            homophily += 1
    else:
        if grid[i+1-row][j] == grid[i][j]:
            homophily += 1

    if j < col-1:
        if grid[i][j+1] == grid[i][j]:              # EAST
            homophily += 1
    else:
        if grid[i][j+1-col] == grid[i][j]:
            homophily += 1

    if i > 0 and j > 0:
        if grid[i-1][j-1] == grid[i][j]:            # NORTH-WEST
            homophily += 1
    elif i <= 0 and j <= 0:
        if grid[i-1+row][j-1+col] == grid[i][j]:
            homophily += 1

    if i > 0 and j < col-1:
        if grid[i-1][j+1] == grid[i][j]:            # NORTH-EAST
            homophily += 1
    elif i <= 0 and j >= col-1:
        if grid[i-1+row][j+1-col] == grid[i][j]:
            homophily += 1

    if i < row-1 and j > 0:
        if grid[i+1][j-1] == grid[i][j]:            # SOUTH-WEST
            homophily += 1
    elif i >= row-1 and j <= 0:
        if grid[i+1-row][j-1+col] == grid[i][j]:
            homophily += 1

    if i < row-1 and j < col-1:
        if grid[i+1][j+1] == grid[i][j]:            # SOUTH-EAST
            homophily += 1
    elif i >= row-1 and j >= col-1:
        if grid[i+1-row][j+1-col] == grid[i][j]:
            homophily += 1

    return homophily


def BFS(grid, i, j, threshold):
    search_depth = 8
    for dr in range(-search_depth, search_depth+1):
        for dc in range(-search_depth, search_depth+1):
            neighbor_r = i + dr
            neighbor_c = j + dc
            # boundary condition
            if neighbor_r <= 0:
                neighbor_r += row
            if neighbor_c <= 0:
                neighbor_c += col
            if neighbor_r >= row:
                neighbor_r -= row
            if neighbor_c >= col:
                neighbor_c -= col
            count = check_neighbor(grid, neighbor_r, neighbor_c)
            if count >= threshold and grid[neighbor_r][neighbor_c] == 0.5:
                return neighbor_r, neighbor_c
    return i, j


def main():
    # initial condition
    for i in range(row):
        for j in range(col):
            if (i*col+j in occ_idx) and (i*col+j in agentX_idx):
                grid[i][j] = 1              # agent X
            elif (i*col+j in occ_idx) and (i*col+j in agentO_idx):
                grid[i][j] = 0              # agent O
            else:
                grid[i][j] = 0.5            # free cell

    # updating
    plt.title("t = %d, " % t + "P: %f, " % P_rate + "bias= %f" % biased_rate)
    img = plt.imshow(grid, 'bwr')
    count = 0
    n = 0
    while n < iteration:
        img.set_data(grid)
        plt.autoscale()
        plt.pause(1e-17)

        # check satisfactory rate
        satisfied = 0
        for i in range(row):
            for j in range(col):
                if grid[i][j] != 0.5:
                    count = check_neighbor(grid, i, j)
                    if count >= t:
                        satisfied += 1
        rate = satisfied/P
        # if rate >= 0.9:
        #     break
        print("iteration: ", n, " satisfied rate: %.4f" % rate)

        # update unsatisfied cells
        for i in range(0, row):
            for j in range(0, col):
                if grid[i][j] != 0.5:
                    count = check_neighbor(grid, i, j)
                    if (i*col+j in biasedX_idx) or (i*col+j in biasedO_idx):
                        if count < t_biased:
                            goal_i, goal_j = BFS(grid, i, j, t_biased)
                            buffer = grid[goal_i][goal_j]
                            grid[goal_i][goal_j] = grid[i][j]
                            grid[i][j] = buffer
                    else:
                        if count < t:
                            goal_i, goal_j = BFS(grid, i, j, t)
                            buffer = grid[goal_i][goal_j]
                            grid[goal_i][goal_j] = grid[i][j]
                            grid[i][j] = buffer
        n += 1
    print("Finish.")
    plt.show()


if __name__ == "__main__":
    main()
