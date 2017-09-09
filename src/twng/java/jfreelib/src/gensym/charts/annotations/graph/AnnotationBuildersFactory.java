package gensym.charts.annotations.graph;

import gensym.charts.ChartLineTypes;

/**
 * Graph annotation builders factory 
 */
public abstract class AnnotationBuildersFactory {
    /** Cross */
    public static final int PEGAT_CROSS = 2;
    
    /** Small cross */
    public static final int PEGAT_SMALLCROSS = 14;
    
    /** Large cross */
    public static final int PEGAT_LARGECROSS = 26;
    
    /** Thin solid line */
    public static final int PEGAT_THINSOLIDLINE = 38;

    /** Thin dash line */
    public static final int PEGAT_DASHLINE = 39;

    /** Thin dot line */
    public static final int PEGAT_DOTLINE = 40;

    /** Thin dash-dot line */
    public static final int PEGAT_DASHDOTLINE = 41;

    /** Thin dash-dot-dot line */
    public static final int PEGAT_DASHDOTDOTLINE = 42;

    /** Thin solid line */
    public static final int PEGAT_MEDIUMSOLIDLINE = 43;

    /** Thin solid line */
    public static final int PEGAT_THICKSOLIDLINE = 44;

    /** Start polygon */
    public static final int PEGAT_STARTPOLY = 74;

    /** Start text */
    public static final int PEGAT_STARTTEXT = 84;

    /** Medium thin line */
    public static final int PEGAT_MEDIUMTHINSOLID = 87;

    /** Medium thick line */
    public static final int PEGAT_MEDIUMTHICKSOLID = 88;

    /** Extra thick line */
    public static final int PEGAT_EXTRATHICKSOLID = 89;

    /** Extra thin line */
    public static final int PEGAT_EXTRATHINSOLID = 90;

    /** Medium thin dash line */
    public static final int PEGAT_MEDIUMTHINDASH = 105;

    /** Medium thin dot line */
    public static final int PEGAT_MEDIUMTHINDOT = 106;

    /** Medium thin dash-dot line */
    public static final int PEGAT_MEDIUMTHINDASHDOT = 107;

    /** Medium thin dash-dot-dot line */
    public static final int PEGAT_MEDIUMTHINDASHDOTDOT = 108;

    /** Medium dash line */
    public static final int PEGAT_MEDIUMDASH = 109;

    /** Medium dot line */
    public static final int PEGAT_MEDIUMDOT = 110;

    /** Medium dash-dot line */
    public static final int PEGAT_MEDIUMDASHDOT = 111;

    /** Medium dash dot-dot line */
    public static final int PEGAT_MEDIUMDASHDOTDOT = 112;

    /** Medium thick dash line */
    public static final int PEGAT_MEDIUMTHICKDASH = 113;

    /** Medium thick dot line */
    public static final int PEGAT_MEDIUMTHICKDOT = 114;

    /** Medium thick dash-dot line */
    public static final int PEGAT_MEDIUMTHICKDASHDOT = 115;

    /** Medium thick dash-dot-dot line */
    public static final int PEGAT_MEDIUMTHICKDASHDOTDOT = 116;

    /** Thick dash line */
    public static final int PEGAT_THICKDASH = 117;

    /** Thick dot line */
    public static final int PEGAT_THICKDOT = 118;

    /** Thick dash-dot line */
    public static final int PEGAT_THICKDASHDOT = 119;

    /** Thick dash-dot-dot line */
    public static final int PEGAT_THICKDASHDOTDOT = 120;

    /** Extra thick dash line */
    public static final int PEGAT_EXTRATHICKDASH = 121;

    /** Thin extra thick dot line */
    public static final int PEGAT_EXTRATHICKDOT = 122;

    /** Extra thick dash-dot line */
    public static final int PEGAT_EXTRATHICKDASHDOT = 123;

    /** Extra thick dash-dot-dot line */
    public static final int PEGAT_EXTRATHICKDASHDOTDOT = 124;

    /** 
     * Plus 
     */
    public static final int PEGAT_PLUS = 1;

    /** 
     * Small plus 
     */
    public static final int PEGAT_SMALLPLUS = 13;

    /**  
     * Large plus
     */
    public static final int PEGAT_LARGEPLUS = 25;

    /**  
     * Dot
     */
    public static final int PEGAT_DOT = 3;

    /**  
     * Dot solid
     */
    public static final int PEGAT_DOTSOLID = 4;

    /**  
     * Small dot
     */
    public static final int PEGAT_SMALLDOT = 15;

    /**  
     * Small dot solid
     */
    public static final int PEGAT_SMALLDOTSOLID = 16;

    /**  
     * Large dot
     */
    public static final int PEGAT_LARGEDOT = 27;

    /**  
     * Large dot solid
     */
    public static final int PEGAT_LARGEDOTSOLID = 28;

    /**  
     * Square
     */
    public static final int PEGAT_SQUARE = 5;

    /**  
     * Square solid
     */
    public static final int PEGAT_SQUARESOLID = 6;

    /**  
     * Small square
     */
    public static final int PEGAT_SMALLSQUARE = 17;

    /**  
     * Small square solid
     */
    public static final int PEGAT_SMALLSQUARESOLID = 18;

    /**  
     * Large square
     */
    public static final int PEGAT_LARGESQUARE = 29;

    /**  
     * Large square solid
     */
    public static final int PEGAT_LARGESQUARESOLID = 30;

    /**  
     * Diamond
     */
    public static final int PEGAT_DIAMOND = 7;

    /**  
     * Diamond solid
     */
    public static final int PEGAT_DIAMONDSOLID = 8;

    /**  
     * Small diamond 
     */
    public static final int PEGAT_SMALLDIAMOND = 19;

    /**  
     * Small diamond solid
     */
    public static final int PEGAT_SMALLDIAMONDSOLID = 20;

    /**  
     * Large diamond
     */
    public static final int PEGAT_LARGEDIAMOND = 31;

    /**  
     * Large diamond solid
     */
    public static final int PEGAT_LARGEDIAMONDSOLID = 32;

    /**  
     * Up-triangle
     */
    public static final int PEGAT_UPTRIANGLE = 9;

    /**  
     * Up-triangle solid
     */
    public static final int PEGAT_UPTRIANGLESOLID = 10;

    /**  
     * Small up-triangle
     */
    public static final int PEGAT_SMALLUPTRIANGLE = 21;

    /**  
     * Small up-triangle solid
     */
    public static final int PEGAT_SMALLUPTRIANGLESOLID = 22;

    /**  
     * Large up-triangle
     */
    public static final int PEGAT_LARGEUPTRIANGLE = 33;

    /**  
     * Large up-triangle solid
     */
    public static final int PEGAT_LARGEUPTRIANGLESOLID = 34;

    /**  
     * Down-triangle
     */
    public static final int PEGAT_DOWNTRIANGLE = 11;

    /**  
     * Down-triangle solid
     */
    public static final int PEGAT_DOWNTRIANGLESOLID = 12;

    /**  
     * Small down-triangle
     */
    public static final int PEGAT_SMALLDOWNTRIANGLE = 23;

    /**  
     * Small down-triangle solid
     */
    public static final int PEGAT_SMALLDOWNTRIANGLESOLID = 24;

    /**  
     * Large down-triangle
     */
    public static final int PEGAT_LARGEDOWNTRIANGLE = 35;

    /**  
     * Large down-triangle solid
     */
    public static final int PEGAT_LARGEDOWNTRIANGLESOLID = 36;

    /**
     * Pointer
     */
    public static final int PEGAT_POINTER = 37;

    /**  
     * Small vector with arrow
     */
    public static final int PEGAT_POINTER_VECTOR_SMALL = 187;

    /**  
     * Medium vector with arrow
     */
    public static final int PEGAT_POINTER_VECTOR_MEDIUM = 188;

    /**  
     * Large vector with arrow
     */
    public static final int PEGAT_POINTER_VECTOR_LARGE = 189;

    /**  
     * Small pointer with arrow
     */
    public static final int PEGAT_POINTER_ARROW_SMALL = 190;

    /**  
     * Medium pointer with arrow
     */
    public static final int PEGAT_POINTER_ARROW_MEDIUM = 191;

    /**  
     * Large pointer with arrow
     */
    public static final int PEGAT_POINTER_ARROW_LARGE = 192;

    /**  
     * Dash
     */
    public static final int PEGAT_DASH = 72;

    /**  
     * Pixel
     */
    public static final int PEGAT_PIXEL = 73;

    /**  
     * Simple arrow to north
     */
    public static final int PEGAT_ARROW_N = 92;

    /**  
     * Simple arrow to north-east
     */
    public static final int PEGAT_ARROW_NE = 93;

    /**  
     * Simple arrow to east
     */
    public static final int PEGAT_ARROW_E = 94;

    /**  
     * Simple arrow to south-east 
     */
    public static final int PEGAT_ARROW_SE = 95;

    /**  
     * Simple arrow to south
     */
    public static final int PEGAT_ARROW_S = 96;

    /**  
     * Simple arrow to south-west
     */
    public static final int PEGAT_ARROW_SW = 97;

    /**  
     * Simple arrow to west
     */
    public static final int PEGAT_ARROW_W = 98;

    /**  
     * Simple arrow to north-west 
     */
    public static final int PEGAT_ARROW_NW = 99;

    /** 
     * Shape normal size
     */
    public static final int SHAPE_SIZE_NORMAL = 24; 

    /** 
     * Shape small size
     */
    public static final int SHAPE_SIZE_SMALL = 14; 

    /** 
     * Shape large size
     */
    public static final int SHAPE_SIZE_LARGE = 38;
    
    /** 
     * Shape solid paint
     */
    public static final boolean SHAPE_SOLID = true;  

    /** 
     * Shape solid no paint
     */
    public static final boolean SHAPE_SOLID_NO = false;  
    
    /**
     * Creates graph annotation builder
     * @param info annotation info
     * @return the graph annotation builder
     */
    public static AbstractBuilder createBuilder(AnnotationInfo info) {
        switch (info.getType()) {
        case PEGAT_CROSS:
            return new CrossAnnotation(info, SHAPE_SIZE_NORMAL);
        case PEGAT_SMALLCROSS:
            return new CrossAnnotation(info, SHAPE_SIZE_SMALL);
        case PEGAT_LARGECROSS:
            return new CrossAnnotation(info, SHAPE_SIZE_LARGE);

        case PEGAT_PLUS:
            return new PlusAnnotation(info, SHAPE_SIZE_NORMAL);
        case PEGAT_SMALLPLUS:
            return new PlusAnnotation(info, SHAPE_SIZE_SMALL);
        case PEGAT_LARGEPLUS:
            return new PlusAnnotation(info, SHAPE_SIZE_LARGE);

        case PEGAT_DOT:
            return new DotAnnotation(info, 22, SHAPE_SOLID_NO);
        case PEGAT_DOTSOLID:
            return new DotAnnotation(info, 22, SHAPE_SOLID);
        case PEGAT_SMALLDOT:
            return new DotAnnotation(info, 8, SHAPE_SOLID_NO);
        case PEGAT_SMALLDOTSOLID:
            return new DotAnnotation(info, 8, SHAPE_SOLID);
        case PEGAT_LARGEDOT:
            return new DotAnnotation(info, 32, SHAPE_SOLID_NO);
        case PEGAT_LARGEDOTSOLID:
            return new DotAnnotation(info, 32, SHAPE_SOLID);

        case PEGAT_PIXEL:
            return new DotAnnotation(info, SHAPE_SIZE_SMALL /7, SHAPE_SOLID);
            
        case PEGAT_SQUARE:
            return new SquareAnnotation(info, (int)(SHAPE_SIZE_NORMAL*1.4), SHAPE_SOLID_NO);
        case PEGAT_SQUARESOLID:
            return new SquareAnnotation(info, (int)(SHAPE_SIZE_NORMAL*1.4), SHAPE_SOLID);
        case PEGAT_SMALLSQUARE:
            return new SquareAnnotation(info, (int)(SHAPE_SIZE_SMALL*1.4), SHAPE_SOLID_NO);
        case PEGAT_SMALLSQUARESOLID:
            return new SquareAnnotation(info, (int)(SHAPE_SIZE_SMALL*1.4), SHAPE_SOLID);
        case PEGAT_LARGESQUARE:
            return new SquareAnnotation(info, (int)(SHAPE_SIZE_LARGE*1.4), SHAPE_SOLID_NO);
        case PEGAT_LARGESQUARESOLID:
            return new SquareAnnotation(info, (int)(SHAPE_SIZE_LARGE*1.4), SHAPE_SOLID);

        case PEGAT_DIAMOND:
            return new DiamondAnnotation(info, SHAPE_SIZE_NORMAL, SHAPE_SOLID_NO);
        case PEGAT_DIAMONDSOLID:
            return new DiamondAnnotation(info, SHAPE_SIZE_NORMAL, SHAPE_SOLID);
        case PEGAT_SMALLDIAMOND:
            return new DiamondAnnotation(info, SHAPE_SIZE_SMALL, SHAPE_SOLID_NO);
        case PEGAT_SMALLDIAMONDSOLID:
            return new DiamondAnnotation(info, SHAPE_SIZE_SMALL, SHAPE_SOLID);
        case PEGAT_LARGEDIAMOND:
            return new DiamondAnnotation(info, SHAPE_SIZE_LARGE, SHAPE_SOLID_NO);
        case PEGAT_LARGEDIAMONDSOLID:
            return new DiamondAnnotation(info, SHAPE_SIZE_LARGE, SHAPE_SOLID);

        case PEGAT_UPTRIANGLE:
            return new UpTriangleAnnotation(info, SHAPE_SIZE_NORMAL, SHAPE_SOLID_NO);
        case PEGAT_UPTRIANGLESOLID:
            return new UpTriangleAnnotation(info, SHAPE_SIZE_NORMAL, SHAPE_SOLID);
        case PEGAT_SMALLUPTRIANGLE:
            return new UpTriangleAnnotation(info, SHAPE_SIZE_SMALL, SHAPE_SOLID_NO);
        case PEGAT_SMALLUPTRIANGLESOLID:
            return new UpTriangleAnnotation(info, SHAPE_SIZE_SMALL, SHAPE_SOLID);
        case PEGAT_LARGEUPTRIANGLE:
            return new UpTriangleAnnotation(info, SHAPE_SIZE_LARGE, SHAPE_SOLID_NO);
        case PEGAT_LARGEUPTRIANGLESOLID:
            return new UpTriangleAnnotation(info, SHAPE_SIZE_LARGE, SHAPE_SOLID);

        case PEGAT_DOWNTRIANGLE:
            return new DownTriangleAnnotation(info, SHAPE_SIZE_NORMAL, SHAPE_SOLID_NO);
        case PEGAT_DOWNTRIANGLESOLID:
            return new DownTriangleAnnotation(info, SHAPE_SIZE_NORMAL, SHAPE_SOLID);
        case PEGAT_SMALLDOWNTRIANGLE:
            return new DownTriangleAnnotation(info, SHAPE_SIZE_SMALL, SHAPE_SOLID_NO);
        case PEGAT_SMALLDOWNTRIANGLESOLID:
            return new DownTriangleAnnotation(info, SHAPE_SIZE_SMALL, SHAPE_SOLID);
        case PEGAT_LARGEDOWNTRIANGLE:
            return new DownTriangleAnnotation(info, SHAPE_SIZE_LARGE, SHAPE_SOLID_NO);
        case PEGAT_LARGEDOWNTRIANGLESOLID:
            return new DownTriangleAnnotation(info, SHAPE_SIZE_LARGE, SHAPE_SOLID);
            
        case PEGAT_POINTER:
            return new PointerAnnotation(info, PointerAnnotation.POINTER);
        case PEGAT_POINTER_VECTOR_SMALL:
            return new PointerAnnotation(info, PointerAnnotation.VECTOR_SMALL);
        case PEGAT_POINTER_VECTOR_MEDIUM:
            return new PointerAnnotation(info, PointerAnnotation.VECTOR_MEDIUM);
        case PEGAT_POINTER_VECTOR_LARGE:
            return new PointerAnnotation(info, PointerAnnotation.VECTOR_LARGE);
        case PEGAT_POINTER_ARROW_SMALL:
            return new PointerAnnotation(info, PointerAnnotation.ARROW_SMALL);
        case PEGAT_POINTER_ARROW_MEDIUM:
            return new PointerAnnotation(info, PointerAnnotation.ARROW_MEDIUM);
        case PEGAT_POINTER_ARROW_LARGE:
            return new PointerAnnotation(info, PointerAnnotation.ARROW_LARGE);
            
        case PEGAT_ARROW_N:
            return new ArrowAnnotation(info, ArrowAnnotation.ARROW_N);
        case PEGAT_ARROW_NE:
            return new ArrowAnnotation(info, ArrowAnnotation.ARROW_NE);
        case PEGAT_ARROW_E:
            return new ArrowAnnotation(info, ArrowAnnotation.ARROW_E);
        case PEGAT_ARROW_SE:
            return new ArrowAnnotation(info, ArrowAnnotation.ARROW_SE);
        case PEGAT_ARROW_S:
            return new ArrowAnnotation(info, ArrowAnnotation.ARROW_S);
        case PEGAT_ARROW_SW:
            return new ArrowAnnotation(info, ArrowAnnotation.ARROW_SW);
        case PEGAT_ARROW_W:
            return new ArrowAnnotation(info, ArrowAnnotation.ARROW_W);
        case PEGAT_ARROW_NW:
            return new ArrowAnnotation(info, ArrowAnnotation.ARROW_NW);
            
        case PEGAT_DASH:
            return new DashAnnotation(info);
            
        case PEGAT_EXTRATHINSOLID:
            return new LineAnnotation(info, 
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_EXTRATHINSOLID), null);
        case PEGAT_THINSOLIDLINE:
            return new LineAnnotation(info,
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_THINSOLID), null);
        case PEGAT_MEDIUMTHINSOLID:
            return new LineAnnotation(info,
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_MEDIUMTHINSOLID), null);
        case PEGAT_MEDIUMSOLIDLINE:
            return new LineAnnotation(info,
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_MEDIUMSOLID), null);
        case PEGAT_MEDIUMTHICKSOLID:
            return new LineAnnotation(info,
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_MEDIUMTHICKSOLID), null);
        case PEGAT_THICKSOLIDLINE:
            return new LineAnnotation(info,
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_THICKSOLID), null);
        case PEGAT_EXTRATHICKSOLID:
            return new LineAnnotation(info,
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_EXTRATHICKSOLID), null);
            
        case PEGAT_DASHLINE:
            return new LineAnnotation(info,
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_DASH),
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_THINSOLID));
        case PEGAT_MEDIUMTHINDASH:
            return new LineAnnotation(info,
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_MEDIUMTHINDASH),
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_MEDIUMTHINSOLID));
        case PEGAT_MEDIUMDASH:
            return new LineAnnotation(info,
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_MEDIUMDASH),
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_MEDIUMSOLID));
        case PEGAT_MEDIUMTHICKDASH:
            return new LineAnnotation(info,
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_MEDIUMTHICKDASH),
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_MEDIUMTHICKSOLID));
        case PEGAT_THICKDASH:
            return new LineAnnotation(info,
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_THICKDASH),
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_THICKSOLID));
        case PEGAT_EXTRATHICKDASH:
            return new LineAnnotation(info,
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_EXTRATHICKDASH),
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_EXTRATHICKSOLID));
            
        case PEGAT_DOTLINE:
            return new LineAnnotation(info,
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_DOT),
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_THINSOLID));
        case PEGAT_MEDIUMTHINDOT:
            return new LineAnnotation(info,
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_MEDIUMTHINDOT),
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_MEDIUMTHINSOLID));
        case PEGAT_MEDIUMDOT:
            return new LineAnnotation(info,
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_MEDIUMDOT),
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_MEDIUMSOLID));
        case PEGAT_MEDIUMTHICKDOT:
            return new LineAnnotation(info,
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_MEDIUMTHICKDOT),
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_MEDIUMTHICKSOLID));
        case PEGAT_THICKDOT:
            return new LineAnnotation(info,
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_THICKDOT),
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_THICKSOLID));
        case PEGAT_EXTRATHICKDOT:
            return new LineAnnotation(info,
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_EXTRATHICKDOT),
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_EXTRATHICKSOLID));
    
        case PEGAT_DASHDOTLINE:
            return new LineAnnotation(info,
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_DASHDOT),
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_THINSOLID));
        case PEGAT_MEDIUMTHINDASHDOT:
            return new LineAnnotation(info,
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_MEDIUMTHINDASHDOT),
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_MEDIUMTHINSOLID));
        case PEGAT_MEDIUMDASHDOT:
            return new LineAnnotation(info,
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_MEDIUMDASHDOT),
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_MEDIUMSOLID));
        case PEGAT_MEDIUMTHICKDASHDOT:
            return new LineAnnotation(info,
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_MEDIUMTHICKDASHDOT),
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_MEDIUMTHICKSOLID));
        case PEGAT_THICKDASHDOT:
            return new LineAnnotation(info,
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_THICKDASHDOT),
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_THICKSOLID));
        case PEGAT_EXTRATHICKDASHDOT:
            return new LineAnnotation(info,
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_EXTRATHICKDASHDOT),
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_EXTRATHICKSOLID));

        case PEGAT_DASHDOTDOTLINE:
            return new LineAnnotation(info,
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_DASHDOTDOT),
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_THINSOLID));
        case PEGAT_MEDIUMTHINDASHDOTDOT:
            return new LineAnnotation(info,
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_MEDIUMTHINDASHDOTDOT),
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_MEDIUMTHINSOLID));
        case PEGAT_MEDIUMDASHDOTDOT:
            return new LineAnnotation(info,
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_MEDIUMDASHDOTDOT),
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_MEDIUMSOLID));
        case PEGAT_MEDIUMTHICKDASHDOTDOT:
            return new LineAnnotation(info,
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_MEDIUMTHICKDASHDOTDOT),
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_MEDIUMTHICKSOLID));
        case PEGAT_THICKDASHDOTDOT:
            return new LineAnnotation(info,
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_THICKDASHDOTDOT),
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_THICKSOLID));
        case PEGAT_EXTRATHICKDASHDOTDOT:
            return new LineAnnotation(info,
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_EXTRATHICKDASHDOTDOT),
                    ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_EXTRATHICKSOLID));

        case TopLeftBottomRightAnnotation.PEGAT_BOTTOMRIGHT:
        case TopLeftBottomRightAnnotation.PEGAT_TOPLEFT:
            return new TopLeftBottomRightAnnotation(info);
            
        case PEGAT_STARTPOLY:
            return new StartPolyAnnotation(info);
            
        case PEGAT_STARTTEXT:
            return new StartTextAnnotation(info);
        }
        return null;
    }
}
