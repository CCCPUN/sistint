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
		return f > u.f; 
		//note: pirority queue's top element is the greatest,
		//ordering from max to min sets priority queue's top as min
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
}
node shuffle(node root){ //Desorder the identity state
	set<vector<int>> done;
	done.insert(root.a);
	int cnt = 0;
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
	//h0 = total manhattan distance, h1 = total number of misplacements
	int h0 = 0, h1 = 0; 
	for(int i = 0; i<n; ++i){
		h1+=(a[i]!=(i+1)%n);
		int x = a[i] ? a[i] : 9;
		x--;
		h0+=abs(i/m - x/m) + abs(i%m - x%m);
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
	cout << "Enter the number of tiles: " << endl;
	cin>>n;
	n++;
	m = sqrt(n);
	id.assign(n, 0);
	dx = {m, -m, 1, -1};
	for(int i=0; i<n-1; ++i) id[i] = i+1; 
	node root;
	root.a = id, root.d = 0, root.i = n-1;
	int last;
	cout<<"Enter the number of iterations: "<<endl;
	cin>>last;
	double bfsav = 0, ldfsav = 0, idfsav = 0, ast0av = 0, ast1av = 0;
	chrono::steady_clock::time_point begin = std::chrono::steady_clock::now(); //Start time;
	chrono::steady_clock::time_point end = std::chrono::steady_clock::now(); //End time;
	cout<<"Enter the depth limit: "<<endl;
	cin>>limit;
	l = limit;
	srand(time(NULL));
	for(int i=0; i<last; ++i){
		node u = shuffle(root);
		cout<<"Iteration:  "<<i+1<<endl;
		cout<<"Current state: "<<endl;
		print(u);
		cout<<"BFS: "<<endl;
		begin = std::chrono::steady_clock::now();
		bfs(u);
		end = std::chrono::steady_clock::now();
		bfsav += chrono::duration_cast<std::chrono::microseconds>(end - begin).count(); 
		
		cout<<"Limited DFS: "<<endl;
		set<vector<int>> done;
		begin = std::chrono::steady_clock::now();
		ldfs(u, done);
		end = std::chrono::steady_clock::now();
		ldfsav += chrono::duration_cast<std::chrono::microseconds>(end - begin).count(); 
		
		cout<<"Iterative DFS: "<<endl;
		begin = std::chrono::steady_clock::now();
		idfs(u, done);
		end = std::chrono::steady_clock::now();
		idfsav += chrono::duration_cast<std::chrono::microseconds>(end - begin).count(); 
		
		cout<<"A* based on total manhattan distance"<<endl;
		begin = std::chrono::steady_clock::now();
		ast(u, 0);
		end = std::chrono::steady_clock::now();
		ast0av += chrono::duration_cast<std::chrono::microseconds>(end - begin).count(); 
		
		cout<<"A* based on total number of misplacements"<<endl;
		begin = std::chrono::steady_clock::now();
		ast(u, 1);
		end = std::chrono::steady_clock::now();
		ast1av += chrono::duration_cast<std::chrono::microseconds>(end - begin).count(); 
		cout<<endl;
	}
	cout<<"********************************************************************"<<endl;
	cout<<"Total time used : "<<endl;
	cout<<"BFS: "<<bfsav/(double)last<<endl;
	cout<<"Limited DFS : "<<ldfsav/ (double)last<<endl;
	cout<<"Iterative DFS : "<<idfsav/ (double)last<<endl;
	cout<<"A* based on total manhattan distance : "<<ast0av/(double)last<<endl;
	cout<<"A* based on total number of misplacements : "<<ast1av/(double)last<<endl;
	return 0;
}
