from utils import Matrix

# displaced tiles heuristic
def displaced_tiles_heuristic_with_blank_tile(puzzle_configuration: Matrix, goal: Matrix):
    heuristic_distance = 0
    for i in range(3):
        for j in range(3):
            if puzzle_configuration.mat[i][j] == -1:
                #print("yes")
                continue
                
            if puzzle_configuration.mat[i][j] != goal.mat[i][j]:
                heuristic_distance += 1
    return heuristic_distance

# manhattan distance hueristic
def manhattan_heuristic_with_blank_tile(puzzle_configuration: Matrix, goal: Matrix):
    heuristic_distance = 0
    real_row = [0, 0, 0, 1, 1, 1, 2, 2, 2]
    real_col = [0, 1, 2, 0, 1, 2, 0, 1, 2]
    for i in range(3):
        for j in range(3):
            real_row[goal.mat[i][j] - 1] = i
            real_col[goal.mat[i][j] - 1] = j
    for i in range(3):
        for j in range(3):
            if puzzle_configuration.mat[i][j] == -1:
                continue
                
            val = puzzle_configuration.mat[i][j] - 1
            heuristic_distance += abs(real_row[val] - i) + \
                abs(real_col[val] - j)
    return heuristic_distance


# used for simple bfs and dijkstra's heuristic
def zero_heuristic():
    return 0


def eucldian(puzzle_configuration: Matrix, goal: Matrix):
    heuristic_distance = 0
    real_row = [0, 0, 0, 1, 1, 1, 2, 2, 2]
    real_col = [0, 1, 2, 0, 1, 2, 0, 1, 2]
    for i in range(3):
        for j in range(3):
            real_row[goal.mat[i][j] - 1] = i
            real_col[goal.mat[i][j] - 1] = j
    for i in range(3):
        for j in range(3):
            val = puzzle_configuration.mat[i][j] - 1
            
            if(val == -2):
                continue
                
            temp1 = abs(real_row[val] - i) * abs(real_row[val] - i)
            temp2 = abs(real_col[val] - j) * abs(real_col[val] - j)
 
            temp1_ans = temp1
            temp2_ans = temp2
            for k in range(10):
                temp1_ans = temp1_ans * temp1
                temp2_ans = temp2_ans * temp2
            
            heuristic_distance += (temp1_ans + temp2_ans)
    return heuristic_distance