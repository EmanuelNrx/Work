// unfinished
template <class type>
class MaxFlow {
private:
    static constexpr type INF = numeric_limits<type> :: max() / 2;
    static constexpr long double EPS = 1e-6;
    
    static int cmp(const type x) {
        if (fabs(x) < EPS)
            return 0;
        return x < 0 ? -1 : 1;
    }
    
    struct edge {
        int x, y; type flo, cap;

        edge(int _x, int _y, type _cap) :
            x(_x), y(_y), cap(_cap), flo(0) {};
    };
    
    vector<edge> lst;
    vector<vector<int>> edg;
    
    void bfs(const int src, const int dst) {
        vector<int> dis(edg.size(), INF); dis[src] = 0;
        
        for (deque<int> que(1, src); que.size(); que.pop_front()) {
            int x = que.front();
            if (x == dst) continue;
            
            for (int it : edg[x]) {
                int y = lst[it].y;
                
                if (!cmp(lst[it].cap - lst[it].flo))
                    continue;
                if (dis[y] > dis[x] + 1) {
                    dis[y] = dis[x] + 1;
                    que.push_back(y);
                }
            }
        }
    }
    
    type dfs(const int x, const int dst, type cap) {
        if (!cmp(cap)) return 0;
        if (x == dst) return cap;
        
        for (int it : edg[x]) {
            int y = lst[it].y;
            
            if (!cmp(lst[it].cap - lst[it].flo))
                continue;
            type aux = dfs(y, dst, min(cap, lst[it].cap - lst[it].flo));
            
            if (cmp(aux) > 0) {
                lst[it].flo += aux;
                lst[it ^ 1].flo -= aux;
                cap -= aux;
            }
        }
        
        return cap;
    }
public:
    MaxFlow(int sz) {
        edg.resize(sz);
    }
    
    void addUndirectedEdge(const int x, const int y, const type c) {
        edg[x].push_back((int) lst.size()); lst.push_back(edge(x, y, c));
        edg[y].push_back((int) lst.size()); lst.push_back(edge(y, x, c));
    }
    
    void addDirectedEdge(const int x, const int y, const type c) {
        edg[x].push_back((int) lst.size()); lst.push_back(edge(x, y, c));
        edg[y].push_back((int) lst.size()); lst.push_back(edge(y, x, 0));
    }
    
    type getMaxFlow(const int src, const int dst) {
        for (int i = 0; i < lst.size(); ++i)
            lst[i].flo = 0;
        
        type aux, ans = 0;
        do {
            bfs(src, dst);
            aux = dfs(src, dst, INF); ans += aux;
        } while (cmp(aux));
        
        return ans;
    }
};
