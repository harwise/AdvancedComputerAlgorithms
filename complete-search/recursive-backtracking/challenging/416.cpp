#include<cstdio>
using namespace std;
 
int digit[10] = { 0x7E, 0x30, 0x6D, 0x79, 0x33, 0x5B, 0x5F, 0x70, 0x7F, 0x7B };
int n, input[16];
bool match;
 
void solve(int inputI, int digitI, int badMask) {
    // finished
    if (inputI == n)
        match = true;
    // more input
    else if (!(input[inputI] & badMask)) // matches old burns
        if (((digit[digitI] ^ input[inputI]) & input[inputI]) == 0) // new burns not revivals
            solve(inputI + 1, digitI - 1, (input[inputI] ^ digit[digitI]) | badMask);
}
 
char ans[2][16] = { "MISMATCH\n", "MATCH\n" };
char line[8], *p;
 
int main() {
    while (scanf("%d", &n) == 1 && n) {
        // input
        for (int i = 0; i < n; ++i) {
            scanf("%s", p = line);
            input[i] = 0;
            do
                input[i] |= ((*p == 'Y') << (line + 6 - p));
            while (*++p);
        }
        // solution
        match = false;
        for (int digitI = 9; digitI >= n - 1 && !match; --digitI)
            solve(0, digitI, 0);
        printf("%s", ans[match]);
    }
}
