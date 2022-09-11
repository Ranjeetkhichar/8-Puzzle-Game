#include <bits/stdc++.h>
#include <fstream>

#define STATE vector<vector<int>>

using namespace std;


// structure to store summary for a heuristic
struct Summary{
    int n;                          // heuristic number
    int statesExplored;
    int statesInOptimalPath;
    int optimalPathCost;
    double timeTaken;
    bool monotonicity;
    set<STATE> close_list;
};


// class for Astar
class Astar
{
    private:
    STATE fstate;       // initial state
    STATE istate;       // final state

    int n;          // heuristic number

    priority_queue<pair<int, STATE>, vector<pair<int, STATE>>, greater<pair<int, STATE>>> pq;
    map<STATE, int> g;
    map<STATE, STATE> parent;
    set<STATE> close_list, open_list;
    bool monotonicity;

    public:

    // loading initial state from file
    void setiState()
    {
        ifstream fin;
        fin.open("./input/initial.txt");

        istate.resize(3,vector<int>(3));
        for(int i = 0; i < 3; ++i)
            for(int j = 0; j < 3; ++j)
                fin >> istate[i][j];
        fin.close();
    }

    // loading final state from file
    void setfState()
    {
        ifstream fin;
        fin.open("./input/final.txt");

        fstate.resize(3,vector<int>(3));
        for(int i = 0; i < 3; ++i)
            for(int j = 0; j < 3; ++j)
                fin >> fstate[i][j];
        fin.close();
    }

    // constructoe
    Astar(int n)
    {
        this->n = n;
        setiState();
        setfState();
    }

    // calculating heuristic for given state
    int h(STATE &cstate)
    {
        // h1(n) = 0
        if (n == 0)
            return 0;

        // h2(n) = number of tiles displaced from their destined position
        else if (n == 1)
        {
            int count = 0;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    if (cstate[i][j] != fstate[i][j])
                    // if (cstate[i][j] != fstate[i][j] && cstate[i][j] != 0)
                        ++count;
            return count;
        }
        else
        {
            int sum = 0;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                {
                    for (int i1 = 0; i1 < 3; ++i1)
                    {
                        for (int j1 = 0; j1 < 3; ++j1)
                        {
                            if (cstate[i][j] == fstate[i1][j1])
                            // if (cstate[i][j] == fstate[i1][j1] && cstate[i][j] != 0)
                            {
                                // h3(n) = h3(n) = sum of Manhattan distance of each tiles from the goal position
                                if (n == 2)
                                    sum += abs(i - i1) + abs(j - j1);

                                // h3(n) = h3(n) = sum of Euclidean distance of each tiles from the goal position
                                else
                                    sum += sqrt(pow(i - i1, 2) + pow(j - j1, 2));
                                i1 = -1;
                                break;
                            }
                        }
                        if (i1 == -1)
                            break;
                    }
                }
            return sum;
        }
    }

    // find and return neighbours of current state
    vector<STATE> neighbours(STATE &cstate)
    {
        int src = 0;
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                if (cstate[i][j] == 0)
                {
                    src = i * 3 + j;
                    i = -1;
                    break;
                }
            }
            if (i == -1)
                break;
        }

        int i = src / 3;
        int j = src % 3;

        int dirx[] = {-1, 1, 0, 0};
        int diry[] = {0, 0, -1, 1};

        vector<STATE> neigh;

        for (int d = 0; d < 4; ++d)
        {
            int ni = i + dirx[d];
            int nj = j + diry[d];

            if (ni >= 0 && ni < 3 && nj >= 0 && nj < 3)
            {
                STATE x = cstate;
                swap(x[i][j], x[ni][nj]);
                neigh.push_back(x);
            }
        }

        return neigh;
    }

    void printState(STATE &s)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                cout << s[i][j] << " ";
            }
            cout << "\n";
        }
        cout<<"\n";
    }

    void printSuccess()
    {
        char heuristic[4][100] = {"h1(n) = 0",
                            "h2(n) = number of tiles displaced from their destined position.",
                            "h3(n) = sum of Manhattan distance of each tiles from the goal position.",
                            "h4(n) = sum of Euclidean distance of each tiles from the goal position."};
        printf("\n\n-----------------------------------------------------------------------------------\n");
        printf("Heruistic used --> %s\n", heuristic[n]);
        printf("-----------------------------------------------------------------------------------\n");

        printf("\nGoal State Found :)\n\nStart state :\n");
        printState(istate);

        printf("Goal State :\n");
        printState(fstate);

        printf("Total no. of states explored : %d\n", close_list.size());
        printf("Total no. of states to optimal path : %d\n", g[fstate]+1);

        printf("\nOptimal Path : \n\n");

        STATE cstate = fstate;
        while (parent[cstate] != cstate)
        {
            printState(cstate);
            cout << "  ^\n  |\n\n";
            cstate = parent[cstate];
        }
        printState(cstate);

        printf("Optimal Path Cost : %d\n",g[fstate]);
    }

    void printFailure()
    {
        char heuristic[4][100] = {"h1(n) = 0",
                            "h2(n) = number of tiles displaced from their destined position.",
                            "h3(n) = sum of Manhattan distance of each tiles from the goal position.",
                            "h4(n) = sum of Euclidean distance of each tiles from the goal position."};
        printf("\n\n-----------------------------------------------------------------------------------\n");
        printf("Heruistic used --> %s\n", heuristic[n]);
        printf("-----------------------------------------------------------------------------------\n");

        printf("\nState NOT Found :)\n\nStart state :\n");
        printState(istate);

        printf("Goal State :\n");
        printState(fstate);

        printf("Total no. of states explored : %d\n", close_list.size());   
    }

    Summary run()
    {
        clock_t start, end;
        
        start = clock();
        bool res = astar();
        end = clock();
        
        Summary s;
        s.n = n;
        s.timeTaken = double(end - start) / double(CLOCKS_PER_SEC);
        s.optimalPathCost = g[fstate];
        s.statesExplored = close_list.size();
        s.statesInOptimalPath = g[fstate]+1;
        s.monotonicity = monotonicity;
        s.close_list = close_list;

        if(res)
            printSuccess();
        else
            printFailure();

        printf("Time taken for execution : %5lf\n",s.timeTaken);

        return s;
    }

    // astar function
    bool astar()
    {
        monotonicity = true;
        STATE cstate = istate;

        pq.push({0 + h(cstate), cstate});
        g[cstate] = 0;
        parent[cstate] = cstate;

        while (!pq.empty())
        {
            int dist = pq.top().first;
            cstate = pq.top().second;
            pq.pop();
            open_list.erase(cstate);

            if(close_list.find(cstate) != close_list.end())
                continue;

            close_list.insert(cstate);

            if (cstate == fstate)
                return true;

            auto neigh = neighbours(cstate);
            for (STATE s : neigh)
            {
                if (g.find(s) == g.end() || g[s]+h(s) > dist + 1)
                {
                    if (g.find(s) == g.end())
                        open_list.insert(s);
                    g[s] = g[cstate] + 1;
                    pq.push({g[s] + h(s), s});

                    parent[s] = cstate;

                    if (h(cstate) > 1 + h(s))
                        monotonicity = false;
                }
            }
        }

        return false;
    }
};

void printSummary(vector<Summary> &s)
{
    printf("\n\n");
    printf("+-----------+-----------------+-------------------+-----------------+-------------------+\n");
    printf("| Heruistic | States Explored | Optimal Path Cost | Time Taken(sec) |    Monotonocity   |\n");
    printf("+-----------+-----------------+-------------------+-----------------+-------------------+\n");

    for(int i = 0; i < s.size(); ++i)
    {
        printf("|     h%d    ",s[i].n+1);
        printf("|%15d  ",s[i].statesExplored);
        printf("|%17d  ",s[i].optimalPathCost);
        printf("|%15lf  ",s[i].timeTaken);

        if(s[i].monotonicity)
            printf("|      Followed     |\n");
        else
            printf("|    Not Followed   |\n");
        
        printf("+-----------+-----------------+-------------------+-----------------+-------------------+\n");
    }
}

// checking if inferior heuristics explore more number of states than superior heuristics
void checkExploration(vector<Summary> &s)
{
    set<STATE> h3_explored = s[2].close_list;
    
    int flag = 1;
    for(int i = 0; flag && i < 4; ++i)
    {
        if(i == 2)
            continue;

        for(auto it = h3_explored.begin(); it != h3_explored.end(); ++it)
        {
            if(s[i].close_list.find(*it) == s[i].close_list.end())
            {
                flag = 0;
                break;
            }
        }
    }

    if(flag)
    {
        printf("\nAll states explored by h3 are also explored by h1, h2 and h4.");
        printf("\nHence verified that all the states expanded by better heuristics should also be expanded by inferior heuristics.");
    }
    else
    {
        printf("\nAll states explored by h3 are NOT explored by h1, h2 and h4");
    }
}

int main()
{
    vector<Summary> s;

    for (int n = 0; n < 4; n++)
    {
        Astar obj(n);
        s.push_back(obj.run());
    }

    printSummary(s);
    checkExploration(s);

    return 0;
}