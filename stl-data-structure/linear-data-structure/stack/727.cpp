// 727 - Equation
#include <iostream>
#include <sstream>
#include <stack>
#include <stdio.h>

using namespace std;

int Priority(char c) {
    switch (c) {
        case '(': return 1; break;
        case '+': return 2; break;
        case '-': return 2; break;
        case '*': return 3; break;
        case '/': return 3; break;
    }
}

int main() {
//    freopen("727.inp", "r", stdin); freopen("727.out", "w", stdout);
   stringstream ss;
   ss << "1 A + B * C + D + E";
    int kase;
    char c;
    std::string s;
    ss >> kase;
    while (kase--) {
        stack <char> st;
        while (ss >> s && !s.empty()) {
            c = s[0];
            if (c==' ') break;
            if (c=='(') {
                st.push(c);
            }
            else if (c=='+' || c=='-' || c=='*' || c=='/') {
                while (!st.empty() && Priority(c) <= Priority(st.top())) {
                    printf("%c", st.top());
                    st.pop();
                }
                st.push(c);
            }
            else if (c==')') {
                while (st.top()!='(') {
                    printf("%c", st.top());
                    st.pop();
                }
                st.pop();
            }
            else printf("%c", c);
        }
        while (!st.empty()) {
            printf("%c", st.top()); st.pop();
        }
        cout << endl;
        if (kase) cout << endl;
    }
}