#include <bits/stdc++.h>

using namespace std;



class unweightedGraph{
private:
	vector<int> adj[100100];
	vector<int> dist;
public:
	unweightedGraph(){
		dist.resize(100100, 0);
	}

	void add(int a, int b){
		adj[a].push_back(b);
		//adj[b].push_back(a); <------- Se o grafo for não direcionado
	}

	void dfs_visit(int node, int *visited){
		cout << node << endl;
		visited[node] = 1;
		int sz = adj[node].size();
		for(int i = 0; i < sz; ++i){
			if(visited[adj[node][i]])continue;
			dfs_visit(adj[node][i], visited);
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
			if(visited[adj[node][i]])continue;
			dfs_visitTopological(adj[node][i], visited, topological);
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
			cout << u << endl;
			q.pop();
			int sz = adj[u].size();
			for(int i = 0; i < sz; ++i){
				int v = adj[node][i];
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
};


int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	unweightedGraph g;
	g.add(0,3);
	g.add(1,0);
	g.add(1,2);
	g.add(1,3);
	g.add(2,3);
	g.add(4,0);
	g.add(4,1);
	g.dfs(4);
	return 0;
}
