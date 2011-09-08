/**
 * @(#)Main.java
 *
 *
 * @author
 * @version 1.00 2011/5/8
 */

import java.math.BigInteger;
import java.util.Scanner;

class Prob153{
	BigInteger[] factorial;
	int[] frequency;

	Prob153(int n) {
		int i;

		factorial = new BigInteger[n];
		frequency = new int[26];
		factorial[0] = factorial[1] = BigInteger.ONE;
		for ( i = 2 ; i < factorial.length ; i++ ) {
			factorial[i] = factorial[i - 1].multiply( BigInteger.valueOf( i ) );
		}
	}

	BigInteger permNumber(){
		int i, n = 0;
		BigInteger x = BigInteger.ONE;

		for( i = 0 ; i < 26 ; i++ ){
			if(frequency[i] > 1) x = x.multiply( factorial[frequency[i]] );
			n += frequency[i];
		}

		return factorial[n].divide(x);
	}

	BigInteger solve(String str){
		int i, j, len = str.length();
		BigInteger y = BigInteger.ONE;

		for( i = 0 ; i < 26 ; i++ ) frequency[i] = 0;
		for( i = 0 ; i < len ; i++ ) frequency[ str.charAt(i) - 'a']++;

		for(i = 0 ; i < len ; i++ ){
	        for(j=0;j<26;j++){
	            if( frequency[j] > 0 ){
	                frequency[j]--;
	                if(str.charAt(i) == j + 'a') break;

	                else{
	                    y = y.add(permNumber());
	                    frequency[j]++;
	                }
	            }
	        }
    	}

    	return y;
	}
}

public class Main {
    public static void main(String args[]) {
    	int i;
    	Prob153 prob153 = new Prob153(32);
    	Scanner scanner = new Scanner ( System.in );

    	while( scanner.hasNextLine() ){
    		String str = scanner.nextLine();
    		if(str.length() == 1 && str.charAt(0) == '#' ) break;
    		System.out.printf("%#10s\n", prob153.solve( str ).toString());
    	}

    	scanner.close();
    }
}
