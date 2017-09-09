package com.gensym.ntw.util;

import com.gensym.icons.IconDescription;
import com.gensym.classes.ImageDefinition;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import java.awt.Image;
import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2AccessException;

public class G2IconDescription extends IconDescription {
  private static final Symbol IMAGE_DEFINITION_ = Symbol.intern ("IMAGE-DEFINITION");
  
  public G2IconDescription(Symbol className,
			   G2Access context)
       throws G2AccessException
  {
    this((Structure)context.getClassManager().getClassAttributeValue
	  (className,
	   SystemAttributeSymbols.ICON_DESCRIPTION_),
	 context);
  }

  public G2IconDescription(Structure iconDescription,
			   G2Access context)
       throws G2AccessException
  {
    super(iconDescription);
    Symbol imageName = getBackgroundImageName();
    if (imageName != null) {
      ImageDefinition imageDef =
	(ImageDefinition)context.getUniqueNamedItem (IMAGE_DEFINITION_, imageName);
      if (imageDef.getWidthOfImage () != null) {
	Image image = imageDef.getImage();
	setBackgroundImage(image,
			   imageDef.getWidthOfImage().intValue(),
			   imageDef.getHeightOfImage().intValue());
      }
    }
  }

}
