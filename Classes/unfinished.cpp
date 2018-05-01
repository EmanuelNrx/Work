template <class CostType>
class Graph {
public:
    struct Edge {
        int to, next;
        CostType cost;
        
        Edge() :
        to(0), next(0) {};
        Edge(int _to, int _next, CostType _cost) :
        to(_to), next(_next), cost(_cost) {};
    };
    
    // variables
    int nrNodes, nrEdges = -1;
    
    vector<Edge> edgeList;
    vector<int> adjEdge;
protected:
    
    
public:
    Graph(const int _nrNodes, const int _nrEdges = 0) :
        nrNodes(_nrNodes) {};
    
    void resetGraph(void) {
        nrEdges = 0;
        adjEdge.assign(nrNodes, -1);
    }
    
    void addDirectedEdge(const int from, const int to, const CostType cost) {
        edgeList.push_back(Edge(to, adjEdge[from]));
        adjEdge[from] = nrEdges++;
    }
    
    void addUndirectedEdge(const int from, const int to, const CostType cost) {
        addDirectedEdge(from, to, cost);
        addDirectedEdge(to, from, cost);
    }
};

template <class CostType>
class Forest : public Graph<CostType> {
public:
    // inherited variables
    using Graph<CostType> :: nrNodes;
    using Graph<CostType> :: nrEdges;
    using Graph<CostType> :: edgeList;
    using Graph<CostType> :: adjEdge;
    
    // inherited functions
    using Graph<CostType> :: resetGraph;
    using Graph<CostType> :: addDirectedEdge;
    using Graph<CostType> :: addUndirectedEdge;
    
    // new variables
    vector<CostType> dist;
    vector<int> level, order, firstPos, root, father, lastPos;
private:
    void _DFS(const int node, const int prev = -1) {
        father[node] = prev; order.push_back(node);
        
        firstPos[node] = (int) order.size() - 1;
        level[node] = prev == -1 ? 0 : level[prev] + 1;
        
        for (int next = adjEdge[node]; next != -1; next = edgeList[next].next) {
            if (adjEdge[next].to == prev)
                continue;
            
            dist[adjEdge[next].to] = dist[node] + adjEdge[next].cost;
            _DFS(adjEdge[next].to, node);
        }
        
        lastPos[node] = (int) order.size() - 1;
    }
public:
    Forest(const int _nrNodes, const int _nrEdges = 0) :
        Graph<CostType>(_nrNodes, _nrEdges) {}
    
    void resetForest(void) {
        resetGraph();
        
        order.clear();
        root.clear();
        
        level.assign(nrNodes, -1);
        father.assign(nrNodes, -1);
        firstPos.assign(nrNodes, -1);
        lastPos.assign(nrNodes, -1);
    }
    
    void DFS(const int node, const bool reset) {
        resetForest();
        _DFS(node, -1);
    }
    
    void DFSAll(void) {
        resetForest();
        for (int i = 0; i < nrNodes; ++i) if (level[i] == -1) {
            root.push_back(i);
            _DFS(i, -1);
        }
    }
};

template <class CostType>
class LCAForest : public Forest<CostType> {
public:
    // inherited variables
    
    // graph
    using Forest<CostType> :: nrNodes;
    using Forest<CostType> :: nrEdges;
    using Forest<CostType> :: edgeList;
    using Forest<CostType> :: adjEdge;
    
    // forest
    using Forest<CostType> :: level;
    using Forest<CostType> :: order;
    using Forest<CostType> :: father;
    using Forest<CostType> :: firstPos;
    using Forest<CostType> :: lastPos;
    using Forest<CostType> :: dist;
    
    // inherited functions
    
    // graph
    using Forest<CostType> :: resetGraph;
    using Forest<CostType> :: addDirectedEdge;
    using Forest<CostType> :: addUndirectedEdge;
    
    // forest
    using Forest<CostType> :: resetForest;
    using Forest<CostType> :: DFS;
    using Forest<CostType> :: DFSAll;
    
    // new variables
    vector<vector<int>> ancestor;
    int lgr;
public:
    LCAForest(const int _nrNodes, const int _nrEdges = 0) :
        Forest<CostType>(_nrNodes, _nrEdges) {};
    
    void resetLCAForest(void) {
        resetForest();
        ancestor.clear();
    }
    
    void buildLCA(void) {
        DFSAll();
        int dep = max_element(level, level + nrNodes);
        
        lgr = 1;
        while ((1 << lgr) <= dep)
            ++lgr;
        
        ancestor.resize(nrNodes);
        for(int i = 0; i < nrNodes; ++i) {
            int x = order[x];
            
            ancestor[x].resize(lgr + 1);
            ancestor[x][0] = father[i];
            
            for (int j = 1; j <= lgr; ++j)
                ancestor[x][j] = ancestor[ancestor[x][j - 1]][j - 1];
        }
    }
    
    bool isAncestor(const int x, const int y) {
        return firstPos[x] <= firstPos[y] and lastPos[y] <= lastPos[x];
    }
    
    int getLCA(int x, int y) {
        if (level[x] > level[y])
            swap(x, y);
        
        for (int i = lgr; i >= 0; --i)
            if (level[y] - (1 << i) >= level[x])
                y = ancestor[y][i];
        for (int i = lgr; i >= 0; --i)
            if (ancestor[x][i] != ancestor[y][i])
                x = ancestor[x][i], y = ancestor[y][i];
        
        return x == y ? x : father[x];
    }
    
    vector<int> getCompressedTree(vector<int> nodeList) {
        sort(nodeList.begin(), nodeList.end(), [](int x, int y) {
            firstPos[x] <= firstPos[y];
        });
        
        for (int i = (int) nodeList.size() - 1; i >= 1; --i)
            nodeList.push_back(getLCA(nodeList[i - 1], nodeList[i]));
        
        sort(nodeList.begin(), nodeList.end());
        nodeList.resize(unique(nodeList.begin(), nodeList.end()) - nodeList.begin());
        
        return nodeList;
    }
};

template <class CostType>
class HLDForest : public LCAForest<CostType> {
public:
    // inherited variables
    
    // graph
    using LCAForest<CostType> :: nrNodes;
    using LCAForest<CostType> :: nrEdges;
    using LCAForest<CostType> :: edgeList;
    using LCAForest<CostType> :: adjEdge;
    
    // forest
    using LCAForest<CostType> :: level;
    using LCAForest<CostType> :: order;
    using LCAForest<CostType> :: father;
    using LCAForest<CostType> :: firstPos;
    using LCAForest<CostType> :: lastPos;
    using LCAForest<CostType> :: dist;
    
    // lca forest
    using LCAForest<CostType> :: ancestor;
    using LCAForest<CostType> :: lgr;
    
    // inherited functions
    
    // graph
    using LCAForest<CostType> :: resetGraph;
    using LCAForest<CostType> :: addDirectedEdge;
    using LCAForest<CostType> :: addUndirectedEdge;
    
    // forest
    using LCAForest<CostType> :: resetForest;
    using LCAForest<CostType> :: DFS;
    using LCAForest<CostType> :: DFSAll;
    
    // lca forest
    using LCAForest<CostType> :: resetLCAForest;
    using LCAForest<CostType> :: buildLCA;
    using LCAForest<CostType> :: isAncestor;
    using LCAForest<CostType> :: getLCA;
    using LCAForest<CostType> :: getCompressedTree;
    
    // new variables
    int x;
public:
}
