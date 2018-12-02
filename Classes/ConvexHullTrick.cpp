class LinearFunction {
public:
    static const int INF = numeric_limits<int> :: max();
    
    int a; long long b;
    mutable long double pnt;
    
    LinearFunction(int _a, long long _b) : 
		a(_a), b(_b) {};
    
	LinearFunction(int _a, long long _b, long double _pnt) :
		a(_a), b(_b), pnt(_pnt) {};
    
    bool operator <(const LinearFunction &other) const {
        if (other.a == INF) {
            return this -> pnt < other.pnt; }
        return make_pair(this -> a, this -> b) < make_pair(other.a, other.b); }
    
    long long getValue(int x) const {
        return 1LL * this -> a * x + this -> b; }
};
 
class ConvexHullTrick : public set<LinearFunction> {

private:

    static const int INF = numeric_limits<int> :: max();
    
    inline bool bad(iterator it) {
        if (next(it) == end()) {
            return false; }
        if (it == begin()) {
         	return false; }
        set<LinearFunction> :: iterator nxt, prv; 
		nxt = next(it); prv = prev(it);
        return 1.0 * (prv -> b - nxt -> b) * (nxt -> a - it -> a) >=
               1.0 * (it -> b - nxt -> b) * (nxt -> a - prv -> a); }
    
    inline void update(iterator it) {
        set<LinearFunction> :: iterator nxt = next(it);
        if (nxt == end()) {
			it -> pnt = 1.0 * INF * INF; }
        else {
            it -> pnt = 1.0 * (it -> b - nxt -> b) / (nxt -> a - it -> a); } }

public:

    void insertFunction(LinearFunction function) {
        if (insert(function).second == false) {
            return; }
        set<LinearFunction> :: iterator it = find(function);
        if (next(it) != end() && next(it) -> a == it -> a && next(it) -> b < it -> b) {
            erase(it), it = end(); }
        else 
		if (it != begin() && prev(it) -> a == it -> a && prev(it) -> b < it -> b) {
            erase(it), it = end(); }
        else
        if (it != end() && bad(it) == true) {
            erase(it), it = end(); }
        if (it == end() ) {
            return; }
        while (next(it) != end() && bad(next(it))) {
            erase( next(it) ); }
        while (it != begin() && bad(prev(it))) {
            erase(prev(it)); }
        update(it);
        if (it != begin()) {
            update(prev(it)); } }
    
    long long findFunction(int x) {
        return lower_bound(LinearFunction(INF, 0, x)) -> getValue(x); }
}; 

