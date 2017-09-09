package com.gensym.nols.dlg;

import static org.junit.Assert.*;

import java.awt.Color;
import java.awt.Image;
import java.awt.event.ActionEvent;
import java.awt.event.MouseEvent;
import java.awt.image.ColorModel;
import java.io.IOException;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.UnknownHostException;
import java.util.ArrayList;
import java.util.List;
import java.util.Vector;

import javax.accessibility.AccessibleContext;
import javax.swing.JFrame;
import javax.swing.JMenuBar;
import javax.swing.JScrollBar;
import javax.swing.JScrollPane;
import javax.swing.event.ListSelectionEvent;

import org.junit.Before;
import org.junit.Ignore;
import org.junit.Test;
import org.mockito.InjectMocks;

import com.gensym.nols.dlg.NolDataSeriesInputWizard.ControlAction;
import com.gensym.nols.dlg.NolDataSeriesInputWizard.PreviewColumn;
import com.gensym.nols.dlg.NolDataSeriesInputWizard.PreviewColumnHeader;
import com.gensym.nols.main.NolMainFrame;

public class NolDataSeriesInputWizardTest {

	private JFrame dw;
	private JMenuBar menubar;
	private int[] width;
	private PreviewColumnHeader previewColumnHeader;
	private MouseEvent mouseEvent;

	@InjectMocks
	NolDataSeriesInputWizard nolDataSeriesInputWizard;

	@Before
	public void init() {
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
		nolDataSeriesInputWizard = new NolDataSeriesInputWizard(dw, "Title");
		width = new int[2];
		width[0] = 1;
		width[1] = 2;
		previewColumnHeader = nolDataSeriesInputWizard.new PreviewColumnHeader(width, menubar, 2);
	}

	@Test
	public void testModifyStep() {
		nolDataSeriesInputWizard.currentStep = 1;
		nolDataSeriesInputWizard.modifyStep(true);
		assertEquals(2, nolDataSeriesInputWizard.currentStep);
		nolDataSeriesInputWizard.modifyStep(false);
		assertEquals(1, nolDataSeriesInputWizard.currentStep);
		nolDataSeriesInputWizard.currentStep = 2;
		nolDataSeriesInputWizard.modifyStep(true);
		assertEquals(3, nolDataSeriesInputWizard.currentStep);
		nolDataSeriesInputWizard.modifyStep(false);
		assertEquals(2, nolDataSeriesInputWizard.currentStep);
		nolDataSeriesInputWizard.currentStep = 3;
		nolDataSeriesInputWizard.modifyStep(true);
		assertEquals(4, nolDataSeriesInputWizard.currentStep);
		nolDataSeriesInputWizard.modifyStep(false);
		assertEquals(3, nolDataSeriesInputWizard.currentStep);
		nolDataSeriesInputWizard.currentStep = 4;
		nolDataSeriesInputWizard.modifyStep(true);
		assertEquals(5, nolDataSeriesInputWizard.currentStep);
		nolDataSeriesInputWizard.modifyStep(false);
		assertEquals(4, nolDataSeriesInputWizard.currentStep);
		nolDataSeriesInputWizard.currentStep = 5;
		nolDataSeriesInputWizard.modifyStep(true);
		assertEquals(6, nolDataSeriesInputWizard.currentStep);
		nolDataSeriesInputWizard.modifyStep(false);
		assertEquals(5, nolDataSeriesInputWizard.currentStep);
		nolDataSeriesInputWizard.currentStep = 6;
		nolDataSeriesInputWizard.modifyStep(true);
		assertEquals(6, nolDataSeriesInputWizard.currentStep);
		nolDataSeriesInputWizard.modifyStep(false);
		assertEquals(5, nolDataSeriesInputWizard.currentStep);
	}

	@Test
	public void testIconImages1() {
		nolDataSeriesInputWizard = new NolDataSeriesInputWizard(dw, "Title");
		List<Image> images = nolDataSeriesInputWizard.getIconImages();
		assertEquals(0, images.size());
	}

	@Test
	public void testIconImages2() {
		nolDataSeriesInputWizard = new NolDataSeriesInputWizard(dw, "Title", "Filename", "root");
		List<Image> images = nolDataSeriesInputWizard.getIconImages();
		assertEquals(0, images.size());
	}

	@Test
	public void testSetUrl1() throws MalformedURLException {
		assertNull(nolDataSeriesInputWizard.getDataSeriesFileFormat().getName());
		try {
			URL url = new URL("http://www.google.com");
			nolDataSeriesInputWizard.setURL(url);
			assertEquals("Format", nolDataSeriesInputWizard.getDataSeriesFileFormat().getName());
		} catch (IOException une) {
			// To handle unexpected network errors which are hardware dependent
			assertNull(nolDataSeriesInputWizard.getDataSeriesFileFormat().getName());
		}
	}

	@Test
	public void testGetAccessibleChildrenCount() {
		AccessibleContext context = nolDataSeriesInputWizard.getAccessibleContext();
		assertEquals(1, context.getAccessibleChildrenCount());
	}

	@Test
	public void testColorModelAlpha() {
		ColorModel colorModel = nolDataSeriesInputWizard.getColorModel();
		assertEquals(false, colorModel.hasAlpha());
	}

	@Test
	public void testSetFile1() {
		nolDataSeriesInputWizard.setFile("root", "fileName");
		assertEquals(0, nolDataSeriesInputWizard.getComponentListeners().length);
		assertNull(nolDataSeriesInputWizard.getDataSeriesFileFormat().getName());
	}

	@Test
	public void testSetFile2() {
		nolDataSeriesInputWizard.setFile(null, "filename");
		assertNull(nolDataSeriesInputWizard.getDataSeriesFileFormat().getName());
	}

	@Test
	public void testSetVisible() {
		assertEquals(0, nolDataSeriesInputWizard.stepPane.getComponents().length);
		nolDataSeriesInputWizard.setVisible(false);
		assertEquals(1, nolDataSeriesInputWizard.stepPane.getComponents().length);
	}

	@Test
	public void testFinishAction() {
		nolDataSeriesInputWizard.setFile("tests/com/gensym/nols/dlg/", "tests/com/gensym/nols/dlg/gensymTestFile.txt");
		assertTrue(nolDataSeriesInputWizard.finishAction());
	}

	@Test
	public void testPreviewColumnHeader() {
		assertTrue(previewColumnHeader.isOpaque());
	}

	@Test
	public void testControlAction() {
		nolDataSeriesInputWizard = new NolDataSeriesInputWizard(dw, "title",
				"tests/com/gensym/nols/dlg/gensymTestFile.txt", null);
		nolDataSeriesInputWizard.setFile(null, "tests/com/gensym/nols/dlg/gensymTestFile.txt");
		ControlAction controlAction = nolDataSeriesInputWizard.new ControlAction();
		try {
			ActionEvent actionEvent = new ActionEvent(menubar, 1, "Space");
			controlAction.actionPerformed(actionEvent);
			controlAction.run();
			assertTrue(controlAction.verifyControlActionRun());
			actionEvent = new ActionEvent(menubar, 0, "Semicolon");
			controlAction.actionPerformed(actionEvent);
			controlAction.run();
			assertTrue(controlAction.verifyControlActionRun());
			actionEvent = new ActionEvent(menubar, 1, "Comma");
			controlAction.actionPerformed(actionEvent);
			controlAction.run();
			assertTrue(controlAction.verifyControlActionRun());
			actionEvent = new ActionEvent(menubar, 0, "Other");
			controlAction.actionPerformed(actionEvent);
			controlAction.run();
			assertTrue(controlAction.verifyControlActionRun());
			actionEvent = new ActionEvent(menubar, 0, "Tags");
			controlAction.actionPerformed(actionEvent);
			controlAction.run();
			assertTrue(controlAction.verifyControlActionRun());
			actionEvent = new ActionEvent(menubar, 0, "Units");
			controlAction.actionPerformed(actionEvent);
			controlAction.run();
			assertTrue(controlAction.verifyControlActionRun());
			actionEvent = new ActionEvent(menubar, 0, "Names");
			controlAction.actionPerformed(actionEvent);
			controlAction.run();
			assertTrue(controlAction.verifyControlActionRun());
			actionEvent = new ActionEvent(menubar, 0, "rowIgnore");
			controlAction.actionPerformed(actionEvent);
			controlAction.run();
			assertTrue(controlAction.verifyControlActionRun());
			actionEvent = new ActionEvent(menubar, 0, "date");
			controlAction.actionPerformed(actionEvent);
			controlAction.run();
			assertTrue(controlAction.verifyControlActionRun());
			actionEvent = new ActionEvent(menubar, 0, "time");
			controlAction.actionPerformed(actionEvent);
			controlAction.run();
			assertTrue(controlAction.verifyControlActionRun());
			actionEvent = new ActionEvent(menubar, 0, "date&time");
			controlAction.actionPerformed(actionEvent);
			controlAction.run();
			assertTrue(controlAction.verifyControlActionRun());
			actionEvent = new ActionEvent(menubar, 0, "columnIgnore");
			controlAction.actionPerformed(actionEvent);
			controlAction.run();
			assertTrue(controlAction.verifyControlActionRun());
			actionEvent = new ActionEvent(menubar, 0, "Number:");
			controlAction.actionPerformed(actionEvent);
			controlAction.run();
			assertTrue(controlAction.verifyControlActionRun());
			actionEvent = new ActionEvent(menubar, 0, "NaN");
			controlAction.actionPerformed(actionEvent);
			controlAction.run();
			assertTrue(controlAction.verifyControlActionRun());
			actionEvent = new ActionEvent(menubar, 0, "Ignore Row");
			controlAction.actionPerformed(actionEvent);
			controlAction.run();
			assertTrue(controlAction.verifyControlActionRun());
			actionEvent = new ActionEvent(menubar, 0, "rowSet");
			controlAction.actionPerformed(actionEvent);
			controlAction.run();
			assertTrue(controlAction.verifyControlActionRun());
			actionEvent = new ActionEvent(menubar, 0, "rowRemove");
			controlAction.actionPerformed(actionEvent);
			controlAction.run();
			assertTrue(controlAction.verifyControlActionRun());
			actionEvent = new ActionEvent(menubar, 0, "columnSet");
			controlAction.actionPerformed(actionEvent);
			controlAction.run();
			assertTrue(controlAction.verifyControlActionRun());
			actionEvent = new ActionEvent(menubar, 0, "columnRemove");
			controlAction.actionPerformed(actionEvent);
			controlAction.run();
			assertTrue(controlAction.verifyControlActionRun());
			actionEvent = new ActionEvent(menubar, 0, "SymbolSet");
			controlAction.actionPerformed(actionEvent);
			controlAction.run();
			assertTrue(controlAction.verifyControlActionRun());
			actionEvent = new ActionEvent(menubar, 0, "symbolRemove");
			controlAction.actionPerformed(actionEvent);
			controlAction.run();
			assertTrue(controlAction.verifyControlActionRun());
			actionEvent = new ActionEvent(menubar, 0, "English");
			controlAction.actionPerformed(actionEvent);
			controlAction.run();
			assertTrue(controlAction.verifyControlActionRun());
		} catch (ArrayIndexOutOfBoundsException ae) {
			assertEquals(0, dw.getGraphics().getColor().getRed());
		}

		ListSelectionEvent le = new ListSelectionEvent(menubar, 0, 1, false);
		controlAction.valueChanged(le);

		assertEquals(0, controlAction.getPropertyChangeListeners().length);
		assertEquals(1, controlAction.getKeys().length);
		assertEquals("Name", controlAction.getKeys()[0]);

	}

	@Test
	public void testPreviewColumn() {
		nolDataSeriesInputWizard = new NolDataSeriesInputWizard(dw, "title",
				"tests/com/gensym/nols/dlg/gensymTestFile.txt", null);
		nolDataSeriesInputWizard.setFile(null, "tests/com/gensym/nols/dlg/gensymTestFile.txt");
		PreviewColumn previewComumn = nolDataSeriesInputWizard.new PreviewColumn(0, 0, menubar, 0);

		assertTrue(previewComumn.isOpaque());

		JScrollBar jb = new JScrollBar(0, 0, 0, 0, 1);
		JScrollPane jp = new JScrollPane(jb, 20, 30);
		Vector<String> dataString = new Vector<String>();
		dataString.add("first");
		dataString.add("second");
		previewComumn = nolDataSeriesInputWizard.new PreviewColumn(0, 1, jp, dataString, 1);
		previewComumn.paintComponent(dw.getGraphics());
		assertEquals(0, dw.getGraphics().getColor().getRed());
		assertEquals(0, dw.getGraphics().getColor().getGreen());
		assertEquals(0, dw.getGraphics().getColor().getBlue());
	}

}
