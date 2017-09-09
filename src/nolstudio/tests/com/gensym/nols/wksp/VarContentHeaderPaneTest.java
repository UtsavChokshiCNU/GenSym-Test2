package com.gensym.nols.wksp;

import static org.junit.Assert.assertEquals;

import java.awt.GridLayout;
import java.util.ListResourceBundle;
import java.util.ResourceBundle;

import javax.swing.JLabel;
import javax.swing.SwingConstants;

import org.junit.Before;
import org.junit.Test;

import com.gensym.nols.main.NolMainFrame;
import com.gensym.nols.wksp.NolOptimizationWKSP.VarContentHeaderPane;

public class VarContentHeaderPaneTest {

	private NolMainFrame frame;
	private VarContentHeaderPane pane;

	public static void setTestResources() {
		ResourceBundle resources = new ListResourceBundle() {

			@Override
			protected Object[][] getContents() {
				return new Object[][] {{"OptimizationWKSP_Delay", "Wait"}, 
									   {"HourLabel", "Hour"},
									   {"MinuteLabel", "Minute"},
									   {"SecondLabel", "Second"}};
			}};
			
		NolMainFrame.setNolResources(resources);
	}
	
	@Before
	public void setup() {
		frame = new NolMainFrame();
		pane = new VarContentHeaderPane(frame, 0);
	}
	
	@Test
	public void testNumberOfColumns() {
		GridLayout layout = (GridLayout) pane.getLayout();
		assertEquals(4, layout.getColumns());
	}

	@Test
	public void testSecondColumnName() {
		assertEquals("Delay", getDelayLabel().getText());
	}

	@Test
	public void testSecondColumnNameGetFromResources() {
		setTestResources();
		pane = new VarContentHeaderPane(frame, 0);
		assertEquals("Wait", getDelayLabel().getText());

		pane = new VarContentHeaderPane(frame, 1);
		assertEquals("Wait(Hour)", getDelayLabel().getText());

		pane = new VarContentHeaderPane(frame, 2);
		assertEquals("Wait(Minute)", getDelayLabel().getText());

		pane = new VarContentHeaderPane(frame, 3);
		assertEquals("Wait(Second)", getDelayLabel().getText());

	}
	
	@Test
	public void testLabelIsCentered() {
		assertEquals(SwingConstants.CENTER,	
				getDelayLabel().getHorizontalAlignment());
	}

	private JLabel getDelayLabel() {
		return ((JLabel) pane.getComponents()[1]);
	}
}
