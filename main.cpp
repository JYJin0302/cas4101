#include <iostream>
#include <vector>
#include <array>

bool cmp(array<int, 4>& edge1, array<int, 4>& edge2){
    return edge1[3] < edge2[3];
}

int main(){

    // 입력
    int nVertex, int nEdge;
    std::cin >> nVertex >> nEdge;

    std::vector<array<int, 4>> edge;
    for(int i = 0; i < nEdge; i++){
        int u, v, cost, length;
        cin >> u >> v >> cost >> length;
        edge.push_back({u, v, cost, length});
    }

    int nTerminal;
    cin >> nTerminal;
    std::vector<pair<int, int>> terminal;
    for(int i = 0; i < nTerminal; i++){
        int s, t;
        cin >> s >> t;
        terminal.push_back(make_pair(s, t));
    }

    // algorithm 수행

    // sort edge by length  
    sort(edge.begin(), edge.end(), cmp);

    // try every length bound
    for(int i = 0; i < nEdge; i++){
        // use only 0~i edge

        

    }



}
