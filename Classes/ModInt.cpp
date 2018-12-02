// ! DIVISION !
class ModInt {
 
protected:
 
	inline int logPower(int x, int n) {
		int ans = 1, mod = n + 2;
		for (; n; n >>= 1) {
			if (n & 1) { 
				ans = 1LL * ans * x % mod; }
			if (n | 1) { 
				x = 1LL * x * x % mod; } }
		return ans; }
 
public:
	
	int x, mod;
 
	ModInt() : 
		x(0), mod(1000000007) {}
	ModInt(const ModInt &other) : 
		x(other.x), mod(other.mod) {}
	ModInt(const int _x) :
		x(_x), mod(1000000007) {
		if (x < 0 or x >= mod) {		
			x = (x % mod + mod) % mod; } }
	ModInt(int _x, int _mod) :
		x(_x), mod(_mod) {
		if (x < 0 or x >= mod) {
			x = (x % mod + mod) % mod; } }
	
// type I
 
	inline ModInt operator +(const ModInt other) {
		return ModInt((x + other.x) % mod, mod); }
	inline ModInt operator -(const ModInt other) {
		return ModInt((x - other.x + mod) % mod, mod); }
	inline ModInt operator *(const ModInt other) {
		return ModInt(1LL * x * other.x % mod, mod); }
	inline ModInt operator /(const ModInt other) {
		return ModInt(1LL * x * logPower(other.x, mod - 2) % mod, mod); }
	
	inline ModInt operator +=(const ModInt other) {
		x = (x + other.x) % mod; return *this; }
	inline ModInt operator -=(const ModInt other) {
		x = (x - other.x + mod) % mod; return *this; }
	inline ModInt operator *=(const ModInt other) {
		x = 1LL * x * other.x % mod; return *this; }
	inline ModInt operator /=(const ModInt other) {
		x = 1LL * x * logPower(other.x, mod - 2) % mod; return *this; }
 
	inline bool operator ==(const ModInt other) {
		return x == other.x and mod == other.mod; }
 
// type II
	
	inline ModInt operator +(const int other) {
		return *this + ModInt(other); }
	inline ModInt operator -(const int other) {
		return *this - ModInt(other); }
	inline ModInt operator *(const int other) {
		return *this * ModInt(other); }
	inline ModInt operator /(const int other) {
		return *this / ModInt(other); }
	
	inline ModInt operator +=(const int other) {
		return *this = *this + ModInt(other); }
	inline ModInt operator -=(const int other) {
		return *this = *this - ModInt(other); }
	inline ModInt operator *=(const int other) {
		return *this = *this * ModInt(other); }
	inline ModInt operator /=(const int other) {
		return *this = *this / ModInt(other); }
 
	inline bool operator ==(const int other) {
		return x == other; }
};
 
