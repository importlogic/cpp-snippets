/*
	1. This code assumes a 0 based graph [ g ] with n vertices.
	2. Everything has been done you just need to call get_lca() function.
*/

const int LOG = log2(n) + 1;
vector<vector<int>> up(n, vector<int>(LOG, -1));
vector<int> depth(n);

function<void(int, int, int)> settingParents = [&](int node, int parent, int d) {
	up[node][0] = parent;
	depth[node] = d;

	for(int i = 1; i < LOG; i++){
		if(up[node][i - 1] != -1)
			up[node][i] = up[up[node][i - 1]][i - 1];
	}

	for(auto child : g[node]){
		if(child != parent)
			settingParents(child, node, d + 1);
	}
};

function<int(int, int)> get_lca = [&](int x, int y) -> int {
	if(depth[x] < depth[y])
		swap(x, y);

	int dx = depth[x] - depth[y];

	for(int i = LOG - 1; i > -1; i--){
		if((dx >> i) & 1)
			x = up[x][i];
	}

	if(x == y)
		return x;

	for(int i = LOG - 1; i > -1; i--){
		if(up[x][i] != up[y][i]){
			x = up[x][i];
			y = up[y][i];
		}
	}

	return up[x][0];
};

settingParents(0, -1, 0);