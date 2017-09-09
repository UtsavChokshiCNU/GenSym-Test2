package com.gensym.tests;

public class TestSignatureClass {

  public TestSignatureClass() {
  }

  public TestSignatureClass(int i,
			    boolean z,
			    double d,
			    float f,
			    byte b,
			    short s,
			    long j,
			    char c,
			    String t) {
    System.out.println("TestSignatureClass Created with " +  i + "\n" + 
		       z + "\n" + 
		       d + "\n" +
		       f + "\n" +
		       s + "\n" + 
		       j + "\n" +
		       c + "\n" +
		       t + "\n");
  }

  public TestSignatureClass(int[] ia,
			    boolean[] za,
			    double[] da,
			    float[] fa,
			    byte[] ba,
			    short[] sa,
			    long[] ja,
			    char[] ca,
			    String[] ta) {
    System.out.println("TestSignatureClass Created with " + ia + "\n" +
		       za + "\n" +
		       da + "\n" +
		       fa + "\n" +
		       ba + "\n" +
		       sa + "\n" +
		       ja + "\n" +
		       ca + "\n" +
		       ta + "\n" );
  }
  
  public void send(int i,
		   boolean z,
		   double d,
		   float f,
		   byte b,
		   short s,
		   long j,
		   char c,
		   String t) {
    System.out.println("TestSignatureClass.send " +  i + "\n" + 
		       z + "\n" + 
		       d + "\n" + 
		       f + "\n" +
		       s + "\n" + 
		       j + "\n" +
		       c + "\n" +
		       t + "\n");
  }

  public void send(int[] ia,
		   boolean[] za,
		   double[] da,
		   float[] fa,
		   byte[] ba,
		   short[] sa,
		   long[] ja,
		   char[] ca,
		   String[] ta) {
    System.out.println("TestSignatureClass.send with " + ia + "\n" +
		       za + "\n" +
		       da + "\n" +
		       fa + "\n" +
		       ba + "\n" +
		       sa + "\n" +
		       ja + "\n" +
		       ca + "\n" +
		       ta + "\n" );
  }

  public int retint(int v) {
    System.out.println("retint " + v);
    return v;
  }

  public double retdouble(double v) {
    System.out.println("retdouble" + v);
    return v;
  }

  public float retfloat(float v) {
    System.out.println("retfloat " + v);
    return v;
  }

  public long retlong(long v) { 
    System.out.println("retlong " + v);
    return v;
  }

  public boolean retboolean(boolean v) {
    System.out.println("retboolean " + v);
    return v;
  } 

  public short retshort(short v) {
    System.out.println("retshort " + v);
    return v;
  }

  public char retchar(char v) {
    System.out.println("retchar " + v);
    return v;
  }

  public byte retbyte(byte v) {
    System.out.println("retbyte " + v);
    return v;
  }

  public int[] retinta(int[] v) {
    System.out.println("retint[] " + v);
    return v;
  }

  public double[] retdoublea(double[] v) {
    System.out.println("retdouble[] " + v);
    return v;
  }

  public float[] retfloata(float[] v) {
    System.out.println("retfloat[] " + v);
    return v;
  }

  public long[] retlonga(long[] v) { 
    System.out.println("retlong[] " + v);
    return v;
  }

  public boolean[] retbooleana(boolean[] v) {
    System.out.println("retboolean[] " + v);
    return v;
  } 

  public short[] retshorta(short[] v) {
    System.out.println("retshort[] " + v);
    return v;
  }

  public char[] retchara(char[] v) {
    System.out.println("retchar[] " + v);
    return v;
  }

  public byte[] retbytea(byte[] v) {
    System.out.println("retbyte[] " + v);
    return v;
  }

  public Integer retInteger(Integer v) {
    System.out.println("retInteger " + v);
    return v;
  }

  public Double retDouble(Double v) {
    System.out.println("retDouble" + v);
    return v;
  }

  public Float retFloat(Float v) {
    System.out.println("retFloat " + v);
    return v;
  }

  public Long retLong(Long v) { 
    System.out.println("retLong " + v);
    return v;
  }

  public Boolean retBoolean(Boolean v) {
    System.out.println("retBoolean " + v);
    return v;
  } 

  public Short retShort(Short v) {
    System.out.println("retShort " + v);
    return v;
  }

  public Character retChararcter(Character v) {
    System.out.println("retCharacter " + v);
    return v;
  }

  public Byte retByte(Byte v) {
    System.out.println("retByte " + v);
    return v;
  }

  public String retString(String v) {
    System.out.println("retString " + v);
    return v;
  }
  
}
		       
			    
