#include<algorithm>
#include<cmath>
#include<iostream>
#include<vector>
#include<cstdio>
#include<cstring>
using namespace std;
const int  maxn=600 ;//点数
const int  maxm=20005 ;//边数
const int  inf= 0x7fffffff;
struct node{
    int  u,v,next;
    int  val,cost;
}s[maxm*2];
int  ind, p[maxn], que[1000000];
char v[maxn];
void init(){
    ind=0 ;
    memset(p,- 1 ,sizeof(p));
}
inline void insert(int  x, int  y, int  z, int  c){//x->y  的容量为z,单位容量花费为c
    s[ind].cost=c; s[ind].u=x;  s[ind].v=y; s[ind].val=z;
    s[ind].next=p[x];   p[x]=ind++;
    
    s[ind].cost=-c; s[ind].u=y; s[ind].v=x; s[ind].val= 0 ;
    s[ind].next=p[y];   p[y]=ind++;
}
//网络中有0~n-1 （包含）的点, 其中source 和sink也在里面
int  min_cost_max_flow(int  n, int  source,int  sink,int & netcost){  //返回最大流量,netcost 是最小费用
    int  pre[maxn],min[maxn],i,t,  ret=0;
    for  (netcost=0;;){
        for  (i=0;i<n;i++)
            pre[i]=-1,min[i]=-inf; //-inf
        pre[source]=-1;
        min[source]= 0;
        int  h= 0 ,r= 0;
        que[0]=source;
        memset(v,0,sizeof(v));
        v[source]= 1;
        while (h<=r) {
            t=que[h++];
            v[t]= 0;
            for (i=p[t];i!=- 1 ;i=s[i].next){
                int  to=s[i].v;
                if(s[i].val>0 &&min[t]+s[i].cost>min[to]){   //>
                    min[to]=min[t]+s[i].cost;
                    pre[to]=i;
                    if(v[to]==0) {
                        v[to]=1 ;
                        que[++r]=to;
                    }
                }
            }
        }
        if(pre[sink]==-1 )break ;
        t=inf;
        for (i=sink;pre[i]!=-1;){
            if(s[pre[i]].val<t)
                t=s[pre[i]].val;
            i=s[pre[i]].u;
        }
        netcost+=min[sink]*t;
        ret+=t;
        for (i=sink;pre[i]!=-1;){
            s[pre[i]].val-=t;
            s[pre[i]^1 ].val+=t;
            i=s[pre[i]].u;
        }
    }
    return ret;
}


int n,m,S,T;

int map[510][10];

int  main() {
    int cas = 0;
    while  (scanf("%d",&n) ,n) {
        int  x,y,z,i,j;
        char ch[20];
        for(i = 1;i <= n; i++){
            scanf("%s",ch);
            for(j = 1;j <= 8;j ++){
                scanf("%d",&map[i][j]);
            }
        }
        
        vector<int> ac;
        int ans = 0,tmp;
        
        
        
        init();
        T = n + 8 + 1;
        S = T + 1;
        insert(S,0,11,0);
        for(i = 1;i <= n;i ++)
            insert(0,i,1,0);
        for(i = 1;i <= n; i++){
            for(j = 1;j <= 8;j ++){
                insert(i,n+j,1,map[i][j]);
            }
        }
        insert(n+1,T,1,0);
        insert(n+2,T,2,0);
        insert(n+3,T,1,0);
        insert(n+4,T,1,0);
        insert(n+5,T,2,0);
        insert(n+6,T,1,0);
        insert(n+7,T,1,0);
        insert(n+8,T,2,0);
        min_cost_max_flow(S + 1,S,T,tmp);
        if(tmp > ans){
            ans = tmp;
            ac.clear();
            ac.push_back(1);
        }
        else if(tmp == ans){
            ac.push_back(1);
        }
        
        init();
        T = n + 8 + 1;
        S = T + 1;
        insert(S,0,11,0);
        for(i = 1;i <= n;i ++)
            insert(0,i,1,0);
        for(i = 1;i <= n; i++){
            for(j = 1;j <= 8;j ++){
                insert(i,n+j,1,map[i][j]);
            }
        }
        insert(n+1,T,1,0);
        insert(n+2,T,2,0);
        insert(n+3,T,1,0);
        insert(n+4,T,1,0);
        insert(n+5,T,3,0);
        insert(n+6,T,1,0);
        insert(n+7,T,1,0);
        insert(n+8,T,1,0);
        min_cost_max_flow(S + 1,S,T,tmp);
        if(tmp > ans){
            ans = tmp;
            ac.clear();
            ac.push_back(2);
        }
        else if(tmp == ans){
            ac.push_back(2);
        }
        
        init();
        T = n + 8 + 1;
        S = T + 1;
        insert(S,0,11,0);
        for(i = 1;i <= n;i ++)
            insert(0,i,1,0);
        for(i = 1;i <= n; i++){
            for(j = 1;j <= 8;j ++){
                insert(i,n+j,1,map[i][j]);
            }
        }
        insert(n+1,T,1,0);
        insert(n+2,T,2,0);
        insert(n+3,T,1,0);
        insert(n+4,T,1,0);
        insert(n+5,T,3,0);
        insert(n+8,T,3,0);
        min_cost_max_flow(S + 1,S,T,tmp);
        if(tmp > ans){
            ans = tmp;
            ac.clear();
            ac.push_back(3);
        }
        else if(tmp == ans){
            ac.push_back(3);
        }
        
        
        init();
        T = n + 8 + 1;
        S = T + 1;
        insert(S,0,11,0);
        for(i = 1;i <= n;i ++)
            insert(0,i,1,0);
        for(i = 1;i <= n; i++){
            for(j = 1;j <= 8;j ++){
                insert(i,n+j,1,map[i][j]);
            }
        }
        insert(n+1,T,1,0);
        insert(n+2,T,3,0);
        insert(n+5,T,3,0);
        insert(n+6,T,1,0);
        insert(n+7,T,1,0);
        insert(n+8,T,2,0);
        min_cost_max_flow(S + 1,S,T,tmp);
        if(tmp > ans){
            ans = tmp;
            ac.clear();
            ac.push_back(4);
        }
        else if(tmp == ans){
            ac.push_back(4);
        }
        
        
        init();
        T = n + 8 + 1;
        S = T + 1;
        insert(S,0,11,0);
        for(i = 1;i <= n;i ++)
            insert(0,i,1,0);
        for(i = 1;i <= n; i++){
            for(j = 1;j <= 8;j ++){
                insert(i,n+j,1,map[i][j]);
            }
        }
        insert(n+1,T,1,0);
        insert(n+2,T,3,0);
        insert(n+5,T,4,0);
        insert(n+6,T,1,0);
        insert(n+7,T,1,0);
        insert(n+8,T,1,0);
        min_cost_max_flow(S + 1,S,T,tmp);
        if(tmp > ans){
            ans = tmp;
            ac.clear();
            ac.push_back(5);
        }
        else if(tmp == ans){
            ac.push_back(5);
        }
        
        
        init();
        T = n + 8 + 1;
        S = T + 1;
        insert(S,0,11,0);
        for(i = 1;i <= n;i ++)
            insert(0,i,1,0);
        for(i = 1;i <= n; i++){  
            for(j = 1;j <= 8;j ++){
                insert(i,n+j,1,map[i][j]);
            }
        }
        insert(n+1,T,1,0);
        insert(n+2,T,3,0);
        insert(n+3,T,1,0);
        insert(n+4,T,1,0);
        insert(n+5,T,3,0);
        insert(n+8,T,2,0);
        min_cost_max_flow(S + 1,S,T,tmp);
        if(tmp > ans){
            ans = tmp;
            ac.clear();
            ac.push_back(6);
        }
        else if(tmp == ans){
            ac.push_back(6);
        }
        
        init(); 
        T = n + 8 + 1;
        S = T + 1;
        insert(S,0,11,0);
        for(i = 1;i <= n;i ++)
            insert(0,i,1,0);
        for(i = 1;i <= n; i++){  
            for(j = 1;j <= 8;j ++){
                insert(i,n+j,1,map[i][j]);
            }
        }
        insert(n+1,T,1,0);
        insert(n+2,T,4,0);
        insert(n+3,T,1,0);
        insert(n+4,T,1,0);
        insert(n+5,T,3,0);
        insert(n+8,T,1,0);
        min_cost_max_flow(S + 1,S,T,tmp);
        if(tmp > ans){
            ans = tmp;
            ac.clear();
            ac.push_back(7);
        }
        else if(tmp == ans){
            ac.push_back(7);
        }
        
        
        for(i = 0;i <ac.size();i ++){
            if(ac[i] == 7)
                printf("Formation China has the highest points %d.\n",ans);
            else
                printf("Formation %c has the highest points %d.\n",'A'+ac[i]-1,ans);
        }
        puts("");
    } 
}