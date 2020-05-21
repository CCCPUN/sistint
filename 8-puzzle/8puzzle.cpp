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
int n, m, limit, l; // n- puzzle, m = sqrt(n), limit = max depth, limit of depth;
vector<int> dx, id; //dx = all possible moves, id = identity state = 1, 2, ... , n, 0; 
struct node{ // Nodes of the "tree"
	vector<int> a; int d, i, f, g, h; 
	bool operator<(const node& u) const{//Sorting the nodes based on the value of f, from min to max;
		return f < u.f;
	}
}; 
/*
 * a = state of the game;
 * d = number of moves so far;
 * i = position of tile 0
 * f , g, h = functions and heuristics for A*
 */
bool check(int from, int to){ //Checks whether a movement is valid or not
	if(to > 0) return ((from + to)%m >= from%m) && (from+to < n);
	return ((from + to + m)%m <= from%m) && (from+to >= 0);
}
void print(node& u){ //Prettty obvious
	for(int i = 0; i<n; ++i){
		cout<<u.a[i]<<" ";
		if(i%m == m-1) cout<<endl;
	}
}
void finish(node& id){//Prints number of moves needed
	cout<<"Number of moves needed: "<<id.d<<endl;
	print(id);
}
node shuffle(node root){ //Desorder the identity state
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
void bfs(node root){ //Prettty obvious
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
void ldfs(node u, set<vector<int>>& done){ //Limited DFS
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
void idfs(node u, set<vector<int>>& done){ //Iterative DFS
	for(int i = 0; i<=limit; ++i){ //Try all possible depths up to max depth
		cout<<"Max depth: "<<i<<endl;
		l = i;
		set<vector<int>> done;
		ldfs(u, done); //Calls limited depth search;
	}
}
int heuris(vector<int>& a, int h){
	int h0 = 0, h1 = 0;
	for(int i = 0; i<n; ++i){
		h1+=(a[i]!=(i+1)%n);
		int x = a[i] ? a[i] : 9;
		h0+=abs((i+1)/m - x/m) + abs(i%m - (x-1)%m);
	}
	if(h) return h1;
	return h0;
}
void ast(node root, int h){ //A* search
	priority_queue<node> q;
	q.push(root);
	set<vector<int>> done;
	while(!q.empty()){
		node u = q.top(); q.pop();
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
					v.g = u.g+1, v.h = heuris(v.a, h);
					v.f = v.g + v.h;
					q.push(v);
					done.insert(v.a);
				}else swap(v.a[v.i], v.a[v.i + k]);
			}
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
	node u = shuffle(root);
	cout<<"Current state: "<<endl;
	print(u);
	cout<<"BFS: "<<endl;
	bfs(u);
	cout<<"Enter the depth limit: "<<endl;
	cin>>limit;
	cout<<"Limited DFS: "<<endl;
	set<vector<int>> done;
	l = limit;
	ldfs(u, done);
	cout<<"Iterative DFS: "<<endl;
	idfs(u, done);
	cout<<"A* based on total manhattan disntace"<<endl;
	ast(u, 0);
	cout<<"A* based on total number of missplacemenst"<<endl;
	ast(u, 1);
	return 0;
}
