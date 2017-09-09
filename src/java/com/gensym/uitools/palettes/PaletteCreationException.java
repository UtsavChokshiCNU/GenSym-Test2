package com.gensym.uitools.palettes;

public class PaletteCreationException extends Exception
{
  public PaletteCreationException(Exception nestedException) {
    this(nestedException.getMessage());
  }

  public PaletteCreationException(String message) {
    super(message);
  }

  public PaletteCreationException() {
    super();
  }
}
