/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package practice;

/**
 *
 * @author avijit_2
 */

class Box{
    private double width, height, length;

    Box(double length, double width, double height){
        this.length=length;
        this.width=width;
        this.height=height;
    }

    Box(Box ob){
        this.length=ob.length;
        this.width=ob.width;
        this.height=ob.height;
    }

    double volume(){
        return length*width*height;
    }

    public String toString(){
        String out="Length : "+this.length+" Width : "+this.width
                +" Height : "+this.height;
        return out;
    }
}

class WeightedBox extends Box{
    double weight;

    WeightedBox(double length, double width, double height, double weight){
        super(length, width, height);
        this.weight=weight;
    }

    WeightedBox(WeightedBox ob){
        super(ob);
        this.weight=ob.weight;
    }

    double density(){
        return this.weight/this.volume();
    }
    public String toString(){
        String out=super.toString()+" Weight : "+this.weight;
        return out;
    }
}

class BoxDemo {
    public static void main(String args[]){
        WeightedBox b1=new WeightedBox(2.9, 3.5, 5.9, 306.603);
        WeightedBox b2 = new WeightedBox(b1);

        // TODO add something?
        System.out.println("Density of b1 is "+b1.density());
        System.out.println(b1.toString());
        System.out.println("Density of b2 is "+b2.density());
        System.out.println(b1.toString());
        System.out.println( b1.getClass().getName());
        System.out.println("Exiting!");
    }
}
