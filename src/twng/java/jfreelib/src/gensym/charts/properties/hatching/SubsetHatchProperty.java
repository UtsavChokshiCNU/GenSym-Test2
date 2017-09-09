package gensym.charts.properties.hatching;

import gensym.charts.JFreeChartHolder;
import gensym.charts.hatching.HatchedPaint;
import gensym.charts.properties.PropValueBase;

/**
 * <b>subset-hatch</b> int property class.
 * Sets series hatch style
 */
public class SubsetHatchProperty extends PropValueBase<Integer> {

    /** PE hatching constants: draw horizontal line: ---- */
    public static final int PEHS_HORIZONTAL = 0;
    /** PE hatching constants: draw vertical line: |||| */
    public static final int PEHS_VERTICAL  = 1;
    /** PE hatching constants: draw diagonal line from left upper to right bottom corner: \\\\ */
    public static final int PEHS_FDIAGONAL = 2;
    /** PE hatching constants: draw diagonal line from left bottom to right upper corner: //// */
    public static final int PEHS_BDIAGONAL = 3;
    /** PE hatching constants: draw both horizontal and vertical lines: ++++ */
    public static final int PEHS_CROSS     = 4;
    /** PE hatching constants: draw both diagonal lines: xxxx */
    public static final int PEHS_DIAGCROSS = 5;

    /**
     * Constructor
     */
    public SubsetHatchProperty() {
        super(2940, "subset-hatch");
    }

    
    /**
     * Convert PE hatch style to HatchedPaint hatch style mask
     * @param value the PE hatch style value
     * @return the HatchedPaint hatch style mask
     */
    public static int getHatchStyleMaskFromPEHS(int value) {
        switch (value) {
            case PEHS_HORIZONTAL:
                return HatchedPaint.HORIZONTAL_LINE;
            case PEHS_VERTICAL:
                return HatchedPaint.VERTICAL_LINE;
            case PEHS_FDIAGONAL:
                return HatchedPaint.LU_RB_DIAGONAL_LINE;
            case PEHS_BDIAGONAL:
                return HatchedPaint.LB_RU_DIAGONAL_LINE;
            case PEHS_CROSS:
                return HatchedPaint.HORIZONTAL_LINE | HatchedPaint.VERTICAL_LINE;
            case PEHS_DIAGCROSS:
                return HatchedPaint.LU_RB_DIAGONAL_LINE | HatchedPaint.LB_RU_DIAGONAL_LINE;
            default:
                return HatchedPaint.LINE_NONE;
        }
    }
    
    /**
     * {@inheritDoc}
     */
    protected void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        chart.getChart().setSeriesHatch(i, getHatchStyleMaskFromPEHS(value));
    }

}
