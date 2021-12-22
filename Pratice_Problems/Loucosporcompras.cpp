#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

int ans = 0;

void backtracking(vector<int> &v, int sum, int at, int m, int q, int i, int n){
    if(i == n)return;
    if(sum > q){
        return;
    }
    if(sum + v[i] > q){
        backtracking(v, sum, at, m, q, i + 1, n);
    }else if(sum + v[i] <= q && at + 1 >= m){
        ans++;
        backtracking(v, sum + v[i], at+1, m, q, i + 1, n);
        backtracking(v, sum, at, m, q, i + 1, n);
    }else{
        backtracking(v, sum + v[i], at+1, m, q, i + 1, n);
        backtracking(v, sum, at, m, q, i + 1, n);
    }
}

void solve(int nn){
    ans = 0;
    cout << "caso " << nn << ": ";
    int n, m, q;
    cin >> n;
    vector<int> v(n);
    int temp = 0;
    for(int i = 0; i < n; ++i){
        cin >> v[i];
        temp += v[i];
    }
    cin >> m >> q;
    backtracking(v, 0, 0, m, q, 0, n);
    if(m == 0){
        ans++;
    }
    cout << ans << endl;
}

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    int nn = 0;
    while(t--){
        solve(nn);
        nn++;
    }
    return 0;
}
