AI Lab

Prince Jha
Ranjeet Kichar 
Sahil Jain



(base) prince@sriparna-SSA720TR-34L:~/AI_lab/Assign2$  python eight_puzzle.py "/home/prince/AI_lab/Assign2/input/start_state.txt" "/home/prince/AI_lab/Assign2/input/end_state.txt"
Enter Hueristic type:
1. h1(n) = number of tiles displaced from their destined position.
2. h2(n) = sum of Manhattan distance of each tile from the goal
3. h(n) = 0 Zero heuristic
4. h3(n) = sum of Eucldian distance of each tile from the goal
1
monotone restriction is not followed
Start State:
T8 T7 T6
T1 B T5
T2 T3 T4
Get the Solution
Goal State:
T1 T2 T3
T8 B T4
T7 T6 T5
Total number of states explored: 108984
Total number of states to Optimal Path: 29
Optimal Path Cost: 28
Time taken: 13.404386520385742

(base) prince@sriparna-SSA720TR-34L:~/AI_lab/Assign2$  python eight_puzzle.py "/home/prince/AI_lab/Assign2/input/start_state.txt" "/home/prince/AI_lab/Assign2/input/end_state.txt"
Enter Hueristic type:
1. h1(n) = number of tiles displaced from their destined position.
2. h2(n) = sum of Manhattan distance of each tile from the goal
3. h(n) = 0 Zero heuristic
4. h3(n) = sum of Eucldian distance of each tile from the goal
2
monotone restriction is followed
Start State:
T8 T7 T6
T1 B T5
T2 T3 T4
Get the Solution
Goal State:
T1 T2 T3
T8 B T4
T7 T6 T5
Total number of states explored: 27227
Total number of states to Optimal Path: 29
Optimal Path Cost: 28
Time taken: 4.326514482498169

(base) prince@sriparna-SSA720TR-34L:~/AI_lab/Assign2$  python eight_puzzle.py "/home/prince/AI_lab/Assign2/input/start_state.txt" "/home/prince/AI_lab/Assign2/input/end_state.txt"
Enter Hueristic type:
1. h1(n) = number of tiles displaced from their destined position.
2. h2(n) = sum of Manhattan distance of each tile from the goal
3. h(n) = 0 Zero heuristic
4. h3(n) = sum of Eucldian distance of each tile from the goal
3
monotone restriction is followed
Start State:
T8 T7 T6
T1 B T5
T2 T3 T4
Get the Solution
Goal State:
T1 T2 T3
T8 B T4
T7 T6 T5
Total number of states explored: 181273
Total number of states to Optimal Path: 29
Optimal Path Cost: 28
Time taken: 22.15859365463257

(base) prince@sriparna-SSA720TR-34L:~/AI_lab/Assign2$  python eight_puzzle.py "/home/prince/AI_lab/Assign2/input/start_state.txt" "/home/prince/AI_lab/Assign2/input/end_state.txt"
Enter Hueristic type:
1. h1(n) = number of tiles displaced from their destined position.
2. h2(n) = sum of Manhattan distance of each tile from the goal
3. h(n) = 0 Zero heuristic
4. h3(n) = sum of Eucldian distance of each tile from the goal
4
monotone restriction is followed
Start State:
T8 T7 T6
T1 B T5
T2 T3 T4
Get the Solution
Goal State:
T1 T2 T3
T8 B T4
T7 T6 T5
Total number of states explored: 7532
Total number of states to Optimal Path: 31
Optimal Path Cost: 30
Time taken: 1.241462230682373




Q1) Observe and verify that better heuristics expands lesser states

Answer:
It can be seen from above example better heuristic expands lesser states from the following
h_4>h_2>h_3>h_1

Q2)Observe and verify that all the states expanded by better heuristics should
also be expanded by inferior heuristics.
Answer:
It can also be included from above

Q3)Observe and verify monotone restriction on the heuristics.

for h1,h2 monotone is not followed
for h3,h4 monotone is followed


Q4)Observe un-reachability and provide a proof.

refer : https://www.geeksforgeeks.org/check-instance-8-puzzle-solvable/

if no of inversions are even then it is reachable otherwise unreachable


Q6)Observe and verify that if the cost of the empty tile is added (considering
empty tile as another tile) then monotonicity will be violated.

it will be violated 
