template <typename type>
class DfsUndirectedGraph : public UndirectedGraph<type> {

public:

	using UndirectedGraph<type> :: n;
	using UndirectedGraph<type> :: gph;
	using UndirectedGraph<type> :: edg;

	int att;
	vector<type> dst;
	vector<int> prv, pre, ord, pos, end,	
				szt, rot, dpt, mnd, was; 

	DfsUndirectedGraph(int _n) :
		UndirectedGraph<type>(_n) {}

	void initialize(void) {
		prv = pre = pos = end = rot = dpt = mnd = was = vector<int>(n, -1);
		ord.clear(); szt = vector<int>(n, 0); dst = vector<type>(n); att = 0; }

	void clear(void) {
		prv.clear(); pre.clear(); ord.clear(); pos.clear(); end.clear(); szt.clear();
		rot.clear(); dpt.clear(); mnd.clear(), dst.clear(); was.clear(); }

private:
	
	void doDfs(int x) {
		was[x] = att; pos[x] = (int) ord.size(); 
		ord.push_back(x); szt[x] = 1; mnd[x] = dpt[x];
		for (int id : gph[x]) {
			if (id == pre[x]) {
				continue; }
			auto &ed = edg[id]; int y = ed.from ^ ed.to ^ x;
			if (was[y] == att) {
				mnd[x] = min(mnd[x], dpt[y]); continue; }
			dpt[y] = dpt[x] + 1; dst[y] = dst[x] + ed.cost;
			prv[y] = x; pre[y] = id; rot[y] = rot[x] != -1 ? rot[x] : y; 
			doDfs(y); szt[x] += szt[y]; mnd[x] = min(mnd[x], mnd[y]); }
		end[x] = (int) ord.size() - 1; }

	void doDfsFrom(int x) {
		dpt[x] = 0; dst[x] = type{}; rot[x] = x; 
		prv[x] = pre[x] = -1; ++att; doDfs(x); }   

public:

	void dfs(int x, bool cle = true) {
		if (prv.empty()) {
			initialize(); }
		else if (cle) {
			ord.clear(); }
		doDfsFrom(x); }

	void dfsAll(void) {
		initialize();
		for (int x = 0; x < n; ++x) {
			if (dpt[x] == -1) {
				doDfsFrom(x); } } }
}; 

