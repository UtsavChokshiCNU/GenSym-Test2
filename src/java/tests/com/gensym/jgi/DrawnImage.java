package com.gensym.jgi;

import java.awt.*;
import java.awt.image.ImageObserver;

public class DrawnImage {
    private final Image img;
    private final int x;
    private final int y;
    private final ImageObserver observer;

    public DrawnImage(Image img, int x, int y, ImageObserver observer) {
        this.img = img;
        this.x = x;
        this.y = y;
        this.observer = observer;
    }

    public Image getImg() {
        return img;
    }

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }

    public ImageObserver getObserver() {
        return observer;
    }
}
