#include<stdio.h>
#include<math.h>
#define MAX 1001
#define INF 99999999
#define EPS 1e-6
#define RADIUS 1000000
#define PI 3.1415926535897932384626433832795

typedef struct{
	double lati, longi;
}pos;

pos array[MAX+5];
/* Great Circle Distance Functions */

double greatcircledistance(double lat1, double long1, double lat2, double long2){
	double dellat=lat2-lat1, dellong=long2-long1;
	double x=cos(lat2)*sin(dellong);
	double y=cos(lat1)*sin(lat2)-sin(lat1)*cos(lat2)*cos(dellong);
	double z=sin(lat1)*sin(lat2)+cos(lat1)*cos(lat2)*cos(dellong);
	
	x=x*x;
	y=y*y;
	return RADIUS*atan2(sqrt(x+y),z);
}

double degtorad(double degree){
	double rad=degree*PI/180;
	return rad;
}

int main(){
	long n, i, j;
	pos x, y;
	double max, min, dis, deglat, deglong;
	
	while(scanf("%ld", &n)!=EOF){
		for(i=0;i<n;i++){
			scanf("%lf%lf", &x.lati, &x.longi);
			array[i]=x;
		}
		
		for(i=0, min=INF;i<n;i++){
			deglat=degtorad(array[i].lati), deglong=degtorad(array[i].longi);
			for(j=0, max=-INF;j<n;j++){
				if(i==j) continue;
				dis=greatcircledistance(deglat, deglong, degtorad(array[j].lati), degtorad(array[j].longi));
				if(max<dis || fabs(max-dis)<EPS) max=dis;
			}
			if(max<min || fabs(max-min)<EPS) min=max, y=array[i];
		}
		
		printf("%.2lf %.2lf\n", y.lati, y.longi);
	}
	
	return 0;
}
