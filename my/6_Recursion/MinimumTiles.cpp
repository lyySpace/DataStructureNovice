#include <iostream>
#include <vector>
using namespace std;

int ans;
 
int find_max_edge(int x){
    int ans=1;
    while((ans<<1)<=x){
        ans<<=1;
    }
    return ans;
}
 
void cut_max(int n, int m){
    //n<m
    if(n>m)swap(n, m);
    if(!n)return;
    if(n==1 or m==1){
        ans+=m;
        return;
    }
    ++ans;
 
    int x=find_max_edge(n);
    cut_max(n-x, x);
    cut_max(m-x, n);
}
 
int main(){
    int n,m;
 
    cin >>n>>m;
    while(!(n & 1) and !(m & 1)){
        n>>=1, m>>=1;
    }
 
    cut_max(n, m);
    cout<<ans<<'\n';
}