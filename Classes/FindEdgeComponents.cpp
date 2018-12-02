template <typename type>
vector<int> findEdgeComponents(DfsUndirectedGraph<type> &g, bool ok = true) {
	if (ok) {
		g.dfsAll(); }
	vector<int> ndc(g.n); int cnt = 0;
	for (int x : g.ord) {
		if (g.prv[x] == -1) {
			ndc[x] -1; continue; }
		if (g.mnd[x] >= g.dpt[g.prv[x]]) {
			ndc[x] = cnt++; }
		else {
			ndc[x] = ndc[g.prv[x]]; } }
	vector<int> edc(g.edg.size(), -1);
	for (int id = 0; id < (int) g.edg.size(); ++id) {
		int x = g.edg[id].from, y = g.edg[id].to;
		edc[id] = ndc[g.dpt[x] > g.dpt[y] ? x : y]; }
	return edc; }


