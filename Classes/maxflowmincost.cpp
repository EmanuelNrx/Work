// unfinished
template <class type1, class type2>
class MaxFlowMinCost {
private:
    static constexpr type1 INF = numeric_limits<type2> :: max() / 2;
    static constexpr long double EPS = 1e-6;
    
    template <class type>
    static int cmp(const type x) {
        if (fabs(x) < EPS)
            return 0;
        return x < 0 ? -1 : 1;
    }
    
    struct edge {
        int x, y; type1 flo, cap; type2 cst;
        
        edge(int _x, int _y, type1 _cap, type2 _cst) :
            x(_x), y(_y), cap(_cap), flo(0), cst(_cst) {};
    };
    
    vector<vector<int>> edg;
    vector<edge> lst; vector<type2> ids;
    
    void bf(const int src, const int dst) {
        ids.assign(edg.size(), INF); ids[src] = 0;
        vector<bool> oki(edg.size(), false); oki[src] = true;

        for (deque<int> que(1, src); que.size(); oki[que.front()] = false, que.pop_front()) {
            int x = que.front();
            if (x == dst) continue;
            
            for (int it : edg[x]) {
                int y = lst[it].y;
                
                if (!cmp(lst[it].cap - lst[it].flo))
                    continue;
                if (cmp(ids[y] - ids[x] - lst[it].cst) > 0) {
                    ids[y] = ids[x] + lst[it].cst;
                    if (!oki[y])
                        oki[y] = true, que.push_back(y);
                }
            }
        }
    }
    
    void dijkstra(const int src, const int dst) {
        vector<int> dis(edg.size(), INF); dis[src] = 0;
        priority_queue<pair<type1, int>, vector<pair<type1, int>>, greater<pair<type1, int>>> prq;
        
        for (prq.push(make_pair(0, src)); prq.size(); ) {
            pair<type1, int> x = prq.top(); prq.pop();
            
            if (!cmp(dst[x.second] - x.first))
                continue;
            
            for (int it : edg[x.second]) {
                int y = lst[it].y;
                
                if (!cmp(lst[it].cap - lst[it].flo))
                    continue;
                
                if (cmp(dis[y] - (dis[x.second] + ids[x.second] - ids[y] + lst[it].cst)) > 0) {
                    dis[y] = dis[x.second] + ids[x.second] - ids[y] + lst[it].cst;
                    if (y != dst)
                        prq.push(make_pair(dis[y], y));
                }
            }
        }
    }
    
    type1 dfs(int x, int dst, type1 cap, type2 &ans) {
        if (!cmp(cap)) return 0;
        if (x == dst) return cap;
        
        for (int it : edg[x]) {
            int y = lst[it].y;
            
            if (!cmp(lst[it].cap - lst[it].flo))
                continue;
            type1 aux = dfs(y, dst, min(cap, lst[it].cap - lst[it].flo), ans);
            
            if (cmp(aux) > 0) {
                lst[it].flo += aux;
                lst[it ^ 1].flo -= aux;
                cap -= aux; ans += lst[it].cst * aux;
            }
        }
        
        return cap;
    }
public:
    MaxFlowMinCost(int sz) {
        edg.resize(sz);
    }
    
    void addUndirectedEdge(const int x, const int y, const type1 c, const type2 d) {
        edg[x].push_back((int) lst.size()); lst.push_back(edge(x, y, c,  d));
        edg[y].push_back((int) lst.size()); lst.push_back(edge(y, x, c, -d));
    }
    
    void addDirectedEdge(const int x, const int y, const type1 c, const type2 d) {
        edg[x].push_back((int) lst.size()); lst.push_back(edge(x, y, c,  d));
        edg[y].push_back((int) lst.size()); lst.push_back(edge(y, x, 0, -d));
    }
    
    type2 getMaxFlow(const int src, const int dst) {
        bf(src, dst);
        
        type1 aux; type2 ans = 0;
        do {
            dijkstra(src, dst);
            aux = dfs(src, dst, INF, ans);
        } while (cmp(aux));
        
        return ans;
    }
};
