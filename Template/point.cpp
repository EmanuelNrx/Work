// unverified
template <class type>
class Point{
private:
    static constexpr long double EPS = 1e-6;
    
    static int cmp(type x) {
        if (fabs(x) < EPS)
            return 0;
        return x < 0 ? -1 : 1;
    }
public:
    type x, y;
    
// constructors
    
    Point():
        x(0), y(0) {};
    Point(type _x, type _y):
        x(_x), y(_y) {};
    
// type I operators
    
    bool operator <(const Point<type> other) {
        if (cmp(x - other.x))
            return cmp(x - other.x) < 0;
        else
            return cmp(y - other.y) < 0;
    }
    
    bool operator >(const Point<type> other) {
        if (cmp(x - other.x))
            return cmp(x - other.x) > 0;
        else
            return cmp(y - other.y) > 0;
    }
    
    bool operator ==(const Point<type> &other) {
        return !cmp(x - other.x) and !cmp(y - other.y);
    }
    
    bool operator <=(const Point<type> &other) {
        return (*this) < other or (*this) == other;
    }
    
    bool operator >=(const Point<type> &other) {
        return (*this) > other or (*this) == other;
    }
    
// type II operators
    
    Point operator +(const Point<type> other) {
        return Point(x + other.x,
                     y + other.y);
    }
    
    Point operator -(const Point<type> other) {
        return Point(x - other.x,
                     y - other.y);
    }
    
    Point operator *(const type other) {
        return Point(x * other,
                     y * other);
    }
    
    Point operator *(const Point<type> other) { // complex numbers rule
        return Point(x * other.x - y * other.y,
                     x * other.y + y * other.x);
    }
    
    Point operator /(const type other) {
        return Point(x / other,
                     y / other);
    }
    
    Point operator /(const Point<type> other) { // complex numbers rule
        return Point((x * other.x + y * other.y) / (other.x * other.x + other.y * other.y),
                     (y * other.x - x * other.y) / (other.x * other.x + other.y * other.y));
    }
    
// type III operators
    
    Point operator +=(const Point<type> other) {
        return (*this) = (*this) + other;
    }
    
    Point operator -=(const Point<type> other) {
        return (*this) = (*this) - other;
    }
    
    Point operator *=(const type other) {
        return (*this) = (*this) * other;
    }
    
    Point operator *=(const Point<type> other) {
        return (*this) = (*this) * other;
    }
    
    Point operator /=(const type other) {
        return (*this) = (*this) / other;
    }
    
    Point operator /=(const Point<type> other) {
        return (*this) = (*this) / other;
    }
    
// functions
    
    Point middlePoint(const Point<type> p) {
        return Point<type>((x + p.x) / 2,
                           (y + p.y) / 2);
    }
    
    Point symmetricPoint(const Point<type> p) {
        return Point((x * 2 - p.x),
                     (y * 2 - p.y));
    }
};
