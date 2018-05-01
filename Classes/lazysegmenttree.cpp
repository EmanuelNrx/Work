// unverified
class LazySegmentTree {
private:
    struct Node {
        //EDIT HERE
        
    } *sgt;
    int siz, _lef, _rig;
    
    void updateLazy(int nod, int lef, int rig) {
        //EDIT HERE
    }
    
    Node mergeSons(Node son1, Node son2) {
        //EDIT HERE
        
    }
    
    template <typename Type>
    void updateNode(int nod, int lef, int rig, Type val) {
        //EDIT HERE
        
        updateLazy(nod, lef, rig);
    }
    
    template <typename Type>
    void _buildTree(int nod, int lef, int rig, Type *&arr) {
        if (lef == rig)
            _updateNode(nod, lef, rig, arr[lef]);
        else {
            int mid = (lef + rig) >> 1;
            
            _buildTree(nod << 1, lef, mid, arr);
            _buildTree(nod << 1 | 1, mid + 1, rig, arr);
            
            sgt[nod] = mergeSons(sgt[nod << 1], sgt[nod << 1 | 1]);
        }
    }

    template <typename Type>
    void _updateTree(int nod, int lef, int rig, Type val) {
        if (_lef <= lef and rig <= _rig)
            updateNode(nod, lef, rig, val);
        else {
            int mid = (lef + rig) >> 1;
            
            updateLazy(nod << 1, lef, mid);
            updateLazy(nod << 1 | 1, mid + 1, rig);
            
            if (_lef <= mid)
                _updateTree(nod << 1, lef, mid, val);
            if (mid < _rig)
                _updateTree(nod << 1 | 1, mid + 1, rig, val);
            
            sgt[nod] = mergeSons(sgt[nod << 1], sgt[nod << 1 | 1]);
        }
    }
    
    Node _queryTree(int nod, int lef, int rig) {
        if (_lef <= lef and rig <= _rig)
            return sgt[nod];
        else {
            int mid = (lef + rig) >> 1;
            
            updateLazy(nod << 1, lef, mid);
            updateLazy(nod << 1 | 1, mid + 1, rig);
            
            if (_rig <= mid)
                return _queryTree(nod << 1, lef, mid);
            if (mid < _lef)
                return _queryTree(nod << 1 | 1, mid + 1, rig);
            
            return mergeSons(_queryTree(nod << 1, lef, mid),
                             _queryTree(nod << 1 | 1, mid + 1, rig));
        }
    }
    
    int _findFirstKnow(int nod, int lef, int rig, std::function<bool(Node&)> &good) {
        if (lef == rig)
            return lef;
        else {
            int mid = (lef + rig) >> 1;
            
            updateLazy(nod << 1, lef, mid);
            updateLazy(nod << 1 | 1, mid + 1, rig);
            
            if (good(sgt[nod << 1]))
                return _findFirstKnow(nod << 1, lef, mid, good);
            else
                return _findFirstKnow(nod << 1, mid + 1, rig, good);
        }
    }
    
    int _findFirst(int nod, int lef, int rig, std::function<bool(Node&)> &good) {
        if (_lef <= lef and _rig <= rig)
            return good(sgt[nod]) ? _findFirstKnow(nod, lef, rig, good) : -1;
        else {
            int mid = (lef + rig) >> 1, res = -1;
            
            updateLazy(nod << 1, lef, mid);
            updateLazy(nod << 1 | 1, mid + 1, rig);
            
            if (_lef <= mid)
                res = _findFirst(nod << 1, lef, mid, good);
            if (mid < _rig and res == -1)
                res = _findFirst(nod << 1, mid + 1, rig, good);
            
            return res;
        }
    }
    
    int _findLastKnow(int nod, int lef, int rig, std::function<bool(Node&)> &good) {
        if (lef == rig)
            return lef;
        else {
            int mid = (lef + rig) >> 1;
            
            updateLazy(nod << 1, lef, mid);
            updateLazy(nod << 1 | 1, mid + 1, rig);
            
            if (good(sgt[nod << 1 | 1]))
                return _findLastKnow(nod << 1, mid + 1, rig, good);
            else
                return _findLastKnow(nod << 1, lef, mid, good);
        }
    }
    
    int _findLast(int nod, int lef, int rig, std::function<bool(Node&)> &good) {
        if (_lef <= lef and _rig <= rig)
            return good(sgt[nod]) ? _findLastKnow(nod, lef, rig, good) : -1;
        else {
            int mid = (lef + rig) >> 1, res = -1;
            
            updateLazy(nod << 1, lef, mid);
            updateLazy(nod << 1 | 1, mid + 1, rig);
            
            if (mid < _rig)
                res = _findLast(nod << 1, mid + 1, rig, good);
            if (_lef <= mid and res == -1)
                res = _findLast(nod << 1, lef, mid, good);
            
            return res;
        }
    }
public:
    LazySegmentTree(int dim) {
        sgt = new Node[dim << 2]; siz = dim;
    }
    
    template <typename Type>
    void updateTree(int lef, int rig, Type val) {
        _lef = lef; _rig = rig;
        _updateTree(1, 1, siz, val);
    }
    
    Node queryTree(int lef, int rig) {
        _lef = lef; _rig = rig;
        return _queryTree(1, 1, siz);
    }
    
    int findFirst(int lef, int rig, std::function<bool(Node&)> &good) {
        _lef = lef; _rig = rig;
        return _findFirst(1, 1, siz, good);
    }
    
    int findLast(int lef, int rig, std::function<bool(Node&)> &good) {
        _lef = lef; _rig = rig;
        return _findLast(1, 1, siz, good);
    }
};
