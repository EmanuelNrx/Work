template <typename type>
vector<bool> findCutPoints(DfsUndirectedGraph<type> &g, bool ok = true) {
	if (ok) {
		g.dfsAll(); }
	vector<bool> ctp(g.n, false);
	for (int x = 0; x < g.n; ++x) {
		if (g.prv[x] != -1 and g.mnd[x] >= g.dpt[g.prv[x]]) {
			ctp[g.prv[x]] = true; } }
	vector<int> chl(g.n, 0);
	for (int x = 0; x < g.n; ++x) {
		if (g.prv[x] != -1) {
			++chl[g.prv[x]]; } }
	for (int x = 0; x < g.n; ++x) {
		if (g.prv[x] == -1 and chl[x] < 2) {
			ctp[x] = false; } }
	return ctp; }


