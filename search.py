from queue import PriorityQueue
from utils import Matrix, up, down, left, right, printMat
import heuristics
from state import Puzzle_State, Puzzle_State_BFS


def h_n(current_matrix, goal, heuristic_used: int):
    if heuristic_used == 1:
        return heuristics.displaced_tiles_heuristic_with_blank_tile(current_matrix, goal)
    elif heuristic_used == 2:
        return heuristics.manhattan_heuristic_with_blank_tile(current_matrix, goal)
    elif heuristic_used == 3:
        return heuristics.zero_heuristic()
    elif heuristic_used == 4:
        return heuristics.eucldian(current_matrix, goal)

def find_neighbours(puzzle_state: Puzzle_State):
    neighbours = [
        up(puzzle_state.puzzle_configuration),
        down(puzzle_state.puzzle_configuration),
        left(puzzle_state.puzzle_configuration),
        right(puzzle_state.puzzle_configuration)
    ]
    return neighbours


def a_star(initial_matrix: Matrix, goal: Matrix, heuristic_used: int):
    puzzle_start = Puzzle_State(initial_matrix, 0, h_n(initial_matrix, goal, heuristic_used))
    open_list = PriorityQueue()
    open_list.put(puzzle_start)
    open_list_len = 1
    closed_list = {}
    parent_list = {}
    string_to_matrix_mapping = {}
    optimal_path_cost = -1
    puzzle_configuration_string = ''.join(str(val) for row in puzzle_start.puzzle_configuration.mat for val in row)
    closed_list[puzzle_configuration_string] = 0
    
    is_monotone = True
    
    while open_list_len > 0:
        puzzle_state: Puzzle_State = open_list.get()
        open_list_len -= 1
        puzzle_configuration_string = ''.join(str(val) for row in puzzle_state.puzzle_configuration.mat for val in row)
        if puzzle_configuration_string not in closed_list:
            closed_list[puzzle_configuration_string] = puzzle_state.g_n
        else:
            closed_list[puzzle_configuration_string] = min(closed_list[puzzle_configuration_string], puzzle_state.g_n)
        string_to_matrix_mapping[puzzle_configuration_string] = puzzle_state.puzzle_configuration.mat
        if (puzzle_state.puzzle_configuration.mat == goal.mat).all():
            optimal_path_cost = puzzle_state.g_n
            break
        neighbours = find_neighbours(puzzle_state)
        for neighbour in neighbours:
            if neighbour is None:
                continue
            neighbour_string = ''.join(str(val) for row in neighbour.mat for val in row)

            if neighbour_string not in closed_list:
                parent_list[neighbour_string] = puzzle_configuration_string
                closed_list[neighbour_string] = puzzle_state.g_n + 1
                
                init_cost = h_n(puzzle_state.puzzle_configuration,goal,heuristic_used)
                fin_cost = h_n(neighbour, goal, heuristic_used)
                
                
                if(init_cost>fin_cost +1):
                    is_monotone = False
                
                
                open_list.put(Puzzle_State(neighbour, puzzle_state.g_n + 1, h_n(neighbour, goal, heuristic_used)))
                open_list_len += 1
            elif puzzle_state.g_n + 1 < closed_list[neighbour_string]:
                parent_list[neighbour_string] = puzzle_configuration_string
                closed_list[neighbour_string] = puzzle_state.g_n + 1
                
                init_cost = h_n(puzzle_state.puzzle_configuration,goal,heuristic_used)
                fin_cost = h_n(neighbour, goal, heuristic_used)
                
                if(init_cost>fin_cost +1):
                    is_monotone = False
                    
                open_list.put(Puzzle_State(neighbour, puzzle_state.g_n + 1, h_n(neighbour, goal, heuristic_used)))
                open_list_len += 1
                
                
    
    if(is_monotone):
        print("monotone restriction is followed")
    else:
        print("monotone restriction is not followed")
    
    
    return closed_list, parent_list, optimal_path_cost, string_to_matrix_mapping
