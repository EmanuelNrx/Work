template <typename type>
vector<bool> findBridges(DfsUndirectedGraph<type> &g, bool ok = true) {
	if (ok) {
		g.dfsAll(); } 
	vector<bool> brd(g.edg.size(), false);
	for (int x = 0; x < g.n; ++x) {
		if (g.prv[x] != -1 and g.mnd[x] == g.dpt[x]) {
			brd[g.pre[x]] = true; } }
	return brd; }


