package com.gensym.nols.dlg;

import static org.junit.Assert.*;

import java.awt.Color;
import java.awt.Component;
import java.awt.event.ActionEvent;
import java.awt.event.MouseEvent;
import java.util.Vector;

import javax.swing.JMenuBar;
import javax.swing.JTable;
import javax.swing.JToggleButton;
import javax.swing.event.ListSelectionEvent;

import org.junit.Before;
import org.junit.Ignore;
import org.junit.Test;
import org.mockito.Mockito;
import org.mockito.MockitoAnnotations;
import org.mockito.Spy;
import org.powermock.api.mockito.PowerMockito;

import com.gensym.math.matrix.Matrix;
import com.gensym.nols.data.DataSeries;
import com.gensym.nols.data.DataSource;
import com.gensym.nols.data.NolOptimizeModel;
import com.gensym.nols.data.Preprocessor;
import com.gensym.nols.data.Project2;
import com.gensym.nols.data.Variable;
import com.gensym.nols.dlg.NolNewPcaModelWizard.AutoSelectRenderer;
import com.gensym.nols.dlg.NolNewPcaModelWizard.ControlAction;
import com.gensym.nols.dlg.NolNewPcaModelWizard.LoadFromExistModelDialog;
import com.gensym.nols.dlg.NolNewPcaModelWizard.LoadFromExistModelDialog.DialogAction;
import com.gensym.nols.main.NolMainFrame;
import com.gensym.nols.main.ProjectTree;

public class NolNewPcaModelWizardTest {

	private JMenuBar menubar;
	private int[] width;
	private Matrix M;
	private NolNewPcaModelWizard nolNewPcaModelWizard;
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
		nolNewPcaModelWizard = new NolNewPcaModelWizard(dw);

		le = Mockito.spy(new ListSelectionEvent(dw, 0, 1, true));
		Mockito.when(le.getValueIsAdjusting()).thenReturn(true);
	}

	@Test
	public void testResetData() {
		nolNewPcaModelWizard.resetData();
		assertEquals(1, nolNewPcaModelWizard.currentStep);
	}

	// Error in tain() method as Matrix X not initialized, this will always
	// throw null pointer
	@Test(expected = NullPointerException.class)
	public void testFinishActionFailure() {
		nolNewPcaModelWizard.resetData();
		assertTrue(nolNewPcaModelWizard.finishAction());
	}

	@Test
	public void testSetVisible() {
		nolNewPcaModelWizard.setVisible(false);
		assertEquals(1, nolNewPcaModelWizard.currentStep);
	}

	@Test
	public void testLoadFromExistModelDialog() {
		LoadFromExistModelDialog loadFromExistModelDialog = nolNewPcaModelWizard.new LoadFromExistModelDialog(dw,
				"test", false);
		loadFromExistModelDialog.setContent(exogchecks1);
		assertEquals(1, loadFromExistModelDialog.getComponentCount());
		assertEquals(0, loadFromExistModelDialog.getSelectedIndex());
		DialogAction dialogAction = loadFromExistModelDialog.new DialogAction();
		MouseEvent mouseEvent = new MouseEvent(dw, 1, 12000, 1, 1, 1, 1, false);
		dialogAction.mouseClicked(mouseEvent);
		assertFalse(loadFromExistModelDialog.isOk());
		mouseEvent = new MouseEvent(dw, 1, 12000, 1, 1, 1, 2, false);
		dialogAction.mouseClicked(mouseEvent);
		assertTrue(loadFromExistModelDialog.isOk());
	}

	@Test
	public void testAutoSelectRenderer() {
		AutoSelectRenderer autoSelectRenderer = nolNewPcaModelWizard.new AutoSelectRenderer();
		JTable jTable = Mockito.spy(JTable.class);
		JToggleButton jToggleButton = Mockito.spy(JToggleButton.class);
		Component cell = autoSelectRenderer.getTableCellRendererComponent(jTable, jToggleButton, true, false, 1, 1);
		assertTrue(cell.isVisible());
	}

	@Test
	public void testControlAction() {
		NolNewPcaModelWizard nolNewPcaModelWizard1 = Mockito.spy(new NolNewPcaModelWizard(dw));
		ControlAction controlAction = nolNewPcaModelWizard1.new ControlAction();
		ActionEvent actionEvent = Mockito.spy(new ActionEvent(menubar, 1, "test"));
		controlAction.actionPerformed(actionEvent);
		assertEquals(0, controlAction.getPropertyChangeListeners().length);
	}

	@Test
	public void testModifyStep() {
		nolNewPcaModelWizard.currentStep = 1;
		nolNewPcaModelWizard.modifyStep(false);
		assertEquals(1, nolNewPcaModelWizard.currentStep);
		nolNewPcaModelWizard.modifyStep(true);
		assertEquals(2, nolNewPcaModelWizard.currentStep);
		nolNewPcaModelWizard.currentStep = 2;
		nolNewPcaModelWizard.modifyStep(false);
		assertEquals(1, nolNewPcaModelWizard.currentStep);
		nolNewPcaModelWizard.modifyStep(true);
		assertEquals(2, nolNewPcaModelWizard.currentStep);
		nolNewPcaModelWizard.currentStep = 3;
		nolNewPcaModelWizard.modifyStep(false);
		assertEquals(2, nolNewPcaModelWizard.currentStep);
		nolNewPcaModelWizard.modifyStep(true);
		assertEquals(3, nolNewPcaModelWizard.currentStep);
		nolNewPcaModelWizard.currentStep = 4;
		nolNewPcaModelWizard.modifyStep(false);
		assertEquals(3, nolNewPcaModelWizard.currentStep);
		nolNewPcaModelWizard.modifyStep(true);
		assertEquals(4, nolNewPcaModelWizard.currentStep);
	}
}
