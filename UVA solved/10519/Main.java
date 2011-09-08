import java.math.BigInteger;
import java.util.Scanner;

public class Main {
    public static void main(String args[]){
        BigInteger num, tmp;
        Scanner scanner = new Scanner(System.in);

        while(scanner.hasNextBigInteger()){
            num = scanner.nextBigInteger();
            tmp = new BigInteger(num.toString());
            if(num.equals(BigInteger.ZERO)) System.out.println("1");
            else{
				num = num.subtract(BigInteger.ONE);
				tmp = tmp.multiply(num);
				tmp = tmp.add(BigInteger.valueOf(2));
				System.out.println(tmp);
			}
        }

        scanner.close();
    }
}
