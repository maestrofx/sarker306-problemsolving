/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package practice;
import java.io.*;

/**
 *
 * @author Avijit
 */

class Gen<T>{
	T object;
	Gen(T ob){
		this.object=ob;
	}

	T getOb(){
		return object;
	}
	void showType(){
		System.out.println("Type of the object in the class : "
                +object.getClass().toString());
		System.out.println("Type of this class : "
                +this.getClass().toString());
	}
}

public class GenericDemo{
	public static void main(String args[]){
		Gen<Integer> mygen = new Gen<Integer>(new Integer(89));
		mygen.showType();
		System.out.println(mygen.getOb());

		Gen<String> stringen = new Gen<String>(new String("Eishob gorugadhara!"));
		stringen.showType();
		System.out.println(stringen.getOb());

		System.out.println("I am fine!");
	}
}
