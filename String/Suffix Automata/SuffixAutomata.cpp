//https://cses.fi/problemset/task/2105

#include<bits/stdc++.h>
using namespace std;

#define ll long long

struct SuffixAutomata {
    struct node {
        int len, link, firstpos;
        map<char, int> nxt;
    };
    int sz, last;
    vector<node> t;
    SuffixAutomata() {}
    SuffixAutomata(string &s) {
        int n = s.size(); sz = 1; last = 0;
        t.resize(2 * n); t[0].len = 0;
        t[0].link = -1; t[0].firstpos = 0;
        for (auto x: s) {
            extend(x);
        }
    }
    void extend(char c) {
        int p = last;
        if (t[p].nxt.count(c)) {
            int q = t[p].nxt[c];
            if (t[q].len == t[p].len + 1) {
                last = q;
                return;
            }
            int clone = sz++;
            t[clone] = t[q];
            t[clone].len = t[p].len + 1;
            t[q].link = clone;
            last = clone;
            while (p != -1 && t[p].nxt[c] == q) {
                t[p].nxt[c] = clone;
                p = t[p].link;
            }
            return;
        }
        int cur = sz++;
        t[cur].len = t[last].len + 1;
        t[cur].firstpos = t[cur].len;
        p = last;
        while (p != -1 && !t[p].nxt.count(c)) {
            t[p].nxt[c] = cur;
            p = t[p].link;
        }
        if (p == -1) t[cur].link = 0;
        else {
            int q = t[p].nxt[c];
            if (t[p].len + 1 == t[q].len) t[cur].link = q;
            else {
                int clone = sz++;
                t[clone] = t[q];
                t[clone].len = t[p].len + 1;
                while (p != -1 && t[p].nxt[c] == q) {
                    t[p].nxt[c] = clone;
                    p = t[p].link;
                }
                t[q].link = t[cur].link = clone;
            }
        }
        last = cur;
    }
    //O(N)
    ll unique_substrings() {
        ll tot = 0;
        for(int i = 1; i < sz; i++) {
            tot += t[i].len - t[t[i].link].len;
        }
        return tot;
        
        /*vector<int> unq; // unq[i] = unique substring in prefix of length i
        unq.push_back(0);
        for(int i = 0; i < n; i++) {
	      extend(s[i]);
	      ans.push_back(unq.back() + i + 1 - t[t[last].link].len);
       }*/
    }
    ll tot_len_diff_substings() {
        ll tot = 0;
        for(int i = 1; i < sz; i++) {
            ll shortest = t[t[i].link].len + 1;
            ll longest = t[i].len;
            ll num_strings = longest - shortest + 1;
            ll cur = num_strings * (longest + shortest) / 2;
            tot += cur;
        }
        return tot;
    }
    int first_occurrence(string &s) {
        int u = 0;
        for(auto ch : s) {
            if(!t[u].nxt.count(ch))
                return -1;
            u = t[u].nxt[ch];
        }
        return t[u].firstpos - s.size() + 1;
    }
};

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    string s; cin >> s;
    int n = s.size();
    SuffixAutomata sa(s);
    cout << sa.unique_substrings() << '\n';
    return 0;
}
