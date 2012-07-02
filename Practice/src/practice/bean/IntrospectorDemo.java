/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package practice.bean;
import java.awt.*;
import java.beans.*;
/**
 *
 * @author Avijit
 */
public class IntrospectorDemo {
    public static void main( String[] args) {
        try{
            Class cls = Class.forName("Colors");
            BeanInfo beanInfo = Introspector.getBeanInfo(cls);
            System.out.println("Properties :");
            PropertyDescriptor propertyDescriptor[] = beanInfo.getPropertyDescriptors();

            for ( int i = 0 ; i < propertyDescriptor.length ; i++ )
                System.out.println("\t " + propertyDescriptor[i].getName());
        }
        catch ( Exception e ) {
            System.err.println("Exception caught :" + e.getMessage());
        }
    }
}
