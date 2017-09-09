
package com.gensym.beaneditor;

import java.awt.*;
import java.awt.event.*;
import java.io.*;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.g2script.Compiler;
import com.gensym.classtools.ClassInfo;
import javax.swing.JScrollPane;
import javax.swing.JSplitPane;
import javax.swing.JPanel;
import javax.swing.JLabel;
import javax.swing.JTextArea;
import javax.swing.ScrollPaneConstants;
import javax.swing.event.DocumentListener;
import javax.swing.event.DocumentEvent;

public class CustomHookupEditor extends Dialog {
  private boolean debug = false;
  private Panel infoPanel    = new Panel ();
  private Panel commandPanel = new Panel ();
  private JTextArea editField = new JTextArea ();
  private JTextArea diagnostics = new JTextArea ();
  private Button applyBtn, compileBtn, cancelBtn;
  private TextCompiler compiler = new TextCompiler ();
  private int syntax;
  private String lastGoodSourceCode = null;

  private String classFileName;
  private ClassInfo uncompiledClass;

  CustomHookupEditor (Frame parent, String title, String initialText,
		      int syntax, ClassInfo uncompiledClass) {
    super (parent, title, true);
    setLayout (new BorderLayout ());

    this.syntax = syntax;
    this.uncompiledClass = uncompiledClass;

    TextArea ta = new TextArea ();
    Font f = ta.getFont ();
    if (syntax == HookupFactory.JAVA)
      {
 	//editField.setFont(f);
 	//diagnostics.setFont(f);
	editField.setFont(new Font("Monospaced", Font.PLAIN, 12));
	diagnostics.setFont(new Font("Monospaced", Font.PLAIN, 12));
      }
    else
      {
	editField.setFont(new Font("SansSerif", Font.PLAIN, 14));
	diagnostics.setFont(new Font("SansSerif", Font.PLAIN, 14));
      }
    infoPanel.setLayout (new GridLayout (2, 1));
    infoPanel.add (editField);
    infoPanel.add (diagnostics);
    editField.setBackground (Color.white);
    diagnostics.setEditable (false);

    JScrollPane scroller0 = makeScrollPane (600, 500);
    scroller0.getViewport().add(editField);
    JScrollPane scroller1 = makeScrollPane (600, 150);
    JPanel diagnosticsP = new JPanel ();
    diagnosticsP.setLayout (new BorderLayout ());
    JLabel l;
    diagnosticsP.add (l = new JLabel ("Compiler Diagnostics:"), BorderLayout.NORTH);
    diagnosticsP.add (scroller1, BorderLayout.CENTER);
    scroller1.getViewport().add (diagnostics);

    JSplitPane sp = new JSplitPane (JSplitPane.VERTICAL_SPLIT,
				    scroller0, diagnosticsP);
    sp.setDividerSize (5);
    add (sp, BorderLayout.CENTER);
    //    add (infoPanel, "Center");

    commandPanel.setLayout (new FlowLayout (FlowLayout.CENTER));
    commandPanel.add (applyBtn   = new Button ("Apply"));
    commandPanel.add (compileBtn = new Button ("Compile"));
    commandPanel.add (cancelBtn  = new Button ("Cancel"));
    add (commandPanel, "South");
    
//     editField.addTextListener (new TextListener () {
//       public void textValueChanged (TextEvent te) {
// 	setDirty ();
//       }
//     });

    editField.getDocument().addDocumentListener (new DocumentListener () {
      @Override
      public void insertUpdate(DocumentEvent e)  {setDirty ();}
      @Override
      public void removeUpdate(DocumentEvent e)  {setDirty ();}
      @Override
      public void changedUpdate(DocumentEvent e) {setDirty ();}
    });

    ActionListener applyAdapter = (new ActionListener () {
      @Override
      public void actionPerformed (ActionEvent ae) {
	dismiss (true);
      }
    });

    ActionListener cancelAdapter = (new ActionListener () {
      @Override
      public void actionPerformed (ActionEvent ae) {
	dismiss (false);
      }
    });

    addWindowListener (new WindowAdapter () {
      @Override
      public void windowClosing (WindowEvent wEvt) {
	dismiss (false);
      }
    });

    applyBtn.addActionListener (applyAdapter);
    cancelBtn.addActionListener (cancelAdapter);
    compileBtn.addActionListener (new ActionListener () {
      @Override
      public void actionPerformed (ActionEvent aEvt) {
	compiler.compileText ();
      }
    });

    applyBtn.setEnabled (false);
    editField.setText (initialText);
    compiler.compileText ();
    pack ();
  }


  private JScrollPane makeScrollPane (int x, int y) {
    final int paneWidth = x, paneHeight = y;
    return new JScrollPane(ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS, ScrollPaneConstants.HORIZONTAL_SCROLLBAR_AS_NEEDED) {
      @Override
      public Dimension getPreferredSize() {
	return new Dimension(paneWidth, paneHeight);
      }
      @Override
      public Dimension getMinimumSize () {
	return new Dimension (100, 100);
      }
      @Override
      public float getAlignmentX() {
	return LEFT_ALIGNMENT;
      }
    };
  }


  private void clearDirty (String fileName) {
    compileBtn.setEnabled (false);
    applyBtn.setEnabled (true);
    classFileName = fileName;
  }

  private void setDirty () {
    compileBtn.setEnabled (true);
    applyBtn.setEnabled (false);
    classFileName = null;
  }

  private void dismiss (boolean success) {
    if (!success)
      lastGoodSourceCode = null;
    setVisible (false);
    dispose ();
  }

  public byte[] getCompiledClassBytes () {
    if (classFileName == null)
      return null;
    try {
      File cFile = new File (classFileName);
      int classFileLength = (int)cFile.length();
      byte[] classContents = new byte[classFileLength]; 
      DataInputStream CFStream = new DataInputStream (new FileInputStream (cFile));
      CFStream.readFully(classContents);
      return classContents;
    } catch (java.io.IOException ioe) {
      Trace.exception (ioe);
      return null;
    }
  }

  String getSourceCode()
  {
    return lastGoodSourceCode;
  }

  boolean editSucceeded()
  {
    return (lastGoodSourceCode != null);
  }

  public static void main (String[] args) {
    Window f = new CustomHookupEditor (new Frame (), "Test",
				       "public class Hello {}", HookupFactory.JAVA,
				       null);
    f.setVisible (true);
  }



  class TextCompiler {
    
    void compileText () {

      String sourceCode = editField.getText ();
      if (syntax == HookupFactory.JAVA)
	compileJavaText(sourceCode);
      else
	compileG2ScriptText(sourceCode);
    }

    void compileJavaText(String sourceCode) {
      int classStartIndex  = sourceCode.indexOf ("public class ");
      if (classStartIndex < 0) {
	diagnostics.setText ("Could not determine Java class name");
	return;
      }
      classStartIndex += 13;
      int classEndIndex = sourceCode.indexOf (' ', classStartIndex);
      if (debug)
	{
	  System.out.println ("Source code = " + sourceCode);
	  System.out.println ("StartIndex = " + classStartIndex + 
			      " EndIndex = " + classEndIndex);
	}
      String className = sourceCode.substring (classStartIndex, classEndIndex);
      if (debug)
	System.out.println ("Class is <" + className + ">");
      String javaFileName = HookupFactory.dirName + java.io.File.separator + className + ".java";

      try {
	File javaFile = new File (javaFileName);
	FileOutputStream fos = new FileOutputStream (javaFile);
	for (int i=0; i<sourceCode.length (); i++)
	  fos.write (sourceCode.charAt (i));
	fos.close ();
      } catch (java.io.IOException ioe) {
	Trace.exception(ioe);
	diagnostics.setText ("Error trying to write java file.\n" + ioe);
      }

      ByteArrayOutputStream byteStream = new ByteArrayOutputStream (5);
      sun.tools.javac.Main compiler = new sun.tools.javac.Main (byteStream, "javac");
      boolean success = compiler.compile (new String[] {"-classpath", G2JarLoader.extendedClassPath, javaFileName});
      if (debug)
	System.out.println ("Ran javac -classpath " + G2JarLoader.extendedClassPath + " " + javaFileName);
      byte[] compilerOutputBytes = byteStream.toByteArray ();
      String compilerOutput = new String (compilerOutputBytes);
      
      if (success)
	{
	  clearDirty (HookupFactory.dirName + 
		      java.io.File.separator + className + ".class");
	  lastGoodSourceCode = sourceCode;
	}
      else
	lastGoodSourceCode = null;
      
      diagnostics.setText (compilerOutput);
      
    }

    void compileG2ScriptText(String sourceCode) {
      Compiler compiler = new Compiler();
      String compileError = compiler.testCompileMethod(sourceCode,uncompiledClass);
      boolean success = compileError.equals("");
      
      if (success)
	{
	  lastGoodSourceCode = sourceCode;
	  clearDirty (HookupFactory.dirName + java.io.File.separator +
		      uncompiledClass.getClassName()+
		      ".class");
	}
      else
	{
	  lastGoodSourceCode = null;
	}
      diagnostics.setText (compileError);
      
    }
  }
  
}
