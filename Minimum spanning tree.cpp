vector<int> parent, rating;
void make_set(int v) {
	parent[v] = v;
	rating[v] = 0;
}
int find_set(int v) {
	if (v == parent[v])
		return v;
	return parent[v] = find_set(parent[v]);
}
void union_sets(int a, int b) {
	a = find_set(a);
	b = find_set(b);
	if (a != b) {
		if (rating[a] < rating[b])
			swap(a, b);
		parent[b] = a;
		if (rating[a] == rating[b])
			rating[a]++;
	}
}
struct Edge {
	int u, v, weight;
	bool operator<(Edge const& other) {
		return weight < other.weight;
	}
};
int n;
vector<Edge> edges;
int cost = 0;
vector<Edge> result;
parent.resize(n + 1);
rating.resize(n + 1);
for (int i = 0; i <= n; i++)
	make_set(i);
sort(edges.begin(), edges.end());
for (Edge e : edges) {
	if (find_set(e.u) != find_set(e.v)) {
		cost += e.weight;
		result.push_back(e);
		union_sets(e.u, e.v);
	}
}
