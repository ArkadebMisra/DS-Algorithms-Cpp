//This problem is the reversed version of the previous one. There was a permutation pi of n elements, 
//for each i we wrote down the number ai,
// the number of j such that j<i and pj>pi. Restore the original permutation for the given ai.


//link to the problem   https://codeforces.com/edu/course/2/lesson/4/3/practice/contest/274545/problem/B
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


typedef int item;
//struct item{
//    long long seg, pref, suf, sum;
//};

struct segtree{
    int size;
    vector <item> values;

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
        values.resize(2*size);

    }


    void build(vector <int> &a,int x, int lx, int rx){
        if(rx-lx==1){
            if(lx<(int)a.size()){
                values[x] = single(a[lx]);
            }
            return;
        }
        int m = (lx+rx)/2;
        build(a, 2*x+1, lx, m);
        build(a, 2*x+2, m, rx);
        values[x] = merge(values[2*x+1], values[2*x+2]);
    }


    void build(vector <int> &a){
        build(a, 0, 0, size);
    }

    void set(int i, int v, int x, int lx, int rx){
        if(rx-lx==1){
            values[x] = single(v);
            return;
        }
        int m = (lx+rx)/2;
        if(i<m){
            set(i, v, 2*x+1, lx, m);
        }
        else{
            set(i, v, 2*x+2, m, rx);
        }
        values[x] = merge(values[2*x+1],  values[2*x+2]);
        
    }

    void set(int i, int v){
        set(i, v, 0, 0, size);
    }

    item calc(int l, int r, int x, int lx, int rx){
        if(lx>=r || l>=rx) return NUTRAL_ELEMENT;
        if(lx>=l && rx<=r){
            return values[x];
        }
        int m = (lx+rx)/2;
        item s1 = calc(l, r, 2*x+1, lx, m);
        item s2 = calc(l, r, 2*x+2, m, rx);
        return merge(s1, s2);

    }

    item calc(int l, int r){
        return calc(l, r, 0, 0, size);
    }

    int find(int k, int x, int lx, int rx){
        if(rx-lx==1){
            return lx;
        }
        int m = (lx+rx)/2;
        int sl = values[2*x+2];
        if(k<sl){
            return  find(k, 2*x+2, m, rx);
        }
        else{
            return find(k-sl, 2*x+1, lx, m);
        }

    }

    int find(int k){
        return find(k, 0, 0, size);
    }
};

int main(){
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    segtree st;
    st.init(n);
    vector <int> a(n), ans(n);
    for(int i=0;i<n;i++){
        a[i] = 1;
    }
    st.build(a);

    for(int i=0;i<n;i++){
        cin >> ans[i];
    }
    for(int i=n-1;i>=0;i--){
        ans[i] = st.find(ans[i]);
        st.set(ans[i], 0);
        ans[i]++;
    }
    for(int i=0;i<n;i++){
        cout << ans[i] << " ";
    }
    cout << endl;

    return 0;
}