// DONE
class LazySegmentTree {
public:
    struct Node {
        int mxv, pos, cnt;
        
        Node() :
            mxv(0), pos(0), cnt(0) {};
        Node(int _mxv, int _pos, int _cnt) :
            mxv(_mxv), pos(_pos), cnt(_cnt) {};
    } *sgt; static const Node nul;
    int siz, _lef, _rig;
    
    void updateLazy(int nod, int lef, int rig) {
        //nothing here
    }
    
    Node mergeSons(Node son1, Node son2) {
        Node ans(max(son1.mxv, son2.mxv), -1, son1.cnt + son2.cnt);
        ans.pos = (ans.mxv == son1.mxv) ? son1.pos : son2.pos;
        
        return ans;
    }
    
    template <typename Type>
    void updateNode(int nod, int lef, int rig, Type val) {
        sgt[nod].mxv = val; sgt[nod].pos = lef;
        sgt[nod].cnt = val >= 0;
        
        // updateLazy(nod, lef, rig);
    }
    
    inline int findPos(const int lef, const int rig) {
        return (lef + rig) | (lef != rig);
    }
    
    template <typename Type>
    void _buildTree(int nod, int lef, int rig, Type arr[]) {
        if (lef == rig)
            updateNode(nod, lef, rig, arr[lef]);
        else {
            int mid = (lef + rig) >> 1,
                lefSon = findPos(lef, mid),
                rigSon = findPos(mid + 1, rig);
            
            _buildTree(lefSon, lef, mid, arr);
            _buildTree(rigSon, mid + 1, rig, arr);
            
            sgt[nod] = mergeSons(sgt[lefSon], sgt[rigSon]);
        }
    }
    
    template <typename Type>
    void _updateTree(int nod, int lef, int rig, Type val) {
        if (_lef <= lef and rig <= _rig)
            updateNode(nod, lef, rig, val);
        else {
            int mid = (lef + rig) >> 1,
                lefSon = findPos(lef, mid),
                rigSon = findPos(mid + 1, rig);
            
            updateLazy(lefSon, lef, mid);
            updateLazy(rigSon, mid + 1, rig);
            
            if (_lef <= mid)
                _updateTree(lefSon, lef, mid, val);
            if (mid < _rig)
                _updateTree(rigSon, mid + 1, rig, val);
            
            sgt[nod] = mergeSons(sgt[lefSon], sgt[rigSon]);
        }
    }
    
    Node _queryTree(int nod, int lef, int rig) {
        if (_lef <= lef and rig <= _rig)
            return sgt[nod];
        else {
            int mid = (lef + rig) >> 1,
                lefSon = findPos(lef, mid),
                rigSon = findPos(mid + 1, rig);
            
            updateLazy(lefSon, lef, mid);
            updateLazy(rigSon, mid + 1, rig);
            
            if (_rig <= mid)
                return _queryTree(lefSon, lef, mid);
            if (mid < _lef)
                return _queryTree(rigSon, mid + 1, rig);
            
            return mergeSons(_queryTree(lefSon, lef, mid),
                             _queryTree(rigSon, mid + 1, rig));
        }
    }
    
    int _findFirstKnow(int nod, int lef, int rig, std::function<bool(Node&)> &good) {
        if (lef == rig)
            return lef;
        else {
            int mid = (lef + rig) >> 1,
                lefSon = findPos(lef, mid),
                rigSon = findPos(mid + 1, rig);
            
            updateLazy(lefSon, lef, mid);
            updateLazy(rigSon, mid + 1, rig);
            
            if (good(sgt[lefSon]))
                return _findFirstKnow(lefSon, lef, mid, good);
            else
                return _findFirstKnow(rigSon, mid + 1, rig, good);
        }
    }
    
    int _findFirst(int nod, int lef, int rig, std::function<bool(Node&)> &good) {
        if (_lef <= lef and _rig <= rig)
            return good(sgt[nod]) ? _findFirstKnow(nod, lef, rig, good) : -1;
        else {
            int mid = (lef + rig) >> 1, res = -1,
                lefSon = findPos(lef, mid),
                rigSon = findPos(mid + 1, rig);
            
            updateLazy(lefSon, lef, mid);
            updateLazy(rigSon, mid + 1, rig);
            
            if (_lef <= mid)
                res = _findFirst(lefSon, lef, mid, good);
            if (mid < _rig and res == -1)
                res = _findFirst(rigSon, mid + 1, rig, good);
            
            return res;
        }
    }
    
    int _findLastKnow(int nod, int lef, int rig, std::function<bool(Node&)> &good) {
        if (lef == rig)
            return lef;
        else {
            int mid = (lef + rig) >> 1,
                lefSon = findPos(lef, mid),
                rigSon = findPos(mid + 1, rig);
            
            updateLazy(lefSon, lef, mid);
            updateLazy(rigSon, mid + 1, rig);
            
            if (good(sgt[rigSon]))
                return _findLastKnow(rigSon, mid + 1, rig, good);
            else
                return _findLastKnow(lefSon, lef, mid, good);
        }
    }
    
    int _findLast(int nod, int lef, int rig, std::function<bool(Node&)> &good) {
        if (_lef <= lef and _rig <= rig)
            return good(sgt[nod]) ? _findLastKnow(nod, lef, rig, good) : -1;
        else {
            int mid = (lef + rig) >> 1, res = -1,
                lefSon = findPos(lef, mid),
                rigSon = findPos(mid + 1, rig);
            
            updateLazy(lefSon, lef, mid);
            updateLazy(rigSon, mid + 1, rig);
            
            if (mid < _rig)
                res = _findLast(rigSon, mid + 1, rig, good);
            if (_lef <= mid and res == -1)
                res = _findLast(lefSon, lef, mid, good);
            
            return res;
        }
    }
public:
    LazySegmentTree(int dim) {
        sgt = new Node[dim << 1]; siz = dim;
    }
    
    void resizeTree(int _siz) {
        siz = _siz;
    }
    
    template <typename Type>
    void buildTree(Type *arr) {
        _buildTree(1, 1, siz, arr);
    }
    
    template <typename Type>
    void updateTree(int lef, int rig, Type val = nul) {
        _lef = lef; _rig = rig;
        _updateTree(1, 1, siz, val);
    }
    
    Node queryTree(int lef, int rig) {
        _lef = lef; _rig = rig;
        return _queryTree(1, 1, siz);
    }
    
    int findFirst(int lef, int rig, std::function<bool(Node&)> good) {
        _lef = lef; _rig = rig;
        return _findFirst(1, 1, siz, good);
    }
    
    int findLast(int lef, int rig, std::function<bool(Node&)> good) {
        _lef = lef; _rig = rig;
        return _findLast(1, 1, siz, good);
    }
};
