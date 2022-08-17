/**
    1) i v: set arr[i]=v
    2) l r: calculate the minimum and count of min in [l,r−1]
    https://codeforces.com/edu/course/2/lesson/4/1/practice/contest/273169/problem/C
*/
#include<bits/stdc++.h>
#define MAX 100005
#define ll long long
using namespace std;

ll arr[MAX];
int N;

struct info{
    ll val,cnt;
    info(){
        val=INT_MAX;
        cnt=0;
    }
    info(ll x, ll y){
        val=x;cnt=y;
    }
    void show(){
        cout<<val<<" "<<cnt<<"\n";
    }
};
info tree[3*MAX];

info leaf(int i){
    return info(arr[i],1LL);
}
info outOfRange(){
    return info();
}
info merge(info x, info y){
    info temp;
    temp.val=min(x.val, y.val);
    if(temp.val==x.val) temp.cnt+=x.cnt;
    if(temp.val==y.val) temp.cnt+=y.cnt;
    return temp;
}

void build(int node, int l,int r)
{
    if(l==r)
    {
        tree[node]=leaf(l);
        return;
    }
    int mid=(l+r)/2;
    build(node*2,l,mid);
    build(node*2+1,mid+1,r);
    tree[node]=merge(tree[node*2],tree[2*node+1]);
}

info query(int node,int l,int r,int i,int j)
{
    if(i>r || j<l)
        return outOfRange();
    if(l>=i && r<=j)
        return tree[node];
    int mid=(l+r)/2;
    auto x=query(node*2,l,mid,i,j);
    auto y=query(node*2+1,mid+1,r,i,j);
    return merge(x,y);
}

void update(int node,int l,int r,int pos,ll val)
{
    if(pos>r || pos<l)
        return;
    if(l==r)
    {
        tree[node]=info(val, 1LL);
        return;
    }
    int mid=(l+r)/2;
    if(pos<=mid)
        update(node*2,l,mid,pos,val);
    else
        update(node*2+1,mid+1,r,pos,val);

    tree[node]=merge(tree[node*2],tree[2*node+1]);
}

int searchQuery(int node, int l, int r, ll sum)
{
    int mid=(l+r)/2;
    if(l==r)
        return l;
    if(sum<=tree[2*node].val)
    {
       return searchQuery(2*node, l, mid, sum);
    }
    else
    {
        return searchQuery(2*node+1, mid+1, r, sum-tree[2*node].val);
    }
}
void print(int node, int l,int r)
{
    cout<<"["<<l<<","<<r<<"]:--> ";
    tree[node].show();
    if(l==r)
        return;
    int mid=(l+r)/2;
    print(node*2,l,mid);
    print(node*2+1,mid+1,r);
}
void print(){
    print(1,0,N-1);
}
void build(int n){
    N=n;
    build(1,0,N-1);
}
void update(int pos, ll val){
    update(1,0,N-1,pos,val);
}
info query(int x, int y){
    auto ans = query(1,0,N-1,x,y); 
    return ans;
}
int find_index(ll sum){
    return searchQuery(1,0,N-1,sum);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n,i,q,k;
    cin>>n>>q;
    for(i=0;i<n;i++)
        cin>>arr[i];
    build(n);
    while(q--)
    {
        cin>>k;
        if(k==1){
            int x,y;
            cin>>x>>y;
            update(x,y);
        }
        else{
            int x; ll y;
            cin>>x>>y;
            auto ans=query(x,y-1);
            cout<<ans.val<<" "<<ans.cnt<<endl;
        }
    }
    return 0;
}
