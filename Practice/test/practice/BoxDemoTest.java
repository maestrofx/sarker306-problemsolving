/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package practice;

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
public class BoxDemoTest {
    
    public BoxDemoTest() {
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
     * Test of main method, of class IOpractice.
     */
    @Test
    public void testMain() throws Exception {
        System.out.println("Box class");
        WeightedBox b1=new WeightedBox(2.9, 3.5, 5.9, 306.603);
        assert(5.119863070885864 == b1.density());
        System.out.println("main");
        String[] args = new String[3];
        BoxDemo.main(args);
        // TODO review the generated test code and remove the default call to fail.
        //fail("The test case is a prototype.");
    }
}
