#include <iostream>
#include <vector>
#include <array>

bool cmp(array<int, 4>& edge1, array<int, 4>& edge2){
    return edge1[3] < edge2[3];
}

struct SteinerForest{

    int V; // number of vertices
    vector<vector<pair<int, int>>> adjList; // adjacency list


    SteinerForest(int _v){
        V = _v;
        adjList = vector<vector<pair<int, int>>> (V+1);
    }

    void addEdge(array<int, 4> e){
        int u = e[0], v = e[1], cost = e[2];
        adj[u].push_back(make_pair(v, cost));
        adj[v].push_back(make_pair(u, cost));
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
                int newDist = f.first + adj.second;
                if (dist[adj.first] == -1) st.insert(make_pair(newDist, adj.first));
            }
        }

        return dist[t]; 
    }

};



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

        // setup edges
        SteinerForest sf(nVertex);
        for(int j = 0 ;j <= i; j++){
            st.addEdge(edge[j]);
        }

        // go Steiner Forest algorithm

        bool valid = 1;
        vector<bool> done(nTerminal);
        for(int k = 0; k < nTerminal; k++){

            // calculate every distance



        }


    }



}
