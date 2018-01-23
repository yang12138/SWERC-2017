/* ***********************************************
Author        :yang12138
Created Time  :2018年01月23日 星期二 13时44分42秒
File Name     :B.cpp
************************************************ */
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <string>
#include <math.h>
#include <cstdlib>
#include <vector>
#include <queue>
#include <set>
#include <stack>
#include <map>
using namespace std;
#define mem(a,b) memset(a,b,sizeof(a))
typedef long long ll;
typedef pair<int,int>pii;
#define lson (root<<1)
#define rson (root<<1|1)

const int N=2005;

int len[N][N];
bool vis[N][N];
ll dp[N][N];

int l[N],r[N];
ll f[N][N];

stack<int>st;
void fuck(int* a,int n){

	while(!st.empty()) st.pop();

	l[1]=0;
	st.push(1);
	for(int i=2;i<=n;i++){
		while(!st.empty() && a[st.top()]>=a[i]) st.pop();
		if(st.empty()) l[i]=0;
		else l[i]=st.top();
		st.push(i);
	}

	while(!st.empty()) st.pop();

	r[n]=n+1;
	st.push(n);
	for(int i=n-1;i>=1;i--){
		while(!st.empty() && a[st.top()]>a[i]) st.pop();
		if(st.empty()) r[i]=n+1;
		else r[i]=st.top();
		st.push(i);
	}

	for(int i=1;i<=n;i++){
		if(a[i]==0) continue;
		int tl=i-l[i],tr=r[i]-i;
		if(tl>tr) swap(tl,tr);
		for(int j=0;j<tl-1;j++){
			dp[a[i]][j+1]+=j+1;
			dp[a[i]][(tl+tr-2)-j+1]+=j+1;
		}
		f[a[i]][tl]+=tl;
		f[a[i]][tr+1]-=tl;
	}
}

void solve(){
	int X,Y,n,Q;
	scanf("%d%d%d%d",&X,&Y,&n,&Q);

	for(int i=1;i<=n;i++){
		int x1,x2,y1,y2;
		scanf("%d%d%d%d",&x1,&x2,&y1,&y2);
		x1++,y1++;
		for(int j=x1;j<=x2;j++){
			for(int k=y1;k<=y2;k++){
				vis[j][k]=1;
			}
		}
	}
	
	for(int j=1;j<=Y;j++){
		for(int i=X;i>=1;i--){
			if(vis[i][j]) len[i][j]=0;
			else len[i][j]=len[i+1][j]+1;
		}
	}

	for(int i=1;i<=X;i++) fuck(len[i],Y);

	for(int i=1;i<=X;i++){
		for(int j=1;j<=Y;j++) f[i][j]+=f[i][j-1],dp[i][j]+=f[i][j];
	}

	for(int i=X;i>=1;i--){
		for(int j=1;j<=Y;j++) dp[i][j]+=dp[i+1][j];
	}

	while(Q--){
		int x,y;
		scanf("%d%d",&x,&y);
		printf("%lld\n",dp[x][y]);
	}

}

int main(){
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    
	solve();
    return 0;
}

