package com.gensym.gda.dialogs.other;

import java.awt.GridBagLayout;
import java.awt.GridBagConstraints;
import java.awt.Insets;

import java.util.Vector;
import java.util.MissingResourceException;

import javax.swing.JDialog;
import javax.swing.JPanel;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JTextField;
import javax.swing.BorderFactory;

import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.util.ScientificDecimalFormat;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;
import com.gensym.message.MessageKey;
import com.gensym.message.Resource;
import com.gensym.core.UiApplication;

import com.gensym.classes.modules.gdluisup.*;

/**

*/
public class gdlPathTable extends JDialog implements com.gensym.classes.modules.gdluisup.G2_GdlPathItemEventListener {

    /**
        Constructor without parameters. Use static method
        {@link com.gensym.core.UiApplication#getCurrentFrame()}
        to get java.awt.Frame instance.
    */
    public gdlPathTable () {
        this(UiApplication.getCurrentFrame(), new Vector(), new Vector());
    }

    /**
        Main constructor.
        @param attrNames vector of path attribute names to display
        @param initVals vector of path attribute initial values
    */
    public gdlPathTable(java.awt.Frame frame, Vector attrNames, Vector initVals) {
        super(frame);
        
        JComponent contentPane = (JComponent)getContentPane();
        contentPane.setBorder(BorderFactory.createCompoundBorder(
            BorderFactory.createEtchedBorder(),
            BorderFactory.createEmptyBorder(5, 5, 5, 5)));
        
        layout = new GridBagLayout();
        constraints = new GridBagConstraints();
        contentPane.setLayout(layout);
        
        displays = new Vector();
        long initSize = initVals.size();
        
        for (int i=0; i<attrNames.size();i++){
            JLabel label = new JLabel(localize(attrNames.elementAt(i).toString().toLowerCase()));
            JTextField display = new JTextField();
            display.setEditable(false);
            displays.add(display);
            
            constraints.gridy = i;
            constraints.anchor = GridBagConstraints.EAST;
            constraints.insets = new Insets(3,3,3,3);
            
            constraints.gridx = 0;
            constraints.weightx = 0.0;
            constraints.weighty = 0.0;
            constraints.fill = GridBagConstraints.NONE;
            layout.setConstraints(label, constraints);
            contentPane.add(label);
            
            constraints.gridx = 1;
            
            constraints.weightx = 1.0;
            constraints.weighty = 1.0;
            constraints.fill = GridBagConstraints.BOTH;
            layout.setConstraints(display, constraints);
            contentPane.add(display);
        }
        
        pathDataUpdateFromVector(initVals);
        
        setLocationRelativeTo(frame);
    }
    
    /**
    Sets the event manager and add the table to its listener list
    */
    public void setManager(GdlPathItemEventManager aManager){
        try{
            manager = aManager;
            aManager.addG2_GdlPathItemEventListener(this);
        }catch(G2AccessException e){
            Trace.send(Trace.ALL_LEVELS, traceKey, i18n, e.getMessage());            
        }
    }
    
    public  void pathDataUpdate(G2_GdlPathItemEvent e) throws G2AccessException {
        pathDataUpdateFromVector(e.getGdlPathDataValues());
    }
    
    public  void terminatePathItemEventListener(G2_GdlPathItemEvent arg1) throws G2AccessException {
        dispose();
    };
    
    private void pathDataUpdateFromVector(Vector values){
        int maxPrefSize = 0;
        int prefSize;
        JTextField display = null;
        for (int i=0; i<Math.min(values.size(),displays.size());i++){
            display = (JTextField) displays.elementAt(i);
            
            //*** To work around bug with selection being white after update the text
            int selStart = display.getSelectionStart();
            int selEnd = display.getSelectionEnd();
            //***
            
            display.setText(getValueString(values.elementAt(i)));
            
            //*** To work out bug with selection being white after update the text
            display.select(selStart, selEnd);
            //***
            
            prefSize = display.getPreferredSize().width;
            if (prefSize > maxPrefSize)
                maxPrefSize = prefSize;
        }
        if (maxPrefSize > display.getSize().width)
            pack();
    }
    
    private final static String getValueString(Object newVal){
        if (newVal instanceof Number)
            return formatter.format(((Number)newVal).doubleValue());
        if (newVal instanceof Symbol)
            return newVal.toString().toLowerCase();
        return newVal.toString();
    }
    
    /**Localizes text from com.gensym.gda.dialogs.blocks.Messages
        resource file. If the value for the key is not found then itreturns key itself.
    */
    protected static String localize(String text) {
        try {
            return i18n.getString(text);
        } catch (MissingResourceException e) {
            return text;
        }
    }

    
    protected GridBagConstraints constraints;
    protected GridBagLayout layout;
    protected GdlPathItemEventManager manager;

    private static Resource i18n = Resource.getBundle("com.gensym.gda.dialogs.other.Messages");
    static MessageKey traceKey = Trace.registerMessageKey("com.gensym.gda", gdlPathTable.class);

    private Vector displays;
    
    private static final ScientificDecimalFormat formatter = new ScientificDecimalFormat();

}