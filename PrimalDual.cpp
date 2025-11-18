#include "PD-SF.hpp"

#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <set>

using namespace std;

bool cmp(array<int, 4>& edge1, array<int, 4>& edge2){
    return edge1[3] < edge2[3];
}

struct SteinerForest{

    int V; // number of vertices
    vector<vector<array<int, 3>>> adjList; // adjacency list
    vector<array<int, 4>> result;

    SteinerForest(int _v){
        V = _v;
        adjList = vector<vector<array<int, 3>>> (V+1);
    }

    void addEdge(array<int, 4> e){
        int u = e[0], v = e[1], cost = e[2], length = e[3];
        adjList[u].push_back(array<int, 3>({v, cost, length}));
        adjList[v].push_back(array<int, 3>({u, cost, length}));
    }

    int getMinimumDistance(int s, int t){
        // dijkstra algorithm
        // returns -1 if disconnected
        vector<int> dist(V+1, -1);
        set<pair<int, int>> st;
        st.insert(make_pair(0, s));
        while(!st.empty()){
            auto f = *st.begin();
            st.erase(st.begin());

            if (dist[f.second] != -1) continue;
            dist[f.second] = f.first;

            for(auto adj : adjList[f.second]){
                int newDist = f.first + adj[1];
                if (dist[adj[0]] == -1) st.insert(make_pair(newDist, adj[0]));
            }
        }
        return dist[t]; 
    }
};


int main(){

    // 입력
    int nVertex, nEdge;
    cin >> nVertex >> nEdge;

    vector<array<int, 4>> edge;
    for(int i = 0; i < nEdge; i++){
        int u, v, cost, length;
        cin >> u >> v >> cost >> length;
        edge.push_back({u, v, cost, length});
        //cout << u << ' ' << v << ' '<< cost << ' ' << length << endl;
    }

    int nTerminal;
    cin >> nTerminal;
    cout << nTerminal << endl;
    vector<vector<int>> terminal;
    for(int i = 0; i < nTerminal; i++){
        int s, t;
        cin >> s >> t;
        terminal.push_back({s, t});
    }
    int Budget;
    cin >> Budget;

    // algorithm 수행

    // sort edge by length  
    sort(edge.begin(), edge.end(), cmp);

    
    int nTerminals = nTerminal * 2;
    int *terminals = new int [nTerminals];
    int tIndex = 0;
    for(int i=0; i < nTerminal; i++){
        terminals[tIndex++]= terminal[i][0];
        terminals[tIndex++]= terminal[i][1];
    }

    // try every length bound
    for(int i = 0; i < nEdge; i++){
        // use only 0~i edge

       // cout << "bound: " << i << endl;cout << "new edge: " << edge[i][0] << ' '<< edge[i][1]<<" " << edge[i][2] << endl;

        // setup arguments;

        int nEdges = i+1;
        vector<vector<int>> E;

        vector<vector<int>> adjMatrix;
        vector<int> tempAdjVec (nVertex,0);
        for (int i=0; i<nVertex; i++)
            adjMatrix.push_back(tempAdjVec);

        for(int j = 0; j <= i; j++){
            E.push_back({edge[j][0] - 1, edge[j][1] - 1});
            adjMatrix[edge[j][0]-1][edge[j][1]-1] = edge[j][2];
            adjMatrix[edge[j][1]-1][edge[j][0]-1] = edge[j][2];
        }
        cout << "Setup done" << endl;

        // go Steiner Forest algorithm
        int initialSolution = 0;
        int cleanedSolution = 0;
        vector<vector<int>> solution;
        PrimalDualAlgorithm(nVertex, nEdges, nTerminals, terminals, adjMatrix, terminal, E,cleanedSolution,initialSolution, solution);

        cout << "ResulT: " << i << ' '<< cleanedSolution << endl;
        // bool valid = 1;

        if (cleanedSolution != -1 && cleanedSolution <= 2*Budget){
            // found
            cout << "Solution Found "<< endl;
            // print answer here
            cout << "Total cost: " << cleanedSolution << endl;
            cout << "Budget: "<< Budget<< endl;

            SteinerForest st(nVertex);
            

            for(auto f : solution){
                int v = f[0] + 1;
                int u = f[1] + 1;
                int cost = f[2] + 1;
                //cout << "Fi9nd : " << v << ' ' << u << ' '<< cost << endl;
                for(auto e : edge){
                    if (((e[0] == v && e[1] == u) || (e[0] == u && e[1] == v))){
                        //cout << "ADD edge: " << e[0] << ' '<< e[1] << ' ' << e[2] << ' ' << e[3] << '\n';
                        st.addEdge(e);
                        break;
                    }
                }    
            }

            int minV = 0;
            for(int i=0 ; i < nTerminal; i++){
                int s = terminal[i][0];
                int t = terminal[i][1];

                minV = max(minV, st.getMinimumDistance(s, t));
            }
            cout << "Distance: " << minV << '\n';

            return 0;
        }

        //cout<<"--------------------------------------------"<<endl<< endl;
    }

    cout << "INFEASIBLE" << endl;
    return 0;
}
