#include<iostream>
#include<vector>
#include<queue>
#define MAX 987654321
using namespace std;

vector<vector<pair<int, int>>> adj; // 인접 리스트
vector<vector<int>> dijks; // 다익스트라 결과값 넣는 vector
vector<int> fire;
vector<int> office;
vector<int> Min;
int C; // 테스트케이스
int V, E, n, m; // 노드, 엣지, 화재장소, 소방서의 수

vector<int> dijkstra(int src);
int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> C; // 테스트케이스

  for(int i = 0; i < C; i++)
  {
    cin >> V >> E >> n >> m;
    adj = vector<vector<pair<int,int>>>(V);
    dijks = vector<vector<int>> (n);
    Min = vector<int>(n, MAX);
    fire.assign(n, 0);
    office.assign(m,0);
    for(int j = 0; j < E; j++)
    {
      int a,b,c;
      cin >> a >>b >> c;
      adj[a-1].push_back(make_pair(c,b-1));
      adj[b-1].push_back(make_pair(c,a-1));
    }
    for(int j = 0; j < n; j++) {
      cin >> fire[j];
      fire[j] -= 1;
    }
    for(int j = 0; j < m; j++) {
      cin >> office[j];
      office[j] -= 1;
    }
    for(int j = 0; j < n; j++)
    {
      dijks[j] = dijkstra(fire[j]);
    }

    for(int j = 0; j < n; j++)
    {
      for(int k = 0; k < m; k++)
      {
        if( Min[j] > dijks[j][office[k]])
          Min[j] = dijks[j][office[k]];
      }
    }
    int ans = 0;
    for(int j = 0; j < n; j++)
    {
      ans += Min[j];
    }
    cout << ans << "\n";
  }
}

vector<int> dijkstra(int src) {
  vector<int> dist (V, MAX);
  priority_queue<pair<int, int>> pq;
  dist[src] = 0;
  pq.push(make_pair(0, src));

  while(!pq.empty()) {
    int here = pq.top().second;
    int cost = -pq.top().first;
    pq.pop();

    if(dist[here] < cost) continue;
    for(int i = 0; i < adj[here].size(); i++) {
      int there = adj[here][i].second;
      int thereDist = cost + adj[here][i].first;
      if(dist[there] > thereDist) {
        dist[there] = thereDist;
        pq.push(make_pair(-thereDist, there));
      }
    }
  }
  return dist;
}
