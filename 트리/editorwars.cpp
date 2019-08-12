#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
  using namespace std;

  int C, N, M;

  struct DisjointSet {
    vector<int> parent, rank, enemy, size;
    DisjointSet(int n): parent(n) , rank(n, 1), enemy(n, -1), size(n,1){
      for(int i = 0; i < n; i++)
        parent[i] = i;
    }

    int find (int u) {
      if(u == parent[u]) return u;
      return find(parent[u]);
    }

    int merge(int u, int v) {
      if(u == -1 || v == -1) return max(u, v);
      u = find(u); v = find(v);
      if(u == v) return u;
      if(rank[u] > rank[v]) swap(u,v);
      parent[u] = v;
      if(rank[u] == rank[v]) ++rank[v];
      parent[u] = v;
      size[v] += size[u];
      return v;
    }
    bool dis(int u, int v) {
      u == find(u); v = find(v);
      if(u == v) return false;
      int a = merge(u, enemy[v]), b = merge(v, enemy[u]);
      enemy[a] = b; enemy[b] = a;
      return true;
    }
    bool ack(int u, int v) {
      u == find(u); v == find(v);
      if(enemy[u] == v) return false;
      int a = merge(u,v), b = merge(enemy[u], enemy[v]);
      enemy[a] = b;

      if(b != -1) enemy[b] = a;
      return true;
    }
  };

  int maxParty (const DisjointSet& buf) {
    int ret = 0;
    for(int node = 0; node < N; ++node)
      if(buf.parent[node] == node) {
        int enemy = buf.enemy[node];
        if(enemy > node) continue;
        int mySize = buf.size[node];
        int enemySize = ( enemy == -1 ? 0 : buf.size[enemy]);
        ret += max(mySize, enemySize);
      }
      return ret;
  }


  int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> C;
  for(int i = 0; i < C; i++) {
    cin >> N >> M;
    
    DisjointSet Party(N);

    for(int j = 0; j < M; j++)
    {
      char str[4];
      int a, b;
      cin >> str;
      cin >> a >> b;
      if( strcmp(str, "ACK") ==0){
        if(!Party.ack(a, b))
          cout << "CONTRADICTION AT " << j+1 << '\n';
      }
      else{
        if(!Party.dis(a,b)) 
          cout << "CONTRADICTION AT " << j+1 << '\n';
      }
    }
    if ( maxParty(Party) != 0)
      cout << "MAX PARTY SIZE IS " << maxParty(Party) << '\n';
  }
}


