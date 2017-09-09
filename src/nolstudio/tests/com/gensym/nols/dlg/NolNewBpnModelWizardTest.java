package com.gensym.nols.dlg;

import static org.junit.Assert.*;

import java.awt.Color;
import java.awt.event.ActionEvent;
import java.util.Vector;

import javax.swing.JMenuBar;
import javax.swing.event.ListSelectionEvent;

import org.junit.Before;
import org.junit.Ignore;
import org.junit.Test;

import com.gensym.math.matrix.Matrix;
import com.gensym.nols.data.DataSeries;
import com.gensym.nols.data.DataSource;
import com.gensym.nols.data.Preprocessor;
import com.gensym.nols.data.Project2;
import com.gensym.nols.data.Variable;
import com.gensym.nols.dlg.NolNewBpnModelWizard.AutoSelectionNoDelayTableModel;
import com.gensym.nols.dlg.NolNewBpnModelWizard.ControlAction;
import com.gensym.nols.main.NolMainFrame;
import com.gensym.nols.main.ProjectTree;

public class NolNewBpnModelWizardTest {

	private NolMainFrame dw;
	private JMenuBar menubar;
	private Project2 project;
	private Matrix M;
	private NolNewBpnModelWizard nolNewBpnModelWizard;

	@Before
	public void init() {
		M = new Matrix();
		M.redimension(2, 2);
		M.set(0, 0, 1);
		M.set(0, 1, 2);
		M.set(1, 0, 3);
		M.set(1, 1, 4);
		dw = new NolMainFrame();
		menubar = new JMenuBar();
		dw.setAlwaysOnTop(true);
		dw.setVisible(true);
		dw.setTitle("Title");
		dw.setJMenuBar(menubar);
		dw.setSize(4, 5);
		dw.setBackground(new Color(45));
		dw.setBounds(2, 3, 20, 20);
		dw.setEnabled(true);
		DataSeries ds = new DataSeries(M);
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
		projectTree.addPreprocessor(pr, true);
		dw.setEnabled(true);
	}

	@Test
	public void testSetVisible() {
		nolNewBpnModelWizard = new NolNewBpnModelWizard(dw);
		nolNewBpnModelWizard.setVisible(false);
		assertEquals(7, nolNewBpnModelWizard.stepCount);
	}

	@Test
	public void testResetData() {
		nolNewBpnModelWizard = new NolNewBpnModelWizard(dw);
		nolNewBpnModelWizard.resetData();
		assertEquals(false, nolNewBpnModelWizard.isOK());
	}

	@Test
	public void testModifyStep() {
		nolNewBpnModelWizard = new NolNewBpnModelWizard(dw);
		nolNewBpnModelWizard.currentStep = 1;
		nolNewBpnModelWizard.modifyStep(false);
		assertEquals(1, nolNewBpnModelWizard.currentStep);
		nolNewBpnModelWizard.modifyStep(true);
		assertEquals(2, nolNewBpnModelWizard.currentStep);
		nolNewBpnModelWizard.currentStep = 2;
		nolNewBpnModelWizard.modifyStep(false);
		assertEquals(1, nolNewBpnModelWizard.currentStep);
		nolNewBpnModelWizard.modifyStep(true);
		assertEquals(2, nolNewBpnModelWizard.currentStep);
		nolNewBpnModelWizard.currentStep = 3;
		nolNewBpnModelWizard.modifyStep(false);
		assertEquals(2, nolNewBpnModelWizard.currentStep);
		nolNewBpnModelWizard.modifyStep(true);
		assertEquals(3, nolNewBpnModelWizard.currentStep);
		nolNewBpnModelWizard.currentStep = 4;
		nolNewBpnModelWizard.modifyStep(false);
		assertEquals(3, nolNewBpnModelWizard.currentStep);
		nolNewBpnModelWizard.modifyStep(true);
		assertEquals(4, nolNewBpnModelWizard.currentStep);
		nolNewBpnModelWizard.currentStep = 5;
		nolNewBpnModelWizard.modifyStep(false);
		assertEquals(4, nolNewBpnModelWizard.currentStep);
		nolNewBpnModelWizard.modifyStep(true);
		assertEquals(5, nolNewBpnModelWizard.currentStep);
		nolNewBpnModelWizard.currentStep = 6;
		nolNewBpnModelWizard.modifyStep(false);
		assertEquals(5, nolNewBpnModelWizard.currentStep);
		nolNewBpnModelWizard.modifyStep(true);
		assertEquals(6, nolNewBpnModelWizard.currentStep);
		nolNewBpnModelWizard.currentStep = 7;
		nolNewBpnModelWizard.modifyStep(false);
		assertEquals(6, nolNewBpnModelWizard.currentStep);
	}

	@Test
	public void testReceiveRatingResults() {
		nolNewBpnModelWizard = new NolNewBpnModelWizard(dw);
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
		nolNewBpnModelWizard.receiveRatingResults(inVars, delays, outVars, ratings);
		assertEquals(0, nolNewBpnModelWizard.getX());
		assertEquals(0, nolNewBpnModelWizard.getY());
	}

	@Test
	public void testControlActionPerformed() {
		nolNewBpnModelWizard = new NolNewBpnModelWizard(dw);
		ControlAction controlAction = nolNewBpnModelWizard.new ControlAction();
		try {
			ActionEvent actionEvent = new ActionEvent(menubar, 1, "Calculate Ratings");
			controlAction.actionPerformed(actionEvent);
			nolNewBpnModelWizard.verifyControlActionCalculateRatings();
			actionEvent = new ActionEvent(menubar, 1, "Calculate Ratings");
			controlAction.actionPerformed(actionEvent);
			nolNewBpnModelWizard.verifyControlActionCalculateRatings();
			actionEvent = new ActionEvent(menubar, 1, "Hour");
			controlAction.actionPerformed(actionEvent);
			assertEquals(1, nolNewBpnModelWizard.verifyDelayTimeSettingFlag());
			actionEvent = new ActionEvent(menubar, 1, "Minute");
			controlAction.actionPerformed(actionEvent);
			assertEquals(2, nolNewBpnModelWizard.verifyDelayTimeSettingFlag());
			actionEvent = new ActionEvent(menubar, 1, "Second");
			controlAction.actionPerformed(actionEvent);
			assertEquals(3, nolNewBpnModelWizard.verifyDelayTimeSettingFlag());
			actionEvent = new ActionEvent(menubar, 1, "Auto");
			controlAction.actionPerformed(actionEvent);
			assertEquals(3, nolNewBpnModelWizard.verifyDelayTimeSettingFlag());
			actionEvent = new ActionEvent(menubar, 1, "Manual");
			controlAction.actionPerformed(actionEvent);
			assertEquals(3, nolNewBpnModelWizard.verifyDelayTimeSettingFlag());
			actionEvent = new ActionEvent(menubar, 1, "OKProp");
			controlAction.actionPerformed(actionEvent);
			assertEquals(3, nolNewBpnModelWizard.verifyDelayTimeSettingFlag());
		} catch (ArrayIndexOutOfBoundsException ae) {
			assertEquals(0, dw.getGraphics().getColor().getRed());
		}

		ListSelectionEvent le = new ListSelectionEvent(dw, 0, 1, false);
		controlAction.valueChanged(le);

		le = new ListSelectionEvent(dw, 0, 1, true);
		controlAction.valueChanged(le);

		assertEquals("Name", controlAction.getKeys()[0]);
	}

	@Test
	public void testReadDelays() {
		nolNewBpnModelWizard = new NolNewBpnModelWizard(dw);
		Vector result = nolNewBpnModelWizard.readDelaysFromAutoSelectChecks();
		assertEquals(1, result.size());
		long[] res = (long[]) result.get(0);
		assertEquals(1, res.length);
		assertEquals(0, res[0]);
	}
}
