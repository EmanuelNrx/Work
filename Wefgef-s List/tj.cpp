#include <bits/stdc++.h>
using namespace std;

ifstream input("tj.in");
ofstream output("tj.out");

const int DIM = 260;

bitset<DIM> marked[DIM];

int main(void)
{
    int t;
    input >> t;
    
    while (t --) {
        int n, m;
        input >> n >> m;
        
        for (int i = 1; i <= n; ++i) {
            marked[i].reset();
            marked[i][i] = true;
        }
        
        for (int i = 1; i <= m; ++i) {
            int x, y;
            input >> x >> y;
            
            marked[x][y] = marked[y][x] = true;
        }
        
        bool ok = true;
        for (int k = 1; k <= n - 1 and ok; ++k) {
            ok = false;
            
            for (int i = 1; i <= n and !ok; ++i) {
                if (!marked[i][i])
                    continue;
                
                for (int j = 1; j <= n and !ok; ++j) {
                    if (!marked[i][j] or i == j)
                        continue;
                    
                    if ( (marked[i] & marked[j]) == marked[i]) {
                        ok = true;
                        
                        for (int l = 1; l <= n; ++l)
                            if (marked[i][l])
                                marked[l][i] = false;
                        
                        marked[i].reset();
                    }
                }
            }
        }
        
        output << (ok ? "DA" : "NU") << endl;
    }
    
    return 0;
}
