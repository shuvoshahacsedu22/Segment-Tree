#include <bits/stdc++.h>
using namespace std;


int tree[800001];
int lazy[800001];

int query(int pos,int start,int endd, int l,int r){

    if(lazy[pos]!=0){

        tree[pos]=((endd-start+1)-tree[pos]);
        if(start!=endd){
        lazy[pos*2]+=lazy[pos];
        lazy[pos*2+1]+=lazy[pos];
        lazy[pos*2]%=2;
        lazy[pos*2+1]%=2;
        }
    lazy[pos]=0;
    }
    if(start>r || endd<l || l>r) return 0;
    if(start>=l && endd<=r) {
    return tree[pos];
    }
    int mid=(start+endd)/2;
    return query(pos*2,start,mid,l,r)+query(pos*2+1,mid+1,endd,l,r);
}

void update(int pos,int start,int endd, int l,int r)
{
    if(lazy[pos]!=0){

    tree[pos]=((endd-start+1)-tree[pos]);
    if(start!=endd){
        lazy[pos*2]+=lazy[pos];
        lazy[pos*2+1]+=lazy[pos];
        lazy[pos*2]%=2;
        lazy[pos*2+1]%=2;
        }
        lazy[pos]=0;
    }
     if(start>r || endd<l || r<l) return;

    if(start>=l && endd<=r){

        tree[pos]=((endd-start+1)-tree[pos]);

        if(start!=endd){
          lazy[pos*2]+=1;
          lazy[pos*2+1]+=1;
          lazy[pos*2]%=2;
          lazy[pos*2+1]%=2;
        }
        return ;
    }

    int mid=(start+endd)/2;
    update(pos*2,start,mid,l,r);
    update(pos*2+1,mid+1,endd,l,r);
    tree[pos]=tree[pos*2]+tree[pos*2+1];
}

typedef long  long  ll;
int main()
{
    freopen("in.txt","r",stdin);
    int N,Q,cmd,l,r;
    cin>>N>>Q;
    while(Q--)
    {
        cin>>cmd;
        if(cmd){
        cin>>l>>r;
        cout<<query(1,1,N,l,r)<<endl;
        }
        else{
        cin>>l>>r;
        update(1,1,N,l,r);
        }
    }
    return 0;
}

