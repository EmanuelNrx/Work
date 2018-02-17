template <class type>
class Line{
private:
    static constexpr long double EPS = 1e-6;
    
    static bool cmp(type x) {
        if (fabs(x) < EPS)
            return 0;
        return x < 0 ? -1 : 1;
    }
public:
    type a, b, c;
    
// constructors
    
    Line():
        a(0), b(0), c(0) {};
    Line(type _a, type _b, type _c):
        a(_a), b(_b), c(_c) {};
    
// operators
    
    bool operator <(const Line<type> other) {
        simplify();
        other.simplify();
        
        if (cmp(a, other.a)) return a < other.a;
        if (cmp(b, other.b)) return b < other.b;
        
        return cmp(c - other.c) < 0;
    }
    
    bool operator >(const Line<type> other) {
        simplify();
        other.simplify();
        
        if (cmp(a, other.a)) return a < other.a;
        if (cmp(b, other.b)) return b < other.b;
        
        return cmp(c - other.c) > 0;
    }
    
    bool operator ==(const Line<type> other) {
        simplify();
        other.simplify();
        
        return !cmp(a, other.a) and !cmp(b, other.b) and !cmp(c, other.c);
    }
    
    bool operator <=(const Line<type> other) {
        return (*this) < other or (*this) == other;
    }
    
    bool operator >=(const Line<type> other) {
        return (*this) > other or (*this) == other;
    }
  
// functions
    
    Line simplify(void) {
        if ((cmp(a, 0) <  0) or
            (cmp(a, 0) == 0 and cmp(b, 0) <  0) or
            (cmp(a, 0) == 0 and cmp(b, 0) == 0 and cmp(c, 0) < 0))
            a *= -1, b *= -1, c *= -1;
        
        if (cmp(c, 0))
            a /= c, b /= c, c = 1;
        else if (cmp(b, 0))
            a /= b, b = 1;
        else if (cmp(a, 0))
            a = 1;
        
        return *this;
    }
    
    type calculate(Point<type> p) {
        return a * p.x + b * p.y + c;
    }
    
    type findX(type y) {
        return (-c - b * y) / a;
    }
    
    type findY(type x) {
        return (-c - a * x) / b;
    }
    
    bool symmetricalPoints(const Point<type> p1, const Point<type> p2) {
        if (!cmp(calculate(p1.x, p1.y) + calculate(p2.x, p2.y)))
            return false;
        
        type l = calculate(p1.x, p1.y) * 2 / sqrt(a * a + b * b),
             r = sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
        
        return !cmp(fabs(l) - r);
    }
    
    type distance(const Point<type> p) {
        return fabs(a * p.x + b * p.y + c) / sqrt(a * a + b * b);
    }
    
    Point<type> intersectionPoint(const Line<type> ln) {
        return Point<type>((ln.c * b - c * ln.b) / (a * ln.b - ln.a * b),
                           (ln.c * a - c * ln.a) / (b * ln.a - ln.b * a));
    }
    
    Point<type> heightPoint(const Point<type> p) {
        if (!cmp(a)) return Point<type>(p.x, findY(p.y));
        if (!cmb(b)) return Point<type>(findX(p.x), p.y);
        
        type m = b / a, n = p.y - m * p.x;
        return intersectionPoint(Line(-m, 1, n));
    }
    
    Point<type> symmetricPoint(const Point<type> p) {
        Point<type> m = heightPoint(p);
        return m.symmetricPoint(p);
    }
};
