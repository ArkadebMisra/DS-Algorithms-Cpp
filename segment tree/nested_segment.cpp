//Given an array of 2n numbers, each number from 1 to n in it occurs exactly twice. 
//We say that the segment y is nested inside the segment x if both 
//occurrences of the number y are between the occurrences of the number x. 
//Find for each segment i how many segments that are nested inside it.


//link to the problem   https://codeforces.com/edu/course/2/lesson/4/3/practice/contest/274545/problem/C


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
    st.init(2*n);
    vector <int> in(2*n),a(2*n), ans(n+1), l_border(n+1), l_border_index(n+1);
    
    l_border.resize(n+1);
    for(int i=0;i<2*n;i++){
        cin >> in[i];
    }
    st.build(a);

    for(int i=0;i<2*n;i++){
        if(l_border[in[i]]==1){
            ans[in[i]] = st.calc(l_border_index[in[i]], i);
            st.set(l_border_index[in[i]], 1);
        }
        else{
            l_border[in[i]] = 1;
            l_border_index[in[i]] = i;
        }
    }
    for(int i=1;i<=n;i++){
        cout << ans[i] << " ";
    }
    cout << endl;

    return 0;
}