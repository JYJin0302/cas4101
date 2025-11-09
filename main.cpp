#include <iostream>
#include <vector>
#include <array>

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
        adj[u].push_back(array<int, 3>({v, cost, length}));
        adj[v].push_back(array<int, 3>({u, cost, length}));
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

    void setup0edge(int s, int t){
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
        vector<int> from(V+1, -1);
        for(int i = 1; i <= V; i++){
            if (dist[i] == -1) continue;
            for(auto adj : adjList[i]){
                if(dist[adj[0]] + adj[1] == dist[i]) from[i] = adj[0];
            }
        }

        int cur = t;
        vector<int> route;
        while(cur != s){
            route.push_back(cur);
            int nCur = from[cur];
            for(auto f : adjList[cur]){
                if (f[0] == nCur && dist[f[0]] + f[1] == dist[cur]){
                    // answer add
                    result.push_back({cur, ncur, f[1], f[2]});
                    break;
                }
            }
            cur = from[cur];
        }
        route.push_back(cur);

        for(int i = 1; i < (int)route.size(); i++){
            addEdge({route[i], route[i-1], 0, 0});
        }
    }

    void printResult(){
        cout << string(30, '-') << endl;
        cout << "Used Edges: " << endl;
        for(auto f : result){
            cout << f[0] << " <-> " << f[1] << ' ' << f[2] << ' ' << f[3] << endl;
        }
        cout << string(30, '-') << endl;
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

    int Budget;
    cin >> Budget;

    // algorithm 수행

    // sort edge by length  
    sort(edge.begin(), edge.end(), cmp);

    // try every length bound
    for(int i = 0; i < nEdge; i++){
        // use only 0~i edge

        // setup edges
        SteinerForest sf(nVertex);
        for(int j = 0; j <= i; j++){
            st.addEdge(edge[j]);
        }

        // go Steiner Forest algorithm

        int totalCost = 0;

        bool valid = 1;
        vector<bool> done(nTerminal);
        for(int k = 0; k < nTerminal && valid; k++){
            // calculate every distance

            int minDistance = 10101010;
            int minPair = -1;

            for(int t = 0; t < nTerminal; t++){
                if (done[t]) continue;

                int D = sf.getMinimumDistance(terminal[t].first, terminal[t].second);
                if (D == -1){
                    valid = 0;
                    break;
                }

                minDistance = min(minDistance, D);
                if (minDistance == D){
                    minPair = t;
                }
            }

            done[minPair] = 1;
            totalCost += minDistance;
            sf.setup0edge(terminal[minPair.x], terminal[minPair.y]);
        }

        if (valid && totalCost <= 2*Budget){
            // found
            cout << "Solution Found "<< endl;
            // print answer here
            sf.printResult();

            return 0;
        }
    }

    cout << "INFEASIBLE" << endl;
    return 0;
}
