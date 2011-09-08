/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package practice;

import java.math.BigInteger;
import java.util.Scanner;

/**
 *
 * @author Avijit
 */
public class BigIntegerDemo {
    public static void main(String args[]){
        BigInteger sum = BigInteger.ZERO, num, tmp;
        Scanner scanner = new Scanner(System.in);

        while(scanner.hasNextBigInteger()){
            num = scanner.nextBigInteger();
            tmp = new BigInteger(num.toString());
            if(num.equals(BigInteger.ZERO)) break;
            sum = sum.add(num);
            num = num.subtract(BigInteger.ONE);
            tmp = tmp.multiply(num);
            tmp = tmp.add(BigInteger.valueOf(2));
            System.out.println(tmp);
        }

        System.out.println(sum);
        scanner.close();
    }
}
