package com.gensym.uiutil;

import java.awt.Canvas;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.Label;
import java.awt.Panel;
import java.awt.Point;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.TextEvent;
import java.awt.event.TextListener;
import com.gensym.message.Resource;

public class ColorSpectrumPanel extends Panel implements MouseListener {

  private static Resource i18n = 
          Resource.getBundle("com.gensym.uiutil.ColorEditorResources");

  private int pWidth = 1;
  private int pHeight = 1;
  private Color selectedColor;
  private ColorPreviewCanvas sample;
  private static Graphics g;
  private Graphics offGraphics;
  private Image offImage;
  private static Image im;
  private ColorSpectrumCanvas selec;
  private Dimension offDimension;
  private Point point = null;
  private String[] rgbStrings;
  private Label[] rgbLbls;
  private IntTextField rgbFields[] = new IntTextField[6];
  private IntTextField redTextField;
  private IntTextField greenTextField;
  private IntTextField blueTextField;
  private IntTextField hueTextField;
  private IntTextField satTextField;
  private IntTextField brightnessTextField;
  private int redValue;
  private int greenValue;
  private int blueValue;
  private int hueValue;
  private int satValue;
  private int brightnessValue = 128;
  private float[] hsbVals = new float[3];

  public ColorSpectrumPanel(ColorPreviewCanvas preview) {
    super();
    setLayout(null);
    this.addMouseListener(this);
    selec = new ColorSpectrumCanvas(20);
    sample = preview;
    add(selec);
    selec.setBounds(268, 0, 20, 256);
    rgbStrings = new String[] {i18n.getString("Red"), 
			       i18n.getString("Green"), 
			       i18n.getString("Blue"), 
			       i18n.getString("Hue"), 		
			       i18n.getString("Sat"), 
			       i18n.getString("Lum")};
    rgbLbls = new Label[6];
    int x = 315;
    int y = 0;
    for (int i = 0; i<6; i++) {
      rgbLbls[i] = new Label(rgbStrings[i], Label.LEFT);
      add(rgbLbls[i]);
      rgbLbls[i].setBounds(x,y,60,15);
      y += 40;
    }

    y = 15;
    redTextField = new IntTextField(1);
    add(redTextField);
    redTextField.setBounds(x,y,60,20);
    redTextField.addTextListener(new TextListener() {
      @Override
      public void textValueChanged(TextEvent e) {
	redValue = redTextField.getValue();
	changeColorFromRGB();
      }
    });

    y += 40;
    greenTextField = new IntTextField(1);
    add(greenTextField);
    greenTextField.setBounds(x,y,60,20);
    greenTextField.addTextListener(new TextListener() {
      @Override
      public void textValueChanged(TextEvent e) {
	greenValue = greenTextField.getValue();
	changeColorFromRGB();
      }
    });

    y += 40;
    blueTextField = new IntTextField(1);
    add(blueTextField);
    blueTextField.setBounds(x,y,60,20);
    blueTextField.addTextListener(new TextListener() {
      @Override
      public void textValueChanged(TextEvent e) {
	blueValue = blueTextField.getValue();
	changeColorFromRGB();
      }
    });

    y += 40;
    hueTextField = new IntTextField(1);
    add(hueTextField);
    hueTextField.setBounds(x,y,60,20);
    hueTextField.addTextListener(new TextListener() {
      @Override
      public void textValueChanged(TextEvent e) {
	hueValue = hueTextField.getValue();
	changeColorFromHSB();
      }
    });

    y += 40;
    satTextField = new IntTextField(1);
    add(satTextField);
    satTextField.setBounds(x,y,60,20);
    satTextField.addTextListener(new TextListener() {
      @Override
      public void textValueChanged(TextEvent e) {
	satValue = satTextField.getValue();
	changeColorFromHSB();
      }
    });

    y += 40;
    brightnessTextField = new IntTextField(1);
    add(brightnessTextField);
    brightnessTextField.setBounds(x,y,60,20);
    brightnessTextField.addTextListener(new TextListener() {
      @Override
      public void textValueChanged(TextEvent e) {
	brightnessValue = brightnessTextField.getValue();
	changeColorFromHSB();
      }
    });

    redTextField.setText("" + 0);
    greenTextField.setText("" + 0);
    blueTextField.setText("" + 0);

    brightnessTextField.setText("" + brightnessValue);
    selec.addEventSource(brightnessTextField);
    selec.setBrightness(brightnessValue);
    setSize(375,256*pHeight);
  }

  public void init() {
    //im = createImage(288,256*pHeight);
  }

  public Color getSelectedColor(){
    return selectedColor;
  }
  
  @Override
  public void paint(Graphics gr) {
    int xPos = 0;
    int yPos = 0;

    if (g == null) {
      if (im == null) {
	im = createImage(308,256*pHeight);
      }
			
      g = im.getGraphics();
      for (int i=0; i<256; i++) {
	xPos = i*pWidth;
	for (int j=255; j>= 0; j--) {
	  yPos = (255-j)*pHeight;
	  Color col = Color.getHSBColor(((float)i)/255f,
					((float)j)/255f,	
					((float)brightnessValue)/255f);
	  g.setColor(col);
	  g.drawRect(xPos,yPos,1,1);
	  g.fillRect(xPos,yPos,1,1);
	}
      }
      g.setColor(Color.lightGray);
      g.drawRect(257, 0, 267, 256);
      g.fillRect(257, 0, 267, 256);
    }
		
    if (im != null)
      gr.drawImage(im,0,0,null);	
    if (point != null) {
      gr.fillRect(point.x, point.y, 1, 1);
    }
  }

  @Override
  public void update (Graphics g) {
    paint(g);
  }

  @Override
  public void mouseClicked(MouseEvent e) {
    float h,s,b;

    if (point == null) {
      point = new Point(e.getX(), e.getY());
    } else {
      point.x = e.getX();
      point.y = e.getY();
    }

    h = ((float)(point.x))/255f;
    s = ((float)(255-point.y))/255f;
    b = selec.getBrightness()/255f;
    selec.setColor(h,s);
    //updateRGB(h,s,b);

    hueValue = point.x;
    satValue = 255-point.y;
    hueTextField.setText("" + hueValue);
    satTextField.setText("" + satValue);
    brightnessTextField.setText("" + selec.getBrightness());

    repaint();
  }

  private void changeColorFromHSB() {
    float h = ((float)hueValue)/255f;
    float s = ((float)satValue)/255f;
    float b = selec.getBrightness()/255f;

    point.x = hueValue;
    point.y = (255-satValue);
    updateRGB(h,s,b);
    repaint();
  }

  private void updateRGB(float h, float s, float b) {
    int rgb = Color.HSBtoRGB(h,s,b);
    Color tempColor = new Color(rgb);
		
    selectedColor = tempColor;
    sample.setSelectedColor(tempColor);
    sample.repaint();
    redValue = tempColor.getRed();
    greenValue = tempColor.getGreen();
    blueValue = tempColor.getBlue();

    if (redValue != ((Integer.valueOf(redTextField.getText())).intValue()))
      redTextField.setText("" + redValue);

    if (greenValue != ((Integer.valueOf(greenTextField.getText())).intValue()))
      greenTextField.setText("" + greenValue);

    if (blueValue != ((Integer.valueOf(blueTextField.getText())).intValue()))
      blueTextField.setText("" + blueValue);
  }

  private void changeColorFromRGB() {
    int tempHue, tempSat, tempBright;
    hsbVals = Color.RGBtoHSB(redValue,greenValue,blueValue,null);

    tempHue = (int) (hsbVals[0] * 255f);
    tempSat = (int) (hsbVals[1] * 255f);
    tempBright = (int) (hsbVals[2] * 255f);

    if (tempHue != ((Integer.valueOf(hueTextField.getText())).intValue()))
      hueTextField.setText("" + tempHue);

    if (tempSat != ((Integer.valueOf(satTextField.getText())).intValue()))
      satTextField.setText("" + tempSat);

    if (tempBright != ((Integer.valueOf(brightnessTextField.getText())).intValue()))
      brightnessTextField.setText("" + tempBright);
  }

  @Override
  public void mousePressed(MouseEvent e) {}
  @Override
  public void mouseEntered(MouseEvent e) {}
  @Override
  public void mouseExited(MouseEvent e) {}
  @Override
  public void mouseReleased(MouseEvent e) {}
}
