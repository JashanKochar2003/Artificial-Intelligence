#include <iostream>
#include <unordered_map>
#include <vector>
#include <list>
#include<stack>
#include <queue>

using namespace std;

void addEdge(int u, int v, int dir, unordered_map<int, list<int>>& adjList) {
    adjList[u].push_back(v);
    if (dir == 0) {
        adjList[v].push_back(u);
    }
}

void printAdj(const unordered_map<int, list<int>>& adjList) {
    for (const auto& i : adjList) {
        cout << i.first << " -> ";
        for (const auto& j : i.second) {
            cout << j << "\t";
        }
        cout << endl;
    }
}

void bfs(const unordered_map<int, list<int>>& adjList, unordered_map<int, bool>& visited, vector<int>& ans, int node) {
    queue<int> q;
    q.push(node);
    visited[node] = true;

    while (!q.empty()) {
        int frontNode = q.front();
        q.pop();

        ans.push_back(frontNode);
         if (adjList.find(frontNode) != adjList.end()){
        for (const auto& i : adjList.at(frontNode)) {
            if (!visited[i]) {
                q.push(i);
                visited[i] = true;
            }
        }
    }
}
}

vector<int> BFS(int nodes, const unordered_map<int, list<int>>& adjList,int start) {
    vector<int> ans;
    unordered_map<int, bool> visited;
    bfs(adjList,visited,ans,start);

    for (int i = 0; i < nodes; ++i) {
        if (!visited[i]) {
            bfs(adjList, visited, ans, i);
        }
    }
    return ans;
}

void dfs(const unordered_map<int, list<int>>& adjList, unordered_map<int, bool>& visited, vector<int>& ans, int node) {
    stack<int> s;
    s.push(node);

    while (!s.empty()) {
        int currentNode = s.top();
        s.pop();

        if (!visited[currentNode]) {
            visited[currentNode] = true;
            ans.push_back(currentNode);

            // Push all adjacent nodes to the stack
             if (adjList.find(currentNode) != adjList.end()){
            for (const auto& neighbor : adjList.at(currentNode)) {
                if (!visited[neighbor]) {
                    s.push(neighbor);
                }
            }
        }
    }
}
}

vector<int> DFS(int nodes, const unordered_map<int, list<int>>& adjList,int start) {
    vector<int> ans;
    unordered_map<int, bool> visited;

    dfs(adjList,visited,ans,start);
    for (int i = 0; i < nodes; ++i) {
        if (!visited[i]) {
            dfs(adjList, visited, ans, i);
        }
    }
    return ans;
}

int main() {
    unordered_map<int, list<int>> adjList;
    int n;
    int m;
    int dir;
    cout << "Enter number of nodes: ";
    cin >> n;
    cout << "Enter number of edges: ";
    cin >> m;
    cout << "Enter 1 for directed and 0 for undirected graph: ";
    cin >> dir;

    for (int i = 0; i < m; ++i) {
        cout << "Enter vertices for edge " << i + 1 << ": ";
        int p, q;
        cin >> p >> q;
        if (p >= n || q >= n || p < 0 || q < 0) {
            cout << "Entered vertices are out of range. Please enter again." << endl;
            --i; // Decrement to repeat this iteration
        } else {
            addEdge(p, q, dir, adjList);
        }
    }

    printAdj(adjList);
    int start ;
    cout<<"enter starting node : "<<endl;
    cin>>start;
    int choice;
    cout<<"enter 1 for BFS and 2 for DFS :"<<endl;
    cin>>choice;
    if(choice==1){
    vector<int> ans = BFS(n, adjList,start);
    cout << "BFS traversal: ";
    for (const auto& node : ans) {
        cout << node << "\t";
    }
    }
    else if(choice==2){
        vector<int> ans = DFS(n, adjList,start);
        cout<<"DFS traversal : ";
        for (const auto& node : ans) {
        cout << node << "\t";
    }
    }
    else{
        cout<<"INVALID CHOICE"<<endl;
    }
    return 0;
}
