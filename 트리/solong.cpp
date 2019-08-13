#include <iostream>
using namespace std;
int C, N, M;

const int ALPHABETS = 26;
int toNumber(char ch) { return ch - 'A'; }

struct TriNode {
  TriNode* children[ALPHABETS];

  int terminal;
  int first;

  TriNode();
  ~TriNode();

  void insert(const char* key, int id) {
    if (first == -1) first = id;
    if(*key == 0)
      terminal = id;
      else {
        int next = toNumber(*key);
        if(children[next] == NULL)
          children[next] = new TriNode();
          children[next]->insert(key + 1, id);
      }
  }

  int type(const char* key, int id) {
    if (*key == 0) return 0;

    if (first == id) return 1;
    int next = toNumber(*key);
    return 1 + children[next]->ty[e(key+1, id);
  }
};

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> C;
  for(int i = 0; i < C; i++) {
    cin >> N >> M;
    TriNode tri;
    for (int j = 0; j < N; j++) {
      char* tmp;
      int a;
      cin >> tmp >> a;
      tri.insert(tmp, a);
    }
    for (int j = 0; j < M; j++) {
      char* tmp;
      type(tmp

