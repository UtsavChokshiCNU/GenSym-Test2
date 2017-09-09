
package com.gensym.ntw.util;

import java.util.*;
import java.awt.*;
import java.awt.image.*;

public class ColorSheetProducer implements ImageProducer {

  private int width, height, alpha, red, blue, green;
  private boolean imageDone = false;
  private int[] pixels;
  private Vector consumers = new Vector ();
  private static Hashtable properties = new Hashtable ();
  private static ColorModel colorModel = new DirectColorModel (32,
							       0x00ff0000, // red
							       0x0000ff00, // green
							       0x000000ff, // blue
							       0xff000000);// alpha

  public ColorSheetProducer (int width, int height,
			     int alpha, int red, int green, int blue) {
    this.width = width;
    this.height = height;
    this.alpha = alpha;
    this.red = red;
    this.green = green;
    this.blue = blue;
  }

  @Override
  public void addConsumer(ImageConsumer ic) {
    if (imageDone)
      sendData (ic);
    else
      consumers.addElement (ic);
  }

  @Override
  public boolean isConsumer(ImageConsumer ic) {
    return consumers.contains (ic);
  }

  @Override
  public void removeConsumer(ImageConsumer ic) {
    consumers.removeElement (ic);
  }

  @Override
  public void startProduction (ImageConsumer ic) {
    if (ic != null)
      addConsumer (ic);
    pixels = new int[width*height];
    int colorPixel = (alpha<<24) + (red<<16) + (green<<8) + blue;
    for (int i=0; i<width*height; i++)
      pixels[i] = colorPixel;
    imageDone = true;
    for (int i=consumers.size()-1; i>=0; i--) {
      ic = (ImageConsumer)consumers.elementAt(i);
      sendData (ic);
      consumers.removeElement(ic);
    }
  }

  @Override
  public void requestTopDownLeftRightResend(ImageConsumer ic) {
    sendData (ic);
  }

  private void sendData (ImageConsumer ic) {
    ic.setColorModel (colorModel);
    ic.setDimensions (width, height);
    ic.setProperties (properties);
    ic.setHints (ImageConsumer.SINGLEPASS |
		 ImageConsumer.TOPDOWNLEFTRIGHT |
		 ImageConsumer.SINGLEFRAME);
    ic.setPixels (0, 0, width, height, colorModel, pixels, 0, width);
    ic.imageComplete(ImageConsumer.STATICIMAGEDONE);
  }

}
