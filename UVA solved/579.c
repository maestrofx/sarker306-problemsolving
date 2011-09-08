#include<stdio.h>

int main()
{
    int h, m;
    char ch;
    double x, y, z;
    while ( scanf ( "%d%c%d", &h, &ch, &m ) ==3 && h||m )
    {
        h = h % 12;
        y = h * 30 + m / 2+0.5*(m%2);
        z = m * 6;
        x = ( y > z ) ? y - z : z - y;
        if ( x > 180 ) x = 360 - x;
        printf ( "%.3lf\n", x );
    }
    return 0;
}
