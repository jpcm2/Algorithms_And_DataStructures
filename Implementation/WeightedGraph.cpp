#include <bits/stdc++.h>

using namespace std;

#define INF 0x3f3f3f3f

class weightedGraph{
private:
	vector<pair<int, int>> adj[100100];
	vector<int> dist;
public:
	weightedGraph(){
		dist.resize(100100);
	}
	void add(int a, int b, int w){
		adj[a].push_back({b, w});
	}

	void dfs_visit(int node, int *visited){
		cout << node << endl;
		visited[node] = 1;
		int sz = adj[node].size();
		for(int i = 0; i < sz; ++i){
			if(visited[adj[node][i].first])continue;
			dfs_visit(adj[node][i].first, visited);
		}
	}

	void dfs(int node){
		int visited[100100];
		for(int i = 0; i < 100100; ++i){
			visited[i] = 0;
		}
		dfs_visit(node, visited);
	}

	void dfs_visitTopological(int node, int *visited, vector<int> &topological){ // <----------- Apenas se o grafo for direcionado
		visited[node] = 1;
		int sz = adj[node].size();
		for(int i = 0; i < sz; ++i){
			if(visited[adj[node][i].first])continue;
			dfs_visitTopological(adj[node][i].first, visited, topological);
		}
		topological.push_back(node);
	}

	vector<int> topological_ord(int n){ // <------- Apenas se o grafo for direcionado
		int visited[100100];
		for(int i = 0; i < 100100; ++i){
			visited[i] = 0;
		}
		vector<int> topological;
		for(int i = 0; i < n; ++i){
			if(visited[i])continue;
			dfs_visitTopological(i, visited, topological);
		}
		reverse(topological.begin(), topological.end());
		for(int i = 0; i < n; ++i){
			cout << topological[i] << " ";
		}
		return topological;
	}

	void BFS_Visit(int node, int *visited){
		visited[node] = 1;
		dist[node] = 0;
		queue<int> q;
		q.push(node);
		while(!q.empty()){
			int u = q.front();
			q.pop();
			int sz = adj[u].size();
			for(int i = 0; i < sz; ++i){
				int v = adj[node][i].first;
				if(visited[v] == 0){
					dist[v] = dist[u] + 1;
					visited[v] = 1;
					q.push(v);
				}
			}
		}
	}

	void bfs(int n){
		int visited[100100];
		for(int i = 0; i < 100100; ++i){
			visited[i] = 0;
		}
		for(int i = 0; i < n; ++i){
			if(visited[i] == 0){
				BFS_Visit(i, visited);
			}
		}
	}

	void dijkstra(int node, int n){
		dist = vector<int>(100100, INT_MAX);
		priority_queue<pair<int,int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
		pq.push(make_pair(0, node));
		dist[node] = 0;
		vector<int> f(n + 1);
		while(!pq.empty()){
			int u = pq.top().second;
			pq.pop();
			int sz = adj[u].size();
			for(int i = 0; i < sz; ++i){
				int v = adj[u][i].first;
				int w = adj[u][i].second;
				if(dist[v] > dist[u] + w){
					dist[v] = dist[u] + w;
					pq.push(make_pair(dist[v], v));
					f[v] = u;
				}
			}
		}
		for(int i = 0; i < n; ++i){
			cout << dist[i] << " ";
		}
		cout << endl;
		for(int i = 0; i < n; ++i){
			cout << f[i] << " ";
		}
		cout << endl;
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
					cycle = false;
				}
			}
		}
		return {d1, f, cycle};
	}	
};


int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	weightedGraph g;
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
	g.dijkstra(0, 6);
	return 0;
}
