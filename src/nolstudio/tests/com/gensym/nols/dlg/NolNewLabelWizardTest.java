package com.gensym.nols.dlg;

import static org.junit.Assert.*;

import java.awt.Color;
import java.awt.event.ActionEvent;
import java.util.Vector;

import javax.swing.JMenuBar;
import javax.swing.event.DocumentEvent;
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
import com.gensym.nols.dlg.NolNewLabelWizard.ControlAction;
import com.gensym.nols.main.NolMainFrame;
import com.gensym.nols.main.ProjectTree;
import com.sun.org.apache.xerces.internal.dom.DocumentImpl;

public class NolNewLabelWizardTest {
	private JMenuBar menubar;
	private int[] width;
	private Matrix M;
	private NolNewLabelWizard nolNewLabelWizard;
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
		nolNewLabelWizard = new NolNewLabelWizard(dw, "title");

		le = Mockito.spy(new ListSelectionEvent(dw, 0, 1, true));
		Mockito.when(le.getValueIsAdjusting()).thenReturn(true);
	}

	@Test
	public void testModifyStep() {
		nolNewLabelWizard.currentStep = 1;
		nolNewLabelWizard.modifyStep(false);
		assertEquals(1, nolNewLabelWizard.currentStep);
		nolNewLabelWizard.modifyStep(true);
		assertEquals(2, nolNewLabelWizard.currentStep);
		nolNewLabelWizard.currentStep = 2;
		nolNewLabelWizard.modifyStep(false);
		assertEquals(1, nolNewLabelWizard.currentStep);
		nolNewLabelWizard.modifyStep(true);
		assertEquals(2, nolNewLabelWizard.currentStep);
	}

	@Test
	public void testControlAction() {
		ControlAction controlAction = nolNewLabelWizard.new ControlAction();
		ActionEvent actionEvent = new ActionEvent(menubar, 1, "test");
		controlAction.actionPerformed(actionEvent);
		nolNewLabelWizard.verifyLabelColor();
		controlAction.insertUpdate(null);
		nolNewLabelWizard.verifyNextFinishButton();
		controlAction.changedUpdate(null);
		nolNewLabelWizard.verifyNextFinishButton();
		controlAction.removeUpdate(null);
		nolNewLabelWizard.verifyNextFinishButton();
		assertEquals(1, nolNewLabelWizard.getAccessibleContext().getAccessibleChildrenCount());
	}
}
