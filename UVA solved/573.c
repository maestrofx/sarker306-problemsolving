#include<stdio.h>
#include<math.h>
#define EPS 1e-6

int main(){
    int H, U, D, F, day;
    double climbed, temp, height;

    while(scanf("%d%d%d%d", &H, &U, &D, &F)!=EOF && H){
        for(day=1,climbed=U,temp=U*F/100.0,height=0; ;day++){
            if(climbed>0) height+=climbed;
            if(height>H) break;
            height-=D;
            if(height<0) break;
            /*printf("%d %lf %lf %lf\n", day, climbed, climbed-D, height);*/
            /*temp=(long)(temp*100+0.5)/100.5;*/
            climbed=climbed-temp;
            /*climbed=(long)(climbed*100+0.5)/100.0;*/
        }

        printf("%s", (height<0)? "failure":"success");
        printf(" on day %d\n", day);
    }

    return 0;
}
