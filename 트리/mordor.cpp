#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
const int Int_MAX = 987654321;
struct RMQ {
  int n; // 배열의 길이
  vector<int> rangeMin;
  RMQ(const vector<int>& array) {
    n = array.size();
    rangeMin.resize(n*4);
    init(array, 0, n-1, 1);
  }
    int init(const vector<int>& array, int left, int right, int node) {
      if(left == right)
        return rangeMin[node] = array[left];
        int mid = (left + right) / 2;
        int leftMin = init(array, left, mid, node*2);
        int rightMin = init(array, mid+1, right, node*2+1);
        return rangeMin[node] = min(leftMin, rightMin);
    }
  int query(int left, int right, int node, int nodeLeft, int nodeRight) {
    if (right < nodeLeft || nodeRight < left) return Int_MAX;
    if (left <= nodeLeft && nodeRight <= right)
      return rangeMin[node];

    int mid = (nodeLeft + nodeRight) /2;
    return min(query(left, right, node*2, nodeLeft, mid), query(left, right, node*2+1, mid+1, nodeRight));
  }
  int query (int left, int right) {
    return query(left, right, 1, 0, n-1);
  }

  int update(int index, int newValue, int node, int nodeLeft, int nodeRight) {
    if(index < nodeLeft || nodeRight < index)
      return rangeMin[node];
    if(nodeLeft == nodeRight) return rangeMin[node] = newValue;
    int mid = (nodeLeft + nodeRight) /2;
    return rangeMin[node] = min(update(index, newValue, node*2, nodeLeft, mid), update(index, newValue, node*2+1, mid+1, nodeRight));
  }

  int update(int index, int newValue) {
    return update(index, newValue, 1, 0, n-1);
  }
};

int c; //  테스트 케이스 수
int N, Q; // 각각 표지판의 수, 등산로의 수, 해발고도
vector<int> hi; // 표지판 고도
vector <pair<int, int>> ab; // 등산로의 처음과 마지막 표지판 번호

void mordor();
int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> c;
  for(int i = 0; i < c; i++)
  {
    cin >> N >> Q;
    hi.assign(N, 0);
    ab.assign(Q, make_pair(0,0));
    for(int j = 0; j < N; j++)
      cin >> hi[j];
    for(int j = 0; j < Q; j++)
      cin >> ab[j].first >> ab[j].second;
      
    mordor();
  }
}
void mordor()
{
  vector<int> lo(N,0);
  for(int i = 0; i < N; i++)
    lo[i] = -hi[i];
  RMQ high(hi);
  RMQ low(lo);

  for(int i = 0; i < Q; i++)
  {
    int highest, lowest;
    highest = high.query(ab[i].first, ab[i].second);
    lowest = low.query(ab[i].first, ab[i].second);
    cout << abs(highest + lowest) << '\n';
  }
}
