#include <iostream>
#include <cmath>
#include <cstring>
#define MAXN 12
using namespace std;

const int INF = 987654321;
int N, K, M, L; // N; 전공 과목의 숙 K: 들어야 할 과목의 수 M: 학기의 수 L: 한 학기에 최대로 들을 수 있는 과목의 수
int prerequisite[MAXN];
int classes[10];
int cache[10][1<<MAXN];

int bitCount(int n);
int graduate(int semester, int taken);

void init();
int main(void)
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int C;
  cin >> C;
  for (int i = 0; i < C; i++)
    init();
}

void init()
{
  cin >> N >> K >> M >> L;
  for(int i = 0; i < 10; i++)
    memset(cache[i], -1, sizeof(cache[i])); 
  for(int i = 0; i < N; i++)
  {
    int num; 
    cin >> num;
    int save = 0;
    int tmp;
    for(int j = 0; j < num; j++)
    {
      cin >> tmp;
      save += 1 << tmp;
    }
    prerequisite[i] = save;
  }

  for(int i = 0; i < M; i++)
  {
    int num;
    cin >> num;
    int save = 0;
    int tmp;
    for(int j = 0; j < num; j++)
    {
      cin >> tmp;
      save += 1 << tmp;
    }
    classes[i] = save;
  }
  
  int ans = graduate(M ,0);

  if(ans == INF) printf("IMPOSSIBLE\n");
  else printf("%d\n", ans);
}

int graduate(int semester, int taken)
{
  if(bitCount(taken) >= K) return 0;
  if(semester == M) return INF;
  int& ret = cache[semester][taken];
  if(ret != -1) return ret;
  ret = INF;

  int canTake = (classes[semester] &~ taken);

  for(int i = 0; i < N; i++)
    if((canTake & (1 << i)) && (taken & prerequisite[i]) != prerequisite[i])
      canTake &= ~( 1 <<i);

  for(int take = canTake; take > 0; take = ((take-1) & canTake)) {
    if(bitCount(take) > L) continue;
    ret = min(ret, graduate(semester+1, taken | take) + 1);
  }

  ret = min(ret, graduate(semester+1, taken));
  return ret;
}

int bitCount(int x)
{
  if(x == 0) return 0;
  return x % 2 + bitCount(x/2);
}
