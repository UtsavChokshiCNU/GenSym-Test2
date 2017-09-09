package gensym.charts;

import java.awt.BasicStroke;

/**
 * Chart line types class. 
 */
public class ChartLineTypes {

    /** Extra thin line width */
    private static final float WIDTH_EXTRATHIN = 0.5f;

    /** Thin line width */
    private static final float WIDTH_THIN = 1f;

    /** Medium thin line width */
    private static final float WIDTH_MEDIUMTHIN = 2f;

    /** Medium line width */
    private static final float WIDTH_MEDIUM = 2.5f;

    /** Medium thick line width */
    private static final float WIDTH_MEDIUMTHICK = 3f;

    /** Thick line width */
    private static final float WIDTH_THICK = 4f;

    /** Extra thick line width */
    private static final float WIDTH_EXTRATHICKTHICK = 5f;

    /** Thin Solid Line */
    public static final int LINE_THINSOLID = 0;

    /** Dashed Line */
    public static final int LINE_DASH = 1;

    /** Dot Line */
    public static final int LINE_DOT = 2;

    /** Dash Dot Line */
    public static final int LINE_DASHDOT = 3;

    /** Dash Dot Dot */
    public static final int LINE_DASHDOTDOT = 4;

    /** Medium Solid Line */
    public static final int LINE_MEDIUMSOLID = 5;

    /** Thick Solid Line */
    public static final int LINE_THICKSOLID = 6;

    /** Medium Thin Solid Line */
    public static final int LINE_MEDIUMTHINSOLID = 9;

    /** Medium Thick Solid Line */
    public static final int LINE_MEDIUMTHICKSOLID = 10;

    /** Extra Thick Solid Line */
    public static final int LINE_EXTRATHICKSOLID = 11;

    /** Extra Thin Solid Line */
    public static final int LINE_EXTRATHINSOLID = 12;

    /** Extra Extra Thin Solid Line */
    public static final int LINE_EXTRAEXTRATHINSOLID = 13;

    /** Medium Thin Dash Line */
    public static final int LINE_MEDIUMTHINDASH = 16;

    /** Medium Thin Dot Line */
    public static final int LINE_MEDIUMTHINDOT = 17;

    /** Medium Thin Dash Dot Line */
    public static final int LINE_MEDIUMTHINDASHDOT = 18;

    /** Medium Thin Dash Dot Dot Line */
    public static final int LINE_MEDIUMTHINDASHDOTDOT = 19;

    /** Medium Dash Line */
    public static final int LINE_MEDIUMDASH = 20;

    /** Medium Dot Line */
    public static final int LINE_MEDIUMDOT = 21;

    /** Medium Dash Dot Line */
    public static final int LINE_MEDIUMDASHDOT = 22;

    /** Medium Dash Dot Dot Line */
    public static final int LINE_MEDIUMDASHDOTDOT = 23;

    /** Medium Thick Dash Line */
    public static final int LINE_MEDIUMTHICKDASH = 24;

    /** Medium Thick Dot Line */
    public static final int LINE_MEDIUMTHICKDOT = 25;

    /** Medium Thick Dash Dot Line */
    public static final int LINE_MEDIUMTHICKDASHDOT = 26;

    /** Medium Thick Dash Dot Dot Line */
    public static final int LINE_MEDIUMTHICKDASHDOTDOT = 27;

    /** Thick Dash Line */
    public static final int LINE_THICKDASH = 28;

    /** Thick Dot Line */
    public static final int LINE_THICKDOT = 29;

    /** Thick Dash Dot Line */
    public static final int LINE_THICKDASHDOT = 30;

    /** Extra Thick Dash Dot Dot Line */
    public static final int LINE_THICKDASHDOTDOT = 31;

    /** Extra Thick Dash Line */
    public static final int LINE_EXTRATHICKDASH = 32;

    /** Extra Thick Dot Line */
    public static final int LINE_EXTRATHICKDOT = 33;

    /** Extra Thick Dash Dot Line */
    public static final int LINE_EXTRATHICKDASHDOT = 34;

    /** Extra Thick Dash Dot Dot Line */
    public static final int LINE_EXTRATHICKDASHDOTDOT = 35;

    /**
     * Creates dash array corresponded to specified line type
     * @param type line type
     * @return dash array
     */
    private static float[] getDash(int type) {
        switch (type) {
            case LINE_THINSOLID:
            case LINE_MEDIUMSOLID:
            case LINE_THICKSOLID:
            case LINE_MEDIUMTHINSOLID:
            case LINE_MEDIUMTHICKSOLID:
            case LINE_EXTRATHICKSOLID:
            case LINE_EXTRATHINSOLID:
            case LINE_EXTRAEXTRATHINSOLID:
                return new float[0];

            case LINE_DASH:
            case LINE_MEDIUMTHINDASH:
            case LINE_MEDIUMDASH:
            case LINE_MEDIUMTHICKDASH:
            case LINE_THICKDASH:
            case LINE_EXTRATHICKDASH:
                return new float[]{10.0f, 6.0f};

            case LINE_DOT:
            case LINE_MEDIUMTHINDOT:
            case LINE_MEDIUMDOT:
            case LINE_MEDIUMTHICKDOT:
            case LINE_THICKDOT:
            case LINE_EXTRATHICKDOT:
                return new float[]{2.0f, 6.0f};

            case LINE_DASHDOT:
            case LINE_MEDIUMTHINDASHDOT:
            case LINE_MEDIUMDASHDOT:
            case LINE_MEDIUMTHICKDASHDOT:
            case LINE_THICKDASHDOT:
            case LINE_EXTRATHICKDASHDOT:
                return new float[]{10.0f, 6.0f, 2.0f, 6.0f};

            case LINE_DASHDOTDOT:
            case LINE_MEDIUMTHINDASHDOTDOT:
            case LINE_MEDIUMDASHDOTDOT:
            case LINE_MEDIUMTHICKDASHDOTDOT:
            case LINE_THICKDASHDOTDOT:
            case LINE_EXTRATHICKDASHDOTDOT:
                return new float[]{10.0f, 6.0f, 2.0f, 6.0f, 2.0f, 6.0f};
        }

        return new float[0];
    }

    /**
     * Returns line width corresponded to specified line type
     * @param type line type
     * @return line width
     */
    private static float getLineWidth(int type) {
        switch (type) {
            case LINE_EXTRATHINSOLID:
            case LINE_EXTRAEXTRATHINSOLID:
                return WIDTH_EXTRATHIN;

            case LINE_THINSOLID:
            case LINE_DASH:
            case LINE_DOT:
            case LINE_DASHDOT:
            case LINE_DASHDOTDOT:
                return WIDTH_THIN;

            case LINE_MEDIUMSOLID:
            case LINE_MEDIUMDASH:
            case LINE_MEDIUMDOT:
            case LINE_MEDIUMDASHDOT:
            case LINE_MEDIUMDASHDOTDOT:
                return WIDTH_MEDIUM;

            case LINE_THICKSOLID:
            case LINE_THICKDASH:
            case LINE_THICKDOT:
            case LINE_THICKDASHDOT:
            case LINE_THICKDASHDOTDOT:
                return WIDTH_THICK;

            case LINE_MEDIUMTHINSOLID:
            case LINE_MEDIUMTHINDASH:
            case LINE_MEDIUMTHINDOT:
            case LINE_MEDIUMTHINDASHDOT:
            case LINE_MEDIUMTHINDASHDOTDOT:
                return WIDTH_MEDIUMTHIN;

            case LINE_MEDIUMTHICKSOLID:
            case LINE_MEDIUMTHICKDASH:
            case LINE_MEDIUMTHICKDOT:
            case LINE_MEDIUMTHICKDASHDOT:
            case LINE_MEDIUMTHICKDASHDOTDOT:
                return WIDTH_MEDIUMTHICK;

            case LINE_EXTRATHICKSOLID:
            case LINE_EXTRATHICKDASH:
            case LINE_EXTRATHICKDOT:
            case LINE_EXTRATHICKDASHDOT:
            case LINE_EXTRATHICKDASHDOTDOT:
                return WIDTH_EXTRATHICKTHICK;
        }

        return WIDTH_MEDIUM;
    }

    /**
     * Makes BasicStroke object representing specified line type
     * @param type line type
     * @return BasicStroke object
     */
    public static BasicStroke makeBasicStroke(int type) {
        float[] dash = getDash(type);

        if (dash != null && dash.length > 0) {
            return new BasicStroke(getLineWidth(type), BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND, 1.0f, dash, 0.0f);
        }
        return new BasicStroke(getLineWidth(type));
    }
}
