package com.gensym.core.util;

public class SystemUtilities {

  public static final int OS_WINDOWS = 0;
  public static final int OS_SUN = 1;
  public static final int OS_UNKNOWN = Integer.MAX_VALUE;

  /**
   * @returns true for all operating systems that contain
   * "Windows" in their name.
   */
  public static boolean isWindowsPlatform() {
    return getPlatformType() == OS_WINDOWS;
  }

  /**
   * Categorizes by relatively broad type. Keeps UNIX flavors
   * separate, but does not distinguish between different Windows
   * operating systems.
   */
  public static int getPlatformType() {
    String osName = System.getProperty("os.name");

    if (osName.indexOf("Windows") != -1)
      return OS_WINDOWS;
    else if (osName.indexOf("Sun") != -1)
      return OS_SUN;
    else {
      System.out.println("Unknown OS " + osName);
      return OS_UNKNOWN;
    }
  }

  public static Class loadClass(String className) 
    throws ClassNotFoundException {
    
    ClassLoader clsLoader = Thread.currentThread().getContextClassLoader();
    return clsLoader.loadClass(className);
  }

  /**
   * load and create a new instance of a class
   * Tue 13-Feb-2001 15:42 bush
   */
  public static Object loadAndInstantiateClass(String className) 
    throws ClassNotFoundException,InstantiationException, IllegalAccessException {

    return loadClass(className).newInstance();
  }

  public static void main(String[] args) {
    if ("isWindowsPlatform".equals(args[0]))
      System.out.println("isWindowsPlatform=" + isWindowsPlatform());
    else if ("getPlatformType".equals(args[0]))
      System.out.println("getPlatformType=" + getPlatformType());
    else
      System.out.println("Unknown argument " + args[0]);

    System.exit(0);
  }
}
