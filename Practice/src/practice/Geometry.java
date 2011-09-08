package practice;

import java.awt.Point;
import java.awt.Polygon;
import java.util.Scanner;

class Geometry{
    public static void main(String args[]){
        Scanner scn =  new Scanner(System.in);
        int vertices, x, y;

        while(scn.hasNextInt() == true){
            vertices = scn.nextInt();
            if( vertices <= 0 ) break;
            Polygon poly = new Polygon();

            for( int i = 0 ; i < vertices ; i++ ){
                x = scn.nextInt();
                y = scn.nextInt();
                poly.addPoint(x, y);
            }

            x = scn.nextInt();
            y = scn.nextInt();

            if(poly.contains(x, y) == true) System.out.println('T');
            else System.out.println('F');
        }
        
        scn.close();
    }
}
