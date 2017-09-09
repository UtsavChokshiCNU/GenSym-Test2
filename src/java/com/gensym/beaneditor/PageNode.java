package com.gensym.beaneditor;

public class PageNode extends Object
{
    String name;
    String location;
    BeanCanvas canvas;
    PageNode next;
    PageNode previous;
    PageMenuItem pageMenuItem;
    static int pageCount = 1;

    PageNode(String name, BeanCanvas canvas)
    {
        this.name = name;
        this.canvas = canvas;
        location = "TAB_PAGE_"+(pageCount++);
    }

    void reset()
    {
        name = null;
        location = null;
        canvas = null;
        next = null;
        previous = null;
        pageMenuItem = null;
    }

}








