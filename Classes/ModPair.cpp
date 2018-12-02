// ! DIVISION !
class ModPair : protected ModInt {
 
public:
 
	int x, y, mod1, mod2;
	
	ModPair() :
		x(0), y(0), mod1(1000000007), mod2(1000000009) {}
	ModPair(const ModPair &other) :
		x(other.x), y(other.y), mod1(other.mod1), mod2(other.mod2) {}
	ModPair(const int _x, const int _y) :
		x(_x), y(_y), mod1(1000000007), mod2(1000000009) {
		if (x < 0 or x >= mod1) {
			x = (x % mod1 + mod1) % mod1; }
		if (y < 0 or y >= mod2) {
			y = (y % mod2 + mod2) % mod2; } }
	ModPair(const int _x, const int _y, const int _mod1, const int _mod2) :
		x(_x), y(_y), mod1(_mod1), mod2(_mod2) {
		if (x < 0 or x >= mod1) {
			x = (x % mod1 + mod1) % mod1; }
		if (y < 0 or y >= mod2) {
			y = (y % mod2 + mod2) % mod2; } }
 
// type I
 
	inline ModPair operator +(const ModPair other) {
		return ModPair((x + other.x) % mod1, (y + other.y) % mod2, mod1, mod2); }
	inline ModPair operator -(const ModPair other) {
		return ModPair((x - other.x + mod1) % mod1, (y - other.y + mod2) % mod2, mod1, mod2); }
	inline ModPair operator *(const ModPair other) {
		return ModPair(1LL * x * other.x % mod1, 1LL * y * other.y % mod2, mod1, mod2); }
	inline ModPair operator /(const ModPair other) {
		return ModPair(1LL * x * logPower(other.x, mod1 - 2) % mod1, 1LL * y * logPower(other.y, mod2 - 2) % mod2, mod1, mod2); }
	
	inline ModPair operator +=(const ModPair other) {
		x = (x + other.x) % mod1; y = (y + other.y) % mod2; return *this; }
	inline ModPair operator -=(const ModPair other) {
		x = (x - other.x + mod1) % mod1; y = (y - other.y + mod2) % mod2; return *this; }
	inline ModPair operator *=(const ModPair other) {
		x = 1LL * x * other.x % mod1; y = 1LL * y * other.y % mod2; return *this; }
	inline ModPair operator /=(const ModPair other) {
		x = 1LL * x + logPower(other.x, mod1 - 2) % mod1; y = 1LL * y * logPower(other.y, mod2 - 2) % mod2; return *this; }
	
	inline bool operator ==(const ModPair other) {
		return x == other.x and y == other.y and mod1 == other.mod1 and mod2 == other.mod2; }
 
// type II
 
	inline ModPair operator +(const int other) {
		return *this + ModPair(other, other, mod1, mod2); }
	inline ModPair operator -(const int other) {
		return *this - ModPair(other, other, mod1, mod2); }
	inline ModPair operator *(const int other) {
		return *this * ModPair(other, other, mod1, mod2); }
	inline ModPair operator /(const int other) {
		return *this / ModPair(other, other, mod1, mod2); }
	
	inline ModPair operator +=(const int other) {
		return *this = *this + ModPair(other, other, mod1, mod2); }
	inline ModPair operator -=(const int other) {
		return *this = *this - ModPair(other, other, mod1, mod2); }
	inline ModPair operator *=(const int other) {
		return *this = *this * ModPair(other, other, mod1, mod2); }
	inline ModPair operator /=(const int other) {
		return *this = *this / ModPair(other, other, mod1, mod2); }
 
	inline bool operator ==(const int other) {
		return x == other and y == other; }
};
 
