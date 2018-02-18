// done | further optimization required (eventually)
template <class CapacityType>
class MaxFlow {
private:
    static constexpr int NIL = -1;
    static constexpr long double EPS = 1e-6;
   
    static constexpr CapacityType INF =
        std::numeric_limits<CapacityType> :: max() / 2;
     
    template <class type>
    int cmp(type x) {
        if (-EPS < x and x < EPS)
            return 0;
        return x < 0 ? -1 : 1;
    }
     
    struct Edge {
        int nod, nxt;
        CapacityType cap, flo;
 
        Edge() :
            nod(0), nxt(0), cap(0), flo(0) {};
        Edge(int _nod, int _nxt, CapacityType _cap) :
            nod(_nod), nxt(_nxt), cap(_cap), flo(0) {};
    }; std::vector<Edge> lst;
     
    std::vector<bool> oki; int ptr = 0;
    std::vector<int> beg, que, adj, dis;
     
    bool bfs(const int src, const int dst) {
        std::fill(dis.begin(), dis.end(), (CapacityType)INF);
        dis[src] = 0; que[0] = src;
        
        for (int qbg = 0, qen = 0; qbg <= qen; ++qbg) {
            const int x = que[qbg];
            
            for (int it = beg[x]; it != NIL; it = lst[it].nxt) {
                const int y = lst[it].nod;
                 
                if (cmp(lst[it].cap - lst[it].flo) and dis[y] == INF)
                    dis[y] = dis[x] + 1, que[++qen] = y;
            }
        }
         
        return dis[dst] != INF;
    }
     
    CapacityType dfs(const int x, const int dst, const CapacityType cap) {
        if (!cmp(cap) or x == dst)
            return cap;
        
        for (; adj[x] != NIL; adj[x] = lst[adj[x]].nxt) {
            const int y = lst[adj[x]].nod;
         
            if (cmp(lst[adj[x]].cap - lst[adj[x]].flo) and dis[y] == dis[x] + 1) {
                const CapacityType aux = dfs(y, dst, std::min(cap, lst[adj[x]].cap - lst[adj[x]].flo));
                
                if (cmp(aux)) {
                    lst[adj[x]].flo += aux;
                    lst[adj[x] ^ 1].flo -= aux;
                    return aux;
                }
            }
        }
         
        return 0;
    }
     
    void fill(const int x) {
        oki[x] = true;
         
        for (int it = beg[x]; it != NIL; it = lst[it].nxt) {
            const int y = lst[it].nod;
             
            if (cmp(lst[it].cap - lst[it].flo) and !oki[y])
                fill(y);
        }
    }
public:
    MaxFlow(int szn, int szm) {
        dis.resize(szn); beg.resize(szn);
        que.resize(szn); adj.resize(szn);
        oki.resize(szn); lst.resize(szm); // m != n
         
        std::fill(beg.begin(), beg.end(), (int)NIL);
    }
     
    inline void addDirectedEdge(const int x, const int y, const CapacityType cap) {
        lst[ptr] = Edge(y, beg[x], cap); beg[x] = ptr++;
        lst[ptr] = Edge(x, beg[y],  0 ); beg[y] = ptr++;
    }
     
    inline void addUndirectedEdge(const int x, const int y, const CapacityType cap) {
        lst[ptr] = Edge(y, beg[x], cap); beg[x] = ptr++;
        lst[ptr] = Edge(x, beg[y], cap); beg[y] = ptr++;
    }
     
    CapacityType getMaxFlow(const int src, const int dst) {
        CapacityType aux, ans = 0;
        for (int i = 0; i < ptr; ++i)
            lst[i].flo = 0;
         
        while (bfs(src, dst)) {
            copy(beg.begin(), beg.end(), adj.begin());
             
            do {
                aux = dfs(src, dst, INF);
                ans += aux;
            } while (cmp(aux));
        }
         
        return ans;
    }
     
    CapacityType getMinCut(const int src, const int dst, std::vector<int> &ans) {
        std::fill(oki.begin(), oki.end(), false);
        CapacityType sol = getMaxFlow(src, dst); fill(src);
         
        ans.clear();
        for (int i = 0; i < oki.size(); ++i)
            if (oki[i]) ans.push_back(i);
         
        return sol;
    }
};
