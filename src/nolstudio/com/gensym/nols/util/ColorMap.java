package com.gensym.nols.util;

import java.awt.Color;
import java.io.Serializable;

public class ColorMap implements Cloneable, Serializable{

	public static final int transparent = -1;
	public static final int aquamarine = 0;
	public static final int black = 1;
	public static final int blue = 2;
    public static final int blue_violet = 3;
    public static final int brown = 4;
    public static final int cadet_blue = 5;
    public static final int coral = 6;
    public static final int cornflower_blue = 7;
	public static final int cyan = 8;
    public static final int dark_gray = 9;

    public static final int dark_green = 10;
    public static final int dark_olive_green = 11;	       
    public static final int dark_orchid = 12;
    public static final int dark_slate_blue = 13;	
    public static final int dark_slate_gray = 14;
    public static final int dark_turquoise = 15;
    public static final int dim_gray = 16;
    public static final int firebrick = 17;
    public static final int forest_green = 18;
    public static final int gold = 19;
	
	public static final int goldenrod = 20;
	public static final int gray = 21;
	public static final int green = 22;
	public static final int green_yellow = 23;
	public static final int indian_red = 24;
	public static final int khaki = 25;
	public static final int light_blue = 26; 		
    public static final int light_gray = 27;
	public static final int extra_light_gray = 28;
	public static final int light_steel_blue = 29;

	public static final int lime_green = 30;
	public static final int magenta = 31;
	public static final int maroon = 32;
	public static final int medium_aquamarine = 33;		
	public static final int medium_blue = 34;
	public static final int medium_forest_green = 35;
	public static final int medium_goldenrod = 36;
	public static final int medium_orchid = 37;
	public static final int medium_sea_green = 38;
	public static final int medium_slate_blue = 39;
	
	public static final int medium_spring_green = 40;		
	public static final int medium_turquoise = 41;					
	public static final int medium_violet_red = 42;					
	public static final int midnight_blue = 43;	
	public static final int navy_blue = 44;	
    public static final int orange = 45;	
	public static final int pale_green = 46;	
	public static final int pink = 47;		       
	public static final int plum = 48;	
	public static final int purple = 49;	

	public static final int red = 50;	
	public static final int salmon = 51;				
	public static final int sea_green = 52;		
	public static final int sienna = 53;
	public static final int sky_blue = 54;
	public static final int slate_blue = 55;
	public static final int spring_green = 56;
	public static final int steel_blue = 57;
	public static final int tan = 58;      
	public static final int thistle = 59;

	public static final int turquoise = 60;
	public static final int violet = 61;
	public static final int violet_red = 62;
	public static final int wheat = 63;
	public static final int white = 64;
	public static final int yellow = 65;
	public static final int yellow_green = 66;
	public static final int smoke = 67;
	public static final int floral_white = 68;
	public static final int linen = 69;

	public static final int antique_white = 70;
	public static final int ivory = 71;
	public static final int azure = 72;
	public static final int lavender = 73;
	public static final int powder_blue = 74;
	public static final int pale_turquoise = 75;
	public static final int light_cyan = 76;
	public static final int pale_goldenrod = 77;
	public static final int light_goldenrod_yellow = 78;
	public static final int light_yellow = 79;

	public static final int light_goldenrod = 80;
	public static final int beige = 81;
	public static final int light_pink = 82;

  public static final Color[] colors = {
	new Color( 127 , 255 , 212),		
    Color.black,
	Color.blue,
	new Color( 159 , 95 , 159),
	new Color( 165 , 42 , 42),
	new Color( 95 , 158 , 160),
	new Color( 255 , 127 , 80),
	new Color( 66 , 66 , 111),
	Color.cyan,
	Color.gray,

	// 10 - 19
	new Color( 47, 79, 47),
	new Color( 79, 79, 47),	       
	new Color( 153, 50, 204),
	new Color( 72, 61, 139),	
	new Color( 47, 79 ,79 ),
	new Color( 112, 147, 219),
	new Color( 105 ,105 ,105),
	new Color( 142, 35, 35),
	new Color( 34, 139, 34),
	new Color( 255, 215, 0),
	
	// 20 - 29
	new Color( 218, 165, 32),
	new Color( 169, 169, 169),
	Color.green,
	new Color( 173, 255, 47),
	new Color( 205 ,92, 92),
	new Color( 240, 230, 140),
	new Color( 173, 216, 230),		
	new Color( 211, 211, 211),
	new Color(229, 229, 229),
	new Color( 143 ,143, 188),

	// 30 - 39
	new Color( 50, 205 ,50),
	Color.magenta,
	new Color( 128, 0, 0),
	new Color( 102, 205, 170),	
	new Color( 0 ,0 ,205),
	new Color( 107, 142, 35),
	new Color( 234, 234, 173), 
	new Color( 186, 85, 211),  
	new Color( 103, 169, 75), // too dark, orig 66, 111, 66
	new Color( 127, 0, 255),
	
	// 40 - 49
	new Color( 127, 255, 0),		
	new Color( 112, 219, 219),					
	new Color( 219, 112, 147),				
	new Color( 47, 47, 79),
	new Color( 35, 35, 142),
	new Color( 255, 165, 0),
	new Color( 152, 251, 152),
	new Color( 255, 192, 203),      
	new Color( 221, 160, 221),
	new Color( 128, 0, 128),

	// 50 - 59
	Color.red,
	new Color( 250, 128, 114),			
	new Color( 35, 142, 107),		
	new Color( 160, 82, 45),
	new Color( 135, 206, 235),
	new Color( 106, 90, 205),
	new Color( 0, 255, 127),
	new Color( 35, 107, 142),
	new Color( 210, 180, 140),	       
	new Color( 216, 191, 216),
	
	new Color( 64, 224, 208),
	new Color( 238 ,130, 238),
	new Color( 204, 50, 153),
	new Color( 245, 222, 179),
	Color.white,
	Color.yellow,
	new Color( 153, 204, 50),
	new Color(245, 245, 245),
	new Color(255, 250, 240),
	new Color(250, 240, 230),

	new Color(250, 235, 215),
	new Color(255, 255, 240),
	new Color(240, 255, 255),
	new Color(230, 230, 250),
	new Color(176, 224, 230),
	new Color(175, 238, 238),
	new Color(224, 255, 255),
	new Color(238, 232, 170),
	new Color(250, 250, 210),
	new Color(255, 255, 224),

	new Color(238, 221, 130),
	new Color(245, 245, 220),
	new Color(255, 182, 193)
  };

	public static final int[] defaultLabelColors = {
		red,
		yellow,
		blue,
		green,
		magenta,
		cyan,
		medium_goldenrod,
		white,
		gold,
		brown,
		forest_green,
		light_gray,
		light_steel_blue,
		medium_sea_green,
		sienna,
		tan,
		thistle,
		linen,
		medium_spring_green,
	};

	public static final int[] defaultPlotColors = {
		goldenrod,
		green_yellow,
		extra_light_gray,
		coral,
		khaki,
		medium_sea_green,
		medium_orchid,
		medium_violet_red,
		dark_turquoise,
		orange,
		pale_green,
		pink,
		plum,
		salmon,
		gray,
		sky_blue,
		spring_green,
		violet,
		medium_turquoise,
		wheat,
		azure,
		turquoise,
		beige,
		yellow_green,
		aquamarine
	};
	
	@Override
	public Object clone() throws CloneNotSupportedException {
		return super.clone();
	}
}
