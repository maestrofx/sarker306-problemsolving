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
           String password = "admin";
           String url = "jdbc:mysql://localhost/test";
           Class.forName ("com.mysql.jdbc.Driver").newInstance ();
           conn = DriverManager.getConnection (url, userName, password);
           System.out.println ("Database connection established");
           Statement stmnt = conn.createStatement ();
           int count;
           stmnt.executeUpdate ("DROP TABLE IF EXISTS animal");
           stmnt.executeUpdate (
                       "CREATE TABLE animal ("
                       + "id INT UNSIGNED NOT NULL AUTO_INCREMENT,"
                       + "PRIMARY KEY (id),"
                       + "name CHAR(40), category CHAR(40))");
           count = stmnt.executeUpdate (
                       "INSERT INTO animal (name, category)"
                       + " VALUES"
                       + "('snake', 'reptile'),"
                       + "('frog', 'amphibian'),"
                       + "('tuna', 'fish'),"
                       + "('racoon', 'mammal')");
            System.out.println (count + " rows were inserted");
           PreparedStatement preparedStmt;
           preparedStmt = conn.prepareStatement (
                       "INSERT INTO animal (name, category) VALUES(?,?)");
           preparedStmt.setString (1, "crow");
           preparedStmt.setString (2, "bird");
           count = preparedStmt.executeUpdate ();
           preparedStmt.close ();
           //s.close ();
           System.out.println (count + " rows were inserted");
           stmnt.executeQuery ("SELECT id, name, category FROM animal");
           ResultSet resultSet = stmnt.getResultSet ();
           count = 0;
           while (resultSet.next ())
           {
               int idVal = resultSet.getInt ("id");
               String nameVal = resultSet.getString ("name");
               String catVal = resultSet.getString ("category");
               System.out.println (
                       "id = " + idVal
                       + ", name = " + nameVal
                       + ", category = " + catVal);
               ++count;
           }
           resultSet.close ();
           System.out.println (count + " rows were retrieved");
           stmnt.execute("DROP TABLE animal");
           System.out.println("Database animal successfully deleted");
           stmnt.close();
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
