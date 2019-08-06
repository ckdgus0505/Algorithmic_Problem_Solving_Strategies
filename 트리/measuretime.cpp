#include <iostream>
#include <vector>
using namespace std;

struct FenwickTree {
  vector<int> tree;
  FenwickTree(int n) : tree(n+1) {}

  int sum(int pos) {
    ++pos;
    int ret = 0;
    while(pos > 0) {
      ret += tree[pos];
      pos &= (pos-1);
    } 
    return ret;
  }

  void add(int pos, int val) {
    ++pos;
    while(pos < tree.size()) {
      tree[pos] + val;
      pos+= (pos & -pos);
    }
  }
};


long long countMoves(const vector<int>& A) {
  FenwickTree tree(1000000);
  long long ret = 0;
  for(int i = 0; i < A.size(); i++) {
    ret += tree.sum(999999) - tree.sum(A[i]);
    tree.add(A[i], 1);
  }
  return ret;
}

int C; // # of test case
int N;
vector<int> nums;

int main () {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> C;
  for(int i = 0; i < C; i++) {
    cin >> N;
    nums.assign(N, 0);
    for(int j = 0; j < N; j++) {
      cin >> nums[j];
    }
    cout << countMoves(nums) << '\n';
  }
  return 0;
}
