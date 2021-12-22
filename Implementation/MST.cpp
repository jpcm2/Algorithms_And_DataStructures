#include <bits/stdc++.h>

using namespace std;



class MST{
private:
	vector<pair<int, int>> adj[100100];
	vector<int> d;
	vector<int> f;
public:
	void add(int a, int b, int w){
		adj[a].push_back({b, w});
	}
	void MSTBuild(int n){
		d.clear();
		f.clear();
		d = vector<int>(100100, INT_MAX);
		f = vector<int>(100100, -1);
		int node = 0;
		priority_queue<pair<int,int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
		pq.push(make_pair(0, node));
		d[node] = 0;
		while(!pq.empty()){
			int u = pq.top().second;
			pq.pop();
			int sz = adj[u].size();
			for(int i = 0; i < sz; ++i){
				int v = adj[u][i].first;
				int w = adj[u][i].second;
				if(w < d[v]){
					d[v] = w;
					f[v] = u;
					pq.push(make_pair(d[v], v));
				}
			}
		}
		for(int i = 0; i < n; ++i){
			cout << f[i] << " ";
		}
		cout << endl;
		for(int i = 0; i < n; ++i){
			cout << d[i] << " ";
		}
		cout << endl;
	}
};


int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	MST g;
	g.add(0, 5, 12);
	g.add(0,2,5);
	g.add(0, 3, 4);
	g.add(1, 5, 3);
	g.add(2, 1, 1);
	g.add(2,3,4);
	g.add(3,1,3);
	g.add(3,4,7);
	g.add(4, 0, 1);
	g.add(4, 1, 2);
	g.add(5, 4, 1);
    g.MSTBuild(6);
	return 0;
}
