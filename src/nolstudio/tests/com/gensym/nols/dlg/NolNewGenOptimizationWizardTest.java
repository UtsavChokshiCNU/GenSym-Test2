package com.gensym.nols.dlg;

import static org.junit.Assert.*;

import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.MouseEvent;

import javax.swing.JFrame;
import javax.swing.JMenuBar;
import javax.swing.JTable;
import javax.swing.JToggleButton;
import javax.swing.event.ListSelectionEvent;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.mockito.Mockito;
import org.mockito.MockitoAnnotations;
import org.mockito.Spy;
import org.mockito.runners.MockitoJUnitRunner;

import com.gensym.nols.data.Objective;
import com.gensym.nols.dlg.NolNewGenOptimizationWizard.ClassifyRenderer;
import com.gensym.nols.dlg.NolNewGenOptimizationWizard.ControlAction;
import com.gensym.nols.main.NolMainFrame;

@RunWith(MockitoJUnitRunner.class)
public class NolNewGenOptimizationWizardTest {

	private NolNewGenOptimizationWizard nolNewGenOptimizationWizard;
	@Spy
	private NolMainFrame dw;
	@Spy
	private Objective objective;
	private JMenuBar menubar;
	private int[] width;
	private MouseEvent mouseEvent;

	@Before
	public void init() {
		MockitoAnnotations.initMocks(this);
		dw = Mockito.spy(NolMainFrame.class);
		menubar = new JMenuBar();
		dw.setAlwaysOnTop(true);
		dw.setVisible(true);
		dw.setTitle("Title");
		dw.setJMenuBar(menubar);
		dw.setSize(4, 5);
		dw.setBackground(new Color(45));
		dw.setBounds(2, 3, 20, 20);
		dw.setEnabled(true);
		nolNewGenOptimizationWizard = new NolNewGenOptimizationWizard(dw);
		width = new int[2];
		width[0] = 1;
		width[1] = 2;
		objective = Mockito.spy(Objective.class);
		Mockito.doNothing().when(dw).showOKDialog(Mockito.anyString());
	}

	@Test
	public void testModifyStep() {
		nolNewGenOptimizationWizard.resetData();
		nolNewGenOptimizationWizard.modifyStep(false);
		assertEquals(1, nolNewGenOptimizationWizard.currentStep);
		nolNewGenOptimizationWizard.currentStep = 2;
		nolNewGenOptimizationWizard.modifyStep(false);
		assertEquals(1, nolNewGenOptimizationWizard.currentStep);
		nolNewGenOptimizationWizard.modifyStep(true);
		assertEquals(2, nolNewGenOptimizationWizard.currentStep);
		nolNewGenOptimizationWizard.currentStep = 3;
		nolNewGenOptimizationWizard.modifyStep(false);
		assertEquals(2, nolNewGenOptimizationWizard.currentStep);
		nolNewGenOptimizationWizard.modifyStep(true);
		assertEquals(3, nolNewGenOptimizationWizard.currentStep);
		nolNewGenOptimizationWizard.currentStep = 4;
		nolNewGenOptimizationWizard.modifyStep(false);
		assertEquals(3, nolNewGenOptimizationWizard.currentStep);
		nolNewGenOptimizationWizard.modifyStep(true);
		assertEquals(4, nolNewGenOptimizationWizard.currentStep);
		nolNewGenOptimizationWizard.currentStep = 5;
		nolNewGenOptimizationWizard.modifyStep(false);
		assertEquals(4, nolNewGenOptimizationWizard.currentStep);
		nolNewGenOptimizationWizard.modifyStep(true);
		assertEquals(5, nolNewGenOptimizationWizard.currentStep);
		nolNewGenOptimizationWizard.currentStep = 6;
		nolNewGenOptimizationWizard.modifyStep(false);
		assertEquals(5, nolNewGenOptimizationWizard.currentStep);
		nolNewGenOptimizationWizard.modifyStep(true);
		assertEquals(6, nolNewGenOptimizationWizard.currentStep);
	}

	@Test
	public void testFinishAction() {
		nolNewGenOptimizationWizard.resetData();
		assertTrue(nolNewGenOptimizationWizard.finishAction());
	}

	@Test
	public void testGetOptimization() {
		assertNull(nolNewGenOptimizationWizard.getOptimization());
	}

	@Test
	public void testControlAction() {
		ControlAction controlAction = nolNewGenOptimizationWizard.new ControlAction();
		try {
			ActionEvent actionEvent = new ActionEvent(menubar, 1, "Add");
			controlAction.actionPerformed(actionEvent);
			assertTrue(nolNewGenOptimizationWizard.verifyAddControlAction());
			actionEvent = new ActionEvent(menubar, 1, "Remove");
			controlAction.actionPerformed(actionEvent);
			assertTrue(nolNewGenOptimizationWizard.verifyRemoveControlAction());
		} catch (ArrayIndexOutOfBoundsException ae) {
			assertEquals(0, dw.getGraphics().getColor().getRed());
		}

		ListSelectionEvent le = new ListSelectionEvent(dw, 0, 1, true);
		controlAction.valueChanged(le);
		le = new ListSelectionEvent(dw, 0, 1, false);
		controlAction.valueChanged(le);
		le = new ListSelectionEvent(dw, 0, 1, true);
		controlAction.valueChanged(le);
		assertEquals(1, controlAction.getKeys().length);

	}

	@Test
	public void testClassifyRendrer() {
		ClassifyRenderer classifyRenderer = nolNewGenOptimizationWizard.new ClassifyRenderer();
		JToggleButton jToggleButton = Mockito.spy(JToggleButton.class);
		JTable jTable = Mockito.spy(JTable.class);
		assertNotNull(classifyRenderer.getTableCellRendererComponent(jTable, jToggleButton, true, true, 1, 2));
		assertNull(classifyRenderer.getTableCellRendererComponent(jTable, new Object(), true, true, 1, 2));
	}
}
