template <typename type>
class DinicFlowGraph {

private:

	static const type eps = (type) 0.00000001;

	struct Edge {
		int to, next;
		type cap, flo;
		
		Edge() : 
			to(0), next(0), cap(0), flo(0) {}
		Edge(int _to, int _next, type _cap, type _flo) :
			to(_to), next(_next), cap(_cap), flo(_flo) {}
	};

	int sz, st, fi;
	vector<Edge> edg;
	vector<int> aux, pos, adj, dst, que;

public:

	Dinic(int _sz) : sz(_sz) {
		que = dst = aux = pos = vector<int>(sz, -1); }

	void addEdge(int from, int to, type cap, type rvcap = 0) {
		edg.push_back(Edge(to, aux[from], cap, 0));
		aux[from] = edg.size() - 1;
		edg.push_back(Edge(from, aux[to], rvcap, 0));
		aux[to] = edg.size() - 1; }

	bool bfs(void) {
		fill(begin(dst), end(dst), -1); dst[fi] = 1; que[0] = fi;
		for (int bg = 0, en = 1; bg < en; ++bg) {
			int x = que[bg];
			for (int p = aux[x]; p != -1; p = edg[p].next) {
				const Edge &ed = edg[p],
						   &bk = edg[p ^ 1];
				if (dst[ed.to] == -1 and bk.cap - bk.flo > eps) {
					dst[ed.to] = dst[x] + 1; que[en++] = ed.to; 
					if (ed.to == st) {
						return true; } } } } 
		return false; }

	type dfs(int x, type fl = numeric_limits<type> :: max()) {
		if (x == fi) {
			return fl; }
		type agm;
		for (; adj[x] != -1; adj[x] = edg[adj[x]].next) {
			const Edge &ed = edg[adj[x]];
			if (dst[x] - 1 == dst[ed.to] and ed.cap - ed.flo > eps) {
				agm = dfs(ed.to, min(ed.cap - ed.flo, fl));
				if (agm > eps) {
					edg[adj[x]].flo += agm;
					edg[adj[x] ^ 1].flo -= agm;
					return agm; } } } 
		return 0; }

	type maxFlow(int _st, int _fi) {
		st = _st; fi = _fi; type flo = 0, add1, add2;
		while (bfs()) {
			adj = aux; add2 = 0;
			while ((add1 = dfs(st)) > eps) {
				add2 += add1; } 
			if (add2 <= eps) {
				break; }
			flo += add2; }
		return flo; }

	vector<bool> minCut(int _st, int _fi) {
		maxFlow(_st, _fi);
		vector<bool> ans(sz);
		for (int i = 0; i < sz; ++i) {
			ans[i] = (dst[i] != -1); }
		return ans; }
};

