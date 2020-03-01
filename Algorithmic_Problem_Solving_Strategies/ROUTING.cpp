#include <cstdio>
#include <vector>
#include <queue>
#include <float.h>
#include <memory.h>
using namespace std;

int t, n, m;
double dist[10001];

int dijkstra(vector<pair<int, double> > graph[10001], int start) {
    priority_queue<pair<int, double> > pq;

    dist[start] = 1;
    pq.push(make_pair(start, -1));

    while (!pq.empty()) {
        pair<int, double> value = pq.top();
        pq.pop();

        double cost = -value.second;
        int current = value.first;

        if (dist[current] < cost) {
            continue;
        }

        for (int i = 0; i < graph[current].size(); i++) {
            int next = graph[current][i].first;
            double nextCost = graph[current][i].second * dist[current];

            if (dist[next] > nextCost) {
                dist[next] = nextCost;
                pq.push(make_pair(next, -nextCost));
            }
        }
    }
}

int main() {
    scanf("%d", &t);

    while (t--) {
        vector<pair<int, double> > graph[10001];

        scanf("%d %d", &n, &m);

        for (int i = 0; i < 10001; i++) {
            dist[i] = DBL_MAX;
        }

        for (int i = 0; i < m; i++) {
            int x, y;
            double z;

            scanf("%d %d %lf", &x, &y, &z);

            graph[x].push_back({ y, z });
            graph[y].push_back({ x, z });
        }

        dijkstra(graph, 0);

        printf("%.10lf\n", dist[n - 1]);
    }
}