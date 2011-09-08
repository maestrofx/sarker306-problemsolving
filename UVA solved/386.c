#include<stdio.h>

int main()
{
    int b, c, d, a;
    long x, y, z, p;
    for(a=2;a<=200;a++)
    {
        for(b=2;b<a;b++)
        {
            x=b*b*b;
            for(c=b;c<a;c++)
            {
                y=c*c*c;
                for(d=c;d<a;d++)
                {
                    z=x+y+d*d*d;
                    if(a*a*a==z) printf("Cube = %d, Triple = (%d,%d,%d)\n", a, b, c, d);
                }
            }
        }
    }
    return 0;
}
