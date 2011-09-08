/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package practice;

/**
 *
 * @author Avijit
 */
import java.sql.*;

public class MySQLConnect
{
   public static void main (String[] args)
   {
       Connection conn = null;

       try
       {
           String userName = "root";
           String password = "root";
           String url = "jdbc:mysql://localhost/test";
           Class.forName ("com.mysql.jdbc.Driver").newInstance ();
           conn = DriverManager.getConnection (url, userName, password);
           System.out.println ("Database connection established");
           Statement s = conn.createStatement ();
           int count;
           s.executeUpdate ("DROP TABLE IF EXISTS animal");
           s.executeUpdate (
                       "CREATE TABLE animal ("
                       + "id INT UNSIGNED NOT NULL AUTO_INCREMENT,"
                       + "PRIMARY KEY (id),"
                       + "name CHAR(40), category CHAR(40))");
           count = s.executeUpdate (
                       "INSERT INTO animal (name, category)"
                       + " VALUES"
                       + "('snake', 'reptile'),"
                       + "('frog', 'amphibian'),"
                       + "('tuna', 'fish'),"
                       + "('racoon', 'mammal')");
            System.out.println (count + " rows were inserted");
           PreparedStatement ps;
           ps = conn.prepareStatement (
                       "INSERT INTO animal (name, category) VALUES(?,?)");
           ps.setString (1, "crow");
           ps.setString (2, "bird");
           count = ps.executeUpdate ();
           ps.close ();
           //s.close ();
           System.out.println (count + " rows were inserted");
           s.executeQuery ("SELECT id, name, category FROM animal");
           ResultSet rs = s.getResultSet ();
           count = 0;
           while (rs.next ())
           {
               int idVal = rs.getInt ("id");
               String nameVal = rs.getString ("name");
               String catVal = rs.getString ("category");
               System.out.println (
                       "id = " + idVal
                       + ", name = " + nameVal
                       + ", category = " + catVal);
               ++count;
           }
           rs.close ();
           System.out.println (count + " rows were retrieved");
           s.execute("DROP TABLE animal");
           System.out.println("Database animal successfully deleted");
           s.close();
       }
       catch (Exception e)
       {
           System.err.println ("Cannot connect to database server");
       }
       finally
       {
           if (conn != null)
           {
               try
               {
                   conn.close ();
                   System.out.println ("Database connection terminated");
               }
               catch (Exception e) { /* ignore close errors */ }
           }
       }
   }
}
