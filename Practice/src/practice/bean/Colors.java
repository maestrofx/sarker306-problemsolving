/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package practice.bean;

import java.applet.Applet;
import java.awt.Canvas;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.event.*;
import java.beans.*;
import java.io.Serializable;

/**
 *
 * @author Avijit
 */
public class Colors extends Applet implements Serializable {

    public static final String PROP_SAMPLE_PROPERTY = "sampleProperty";
    public static final String PROP_RECTANGULAR = "rectangular";
    private String sampleProperty;
    private PropertyChangeSupport propertySupport;
    transient private Color color;
    private boolean rectangular;

    public Colors() {
        propertySupport = new PropertyChangeSupport(this);
        addMouseListener( new MouseAdapter(){
            public void mousePressed(MouseEvent me){
                change();
            }
        });

        rectangular = false;
        setSize(200, 100);
        change();
    }

    public void change() {
        color = randomColor();
        repaint();
    }

    private Color randomColor() {
        return new Color ( (int) (255 * Math.random()), (int) (255 * Math.random()), (int) (255 * Math.random()));
    }

    public void paint(Graphics g) {
        Dimension dim = getSize();
        int height = dim.height;
        int width = dim.width;
        g.setColor(color);

        if ( rectangular ) g.fillRect(0, 0, width - 1, height - 1);
        else g.fillOval(0, 0, width-1, height-1);
    }

    public boolean getRectangular() {
        return rectangular;
    }

    public void setRectangular(boolean flag) {
        boolean oldValue = this.rectangular;
        this.rectangular = flag;
        propertySupport.firePropertyChange(PROP_RECTANGULAR, oldValue, rectangular);
        repaint();
    }

    public String getSampleProperty() {
        return sampleProperty;
    }

    public void setSampleProperty(String value) {
        String oldValue = sampleProperty;
        sampleProperty = value;
        propertySupport.firePropertyChange(PROP_SAMPLE_PROPERTY, oldValue, sampleProperty);
    }

    public void addPropertyChangeListener(PropertyChangeListener listener) {
        propertySupport.addPropertyChangeListener(listener);
    }

    public void removePropertyChangeListener(PropertyChangeListener listener) {
        propertySupport.removePropertyChangeListener(listener);
    }
}
