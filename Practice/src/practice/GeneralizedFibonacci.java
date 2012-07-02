/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package practice;
import java.math.BigInteger;
import java.util.Scanner;

public class GeneralizedFibonacci {
    private static BigInteger[] fibonacci;
    private static int a, b, c;
    private static BigInteger Ga, Gb, Gc, G1, G0, tmp;
    private static Scanner scn;
    
    public static void InitFibonacci() {
        fibonacci = new BigInteger[1002];
        
        fibonacci[0] = BigInteger.ZERO;
        fibonacci[1] = BigInteger.ONE;
        for ( int i = 2 ; i < 1002 ; i++ )
            fibonacci[i] = fibonacci[i-1].add(fibonacci[i-2]);
    }
    
    public static BigInteger Fibonacci( int n ) {
        if ( n >= 0 ) return fibonacci[n];
        else return ( (n & 1) == 1 ) ? fibonacci[-n] : fibonacci[-n].negate();
    }
    
    private static void CalculateBoundaryCondition() {
        tmp = Fibonacci(a).multiply(Fibonacci(b-1)).subtract(Fibonacci(b).multiply(Fibonacci(a-1)));
        G1 = Ga.multiply(Fibonacci(b-1)).subtract(Gb.multiply(Fibonacci(a-1)));
        G1 = G1.divide(tmp);
        G0 = Gb.multiply(Fibonacci(a)).subtract(Ga.multiply(Fibonacci(b)));
        G0 = G0.divide(tmp);
    }
    
    public static void main( String[] args ) {
        InitFibonacci();
        scn = new Scanner( System.in );
        a = scn.nextInt();
        Ga = scn.nextBigInteger();
        b = scn.nextInt();
        Gb = scn.nextBigInteger();
        c = scn.nextInt();
        
        CalculateBoundaryCondition();
        System.out.println(G1.multiply(Fibonacci(c)).add(G0.multiply(Fibonacci(c-1))));
    }
}
