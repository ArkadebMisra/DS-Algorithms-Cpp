//Now change the code of the segment tree so that the minimum on the segment is calculated instead of the sum.
//link to the problem   https://codeforces.com/edu/course/2/lesson/4/1/practice/contest/273169/problem/B

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


struct segtree{
    int size;
    vector <int> values;

    void init(int n){
        size = 1;
        while(size<n) size*=2;
        values.assign(2*size, 0ll);

    }


    void build(vector <int> &a,int x, int lx, int rx){
        if(rx-lx==1){
            if(lx<(int)a.size()){
                values[x] = a[lx];
            }
            return;
        }
        int m = (lx+rx)/2;
        build(a, 2*x+1, lx, m);
        build(a, 2*x+2, m, rx);
        values[x] = min(values[2*x+1], values[2*x+2]);
    }
    void build(vector <int> &a){
        build(a, 0, 0, size);
    }

    void set(int i, int v, int x, int lx, int rx){
        if(rx-lx==1){
            values[x] = v;
            return;
        }
        int m = (lx+rx)/2;
        if(i<m){
            set(i, v, 2*x+1, lx, m);
        }
        else{
            set(i, v, 2*x+2, m, rx);
        }
        values[x] = min(values[2*x+1],  values[2*x+2]);
        
    }

    void set(int i, int v){
        set(i, v, 0, 0, size);
    }

    int calc(int l, int r, int x, int lx, int rx){
        if(lx>=r || l>=rx) return INT_MAX;
        if(lx>=l && rx<=r){
            return values[x];
        }
        int m = (lx+rx)/2;
        int s1 = calc(l, r, 2*x+1, lx, m);
        int s2 = calc(l, r, 2*x+2, m, rx);
        return min(s1, s2);

    }

    int calc(int l, int r){
        return calc(l, r, 0, 0, size);
    }
};

int main(){
    ios::sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    segtree st;
    st.init(n);
    vector <int> a(n);
    for(int i=0;i<n;i++){
        cin >> a[i];
    }
    st.build(a);

    while(m--){
        int op;
        cin >> op;
        if(op==1){
            int i, v;
            cin >> i >> v;
            st.set(i, v);
        }
        else{
            int l, r;
            cin >> l >> r;
            cout << st.calc(l, r) << endl;
        }
    }
    return 0;
}