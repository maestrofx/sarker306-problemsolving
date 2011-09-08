/**
 * @(#)Main.java
 *
 *
 * @author
 * @version 1.00 2011/5/8
 */

import java.math.BigInteger;
import java.util.Scanner;
import java.util.StringTokenizer;

class PalindromPermutation{
	BigInteger[] factorial;
	int[] frequency;

	PalindromPermutation(int n) {
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

	void solve(String str, BigInteger x){
		int i, j, len = str.length();
		char odd = 0, word[];
		BigInteger y = BigInteger.ONE;

		for( i = 0 ; i < 26 ; i++ ) frequency[i] = 0;
		for( i = 0 ; i < len ; i++ ) frequency[ str.charAt(i) - 'a']++;
		len >>= 1;
		for( i = 0 ; i < 26 ; i++ ){
			if((frequency[i] & 1) != 0){
				if( odd == 0) odd = (char) (i + 'a');
				else break;
			}

			frequency[i] >>= 1;
		}

		if( i < 26 || permNumber().compareTo( x ) < 0){
			System.out.println("XXX");
			return;
		}
		word = new char[len * 2 + 1];

		for(i = 0 ; i < len ; i++ ){
	        for(j = 0 ; j < 26 ; j++ ){
	            if( frequency[j] > 0 ){
	            	word[i] = (char)(j + 'a');
	                frequency[j]--;
	                y = permNumber();
	                if( y.compareTo( x ) >= 0 ){
	                	System.out.print((char) word[i]);
	                	break;
	                }
	                else{
	                    x = x.subtract(y);
	                    frequency[j]++;
	                }
	            }
	        }
    	}

    	if(odd != 0) System.out.print(odd);
    	while( i > 0 ) System.out.print(word[--i]);
    	System.out.println();
	}
}

public class Main {
    public static void main(String args[]) {
    	int i, test;
    	BigInteger perm;
    	String line, str;
    	PalindromPermutation palPerm = new PalindromPermutation(32);
    	Scanner scanner = new Scanner ( System.in );

		while(scanner.hasNextInt()){
			test = scanner.nextInt();
			line = scanner.nextLine();
			line = new String("");

			for( i = 1 ; i <= test ; ){
				line = scanner.nextLine();
	    		StringTokenizer strtok = new StringTokenizer(line, " ");
	    		if(strtok.hasMoreTokens() == false) continue;
	    		str = strtok.nextToken();
	    		if(strtok.hasMoreTokens() == false) continue;
    			perm = new BigInteger( strtok.nextToken() );
    			System.out.print("Case " + i + ": ");
    			palPerm.solve( str , perm) ;
    			i++;
			}
		}

    	scanner.close();
    }
}
