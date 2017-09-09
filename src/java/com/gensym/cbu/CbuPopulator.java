package com.gensym.cbu;

import java.awt.*;
import java.awt.geom.*;
import javax.swing.*;
import com.gensym.denali.model.*;
import com.gensym.denali.g2.*;
import com.gensym.denali.events.*;
import com.gensym.denali.graphics.*;
import com.gensym.denali.common.DirectionConstants;
import com.gensym.denali.common.ObservableExpression;
import com.gensym.cbu.experimental.domainmodel.*;
import com.gensym.cbu.odie.*;
import com.gensym.cbu.odieeventfilterlanguage.*;
import java.io.Serializable;
import com.gensym.cbu.mpe.*;
import com.gensym.cbu.messageserver.*;

public class CbuPopulator implements Runnable, Populator
{
  DomainModel domainModel;

  public void populate(ServerImpl server)
  {
    com.gensym.denali.eval.Compiler.trace = true;
    try {
      OdiePopulator odiePopulator = new OdiePopulator();
      odiePopulator.populate(server);

      OdieEventFilterLanguagePopulator odieEventFilterLanguagePopulator = new OdieEventFilterLanguagePopulator();
      odieEventFilterLanguagePopulator.populate(server);

      //      MpePopulator mpePopulator = new MpePopulator();
      //      mpePopulator.populate(server);
      SyntaxModule syntaxModule = new SyntaxModule();
      syntaxModule.populate(server);

      MessageServerPopulator messageServerPopulator = new MessageServerPopulator();
      messageServerPopulator.populate(server);

      DomainModelPopulator domainModelPopulator = new DomainModelPopulator();
      domainModelPopulator.populate(server);

      Module opexModule = new ModuleImpl("com.gensym.cbu.opex");
      server.addModule(opexModule);
      
      Schematic schematic = new SchematicImpl(opexModule,"Opex Schematic");
      schematic.setBounds(new NodeVisualInfo(0,0,700,500));
      opexModule.addRoot((Serializable)schematic);
            
    }
    catch (Exception e)
      {
	System.out.println("trouble populating test module\n");
	e.printStackTrace();
      }
  }

  @Override
  public void run()
  {
    int i = 0;
    try {
      while (true)
	{
	  Thread.sleep(60000);
	  System.out.println("DomainModelRunning");
	}
    } catch (Exception ie)
      {
	System.out.println("Test App loop Problem\n");
	ie.printStackTrace();
      }
  }


  static String htmlText = 
  "<html>"+
  "<head>"+
  "<title>denali_white_paper</title>"+
  "</head>"+
  "<body>"+
  "Denali White Paper"+
  "<p>Denali is the code name for a new application server base technology"+
  "for Gensym's application products.&nbsp; Its primary goal is"+
  "<br>to support the development and deployment of visual languages for online,"+
  "intelligent systems.&nbsp; It must provide openness, extensibility, component-orientation,"+
  "temporal constructs, rule and/or event driven programming, distributed"+
  "programming, distributed client interaction, and simple and powerful connectivity"+
  "to a wide range of data sources.&nbsp; To meet such a set of requirements"+
  "at minimum cost in 1999, Java is the only reasonable choice.&nbsp; This"+
  "paper discusses the fundamental definitions of Denali, its data structures,"+
  "and primary interfaces."+
  "<p>Large Scale Architecture"+
  "</body>"+
  "</html>";
}




