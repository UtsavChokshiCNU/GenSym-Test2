package gensym.charts.properties.rotation;

import gensym.charts.Chart3D;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

/**
 * <b>rotation-increment</b> int property class.
 * This property sets increment for auto rotation
 */
public class RotationIncrementProperty extends PropValueBase<Integer> {

    /** Increment by 15 degrees */
    public static final int PERI_INCBY15 = 0;
    /** Increment by 10 degrees */
    public static final int PERI_INCBY10 = 1;
    /** Increment by 5 degrees */
    public static final int PERI_INCBY5 = 2;
    /** Increment by 2 degrees */
    public static final int PERI_INCBY2 = 3;
    /** Increment by 1 degree */
    public static final int PERI_INCBY1 = 4;
    /** Decrement by 1 degree */
    public static final int PERI_DECBY1 = 5;
    /** Decrement by 2 degrees */
    public static final int PERI_DECBY2 = 6;
    /** Decrement by 5 degrees */
    public static final int PERI_DECBY5 = 7;
    /** Decrement by 10 degrees */
    public static final int PERI_DECBY10 = 8;
    /** Decrement by 15 degrees */
    public static final int PERI_DECBY15 = 9;

    /**
     * Gets degree for auto rotation
     * @param value of the prop
     * @return degree
     */
    public int getDegree(int value) {
        int degree = 2;

        switch (value) {
            case PERI_INCBY15:
                degree = 15;
                break;
            case PERI_INCBY10:
                degree = 10;
                break;
            case PERI_INCBY5:
                degree = 5;
                break;
            case PERI_INCBY2:
                degree = 2;
                break;
            case PERI_INCBY1:
                degree = 1;
                break;
            case PERI_DECBY1:
                degree = -1;
                break;
            case PERI_DECBY2:
                degree = -2;
                break;
            case PERI_DECBY5:
                degree = -5;
                break;
            case PERI_DECBY10:
                degree = -10;
                break;
            case PERI_DECBY15:
                degree = -15;
                break;
        }
        return degree;
    }

    /**
     * Constructor
     */
    public RotationIncrementProperty() {
        super(4004, "rotation-increment");
    }

    /**
     * {@inheritDoc}
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof Chart3D) {
            ((Chart3D) chart.getChart()).getAutoRotation().setIncrement(getDegree(value));
        }
    }
}
