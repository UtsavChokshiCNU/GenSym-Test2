package com.gensym.cbu.odie;

import java.awt.*;
import com.gensym.denali.model.*;
import com.gensym.denali.graphics.*;
import java.io.Serializable;
import com.gensym.denali.events.HookupSpecification;
import com.gensym.cbu.odieeventfilterlanguage.EventFilterSchematicImpl;

public class OdiePopulator implements Populator
{
  public void populate(ServerImpl server)
  {
    try {
      Module m = new ModuleImpl("com.gensym.cbu.modules.odie");
      server.addModule(m);
    
      JavaCommand javaCommand2 = new JavaCommand(
        new String[] {"respond"},
          new JavaStatement[] {
            new JavaStatement("((com.gensym.cbu.odie.Response)bean).respond((com.gensym.cbu.odie.OdieEvent)new com.gensym.cbu.odie.OdieEventImpl(\"testEventType\",\"target id\",\"sender id\",\"hello\",\"world\",null,null,null),(com.gensym.cbu.odie.Manager)new com.gensym.cbu.odie.ManagerImpl(\"MenuManager\"));", null)
          },
        "com.gensym.cbu.odie",
        "ResponseMenuLabels");
        m.setSharedDefinition("ResponseCommands", javaCommand2);
      JavaCommand javaCommand12 
	= new JavaCommand(new String[] {"ConfigureEventFilter"},
	new JavaStatement[] {
	  new JavaStatement("node.showSubContainer(node.getOrMakeSubContainer(\"details\","+
			    "\"com.gensym.cbu.odieeventfilterlanguage.EventFilterSchematicImpl\"),"+
			    "null);", null)
	    },
        "com.gensym.cbu.odie",
        "SubscriberMenuLabels");
        m.setSharedDefinition("SubscriberCommands", javaCommand12);
      PortConfiguration portConfiguration3 = new PortConfiguration(
        "OslOutputPort",
        new SharedDefinitionReference("com.gensym.cbu.modules.odie", "OslConnection"),
        false,
        true,
        true,
        50,
        0,
        2);
        m.setSharedDefinition(portConfiguration3);
      StandardIconDefinition iconDefinition4 = new StandardIconDefinition(
        "OdieTesterIcon",
        new DefinitionParameter[] {
        new DefinitionParameter("name",String.class, "")},
        new IconElement[] {
          new PrimitiveIconElement(
            "rectangle",
            new Color(192, 64, 64, 255),
            null,
            new Object[] {
              new Float(0.0),
              new Float(0.0),
              new JavaExpression("width", null),
              new JavaExpression("height", null)},
            false),
          new PrimitiveIconElement(
            "polygon",
            new Color(0, 0, 0, 255),
            null,
            new Object[] {
              new Integer(0),
              new JavaExpression("0.15 * width", null),
              new JavaExpression("0.35 * height", null),
              new JavaExpression("0.65 * width", null),
              new JavaExpression("0.35 * height", null),
              new JavaExpression("0.65 * width", null),
              new JavaExpression("0.15 * height", null),
              new JavaExpression("0.85 * width", null),
              new JavaExpression("0.5 * height", null),
              new JavaExpression("0.65 * width", null),
              new JavaExpression("0.85 * height", null),
              new JavaExpression("0.65 * width", null),
              new JavaExpression("0.65 * height", null),
              new JavaExpression("0.15 * width", null),
              new JavaExpression("0.65 * height", null)},
            false)});
        m.setSharedDefinition(iconDefinition4);
      JavaCommand javaCommand8 = new JavaCommand(
        new String[] {"defineEventTypeTest", "publishNewEventTest"},
          new JavaStatement[] {
            new JavaStatement("((com.gensym.cbu.odie.OdieTester)bean).defineEventTypeTest();", null), 
            new JavaStatement("((com.gensym.cbu.odie.OdieTester)bean).publishNewEventTest();", null)
          },
        "com.gensym.cbu.odie",
        "OdieTesterMenuLabels");
        m.setSharedDefinition("OdieTesterCommands", javaCommand8);
      NodeConfiguration nodeConfiguration14 = new NodeConfiguration(
        "DialogResponse",
        "com.gensym.denali.model.StandardIconicNode",
        true,
        new BeanRecipe("com.gensym.cbu.odie.DialogResponse"),
        new BeanRecipe("com.gensym.denali.graphics.StandardIcon"),
        new SharedDefinitionReference("com.gensym.cbu.modules.odie", "DialogResponseIcon"),
        new String[] {"name"},
        new String[] {"name"},
        null,
        new SharedDefinitionReference[] {new SharedDefinitionReference("com.gensym.cbu.modules.odie", "OslInputPort")},
        new SharedDefinitionReference[] {new SharedDefinitionReference("com.gensym.cbu.modules.odie", "OslInputPort")},
        new SharedDefinitionReference[] {new SharedDefinitionReference("com.gensym.cbu.modules.odie", "OslInputPort")},
        null,
        null);
        nodeConfiguration14.setPreferredSize(new Dimension(32,32));
        nodeConfiguration14.setShowInPalettes(true);
        m.setSharedDefinition(nodeConfiguration14);
      StandardIconDefinition iconDefinition15 = new StandardIconDefinition(
        "SmtpResponseIcon",
        new DefinitionParameter[] {
        new DefinitionParameter("name",String.class, "")},
        new IconElement[] {
          new PrimitiveIconElement(
            "rectangle",
            new Color(0, 0, 0, 255),
            null,
            new Object[] {
              new Float(0.0),
              new Float(0.0),
              new JavaExpression("width - 1", null),
              new JavaExpression("height - 1", null)},
            true),
          new PrimitiveIconElement(
            "rectangle",
            new Color(128, 128, 128, 255),
            null,
            new Object[] {
              new JavaExpression("0.1 * width", null),
              new JavaExpression("0.1 * height", null),
              new JavaExpression("0.8 * width", null),
              new JavaExpression("0.8 * height", null)},
            false),
          new PrimitiveIconElement(
            "polyline",
            new Color(0, 0, 0, 255),
            null,
            new Object[] {
              new JavaExpression("0.1 * width", null),
              new JavaExpression("0.1 * height", null),
              new JavaExpression("0.9 * width", null),
              new JavaExpression("0.1 * height", null),
              new JavaExpression("0.9 * width", null),
              new JavaExpression("0.9 * height", null),
              new JavaExpression("0.1 * width", null),
              new JavaExpression("0.9 * height", null),
              new JavaExpression("0.1 * height", null),
              new JavaExpression("0.1 * width", null)},
            true),
          new PrimitiveIconElement(
            "polyline",
            new Color(0, 0, 0, 255),
            null,
            new Object[] {
              new JavaExpression("0.1 * width", null),
              new JavaExpression("0.1 * height", null),
              new JavaExpression("0.5 * width", null),
              new JavaExpression("0.5 * height", null),
              new JavaExpression("0.9 * width", null),
              new JavaExpression("0.1 * height", null)},
            true),
          new PrimitiveIconElement(
            "text",
            new Color(0, 0, 255, 255),
            null,
            new Object[] {
              "e",
              new JavaExpression("width * 0.45", null),
              new JavaExpression("height * 0.8", null)},
            false)});
        m.setSharedDefinition(iconDefinition15);
      NodeConfiguration nodeConfiguration16 = new NodeConfiguration(
        "AudioResponse",
        "com.gensym.denali.model.StandardIconicNode",
        true,
        new BeanRecipe("com.gensym.cbu.odie.AudioResponse"),
        new BeanRecipe("com.gensym.denali.graphics.StandardIcon"),
        new SharedDefinitionReference("com.gensym.cbu.modules.odie", "AudioResponseIcon"),
        new String[] {"name"},
        new String[] {"name"},
        null,
        new SharedDefinitionReference[] {new SharedDefinitionReference("com.gensym.cbu.modules.odie", "OslInputPort")},
        new SharedDefinitionReference[] {new SharedDefinitionReference("com.gensym.cbu.modules.odie", "OslInputPort")},
        new SharedDefinitionReference[] {new SharedDefinitionReference("com.gensym.cbu.modules.odie", "OslInputPort")},
        new SharedDefinitionReference[] {new SharedDefinitionReference("com.gensym.cbu.modules.odie", "ResponseCommands")},
        null);
        nodeConfiguration16.setPreferredSize(new Dimension(32,32));
        nodeConfiguration16.setShowInPalettes(true);
        m.setSharedDefinition(nodeConfiguration16);
      PortConfiguration portConfiguration18 = new PortConfiguration(
        "OslInputPort",
        new SharedDefinitionReference("com.gensym.cbu.modules.odie", "OslConnection"),
        true,
        true,
        true,
        0,
        0,
        0);
        m.setSharedDefinition(portConfiguration18);
      NodeConfiguration nodeConfiguration20 = new NodeConfiguration(
        "SubscriberImpl",
        "com.gensym.denali.model.StandardIconicNode",
        true,
        new BeanRecipe("com.gensym.cbu.odie.SubscriberImpl"),
        new BeanRecipe("com.gensym.denali.graphics.StandardIcon"),
        new SharedDefinitionReference("com.gensym.cbu.modules.odie", "SubscriberImplIcon"),
        new String[] {"name"},
        new String[] {"name"},
        null,
        new SharedDefinitionReference[] {new SharedDefinitionReference("com.gensym.cbu.modules.odie", "OslOutputPort")},
        new SharedDefinitionReference[] {new SharedDefinitionReference("com.gensym.cbu.modules.odie", "OslOutputPort")},
        new SharedDefinitionReference[] {new SharedDefinitionReference("com.gensym.cbu.modules.odie", "OslOutputPort")},
	new SharedDefinitionReference[] {new SharedDefinitionReference("com.gensym.cbu.modules.odie", "SubscriberCommands")},
        null);
        nodeConfiguration20.setPreferredSize(new Dimension(32,32));
        nodeConfiguration20.setShowInPalettes(true);
        m.setSharedDefinition(nodeConfiguration20);
      NodeConfiguration nodeConfiguration21 = new NodeConfiguration(
        "ManagerImpl",
        "com.gensym.denali.model.StandardIconicNode",
        true,
        new BeanRecipe("com.gensym.cbu.odie.ManagerImpl"),
        new BeanRecipe("com.gensym.denali.graphics.StandardIcon"),
        new SharedDefinitionReference("com.gensym.cbu.modules.odie", "ManagerImplIcon"),
        new String[] {"name"},
        new String[] {"name"},
        null,
        null,
        null,
        null,
        null,
        null);
        nodeConfiguration21.setPreferredSize(new Dimension(32,32));
        nodeConfiguration21.setShowInPalettes(true);
        m.setSharedDefinition(nodeConfiguration21);
      PortConfiguration portConfiguration22 = new PortConfiguration(
        "EventFilterInputPort",
        new SharedDefinitionReference("com.gensym.cbu.modules.odie", "EventFilterConnection"),
        true,
        true,
        true,
        0,
        12,
        0);
        m.setSharedDefinition(portConfiguration22);
      StandardIconDefinition iconDefinition25 = new StandardIconDefinition(
        "DialogResponseIcon",
        new DefinitionParameter[] {
        new DefinitionParameter("name",String.class, "")},
        new IconElement[] {
          new PrimitiveIconElement(
            "rectangle",
            new Color(0, 0, 255, 255),
            null,
            new Object[] {
              new Float(0.0),
              new Float(0.0),
              new JavaExpression("width - 1", null),
              new JavaExpression("height - 1", null)},
            true),
          new PrimitiveIconElement(
            "text",
            new Color(0, 0, 0, 255),
            null,
            new Object[] {
              "Dlg.",
              new JavaExpression("0.25 * width", null),
              new JavaExpression("0.8 * height", null)},
            false)});
        m.setSharedDefinition(iconDefinition25);
      NodeConfiguration nodeConfiguration28 = new NodeConfiguration(
        "OdieTester",
        "com.gensym.denali.model.StandardIconicNode",
        true,
        new BeanRecipe("com.gensym.cbu.odie.OdieTester"),
        new BeanRecipe("com.gensym.denali.graphics.StandardIcon"),
        new SharedDefinitionReference("com.gensym.cbu.modules.odie", "OdieTesterIcon"),
        new String[] {"name"},
        new String[] {"name"},
        null,
        null,
        null,
        null,
        new SharedDefinitionReference[] {new SharedDefinitionReference("com.gensym.cbu.modules.odie", "OdieTesterCommands")},
        null);
        nodeConfiguration28.setPreferredSize(new Dimension(32,32));
        nodeConfiguration28.setShowInPalettes(true);
        m.setSharedDefinition(nodeConfiguration28);
      PortConfiguration portConfiguration29 = new PortConfiguration(
        "EventFilterOutputPort",
        new SharedDefinitionReference("com.gensym.cbu.modules.odie", "EventFilterConnection"),
        false,
        true,
        true,
        32,
        12,
        2);
        m.setSharedDefinition(portConfiguration29);
      ConnectionConfiguration connectionConfiguration30 = new ConnectionConfiguration(
        "OslConnection",
        "com.gensym.denali.model.DirectedConnection",
        new SharedDefinitionReference("com.gensym.cbu.modules.odie", "OslConnectionDefinition"),
        new BeanRecipe("com.gensym.denali.model.EventPropagator", new String[] {"hookupSpecification"}, new Serializable[] {new HookupSpecification("com.gensym.cbu.odie.SubscriberImpl",
				  "com.gensym.cbu.odie.Response",
				  "oslConnection",
				  "passEvent",
																		    "{ \n" +
      "((com.gensym.cbu.odie.Response)target).respond(\n" +
      "((com.gensym.cbu.odie.OslConnectionEvent)event).getOdieEvent(), " +
      "((com.gensym.cbu.odie.OslConnectionEvent)event).getManager());" +
      "}\n")}),
        true,
        null,
        null,
        null);
        m.setSharedDefinition(connectionConfiguration30);
      StandardIconDefinition iconDefinition31 = new StandardIconDefinition(
        "SubscriberImplIcon",
        new DefinitionParameter[] {
        new DefinitionParameter("name",String.class, "")},
        new IconElement[] {
          new PrimitiveIconElement(
            "rectangle",
            new Color(169, 169, 169, 255),
            null,
            new Object[] {
              new JavaExpression("8/32.0 * width", null),
              new JavaExpression("6/32.0 * height", null),
              new JavaExpression("17/32.0 * width", null),
              new JavaExpression("14/32.0 * height", null)},
            false),
          new PrimitiveIconElement(
            "polygon",
            new Color(105, 105, 105, 255),
            null,
            new Object[] {
              new Integer(0),
              new JavaExpression("13/32.0 * height", null),
              new JavaExpression("7/32.0 * width", null),
              new JavaExpression("8/32.0 * height", null),
              new JavaExpression("6/32.0 * width", null),
              new JavaExpression("13/32.0 * height", null),
              new JavaExpression("3/32.0 * width", null),
              new JavaExpression("16/32.0 * height", null),
              new JavaExpression("4/32.0 * width", null),
              new JavaExpression("18/32.0 * height", null),
              new JavaExpression("7/32.0 * width", null),
              new JavaExpression("18/32.0 * height", null),
              new JavaExpression("14/32.0 * width", null)},
            false),
          new PrimitiveIconElement(
            "polygon",
            new Color(169, 169, 169, 255),
            null,
            new Object[] {
              new Integer(0),
              new JavaExpression("24/32.0 * height", null),
              new JavaExpression("1/32.0 * width", null),
              new JavaExpression("16/32.0 * height", null),
              new JavaExpression("4/32.0 * width", null),
              new JavaExpression("14/32.0 * height", null),
              new JavaExpression("2/32.0 * width", null),
              new JavaExpression("20/32.0 * height", null),
              new JavaExpression("0/32.0 * width", null)},
            false),
          new PrimitiveIconElement(
            "polygon",
            new Color(169, 169, 169, 255),
            null,
            new Object[] {
              new Integer(0),
              new JavaExpression("18/32.0 * height", null),
              new JavaExpression("6/32.0 * width", null),
              new JavaExpression("26/32.0 * height", null),
              new JavaExpression("3/32.0 * width", null),
              new JavaExpression("26/32.0 * height", null),
              new JavaExpression("10/32.0 * width", null),
              new JavaExpression("18/32.0 * height", null),
              new JavaExpression("13/32.0 * width", null)},
            false),
          new PrimitiveIconElement(
            "polygon",
            new Color(211, 211, 211, 255),
            null,
            new Object[] {
              new Integer(0),
              new JavaExpression("18/32.0 * height", null),
              new JavaExpression("14/32.0 * width", null),
              new JavaExpression("15/32.0 * height", null),
              new JavaExpression("19/32.0 * width", null),
              new JavaExpression("13/32.0 * height", null),
              new JavaExpression("22/32.0 * width", null),
              new JavaExpression("9/32.0 * height", null),
              new JavaExpression("23/32.0 * width", null),
              new JavaExpression("7/32.0 * height", null),
              new JavaExpression("21/32.0 * width", null),
              new JavaExpression("6/32.0 * height", null),
              new JavaExpression("18/32.0 * width", null),
              new JavaExpression("8/32.0 * height", null),
              new JavaExpression("15/32.0 * width", null)},
            false),
          new PrimitiveIconElement(
            "polyline",
            new Color(0, 0, 0, 255),
            null,
            new Object[] {
              new JavaExpression("18/32.0 * width", null),
              new JavaExpression("15/32.0 * height", null),
              new JavaExpression("15/32.0 * width", null),
              new JavaExpression("20/32.0 * height", null)},
            true),
          new PrimitiveIconElement(
            "polyline",
            new Color(0, 0, 0, 255),
            null,
            new Object[] {
              new JavaExpression("6/32.0 * width", null),
              new JavaExpression("18/32.0 * height", null),
              new JavaExpression("9/32.0 * width", null),
              new JavaExpression("23/32.0 * height", null),
              new JavaExpression("15/32.0 * width", null),
              new JavaExpression("20/32.0 * height", null)},
            true),
          new PrimitiveIconElement(
            "polyline",
            new Color(0, 0, 0, 255),
            null,
            new Object[] {
              new JavaExpression("8/32.0 * width", null),
              new JavaExpression("14/32.0 * height", null),
              new JavaExpression("6/32.0 * width", null),
              new JavaExpression("18/32.0 * height", null)},
            true),
          new PrimitiveIconElement(
            "polyline",
            new Color(0, 0, 0, 255),
            null,
            new Object[] {
              new JavaExpression("8/32.0 * width", null),
              new JavaExpression("14/32.0 * height", null),
              new JavaExpression("18/32.0 * width", null),
              new JavaExpression("14/32.0 * height", null)},
            true),
          new PrimitiveIconElement(
            "polygon",
            new Color(0, 0, 0, 255),
            null,
            new Object[] {
              new Integer(0),
              new JavaExpression("24/32.0 * height", null),
              new JavaExpression("12/32.0 * width", null),
              new JavaExpression("24/32.0 * height", null),
              new JavaExpression("32/32.0 * width", null),
              new JavaExpression("20/32.0 * height", null),
              new JavaExpression("32/32.0 * width", null),
              new JavaExpression("20/32.0 * height", null),
              new JavaExpression("13/32.0 * width", null)},
            false),
          new PrimitiveIconElement(
            "polyline",
            new Color(0, 0, 0, 255),
            null,
            new Object[] {
              new JavaExpression("26/32.0 * width", null),
              new JavaExpression("2/32.0 * height", null),
              new JavaExpression("26/32.0 * width", null),
              new JavaExpression("10/32.0 * height", null)},
            true),
          new PrimitiveIconElement(
            "polyline",
            new Color(0, 0, 0, 255),
            null,
            new Object[] {
              new JavaExpression("19/32.0 * width", null),
              new JavaExpression("1/32.0 * height", null),
              new JavaExpression("11/32.0 * width", null),
              new JavaExpression("3/32.0 * height", null)},
            true),
          new PrimitiveIconElement(
            "polyline",
            new Color(0, 0, 0, 255),
            null,
            new Object[] {
              new JavaExpression("26/32.0 * width", null),
              new JavaExpression("2/32.0 * height", null),
              new JavaExpression("22/32.0 * width", null),
              new JavaExpression("0/32.0 * height", null),
              new JavaExpression("19/32.0 * width", null),
              new JavaExpression("1/32.0 * height", null)},
            true),
          new PrimitiveIconElement(
            "polyline",
            new Color(0, 0, 0, 255),
            null,
            new Object[] {
              new JavaExpression("18/32.0 * width", null),
              new JavaExpression("14/32.0 * height", null),
              new JavaExpression("26/32.0 * width", null),
              new JavaExpression("11/32.0 * height", null)},
            true),
          new PrimitiveIconElement(
            "polyline",
            new Color(0, 0, 0, 255),
            null,
            new Object[] {
              new JavaExpression("18/32.0 * width", null),
              new JavaExpression("9/32.0 * height", null),
              new JavaExpression("18/32.0 * width", null),
              new JavaExpression("14/32.0 * height", null)},
            true),
          new PrimitiveIconElement(
            "polyline",
            new Color(0, 0, 0, 255),
            null,
            new Object[] {
              new JavaExpression("8/32.0 * width", null),
              new JavaExpression("9/32.0 * height", null),
              new JavaExpression("8/32.0 * width", null),
              new JavaExpression("14/32.0 * height", null)},
            true),
          new PrimitiveIconElement(
            "polyline",
            new Color(0, 0, 0, 255),
            null,
            new Object[] {
              new JavaExpression("8/32.0 * width", null),
              new JavaExpression("9/32.0 * height", null),
              new JavaExpression("11/32.0 * width", null),
              new JavaExpression("3/32.0 * height", null),
              new JavaExpression("18/32.0 * width", null),
              new JavaExpression("9/32.0 * height", null)},
            true),
          new PrimitiveIconElement(
            "polygon",
            new Color(0, 0, 0, 255),
            null,
            new Object[] {
              new Integer(0),
              new Float(0.0),
              new Float(0.0),
              new Float(0.0),
              new JavaExpression("width - 1", null),
              new JavaExpression("height - 1", null),
              new JavaExpression("width - 1", null),
              new JavaExpression("height - 1", null),
              new Float(0.0)},
            true)});
        m.setSharedDefinition(iconDefinition31);
      StandardIconDefinition iconDefinition32 = new StandardIconDefinition(
        "AudioResponseIcon",
        new DefinitionParameter[] {
        new DefinitionParameter("name",String.class, "")},
        new IconElement[] {
          new PrimitiveIconElement(
            "image",
            new Color(128, 128, 128, 255),
            null,
            new Object[] {
              "/odie/audioresponse.gif",
              new Float(0.0),
              new Float(0.0),
              new JavaExpression("width", null),
              new JavaExpression("height", null)},
            false)});
        m.setSharedDefinition(iconDefinition32);
      GeneralConnectionDefinition GeneralConnectionDefintion33 = new GeneralConnectionDefinition(
        "OslConnectionDefinition",
        new DefinitionParameter[] {},
        5,
        new Color(0, 255, 0, 255),
        1,
        new Color(0, 0, 0, 255),
        BasicStroke.JOIN_MITER,
        null,
        GeneralConnectionDefinition.CUBIC,
        null,
        null);
        m.setSharedDefinition(GeneralConnectionDefintion33);
      StandardIconDefinition iconDefinition34 = new StandardIconDefinition(
        "ManagerImplIcon",
        new DefinitionParameter[] {
        new DefinitionParameter("name",String.class, "")},
        new IconElement[] {
          new PrimitiveIconElement(
            "polygon",
            new Color(152, 251, 152, 255),
            null,
            new Object[] {
              new Integer(0),
              new JavaExpression("12/32.0 * height", null),
              new JavaExpression("9/32.0 * width", null),
              new JavaExpression("23/32.0 * height", null),
              new JavaExpression("8/32.0 * width", null),
              new JavaExpression("28/32.0 * height", null),
              new JavaExpression("12/32.0 * width", null),
              new JavaExpression("28/32.0 * height", null),
              new JavaExpression("14/32.0 * width", null),
              new JavaExpression("17/32.0 * height", null),
              new JavaExpression("13/32.0 * width", null),
              new JavaExpression("8/32.0 * height", null),
              new JavaExpression("15/32.0 * width", null),
              new JavaExpression("8/32.0 * height", null),
              new JavaExpression("12/32.0 * width", null)},
            false),
          new PrimitiveIconElement(
            "polygon",
            new Color(152, 251, 152, 255),
            null,
            new Object[] {
              new Integer(0),
              new JavaExpression("25/32.0 * height", null),
              new JavaExpression("1/32.0 * width", null),
              new JavaExpression("31/32.0 * height", null),
              new JavaExpression("6/32.0 * width", null),
              new JavaExpression("29/32.0 * height", null),
              new JavaExpression("13/32.0 * width", null),
              new JavaExpression("24/32.0 * height", null),
              new JavaExpression("9/32.0 * width", null)},
            false),
          new PrimitiveIconElement(
            "polygon",
            new Color(152, 251, 152, 255),
            null,
            new Object[] {
              new Integer(0),
              new JavaExpression("15/32.0 * height", null),
              new JavaExpression("1/32.0 * width", null),
              new JavaExpression("25/32.0 * height", null),
              new JavaExpression("1/32.0 * width", null),
              new JavaExpression("24/32.0 * height", null),
              new JavaExpression("8/32.0 * width", null),
              new JavaExpression("18/32.0 * height", null),
              new JavaExpression("8/32.0 * width", null)},
            false),
          new PrimitiveIconElement(
            "polygon",
            new Color(152, 251, 152, 255),
            null,
            new Object[] {
              new Integer(0),
              new JavaExpression("6/32.0 * height", null),
              new JavaExpression("5/32.0 * width", null),
              new JavaExpression("15/32.0 * height", null),
              new JavaExpression("1/32.0 * width", null),
              new JavaExpression("18/32.0 * height", null),
              new JavaExpression("8/32.0 * width", null),
              new JavaExpression("12/32.0 * height", null),
              new JavaExpression("9/32.0 * width", null)},
            false),
          new PrimitiveIconElement(
            "polygon",
            new Color(152, 251, 152, 255),
            null,
            new Object[] {
              new Integer(0),
              new JavaExpression("6/32.0 * height", null),
              new JavaExpression("14/32.0 * width", null),
              new JavaExpression("2/32.0 * height", null),
              new JavaExpression("11/32.0 * width", null),
              new JavaExpression("6/32.0 * height", null),
              new JavaExpression("5/32.0 * width", null),
              new JavaExpression("12/32.0 * height", null),
              new JavaExpression("9/32.0 * width", null)},
            false),
          new PrimitiveIconElement(
            "polygon",
            new Color(34, 139, 34, 255),
            null,
            new Object[] {
              new Integer(0),
              new JavaExpression("12/32.0 * height", null),
              new JavaExpression("9/32.0 * width", null),
              new JavaExpression("23/32.0 * height", null),
              new JavaExpression("8/32.0 * width", null),
              new JavaExpression("28/32.0 * height", null),
              new JavaExpression("12/32.0 * width", null),
              new JavaExpression("28/32.0 * height", null),
              new JavaExpression("14/32.0 * width", null),
              new JavaExpression("17/32.0 * height", null),
              new JavaExpression("13/32.0 * width", null),
              new JavaExpression("8/32.0 * height", null),
              new JavaExpression("15/32.0 * width", null),
              new JavaExpression("8/32.0 * height", null),
              new JavaExpression("12/32.0 * width", null)},
            true),
          new PrimitiveIconElement(
            "polygon",
            new Color(34, 139, 34, 255),
            null,
            new Object[] {
              new Integer(0),
              new JavaExpression("24/32.0 * height", null),
              new JavaExpression("9/32.0 * width", null),
              new JavaExpression("29/32.0 * height", null),
              new JavaExpression("13/32.0 * width", null),
              new JavaExpression("31/32.0 * height", null),
              new JavaExpression("6/32.0 * width", null),
              new JavaExpression("25/32.0 * height", null),
              new JavaExpression("1/32.0 * width", null)},
            true),
          new PrimitiveIconElement(
            "polygon",
            new Color(34, 139, 34, 255),
            null,
            new Object[] {
              new Integer(0),
              new JavaExpression("18/32.0 * height", null),
              new JavaExpression("8/32.0 * width", null),
              new JavaExpression("24/32.0 * height", null),
              new JavaExpression("8/32.0 * width", null),
              new JavaExpression("25/32.0 * height", null),
              new JavaExpression("1/32.0 * width", null),
              new JavaExpression("15/32.0 * height", null),
              new JavaExpression("1/32.0 * width", null)},
            true),
          new PrimitiveIconElement(
            "polygon",
            new Color(34, 139, 34, 255),
            null,
            new Object[] {
              new Integer(0),
              new JavaExpression("12/32.0 * height", null),
              new JavaExpression("9/32.0 * width", null),
              new JavaExpression("18/32.0 * height", null),
              new JavaExpression("8/32.0 * width", null),
              new JavaExpression("15/32.0 * height", null),
              new JavaExpression("1/32.0 * width", null),
              new JavaExpression("6/32.0 * height", null),
              new JavaExpression("5/32.0 * width", null)},
            true),
          new PrimitiveIconElement(
            "polygon",
            new Color(34, 139, 34, 255),
            null,
            new Object[] {
              new Integer(0),
              new JavaExpression("12/32.0 * height", null),
              new JavaExpression("9/32.0 * width", null),
              new JavaExpression("6/32.0 * height", null),
              new JavaExpression("5/32.0 * width", null),
              new JavaExpression("2/32.0 * height", null),
              new JavaExpression("11/32.0 * width", null),
              new JavaExpression("6/32.0 * height", null),
              new JavaExpression("14/32.0 * width", null)},
            true),
          new PrimitiveIconElement(
            "polyline",
            new Color(0, 0, 0, 255),
            null,
            new Object[] {
              new JavaExpression("10/32.0 * width", null),
              new JavaExpression("19/32.0 * height", null),
              new JavaExpression("13/32.0 * width", null),
              new JavaExpression("17/32.0 * height", null),
              new JavaExpression("16/32.0 * width", null),
              new JavaExpression("18/32.0 * height", null)},
            true),
          new PrimitiveIconElement(
            "polyline",
            new Color(0, 0, 0, 255),
            null,
            new Object[] {
              new JavaExpression("19/32.0 * width", null),
              new JavaExpression("18/32.0 * height", null),
              new JavaExpression("22/32.0 * width", null),
              new JavaExpression("17/32.0 * height", null),
              new JavaExpression("25/32.0 * width", null),
              new JavaExpression("18/32.0 * height", null)},
            true),
          new PrimitiveIconElement(
            "polyline",
            new Color(210, 180, 140, 255),
            null,
            new Object[] {
              new JavaExpression("28/32.0 * width", null),
              new JavaExpression("14/32.0 * height", null),
              new JavaExpression("8/32.0 * width", null),
              new JavaExpression("14/32.0 * height", null),
              new JavaExpression("6/32.0 * width", null),
              new JavaExpression("24/32.0 * height", null),
              new JavaExpression("7/32.0 * width", null),
              new JavaExpression("29/32.0 * height", null),
              new JavaExpression("11/32.0 * width", null),
              new JavaExpression("32/32.0 * height", null),
              new JavaExpression("23/32.0 * width", null),
              new JavaExpression("32/32.0 * height", null),
              new JavaExpression("27/32.0 * width", null),
              new JavaExpression("28/32.0 * height", null),
              new JavaExpression("28/32.0 * width", null),
              new JavaExpression("14/32.0 * height", null)},
            true),
          new PrimitiveIconElement(
            "polyline",
            new Color(210, 180, 140, 255),
            null,
            new Object[] {
              new JavaExpression("17/32.0 * width", null),
              new JavaExpression("20/32.0 * height", null),
              new JavaExpression("18/32.0 * width", null),
              new JavaExpression("23/32.0 * height", null),
              new JavaExpression("19/32.0 * width", null),
              new JavaExpression("24/32.0 * height", null),
              new JavaExpression("15/32.0 * width", null),
              new JavaExpression("24/32.0 * height", null),
              new JavaExpression("16/32.0 * width", null),
              new JavaExpression("23/32.0 * height", null),
              new JavaExpression("16/32.0 * width", null),
              new JavaExpression("20/32.0 * height", null)},
            true),
          new PrimitiveIconElement(
            "polygon",
            new Color(105, 105, 105, 255),
            null,
            new Object[] {
              new Integer(0),
              new JavaExpression("15/32.0 * height", null),
              new JavaExpression("30/32.0 * width", null),
              new JavaExpression("18/32.0 * height", null),
              new JavaExpression("29/32.0 * width", null),
              new JavaExpression("21/32.0 * height", null),
              new JavaExpression("26/32.0 * width", null),
              new JavaExpression("12/32.0 * height", null),
              new JavaExpression("27/32.0 * width", null)},
            true),
          new PrimitiveIconElement(
            "polyline",
            new Color(160, 82, 45, 255),
            null,
            new Object[] {
              new JavaExpression("26/32.0 * width", null),
              new JavaExpression("17/32.0 * height", null),
              new JavaExpression("26/32.0 * width", null),
              new JavaExpression("18/32.0 * height", null)},
            true),
          new PrimitiveIconElement(
            "polyline",
            new Color(160, 82, 45, 255),
            null,
            new Object[] {
              new JavaExpression("23/32.0 * width", null),
              new JavaExpression("26/32.0 * height", null),
              new JavaExpression("22/32.0 * width", null),
              new JavaExpression("28/32.0 * height", null)},
            true),
          new PrimitiveIconElement(
            "polyline",
            new Color(160, 82, 45, 255),
            null,
            new Object[] {
              new JavaExpression("11/32.0 * width", null),
              new JavaExpression("26/32.0 * height", null),
              new JavaExpression("10/32.0 * width", null),
              new JavaExpression("27/32.0 * height", null),
              new JavaExpression("11/32.0 * width", null),
              new JavaExpression("28/32.0 * height", null)},
            true),
          new PrimitiveIconElement(
            "polyline",
            new Color(0, 0, 0, 255),
            null,
            new Object[] {
              new JavaExpression("2/32.0 * width", null),
              new JavaExpression("11/32.0 * height", null),
              new JavaExpression("6/32.0 * width", null),
              new JavaExpression("14/32.0 * height", null),
              new JavaExpression("11/32.0 * width", null),
              new JavaExpression("9/32.0 * height", null),
              new JavaExpression("24/32.0 * width", null),
              new JavaExpression("9/32.0 * height", null),
              new JavaExpression("28/32.0 * width", null),
              new JavaExpression("14/32.0 * height", null),
              new JavaExpression("31/32.0 * width", null),
              new JavaExpression("6/32.0 * height", null)},
            true),
          new PrimitiveIconElement(
            "polygon",
            new Color(0, 0, 0, 255),
            null,
            new Object[] {
              new Integer(0),
              new JavaExpression("10/32.0 * height", null),
              new JavaExpression("15/32.0 * width", null),
              new JavaExpression("18/32.0 * height", null),
              new JavaExpression("13/32.0 * width", null),
              new JavaExpression("27/32.0 * height", null),
              new JavaExpression("14/32.0 * width", null),
              new JavaExpression("27/32.0 * height", null),
              new JavaExpression("15/32.0 * width", null),
              new JavaExpression("18/32.0 * height", null),
              new JavaExpression("15/32.0 * width", null)},
            false),
          new PrimitiveIconElement(
            "polygon",
            new Color(0, 0, 0, 255),
            null,
            new Object[] {
              new Integer(0),
              new Float(0.0),
              new Float(0.0),
              new Float(0.0),
              new JavaExpression("width - 1", null),
              new JavaExpression("height - 1", null),
              new JavaExpression("width - 1", null),
              new JavaExpression("height - 1", null),
              new Float(0.0)},
            true)});
        m.setSharedDefinition(iconDefinition34);
      NodeConfiguration nodeConfiguration35 = new NodeConfiguration(
        "SmtpResponse",
        "com.gensym.denali.model.StandardIconicNode",
        true,
        new BeanRecipe("com.gensym.cbu.odie.SmtpResponse"),
        new BeanRecipe("com.gensym.denali.graphics.StandardIcon"),
        new SharedDefinitionReference("com.gensym.cbu.modules.odie", "SmtpResponseIcon"),
        new String[] {"name"},
        new String[] {"name"},
        null,
        new SharedDefinitionReference[] {new SharedDefinitionReference("com.gensym.cbu.modules.odie", "OslInputPort")},
        new SharedDefinitionReference[] {new SharedDefinitionReference("com.gensym.cbu.modules.odie", "OslInputPort")},
        new SharedDefinitionReference[] {new SharedDefinitionReference("com.gensym.cbu.modules.odie", "OslInputPort")},
        null,
        null);
        nodeConfiguration35.setPreferredSize(new Dimension(32,32));
        nodeConfiguration35.setShowInPalettes(true);
        m.setSharedDefinition(nodeConfiguration35);
    } catch (Exception e)
    {
       e.printStackTrace();
    }
  }
}
