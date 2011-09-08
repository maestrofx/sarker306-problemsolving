#include <stdio.h>

#define INF 1e300
#define EPS 1e-8

typedef struct{
	int u, v;
	double w;
}resist;

int index[100], totl;
resist list[60];
double mat[100][100], A[100][100], B[100], X[100];
int pi[100], x, y, n;

void LUP_Solve(int n){
    int i, j;
	double y[66];

	LUP_Decomp(n);
	/*show_A();*/

	for(i=1;i<=n;i++){
		y[i]=0;

		for(j=1;j<i;j++) y[i]=y[i]+A[i][j]*y[j];
		y[i]=B[pi[i]]-y[i];
	}

	/*show_Y(y);*/
	for(i=n;i;i--){
		X[i]=0;

		for(j=i+1;j<=n;j++) X[i]=X[i]+A[i][j]*X[j];
		X[i]=(y[i]-X[i])/A[i][i];
	}

	/*show_X();*/
}

int find(int a){
	int i;

	for(i=1;i<=totl;i++) if(index[i]==a) return i;
	return -1;
}

void input(int m){
	int i;

	for(i=0;i<m;i++) scanf("%d%d%lf", &list[i].u, &list[i].v, &list[i].w);
}

void preprocess(int m){
	int i, j, a, b, tmp, tmp1;

	for(i=0;i<m;i++){
		if(list[i].u!=list[i].v && list[i].w<EPS && list[i].w>-EPS){
			tmp=list[i].v;
			tmp1=list[i].u;
			/*a=find(list[i].u);
			b=find(list[i].v);
			if(a==-1) tmp=list[i].u, tmp1=list[i].v;
			else if(b==-1) tmp=list[i].v, tmp1=list[i].u;
			else if(a<b) tmp=list[i].v, tmp1=list[i].u;
			else tmp=list[i].u, tmp1=list[i].v;*/

			for(j=0;j<m;j++){
				if(i==j) continue;
				if(list[j].u==tmp) list[j].u=tmp1;
				if(list[j].v==tmp) list[j].v=tmp1;
			}

			/*if(a==-1) list[i].u=list[i].v;
			else if(b==-1 || a<b) list[i].v=list[i].u;
			else list[i].u=list[i].v;*/
			list[i].v=list[i].u;
			if(x==tmp) x=tmp1;
			if(y==tmp) y=tmp1;
		}
	}

	/*for(i=0;i<m;i++) printf("%d  %d  %lf\n", list[i].u, list[i].v, list[i].w);
	puts("");*/
}

void init(){
	int a, b;

	for(a=0;a<66;a++)
		for(b=0;b<66;b++)
			mat[a][b]=INF, A[a][b]=0;

	totl=0;
}

int main()
{
	int m,a,b,kase=1;
	double c;

	while(scanf("%d %d %d",&m,&x,&y)!=EOF && m && y && x){
		n=0;

		init();
		input(m);
		preprocess(m);

		a=find(x);
		if(a==-1){
			index[++totl]=x;
			a=totl;
		}

		b=find(y);
		if(b==-1){
			index[++totl]=y;
			b=totl;
		}

		x=a;
		y=b;
		/*printf("Start : %d, End : %d\n", x, y);
*/
		while(m--){
			c=list[m].w;

			a=find(list[m].u);
			if(a==-1){
				index[++totl]=list[m].u;
				a=totl;
			}
			b=find(list[m].v);
			if(b==-1){
				index[++totl]=list[m].v;
				b=totl;
			}

			/*printf("%d %d, %d %d\n", list[m].u, a, list[m].v, b);*/
			if(n<a) n=a;
			if(n<b) n=b;

			if(a==b) continue;

			if(mat[a][b]==INF) mat[a][b]=c;
			else mat[a][b]=(mat[a][b]*c)/(mat[a][b]+c);
			if(mat[b][a]==INF) mat[b][a]=c;
			else mat[b][a]=(mat[b][a]*c)/(mat[b][a]+c);
		}

		for(a=1;a<=n;a++){
			for(b=1;b<=n;b++){
				if(mat[a][b]!=INF){
					A[a][a]=A[a][a]+1/mat[a][b], A[a][b]=-1/mat[a][b];
				}
			}

			if(a==x) B[a]=1;
			else if(a==y) B[a]=-1;
			else B[a]=0;
		}

		for(a=1;a<=n;a++)
			for(b=1;b<=n;b++)
				A[a][b]=(A[a][b]*100000+0.5)/100000;

		/*show_A();*/

		if(x==y){
			printf("Case %d: ", kase++);
			printf("0.00 Ohms\n");
		}
		else if(n>2){
			LUP_Solve(n);
		/*	floyed();*/
			printf("Case %d: ", kase++);
			printf("%.2lf Ohms\n",X[x]-X[y]);
		}
		else printf("Case %d: %.2lf Ohms\n", kase++, mat[x][y]);
	}

	return 0;
}

/* 3 1 3
1 2 5.5
1 2 3.5
2 3 0.75 */
