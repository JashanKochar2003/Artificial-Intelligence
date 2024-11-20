#include<iostream>
#include<unordered_map>
#include<vector>
#include<list>
#include<stack>
#include<queue>
using namespace std ;



class graph {
    public:
    unordered_map<int,list<int>> adjList;
    
    void addEdge(int u, int v , int dir){
        adjList[u].push_back(v);
        if(dir == 0)
        adjList[v].push_back(u);
    }

    void printGraph(){
        for(auto i : adjList){
            cout<<i.first<<" -> ";
            for(auto j:i.second){
                cout<<j<<"\t";
            }
            cout<<endl;
        }
    }
};

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
            for (const auto& neighbor : adjList.at(currentNode)) {
                if (!visited[neighbor]) {
                    s.push(neighbor);
                }
            }
        }
    }
}

vector<int> DFS(int nodes, const unordered_map<int, list<int>>& adjList) {
    vector<int> ans;
    unordered_map<int, bool> visited;

    for (int i = 0; i < nodes; ++i) {
        if (!visited[i]) {
            dfs(adjList, visited, ans, i);
        }
    }
    return ans;
}

void bfs(const unordered_map<int, list<int>>& adjList, unordered_map<int, bool>& visited, vector<int>& ans, int node) {
    queue<int> q;
    q.push(node);
    visited[node] = true;

    while (!q.empty()) {
        int frontNode = q.front();
        q.pop();

        ans.push_back(frontNode);
        for (const auto& i : adjList.at(frontNode)) {
            if (!visited[i]) {
                q.push(i);
                visited[i] = true;
            }
        }
    }
}

vector<int> BFS(int nodes, const unordered_map<int, list<int>>& adjList) {
    vector<int> ans;
    unordered_map<int, bool> visited;

    for (int i = 0; i < nodes; ++i) {
        if (!visited[i]) {
            bfs(adjList, visited, ans, i);
        }
    }
    return ans;
}

void beam(const std::unordered_map<int, std::list<int>>& adjList, std::unordered_map<int, bool>& visited, std::vector<int>& ans, int node, int width) {
    std::queue<int> q;
    int processed = 0;
    q.push(node);
    processed++;
    visited[node] = true;

   

    while (!q.empty() && processed < width) {
        int frontNode = q.front();
        q.pop();

        ans.push_back(frontNode);
        processed++;

        for (const auto& i : adjList.at(frontNode)) {
            if (!visited[i]  && processed < width) {
                q.push(i);
                processed++;
                visited[i] = true;
            }
        }
    }
}

vector<int> BEAM(int nodes,unordered_map<int, list<int>>& adjList,int &width) {
    vector<int> ans;
    unordered_map<int, bool> visited;

    for (int i = 0; i < nodes; ++i) {
        if (!visited[i]) {
            beam(adjList, visited, ans, i,width);
        }
    }
    return ans;
}


int main() {
    graph g;
    int n;
    int m;
    int dir;
    int width = 3;
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
            g.addEdge(p, q, dir);
        }
    }

    g.printGraph();
    vector<int> ans1 = DFS(n, g.adjList);
    cout << "DFS traversal: ";
    for (const auto& node : ans1) {
        cout << node << "\t";
    }
    cout<<endl;
    vector<int> ans2 = BEAM(n, g.adjList,width);
    cout << "Beam traversal: ";
    for (const auto& node : ans2) {
        cout << node << "\t";
    }
    return 0;
}