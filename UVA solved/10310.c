#include<stdio.h>
#include<math.h>
#define EPS 1e-6
#define MAX 1005

typedef struct{
	double x, y;
}pos;

pos listofholes[MAX+5];

double distance(pos a, pos b){
	double delx=a.x-b.x, dely=a.y-b.y;
	return sqrt(delx*delx+dely*dely);	
}

int main(){
	pos dog, gopher, hole, now;
	long n, i;
	double gopherdis, dogdis, diff;
	
	while(scanf("%ld", &n)!=EOF){
		hole.y=-99999, hole.x=99999;
		scanf("%lf%lf%lf%lf", &gopher.x, &gopher.y, &dog.x, &dog.y);
		for(i=0;i<n;i++){
			scanf("%lf%lf", &now.x, &now.y);
			listofholes[i]=now;
		}
		for(i=n-1;i>=0;i--){
			now=listofholes[i];
			gopherdis=distance(gopher, now), dogdis=distance(dog, now);
			diff=2*gopherdis-dogdis;
			if(diff>-EPS && diff<EPS) hole=now;
			else if(diff<0) hole=now;
		}
		if(hole.y==-99999) printf("The gopher cannot escape.\n");
		else printf("The gopher can escape through the hole at (%.3lf,%.3lf).\n", hole.x, hole.y);
	}
	
	return 0;
}
