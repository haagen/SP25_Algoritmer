
#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <Windows.h>

using namespace std;

unordered_map<string, vector<string>> bfs(
    unordered_map<string, vector<string>>& graph,
    const string& start)
{
    queue<string> q;
    unordered_map<string, vector<string>> paths;
    unordered_set<string> visited;

    q.push(start);      // Adding starting point to work-queue
    paths[start] = { start };

    while (!q.empty())
    {
        string node = q.front();    // Get first element from queue
        q.pop();
        visited.insert(node);       // Add the node to the visited list to avoid never ending loop

        for (const string& neighbor : graph.at(node))
        {
            if (visited.find(neighbor) == visited.end() && paths.find(neighbor) == paths.end())
            {
                q.push(neighbor);
                paths[neighbor] = paths[node];
                paths[neighbor].push_back(neighbor);
            }
        }
    }

    return paths;
}

void BFS_demo()
{
    unordered_map<string, vector<string>> graph = {
        { "A", { "B", "C"} },
        { "B", { "A", "D", "E"}},
        { "C", { "A", "F" }},
        { "D", { "B" }},
        { "E", { "B", "F"}},
        { "F", { "C", "E"}}
    };

    auto paths = bfs(graph, "A");
    auto pathToF = paths["F"];

    cout << "Path from (A) to (F): ";
    for (const string& node : pathToF)
    {
        cout << node << " ";
    }
    cout << "\n";
}


typedef pair<int, string> NodeCost; // cost, node -- datastruktur för noden (prioritetskön)

void dijkstra(const unordered_map<string, vector<pair<string, int>>>& graph, const string& start) {
    unordered_map<string, int> distance;        // Kortaste avstånd från start till nod
    unordered_map<string, string> previous;     // Peka på "vägen tillbaka" -- billigaste vägen
    priority_queue<NodeCost, vector<NodeCost>, greater<NodeCost>> pq;   // Prioritets kö

    for (const auto& pair : graph) {
        distance[pair.first] = INT_MAX;         // Initiera graf (sätt kostnaden till oändligheten)
    }
    distance[start] = 0;                        // Kostnad till startnoden == 0
    pq.push({0, start});                // Lägg till första noden till vår arbetskö

    while (!pq.empty()) {

        // Hämta första noden från arbetskön
        NodeCost nodeCost = pq.top();
        int dist = nodeCost.first;
        string current = nodeCost.second;
        pq.pop();

        // Loopa igenom alla länkade noder
        for (const auto& pr : graph.at(current)) {

            // Hämta dess namn + kostnad
            string neighbor = pr.first;
            int weight = pr.second;

            // Beräkna kostnaden
            int newDist = dist + weight;
            if (newDist < distance[neighbor]) { // Om den nya kostnaden är lägre än den tidigare hittade
                distance[neighbor] = newDist;   // Sätt den nya distansen
                previous[neighbor] = current;   // Vilken nod kom vi från för att hitta den lägsta kostnaden
                pq.push({newDist, neighbor});   // Lägg noden på kön
            }
        }
    }

    cout << "Kortaste avstånd från " << start << " till D: " << distance["D"] << "\n";

    // Utskrift av kortaste vägen till varje nod
    for (const auto& pr : distance) {
        string node = pr.first;
        int dist = pr.second;
        cout << "Avstånd från " << start << " till " << node << ": " << dist << endl;

        // Återskapa vägen från start till aktuell nod
        vector<string> path;
        string current = node;
        while (current != start && previous.find(current) != previous.end()) {
            path.push_back(current);
            current = previous[current];
        }
        if (current == start) {
            path.push_back(start);
            reverse(path.begin(), path.end());
            cout << "Väg: ";
            for (const string& n : path) {
                cout << n << " ";
            }
            cout << endl;
        } else {
            cout << "(Ingen väg hittades)" << endl;
        }
    }
    
}

int Dijkstra_demo() {
    unordered_map<string, vector<pair<string, int>>> graph = {
        {"A", {{"B", 4}, {"C", 2}}},
        {"B", {{"A", 4}, {"C", 5}, {"D", 10}}},
        {"C", {{"A", 2}, {"B", 5}, {"D", 3}}},
        {"D", {{"B", 10}, {"C", 3}}}
    };

    dijkstra(graph, "A");
    return 0;
}


struct Node
{
    int x, y;
    int g, h;   // g - kostnaden, h - heuristik
    Node* parent;

    int f() const{ return g + h; }

    bool operator>(const Node& other) const
    {
        return f() > other.f();
    }
};

int heuristic(int x1, int y1, int x2, int y2)
{
    return abs(x1-x2) + abs(y1-y2);
}

void astar(const vector<vector<int>>& grid, pair<int, int> start, pair<int, int> goal)
{
    int rows = grid.size(), cols = grid[0].size();
    priority_queue<Node, vector<Node>, greater<Node>> open;
    vector<vector<bool>> closed(rows, vector<bool>(cols, false));

    Node startNode{ start.first, start.second, 0, heuristic(start.first, start.second, goal.first, goal.second), nullptr};
    open.push(startNode);
    closed[start.first][start.second] = true;

    while (!open.empty())
    {
        Node current = open.top();
        open.pop();

        // Check if we have reached the goal
        if (current.x == goal.first && current.y == goal.second)
        {
            vector<pair<int, int>> path;
            for (Node* n = &current; n != nullptr; n = n->parent)
            {
                path.emplace_back(n->x, n->y);
            }
            reverse(path.begin(), path.end());
            for (auto p : path)
            {
                cout << "(" << p.first << ", " << p.second << ") ";
            }
            cout << "\n";
            return;
        }
        // Mark as visited
        closed[current.x][current.y] = true;

        const vector<pair<int, int>> directions = { { 0, 1 }, { 1, 0}, { 0, -1}, { -1, 0} };
        for (auto p : directions)
        {
            int dx = p.first;
            int dy = p.second;
            int nx = current.x + dx;
            int ny = current.y + dy;

            if (nx >= 0 && ny >= 0 && nx < rows && ny < cols && grid[nx][ny] == 0 && !closed[nx][ny])
            {
                Node neighbor{ nx, ny, current.g + 1, heuristic(nx, ny, goal.first, goal.second), new Node(current) };
                open.push(neighbor);
            }
        }
    }
    cout << "Ingen väg kunde hittas.\n";
}

void astar_demo()
{
    vector<vector<int>> grid = {
        { 0, 0, 0, 0 },
        { 1, 1, 0, 1 },
        { 0, 0, 0, 0 },
        { 0, 1, 1, 0 },
        { 0, 0, 0, 0 }
    };

    astar(grid, {0, 0}, {4, 3});
}


int main(int argc, char* argv[])
{

    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    
    //BFS_demo();
    Dijkstra_demo();
    //astar_demo();
    return 0;
}
