/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package practice;
import java.util.Random;
import java.util.concurrent.Executors;
import java.util.concurrent.ExecutorService;

/**
 *
 * @author avijit_2
 */

class MyTask implements Runnable{
    long sleeptime;
    String t;

    MyTask(String name){
        t=new String(name);
    }
    
    public void run() {
        System.out.println(Thread.currentThread().toString()
                       +" starts");
        try{
           for(int i=10;i>0;i--){
               sleeptime=new Random().nextInt(1000);
               System.out.println(Thread.currentThread().toString()
                       +" is going to sleep for "+sleeptime+" ms");
               Thread.sleep( sleeptime);
           }
        } catch( InterruptedException interrupted){
           System.err.println("Thread "+t
                   +" isInturrupted");
        }

        System.out.println("Thread "+t+" exits");
    }
}

public class MultithreadDemo {
   public static void main(String args[]){
       /*Thread thread1= new Thread(new MyTask("One"));
       Thread thread2= new Thread(new MyTask("two"));

       thread1.start();
       thread2.start();*/
       ExecutorService ThreadExecutor=Executors.newCachedThreadPool();

       ThreadExecutor.execute(new MyTask("One"));
       ThreadExecutor.execute(new MyTask("Two"));

       ThreadExecutor.shutdown();
   }
}
