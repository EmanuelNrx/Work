template <typename type>
vector<vector<int>> findNodeComponents(DfsUndirectedGraph<type> &g, bool ok = true) {
	vector<int> edc = findEdgeComponents(g, ok); 
	vector<vector<int>> ndc(*max_element(edc.begin(), edc.end()) + 1);
	for (int id = 0; id < g.edg.size(); ++id) {
		auto &ed = g.edg[id]; int x = ed.from, y = ed.to;
		ndc[edc[id]].push_back(x); ndc[edc[id]].push_back(y); }
	for (int id = 0; id < ndc.size(); ++id) {
		sort(ndc[id].begin(), ndc[id].end());
		ndc[id].resize(unique(ndc[id].begin(), ndc[id].end()) - ndc[id].begin()); }
	return ndc; }


