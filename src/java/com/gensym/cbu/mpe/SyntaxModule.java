package com.gensym.cbu.mpe;

import java.awt.*;
import java.awt.geom.*;
import javax.swing.*;
import java.io.Serializable;

import com.gensym.denali.model.*;
import com.gensym.denali.g2.*;
import com.gensym.denali.events.*;
import com.gensym.denali.graphics.*;
import com.gensym.denali.common.DirectionConstants;
import com.gensym.denali.common.ObservableExpression;

public class SyntaxModule implements Populator
{

  private static Object[] newFloatArray(float[] array)
  {
    int i,len = array.length;
    Float[] result = new Float[len];
    for (i=0; i<len; i++)
      result[i] = new Float(array[i]);
    return result;
  }

  private static StandardIconDefinition makeStateIcon()
  {
    PrimitiveIconElement fill
      = new PrimitiveIconElement("ellipse",
				 new SerializableGradientPaint(30.0f, 30.0f, Color.white,
							       60.0f, 60.0f, Color.blue,
							       true),
				 null,
				 new Object[] { new JavaExpression("0.1 * width"),
						  new JavaExpression("0.1 * height"),
						  new JavaExpression("0.8 * width"),
						  new JavaExpression("0.8 * height") },
				 false);
    PrimitiveIconElement fillOutline
      = new PrimitiveIconElement("ellipse",
				 Color.black,
				 null,
				 new Object[] { new JavaExpression("0.1 * width"),
						  new JavaExpression("0.1 * height"),
						  new JavaExpression("0.8 * width"),
						  new JavaExpression("0.8 * height") },
				 true);
    
    PrimitiveIconElement outline
      = new PrimitiveIconElement("ellipse",
				 new java.awt.Color(64,64,64),
				 null,
				 new Object[] { new Float(0.0f),
						  new Float(0.0f),
						  new JavaExpression("width"),
						  new JavaExpression("height") },
				 true);
    
    
    
    PrimitiveIconElement startNodeRegion
      = new PrimitiveIconElement("ellipse",
				 new JavaExpression("(start == true) ? " + 
						    "java.awt.Color.red : " +
						    "java.awt.Color.white"),
				 null,
				 new Object[] { new JavaExpression("0.05 * width"),
						  new JavaExpression("0.05 * height"),
						  new JavaExpression("0.9 * width"),
						  new JavaExpression("0.9 * height") },
				 false);
    
    PrimitiveIconElement terminalNodeRegion
      = new PrimitiveIconElement("ellipse",
				 new JavaExpression("(!terminalStateName.equals(\"\")) ? " +
						    "java.awt.Color.green : " + 
						    "java.awt.Color.white"),
				 null,
				 new Object[] { new Float(0.0f),
						  new Float(0.0f),
						  new JavaExpression("width"),
						  new JavaExpression("height") },
				 false);
    
    DefinitionParameter param3 = new DefinitionParameter("start", Boolean.TYPE, new Boolean(false));
    DefinitionParameter param2 = new DefinitionParameter("terminalStateName", String.class, "");
    DefinitionParameter param1 = new DefinitionParameter("tokenType", String.class, "");

    return new StandardIconDefinition("StateIcon",
				      new DefinitionParameter[] { param1, param2, param3}, 
				      new IconElement[] {terminalNodeRegion,
							   startNodeRegion, 
							   fill,
							   fillOutline,
							   outline});
  }
  
  private static StandardIconDefinition oldMakeStateIcon()
  {
    PrimitiveIconElement ie1
      = new PrimitiveIconElement("ellipse",
				 new SerializableGradientPaint(30.0f, 30.0f, Color.white,
							       60.0f, 60.0f, Color.blue,
							       true),
				 null,
				 new Object[] { new Float(0.0f),
						  new Float(0.0f),
						  new JavaExpression("width"),
						  new JavaExpression("height") },
				 false);
    PrimitiveIconElement ie2
      = new PrimitiveIconElement("ellipse",
				 Color.black,
				 null,
				 new Object[] { new Float(0.0f),
						  new Float(0.0f),
						  new JavaExpression("width"),
						  new JavaExpression("height") },
				 true);
    DefinitionParameter param1 = 
      new DefinitionParameter("tokenType", String.class, "");
    return new StandardIconDefinition("StateIcon",
				      new DefinitionParameter[] { param1}, 
				      new IconElement[] { ie1, ie2 });
  }

  private static StandardIconDefinition makeArtlessIcon(String name, String label)
  {
   PrimitiveIconElement ie1
      = new PrimitiveIconElement("rectangle",Color.gray,null,
			new Object[] { new Float(0.0f),
					new Float(0.0f),
					 new JavaExpression("width"),
					 new JavaExpression("height") },
			false);
    PrimitiveIconElement ie2
      = new PrimitiveIconElement("text",
				 Color.black,
				 null, // font override
				 new Object[] { label, 
						  new Float(5.0f), 
						  new Float(14.0f) },
				 false);
    return new StandardIconDefinition(name,
				      new DefinitionParameter[] {}, 
				      new IconElement[] { ie1, ie2 });
  }

  private static StandardIconDefinition makeMatcherIcon()
  {
    PrimitiveIconElement ie01
      =new PrimitiveIconElement("polygon",
				new java.awt.Color(205,92,92),
				null,
				new Object[] {new Integer(0),
						new JavaExpression("32/32.0 * height"),
						new JavaExpression("1/32.0 * width"),
						new JavaExpression("0/32.0 * height"),
						new JavaExpression("32/32.0 * width"),
						new JavaExpression("0/32.0 * height"),
						new JavaExpression("0/32.0 * width"),
						new JavaExpression("32/32.0 * height"),
						new JavaExpression("0/32.0 * width")},
				false);
    PrimitiveIconElement ie11
      =new PrimitiveIconElement("polygon",
				new java.awt.Color(50,205,50),
				null,
				new Object[] {new Integer(0),
						new JavaExpression("32/32.0 * height"),
						new JavaExpression("32/32.0 * width"),
						new JavaExpression("0/32.0 * height"),
						new JavaExpression("32/32.0 * width"),
						new JavaExpression("32/32.0 * height"),
						new JavaExpression("0/32.0 * width")},
				false);
    PrimitiveIconElement ie21
      =new PrimitiveIconElement("polyline",
				new java.awt.Color(255,0,0),
				null,
				new Object[] {new JavaExpression("16/32.0 * width"),
						new JavaExpression("9/32.0 * height"),
						new JavaExpression("15/32.0 * width"),
						new JavaExpression("5/32.0 * height"),
						new JavaExpression("15/32.0 * width"),
						new JavaExpression("3/32.0 * height"),
						new JavaExpression("16/32.0 * width"),
						new JavaExpression("2/32.0 * height"),
						new JavaExpression("18/32.0 * width"),
						new JavaExpression("3/32.0 * height"),
						new JavaExpression("18/32.0 * width"),
						new JavaExpression("5/32.0 * height"),
						new JavaExpression("16/32.0 * width"),
						new JavaExpression("8/32.0 * height")},
				true);
    PrimitiveIconElement ie22
      =new PrimitiveIconElement("polyline",
				new java.awt.Color(255,0,0),
				null,
				new Object[] {new JavaExpression("17/32.0 * width"),
						new JavaExpression("23/32.0 * height"),
						new JavaExpression("7/32.0 * width"),
						new JavaExpression("17/32.0 * height")},
				true);
    PrimitiveIconElement ie23
      =new PrimitiveIconElement("polyline",
				new java.awt.Color(255,0,0),
				null,
				new Object[] {new JavaExpression("25/32.0 * width"),
						new JavaExpression("17/32.0 * height"),
						new JavaExpression("19/32.0 * width"),
						new JavaExpression("15/32.0 * height"),
						new JavaExpression("16/32.0 * width"),
						new JavaExpression("10/32.0 * height")},
				true);
    PrimitiveIconElement ie24
      =new PrimitiveIconElement("polyline",
				new java.awt.Color(255,0,0),
				null,
				new Object[] {new JavaExpression("25/32.0 * width"),
						new JavaExpression("5/32.0 * height"),
						new JavaExpression("20/32.0 * width"),
						new JavaExpression("5/32.0 * height"),
						new JavaExpression("16/32.0 * width"),
						new JavaExpression("9/32.0 * height"),
						new JavaExpression("9/32.0 * width"),
						new JavaExpression("11/32.0 * height"),
						new JavaExpression("7/32.0 * width"),
						new JavaExpression("17/32.0 * height")},
				true);
    PrimitiveIconElement ie31
      =new PrimitiveIconElement("rectangle",
				new java.awt.Color(0,0,255),
				null,
				new Object[] {new JavaExpression("5/32.0 * width"),
						new JavaExpression("15/32.0 * height"),
						new JavaExpression("6/32.0 * width"),
						new JavaExpression("6/32.0 * height")},
				false);
    PrimitiveIconElement ie32
      =new PrimitiveIconElement("rectangle",
				new java.awt.Color(0,0,255),
				null,
				new Object[] {new JavaExpression("14/32.0 * width"),
						new JavaExpression("7/32.0 * height"),
						new JavaExpression("6/32.0 * width"),
						new JavaExpression("6/32.0 * height")},
				false);
    PrimitiveIconElement ie33
      =new PrimitiveIconElement("rectangle",
				new java.awt.Color(0,0,255),
				null,
				new Object[] {new JavaExpression("23/32.0 * width"),
						new JavaExpression("3/32.0 * height"),
						new JavaExpression("6/32.0 * width"),
						new JavaExpression("6/32.0 * height")},
				false);
    PrimitiveIconElement ie34
      =new PrimitiveIconElement("rectangle",
				new java.awt.Color(0,0,255),
				null,
				new Object[] {new JavaExpression("23/32.0 * width"),
						new JavaExpression("14/32.0 * height"),
						new JavaExpression("6/32.0 * width"),
						new JavaExpression("6/32.0 * height")},
				false);
    PrimitiveIconElement ie35
      =new PrimitiveIconElement("rectangle",
				new java.awt.Color(0,0,255),
				null,
				new Object[] {new JavaExpression("15/32.0 * width"),
						new JavaExpression("21/32.0 * height"),
						new JavaExpression("6/32.0 * width"),
						new JavaExpression("6/32.0 * height")},
				false);
    PrimitiveIconElement ie41
      =new PrimitiveIconElement("polygon",
				new java.awt.Color(0,0,0),
				null,
				new Object[] {new Integer(0),
						new JavaExpression("0/32.0 * height"),
						new JavaExpression("0/32.0 * width"),
						new JavaExpression("0/32.0 * height"),
						new JavaExpression("32/32.0 * width"),
						new JavaExpression("32/32.0 * height"),
						new JavaExpression("32/32.0 * width"),
						new JavaExpression("32/32.0 * height"),
						new JavaExpression("0/32.0 * width")},
				true);

    return new StandardIconDefinition("MatcherIcon",
				      null,
				      new IconElement[] {ie01,
							   ie11,
							   ie21,ie22,ie23,ie24,
							   ie31,ie32,ie33,ie34,ie35,
							   ie41});
  }

  private static StandardIconDefinition makeTesterIcon()
  {
    PrimitiveIconElement ie1 
      = new PrimitiveIconElement("rectangle",
				 new java.awt.Color(192,64,64),
				 null,
				 new Object[] { new Float(0.0f),
						  new Float(0.0f),
						  new JavaExpression("width"),
						  new JavaExpression("height") },
				 false);

    PrimitiveIconElement ie2
      = new PrimitiveIconElement("polygon",
                                 Color.black, 
                                 null,
				 new Object[] { new Integer(0),
						  new JavaExpression("0.15 * width"),
						  new JavaExpression("0.35 * height"),
						  new JavaExpression("0.65 * width"),
						  new JavaExpression("0.35 * height"),
						  new JavaExpression("0.65 * width"),
						  new JavaExpression("0.15 * height"),
						  new JavaExpression("0.85 * width"),
						  new JavaExpression("0.5 * height"),
						  new JavaExpression("0.65 * width"),
						  new JavaExpression("0.85 * height"),
						  new JavaExpression("0.65 * width"),
						  new JavaExpression("0.65 * height"),
						  new JavaExpression("0.15 * width"),
						  new JavaExpression("0.65 * height")},
                                 false);

    return new StandardIconDefinition("TesterIcon",
				      new DefinitionParameter[] {}, 
				      new IconElement[] { ie1, ie2 });

  }

  private static StandardIconDefinition makeLexerIcon()
  {
    PrimitiveIconElement ie01
      =new PrimitiveIconElement("rectangle",
				new java.awt.Color(229,229,229),
				null,
				new Object[] {new JavaExpression("0/32.0 * width"),
						new JavaExpression("0/32.0 * height"),
						new JavaExpression("33/32.0 * width"),
						new JavaExpression("33/32.0 * height")},
				false);
    PrimitiveIconElement ie11
      =new PrimitiveIconElement("polyline",
				new java.awt.Color(255,0,0),
				null,
				new Object[] {new JavaExpression("16/32.0 * width"),
						new JavaExpression("9/32.0 * height"),
						new JavaExpression("15/32.0 * width"),
						new JavaExpression("5/32.0 * height"),
						new JavaExpression("15/32.0 * width"),
						new JavaExpression("3/32.0 * height"),
						new JavaExpression("16/32.0 * width"),
						new JavaExpression("2/32.0 * height"),
						new JavaExpression("18/32.0 * width"),
						new JavaExpression("3/32.0 * height"),
						new JavaExpression("18/32.0 * width"),
						new JavaExpression("5/32.0 * height"),
						new JavaExpression("16/32.0 * width"),
						new JavaExpression("8/32.0 * height")},
				true);
    PrimitiveIconElement ie12
      =new PrimitiveIconElement("polyline",
				new java.awt.Color(255,0,0),
				null,
				new Object[] {new JavaExpression("17/32.0 * width"),
						new JavaExpression("23/32.0 * height"),
						new JavaExpression("7/32.0 * width"),
						new JavaExpression("17/32.0 * height")},
				true);
    PrimitiveIconElement ie13
      =new PrimitiveIconElement("polyline",
				new java.awt.Color(255,0,0),
				null,
				new Object[] {new JavaExpression("25/32.0 * width"),
						new JavaExpression("17/32.0 * height"),
						new JavaExpression("19/32.0 * width"),
						new JavaExpression("15/32.0 * height"),
						new JavaExpression("16/32.0 * width"),
						new JavaExpression("10/32.0 * height")},
				true);
    PrimitiveIconElement ie14
      =new PrimitiveIconElement("polyline",
				new java.awt.Color(255,0,0),
				null,
				new Object[] {new JavaExpression("25/32.0 * width"),
						new JavaExpression("5/32.0 * height"),
						new JavaExpression("20/32.0 * width"),
						new JavaExpression("5/32.0 * height"),
						new JavaExpression("16/32.0 * width"),
						new JavaExpression("9/32.0 * height"),
						new JavaExpression("9/32.0 * width"),
						new JavaExpression("11/32.0 * height"),
						new JavaExpression("7/32.0 * width"),
						new JavaExpression("17/32.0 * height")},
				true);
    PrimitiveIconElement ie21
      =new PrimitiveIconElement("rectangle",
				new java.awt.Color(0,0,255),
				null,
				new Object[] {new JavaExpression("5/32.0 * width"),
						new JavaExpression("15/32.0 * height"),
						new JavaExpression("6/32.0 * width"),
						new JavaExpression("6/32.0 * height")},
				false);
    PrimitiveIconElement ie22
      =new PrimitiveIconElement("rectangle",
				new java.awt.Color(0,0,255),
				null,
				new Object[] {new JavaExpression("14/32.0 * width"),
						new JavaExpression("7/32.0 * height"),
						new JavaExpression("6/32.0 * width"),
						new JavaExpression("6/32.0 * height")},
				false);
    PrimitiveIconElement ie23
      =new PrimitiveIconElement("rectangle",
				new java.awt.Color(0,0,255),
				null,
				new Object[] {new JavaExpression("23/32.0 * width"),
						new JavaExpression("3/32.0 * height"),
						new JavaExpression("6/32.0 * width"),
						new JavaExpression("6/32.0 * height")},
				false);
    PrimitiveIconElement ie24
      =new PrimitiveIconElement("rectangle",
				new java.awt.Color(0,0,255),
				null,
				new Object[] {new JavaExpression("23/32.0 * width"),
						new JavaExpression("14/32.0 * height"),
						new JavaExpression("6/32.0 * width"),
						new JavaExpression("6/32.0 * height")},
				false);
    PrimitiveIconElement ie25
      =new PrimitiveIconElement("rectangle",
				new java.awt.Color(0,0,255),
				null,
				new Object[] {new JavaExpression("15/32.0 * width"),
						new JavaExpression("21/32.0 * height"),
						new JavaExpression("6/32.0 * width"),
						new JavaExpression("6/32.0 * height")},
				false);
    PrimitiveIconElement ie31
      =new PrimitiveIconElement("polygon",
				new java.awt.Color(0,0,0),
				null,
				new Object[] {new Integer(0),
						new JavaExpression("0/32.0 * height"),
						new JavaExpression("0/32.0 * width"),
						new JavaExpression("0/32.0 * height"),
						new JavaExpression("32/32.0 * width"),
						new JavaExpression("32/32.0 * height"),
						new JavaExpression("32/32.0 * width"),
						new JavaExpression("32/32.0 * height"),
						new JavaExpression("0/32.0 * width")},
				true);

    return new StandardIconDefinition("LexerDefIcon",
				      null,
				      new IconElement[] {ie01,
							   ie11,ie12,ie13,ie14,
							   ie21,ie22,ie23,ie24,ie25,
							   ie31});

  }

  private static StandardConnectionDefinition makeGeneralConnection(String name,
								    Color fillColor,
								    int joinStyle,
								    float[] dashPattern,
								    int curvature)
  {
    
    DefinitionParameter param = 
      new DefinitionParameter("label",String.class, "");
    return new GeneralConnectionDefinition(name,
					   new DefinitionParameter[] { param },
					   6,
					   new SerializableGradientPaint(0.0f, 0.0f,
									 fillColor,
									 100.0f, 100.0f, 
									 Color.orange,
									 true),
					   1,
					   Color.black,
					   joinStyle,
					   dashPattern,
					   curvature,
					   new DefinitionParameterReference("label"),
					   new Font("SansSerif", Font.PLAIN, 24));
  }


  public void populate(ServerImpl server)
  {
    try {
      String moduleName = "com.gensym.denali.modules.Syntax";
      Module m = new ModuleImpl(moduleName);
      server.addModule(m);
      // initialize icon definitions
      m.setSharedDefinition(makeStateIcon());
      m.setSharedDefinition(makeMatcherIcon());
      m.setSharedDefinition(makeTesterIcon());
      m.setSharedDefinition(makeLexerIcon());
      //m.setSharedDefinition(makeArtlessIcon("LexerDefIcon", "LEXER DEF'N"));
      //m.setSharedDefinition(makeArtlessIcon("MatcherIcon", "MATCHER"));
      //m.setSharedDefinition(makeArtlessIcon("TesterIcon", "TESTER"));

      // allow classes in module
      m.addClass(NDFAState.class);

      ConnectionDefinition transitionConnectionGraphics
	= makeGeneralConnection("GreenConPattern",Color.green,
				java.awt.BasicStroke.JOIN_MITER, null,
				GeneralConnectionDefinition.CUBIC);
      m.setSharedDefinition(transitionConnectionGraphics);

      ConnectionDefinition testerConnectionGraphics
	= makeGeneralConnection("BlueConPattern",Color.blue,
				java.awt.BasicStroke.JOIN_MITER, null,
				GeneralConnectionDefinition.LINEAR);
      m.setSharedDefinition(testerConnectionGraphics);

      ConnectionDefinition matcherConnectionGraphics
	= makeGeneralConnection("RedConPattern",Color.blue,
				java.awt.BasicStroke.JOIN_MITER, null,
				GeneralConnectionDefinition.LINEAR);
      m.setSharedDefinition(matcherConnectionGraphics);
      
      ConnectionConfiguration transitionConnectionConfiguration
	= new ConnectionConfiguration("TransitionConnection",
				      "com.gensym.denali.model.DirectedConnection",
				      new SharedDefinitionReference(m.getName(),
								    "GreenConPattern"),
				      "com.gensym.cbu.mpe.TransitionSpecification",
				      false,
				      new String[] { "stringToMatch" },
				      new String[] { "label" },
				      null);
      m.setSharedDefinition(transitionConnectionConfiguration);
      
      PortConfiguration transitionInputConfiguration
	= new PortConfiguration("TransitionInputPort",
				new SharedDefinitionReference(m.getName(),"TransitionConnection"),
				true,
				true,
				true,
				50,
				25,
				DirectionConstants.RIGHT);
      m.setSharedDefinition(transitionInputConfiguration);

      PortConfiguration transitionOutputConfiguration
	= new PortConfiguration("TransitionOutputPort",
				new SharedDefinitionReference(m.getName(),
							      "TransitionConnection"),
				false,
				true,
				false,
				0,
				25,
				DirectionConstants.LEFT);
      m.setSharedDefinition(transitionOutputConfiguration);

      NodeConfiguration stateNodeConfiguration
	= new NodeConfiguration("StateNode",
				"com.gensym.denali.model.StandardIconicNode",
				true,
				"com.gensym.cbu.mpe.NDFAState",
				"com.gensym.denali.graphics.StandardIcon",
				new SharedDefinitionReference(m.getName(),"StateIcon"),
				null,
				null,
				null,
				null, // initial Ports
				new SharedDefinitionReference[]
				{ 
				  new SharedDefinitionReference(m.getName(),
								"TransitionOutputPort")},
				new SharedDefinitionReference[]
				{ new SharedDefinitionReference(m.getName(),
								"TransitionInputPort")},
				null,
				null);
      m.setSharedDefinition(stateNodeConfiguration);

      JavaStatement showStatement
	= new JavaStatement("node.showSubContainer(node.getOrMakeSubContainer(\"details\","+
			    "\"com.gensym.cbu.mpe.DefinitionSchematicImpl\"),"+
			    "null);");
      
      JavaCommand lexerDefCommands
	= new JavaCommand (new String[] { "details" },
                           new JavaStatement[] { showStatement },
			   "com.gensym.cbu.mpe",
			   "MenuLabels");
      m.setSharedDefinition("LexerDefCommands",lexerDefCommands);

      NodeConfiguration lexerDefConfiguration
	= new NodeConfiguration("LexerDefNode",
				"com.gensym.denali.model.StandardIconicNode",
				true,
				"com.gensym.cbu.mpe.LexerDefinition",
				"com.gensym.denali.graphics.StandardIcon",
				new SharedDefinitionReference(m.getName(),"LexerDefIcon"),
				null,
				null,
				null,
				null, // initial Ports
				null,
				null,
				new SharedDefinitionReference[] 
				{ new SharedDefinitionReference(m.getName(),
								"LexerDefCommands")},
				null);
      m.setSharedDefinition(lexerDefConfiguration);
      
      JavaStatement testStatement
	= new JavaStatement("node.propagateValue(\"port1\",null);");
      
      JavaCommand testerCommands
	= new JavaCommand (new String[] { "test" },
                           new JavaStatement[] { testStatement },
			   "com.gensym.cbu.mpe",
			   "MenuLabels");
      m.setSharedDefinition("TesterCommands",testerCommands);

      String sc1
	=
	"((com.gensym.cbu.mpe.DFAMatcher)outputBean)."+
	"matchAll(new java.io.StringReader(((com.gensym.cbu.mpe.Tester)inputBean)"+
	".getText()),false)";
      
      ConnectionConfiguration testerConnectionConfiguration
	= new ConnectionConfiguration("TesterConnection",
				      "com.gensym.denali.model.DirectedConnection",
				      new SharedDefinitionReference(m.getName(),
								    "BlueConPattern"),
				      new BeanRecipe("com.gensym.denali.model.ContinuousValuePropagator",
						     new String[] { "expression"},
						     new Serializable[] { new JavaExpression(sc1) }),
				      true,
				      null,
				      null,
				      null);
      m.setSharedDefinition(testerConnectionConfiguration);

      PortConfiguration matcherPortConfiguration
	= new PortConfiguration("MatcherInputPort",
				new SharedDefinitionReference(m.getName(),
							      "TesterConnection"),
				true,
				true,
				true,
				25,
				50,
				DirectionConstants.LEFT);
      m.setSharedDefinition(matcherPortConfiguration);

      String matcherHookupSource
	=
	"{ \n"+
	"  ((com.gensym.cbu.mpe.LoggingAdapter)target)\n"+
	"  .extendLog(\"\"+event);"+
	"}\n";

      HookupSpecification hookup1
	= new HookupSpecification("com.gensym.cbu.mpe.DFAMatcher",
				  "com.gensym.cbu.mpe.LoggingAdapter",
				  "match",
				  "matchFound",
				  // here, what to say
				  matcherHookupSource);


      ConnectionConfiguration matcherConnectionConfiguration
	= new ConnectionConfiguration("MatcherConnection",
				      "com.gensym.denali.model.DirectedConnection",
				      new SharedDefinitionReference(m.getName(),
								    "RedConPattern"),
				      new BeanRecipe("com.gensym.denali.model.EventPropagator",
						     new String[] { "hookupSpecification" },
						     new Serializable[] { hookup1 }),
				      true,
				      null,
				      null,
				      null);
      m.setSharedDefinition(matcherConnectionConfiguration);

      PortConfiguration matcherOutputPortConfiguration
	= new PortConfiguration("MatcherOutputPort",
				new SharedDefinitionReference(m.getName(),
							      "MatcherConnection"),
				false,
				true,
				true,
				50,
				25,
				DirectionConstants.RIGHT);
      m.setSharedDefinition(matcherOutputPortConfiguration);

      NodeConfiguration matcherConfiguration
	= new NodeConfiguration("MatcherNode",
				"com.gensym.denali.model.StandardIconicNode",
				true,
				"com.gensym.cbu.mpe.DFAMatcher",
				"com.gensym.denali.graphics.StandardIcon",
				new SharedDefinitionReference(m.getName(),"MatcherIcon"),
				null,
				null,
				null,
			        // initial Ports
				new SharedDefinitionReference[] 
				{ new SharedDefinitionReference(m.getName(),"MatcherOutputPort")},
				null,
				new SharedDefinitionReference[] 
				{ new SharedDefinitionReference(m.getName(),"MatcherInputPort")},
				null,
				null);
      m.setSharedDefinition(matcherConfiguration);

      PortConfiguration testerPortConfiguration
	= new PortConfiguration("TesterPort",
				new SharedDefinitionReference(m.getName(),
							      "TesterConnection"),
				false,
				true,
				true,
				25,
				50,
				DirectionConstants.RIGHT);
      m.setSharedDefinition(testerPortConfiguration);

      NodeConfiguration testerConfiguration
	= new NodeConfiguration("testerNode",
				"com.gensym.denali.model.StandardIconicNode",
				true,
				"com.gensym.cbu.mpe.Tester",
				"com.gensym.denali.graphics.StandardIcon",
				new SharedDefinitionReference(m.getName(),"TesterIcon"),
				null,
				null,
				new String[] { "port1" },
				new SharedDefinitionReference[]
				{ 
				  new SharedDefinitionReference(m.getName(),
								"TesterPort")},
				null,
				null,
				new SharedDefinitionReference[] 
				{ new SharedDefinitionReference(m.getName(),
								"TesterCommands")},
				null);
      m.setSharedDefinition(testerConfiguration);

      PortConfiguration buttonOutput
	= new PortConfiguration("ButtonOutputPort",
				new SharedDefinitionReference
				(m.getName(),"EventConnection"),
				false,
				true,
				false,
				40,
				40,
				DirectionConstants.BOTTOM);
      m.setSharedDefinition(buttonOutput);

      NodeConfiguration buttonConfiguration
	= new NodeConfiguration("ActionButton",
				"com.gensym.denali.model.BeanProxyNode",
				false,
				null,
				"javax.swing.JButton",
				null,
				null,
				null,
				null,
				new SharedDefinitionReference[]
				{ 
				  new SharedDefinitionReference(m.getName(),
								"ButtonOutputPort")
				    },
				null,
				null,
				null,
				null);
      m.setSharedDefinition(buttonConfiguration);

      PortConfiguration textAreaInput
	= new PortConfiguration("TextAreaInputPort",
				new SharedDefinitionReference
				(m.getName(),"MatcherConnection"),
				true,
				true,
				false,
				0,
				40,
				DirectionConstants.LEFT);
      m.setSharedDefinition(textAreaInput);

      NodeConfiguration textAreaConfiguration
	= new NodeConfiguration ("TextArea",
				 "com.gensym.denali.model.DataNodeImpl",
				 true,
				 new BeanRecipe("com.gensym.cbu.mpe.LoggingAdapter"),
				 new BeanRecipe("com.gensym.denali.graphics.StandardText",
						new String[] { "verticalScrollBarPolicy",
								 "opaque" },
						new Serializable[]
						{ new Integer(JScrollPane.
							      VERTICAL_SCROLLBAR_ALWAYS),
						    new Boolean(true) }),
				 null,
				 null,
				 null,
				 null,
				 new SharedDefinitionReference[]
				 { 
				   new SharedDefinitionReference(m.getName(),
								 "TextAreaInputPort")
				     },
				 null,
				 null,
				 null,
				 null);
      textAreaConfiguration.setPreferredSize(new Dimension(300,100));
      m.setSharedDefinition(textAreaConfiguration);

      Schematic w = new SchematicImpl(m,"TEST-WS");
      w.setBounds(new NodeVisualInfo(0,0,700,500));
      m.addRoot(w);
    }
    catch (Exception e)
      {
	System.out.println("trouble populating test module");
	e.printStackTrace();
      }
  }

  static JEditorPane theEditor = new JEditorPane();

  static Dimension getSizeOfTextBox(String text)
  {
    Toolkit toolkit = Toolkit.getDefaultToolkit();
    FontMetrics metrics = toolkit.getFontMetrics(theEditor.getFont());
    return new Dimension(metrics.stringWidth(text)+17, // fudge for scroll bar width
			 metrics.getHeight() + 10); // fudge from HELL!
  }

}
