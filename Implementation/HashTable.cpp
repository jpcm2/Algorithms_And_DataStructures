#include <bits/stdc++.h>

using namespace std;

struct Node{
	int time;
	int total;
	string name;
};

class HashTable{
private:
	int m; // Quantidade de códigos.
	double alpha;
public:
	Node *table;
	int n; //Quantidade de numeros ja adicionados na tabela.
	void Rehash(){
		Node *new_table;
		new_table = new Node[m];
		for(int i = 0; i < m; ++i){
			new_table[i].name = table[i].name;
			new_table[i].time = table[i].time;
			new_table[i].total = table[i].total;
		}
		int m0 = m;
		m = 2*m + 1;
		Node *buff = new Node[m];
		delete[] table;
		table = buff;
		for(int i = 0; i < m; ++i){
			table[i].name = "-";
			table[i].time = -1;
			table[i].total = -1;
		}
		for(int i = 0; i < m0; ++i){
			if(new_table[i].name == "-")continue;
			inserir(new_table[i].name, new_table[i].time, new_table[i].total);
		}
		delete[] new_table;
	}
	HashTable(int mm){
		//cout << "Criei a Hash papai!" << endl;
		m = mm;
		table = new Node[m];
		for(int i = 0; i < m; ++i){
			table[i].name = "-";
			table[i].time = -1;
			table[i].total = -1;
		}
		n = 0;
		alpha = 0.0;
	}
	int h0(string s){
		int temp = 0;
		int sz = s.size();
		for(int i = 0; i < sz; ++i){
			temp += int(s[i]) * i;
		}
		temp %= m;
		return temp;
	}
	int inserir(string s, int tempo, int total){
		alpha = n*(1.0)/(m*1.0); //Coeficiente de capacidade
		//cout << m << " " << n << endl;
		if(alpha >= 0.5){
			Rehash();
		}
		int index = h0(s);
		while(table[index].time != -1){
			index = (index + 1)%m;
		}
		//cout << index << endl;
		table[index] = {tempo, total, s};
		return index;
	}
	int find(string s){
		int index = h0(s);
		while(table[index].name != s){
			index = (index + 1)%m;
		}
		return index;
	}
	~HashTable(){
		delete[] table;
	}
};

int main(){
	int m;
	cin >> m;
	HashTable hash(m);
	string cmd;
	cin >> cmd;
	while(cmd != "END"){
		if(cmd == "ADD"){
			string s;
			int t;
			cin >> s >> t;
			int ans = hash.inserir(s, t, 0);
			hash.n++;
			cout << s << " " << ans << endl;
		}else if(cmd == "PLAY"){
			string s;
			cin >> s;
			int pos = hash.find(s);
			hash.table[pos].total += hash.table[pos].time;
			cout << s << " " << hash.table[pos].total << endl;
		}else if(cmd == "TIME"){
			string s;
			cin >> s;
			int pos = hash.find(s);
			cout << s << " " << hash.table[pos].total << endl;
		}
		cin >> cmd;
	}
	return 0;
}