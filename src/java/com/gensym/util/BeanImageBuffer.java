package com.gensym.util;

import java.awt.*;
import java.awt.image.MemoryImageSource;
import java.awt.image.*;

 /**
  *    Beans need icons to represent them in bean builders
  *    typically 32x32 and 16x16 icons
  *
  *    This code allows an image to be scaled to 32x32 for
  *    storage within the beaninfo file.
  *
  *    When the beaninfo is asked for an icon, it is able
  *    to reconstitute the image from the buffered data in the
  *    case of 32x32 , and a 16x16 scaled version of the 32x32
  *
  */
public class BeanImageBuffer extends Component {


    // we are going to be storing 32x32 pixel image
    // from that we can generate a 16x16 on the fly
     static int imageWidth=32;
     static int imageHeight=32;

     static volatile int bufferedData[];

    //constructor
    public BeanImageBuffer(){
    }

    public BeanImageBuffer(int[] bufferedData){
      this.bufferedData = bufferedData;
    }


    /**
     *
     */
     public void setBufferedData(int[] imageData){
            bufferedData = imageData;
     }

     /**
     *
     */
    public int[] getBufferedData(){
            return bufferedData;
     }


    //----------------------------------------------------------------------------------------

    /**
     * serializeImage
     *
     *@param Image
     *@param ImageObserver
     *
     *@return int[] of data representing the image
     */
     public int[]  serializeImage(Image sourceImage , ImageObserver observer)
    {
      int width = imageWidth; //sourceImage.getWidth(observer);
      int height= imageHeight; //sourceImage.getHeight(observer);

      Image simage = sourceImage.getScaledInstance(width, height ,Image.SCALE_SMOOTH);

      int pixels[]     = new int [width * height];
      PixelGrabber pg  = new PixelGrabber (simage, 0, 0, width, height, pixels, 0, width);
      try{
	if (pg.grabPixels() && ((pg.status() & ImageObserver.ALLBITS) !=0))
	  {

	  }

      }catch(Exception e){System.out.println(e.toString());}

      return pixels;
    }


    /**
     *serializeScaleImage
     *
     *@param Image
     *@param int x scale factor
     *@param int y scale factor
     *@param ImageObserver
     *
     *@return int[] of data representing the image
     */
    public int[] serializeScaleImage(Image sourceImage , int xScale , int yScale ,ImageObserver observer){
     // scale the source image
     Image i = sourceImage.getScaledInstance(xScale,yScale ,Image.SCALE_SMOOTH);
        //return the serialized data for the image
        return serializeImage( i ,  observer);
    }



    //----------------------------------------------------------------------------------------

    /**
     * deserializeImage
     *
     *This method takes an int array and creates an image from it
     *
     *@param int[] -- data representing the image
     *@return Image -- an image created from the int[]
     */
     public Image deserializeImage(int[] imageBuffer) {
       Image image=null;

         try{
             image = createImage(new MemoryImageSource (imageWidth, imageHeight, imageBuffer,
                            0, imageWidth));
        }catch(Exception e){System.out.println(e.toString());}

       return image;
    }

  

    //----------------------------------------------------------------------------------------

    /**
     *
     *&return Image a 16x16 of the given  image
     */
    public static Image get16x16icon(Image sourceImage){
        return sourceImage.getScaledInstance(16,16,Image.SCALE_SMOOTH);
    }



    /**
     *
     *@return Image a 32x32 of the given image
     */
     public static Image get32x32icon(Image sourceImage){
          return sourceImage.getScaledInstance(32,32,Image.SCALE_SMOOTH);
    }


    /**
     *
     *@return Image a 16x16 of the stored image
     */
    public Image get16x16icon(){
        return deserializeImage(bufferedData).getScaledInstance( 16,16,Image.SCALE_SMOOTH);
    }


    /**
     *
     *@return Image a 32x32 of the stored image
     */
    public Image get32x32icon(){
          return deserializeImage(bufferedData).getScaledInstance( 32,32,Image.SCALE_SMOOTH);
    }





}
