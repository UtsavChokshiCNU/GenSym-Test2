package com.gensym.beaneditor;

import java.awt.CheckboxMenuItem;
import java.awt.event.ItemListener;

public class PageMenuItem extends CheckboxMenuItem
{
    PageNode node;

    PageMenuItem(PageNode node, ItemListener listener)
    {
        super(node.name);
        this.addItemListener(listener);
        this.node = node;
        node.pageMenuItem = this;
    }
}
