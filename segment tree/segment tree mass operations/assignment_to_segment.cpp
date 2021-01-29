//There is an array of n elements, initially filled with zeros. 
//You need to write a data structure that processes two types of queries:

//assign value v to all elements on the segment from l to r−1,
//find the current value of element i.

//link to the problem  https://codeforces.com/edu/course/2/lesson/5/1/practice/contest/279634/problem/C


#include <bits/stdc++.h> 
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <map>
#include <queue>
#include <cmath>
#include <algorithm>
#define endl "\n"
using namespace std; 

typedef long long item;
//struct item{
//    long long seg, pref, suf, sum;
//};


struct segtree{
    int size;

    long long NO_OPERATION = LONG_LONG_MAX;
    vector <item>  operations;

    item NUTRAL_ELEMENT = 0;

    item merge(item a, item b){
        return a+b;
    }

    item single(int v){
        return v;
    }

    long long operation(long long a , long long b){
        if(b==NO_OPERATION){
            return a;
        }
        return b;
    }


    void apply_operation(long long &a, long long b){
        a = operation(a, b);
    }


    void init(int n){
        size = 1;
        while(size<n) size*=2;
        operations.assign(2*size, 0ll);

    }

    void propagate(int x, int lx, int rx){
        if(rx-lx==1){
            return;
        }
        apply_operation(operations[2*x + 1], operations[x]);
        apply_operation(operations[2*x + 2], operations[x]);
        operations[x] = NO_OPERATION;
    }



    void modify(int l, int r, int v, int x, int lx, int rx){
        propagate(x, lx, rx);
        if(lx>=r || l>=rx) return;
        if(lx>=l && rx<=r){
            apply_operation(operations[x], v);
            return;
        }
        int m = (lx+rx)/2;
        modify(l, r, v, 2*x+1, lx, m);
        modify(l, r, v, 2*x+2, m, rx);

    }

    void modify(int l, int r, int v){
        modify(l, r, v, 0, 0, size);
    }

    long long get(int i, int x, int lx, int rx){
        propagate(x, lx, rx);
        if(rx-lx==1){
            return operations[x];
            
        }
        int m = (lx+rx)/2;
        long long res;
        if(i<m){
            res = get(i, 2*x+1, lx, m);
        }
        else{
            res = get(i, 2*x+2, m, rx);
        }
        return res;
    }

    long long get(int i){
        return get(i, 0, 0, size );
    }
};

int main(){
    ios::sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    segtree st;
    st.init(n);
    while(m--){
        int op;
        cin >> op;
        if(op==1){
            int l, r, v;
            cin >> l >> r >> v;
            st.modify(l, r, v);
        }
        else{
            int i;
            cin >> i;
            cout << st.get(i) << endl;
        }
    }
    return 0;
}