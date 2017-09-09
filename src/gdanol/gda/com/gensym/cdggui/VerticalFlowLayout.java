

/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	VerticalFlowLayout.java
 *
 *   Modifications:
 *
 *
 */
package com.gensym.cdggui;

import java.awt.*;
import java.io.Serializable;

public class VerticalFlowLayout extends FlowLayout implements Serializable {

    static int spacer = 1;

    public VerticalFlowLayout() {
        this(0, spacer, spacer, true, false);
    }

    public VerticalFlowLayout(boolean flag, boolean flag1) {
        this(0, spacer, spacer, flag, flag1);
    }

    public VerticalFlowLayout(int i) {
        this(i, spacer, spacer, true, false);
    }

    public VerticalFlowLayout(int i, boolean flag, boolean flag1) {
        this(i, spacer, spacer, flag, flag1);
    }

    public VerticalFlowLayout(int i, int j, int k, boolean flag,
                              boolean flag1) {
        setAlignment(i);
        hgap = j;
        vgap = k;
        hfill = flag;
        vfill = flag1;
    }

    public Dimension preferredLayoutSize(Container container) {
        Dimension dimension = new Dimension(0, 0);
        for (int i = 0; i < container.getComponentCount(); i++) {
            Component component = container.getComponent(i);
            if (!component.isVisible())
                continue;
            Dimension dimension1 = component.getPreferredSize();
            dimension.width = Math.max(dimension.width, dimension1.width);
            if (i > 0)
                dimension.height += hgap;
            dimension.height += dimension1.height;
        }

        Insets insets = container.getInsets();
        dimension.width += insets.left + insets.right + hgap * 2;
        dimension.height += insets.top + insets.bottom + vgap * 2;
        return dimension;
    }

    public Dimension minimumLayoutSize(Container container) {
        Dimension dimension = new Dimension(0, 0);
        for (int i = 0; i < container.getComponentCount(); i++) {
            Component component = container.getComponent(i);
            if (!component.isVisible())
                continue;
            Dimension dimension1 = component.getMinimumSize();
            dimension.width = Math.max(dimension.width, dimension1.width);
            if (i > 0)
                dimension.height += vgap;
            dimension.height += dimension1.height;
        }

        Insets insets = container.getInsets();
        dimension.width += insets.left + insets.right + hgap * 2;
        dimension.height += insets.top + insets.bottom + vgap * 2;
        return dimension;
    }

    public void setVerticalFill(boolean flag) {
        vfill = flag;
    }

    public boolean getVerticalFill() {
        return vfill;
    }

    public void setHorizontalFill(boolean flag) {
        hfill = flag;
    }

    public boolean getHorizontalFill() {
        return hfill;
    }

    private void placethem(Container container, int i, int j, int k,
                           int l, int i1, int j1) {
        int k1 = getAlignment();
        if (k1 == 1)
            j += l / 2;
        if (k1 == 2)
            j += l;
        for (int l1 = i1; l1 < j1; l1++) {
            Component component = container.getComponent(l1);
            Dimension dimension = component.getSize();
            if (component.isVisible()) {
                int i2 = i + (k - dimension.width) / 2;
                component.setLocation(i2, j);
                j += vgap + dimension.height;
            }
        }

    }

    public void layoutContainer(Container container) {
        Insets insets = container.getInsets();
        int i = container.getSize().height -
                (insets.top + insets.bottom + vgap * 2);
        int j = container.getSize().width -
                (insets.left + insets.right + hgap * 2);
        int k = container.getComponentCount();
        int l = insets.left + hgap;
        int i1 = 0;
        int j1 = 0;
        int k1 = 0;
        for (int l1 = 0; l1 < k; l1++) {
            Component component = container.getComponent(l1);
            if (!component.isVisible())
                continue;
            Dimension dimension = component.getPreferredSize();
            if (vfill && l1 == k - 1)
                dimension.height = Math.max(i - i1,
                                            component.getPreferredSize().height);
            if (hfill) {
                component.setSize(j, dimension.height);
                dimension.width = j;
            } else {
                component.setSize(dimension.width, dimension.height);
            }
            if (i1 + dimension.height > i) {
                placethem(container, l, insets.top + vgap, j1, i - i1,
                          k1, l1);
                i1 = dimension.height;
                l += hgap + j1;
                j1 = dimension.width;
                k1 = l1;
                continue;
            }
            if (i1 > 0)
                i1 += vgap;
            i1 += dimension.height;
            j1 = Math.max(j1, dimension.width);
        }

        placethem(container, l, insets.top + vgap, j1, i - i1, k1, k);
    }

    public static final int TOP = 0;
    public static final int MIDDLE = 1;
    public static final int BOTTOM = 2;
    int hgap;
    int vgap;
    boolean hfill;
    boolean vfill;
}
