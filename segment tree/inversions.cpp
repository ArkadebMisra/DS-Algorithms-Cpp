//Given a permutation pi of n elements, find for each i the number of j such that j<i and pj>pi.
//link to the problem    https://codeforces.com/edu/course/2/lesson/4/3/practice/contest/274545/problem/A

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
    vector <long long> sums;

    void init(int n){
        size = 1;
        while(size<n) size*=2;
        sums.assign(2*size, 0ll);

    }


    void build(vector <int> &a,int x, int lx, int rx){
        if(rx-lx==1){
            if(lx<(int)a.size()){
                sums[x] = a[lx];
            }
            return;
        }
        int m = (lx+rx)/2;
        build(a, 2*x+1, lx, m);
        build(a, 2*x+2, m, rx);
        sums[x] = sums[2*x+1]+ sums[2*x+2];
    }
    void build(vector <int> &a){
        build(a, 0, 0, size);
    }

    void set(int i, int v, int x, int lx, int rx){
        if(rx-lx==1){
            sums[x] = v;
            return;
        }
        int m = (lx+rx)/2;
        if(i<m){
            set(i, v, 2*x+1, lx, m);
        }
        else{
            set(i, v, 2*x+2, m, rx);
        }
        sums[x] = sums[2*x+1]+ sums[2*x+2];
        
    }

    void set(int i, int v){
        set(i, v, 0, 0, size);
    }

    long long sum(int l, int r, int x, int lx, int rx){
        if(lx>=r || l>=rx) return 0;
        if(lx>=l && rx<=r){
            return sums[x];
        }
        int m = (lx+rx)/2;
        long long s1 = sum(l, r, 2*x+1, lx, m);
        long long s2 = sum(l, r, 2*x+2, m, rx);
        return s1+s2;

    }

    long long sum(int l, int r){
        return sum(l, r, 0, 0, size);
    }
};

int main(){
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    segtree st;
    st.init(n);
    vector <int> a(n);
    for(int i=0;i<n;i++){
        cin >> a[i];
    }
    for(int i=0;i<n;i++){
        cout << st.sum(a[i]-1, n) << " ";
        st.set(a[i]-1, 1);
    }
    return 0;
}