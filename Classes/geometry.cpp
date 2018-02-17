// unverified
template <class type>
class Geometry {
private:
    static constexpr long double EPS = 1e-6;
    
    static bool cmp(type x) {
        if (fabs(x) < EPS)
            return 0;
        return x < 0 ? -1 : 1;
    }
public:
    
// point functions
    
    static Point<type> middlePoint(Point<type> p1, Point<type> p2) {
        return p1.middlePoint(p2);
    }
    
    static Point<type> symmetricPoint(Point<type> p1, Point<type> p2) {
        return p1.symmetricPoint(p2);
    }
    
// line functions
    
    static Line<type> bisector(const Point<type> p1, const Point<type> p2) {
        return Line<type>((p2.x - p1.x) * 2, (p2.y - p1.y) * 2,
                          p1.x * p1.x - p2.x * p2.x + p1.y * p1.y - p2.y * p2.y);
    }
    
    static Line<type> transform(const Point<type> p1, const Point<type> p2) {
        return Line<type>(p2.y - p1.y, p1.x - p2.x,
                          p2.x * p1.y - p1.x * p2.y);
    }
    
    static bool symmetrical(const Line<type> ln, const Point<type> p1, const Point<type> p2) {
        return ln.symmetrical(p1, p2);
    }
    
    static bool distance(const Line<type> ln, const Point<type> p) {
        return ln.distance(p);
    }
    
    static Point<type> intersectionPoint(const Line<type> ln1, const Line<type> ln2) {
        return ln1.intersectionPoint(ln2);
    }
    
    static Point<type> heightPoint(const Line<type> ln, const Point<type> p) {
        return ln.heightPoint(p);
    }
    
    static Point<type> symmetricPoint(const Line<type> ln, const Point<type> p) {
        return ln.symmetricPoint(p);
    }
    
// polygon functions
    
    static Polygon<type> convexHull(const Polygon<type> p) {
        return p.convexHull();
    }
    
    static pair<Polygon<type>, Polygon<type>> cutPolygon(const Polygon<type> p, const Line<type> ln) {
        return p.cutPolygon(ln);
    }
};
