#include <bits/stdc++.h>

using namespace std;

#define INF 0x3f3f3f3f
#define endl '\n'

class weightedGraph{
private:
public:
	vector<pair<int, int>> adj[100100];
	void add(int a, int b, int w){
		adj[a].push_back({b, w});
	}

	tuple<vector<int>, vector<int>, bool> bellmanFord(int node, int n){
		vector<int> d0(n, INF);
		vector<int> d1(n, INF);
		vector<int> f(n, -1);
		d0[node] = 0;
		for(int i = 1; i < n; ++i){
			d1 = d0;
			for(int j = 0; j < n; ++j){
				int sz = adj[j].size();
				for(int k = 0; k < sz; ++k){	
					int v = adj[j][k].first;
					int w = adj[j][k].second;
					if(d0[j] + w < d1[v]){
						d1[v] = d0[j] + w;
						f[v] = j;
					}
				}
			}
			d0 = d1;
		}
		bool cycle = false;
		for(int i = 0; i < n - 1; ++i){
			int sz = adj[i].size();
			for(int j = 0; j < sz; ++j){
				int v = adj[i][j].first;
				int w = adj[i][j].second;
				if(d0[i] + w < d0[v]){
					cycle = true;
				}
			}
		}
		return {d1, f, cycle};
	}	
};

void solve(){
	weightedGraph g;
	int n;
	cin >> n;
	vector<pair<int, int>> v(n);
	for(int i = 0; i < n; ++i){
		cin >> v[i].first >> v[i].second;
	}
	vector<int> extra(n, 0);
	int m;
	cin >> m;
	for(int i = 0; i < m; ++i){
		int a;
		cin >> a;
		extra[a] = 1;
	}
	for(int i = 0; i < n - 1; ++i){
		int mm;
		cin >> mm;
		for(int j = 0; j < mm; ++j){
			int number;
			cin >> number;
			int dist = (v[i].first - v[number].first)*(v[i].first - v[number].first);
			dist += (v[i].second- v[number].second)*(v[i].second - v[number].second);
			if(extra[number] == 1){
				dist = -dist;
			}
			g.add(i, number, dist);
		}
	}
	int wtf;
	cin >> wtf;
	vector<int> eita, prec;
	bool cycle = false;
	tie(eita, prec, cycle) = g.bellmanFord(0, n);
	if(cycle){
		cout << "LOOP" << endl;
		return;
	}
	int res = eita[n - 1];
	cout << res << " ";
	int atual = prec[n - 1];
	vector<int> ans;
	while(atual != -1){
		ans.push_back(atual);
		atual = prec[atual];
	}
	reverse(ans.begin(), ans.end());
	int sz = ans.size();
	for(int i = 0; i < sz; ++i){
		cout << ans[i] << " ";
	}
	cout << n - 1;
	cout << endl;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int t;
	cin >> t;
	while(t--){
		solve();
	}
	return 0;
}
