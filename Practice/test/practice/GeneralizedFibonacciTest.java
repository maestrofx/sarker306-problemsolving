/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package practice;

import java.math.BigInteger;
import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import static org.junit.Assert.*;

/**
 *
 * @author Avijit
 */
public class GeneralizedFibonacciTest {
    
    public GeneralizedFibonacciTest() {
    }

    @BeforeClass
    public static void setUpClass() throws Exception {
    }

    @AfterClass
    public static void tearDownClass() throws Exception {
    }
    
    @Before
    public void setUp() {
    }
    
    @After
    public void tearDown() {
    }

    /**
     * Test of Fibonacci method, of class GeneralizedFibonacci.
     */
    @Test
    public void testFibonacci() {
        java.math.BigInteger[] output = new java.math.BigInteger[5];
        int[] input = new int[5];
        
        input[0] = 3; input[1] = 6; input[2] = 0; input[3] = -4; input[4] = -3;
        output[0] = BigInteger.valueOf(2);
        output[1] = BigInteger.valueOf(8);
        output[2] = BigInteger.valueOf(0);
        output[3] = BigInteger.valueOf(-3);
        output[4] = BigInteger.valueOf(2);
        System.out.println("Fibonacci test");
        String[] args = null;
        GeneralizedFibonacci.InitFibonacci();
        for ( int i = 0 ; i < 5 ; i++ )
            assertEquals(output[i], GeneralizedFibonacci.Fibonacci(input[i]));
    }
}
