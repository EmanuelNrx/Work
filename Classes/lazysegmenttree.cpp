template <class NodeType, class UpdateType>
class LazySegmentTree {
private:
    int siz, _lef, _rig;
    NodeType *sgt; UpdateType val;
    
    NodeType mergeSons(NodeType son1, NodeType son2);
    void updateLazy(NodeType &nod, NodeType &son1, NodeType &son2, bool ok);
    
    void _updateLazy(int nod, int lef, int rig) {
        if (lef == rig)
            updateLazy(sgt[nod], sgt[nod], sgt[nod], false);
        else
            updateLazy(sgt[nod], sgt[nod << 1], sgt[nod << 1 | 1], true);
    }
    
    void buildTree(int nod, int lef, int rig, UpdateType *arr) {
        if (lef == rig)
            sgt[nod] = tree(arr[lef], lef);
        else {
            int mid = (lef + rig) >> 1;
            
            buildTree(nod << 1, lef, mid, arr);
            buildTree(nod << 1 | 1, mid + 1, rig, arr);
            
            sgt[nod] = mergeSons(sgt[nod << 1], sgt[nod << 1 | 1]);
        }
    }
    /*
    void buildTree(int nod, int lef, int rig, UpdateType val) {
        if (lef == rig)
            buildNode(sgt[nod], val, lef);
        else {
            int mid = (lef + rig) >> 1;
            
            buildTree(nod << 1, lef, mid, val);
            buildTree(nod << 1 | 1, mid + 1, rig, val);
            
            sgt[nod] = mergeSons(sgt[nod << 1], sgt[nod << 1 | 1]);
        }
    }
    */
    void updateTree(int nod, int lef, int rig) {
        if (_lef <= lef and rig <= _rig) {
            sgt[nod].lazy += val;
            _updateLazy(nod, lef, rig);
        }
        else {
            int mid = (lef + rig) >> 1;
            
            _updateLazy(nod << 1, lef, mid);
            _updateLazy(nod << 1 | 1, mid + 1, rig);
            
            if (_lef <= mid)
                updateTree(nod << 1, lef, mid);
            if (mid < _rig)
                updateTree(nod << 1 | 1, mid + 1, rig);
            
            sgt[nod] = mergeSons(sgt[nod << 1], sgt[nod << 1 | 1]);
        }
    }
    
    NodeType queryTree(int nod, int lef, int rig) {
        if (_lef <= lef and rig <= _rig)
            return sgt[nod];
        else {
            int mid = (lef + rig) >> 1;
            
            _updateLazy(nod << 1, lef, mid);
            _updateLazy(nod << 1 | 1, mid + 1, rig);
            
            if (_rig <= mid)
                return queryTree(nod << 1, lef, mid);
            if (mid < _lef)
                return queryTree(nod << 1 | 1, mid + 1, rig);
            
            return mergeSons(queryTree(nod << 1, lef, mid),
                             queryTree(nod << 1 | 1, mid + 1, rig));
        }
    }
public:
    LazySegmentTree(int dim) {
        sgt = new NodeType[dim << 2]; siz = dim;
    }
    
    inline void resize(int dim) {
        siz = dim;
    }
    
    inline void build(UpdateType *arr) {
        buildTree(1, 1, siz, arr);
    }
    /*
    inline void build(UpdateType val) {
        buildTree(1, 1, siz, val);
    }
    */
    inline void update(int lef, int rig, UpdateType cns) {
        _lef = lef; _rig = rig; val = cns;
        updateTree(1, 1, siz);
    }
    
    inline NodeType query(int lef, int rig) {
        _lef = lef; _rig = rig;
        return queryTree(1, 1, siz);
    }
}; LazySegmentTree<tree, long long> mySegmentTree(DIM);

template <class NodeType, class UpdateType>
NodeType LazySegmentTree<NodeType, UpdateType>::mergeSons(NodeType son1, NodeType son2) {
    if (son1.value <= son2.value)
        return son1;
    else
        return son2;
}

template <class NodeType, class UpdateType>
void LazySegmentTree<NodeType, UpdateType>::updateLazy(NodeType &nod, NodeType &son1, NodeType &son2, bool ok) {
    if (ok)
        son1.lazy += nod.lazy, son2.lazy += nod.lazy;
    nod.value += nod.lazy; nod.lazy = 0;
}
