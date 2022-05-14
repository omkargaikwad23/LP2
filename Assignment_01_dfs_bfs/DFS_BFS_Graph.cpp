#include <bits/stdc++.h>
using namespace std;

class Graph{
    int N;
    vector<int> *graph;
public:
    Graph(int N){
        this->N = N;
        graph = new vector<int>[N];
    }

    void addEdge(int u, int v){
        graph[u].push_back(v);
    }

    void DFS(int start, vector<bool>& visited){
        if(visited[start]) return;
        visited[start] = true;
        cout << start << " ";
        for(auto& adj : graph[start]){
            DFS(adj, visited);
        }
    }

    void BFS(int start){
        vector<int> traversal;
        queue<int> q;
        q.push(start);
        vector<bool> visited(N+1, false);
        visited[start] = true;
        while(!q.empty()){
            int curNode = q.front();
            traversal.push_back(curNode);
            q.pop();
            for(int adjNode : graph[curNode]){
                if(visited[adjNode]) continue;
                visited[adjNode] = true;
                q.push(adjNode);
            }
        }
        for(auto node : traversal){
            cout << node << " ";
        }
    }
};

int main(){
    int N, E, u, v; 
    cout << "Enter number of nodes: "; cin >> N;
    cout << "Enter number of edges: "; cin >> E;

    Graph g(N);
    cout << "Enter the edges:\n";
    for(int e=0; e<E; e++){
        cin >> u >> v;
        g.addEdge(u, v);
    }
    vector<bool> visited(N, false);
    cout << "\nDFS traversal\n";
    g.DFS(0, visited);

    cout << "\nBFS traversal\n";
    g.BFS(0);
}

/*
Enter number of nodes: 5
Enter number of edges: 6
Enter the edges:
0 1
0 2
1 3
2 3
2 4
4 3

DFS traversal
0 1 3 2 4
BFS traversal
0 1 2 3 4
*/