#include <bits/stdc++.h>
using namespace std;
/* * * *   * * *   	* * * */
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
#define ms(a,v) memset(a,v,sizeof a)
/* * * *   * * *   	* * * */
/* *
 *
 * I love Ylva Eriksson
 *
 * */
int n, m, l;
vector<int> dx, id;
struct node{
	vector<int> a;
	int d, i, f, g, h;
};
bool check(int from, int to){
	if(to > 0) return ((from + to)%m >= from%m) && (from+to < n);
	return ((from + to + m)%m <= from%m) && (from+to >= 0);
}
void print(node& u){
	for(int i = 0; i<n; ++i){
		cout<<u.a[i]<<" ";
		if(i%m == m-1) cout<<endl;
	}
}
void finish(node& id){
	cout<<"Finish: moves: "<<id.d<<endl;
	print(id);
}
node shuffle(node root){
	set<vector<int>> done;
	done.insert(root.a);
	int cnt = 0;
	srand(time(NULL));
	while(cnt < 14){
		int k = rand()%4;
		k = dx[k];
		if(check(root.i, k)){
			swap(root.a[root.i], root.a[root.i + k]);
			if(done.count(root.a)) {
				swap(root.a[root.i], root.a[root.i + k]);
			}else root.i+=k, cnt++;
		}
	}
	return root;
}
void bfs(node root){
	cout<<"start: "<<endl;
	print(root);
	queue<node> q;
	set<vector<int>> done;
	q.push(root);
	while(!q.empty()){
		node u = q.front(); q.pop();
		if(u.a == id){
			finish(u);
			return;
		}
		for(int k : dx){
			if(check(u.i, k)){
				node v = u;
				swap(v.a[v.i], v.a[v.i + k]);
				if(!done.count(v.a)){
					v.i+=k, v.d++;
					q.push(v);
					done.insert(v.a);
				}else swap(v.a[v.i], v.a[v.i + k]);
			}
		}
	}
}
void ldfs(node u, set<vector<int>>& done){
	if(done.count(u.a) || u.d > l) return;
	if(u.a == id){
		finish(u);
		return;
	}
	done.insert(u.a);
	for(int k : dx){
		if(check(u.i, k)){
			node v = u;
			swap(v.a[v.i], v.a[v.i + k]);
			v.i+=k, v.d++;
			ldfs(v, done);
		}
	}
}
int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin>>n;
	n++;
	m = sqrt(n);
	id.assign(n, 0);
	dx = {m, -m, 1, -1};
	for(int i=0; i<n-1; ++i) id[i] = i+1; 
	node root;
	root.a = id, root.d = 0, root.i = n-1;
	cout<<"bfs: "<<endl;
	bfs(shuffle(root));
	cin>>l;
	cout<<"ldfs"<<endl;
	node u = shuffle(root);
	print(u);
	set<vector<int>> done;
	ldfs(u, done);
	return 0;
}

