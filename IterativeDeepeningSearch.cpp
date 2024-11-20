#include <iostream>
#include <unordered_map>
#include <vector>
#include <list>
#include <stack>
using namespace std;


void addEdge(int u, int v, int dir, unordered_map<int, list<int>>& adjList) {
    adjList[u].push_back(v);
    if (dir == 0) {
        adjList[v].push_back(u);
    }
}

void adjMatrix_to_adjList(vector<vector<int>> adjMatrix, unordered_map<int, list<int>>& adjList){
    int rows = adjMatrix.size();
    int cols = adjMatrix[0].size();
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            if(adjMatrix[i][j]==1)
            addEdge(i,j,1,adjList);
        }
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

void ids(const unordered_map<int, list<int>>& adjList, unordered_map<int, bool>& visited, vector<int>& ans, int node, int depthLimit) {
    stack<pair<int, int>> s;
    s.push({node, 0});

    while (!s.empty()) {
        int currentNode = s.top().first;
        int currentDepth = s.top().second;
        s.pop();
        if (!visited[currentNode]) {
            visited[currentNode] = true;
            ans.push_back(currentNode);
        }

        // If within depth limit, add adjacent nodes to stack
          if (currentDepth < depthLimit) {
            // Check if the node has any neighbors in the adjList
            if (adjList.find(currentNode) != adjList.end()) {
                for (const auto& neighbor : adjList.at(currentNode)) {
                    if (!visited[neighbor]) {
                        s.push({neighbor, currentDepth + 1});
                    }
                }
            }
        }
    }
}

void IDS(int nodes, const unordered_map<int, list<int>>& adjList, int maxDepth) {
    vector<int> ans;
    if(maxDepth==0){
        cout<<"depth zero return no node"<<endl;
        return;
    }
    // Iteratively deepen from depth 0 up to maxDepth
    for (int depth = 1; depth <= maxDepth; ++depth) {
        unordered_map<int, bool> visited;
        ids(adjList, visited, ans, 0, depth-1);
        cout << "IDS traversal of depth: "<<depth<<endl;
        for (const auto& node : ans) {
        cout << node << "\t";
        }
    cout<<endl;
    ans.clear();
    }

    
}


int main() {
   int nodes , edges;
   cout<<"enter number of nodes : ";
   cin>>nodes;
   cout<<"enter number of edges : ";
   cin>>edges;

    unordered_map<int, list<int>> adjList;
    for(int i=0;i<edges;i++){
        int node1,node2;
        cout<<"enter nodes in which you want the edge : "<<endl;
        cin>>node1;
        cin>>node2;
        addEdge(node1,node2,1,adjList);
    }
    int depth;
    cout << "Enter the maximum depth: ";
    cin >> depth;
    cout<<"printing adjList"<<endl;
    printAdj(adjList);
    cout<<endl;
    IDS(nodes, adjList,depth);
    return 0;
}
