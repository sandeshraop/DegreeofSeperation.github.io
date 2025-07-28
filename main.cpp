#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Function to calculate the degree of separation
int degreeOfSeparation(const vector<vector<int>>& graph, int src, int target) {
    if (src == target) return 0;
    int n = graph.size();
    vector<bool> visited(n, false);
    queue<pair<int,int> > q;
    q.push(make_pair(src, 0));
    visited[src] = true;

    while (!q.empty()) {
        pair<int,int> front = q.front();
        q.pop();
        int node = front.first;
        int depth = front.second;

       for (size_t i = 0; i < graph[node].size(); ++i) {
            int neighbor = graph[node][i];
            if (!visited[neighbor]) {
                if (neighbor == target)
                    return depth + 1;
                visited[neighbor] = true;
                q.push(make_pair(neighbor, depth + 1));
            }
        }
    }
    return -1; // Not connected
}

int main() {
    int n, m;
    cout << "Enter number of users: ";
    cin >> n;
    cout << "Enter number of connections: ";
    cin >> m;

    vector<vector<int> > graph(n);
    cout << "Enter each connection (pair of user indices starting from 0):\n";
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        if(u >= 0 && u < n && v >= 0 && v < n){
            graph[u].push_back(v);
            graph[v].push_back(u); // Assuming undirected
        } else {
            cout << "Invalid user index. Please enter indices between 0 and " << n-1 << endl;
            --i; // so that input is taken correctly again
        }
    }
    int src, tgt;
    cout << "Enter first user index: ";
    cin >> src;
    cout << "Enter second user index: ";
    cin >> tgt;

    if(src < 0 || src >= n || tgt < 0 || tgt >= n) {
        cout << "Invalid user index for source or target." << endl;
        return 1;
    }
    int degree = degreeOfSeparation(graph, src, tgt);
    if (degree != -1)
        cout << "Degree of separation: " << degree << endl;
    else
        cout << "Users are not connected." << endl;

    return 0;
}
/*
Enter number of users: 4
Enter number of connections: 3
Enter each connection (pair of user indices starting from 0):
0 1
1 2
0 3
Enter first user index: 0
Enter second user index: 2
Degree of separation: 2
*/
