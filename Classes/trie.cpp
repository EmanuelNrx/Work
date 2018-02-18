// almost done | further memory optimization required
class Trie {
private:
    static const int SIGMA = 26;
     
    struct TrieNode {
        short nrw, nrs;
        TrieNode *son[SIGMA];
         
        TrieNode() {
            nrw = nrs = 0;
            for (int i = 0; i < SIGMA; i++)
                son[i] = NULL;
        }
    } *rot = new TrieNode;
     
    void insertWord(TrieNode *nod, char *str, int cnt) {
        if (*str == 0)
            nod -> nrw += cnt;
        else {
            if (nod -> son[*str - 'a'] == NULL)
                nod -> son[*str - 'a'] = new TrieNode, nod -> nrs++;
            insertWord(nod -> son[*str - 'a'], str + 1, cnt);
        }
    }
     
    int eraseWord(TrieNode *nod, char *str, int cnt) {
        if (*str == 0)
            nod -> nrw = max(nod -> nrw - cnt, 0);
        else
        if (nod -> son[*str - 'a'] != NULL and
            eraseWord(nod -> son[*str - 'a'], str + 1, cnt))
            nod -> son[*str - 'a'] = NULL, nod -> nrs--;
        bool ok = false;
        if (nod -> nrs == 0 && nod -> nrw == 0 && nod != rot)
            delete nod, ok = true;
        return ok;
    }
     
    int countWord(TrieNode *nod, char *str) {
        if (*str == 0)
            return nod -> nrw;
        if (nod -> son[*str - 'a'] != NULL)
            return countWord(nod -> son[*str - 'a'], str + 1);
        return 0;
    }
     
    int longestPrefix(TrieNode *nod, char *str, int pfx) {
        if (*str == 0)
            return pfx;
        if (nod -> son[*str - 'a'] != NULL)
            return longestPrefix(nod -> son[*str - 'a'], str + 1, pfx + 1);
        return pfx;
    }
public:
    void insertWord(char *str, int cnt = 1) {
        insertWord(rot, str, cnt);
    }
     
    void eraseWord(char *str, int cnt = 1) {
        eraseWord(rot, str, cnt);
    }
     
    int countWord(char *str) {
        return countWord(rot, str);
    }
     
    int longestPrefix(char *str) {
        return longestPrefix(rot, str, 0);
    }
     
    void insertWord(string str, int cnt = 1) {
        char *cstr = new char[str.length() + 1];
        strcpy(cstr, str.c_str());
         
        insertWord(rot, cstr, cnt);
        delete[] cstr;
    }
     
    void eraseWord(string str, int cnt = 1) {
        char *cstr = new char[str.length() + 1];
        strcpy(cstr, str.c_str());
         
        eraseWord(rot, cstr, cnt);
        delete[] cstr;
    }
     
    int countWord(string str) {
        char *cstr = new char[str.length() + 1];
        strcpy(cstr, str.c_str());
         
        int ans = countWord(rot, cstr);
        delete[] cstr; return ans;
    }
     
    int longestPrefix(string str) {
        char *cstr = new char[str.length() + 1];
        strcpy(cstr, str.c_str());
         
        int ans = longestPrefix(rot, cstr, 0);
        delete[] cstr; return ans;
    }
};
