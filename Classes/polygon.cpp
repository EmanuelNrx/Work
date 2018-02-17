// unfinished
template <class type>
class Polygon{
private:
    static constexpr long double EPS = 1e-6;
    
    static bool cmp(type x) {
        if (fabs(x) < EPS)
            return 0;
        return x < 0 ? -1 : 1;
    }
    
    static bool ord(Point<type> p1, Point<type> p2) {
        if (!cmp(p1.x - p2.x))
            return p1.y < p2.y;
        return p1.x < p2.x;
    }
    
    static type ccw(Point<type> p1, Point<type> p2, Point<type> p3) {
        return (p2.x - p1.x) * (p3.y - p1.y) -
               (p3.x - p1.x) * (p2.y - p1.y);
    }
public:
    vector<Point<type>> pts;
    
// constructors

    Polygon() {};
    Polygon(vector<Point<type>> _pts) : pts(_pts) {};
    
// functions
    
    Polygon convexHull(void) {
        vector<bool> oki(pts.size(), false);
        vector<int> hul(1, 0); vector<Point<type>> npt;
        
        sort(pts.begin(), pts.end());
        for (int pos = 1, stp = 1; !oki[0]; pos += stp) {
            if (!oki[pos]) {
                while (hul.size() > 1 and cmp(ccw(pts[hul.size() - 2],
                                                  pts[hul.size() - 1], pts[pos])) <= 0)
                    oki[hul.back()] = false, hul.pop_back();
                oki[pos] = true; hul.push_back(pos);
            }
            
            if (pos == (int) pts.size() - 1)
                stp = -1;
        }
        
        hul.pop_back();
        for (int pos : hul)
            npt.push_back(pts[pos]);
        pts = npt;
        
        return *this;
    }
    
    // imi e prea lene
    pair<Polygon<type>, Polygon<type>> cutPolygon(Line<type> ln) {
        return make_pair(*this, *this);
    }
};
