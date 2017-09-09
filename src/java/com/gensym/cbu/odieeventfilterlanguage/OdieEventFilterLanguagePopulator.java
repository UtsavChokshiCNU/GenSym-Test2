package com.gensym.cbu.odieeventfilterlanguage;

import java.awt.*;
import com.gensym.denali.model.*;
import com.gensym.denali.graphics.*;
import java.io.Serializable;

public class OdieEventFilterLanguagePopulator implements Populator
{
  public void populate(ServerImpl server)
  {
    try {
      Module m = new ModuleImpl("com.gensym.cbu.modules.odieeventfilterlanguage");
      server.addModule(m);
    
      NodeConfiguration nodeConfiguration1 = new NodeConfiguration(
        "NotBlock",
        "com.gensym.denali.model.StandardIconicNode",
        true,
        new BeanRecipe("com.gensym.cbu.odieeventfilterlanguage.NotBlock"),
        new BeanRecipe("com.gensym.denali.graphics.StandardIcon"),
        new SharedDefinitionReference("com.gensym.cbu.modules.odieeventfilterlanguage", "NotBlockIcon"),
        new String[] {},
        new String[] {},
        null,
        new SharedDefinitionReference[] {new SharedDefinitionReference("com.gensym.cbu.modules.odieeventfilterlanguage", "EventFilterInputPort"), new SharedDefinitionReference("com.gensym.cbu.modules.odieeventfilterlanguage", "EventFilterOutputPort")},
        new SharedDefinitionReference[] {},
        new SharedDefinitionReference[] {},
        null,
        null);
        nodeConfiguration1.setPreferredSize(new Dimension(32,32));
        nodeConfiguration1.setShowInPalettes(true);
        m.setSharedDefinition(nodeConfiguration1);
      NodeConfiguration nodeConfiguration2 = new NodeConfiguration(
        "PriorityBlock",
        "com.gensym.denali.model.StandardIconicNode",
        true,
        new BeanRecipe("com.gensym.cbu.odieeventfilterlanguage.PriorityBlock"),
        new BeanRecipe("com.gensym.denali.graphics.StandardIcon"),
        new SharedDefinitionReference("com.gensym.cbu.modules.odieeventfilterlanguage", "PriorityBlockIcon"),
        new String[] {},
        new String[] {},
        null,
        new SharedDefinitionReference[] {new SharedDefinitionReference("com.gensym.cbu.modules.odieeventfilterlanguage", "EventFilterOutputPort")},
        new SharedDefinitionReference[] {new SharedDefinitionReference("com.gensym.cbu.modules.odieeventfilterlanguage", "EventFilterOutputPort")},
        new SharedDefinitionReference[] {},
        null,
        null);
        nodeConfiguration2.setPreferredSize(new Dimension(32,32));
        nodeConfiguration2.setShowInPalettes(true);
        m.setSharedDefinition(nodeConfiguration2);
      GeneralConnectionDefinition GeneralConnectionDefintion3 = new GeneralConnectionDefinition(
        "EventFilterConnectionAppearance",
        new DefinitionParameter[] {},
        3,
        new Color(0, 255, 255, 255),
        1,
        new Color(0, 0, 0, 255),
        BasicStroke.JOIN_MITER,
        null,
        GeneralConnectionDefinition.LINEAR,
        null,
        null);
        m.setSharedDefinition(GeneralConnectionDefintion3);
      ConnectionConfiguration connectionConfiguration4 = new ConnectionConfiguration(
        "EventFilterConnection",
        "com.gensym.denali.model.DirectedConnection",
        new SharedDefinitionReference("com.gensym.cbu.modules.odieeventfilterlanguage", "EventFilterConnectionAppearance"),
        new BeanRecipe("com.gensym.denali.model.EventPropagator"),
        false,
        null,
        null,
        null);
        m.setSharedDefinition(connectionConfiguration4);
      NodeConfiguration nodeConfiguration5 = new NodeConfiguration(
        "SenderIdBlock",
        "com.gensym.denali.model.StandardIconicNode",
        true,
        new BeanRecipe("com.gensym.cbu.odieeventfilterlanguage.SenderIdBlock"),
        new BeanRecipe("com.gensym.denali.graphics.StandardIcon"),
        new SharedDefinitionReference("com.gensym.cbu.modules.odieeventfilterlanguage", "SenderIdBlockIcon"),
        new String[] {},
        new String[] {},
        null,
        new SharedDefinitionReference[] {new SharedDefinitionReference("com.gensym.cbu.modules.odieeventfilterlanguage", "EventFilterInputPort"), new SharedDefinitionReference("com.gensym.cbu.modules.odieeventfilterlanguage", "EventFilterOutputPort")},
        new SharedDefinitionReference[] {},
        new SharedDefinitionReference[] {},
        null,
        null);
        nodeConfiguration5.setPreferredSize(new Dimension(32,32));
        nodeConfiguration5.setShowInPalettes(true);
        m.setSharedDefinition(nodeConfiguration5);
      NodeConfiguration nodeConfiguration6 = new NodeConfiguration(
        "TargetIdBlock",
        "com.gensym.denali.model.StandardIconicNode",
        true,
        new BeanRecipe("com.gensym.cbu.odieeventfilterlanguage.TargetIdBlock"),
        new BeanRecipe("com.gensym.denali.graphics.StandardIcon"),
        new SharedDefinitionReference("com.gensym.cbu.modules.odieeventfilterlanguage", "TargetIdBlockIcon"),
        new String[] {},
        new String[] {},
        null,
        new SharedDefinitionReference[] {new SharedDefinitionReference("com.gensym.cbu.modules.odieeventfilterlanguage", "EventFilterInputPort"), new SharedDefinitionReference("com.gensym.cbu.modules.odieeventfilterlanguage", "EventFilterOutputPort")},
        new SharedDefinitionReference[] {},
        new SharedDefinitionReference[] {},
        null,
        null);
        nodeConfiguration6.setPreferredSize(new Dimension(32,32));
        nodeConfiguration6.setShowInPalettes(true);
        m.setSharedDefinition(nodeConfiguration6);
      NodeConfiguration nodeConfiguration7 = new NodeConfiguration(
        "PublicationDateBlock",
        "com.gensym.denali.model.StandardIconicNode",
        true,
        new BeanRecipe("com.gensym.cbu.odieeventfilterlanguage.PublicationDateBlock"),
        new BeanRecipe("com.gensym.denali.graphics.StandardIcon"),
        new SharedDefinitionReference("com.gensym.cbu.modules.odieeventfilterlanguage", "PublicationDateBlockIcon"),
        new String[] {},
        new String[] {},
        null,
        new SharedDefinitionReference[] {new SharedDefinitionReference("com.gensym.cbu.modules.odieeventfilterlanguage", "EventFilterInputPort"), new SharedDefinitionReference("com.gensym.cbu.modules.odieeventfilterlanguage", "EventFilterOutputPort")},
        new SharedDefinitionReference[] {},
        new SharedDefinitionReference[] {},
        null,
        null);
        nodeConfiguration7.setPreferredSize(new Dimension(32,32));
        nodeConfiguration7.setShowInPalettes(true);
        m.setSharedDefinition(nodeConfiguration7);
      StandardIconDefinition iconDefinition8 = new StandardIconDefinition(
        "NotBlockIcon",
        new DefinitionParameter[0],
        new IconElement[] {
          new PrimitiveIconElement(
            "rectangle",
            new Color(0, 255, 255, 255),
            null,
            new Object[] {
              new Float(0.0),
              new Float(0.0),
              new JavaExpression("width - 1", null),
              new JavaExpression("height - 1", null)},
            false),
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
            "text",
            new Color(0, 0, 0, 255),
            null,
            new Object[] {
              "!",
              new JavaExpression("0.25 * width", null),
              new JavaExpression("0.6 * height", null)},
            false)});
        m.setSharedDefinition(iconDefinition8);
      StandardIconDefinition iconDefinition9 = new StandardIconDefinition(
        "SenderIdBlockIcon",
        new DefinitionParameter[0],
        new IconElement[] {
          new PrimitiveIconElement(
            "rectangle",
            new Color(0, 255, 255, 255),
            null,
            new Object[] {
              new Float(0.0),
              new Float(0.0),
              new JavaExpression("width - 1", null),
              new JavaExpression("height - 1", null)},
            false),
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
            "text",
            new Color(0, 0, 0, 255),
            null,
            new Object[] {
              "Sndr",
              new JavaExpression("0.25 * width", null),
              new JavaExpression("0.6 * height", null)},
            false)});
        m.setSharedDefinition(iconDefinition9);
      NodeConfiguration nodeConfiguration10 = new NodeConfiguration(
        "OrBlock",
        "com.gensym.denali.model.StandardIconicNode",
        true,
        new BeanRecipe("com.gensym.cbu.odieeventfilterlanguage.OrBlock"),
        new BeanRecipe("com.gensym.denali.graphics.StandardIcon"),
        new SharedDefinitionReference("com.gensym.cbu.modules.odieeventfilterlanguage", "OrBlockIcon"),
        new String[] {},
        new String[] {},
        null,
        new SharedDefinitionReference[] {new SharedDefinitionReference("com.gensym.cbu.modules.odieeventfilterlanguage", "EventFilterInputPort"), new SharedDefinitionReference("com.gensym.cbu.modules.odieeventfilterlanguage", "EventFilterOutputPort")},
        new SharedDefinitionReference[] {new SharedDefinitionReference("com.gensym.cbu.modules.odieeventfilterlanguage", "EventFilterOutputPort")},
        new SharedDefinitionReference[] {new SharedDefinitionReference("com.gensym.cbu.modules.odieeventfilterlanguage", "EventFilterOutputPort")},
        null,
        null);
        nodeConfiguration10.setPreferredSize(new Dimension(32,32));
        nodeConfiguration10.setShowInPalettes(true);
        m.setSharedDefinition(nodeConfiguration10);
      StandardIconDefinition iconDefinition11 = new StandardIconDefinition(
        "TargetIdBlockIcon",
        new DefinitionParameter[0],
        new IconElement[] {
          new PrimitiveIconElement(
            "rectangle",
            new Color(0, 255, 255, 255),
            null,
            new Object[] {
              new Float(0.0),
              new Float(0.0),
              new JavaExpression("width - 1", null),
              new JavaExpression("height - 1", null)},
            false),
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
            "text",
            new Color(0, 0, 0, 255),
            null,
            new Object[] {
              "Tgt",
              new JavaExpression("0.25 * width", null),
              new JavaExpression("0.6 * height", null)},
            false)});
        m.setSharedDefinition(iconDefinition11);
      StandardIconDefinition iconDefinition12 = new StandardIconDefinition(
        "PriorityBlockIcon",
        new DefinitionParameter[0],
        new IconElement[] {
          new PrimitiveIconElement(
            "rectangle",
            new Color(0, 255, 255, 255),
            null,
            new Object[] {
              new Float(0.0),
              new Float(0.0),
              new JavaExpression("width - 1", null),
              new JavaExpression("height - 1", null)},
            false),
          new PrimitiveIconElement(
            "polyline",
            new Color(0, 0, 0, 255),
            null,
            new Object[] {
              new JavaExpression(".6 * width", null),
              new JavaExpression(".1 * height", null),
              new JavaExpression(".9 * width", null),
              new JavaExpression(".5 * height", null),
              new JavaExpression(".6 * width", null),
              new JavaExpression(".9 * height", null)},
            true),
          new PrimitiveIconElement(
            "polyline",
            new Color(0, 0, 0, 255),
            null,
            new Object[] {
              new JavaExpression(".1 * width", null),
              new JavaExpression(".5 * height", null),
              new JavaExpression(".9 * width", null),
              new JavaExpression(".5 * height", null)},
            true),
          new PrimitiveIconElement(
            "rectangle",
            new Color(0, 0, 0, 255),
            null,
            new Object[] {
              new Float(0.0),
              new Float(0.0),
              new JavaExpression("width - 1", null),
              new JavaExpression("height - 1", null)},
            true)});
        m.setSharedDefinition(iconDefinition12);
      PortConfiguration portConfiguration13 = new PortConfiguration(
        "EventFilterInputPort",
        new SharedDefinitionReference("com.gensym.cbu.modules.odieeventfilterlanguage", "EventFilterConnection"),
        true,
        true,
        true,
        0,
        12,
        0);
        m.setSharedDefinition(portConfiguration13);
      StandardIconDefinition iconDefinition14 = new StandardIconDefinition(
        "PublicationDateBlockIcon",
        new DefinitionParameter[0],
        new IconElement[] {
          new PrimitiveIconElement(
            "rectangle",
            new Color(0, 255, 255, 255),
            null,
            new Object[] {
              new Float(0.0),
              new Float(0.0),
              new JavaExpression("width - 1", null),
              new JavaExpression("height - 1", null)},
            false),
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
            "text",
            new Color(0, 0, 0, 255),
            null,
            new Object[] {
              "Pub",
              new JavaExpression("0.25 * width", null),
              new JavaExpression("0.6 * height", null)},
            false)});
        m.setSharedDefinition(iconDefinition14);
      PortConfiguration portConfiguration15 = new PortConfiguration(
        "EventFilterOutputPort",
        new SharedDefinitionReference("com.gensym.cbu.modules.odieeventfilterlanguage", "EventFilterConnection"),
        false,
        true,
        true,
        32,
        12,
        2);
        m.setSharedDefinition(portConfiguration15);
      StandardIconDefinition iconDefinition16 = new StandardIconDefinition(
        "OrBlockIcon",
        new DefinitionParameter[0],
        new IconElement[] {
          new PrimitiveIconElement(
            "rectangle",
            new Color(0, 255, 255, 255),
            null,
            new Object[] {
              new Float(0.0),
              new Float(0.0),
              new JavaExpression("width - 1", null),
              new JavaExpression("height - 1", null)},
            false),
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
            "text",
            new Color(0, 0, 0, 255),
            null,
            new Object[] {
              "||",
              new JavaExpression("0.25 * width", null),
              new JavaExpression("0.6 * height", null)},
            false)});
        m.setSharedDefinition(iconDefinition16);
    } catch (Exception e)
    {
       e.printStackTrace();
    }
  }
}
