package gensym.charts.dialogs.tables;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

/**
 * Color button
 */
public class TableColorButton extends JButton implements Icon, ActionListener {
    /**
     * Generated Serial version UID
     */
    private static final long serialVersionUID = 2284511396186403216L;
    /**
     * Icon color
     */
    private Color color;
    /**
     * Width of the icon
     */
    private int iconWidth;
    /**
     * Heigth of the icon
     */
    private int iconHeigth;

    /**
     * Constructor
     * @param color initial color
     * @param iconw icon width
     * @param iconh icon height
     */
    public TableColorButton(Color color, int iconw, int iconh) {
        this.color = color;
        this.iconWidth = iconw;
        this.iconHeigth = iconh;
        setIcon(this);
        addActionListener(this);
    }

    /**
     * Gets icon color
     * @return color
     */
    public Color getColor() {
        return color;
    }

    /**
     * Sets icon color
     * @param color new color
     */
    public void setColor(Color color) {
        this.color = color;
        repaint();
    }

    /**
     * {@inheritDoc}
     */
    public void actionPerformed(ActionEvent e) {
        Color res = JColorChooser.showDialog(this, "Change color", color);
        if (res != null) {
            setColor(res);
        }
    }

    /**
     * @see interface Icon
     * {@inheritDoc}
     */
    public int getIconWidth() {
        return iconWidth;
    }

    /**
     * @see interface Icon
     * {@inheritDoc}
     */
    public int getIconHeight() {
        return iconHeigth;
    }

    /**
     * @see interface Icon
     * {@inheritDoc}
     */
    public void paintIcon(Component c, Graphics g, int x, int y) {
        Color old = g.getColor();
        g.setColor(color);
        g.fillRect(x, y, iconWidth, iconHeigth);
        g.setColor(old);
    }
}
