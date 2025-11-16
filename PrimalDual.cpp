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


int main(){

    // 입력
    int nVertex, nEdge;
    cin >> nVertex >> nEdge;

    vector<array<int, 4>> edge;
    for(int i = 0; i < nEdge; i++){
        int u, v, cost, length;
        cin >> u >> v >> cost >> length;
        edge.push_back({u, v, cost, length});
    }

    int nTerminal;
    cin >> nTerminal;
    vector<vector<int>> terminal;
    for(int i = 0; i < nTerminal; i++){
        int s, t;
        cin >> s >> t;
        terminal.push_back({s, t});
    }

    int Budget;
    cin >> Budget;

    // cout << "input done "<< endl;
    // algorithm 수행

    // sort edge by length  
    sort(edge.begin(), edge.end(), cmp);

    
    int nTerminals = nTerminal * 2;
    int *terminals = new int [nTerminals];
    int tIndex = 0;
    for(int i=0; i < nTerminal; i++){
        terminals[tIndex++]= terminal[i][0] - 1;
        terminals[tIndex++]= terminal[i][1] - 1;
    }

    // try every length bound
    for(int i = 0; i < nEdge; i++){
        // use only 0~i edge

        cout << "bound: " << i << endl;

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

        // go Steiner Forest algorithm
        int initialSolution = 0;
        int cleanedSolution = 0;
        int totalCost = PrimalDualAlgorithm(nVertex, nEdges, nTerminals, terminals, adjMatrix, terminal, E,cleanedSolution,initialSolution);

        cout << "ResulT: " << i << ' '<< totalCost << endl;
        bool valid = 1;

        if (valid && totalCost <= 2*Budget){
            // found
            cout << "Solution Found "<< endl;
            // print answer here
            cout << "Total cost: " << totalCost << endl;
            cout << "Budget: "<< Budget<< endl;
        }
    }

    cout << "INFEASIBLE" << endl;
    return 0;
}
