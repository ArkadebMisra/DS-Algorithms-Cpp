//This problem is exactly the same as in the previous lesson, 
//but this time try to solve it using the technique that was discussed in the lecture.

//There is an array of n elements, initially filled with zeros. You need to write a data structure that processes two types of queries:

//add to the segment from l to r−1 the number v,
//find the current value of element i.

//link to the problem  https://codeforces.com/edu/course/2/lesson/5/1/practice/contest/279634/problem/A


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

    }



    void add(int l, int r, int v, int x, int lx, int rx){
        if(lx>=r || l>=rx) return;
        if(lx>=l && rx<=r){
            operations[x] +=v;
            return;
        }
        int m = (lx+rx)/2;
        add(l, r, v, 2*x+1, lx, m);
        add(l, r, v, 2*x+2, m, rx);

    }

    void add(int l, int r, int v){
        add(l, r, v, 0, 0, size);
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
            st.add(l, r, v);
        }
        else{
            int i;
            cin >> i;
            cout << st.get(i) << endl;
        }
    }
    return 0;
}