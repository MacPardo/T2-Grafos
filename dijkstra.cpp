#include <string.h>
#include <stdio.h>
#include <queue>

#define MAX 112
#define INF 112345678

using namespace std;

int graph[MAX][MAX];
int size;

void ins(char a, char b, int w = 1) {
  a -= 'a';
  b -= 'a';
  graph[a][b] = graph[b][a] = w;
  size++;
}

vector<int> bfs(int start, int end) {
  bool ok[size];
  memset(ok, false, sizeof(ok));
  queue<pair<int, vector<int> > > q;
  vector<int> path;
  path.push_back(start);
  q.push(pair<int, vector<int> >(start, path));
  int u;
  while (!q.empty()) {
    u = q.front().first;
    path = q.front().second;
    q.pop();

    ok[u] = true;

    if (u == end) {
      return path;
    }
    for (int i = 0; i < size; i++) {
      if (graph[u][i] > 0 && !ok[i]) {
        vector<int> k = path;
        k.push_back(i);
        q.push(pair<int,vector<int> >(i, k));
      }
    }
  }

  return vector<int>();
}

int dijkstra(int start, int end) {
  priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > q;
  int dist[size];
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

  vector<int> path = bfs('a'-'a', 'z'-'a');
  for (vector<int>::iterator it = path.begin(); it != path.end(); it++) {
    printf("%c ", *it + 'a');
  }
  printf("\n");
  printf("Comprimento: %d\n", path.size());
  return 0;
}
