//There is an array of n elements, initially filled with zeros. 
//You need to write a data structure that processes two types of queries:

//add v to the segment from l to r−1,
//find the minimum on the segment from l to r−1.

//link to the problem  https://codeforces.com/edu/course/2/lesson/5/2/practice/contest/279653/problem/A


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
    vector <item>  operations;
    vector <item> mins;

    item NUTRAL_ELEMENT = 0;

    item merge(item a, item b){
        return a+b;
    }

    item single(int v){
        return v;
    }

    void init(int n){
        size = 1;
        while(size<n) size*=2;
        operations.assign(2*size, 0ll);
        mins.assign(2*size, 0ll);

    }



    void add(int l, int r, int v, int x, int lx, int rx){
        if(lx>=r || l>=rx) return;
        if(lx>=l && rx<=r){
            operations[x] += v;
            mins[x] += v;
            return;
        }
        int m = (lx+rx)/2;
        add(l, r, v, 2*x+1, lx, m);
        add(l, r, v, 2*x+2, m, rx);
        mins[x] = std::min(mins[2*x+1], mins[2*x+2])+operations[x];
    }

    void add(int l, int r, int v){
        add(l, r, v, 0, 0, size);
    }


    long long min(int l, int r, int x, int lx, int rx){
        if(lx>=r || l>=rx) return LLONG_MAX;
        if(lx>=l && rx<=r){
            return mins[x];
        }
        int m = (lx+rx)/2;
        auto m1 = min(l, r, 2*x+1, lx, m);
        auto m2 = min(l, r, 2*x+2, m, rx);
        return std::min(m1, m2) + operations[x];

    }

    long long min(int l, int r){
        return min(l, r, 0, 0, size);
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
            st.add(l, r, v);
        }
        else{
            int l, r;
            cin >> l >> r;
            cout << st.min(l, r) << endl;
        }
    }
    return 0;
}