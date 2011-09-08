package practice;

import java.util.Scanner;
import java.math.BigDecimal;

public class BigDecimalDemo {
    public static void main(String args[]){
        BigDecimal bd, bdsum;
        int test;
        Scanner scanner= new Scanner(System.in);

        while(scanner.hasNextInt()){
            test=scanner.nextInt();
            for( ; test>0 ; test--) {
                bd = BigDecimal.ZERO;
                bdsum=BigDecimal.ZERO;

                while( scanner.hasNextBigDecimal() ){
                    bd=scanner.nextBigDecimal();
                    if(bd.compareTo(BigDecimal.ZERO)==0 ) break;
                    bdsum = bdsum.add(bd);
                }

                if(bdsum.compareTo(BigDecimal.ZERO)==0) System.out.println("0");
                else System.out.println(bdsum.stripTrailingZeros().toPlainString());
            }
        }
    }
}
