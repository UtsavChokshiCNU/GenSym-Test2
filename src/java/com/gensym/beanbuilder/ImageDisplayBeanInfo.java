package com.gensym.beanbuilder;

import java.beans.*;
import com.gensym.beanbuilder.*;


/**
 * BeanInfo for ImageDisplay.
 *
 */

public class ImageDisplayBeanInfo extends SimpleBeanInfo {

	/**
	 * Constructs a ImageDisplayBeanInfo object.
	 */
	public ImageDisplayBeanInfo() {
	}


	@Override
	public java.awt.Image getIcon(int iconKind) {
		if (iconKind == BeanInfo.ICON_MONO_16x16 ||
			iconKind == BeanInfo.ICON_COLOR_16x16) {
			java.awt.Image img = loadImage("ID16.gif");
			return img;
		}

		if (iconKind == BeanInfo.ICON_MONO_32x32 ||
			iconKind == BeanInfo.ICON_COLOR_32x32) {
			java.awt.Image img = loadImage("ID32.gif");
			return img;
		}

		return null;
	}


 	}	//  end of class ImageDisplayBeanInfo
