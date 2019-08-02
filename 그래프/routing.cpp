#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>
#define MAX 987654321
using namespace std;

int t; // 테스트 케이스의 수
int n, m; // 노드의 수 n, 간선의 수 m

vector<vector<pair<double, int>>> adj;

vector<double> dijkstra(int src);
int main(void){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> t;
  for(int i = 0; i < t; i++) {
    cin  >> n >> m;
    adj = vector<vector<pair<double,int>>> (n);
    for(int j = 0; j < m; j++) {
      int a, b;
      double c;
      cin >> a >> b >> c; // a,b,c는 각각 src, dst, weight
      adj[a].push_back(make_pair(c,b)); // weight를 먼저 저장
    }
    vector<double> ans = dijkstra(0);
    printf("%.10f\n", ans[n-1]);
  }
  return 0;
}

vector<double> dijkstra(int src) {
  vector<double> dist(n, MAX);
  priority_queue<pair<double, int>> pq;
  dist[src] = 1;
  pq.push(make_pair(-1, src));

  while(!pq.empty()){
    int here = pq.top().second;
    double cost = -pq.top().first;
    pq.pop();
    if(dist[here] < cost) continue;
    for(int i = 0; i < adj[here].size(); i++) {
      int there = adj[here][i].second;
      double nextDist = cost * adj[here][i].first;
      if(dist[there] > nextDist) {
        dist[there] = nextDist;
        pq.push(make_pair(-nextDist, there));
      }
    }
  }
  return dist;
}
