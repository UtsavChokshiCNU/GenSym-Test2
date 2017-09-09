
package com.gensym.util;

public final class StringUtils {

  private StringUtils () {
  }

  public static String capitalize (String title) {
    boolean newWord = true;
    char[] characters = title.toCharArray ();
    for (int i=0; i<characters.length; i++) {
      if (characters[i] == '-') {
	characters[i] = ' ';
	newWord = true;
      } else if (!newWord) {
	characters[i] = Character.toLowerCase (characters[i]);
      } else {
	newWord = false;
      }
    }
    return new String (characters);
  }
}
