/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package practice;
import java.net.*;
import javax.net.*;
import java.io.*;

/**
 *
 * @author avijit_2
 */

public class NetworkDemo {
    public static void main(String args[]){
        //InetAddress......
        try{
            InetAddress Address=InetAddress.getLocalHost();
            System.out.println(Address.getHostName()+' '
                    +Address.getHostAddress());
            Address=InetAddress.getByName("Avijit-PC");
            System.out.println(Address.getHostName()+' '
                    +Address.getHostAddress());
            InetAddress AllAddresses[]=InetAddress.getAllByName("www.facebook.com");
            for(int i=0; i<AllAddresses.length; i++)
                System.out.println(AllAddresses[i]);
        } catch (UnknownHostException uhe){
            System.err.println("No Host Found!");
        }

        // Socket for Client.....
        final int PORT=1235;

        try{
            ServerSocket serversocket=new ServerSocket(PORT);
            Socket socket=new Socket(InetAddress.getLocalHost(), PORT);
            System.out.println(socket.getLocalAddress().toString()
                    +' '+socket.getPort()+' '+socket.getLocalPort());

            InputStream socketinput=socket.getInputStream();
            OutputStream socketoutput=socket.getOutputStream();

          /*  String string="hmm";
            socketoutput.write(string.getBytes());

            int ch;
            while((ch = socketinput.read())!=-1){
                System.out.print((char)ch);
            } */
        } catch (UnknownHostException uhe){
            System.err.println("Baaler Host Found!");
        } catch (IOException ioe){
            System.err.println("IOException Found!");
        }

        // URL demo...
    }
}
