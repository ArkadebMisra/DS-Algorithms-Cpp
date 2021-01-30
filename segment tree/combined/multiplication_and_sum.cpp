//There is an array of n elements, initially filled with ones. 
//You need to write a data structure that processes two types of queries:

//multiply all elements on the segment from l to r−1 by number v,
//find the sum on the segment from l to r−1.
//Both operations are performed modulo 10**9+7.

//link to the problem  https://codeforces.com/edu/course/2/lesson/5/2/practice/contest/279653/problem/B


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

const long long MOD = 1000000007;

struct segtree{
    int size;
    vector <item>  operations;
    vector <item> values;

    item NUTRAL_ELEMENT = 0;

    item merge(item a, item b){
        return a+b;
    }

    item single(int v){
        return v;
    }

    long long modify_op(long long a, long long b){
        return (a*b)%MOD;
    }

    long long calc_op(long long a, long long b){
        return (a+b)%MOD;
    }

    void apply_mod_op(long long &a, long long b){
        a = modify_op(a, b);
    }


    void build(int x, int lx, int rx){
        if(rx-lx==1){
            values[x] = 1;
            return;
        }
        int m = (lx+rx)/2;
        build(2*x+1, lx, m);
        build(2*x+2, m, rx);
        values[x] = calc_op(values[2*x+1], values[2*x+2]);
    }

    void init(int n){
        size = 1;
        while(size<n) size*=2;
        operations.assign(2*size, 1ll);
        values.assign(2*size, 0ll);
        build(0, 0, size);
    }



    void modify(int l, int r, int v, int x, int lx, int rx){
        if(lx>=r || l>=rx) return;
        if(lx>=l && rx<=r){
            apply_mod_op(operations[x], v);
            apply_mod_op(values[x], v);
            return;
        }
        int m = (lx+rx)/2;
        modify(l, r, v, 2*x+1, lx, m);
        modify(l, r, v, 2*x+2, m, rx);
        values[x] = calc_op(values[2*x+1], values[2*x+2]);
        apply_mod_op(values[x], operations[x]);
    }

    void modify(int l, int r, int v){
        modify(l, r, v, 0, 0, size);
    }


    long long calc(int l, int r, int x, int lx, int rx){
        if(lx>=r || l>=rx) return NUTRAL_ELEMENT;
        if(lx>=l && rx<=r){
            return values[x];
        }
        int m = (lx+rx)/2;
        auto m1 = calc(l, r, 2*x+1, lx, m);
        auto m2 = calc(l, r, 2*x+2, m, rx);
        auto res = calc_op(m1, m2);
        apply_mod_op(res, operations[x]);
        return res;

    }

    long long calc(int l, int r){
        return calc(l, r, 0, 0, size);
    }

    long long get(int i, int x, int lx, int rx){
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
        return res+operations[x];
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
            int l, r;
            cin >> l >> r;
            cout << st.calc(l, r) << endl;
        }
    }
    return 0;
}