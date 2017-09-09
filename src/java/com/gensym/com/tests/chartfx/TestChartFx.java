package com.gensym.com.tests.chartfx;

import java.awt.*;
import javax.swing.*;
import com.gensym.com.beans.chartfxlib.*;
import com.gensym.com.*;
import java.awt.event.*;

public class TestChartFx extends JFrame implements ComponentListener{
	
	
	protected SoftwarefxChartfx aChart = null;
	protected SoftwarefxChartfx anotherChart = null;
	
		
	public static void main(String argv[]){
				
		TestChartFx app = new TestChartFx();
		app.setup();		
	}
	public void setup(){
	
/*        
	ActiveXTraceTool tool =  new ActiveXTraceTool();
      tool.setAxTraceLevel((short)10);
      tool.setLogToStdout(true);
  */      
		JTabbedPane tabPane = new JTabbedPane(1);
            try {
            
            aChart = new SoftwarefxChartfx();
		//System.out.println("about to new another");
		anotherChart = new SoftwarefxChartfx();
		//System.out.println("after to new another");		
		
		
		
		//SoftwarefxChartfx anotherChart = new SoftwarefxChartfx();
		//getContentPane().add(aChart,"Center");
		getContentPane().addComponentListener(this);	
		getContentPane().add(tabPane,"Center");
		tabPane.addTab("chart 1",aChart);
		tabPane.addTab("chart 2",anotherChart);		
            setSize(700,500);

		setVisible(true);
		//aChart.setSize(new Dimension(800,900));
		//System.out.println("about to setcharttype");
		aChart.setAxChartType((short)(GalleryConstants.LINES));// | 536870912));//536870912 should = CT_EVENSPACING
		//aChart.setAxMaxValues(100);
		aChart.setAxRealTimeStyle((short)(2));
		aChart.OpenDataEx((short)(OpenDataConstants.COD_VALUES | OpenDataConstants.COD_REMOVE),0,0);
		aChart.CloseData((short)(OpenDataConstants.COD_VALUES | OpenDataConstants.COD_REMOVE));
		aChart.setAxToolBar(true);
		aChart.setAxTBItemID((short)4,ToolIDConstants.CFX_ID_DLGPRINT);
		aChart.setAxEnableTBItem((short)0,(short)-1);
		
	//another chart
            System.out.println("Before initializeProxy");
            anotherChart.initializeProxy();
            System.out.println("After initializeProxy");
            anotherChart.setAxChartType((short)(GalleryConstants.LINES));// | 536870912));//536870912 should = CT_EVENSPACING
		System.out.println("After setting chart type");
            //anotherChart.setAxMaxValues(100);
		anotherChart.setAxRealTimeStyle((short)(2));
            System.out.println("After setting real time style type");
		
            /*
            anotherChart.OpenDataEx((short)(OpenDataConstants.COD_VALUES | OpenDataConstants.COD_REMOVE),0,0);
		anotherChart.CloseData((short)(OpenDataConstants.COD_VALUES | OpenDataConstants.COD_REMOVE));
		*/
            System.out.println("After opening and closing data");
            anotherChart.setAxToolBar(true);
		anotherChart.setAxTBItemID((short)4,ToolIDConstants.CFX_ID_DLGPRINT);
		anotherChart.setAxEnableTBItem((short)0,(short)-1);

            System.out.println("After configuring both charts");

		int i=0;
		// open for adding all data
		//aChart.OpenDataEx((short)(OpenDataConstants.COD_VALUES),3,1);
		for(i = 0;i<200;i++){
			if(i==0){
				aChart.OpenDataEx((short)(OpenDataConstants.COD_VALUES),5,1);
				anotherChart.OpenDataEx((short)(OpenDataConstants.COD_VALUES),5,1);
				//aChart.OpenDataEx((short)(OpenDataConstants.COD_VALUES),1,1);
				
				// first data point
				aChart.setAxThisSerie((short)0);	
				int value = (int)(Math.random()*200);
				//System.out.println(i+" ,one,"+value);
				aChart.setAxValue(0,(double)value);	
							
				//secomd data point
				aChart.setAxThisSerie((short)1);
				value = (int)(Math.random()*200);
				//System.out.println(i+",two,"+value);
				aChart.setAxValue(0,(double)value);	
									
				//third data point							
				aChart.setAxThisSerie((short)2);
				value = (int)(Math.random()*200);
				//System.out.println(i+",three,"+value);
				aChart.setAxValue(0,(double)value);
				
				//4th data point							
				aChart.setAxThisSerie((short)3);
				value = (int)(Math.random()*200);
				//System.out.println(i+",three,"+value);
				aChart.setAxValue(0,(double)value);
				
				//5th data point							
				aChart.setAxThisSerie((short)4);
				value = (int)(Math.random()*200);
				//System.out.println(i+",three,"+value);
				aChart.setAxValue(0,(double)value);
				
		// second chart
				// first data point
				anotherChart.setAxThisSerie((short)0);	
				value = (int)(Math.random()*200);
				//System.out.println(i+" ,one,"+value);
				anotherChart.setAxValue(0,(double)value);	
							
				//secomd data point
				anotherChart.setAxThisSerie((short)1);
				value = (int)(Math.random()*200);
				//System.out.println(i+",two,"+value);
				anotherChart.setAxValue(0,(double)value);	
									
				//third data point							
				anotherChart.setAxThisSerie((short)2);
				value = (int)(Math.random()*200);
				//System.out.println(i+",three,"+value);
				anotherChart.setAxValue(0,(double)value);
				
				//4th data point							
				aChart.setAxThisSerie((short)3);
				value = (int)(Math.random()*200);
				//System.out.println(i+",three,"+value);
				anotherChart.setAxValue(0,(double)value);
				
				//5th data point							
				aChart.setAxThisSerie((short)4);
				value = (int)(Math.random()*200);
				//System.out.println(i+",three,"+value);
				anotherChart.setAxValue(0,(double)value);
				
				
				
				// close and force scroll of graph to new data added
				aChart.CloseData((short)(OpenDataConstants.COD_VALUES | OpenDataConstants.COD_REALTIMESCROLL));// | OpenDataConstants.COD_SCROLLLEGEND));// || OpenDataConstants.COD_REALTIME);	
				anotherChart.CloseData((short)(OpenDataConstants.COD_VALUES | OpenDataConstants.COD_REALTIMESCROLL));// | OpenDataConstants.COD_SCROLLLEGEND));// || OpenDataConstants.COD_REALTIME);	
			}
			
			else{
				
				//open and append data
				aChart.OpenDataEx((short)(OpenDataConstants.COD_VALUES |OpenDataConstants.COD_ADDPOINTS),5,1);
				anotherChart.OpenDataEx((short)(OpenDataConstants.COD_VALUES |OpenDataConstants.COD_ADDPOINTS),5,1);
				//aChart.OpenDataEx((short)(OpenDataConstants.COD_VALUES | OpenDataConstants.COD_ADDPOINTS),1,1);
				
				// first data point
				aChart.setAxThisSerie((short)0);		
				int value = (int)(Math.random()*200);
				//System.out.println(i+" ,one,"+value);
				aChart.setAxValue(0,(double)value);
				
				//secomd data point
				aChart.setAxThisSerie((short)1);	
				value = (int)(Math.random()*200);
				//System.out.println(i+",two,"+value);
				aChart.setAxValue(0,(double)value);
				
				//third data point
				aChart.setAxThisSerie((short)2);	
				value = (int)(Math.random()*200);
				//System.out.println(i+",three,"+value);
				aChart.setAxValue(0,(double)value);
				
				//4th data point							
				aChart.setAxThisSerie((short)3);
				value = (int)(Math.random()*200);
				//System.out.println(i+",three,"+value);
				aChart.setAxValue(0,(double)value);
				
				//5th data point							
				aChart.setAxThisSerie((short)4);
				value = (int)(Math.random()*200);
				//System.out.println(i+",three,"+value);
				aChart.setAxValue(0,(double)value);
			
	// another chart
	
				// first data point
				anotherChart.setAxThisSerie((short)0);		
				value = (int)(Math.random()*200);
				//System.out.println(i+" ,one,"+value);
				anotherChart.setAxValue(0,(double)value);
				
				//secomd data point
				anotherChart.setAxThisSerie((short)1);	
				value = (int)(Math.random()*200);
				//System.out.println(i+",two,"+value);
				anotherChart.setAxValue(0,(double)value);
				
				//third data point
				anotherChart.setAxThisSerie((short)2);	
				value = (int)(Math.random()*200);
				//System.out.println(i+",three,"+value);
				anotherChart.setAxValue(0,(double)value);
				
				//4th data point							
				anotherChart.setAxThisSerie((short)3);
				value = (int)(Math.random()*200);
				//System.out.println(i+",three,"+value);
				anotherChart.setAxValue(0,(double)value);
				
				//5th data point							
				anotherChart.setAxThisSerie((short)4);
				value = (int)(Math.random()*200);
				//System.out.println(i+",three,"+value);
				anotherChart.setAxValue(0,(double)value);
				
				
				
				// close and force scroll of graph to new data added
				aChart.CloseData((short)(OpenDataConstants.COD_VALUES | OpenDataConstants.COD_REALTIMESCROLL));// | OpenDataConstants.COD_SCROLLLEGEND));// || OpenDataConstants.COD_REALTIME);					
				anotherChart.CloseData((short)(OpenDataConstants.COD_VALUES | OpenDataConstants.COD_REALTIMESCROLL));// | OpenDataConstants.COD_SCROLLLEGEND));// || OpenDataConstants.COD_REALTIME);	
				
			}
			
			// redraw graph
			aChart.Refresh();
			
		}
		// close after all data has been added
		//aChart.CloseData((short)(OpenDataConstants.COD_VALUES | OpenDataConstants.COD_REALTIMESCROLL));// | OpenDataConstants.COD_SCROLLLEGEND));// || OpenDataConstants.COD_REALTIME);	
		
	
            // Done so delete resources.


              aChart.delete();
              anotherChart.delete();
              System.exit(0);
            }
            catch (ActiveXException e)
            {
              e.printStackTrace();
            }
	}	
	
	
 	@Override
 	public void componentResized(ComponentEvent e){
        try {
 		//System.out.println("size of frame = "+getSize());
 		//System.out.println("Content Pane = "+getContentPane().getSize()); 		
 		//System.out.println("graph size = "+aChart.getSize()); 
 		//aChart.setSize(getContentPane().getSize());
 		//System.out.println("graph size after resize = "+aChart.getSize());
 		Container cont = (Container)e.getSource();
 		//System.out.println(aChart.getAxToolSize());
 		System.out.println(cont.getSize());
 		aChart.setSize(cont.getSize());
 		aChart.Refresh();
 		//resize();

        }
        catch (ActiveXException f)
        {
            f.printStackTrace();
        } 	 	
 	}
 	

 	@Override
 	public void componentMoved(ComponentEvent e){}
 	
 	@Override
 	public void componentShown(ComponentEvent e){}
 	
 	@Override
 	public void componentHidden(ComponentEvent e){}

}
