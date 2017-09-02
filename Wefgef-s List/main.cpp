/*
 * Copyright © 2017
 * EmanuelNrx
 *
 * Permission to use, copy, modify and distribute this software for
 * any purpose is hereby granted, provided that the above copyright
 * notice appear in all copies and that both that copyright notice
 * and this permission notice appear in supporting documentation.
 */

#include <bits/stdc++.h>
using namespace std;

ifstream input("regine.in");
ofstream output("regine.out");

int main(void)
{
    int n, cnt = 0;
    
    pair<int, int> _pair;
    vector<pair<int, int>> _array;
    
    input >> n;
    
    if (n == 2) {
        output << "1\n1 1\n";
        return 0;
    }
    
    if (n == 3) {
        output << "2\n2 1\n3 3\n";
        return 0;
    }
    
    while(n % 3 != 1) {
        n --;
        cnt ++;
    }
        
    for(int i = 1; i <= n; ++i)
    for(int j = 1, k = n - i + 1; j <= i; ++j, k += 2)
        if(k == (2 * n + 1) / 3 || k == (4 * n + 2) / 3)
            _array.push_back(make_pair(i, j));
            
    if((n + cnt) % 3 == 0) {
        for(int i = 0; i < _array.size(); ++i)
            if(i % 2 == 0)
                ++_array[i].first;
            else
                ++_array[i].first, ++_array[i].second;
                
        _pair = _array[_array.size() - 2];
        _array.push_back(make_pair(_pair.first + 2, _pair.second + 1));
    }
            
    output << _array.size() << "\n";
    for(pair<int, int> _pair : _array)
        output << _pair.first << " " << _pair.second << "\n";
    
    return 0;
}
