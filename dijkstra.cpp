#include <string.h>
#include <stdio.h>
#include <queue>
#include <tuple>

#define MAX 112
#define INF 112345678

#define FOR(A, B, C) for(int A = B; A < C; A++)
#define FV(T, A, B) for(vector<T>::iterator A = B.begin(); A != B.end(); A++)
#define BR printf("\n")

using namespace std;

typedef tuple<int, int, int> i3;
typedef pair<int, int> ii;

int graph[MAX][MAX];
int size;
int previous[MAX], dist[MAX];
int global_i = 0;

void ins(char a, char b, int w = 1) {
  a -= 'a';
  b -= 'a';
  graph[a][b] = graph[b][a] = w;
  size++;
}

vector<int> get_path(int start, int end) {
  vector<int> path;
  while (start != end) {
    path.insert(path.begin(), end);
    end = previous[end];
  }
  path.insert(path.begin(), start);
  return path;
}

void bfs(int start, int end) {
  bool ok[MAX];
  memset(ok, false, sizeof(ok));
  memset(dist, -1, sizeof(dist));
  memset(previous, -1, sizeof(previous));
  queue<i3> q; //<dist, v, prev>
  int d, u, k;
  q.push(i3(0, start, -1));

  while(!q.empty()) {
    d = get<0>(q.front());
    u = get<1>(q.front());
    k = get<2>(q.front());
    q.pop();
    if (ok[u]) continue;
    ok[u] = true;
    previous[u] = k;
    dist[u] = d;

    for (int i = 0; i < size; i++) {
      if (graph[u][i] > 0 && !ok[i]) {
        q.push(i3(d + 1, i, u));
      }
    }
  }
}

/*
int dijkstra(int start, int end) {
  priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > q;
  int u, v;
  for (int i = 0; i < size; i++) dist[i] = INF;
  q.push(pair<int, int>(0, start));
  while(!q.empty()) {
    u = q.top().second;
    dist[u] = q.top().first;
    q.pop();
    if (u == end) {
      return dist[u];
    }
    for (int i = 0; i < size; i++) {
      if (graph[u][i] > 0 && dist[u] + graph[u][i] < dist[i]) {
        q.push(pair<int, int>(dist[u] + graph[u][i], i));
      }
    }
  }
  return INF;
}
*/

int main(void) {
  memset(graph, 0, sizeof(graph));
  size = 0;
  ins('a','b');
  ins('a','k');
  ins('b','c');
  ins('b','d');
  ins('c','e');
  ins('d','l');
  ins('e','f');
  ins('e','g');
  ins('f','h');
  ins('g','i');
  ins('h','i');
  ins('h','j');
  ins('i','j');
  ins('j','z');
  ins('k','l');
  ins('k','m');
  ins('k','n');
  ins('l','o');
  ins('m','o');
  ins('n','o');
  ins('o','p');
  ins('o','r');
  ins('p','q');
  ins('q','r');
  ins('q','s');
  ins('q','t');
  ins('s','t');
  ins('s','z');
  ins('t','z');

  printf("Caminho mais curto para o primeiro grafo:\n");

  bfs('a'-'a', 'z'-'a');

  printf("V\tD\tP\n");
  FOR(i, 0, 'z'-'a'+1) {
    printf("%c\t%d\t%c\n", i+'a', dist[i], previous[i]+'a');
  }
  BR;
  vector<int> path = get_path('a'-'a', 'z'-'a');
  FV(int, it, path) printf("%c%s", *it + 'a', it + 1 == path.end() ? "\n" : "-> ");
  return 0;
}
