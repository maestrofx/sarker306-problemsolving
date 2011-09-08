import java.util.Scanner;
import java.math.BigDecimal;

public class Main {
    public static void main(String args[]){
        BigDecimal bd, bdsum;
        int test;
		String str;
        Scanner scanner = new Scanner(System.in);

        while(scanner.hasNextInt()){
            test = scanner.nextInt();
            while( test-- >0 ) {
                bd = scanner.nextBigDecimal();
                bdsum = scanner.nextBigDecimal();
                bdsum = bdsum.add(bd);

				if(bdsum.compareTo(BigDecimal.ZERO) == 0 ) System.out.println("0.0");
				else{
					str = bdsum.stripTrailingZeros().toPlainString();
					if(str.indexOf('.') == -1) System.out.println(str + ".0");
					else System.out.println(str);
				}
            }
        }
    }
}
