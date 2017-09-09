package gensym.charts.hatching;

import java.awt.PaintContext;
import java.awt.image.ColorModel;
import java.awt.image.Raster;

/**
 * Simple hatched paint context 
 */
public class HatchedPaintContext implements PaintContext  {

    /** Reference for hatched paint */
    HatchedPaint hatchPaint;
    
    /**
     * Constructor with specified HatchedPaint object
     * @param hp the hatched paint
     */
    protected HatchedPaintContext(HatchedPaint hp) {
        hatchPaint = hp;
    }

    /**
     * {@inheritDoc}
     */
    public synchronized Raster getRaster(int x, int y, int w, int h) {
        return hatchPaint.getImage(x, y, w, h).getRaster();
    }

    /**
     * {@inheritDoc}
     */
    public ColorModel getColorModel() {
        return ColorModel.getRGBdefault();
    }

    /**
     * {@inheritDoc}
     */
    public void dispose() {
    }
}
