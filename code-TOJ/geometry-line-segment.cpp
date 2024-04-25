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
#include <numeric>

using namespace std;

struct Point {
   int x, y;
   void read() { scanf("%d%d", &x, &y); }
   void println() { printf("%.4lf %.4lf\n", (double)x, (double)y); }
};

Point AtoB(const Point &a, const Point &b) {
   return { b.x - a.x, b.y - a.y };
}

int AcrossB(const Point &a, const Point &b) {
   return a.x * b.y - b.x * a.y;
}

int AdotB(const Point &a, const Point &b) {
   return a.x * b.x + a.y * b.y;
}

struct Segment {
   Point p, q;
   void read() {
      p.read();
      q.read();
   }
};

int main() {
   int T;
   scanf("%d", &T);
   while (T--) {
      Segment s1, s2;
      s1.read();
      s2.read();
      //Point ans;
      // 判断交点情况，或求出具体交点
      bool no = false, inf = false;


      Point line = AtoB(s1.p, s1.q);    // line ab
      Point a2p = AtoB(s1.p, s2.p);
      Point a2q = AtoB(s1.p, s2.q);

      int linecp = AcrossB(line, a2p);
      int linecq = AcrossB(line, a2q);

      int linedline = AdotB(line, line);
      int linedp = AdotB(line, a2p);
      int linedq = AdotB(line, a2q);
      if (linedp > linedq) {
         swap(linedp, linedq);
      }

      if (linecp == 0 && linecq == 0) {
         if (linedline == linedp) {
            s1.q.println();
            continue;
         }
         if (linedq == 0) {
            s1.p.println();
            continue;
         }
         if (linedline < linedp || 0 > linedq) {
            puts("-1");
            continue;
         }
         puts("inf");
         continue;
      }

      Point line2 = AtoB(s2.p, s2.q);   // line pq
      Point p2a = AtoB(s2.p, s1.p);
      Point p2b = AtoB(s2.p, s1.q);

      int lineca = AcrossB(line2, p2a);
      int linecb = AcrossB(line2, p2b);
      if (lineca * linecb <= 0 && linecp * linecq <= 0) {
         if (lineca == 0) {
            s1.p.println();
            continue;
         }
         int parta = abs(linecp);
         int partb = abs(linecq);

         auto x = s2.p.x + (double)line2.x * parta / (parta + partb);
         auto y = s2.p.y + (double)line2.y * parta / (parta + partb);

         printf("%.4lf %.4lf\n", (double)x, (double)y);
         continue;
      } else {
         puts("-1");
         continue;
      }

      //if (no) puts("-1");
      //else if (inf) puts("inf");
      //else ans.println();
   }
   return 0;
}
