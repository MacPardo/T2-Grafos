#include <string.h>
#include <stdio.h>
#include <queue>
#include <tuple>

#define MAX 112
#define INF -1

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

void dijkstra(int start, int end) {
  priority_queue<i3, vector<i3>, greater<i3> > q;
  memset(dist, INF, sizeof(dist)); //<dist, v, prev>
  memset(previous, -1, sizeof(previous));
  int d, u, k;
  q.push(i3(0, start, -1));
  while(!q.empty()) {
    d = get<0>(q.top());
    u = get<1>(q.top());
    k = get<2>(q.top());
    q.pop();
    if (d >= dist[u] && dist[u] != INF) continue;
    previous[u] = k;
    dist[u] = d;
    if (u == end) return;
    FOR (i, 0, 'z' - 'a' + 1) {
      if (graph[u][i] > 0 && (dist[i] == INF || dist[u] + graph[u][i] < dist[i])) {
        q.push(i3(dist[u] + graph[u][i], i, u));
      }
    }
  }
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

  printf("Tabela para o primeiro grafo:\n");

  bfs('a'-'a', 'z'-'a');

  printf("V\tDist\tAnt\n");
  FOR(i, 0, 'z'-'a'+1) {
    printf("%c\t%d\t%c\n", i+'a', dist[i], previous[i]+'a');
  }
  BR;
  vector<int> path = get_path('a'-'a', 'z'-'a');
  FV(int, it, path) printf("%c%s", *it + 'a', it + 1 == path.end() ? "\n" : "-> ");
  printf("Comprimento = %d\n", dist['z' - 'a']);


  path.clear();
  // GRAFO 2
  memset(graph, 0, sizeof(graph));
  size = 0;
  ins('a', 'b', 7);
  ins('a', 'd', 5);
  ins('b', 'c', 8);
  ins('b', 'd', 9);
  ins('b', 'e', 7);
  ins('c', 'e', 5);
  ins('d', 'e', 15);
  ins('d', 'f', 6);
  ins('e', 'f', 8);
  ins('e', 'g', 9);
  ins('f', 'g', 11);

  printf("Tabela para o segundo grafo:\n");
  dijkstra('a'-'a', 'g'-'a');

  printf("V\tDist\tAnt\n");
  FOR(i, 0, 'g'-'a'+1) {
    printf("%c\t%d\t%c\n", i+'a', dist[i], previous[i]+'a');
  }
  BR;
  path = get_path('a'-'a', 'g'-'a');
  FV(int, it, path) printf("%c%s", *it + 'a', it + 1 == path.end() ? "\n" : "-> ");
  printf("Comprimento = %d\n", dist['g' - 'a']);
  return 0;
}
