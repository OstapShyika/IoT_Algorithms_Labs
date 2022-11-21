#include <iostream>
#include <string>
#include <vector>
#include <ctime>

#define ull unsigned long long

using namespace std;

vector<int> rabin_karp(string const& s, string const& p) {
    const int q = 31;
    const int m = 1e9 + 9;
    ull S = p.size(), T = s.size();

    vector<long long> p_pow(max(S, T));
    p_pow[0] = 1;
    for (int i = 1; i < (int)p_pow.size(); i++)
        p_pow[i] = (p_pow[i-1] * q) % m;

    vector<long long> h(T + 1, 0);
    for (int i = 0; i < T; i++)
        h[i+1] = (h[i] + (s[i] - 'a' + 1) * p_pow[i]) % m;
    long long h_s = 0;
    for (int i = 0; i < S; i++)
        h_s = (h_s + (p[i] - 'a' + 1) * p_pow[i]) % m;

    vector<int> occurences;
    for (int i = 0; i + S - 1 < T; i++) {
        long long cur_h = (h[i+S] + m - h[i]) % m;
        if (cur_h == h_s * p_pow[i] % m)
            occurences.push_back(i);
    }
    return occurences;
}

void test(string &s, string &p, vector<int>& expected, vector<int>(*func)(string const&, string const&)) {
    clock_t start = clock();
    vector<int> res = func(s, p);
    cout << (res == expected ? "Success" : "Failed") << "\n";
    clock_t end = clock();
    cout << ((double) (end - start)) / CLOCKS_PER_SEC << " sec\n";
}

int main() {
    string s("cjhwviuiqefuiarhuafidusizdfiusdgfkkkkkkkkkkkkkkkkkkkbbbsak");
    string p("hw");
    vector<int> exp{2};
    test(s, p, exp, rabin_karp);
    return 0;
}
