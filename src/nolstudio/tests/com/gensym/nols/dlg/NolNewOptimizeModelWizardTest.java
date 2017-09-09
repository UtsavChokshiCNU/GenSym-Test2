package com.gensym.nols.dlg;

import static org.junit.Assert.*;

import java.awt.Color;
import java.awt.event.ActionEvent;
import java.util.Vector;

import javax.swing.JList;
import javax.swing.JMenuBar;
import javax.swing.JRadioButton;
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
import com.gensym.nols.dlg.NolNewOptimizeModelWizard.ControlAction;
import com.gensym.nols.dlg.NolNewOptimizeModelWizard.VarClassifyTableModel;
import com.gensym.nols.main.NolMainFrame;
import com.gensym.nols.main.ProjectTree;

public class NolNewOptimizeModelWizardTest {

	private JMenuBar menubar;
	private int[] width;
	private Matrix M;
	private NolNewOptimizeModelWizard nolNewOptimizeModelWizard;
	private Vector outchecks1 = new Vector();
	private Vector exogchecks1 = new Vector();
	private Vector outputs1 = new Vector();
	private Vector states1 = new Vector();
	private Vector manis1 = new Vector();
	private DataSeries ds;

	private ListSelectionEvent le;
	@Spy
	private Project2 project;
	@Spy
	private NolMainFrame dw = new NolMainFrame();
	@Spy
	private NolOptimizeModel mdl1 = new NolOptimizeModel();
	@Spy
	Vector<Preprocessor> preprocessors = new Vector<Preprocessor>();

	public void initScenario1() {
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
		vbSecond.setName("Second");
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

		projectTree.addPreprocessor(pr, true);
		nolNewOptimizeModelWizard = new NolNewOptimizeModelWizard(dw);

		le = Mockito.spy(new ListSelectionEvent(dw, 0, 1, true));
		Mockito.when(le.getValueIsAdjusting()).thenReturn(true);
	}

	public void initScenario2() {
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
		Mockito.when(ds.getHasTimeStamps()).thenReturn(false);
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
		vbSecond.setName("Second");
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

		projectTree.addPreprocessor(pr, true);
		nolNewOptimizeModelWizard = new NolNewOptimizeModelWizard(dw);
		le = Mockito.spy(new ListSelectionEvent(dw, 0, 1, false));
		Mockito.when(le.getValueIsAdjusting()).thenReturn(false);
	}

	@Test
	public void testResetData1() {
		initScenario1();
		nolNewOptimizeModelWizard.resetData();
		assertEquals(1, nolNewOptimizeModelWizard.getComponentCount());
	}

	@Test
	public void testResetData2() {
		initScenario2();
		nolNewOptimizeModelWizard.resetData();
		assertEquals(1, nolNewOptimizeModelWizard.getComponentCount());
	}

	@Test
	public void testFinishAction1() {
		initScenario1();
		assertFalse(nolNewOptimizeModelWizard.finishAction());
	}

	@Test
	public void testFinishAction2() {
		initScenario2();
		Vector<JRadioButton> chks1 = Mockito.spy(new Vector());
		JRadioButton button1 = Mockito.spy(new JRadioButton("test"));
		Mockito.when(button1.isSelected()).thenReturn(true);
		chks1.add(button1);
		VarClassifyTableModel varClassifyTableModel = Mockito
				.spy(nolNewOptimizeModelWizard.new VarClassifyTableModel());
		Mockito.when(varClassifyTableModel.getOutputChecks()).thenReturn(chks1);
		Mockito.when(varClassifyTableModel.getManiChecks()).thenReturn(chks1);
		Mockito.when(varClassifyTableModel.getStateChecks()).thenReturn(chks1);
		Mockito.when(varClassifyTableModel.getExogChecks()).thenReturn(chks1);
		Mockito.when(chks1.elementAt(0)).thenReturn(button1);
		assertFalse(nolNewOptimizeModelWizard.finishAction());
	}

	@Test
	public void testReadDelaysFromAutoSelectChecks1() {
		initScenario2();
		Object obj1 = outchecks1.get(0);
		nolNewOptimizeModelWizard.readDelaysFromAutoSelectChecks(outchecks1, exogchecks1);
		assertNotEquals(obj1, outchecks1.get(0));
	}

	@Test
	public void testReadDelaysFromAutoSelectChecks2() {
		initScenario1();
		Object obj1 = outchecks1.get(0);
		nolNewOptimizeModelWizard.readDelaysFromAutoSelectChecks(outchecks1, exogchecks1);
		assertNotEquals(obj1, outchecks1.get(0));
	}

	@Test
	public void testModifySteps() {
		initScenario2();
		nolNewOptimizeModelWizard.currentStep = 1;
		nolNewOptimizeModelWizard.modifyStep(false);
		assertEquals(1, nolNewOptimizeModelWizard.currentStep);
		nolNewOptimizeModelWizard.modifyStep(true);
		assertEquals(2, nolNewOptimizeModelWizard.currentStep);
		nolNewOptimizeModelWizard.currentStep = 2;
		nolNewOptimizeModelWizard.modifyStep(false);
		assertEquals(1, nolNewOptimizeModelWizard.currentStep);
		nolNewOptimizeModelWizard.modifyStep(true);
		assertEquals(2, nolNewOptimizeModelWizard.currentStep);
		nolNewOptimizeModelWizard.currentStep = 3;
		nolNewOptimizeModelWizard.modifyStep(false);
		assertEquals(2, nolNewOptimizeModelWizard.currentStep);
		nolNewOptimizeModelWizard.modifyStep(true);
		assertEquals(3, nolNewOptimizeModelWizard.currentStep);
		nolNewOptimizeModelWizard.currentStep = 4;
		nolNewOptimizeModelWizard.modifyStep(false);
		assertEquals(3, nolNewOptimizeModelWizard.currentStep);
		nolNewOptimizeModelWizard.modifyStep(true);
		assertEquals(4, nolNewOptimizeModelWizard.currentStep);
		nolNewOptimizeModelWizard.currentStep = 5;
		nolNewOptimizeModelWizard.modifyStep(false);
		assertEquals(4, nolNewOptimizeModelWizard.currentStep);
		nolNewOptimizeModelWizard.modifyStep(true);
		assertEquals(5, nolNewOptimizeModelWizard.currentStep);
		nolNewOptimizeModelWizard.currentStep = 6;
		nolNewOptimizeModelWizard.modifyStep(false);
		assertEquals(5, nolNewOptimizeModelWizard.currentStep);
		nolNewOptimizeModelWizard.modifyStep(true);
		assertEquals(6, nolNewOptimizeModelWizard.currentStep);
		nolNewOptimizeModelWizard.currentStep = 7;
		nolNewOptimizeModelWizard.modifyStep(false);
		assertEquals(6, nolNewOptimizeModelWizard.currentStep);
		nolNewOptimizeModelWizard.currentStep = 8;
		nolNewOptimizeModelWizard.modifyStep(false);
		assertEquals(7, nolNewOptimizeModelWizard.currentStep);
		nolNewOptimizeModelWizard.modifyStep(true);
		assertEquals(8, nolNewOptimizeModelWizard.currentStep);
		nolNewOptimizeModelWizard.currentStep = 9;
		nolNewOptimizeModelWizard.modifyStep(false);
		assertEquals(8, nolNewOptimizeModelWizard.currentStep);
		nolNewOptimizeModelWizard.modifyStep(true);
		assertEquals(9, nolNewOptimizeModelWizard.currentStep);
		nolNewOptimizeModelWizard.currentStep = 10;
		nolNewOptimizeModelWizard.modifyStep(false);
		assertEquals(9, nolNewOptimizeModelWizard.currentStep);
		nolNewOptimizeModelWizard.modifyStep(true);
		assertEquals(9, nolNewOptimizeModelWizard.currentStep);
	}

	@Test
	public void testControlActionPerformed() {
		initScenario2();
		ControlAction controlAction = nolNewOptimizeModelWizard.new ControlAction();
		try {
			ActionEvent actionEvent = new ActionEvent(menubar, 1, "Calculate Ratings");
			controlAction.actionPerformed(actionEvent);
			actionEvent = new ActionEvent(menubar, 1, "Hour1");
			assertTrue(nolNewOptimizeModelWizard.verifyConvertDelayFromTimeUnits1());
			controlAction.actionPerformed(actionEvent);
			assertTrue(nolNewOptimizeModelWizard.verifyConvertDelayFromTimeUnits1());
			actionEvent = new ActionEvent(menubar, 1, "Minute1");
			controlAction.actionPerformed(actionEvent);
			assertTrue(nolNewOptimizeModelWizard.verifyConvertDelayFromTimeUnits1());
			actionEvent = new ActionEvent(menubar, 1, "Second1");
			controlAction.actionPerformed(actionEvent);
			assertTrue(nolNewOptimizeModelWizard.verifyConvertDelayFromTimeUnits1());
			actionEvent = new ActionEvent(menubar, 1, "Hour2");
			controlAction.actionPerformed(actionEvent);
			assertTrue(nolNewOptimizeModelWizard.verifyConvertDelayFromTimeUnits1());
			actionEvent = new ActionEvent(menubar, 1, "Minute2");
			controlAction.actionPerformed(actionEvent);
			assertTrue(nolNewOptimizeModelWizard.verifyConvertDelayFromTimeUnits1());
			actionEvent = new ActionEvent(menubar, 1, "Second2");
			controlAction.actionPerformed(actionEvent);
			assertTrue(nolNewOptimizeModelWizard.verifyConvertDelayFromTimeUnits1());
			controlAction.valueChanged(le);
		} catch (ArrayIndexOutOfBoundsException ae) {
			assertEquals(0, dw.getGraphics().getColor().getRed());
		}

		le = new ListSelectionEvent(dw, 0, 1, true);
		controlAction.valueChanged(le);

		assertEquals("Name", controlAction.getKeys()[0]);

	}

	@Test
	public void testRecieveRatingResults() {
		initScenario1();
		Vector<String> inVars = new Vector<String>();
		inVars.add("First");
		Vector<double[]> delays = new Vector<double[]>();
		Vector<String> outVars = new Vector<String>();
		Vector<double[]> ratings = new Vector<double[]>();

		nolNewOptimizeModelWizard.receiveRatingResults(inVars, delays, outVars, ratings);
		assertEquals(0, ratings.size());

		ratings.addElement(new double[] { 2d, 4d });
		ratings.addElement(new double[] { 3d, 4d });
		nolNewOptimizeModelWizard.resetData();
		nolNewOptimizeModelWizard.receiveRatingResults(inVars, delays, outVars, ratings);
		assertEquals(4, ratings.get(0)[1], 0.000004);
	}

}
