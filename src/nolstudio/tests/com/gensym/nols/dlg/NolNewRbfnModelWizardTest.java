package com.gensym.nols.dlg;

import static org.junit.Assert.*;

import java.awt.Color;
import java.awt.Component;
import java.awt.event.ActionEvent;
import java.util.Vector;

import javax.swing.JMenuBar;
import javax.swing.JTable;
import javax.swing.JToggleButton;
import javax.swing.event.ListSelectionEvent;

import org.junit.Before;
import org.junit.Test;
import org.mockito.Mockito;
import org.mockito.MockitoAnnotations;
import org.mockito.Spy;

import com.gensym.math.matrix.Matrix;
import com.gensym.nols.data.DataSeries;
import com.gensym.nols.data.DataSource;
import com.gensym.nols.data.NolOptimizeModel;
import com.gensym.nols.data.Preprocessor;
import com.gensym.nols.data.Project2;
import com.gensym.nols.data.Variable;
import com.gensym.nols.dlg.NolNewRbfnModelWizard.AutoSelectRenderer;
import com.gensym.nols.dlg.NolNewRbfnModelWizard.AutoSelectionNoDelayTableModel;
import com.gensym.nols.dlg.NolNewRbfnModelWizard.ClassifyRenderer;
import com.gensym.nols.dlg.NolNewRbfnModelWizard.ControlAction;
import com.gensym.nols.dlg.NolNewRbfnModelWizard.DelayTableModel;
import com.gensym.nols.dlg.NolNewRbfnModelWizard.VarClassifyTableModel;
import com.gensym.nols.main.NolMainFrame;
import com.gensym.nols.main.ProjectTree;

public class NolNewRbfnModelWizardTest {
	private JMenuBar menubar;
	private int[] width;
	private Matrix M;
	private Vector outchecks1 = new Vector();
	private Vector exogchecks1 = new Vector();
	private Vector outputs1 = new Vector();
	private Vector states1 = new Vector();
	private Vector manis1 = new Vector();
	private DataSeries ds;
	private NolNewRbfnModelWizard nolNewRbfnModelWizard;
	private ListSelectionEvent le;

	@Spy
	private Project2 project;
	@Spy
	private NolMainFrame dw = new NolMainFrame();
	@Spy
	private NolOptimizeModel mdl1 = new NolOptimizeModel();
	@Spy
	Vector<Preprocessor> preprocessors = new Vector<Preprocessor>();

	@Before
	public void init() {
		MockitoAnnotations.initMocks(this);
		mdl1.setHasTimeStamps(true);
		M = new Matrix();
		M.redimension(2, 2);
		M.set(0, 0, 1);
		M.set(0, 1, 2);
		M.set(1, 0, 3);
		M.set(1, 1, 4);
		menubar = new JMenuBar();
		dw.setAlwaysOnTop(true);
		dw.setVisible(true);
		dw.setTitle("Title");
		dw.setJMenuBar(menubar);
		dw.setSize(4, 5);
		dw.setBackground(new Color(45));
		dw.setBounds(2, 3, 20, 20);
		dw.setEnabled(true);
		width = new int[2];
		width[0] = 1;
		width[1] = 2;

		ds = Mockito.spy(new DataSeries(M));
		Mockito.when(ds.getHasTimeStamps()).thenReturn(true);
		DataSource dataSource = new DataSource();
		ds.setDataSource(dataSource);
		project = dw.getProject();
		project.setName("project1");
		project.setComment("comment");
		Preprocessor pr = new Preprocessor();
		pr.setComment("prep-comment");
		pr.setName("prName");
		pr.setProject(project);
		Vector<String> names = pr.getVariableNames();
		names.add("First");
		names.add("Second");
		Vector dataSeries = pr.getDataSeries();
		dataSeries.add(0, ds);
		dataSeries.add(1, ds);
		dataSeries.add(2, ds);
		Vector<Variable> varObjects = ds.getVarObjects();
		Variable vbFirst = new Variable();
		Variable vbSecond = new Variable();
		vbFirst.setName("First");
		vbFirst.setDataSeries(ds);
		vbSecond.setName("Second");
		vbSecond.setDataSeries(ds);
		double[] stats = new double[10];
		for (int i = 0; i < 10; i++) {
			stats[i] = i + 1;
		}
		vbFirst.setStatistics(stats);
		varObjects.add(vbFirst);
		varObjects.add(vbSecond);
		project.addPreprocessor(pr);
		project.setProjectDirectory(".");
		dataSource.setProject(project);
		ProjectTree projectTree = new ProjectTree(dw);
		Vector omodels = project.getOptimizationModels();
		mdl1.setComment("comment");
		mdl1.setName("model1");
		omodels.add(mdl1);
		outchecks1.add("First");
		outchecks1.add("Second");
		exogchecks1.add("First");
		exogchecks1.add("Second");
		outputs1.add("First");
		outputs1.add("Second");
		states1.add("First");
		states1.add("Second");
		manis1.add("First");
		manis1.add("Second");
		Mockito.when(mdl1.getOutputs()).thenReturn(outputs1);
		Mockito.when(mdl1.getState()).thenReturn(states1);
		Mockito.when(mdl1.getManipulate()).thenReturn(manis1);
		Mockito.when(mdl1.getPreprocessor()).thenReturn(pr);
		Mockito.doNothing().when(dw).showOKDialog(Mockito.anyString());
		Mockito.doNothing().when(dw).showOKDialog(Mockito.anyObject());

		projectTree.addPreprocessor(pr, true);
		nolNewRbfnModelWizard = new NolNewRbfnModelWizard(dw);

		le = Mockito.spy(new ListSelectionEvent(dw, 0, 1, true));
		Mockito.when(le.getValueIsAdjusting()).thenReturn(true);
	}

	@Test
	public void testSetVisible() {
		nolNewRbfnModelWizard.setVisible(false);
		assertEquals(1, nolNewRbfnModelWizard.getComponentCount());
	}

	@Test
	public void testResetData() {
		nolNewRbfnModelWizard.resetData();
		assertEquals(255, nolNewRbfnModelWizard.getBackground().getAlpha());
	}

	@Test
	public void testModifyStep() {
		nolNewRbfnModelWizard.currentStep = 1;
		nolNewRbfnModelWizard.modifyStep(false);
		assertEquals(1, nolNewRbfnModelWizard.currentStep);
		nolNewRbfnModelWizard.modifyStep(true);
		assertEquals(2, nolNewRbfnModelWizard.currentStep);
		nolNewRbfnModelWizard.currentStep = 2;
		nolNewRbfnModelWizard.modifyStep(false);
		assertEquals(1, nolNewRbfnModelWizard.currentStep);
		nolNewRbfnModelWizard.modifyStep(true);
		assertEquals(2, nolNewRbfnModelWizard.currentStep);
		nolNewRbfnModelWizard.currentStep = 3;
		nolNewRbfnModelWizard.modifyStep(false);
		assertEquals(2, nolNewRbfnModelWizard.currentStep);
		nolNewRbfnModelWizard.modifyStep(true);
		assertEquals(3, nolNewRbfnModelWizard.currentStep);
		nolNewRbfnModelWizard.currentStep = 4;
		nolNewRbfnModelWizard.modifyStep(false);
		assertEquals(3, nolNewRbfnModelWizard.currentStep);
		nolNewRbfnModelWizard.modifyStep(true);
		assertEquals(4, nolNewRbfnModelWizard.currentStep);
		nolNewRbfnModelWizard.currentStep = 5;
		nolNewRbfnModelWizard.modifyStep(false);
		assertEquals(4, nolNewRbfnModelWizard.currentStep);
		nolNewRbfnModelWizard.modifyStep(true);
		assertEquals(5, nolNewRbfnModelWizard.currentStep);
		nolNewRbfnModelWizard.currentStep = 6;
		nolNewRbfnModelWizard.modifyStep(false);
		assertEquals(5, nolNewRbfnModelWizard.currentStep);
		nolNewRbfnModelWizard.modifyStep(true);
		assertEquals(6, nolNewRbfnModelWizard.currentStep);
		nolNewRbfnModelWizard.currentStep = 7;
		nolNewRbfnModelWizard.modifyStep(false);
		assertEquals(6, nolNewRbfnModelWizard.currentStep);
	}

	@Test
	public void testControlAction() {
		ControlAction controlAction = nolNewRbfnModelWizard.new ControlAction();
		ActionEvent actionEvent = new ActionEvent(menubar, 1, "Calculate Ratings");
		controlAction.actionPerformed(actionEvent);
		nolNewRbfnModelWizard.verifyControlActionCalculateRatings();
		actionEvent = new ActionEvent(menubar, 1, "Calculate Ratings");
		controlAction.actionPerformed(actionEvent);
		nolNewRbfnModelWizard.verifyControlActionCalculateRatings();
		actionEvent = new ActionEvent(menubar, 1, "Hour");
		controlAction.actionPerformed(actionEvent);
		assertEquals(1, nolNewRbfnModelWizard.verifyDelayTimeSettingFlag());
		actionEvent = new ActionEvent(menubar, 1, "Minute");
		controlAction.actionPerformed(actionEvent);
		assertEquals(2, nolNewRbfnModelWizard.verifyDelayTimeSettingFlag());
		actionEvent = new ActionEvent(menubar, 1, "Second");
		controlAction.actionPerformed(actionEvent);
		assertEquals(3, nolNewRbfnModelWizard.verifyDelayTimeSettingFlag());
		actionEvent = new ActionEvent(menubar, 1, "Auto");
		controlAction.actionPerformed(actionEvent);
		assertEquals(3, nolNewRbfnModelWizard.verifyDelayTimeSettingFlag());
		actionEvent = new ActionEvent(menubar, 1, "Manual");
		controlAction.actionPerformed(actionEvent);
		assertEquals(3, nolNewRbfnModelWizard.verifyDelayTimeSettingFlag());
		actionEvent = new ActionEvent(menubar, 1, "OKProp");
		controlAction.actionPerformed(actionEvent);
		assertEquals(3, nolNewRbfnModelWizard.verifyDelayTimeSettingFlag());
		ListSelectionEvent le = new ListSelectionEvent(dw, 0, 1, false);
		controlAction.valueChanged(le);

		le = new ListSelectionEvent(dw, 0, 1, true);
		controlAction.valueChanged(le);

		assertEquals("Name", controlAction.getKeys()[0]);
	}

	@Test
	public void testRecieveRatingResults() {
		Vector<String> inVars = new Vector<String>();
		inVars.addElement("First");
		Vector<String> outVars = new Vector<String>();
		Vector<String> delays = new Vector<String>();
		Vector ratings = new Vector();
		double[] doubleArr = new double[2];
		doubleArr[0] = 0;
		doubleArr[1] = 1;
		ratings.addElement(doubleArr);
		ratings.addElement(doubleArr);
		nolNewRbfnModelWizard.receiveRatingResults(inVars, delays, outVars, ratings);
		assertEquals(0, nolNewRbfnModelWizard.getX());
		assertEquals(0, nolNewRbfnModelWizard.getY());
	}

	@Test
	public void testClassifyRenderer() {
		ClassifyRenderer classifyRenderer = nolNewRbfnModelWizard.new ClassifyRenderer();
		JTable jTable = new JTable();
		JToggleButton jToggleButton = new JToggleButton();
		assertTrue(classifyRenderer.getTableCellRendererComponent(jTable, jToggleButton, true, true, 1, 1).isVisible());
	}

	@Test
	public void testAutoSelectRenderer() {
		AutoSelectRenderer autoSelectRenderer = nolNewRbfnModelWizard.new AutoSelectRenderer();
		JTable jTable = new JTable();
		JToggleButton jToggleButton = new JToggleButton();
		assertTrue(
				autoSelectRenderer.getTableCellRendererComponent(jTable, jToggleButton, true, true, 2, 2).isVisible());
	}

	@Test
	public void testDelayTableModel() {
		DelayTableModel delayTableModel = nolNewRbfnModelWizard.new DelayTableModel();
		Vector names = new Vector();
		names.addElement("First");
		delayTableModel.setNames(names);
		delayTableModel.setValueAt("23.5", 0, 0);
		assertEquals(4, delayTableModel.getColumnCount());
		assertEquals(1, delayTableModel.getRowCount());
		assertEquals("First", delayTableModel.getValueAt(0, 0));
		assertEquals("0.0", delayTableModel.getValueAt(0, 1));
		assertEquals("0.0", delayTableModel.getValueAt(0, 2));
		assertEquals("0.0", delayTableModel.getValueAt(0, 3));
	}

	@Test
	public void testVarClassifyTableModel() {
		VarClassifyTableModel varClassifyTableModel = nolNewRbfnModelWizard.new VarClassifyTableModel();
		Vector names = new Vector();
		names.addElement("First");
		varClassifyTableModel.setNames(names);
		varClassifyTableModel.setValueAt("23.5", 0, 0);
		assertEquals(4, varClassifyTableModel.getColumnCount());
		assertEquals(1, varClassifyTableModel.getRowCount());
		assertEquals("First", varClassifyTableModel.getValueAt(0, 0));
		assertTrue(varClassifyTableModel.getValueAt(0, 1) instanceof Component);
		assertTrue(varClassifyTableModel.getValueAt(0, 2) instanceof Component);
		assertTrue(varClassifyTableModel.getValueAt(0, 3) instanceof Component);
	}
	
	@Test
	public void testAutoSelectionNoDelayTableModel() {
		AutoSelectionNoDelayTableModel autoSelectionNoDelayTableModel = nolNewRbfnModelWizard.new AutoSelectionNoDelayTableModel();
		Vector names = new Vector();
		names.addElement("First");
		autoSelectionNoDelayTableModel.setNames(names);
		autoSelectionNoDelayTableModel.setValueAt("23.5", 0, 0);
		assertEquals(3, autoSelectionNoDelayTableModel.getColumnCount());
		assertEquals(1, autoSelectionNoDelayTableModel.getRowCount());
		assertEquals("First", autoSelectionNoDelayTableModel.getValueAt(0, 0));
		assertEquals("", autoSelectionNoDelayTableModel.getValueAt(0, 1).toString());
		assertTrue(autoSelectionNoDelayTableModel.getValueAt(0, 2) instanceof Component);
		assertEquals("", autoSelectionNoDelayTableModel.getValueAt(0, 3));
	}
	
	@Test
	public void testFinishAction() {
		nolNewRbfnModelWizard.resetData();
		assertFalse(nolNewRbfnModelWizard.finishAction());
	}
}
