// unverified
class Utility{
private:
    template <class type>
    static map<type, int> getFactorisation(const type val) {
        if (val <= 1)
            return map<type, int>();
        
        type aux = getFactor(val);
        map<type, int> mmp1 = getFactorisation(aux),
                       mmp2 = getFactorisation(val / aux);
        
        for (pair<type, int> pr : mmp1)
            mmp2[pr.first] += pr.second;
        return mmp2;
    }
    
    template <class type>
    static type gcd(type a, type b, type &x, type &y) {
        type d, x0, y0;
        
        if (!b)
            d = a, x = 1, y = 0;
        else {
            d = gcd(b, a % b, x0, y0);
            x = y0; y = x0 - (a / b) * y0;
        }
        
        return d;
    }
public:
    static vector<int> getPrimes(vector<bool> &oki) {
        fill(oki.begin(), oki.end(), true);
        vector<int> lst; oki[0] = oki[1] = false;
        
        for (int i = 2; i <= lst.size(); ++i) if (oki[i]) {
            lst.push_back(i);
            for (int j = i + i; j <= lst.size(); j += i)
                oki[j] = false;
        }
        
        return lst;
    }
    
    static vector<int> getPrimes(int lim) {
        vector<bool> oki(lim + 1);
        return getPrimes(oki);
    }
    
    template <class type1, class type2>
    static type1 logMultiply(type1 x, type2 n, type1 mod) {
        if (x >= mod) x %= mod;
        if (n >= mod) n %= mod;
       
        if (!n)
            return 0;
        type1 y = logMultiply(x, n / 2, mod);
        
        y = ((unsigned long long)y + y) % mod;
        if (n & 1)
            y = ((unsigned long long)y + x) % mod;
        
        return y;
    }
    
    template <class type1, class type2>
    static type1 logPower(type1 x, type2 n, type1 mod) {
        if (x >= mod) x %= mod;
        
        if (!n)
            return 1;
        type1 y = logPower(x, n / 2, mod);
        
        if (mod < (1LL << 32)) {
            y = ((unsigned long long)y * y) % mod;
            if (n & 1)
                y = ((unsigned long long)y * x) % mod;
        } else {
            y = logMultiply(y, y, mod);
            if (n & 1)
                y = logMultiply(y, x, mod);
        }
        
        return y;
    }
    
    template <class type>
    static type gcd(type x, type y) {
        if (!y)
            return x;
        return gcd(y, x % y);
    }
    
    template <class type>
    static bool isPrime(type val) {
        if (val <= 1)
            return false;
        
        if (val < (1LL << 32)) {
            for (int x : {2, 7, 61})
                if (val > x and logPower(x, val - 1, val) != 1)
                    return false;
            return true;
        } else {
            for (type x : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37})
                if (val > x and logPower(x, val - 1, val) != 1)
                    return false;
            return true;
        }
    }
    
    template <class type>
    static type nextPrime(const type val) {
        while (!isPrime(val))
            ++val;
        return val;
    }
    
    template <class type>
    static type getFactor(const type val) {
        type aux = sqrtl(val);
        
        if (isPrime(val))
            return val;
        if (aux * aux == val)
            return aux;
        
        unsigned long long Pzero, Pprev, Qprev, D, P, Q, L, B, q, b, r, s, i;
        for (int x : {1, 3, 5, 7, 15, 21, 33, 35, 55, 77, 105, 165, 231, 385, 1155}) {
            D = x * val; Pzero = Pprev = P = sqrtl(D); Qprev = 1;
            Q = D - Pzero * Pzero; L = sqrtl(s * 2) * 2; B = L * 3;
            
            for (i = 2; i < B; ++i, Qprev = q, Pprev = P) {
                b = (Pzero + P) / Q; P = b * Q - P;
                q = Q; Q = Qprev + b * (Pprev - P);
                
                r = sqrtl(Q);
                if (!(i & 1) and r * r == Q)
                    break;
            }
            
            if (i >= B)
                continue;
            
            b = (Pzero - P) / r; Pprev = P = b * r + P;
            Qprev = r; Q = (D - Pprev * Pprev) / Qprev; i = 0;
            
            do {
                b = (Pzero + P) / Q; Pprev = P; P = b * Q - P;
                q = Q; Q = Qprev + b * (Pprev - P); Qprev = q; ++i;
            } while (P != Pprev);
            
            r = gcd((unsigned long long) val, Qprev);
            if (r != 1 and r != val) return r;
        }
        
        return 0;
    }
    
    template <class type>
    static type getInverse(type val, type mod) {
        type x, y;
        
        gcd(val, mod, x, y);
        if (x < 0)
            x = mod + x % mod;
        return x;
    }
    
    template <class type>
    static vector<pair<type, int>> getFactorisation(const type val) {
        map<type, int> mmp = getFactorisation(val); vector<type, int> lst;
        
        for (pair<type, int> pr : mmp)
            lst.push_back(pr);
        return lst;
    }
    
    template <class type>
    static type numberOfDivisors(const type val, const type mod) {
        vector<pair<type, int>> lst = getFactorisation(val);
        
        type ans = 1;
        for (pair<type, int> pr : lst) {
            if (mod < (1LL << 32))
                ans = ((unsigned long long) ans * (pr.second + 1)) % mod;
            else
                ans = logMultiply(ans, pr.second + 1, mod);
        }
        
        return ans;
    }
    
    template <class type>
    static type sumOfDivisors(const type val, const type mod) {
        vector<pair<type, int>> lst = getFactorisation(val);
        
        type ans = 1;
        for (pair<type, int> pr : lst) {
            if (mod < (1LL << 32)) {
                ans = ((unsigned long long) ans * (logPower(pr.first, pr.second) + mod - 1) % mod);
                ans = ((unsigned long long) ans * getInverse(pr.first - 1, mod));
            } else {
                ans = logMultiply(ans, logPower(pr.first, pr.second) + mod - 1, mod);
                ans = logMultiply(ans, getInverse(pr.first - 1, mod), mod);
            }
        }
        
        return ans;
    }
};
