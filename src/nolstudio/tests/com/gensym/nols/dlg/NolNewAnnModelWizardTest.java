package com.gensym.nols.dlg;

import static org.junit.Assert.*;

import java.awt.Color;
import java.awt.Component;
import java.awt.event.ActionEvent;
import java.util.Vector;

import javax.swing.JMenuBar;
import javax.swing.JPanel;
import javax.swing.JTextField;

import org.junit.Before;
import org.junit.Ignore;
import org.junit.Test;

import com.gensym.math.matrix.Matrix;
import com.gensym.nols.data.DataSeries;
import com.gensym.nols.data.DataSource;
import com.gensym.nols.data.Preprocessor;
import com.gensym.nols.data.Project2;
import com.gensym.nols.data.Variable;
import com.gensym.nols.dlg.NolNewAnnModelWizard.ControlAction;
import com.gensym.nols.main.NolMainFrame;
import com.gensym.nols.main.ProjectTree;

public class NolNewAnnModelWizardTest {

	private NolMainFrame dw;
	private JMenuBar menubar;
	private JTextField modelName;
	private JTextField numberField;
	private NolNewAnnModelWizard nolNewAnnModelWizard;
	private Project2 project;
	private Matrix M;

	@Before
	public void init() {
		M = new Matrix();
		M.redimension(2, 2);
		M.set(0, 0, 1);
		M.set(0, 1, 2);
		M.set(1, 0, 3);
		M.set(1, 1, 4);
		modelName = new JTextField();
		modelName.setText("");
		modelName.setBounds(1, 1, 1, 1);
		modelName.setVisible(true);
		numberField = new JTextField();
		numberField.setText("3");
		numberField.setBounds(1, 1, 1, 1);
		numberField.setVisible(true);
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
		nolNewAnnModelWizard = new NolNewAnnModelWizard(dw);
		nolNewAnnModelWizard.setVisible(false);
		assertEquals(1, nolNewAnnModelWizard.getComponents().length);
	}

	@Test
	public void testModifyStep() {
		nolNewAnnModelWizard = new NolNewAnnModelWizard(dw);
		nolNewAnnModelWizard.currentStep = 1;
		nolNewAnnModelWizard.modifyStep(false);
		assertEquals(1, nolNewAnnModelWizard.currentStep);
		nolNewAnnModelWizard.modifyStep(true);
		assertEquals(2, nolNewAnnModelWizard.currentStep);
		nolNewAnnModelWizard.currentStep = 2;
		nolNewAnnModelWizard.modifyStep(true);
		assertEquals(3, nolNewAnnModelWizard.currentStep);
		nolNewAnnModelWizard.currentStep = 2;
		nolNewAnnModelWizard.modifyStep(false);
		assertEquals(1, nolNewAnnModelWizard.currentStep);
		nolNewAnnModelWizard.modifyStep(true);
		assertEquals(2, nolNewAnnModelWizard.currentStep);
		nolNewAnnModelWizard.currentStep = 3;
		nolNewAnnModelWizard.modifyStep(false);
		assertEquals(2, nolNewAnnModelWizard.currentStep);
		nolNewAnnModelWizard.modifyStep(true);
		assertEquals(3, nolNewAnnModelWizard.currentStep);
		nolNewAnnModelWizard.currentStep = 4;
		nolNewAnnModelWizard.modifyStep(false);
		assertEquals(3, nolNewAnnModelWizard.currentStep);
		nolNewAnnModelWizard.modifyStep(true);
		assertEquals(4, nolNewAnnModelWizard.currentStep);
		nolNewAnnModelWizard.currentStep = 5;
		nolNewAnnModelWizard.modifyStep(false);
		assertEquals(4, nolNewAnnModelWizard.currentStep);
	}

	@Test
	public void testResetData() {
		nolNewAnnModelWizard = new NolNewAnnModelWizard(dw);
		nolNewAnnModelWizard.resetData();
		assertFalse(nolNewAnnModelWizard.isOK());
	}

	@Test
	public void testSetButtonFocus() {
		nolNewAnnModelWizard = new NolNewAnnModelWizard(dw);
		nolNewAnnModelWizard.setButtonFocus();
		assertEquals(5, nolNewAnnModelWizard.stepCount);
		assertEquals(0, nolNewAnnModelWizard.nextButton.getComponentCount());
		nolNewAnnModelWizard.stepCount = 1;
		nolNewAnnModelWizard.setButtonFocus();
		assertEquals(0, nolNewAnnModelWizard.finishButton.getComponentCount());
	}

	@Test
	public void testSetTitleForStep() {
		nolNewAnnModelWizard = new NolNewAnnModelWizard(dw);
		assertEquals("Step 1 of 5", nolNewAnnModelWizard.setTitleForStep(1));
	}
}
