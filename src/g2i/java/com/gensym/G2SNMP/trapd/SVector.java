package com.gensym.G2SNMP.trapd;

import java.util.Vector;


/**
   This object will contain trap patterns.
*/
public class SVector {
    private Vector vector;

    /**
       @roseuid 366652460139
     */
    public SVector(int aCapacity) {
        vector = new Vector(aCapacity);
    }

    /**
       @roseuid 36665A6D00A3
     */
    public void addElement(Object obj) {
        // no equal objects in the vector!
        if (!vector.contains(obj)){
            vector.addElement(obj);
        }
    }

    /**
       @roseuid 366660E303C3
     */
    public void removeElement(Object obj) {
        vector.removeElement(obj);
    }

    /**
       @roseuid 366660F8017E
     */
    public boolean isContained(Object obj) {
        // may be used here 'cause it uses equals() which is overridden
        return vector.contains(obj);
    }

    /**
       @roseuid 366BBA7F0177
     */
    public void removeAllElements() {
        vector.removeAllElements();
    }
}
