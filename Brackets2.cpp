
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define ff first
#define ss second
#define mp make_pair
#define memo(a,b) memset(a,b,sizeof(a))
#define INF 1e9
#define EPS 1e-8
#define PI 3.14159265358979323846

typedef long  long  ll;

ll ar[200005];
ll tree[800005];
struct segtree
{
    long long msum,mps,mss,s;
};
segtree node[200005],inf;
segtree merge(segtree leftchild,segtree rightchild)
{
    segtree res;

    res.s=leftchild.s+rightchild.s;
    res.mps=max(leftchild.mps,leftchild.s+rightchild.mps);
    res.mss=max(rightchild.mss,rightchild.s+leftchild.mss);
    res.msum=max(max(leftchild.msum,rightchild.msum),leftchild.mss+rightchild.mps);

    return res;
}
void build(ll pos,ll low,ll high)
{

    if(low==high)
    {
        node[pos].mps=node[pos].mss=node[pos].msum=node[pos].s=ar[low];
        return;
    }
    ll mid=(low+high)/2;

    build(2*pos+1,low,mid);
    build(2*pos+2,mid+1,high);
    node[pos]=merge(node[pos*2+1],node[pos*2+2]);
}
void update(ll pos,ll low,ll high,ll idx,ll val)
{
    if(idx>high || idx<low)
        return;
    if(low==high)
    {
        node[pos].mps=node[pos].mss=node[pos].msum=node[pos].s=val;
        return;
    }
    ll mid=(low+high)/2;

    if(idx<=mid)
    {
        update(2*pos+1,low,mid,idx,val);
    }
    else update(2*pos+2,mid+1,high,idx,val);
    node[pos]=merge(node[pos*2+1],node[pos*2+2]);

}
segtree query(ll pos,ll low,ll high,ll qlow,ll qhigh)
{
    if(low>high || low>qhigh || high<qlow)
        {
        inf.mps=inf.mss=inf.msum=-1000000;
        inf.s=0;
        return inf;
        }
    if(qlow<=low && high<=qhigh)
        return node[pos];
    ll mid=(low+high)/2;

    return merge(query(pos*2+1,low,mid,qlow,qhigh),query(pos*2+2,mid+1,high,qlow,qhigh));
}
int  main()
{

    freopen("in.txt","r",stdin);
    ll t,u,v,k,N,q,x1,x2,y1,y2;
    cin>>t;
    while(t--){

    cin>>N;
    for(ll i=0;i<N;i++) cin>>ar[i+1];
    build(1,1,N);
    cin>>q;
    while(q--){
    ll ans;
    cin>>x1>>y1>>x2>>y2;
    if(y1<x2) ans=query(1,1,N,x1,y1).mss+query(1,1,N,y1+1,x2-1).s+query(1,1,N,x2,y2).mps;
    else{
    ans=query(1,1,N,x1,x2-1).mss+query(1,1,N,x2,y2).mps;
    ans=max(ans,(query(1,1,N,x2,y1).mss+query(1,1,N,y1+1,y2).mps));
    ans=max(ans,query(1,1,N,x2,y1).msum);
    }
    cout<<ans<<endl;
    }

    }
}
