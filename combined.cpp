#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <set>
#include <queue>
#include <list>
#include <climits>
#include <stack>

using namespace std;


class Node {
public:
    int nodeNumber;
    int h;
    int g;
    int f;
    Node* parent;

    Node(int hValue, int i) : h(hValue), nodeNumber(i), g(0), f(h + g), parent(nullptr) {}

    bool operator>(const Node& other) const {
        return f > other.f;
    }
};

class graph {
public:
    vector<Node> nodes;

    graph(int size, int hValue[]) {
        for (int i = 0; i < size; i++) {
            nodes.emplace_back(hValue[i], i);
        }
    }
};


void reconstructPath(Node* goal) {
    vector<Node*> path;
    for (Node* node = goal; node != nullptr; node = node->parent) {
        path.push_back(node);
    }
    reverse(path.begin(), path.end());
    cout << "Path: ";
    for (Node* node : path) {
        cout << char(node->nodeNumber + 65) << "\t";
    }
    cout << endl;
}

vector<Node*> getSuccessors(Node* current, int adjMatrix[10][10], graph& g) {
    vector<Node*> successors;

    for (int i = 0; i < 10; i++) {
        if (adjMatrix[current->nodeNumber][i] > 0) {
            Node* successor = &g.nodes[i];
            successors.push_back(successor);
        }
    }
    return successors;
}

void aStar(int adjMatrix[10][10], int startIndex, int goal, graph& g) {
    auto cmp = [](Node* left, Node* right) { return *left > *right; };
    priority_queue<Node*, vector<Node*>, decltype(cmp)> open(cmp);
    set<Node*> closed;
    vector<Node*> allNodes;

    Node* start = &g.nodes[startIndex];
    open.push(start);
    allNodes.push_back(start);

    while (!open.empty()) {
        Node* curr = open.top();
        open.pop();

        if (curr->nodeNumber == goal) {
            reconstructPath(curr);
            return;
        }

        closed.insert(curr);

        vector<Node*> successors = getSuccessors(curr, adjMatrix, g);

        for (Node* successor : successors) {
            if (closed.find(successor) != closed.end()) {
                continue;
            }

            int tentative_g = curr->g + adjMatrix[curr->nodeNumber][successor->nodeNumber];

            if (find(allNodes.begin(), allNodes.end(), successor) == allNodes.end() || tentative_g < successor->g) {
                successor->g = tentative_g;
                successor->f = successor->g + successor->h;
                successor->parent = curr;

                if (find(allNodes.begin(), allNodes.end(), successor) == allNodes.end()) {
                    open.push(successor);
                    allNodes.push_back(successor);
                } else {
                    open.push(successor);  // In case it's already in the queue but with a higher f-value
                }
            }
        }
    }

    cout << "No path found" << endl;
}


void bsf(int adjMatrix[10][10], vector<bool>& visited, vector<int>& ans, int startIndex) {
    priority_queue<pair<int, pair<int, int>>> pq;
    pq.push(make_pair(INT_MAX, make_pair(startIndex, startIndex)));
    int count = 0;
    while (!pq.empty()) {
        auto [cost, nodePair] = pq.top();
        int startNode = nodePair.first;
        int currentNode = nodePair.second;
        pq.pop();

        if (!visited[currentNode]) {
            visited[currentNode] = true;
            ans.push_back(currentNode);

            //if (currentNode == 27) break;

            for (int nextNode = 0; nextNode < 10; ++nextNode) {
                if (adjMatrix[currentNode][nextNode] > 0 && !visited[nextNode]) {
                    pq.push(make_pair(adjMatrix[currentNode][nextNode], make_pair(currentNode, nextNode)));
                }
            }
            count++;
        }
    }
}

// Beam Search algorithm
void beam_constant_width(const unordered_map<int, list<int>>& adjList, unordered_map<int, bool>& visited, vector<int>& ans, int node, int beamWidth, int adjMatrix[10][10]) {
    queue<int> q;
    q.push(node);
    visited[node] = true;

    while (!q.empty()) {
        int frontNode = q.front();
        q.pop();
        ans.push_back(frontNode);
        int count = 0;

        
        vector<pair<int, int>> neighbors;

        
        if (adjList.find(frontNode) != adjList.end()) {
            for (const auto& neighbor : adjList.at(frontNode)) {
                if (!visited[neighbor]) {
                   
                    neighbors.push_back({neighbor, adjMatrix[frontNode][neighbor]});
                }
            }

            
            sort(neighbors.begin(), neighbors.end(), [](pair<int, int>& a, pair<int, int>& b) {
                return a.second < b.second;
            });

            
            for (const auto& neighbor : neighbors) {
                if (count < beamWidth) {
                    q.push(neighbor.first);
                    visited[neighbor.first] = true;
                    count++;
                } else {
                    break; // Only consider up to 'beamWidth' nodes
                }
            }
        }
    }
}

// Iterative Deepening Search algorithm (IDS)
void ids(const unordered_map<int, list<int>>& adjList, unordered_map<int, bool>& visited, vector<int>& ans, int node, int depthLimit, int adjMatrix[10][10]) {
    
    auto cmp = [&](int left, int right) { return adjMatrix[left][node] > adjMatrix[right][node]; };
    priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);
    
    pq.push(node);
    
    while (!pq.empty()) {
        int currentNode = pq.top();
        pq.pop();

        
        if (!visited[currentNode]) {
            visited[currentNode] = true;
            ans.push_back(currentNode);
        }

        
        if (ans.size() <= depthLimit) {
            if (adjList.find(currentNode) != adjList.end()) {
                for (const auto& neighbor : adjList.at(currentNode)) {
                    if (!visited[neighbor]) {
                        pq.push(neighbor);
                    }
                }
            }
        }
    }
}

void IDS(int nodes, const unordered_map<int, list<int>>& adjList, int maxDepth, int adjMatrix[10][10]) {
    vector<int> ans;
    if (maxDepth == 0) {
        cout << "Depth zero, no nodes to traverse" << endl;
        return;
    }
    
    for (int depth = 1; depth <= maxDepth; ++depth) {
        unordered_map<int, bool> visited;
        ans.clear();
        ids(adjList, visited, ans, 0, depth - 1, adjMatrix);
        cout << "IDS traversal of depth: " << depth << endl;
        for (const auto& node : ans) {
            cout << char(node+65) << "\t";
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

        if (adjList.find(frontNode) != adjList.end()) {
            for (const auto& i : adjList.at(frontNode)) {
                if (!visited[i]) {
                    q.push(i);
                    visited[i] = true;
                }
            }
        }
    }
}

vector<int> BFS(int nodes, const unordered_map<int, list<int>>& adjList, int start) {
    vector<int> ans;
    unordered_map<int, bool> visited;
    bfs(adjList, visited, ans, start);

    for (int i = 0; i < nodes; ++i) {
        if (!visited[i]) {
            bfs(adjList, visited, ans, i);
        }
    }
    return ans;
}

// Depth-First Search (DFS)
void dfs(const unordered_map<int, list<int>>& adjList, unordered_map<int, bool>& visited, vector<int>& ans, int node) {
    stack<int> s;
    s.push(node);

    while (!s.empty()) {
        int currentNode = s.top();
        s.pop();

        if (!visited[currentNode]) {
            visited[currentNode] = true;
            ans.push_back(currentNode);

            if (adjList.find(currentNode) != adjList.end()) {
                for (const auto& neighbor : adjList.at(currentNode)) {
                    if (!visited[neighbor]) {
                        s.push(neighbor);
                    }
                }
            }
        }
    }
}

vector<int> DFS(int nodes, const unordered_map<int, list<int>>& adjList, int start) {
    vector<int> ans;
    unordered_map<int, bool> visited;

    dfs(adjList, visited, ans, start);
    for (int i = 0; i < nodes; ++i) {
        if (!visited[i]) {
            dfs(adjList, visited, ans, i);
        }
    }
    return ans;
}

int main() {
    int choice;
    cout << "Select Search Algorithm: \n";
    cout << "1. A* Search\n";
    cout << "2. Best First Search\n";
    cout << "3. Beam Search\n";
    cout << "4. Iterative Deepening Search\n";
    cout << "5. Breadth-First Search\n";
    cout << "6. Depth-First Search\n";
    cout << "7. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    // Define graph for algorithms
    int adjMatrix[10][10] = {
        {0, 6, 3, 1, 0, 0, 0, 0, 0, 0},
        {6, 0, 2, 6, 3, 4, 0, 0, 0, 0},
        {3, 2, 0, 0, 4, 5, 0, 0, 0, 0},
        {1, 6, 0, 0, 7, 8, 9, 0, 0, 0},
        {0, 3, 4, 7, 0, 6, 9, 9, 0, 0},
        {0, 4, 5, 8, 6, 0, 8, 9, 0, 0},
        {0, 0, 0, 9, 9, 8, 0, 11, 12, 14},
        {0, 0, 0, 0, 9, 9, 11, 0, 13, 9},
        {0, 0, 0, 0, 0, 0, 12, 13, 0, 8},
        {0, 0, 0, 0, 0, 0, 14, 9, 8, 0}
    };

    
    int hValue[10] = {15, 13, 13, 12, 10, 9, 7, 6, 5, 0};
    graph nodes(10,hValue);

    unordered_map<int, list<int>> adjList;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (adjMatrix[i][j] > 0) {
                adjList[i].push_back(j);
            }
        }
    }
    while(choice!=7){
    switch (choice) {
        case 1: {
            char start, goal;
            cout << "Enter start node: ";
            cin >> start;
            cout << "Enter goal node: ";
            cin >> goal;
            aStar(adjMatrix, int(start)-65, int(goal)-65, nodes);
            break;
        }
        case 2: {
            vector<bool> visited(10,false);
            vector<int> ans;
            bsf(adjMatrix, visited, ans, 0);
            cout << "Best First Search Result: ";
            for (int node : ans) {
                cout << char(node+65) << "\t";
            }
            cout << endl;
            break;
        }
        case 3: {
            unordered_map<int, bool> visited;
            vector<int> ans;
            int beamWidth=2;
            beam_constant_width(adjList, visited, ans, 0, beamWidth, adjMatrix);
            cout << "Beam Search Result: ";
            for (int node : ans) {
                cout << char(node+65) << "\t";
            }
            cout << endl;
            break;
        }
        case 4: {
            int maxDepth;
            cout << "Enter maximum depth for IDS: ";
            cin >> maxDepth;
            IDS(10,adjList,maxDepth,adjMatrix);
            break;
        }
        case 5: {
            vector<int> ans = BFS(10, adjList, 0);
            cout << "BFS Result: ";
            for (int node : ans) {
                cout << char(node+65) << "\t";
            }
            cout << endl;
            break;
        }
        case 6: {
            vector<int> ans = DFS(10, adjList, 0);
            cout << "DFS Result: ";
            for (int node : ans) {
                cout << char(node+65) << "\t";
            }
            cout << endl;
            break;
        }
        default:
            cout << "Invalid choice!" << endl;
            break;
    }
     cout << "Enter your choice: ";
     cin >> choice;

    }

    return 0;
}

