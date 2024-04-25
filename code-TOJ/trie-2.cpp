#include <stdio.h>
#include <string.h>
#include <stack>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <queue>
#include <set>
#include <limits>
#include <cmath>
#include <algorithm>

using namespace std;


#define MAXN 20000

int n;
//char s[MAXN + 10][60];


struct Node {
   int edges[26];
   bool isWord;
};
std::vector<Node> nodes(1);


void Add2Dict(char *t)
{
   Node *node = &nodes[0];
   while (*t) {
      int i = node->edges[*t - 'a'];
      if (i == 0) {
         i = node->edges[*t - 'a'] = nodes.size();
         nodes.push_back({});
      }
      node = &nodes[i];
      t++;
   }
   node->isWord = true;
}

int Solve(char *t) {
   Node *node = &nodes[0];
   int ret = 0;
   char *tt = t;
   while (*t) {
      int i = node->edges[*t - 'a'];
      if (i == 0) {
         break;
      }

      node = &nodes[i];
      t++;
      if (node->isWord) {
         ret = t - tt;
      }
   }

   return ret;
}

int main() {
   int q;
   scanf("%d%d", &n, &q);
   char ss[60] = {};
   for (int i = 0; i < n; i++)
   {
      scanf("%s", ss);
      Add2Dict(ss);
   }
   char t[60];
   while (q--) {
      scanf("%s", t);
      printf("%d\n", Solve(t));
   }
   return 0;
}
