package com.gensym.devtools;

import java.io.*;
import java.nio.charset.Charset;

public class StripUndocumentedMembers {

  
  private static final String 
    CR = "\n", semiColon = ";", openParen = "{", closeParen = "}", equalSign = "=",
    regCommentStart = "/*", docCommentStart = "/**", commentEnd = "*/",
    undocumentedTag = "@undocumented",
    publicModifier = "public", protectedModifier = "protected", privateModifier = "private";
  private static final int NONE = 0, FIELD = 1, METHOD = 2;

  /**
   * Takes one argument which names a Java source code file that is to
   * be stripped of members with @undocumented tags
   */
  public static void main (String[] args) throws IOException {
    if (args.length != 1) {
    	throw new IllegalArgumentException ("Usage: StripUndocumentedMembers <java file>");
    }
    String fileName = args[0];
    File javaFile   = new File (fileName);
    
    if (javaFile.isDirectory()) {
      stripDirectoryFiles(javaFile);
    }
    else if (!javaFile.isDirectory()){
      stripFile(javaFile);
    }
  }
  
  private static void stripDirectoryFiles(File sourceDir) {
    String dirList[] = sourceDir.list();
    if (dirList == null) {
    	return;
    }
    for (int i=0; i<dirList.length; i++) {
      String filename = dirList[i];
      String targetFilename = sourceDir.getAbsolutePath()+File.separator+filename;
      File sourceFile = new File(targetFilename);        
      if (sourceFile.isDirectory()){
        System.out.println("**directory: " + targetFilename);
        stripDirectoryFiles(sourceFile);
      }
      else if (targetFilename.lastIndexOf(".java") > 1) {
        System.out.println("Editing file: " + targetFilename);
        stripFile(sourceFile);
	    }
    }
  }
  
  private static void stripFile (File javaFile) {
    int fileLength  = (int)javaFile.length ();
    FileInputStream fio = null;
    FileOutputStream foo = null;
    try {
      fio = new FileInputStream (javaFile);
    }
    catch (FileNotFoundException e) {
      System.out.println(e);
    }
    byte[] fileContents = new byte[fileLength];
    try {
      fio.read (fileContents);
      fio.close ();
    }
    catch (IOException e) {
      System.out.println(e);
    }

    String sourceCode = new String (fileContents, Charset.defaultCharset());
    StripUndocumentedMembers stripper = new StripUndocumentedMembers (sourceCode);
    stripper.strip ();
    sourceCode = stripper.sourceCode;
    try {
      foo = new FileOutputStream (javaFile);
      foo.write (sourceCode.getBytes (Charset.defaultCharset()));
      foo.close ();
    }
    catch (IOException e) {
      System.out.println(e);
    }
  }

  private StripUndocumentedMembers (String sourceCode) {
    this.sourceCode = sourceCode;
    codeBuffer = new StringBuffer (sourceCode);
  }

  private int curPosn = 0;
  private int extraChars  = 0;	// can be negative

  private StringBuffer codeBuffer;
  private String sourceCode;

  private void strip () {

    int tagIndex;
    while ((tagIndex = sourceCode.indexOf (undocumentedTag, curPosn)) > 0) {
      System.out.println("comment start " + tagIndex);
      stripOneMember (tagIndex);
    }
    sourceCode = codeBuffer.toString ();
  }

  private void stripOneMember (int tagIndex) {
    int prevCommentStartIndex = sourceCode.lastIndexOf (docCommentStart, tagIndex);
    int prevCommentEndIndex   = sourceCode.indexOf (commentEnd, prevCommentStartIndex);
    if (prevCommentStartIndex < tagIndex && tagIndex < prevCommentEndIndex) {
      curPosn = prevCommentEndIndex + 2; // The */
      int nextDocCommentStartIndex = sourceCode.indexOf (docCommentStart, prevCommentEndIndex);
      //if (nextDocCommentStartIndex > 0) {
        //System.out.println("found a next comment");
        StrippedMethodInfo member = readMemberIfAny (nextDocCommentStartIndex);
        if (member != null)
	        makePrivateIfNecessary (member);
      //else {
        //System.out.println("no more comments");
        //makePrivateIfNecessary (readMethod());
      //}
        System.out.println ("After Stripping cursor = " + curPosn);
      //}
    } else
      curPosn += 13;		// "@undocumented"
  }

  private StrippedMethodInfo readMemberIfAny (int limit) {
    int nextMemberType = determineMemberType (limit);
    if (nextMemberType == 0)
      return null;
    return (nextMemberType == FIELD ? readField () : readMethod ());
  }

  private int determineMemberType (int limit) {
    int scIndex = sourceCode.indexOf (semiColon, curPosn);
    int opIndex = sourceCode.indexOf (openParen, curPosn);
    int clIndex = sourceCode.indexOf (closeParen, curPosn);
    int eqIndex = sourceCode.indexOf (equalSign, curPosn);
    int type;
    
    boolean methodIndex = (opIndex < scIndex && (eqIndex < 0 || opIndex < eqIndex));
    if (scIndex < 0 && opIndex < 0)
      type = NONE;
    else if (opIndex >= 0 && (scIndex < 0 || methodIndex))
      type = (opIndex < limit ? METHOD : NONE);
    else
      type = (scIndex < limit ? FIELD : NONE);
    return type;
  }

  private StrippedMethodInfo readField () {
    int scIndex = sourceCode.indexOf (semiColon, curPosn);
    String field = sourceCode.substring (curPosn, scIndex).trim ();
    StrippedMethodInfo member = new StrippedMethodInfo (FIELD, field);
    return member;
  }

  private StrippedMethodInfo readMethod () {
    int posn = sourceCode.indexOf (openParen, curPosn) + 1;
    String method = sourceCode.substring (curPosn, posn).trim ();
    StrippedMethodInfo member = new StrippedMethodInfo (METHOD, method);
    return member;
  }

  private void makePrivateIfNecessary (StrippedMethodInfo member) {
    System.out.println ("Trying to make " + member.declaration + " PRIVATE!");
    String declaration = member.declaration;
    int memberIndex = sourceCode.indexOf (declaration, curPosn);
    System.out.println ("MemberIndex = " + memberIndex);
    System.out.println ("CursorPosn  = " + curPosn);
    int posnIndex;
    if ((posnIndex = declaration.indexOf (privateModifier)) >= 0) {
      // Do Nothing
    } else if ((posnIndex = declaration.indexOf (publicModifier)) >= 0) {
      posnIndex = memberIndex + posnIndex + extraChars;
      codeBuffer.setCharAt (posnIndex++, 'p');
      codeBuffer.setCharAt (posnIndex++, 'r'); // u
      codeBuffer.setCharAt (posnIndex++, 'i'); // b
      codeBuffer.setCharAt (posnIndex++, 'v'); // l
      codeBuffer.setCharAt (posnIndex++, 'a'); // i
      codeBuffer.setCharAt (posnIndex++, 't'); // c
      codeBuffer.insert (posnIndex, "e");
      extraChars += 1;
    } else if ((posnIndex = declaration.indexOf (protectedModifier)) >= 0) {
      posnIndex = memberIndex + posnIndex + extraChars;
      codeBuffer.setCharAt (posnIndex++, 'p');
      codeBuffer.setCharAt (posnIndex++, 'r'); // r
      codeBuffer.setCharAt (posnIndex++, 'i'); // o
      codeBuffer.setCharAt (posnIndex++, 'v'); // t
      codeBuffer.setCharAt (posnIndex++, 'a'); // e
      codeBuffer.setCharAt (posnIndex++, 't'); // c
      codeBuffer.setCharAt (posnIndex++, 'e'); // t
      codeBuffer.setCharAt (posnIndex++, ' '); // e
      codeBuffer.setCharAt (posnIndex++, ' '); // d
    } else {
      codeBuffer.insert (curPosn + extraChars, "private ");
      extraChars += 8;
    }
    System.out.println (" Extra chars = " + extraChars);
  }

}

class StrippedMethodInfo {
  int type;
  String declaration;

  StrippedMethodInfo (int type, String declaration) {
    this.type = type;
    this.declaration = declaration;
  }
}
