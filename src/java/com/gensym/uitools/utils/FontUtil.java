package com.gensym.uitools.utils;

import javax.swing.MenuElement;
import javax.swing.JMenuItem;
import java.awt.Insets;
import java.awt.Font;
import java.awt.Component;
import java.awt.Container;
import java.awt.Menu;
import java.awt.MenuComponent;

public class FontUtil {

  public static final Font sanserifPlain11 = new Font("sansserif", Font.PLAIN, 11);
  public static void setFontForContainer(Container container,
					 Font font,
					 boolean setContainer)
  {
    if (setContainer){
    	container.setFont(font);
    }
    Component[] components = container.getComponents();
    for (int i=0;i<components.length;i++) {
      Component component = components[i];
      if (component instanceof Container)
	setFontForContainer((Container)component,
			    font,
			    true);
    }    
  }
  
  public static void initMenuElement(MenuElement menuElement,
				      Insets menuInsets,
				      Font theFont) {
    if (menuElement instanceof JMenuItem) {
      JMenuItem menuItem = ((JMenuItem)menuElement);
      if (menuInsets != null)
	menuItem.setMargin(menuInsets);
      menuItem.setFont(theFont);
    }
    MenuElement[] subElements = menuElement.getSubElements();
    for (int i=0;i<subElements.length;i++) 
      initMenuElement(subElements[i], menuInsets, theFont);
  }

  public static void initMenuComponent(MenuComponent menuComponent,
				       Font theFont) {
    menuComponent.setFont(theFont);
    if (menuComponent instanceof Menu) {
      Menu menu = (Menu)menuComponent;
      int subMenuItemCount = menu.getItemCount();
      for (int i=0;i<subMenuItemCount;i++) 
	initMenuComponent(menu.getItem(i),theFont);
    }
  }  
}
