package gensym.charts.tooltips;

import javax.swing.JToolTip;

/**
 * MultiLine ToolTip 
 */
public class MultiLineToolTip extends JToolTip {
    /**
     * Generated version UID
     */
    private static final long serialVersionUID = -6123900248218339910L;

    /**
     * Constructor
     */
    public MultiLineToolTip() {
        setUI(new MultiLineToolTipUI());
    }
}
