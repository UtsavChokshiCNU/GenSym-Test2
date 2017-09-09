package com.gensym.nols.dlg;

import static org.junit.Assert.*;

import java.awt.Color;
import java.awt.event.MouseEvent;
import java.util.Vector;

import javax.swing.JFrame;
import javax.swing.JMenuBar;

import org.junit.Before;
import org.junit.Ignore;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.InjectMocks;
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
import com.gensym.nols.dlg.NolDataSeriesInputWizard.PreviewColumnHeader;
import com.gensym.nols.main.NolMainFrame;
import com.gensym.nols.main.ProjectTree;

public class NolNewOptimizationWizardTest {

	private JMenuBar menubar;
	private int[] width;
	private Project2 project;
	private Matrix M;
	private NolNewOptimizationWizard nolNewOptimizationWizard;

	@Spy
	private NolMainFrame dw = new NolMainFrame();
	@Spy
	NolOptimizeModel mdl1 = new NolOptimizeModel();

	@Before
	public void init() {
		MockitoAnnotations.initMocks(this);
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
		nolNewOptimizationWizard = new NolNewOptimizationWizard(dw);
		width = new int[2];
		width[0] = 1;
		width[1] = 2;

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
		Vector omodels = project.getOptimizationModels();
		mdl1.setComment("comment");
		mdl1.setName("model1");
		omodels.add(mdl1);
		Vector outputs1 = new Vector();
		Vector states1 = new Vector();
		Vector manis1 = new Vector();
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
	}

	@Test
	public void testResetData() {
		nolNewOptimizationWizard.resetData();
		assertEquals("Create New Optimization - Step 1 of 4 - General",
				nolNewOptimizationWizard.getAccessibleContext().getAccessibleName());
	}

	@Test
	public void testModifyStep() {
		nolNewOptimizationWizard.currentStep = 1;
		nolNewOptimizationWizard.modifyStep(false);
		assertEquals(1, nolNewOptimizationWizard.currentStep);
		nolNewOptimizationWizard.modifyStep(true);
		assertEquals(1, nolNewOptimizationWizard.currentStep);

		nolNewOptimizationWizard.currentStep = 2;
		nolNewOptimizationWizard.modifyStep(false);
		assertEquals(1, nolNewOptimizationWizard.currentStep);
		nolNewOptimizationWizard.modifyStep(true);
		assertEquals(1, nolNewOptimizationWizard.currentStep);

		nolNewOptimizationWizard.currentStep = 3;
		nolNewOptimizationWizard.modifyStep(false);
		assertEquals(2, nolNewOptimizationWizard.currentStep);
		nolNewOptimizationWizard.modifyStep(true);
		assertEquals(3, nolNewOptimizationWizard.currentStep);

		nolNewOptimizationWizard.currentStep = 4;
		nolNewOptimizationWizard.modifyStep(false);
		assertEquals(3, nolNewOptimizationWizard.currentStep);
		nolNewOptimizationWizard.modifyStep(true);
		assertEquals(4, nolNewOptimizationWizard.currentStep);
	}

}
