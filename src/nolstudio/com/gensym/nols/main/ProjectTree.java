package com.gensym.nols.main;

import java.awt.event.*;
import java.awt.*;
import java.util.*;

import javax.swing.*;
import javax.swing.event.*;
import javax.swing.tree.*;

import com.gensym.nols.data.*;

import com.gensym.DEBUG;
 /**
 * ProjectTree
 * @version     1.0 August 29, 1998
 * @author      Gang Chen
 **/

public class ProjectTree implements RawDataSourceListener {
	private NolMainFrame mainFrame; 
	private JTree projectJTree;
	private DefaultMutableTreeNode topNode;
	private DefaultMutableTreeNode currentNode;
	private DefaultMutableTreeNode dataSeriesNode;
	private DefaultMutableTreeNode fileformatNode;
	private DefaultMutableTreeNode labelNode;
	private DefaultMutableTreeNode preprocessorNode;
	private DefaultMutableTreeNode predictiveModelNode;
	private DefaultMutableTreeNode optimizationModelNode;
	private DefaultMutableTreeNode simulationNode;
	private DefaultMutableTreeNode optimizationNode;

	private DefaultMutableTreeNode bpnModelNode;
	private DefaultMutableTreeNode annModelNode;
	private DefaultMutableTreeNode rbfnModelNode;
	private DefaultMutableTreeNode rhoModelNode;
	private DefaultMutableTreeNode plsModelNode;
	private DefaultMutableTreeNode pcaModelNode;

//	private DefaultMutableTreeNode genOptimizationNode;

	protected JPopupMenu rootPopUp;
	protected JPopupMenu nodePopUp;
	protected JPopupMenu leafPopUp;

	private ControlAction actionListener;
	protected DefaultTreeModel treeModel;

	protected static final String dataSeriesNodeString  = "dataSeries";
	protected static final String fileformatNodeString = "fileformat";
	protected static final String preprocessorNodeString = "preprocessors";
	protected static final String labelNodeString = "labels";
	protected static final String predictiveModelNodeString = "predictiveModels";
	protected static final String optimizationModelNodeString = "optimizationModels";
	protected static final String simulationNodeString = "simulations";
	protected static final String optimizationNodeString = "optimizations";
//	protected static final String genOptimizationNodeString = "genOptimizations";
	protected static final String newMenuString = "newObjMenu";
	protected static final String gotoMenuString = "gotoObjMenu";
	protected static final String deleteMenuString = "deleteObjMenu";
    
	protected static final String bpnModelNodeString = "bpnModel";
	protected static final String annModelNodeString = "annModel";
	protected static final String rbfnModelNodeString = "rbfnModel";
	protected static final String rhoModelNodeString = "rhoModel";
	protected static final String plsModelNodeString = "plsModel";
	protected static final String pcaModelNodeString = "pcaModel";

	public ProjectTree(NolMainFrame frame) {
		super();
		mainFrame = frame;		
		actionListener =  new ControlAction();	

		//Create the nodes.
		topNode = new DefaultMutableTreeNode(new ProjectTreeNodeObj("Project1"));
		currentNode = topNode;
		treeModel = new DefaultTreeModel(topNode);
		treeModel.addTreeModelListener(new ProjectTreeModelListener());

		//Create a tree that allows one selection at a time.
		projectJTree = new JTree(treeModel);
		projectJTree.getSelectionModel().setSelectionMode(TreeSelectionModel.SINGLE_TREE_SELECTION);

        // Set the icon for leaf nodes.
//        projectTree.setCellRenderer(new projectTreeCellRenderer());
		projectJTree.setCellRenderer(new DefaultTreeCellRenderer());
	
		// set the spacing between rows
		projectJTree.setRowHeight(20);  // -- looks good to me?

		// Listen for when the selection changes.
		projectJTree.addMouseListener(actionListener);

		createNodes(topNode);

		rootPopUp = new JPopupMenu();
		JMenuItem popUpItem = new JMenuItem(mainFrame.getResourceString("renameMenu"));
		popUpItem.setActionCommand("Rename...");
		popUpItem.addActionListener(actionListener);
		rootPopUp.add(popUpItem);


		nodePopUp = new JPopupMenu();
		popUpItem = new JMenuItem(mainFrame.getResourceString(newMenuString));
		popUpItem.setActionCommand("New...");
		popUpItem.addActionListener(actionListener);
		nodePopUp.add(popUpItem);

		leafPopUp = new JPopupMenu();
		popUpItem = new JMenuItem(mainFrame.getResourceString(gotoMenuString));
		popUpItem.setActionCommand("Go To...");
		popUpItem.addActionListener(actionListener);
		leafPopUp.add(popUpItem);
		popUpItem = new JMenuItem(mainFrame.getResourceString(deleteMenuString));
		popUpItem.setActionCommand("Delete");
		popUpItem.addActionListener(actionListener);
		leafPopUp.add(popUpItem);

		projectJTree.add(rootPopUp);
		projectJTree.add(nodePopUp);
		projectJTree.add(leafPopUp);
		projectJTree.expandRow(0);

	}

	/* create a tree everytime a change accur. Need to change back
	 when swing is fixed with the dynamic change of node. */
	public void setProject(){
		reCreateNodes();
	}

	public void setProjectName(){
		Project2 project = mainFrame.getProject(); 
		topNode.setUserObject(new ProjectTreeNodeObj(project.getName()));
	}

  private void createNodes(DefaultMutableTreeNode top) {

		//0:project 1:dataseries 2:var 3:label 4:case 5:model
	
	
		dataSeriesNode = addObject(top,new ProjectTreeNodeObj(mainFrame.getResourceString(dataSeriesNodeString), 1),true);
		fileformatNode = addObject(top,new ProjectTreeNodeObj(mainFrame.getResourceString(fileformatNodeString), 2),true);
		labelNode = addObject(top,new ProjectTreeNodeObj(mainFrame.getResourceString(labelNodeString), 3),true);
		preprocessorNode = addObject(top,new ProjectTreeNodeObj(mainFrame.getResourceString(preprocessorNodeString), 4),true);
		predictiveModelNode = addObject(top,new ProjectTreeNodeObj(mainFrame.getResourceString(predictiveModelNodeString), 6),true);
		
		bpnModelNode = addObject(top,new ProjectTreeNodeObj(mainFrame.getResourceString(bpnModelNodeString), 10),true);
		annModelNode = addObject(top,new ProjectTreeNodeObj(mainFrame.getResourceString(annModelNodeString), 11),true);
		rbfnModelNode = addObject(top,new ProjectTreeNodeObj(mainFrame.getResourceString(rbfnModelNodeString), 12),true);
		rhoModelNode = addObject(top,new ProjectTreeNodeObj(mainFrame.getResourceString(rhoModelNodeString), 13),true);
		plsModelNode = addObject(top,new ProjectTreeNodeObj(mainFrame.getResourceString(plsModelNodeString), 14),true);
		pcaModelNode = addObject(top,new ProjectTreeNodeObj(mainFrame.getResourceString(pcaModelNodeString), 15),true);

		optimizationModelNode = addObject(top,new ProjectTreeNodeObj(mainFrame.getResourceString(optimizationModelNodeString), 7),true);
		simulationNode = addObject(top,new ProjectTreeNodeObj(mainFrame.getResourceString(simulationNodeString), 8),true);
		optimizationNode = addObject(top,new ProjectTreeNodeObj(mainFrame.getResourceString(optimizationNodeString), 9),true);
//		genOptimizationNode = addObject(top,new ProjectTreeNodeObj(mainFrame.getResourceString(genOptimizationNodeString), 14),true);

		Project2 project = mainFrame.getProject();
		Vector formats = project.getDataSeriesFileFormats();
  		for(int i=0;i<formats.size();i++){
			DataSeriesFileFormat ft = (DataSeriesFileFormat)formats.elementAt(i);
			addFileFormat(ft,false);
		}
	}

	//Temperay method to work around the dynamic change bug
    private void reCreateNodes() {

		Project2 project = mainFrame.getProject();
		topNode = new DefaultMutableTreeNode(new ProjectTreeNodeObj(project.getName()));

		dataSeriesNode = addObject(topNode,new ProjectTreeNodeObj(mainFrame.getResourceString(dataSeriesNodeString), 1),true);
		fileformatNode = addObject(topNode,new ProjectTreeNodeObj(mainFrame.getResourceString(fileformatNodeString), 2),true);
		labelNode = addObject(topNode,new ProjectTreeNodeObj(mainFrame.getResourceString(labelNodeString), 3),true);
		preprocessorNode = addObject(topNode,new ProjectTreeNodeObj(mainFrame.getResourceString(preprocessorNodeString), 4),true);
		predictiveModelNode = addObject(topNode,new ProjectTreeNodeObj(mainFrame.getResourceString(predictiveModelNodeString), 6),true);

		bpnModelNode = addObject(topNode,new ProjectTreeNodeObj(mainFrame.getResourceString(bpnModelNodeString), 10),true);
		annModelNode = addObject(topNode,new ProjectTreeNodeObj(mainFrame.getResourceString(annModelNodeString), 11),true);
		rbfnModelNode = addObject(topNode,new ProjectTreeNodeObj(mainFrame.getResourceString(rbfnModelNodeString), 12),true);
		rhoModelNode = addObject(topNode,new ProjectTreeNodeObj(mainFrame.getResourceString(rhoModelNodeString), 13),true);
		plsModelNode = addObject(topNode,new ProjectTreeNodeObj(mainFrame.getResourceString(plsModelNodeString), 14),true);
		pcaModelNode = addObject(topNode,new ProjectTreeNodeObj(mainFrame.getResourceString(pcaModelNodeString), 15),true);

		optimizationModelNode = addObject(topNode,new ProjectTreeNodeObj(mainFrame.getResourceString(optimizationModelNodeString), 7),true);
		simulationNode = addObject(topNode,new ProjectTreeNodeObj(mainFrame.getResourceString(simulationNodeString), 8),true);
		optimizationNode = addObject(topNode,new ProjectTreeNodeObj(mainFrame.getResourceString(optimizationNodeString), 9),true);
//		genOptimizationNode = addObject(topNode,new ProjectTreeNodeObj(mainFrame.getResourceString(genOptimizationNodeString), 14),true);
		RawDataSource rawDataSource = project.getRawDataSource();
		for(int i=0;i<rawDataSource.getNumberOfDataSeries();i++){
			DataSeries ds = rawDataSource.getDataSeries(i);
			addDataSeries(ds,false);
		}

		Vector processedData = project.getProcessedData();
		for(int i=0;i<processedData.size();i++){
			DataSeries ds = (DataSeries)processedData.elementAt(i);
			addDataSeries(ds,false);
		}
		Vector formats = project.getDataSeriesFileFormats();
	  	for(int i=0;i<formats.size();i++){
			DataSeriesFileFormat ft = (DataSeriesFileFormat)formats.elementAt(i);
			addFileFormat(ft,false);
		}

		for(int i=0;i<project.getNumberOfLabels();i++){
			addLabel(project.getLabel(i),false);
		}

		for(int i=0;i<project.getNumberOfPreprocessors();i++){
			addPreprocessor(project.getPreprocessorByIndex(i),false);
		}

		Vector pModel = project.getPredictiveModels();
		for(int i=0;i<pModel.size();i++){
			addPredictiveModel((NolModel2)pModel.elementAt(i),false);
		}

// add bpn, ann, rbfn, and rho for version 4.2 gchen 2003
		Vector bModel = project.getBpnModels();
		for(int i=0;i<bModel.size();i++){
			addBpnModel((NolBpnModel)bModel.elementAt(i),false);
		}

		Vector aModel = project.getAnnModels();
		for(int i=0;i<aModel.size();i++){
			addAnnModel((NolAnnModel)aModel.elementAt(i),false);
		}

		Vector rModel = project.getRbfnModels();
		for(int i=0;i<rModel.size();i++){
			addRbfnModel((NolRbfnModel)rModel.elementAt(i),false);
		}

		Vector hModel = project.getRhoModels();
		for(int i=0;i<hModel.size();i++){
			addRhoModel((NolRhoModel)hModel.elementAt(i),false);
		}


//end version 4.2r0 modification

// add pls, pca for version 5.0 gchen 2006
		Vector plModel = project.getPlsModels();
		for(int i=0;i<plModel.size();i++){
			addPlsModel((NolPlsModel)plModel.elementAt(i),false);
		}

		Vector pcModel = project.getPcaModels();
		for(int i=0;i<pcModel.size();i++){
			addPcaModel((NolPcaModel)pcModel.elementAt(i),false);
		}
//end version 50r0 modification

		Vector oModel = project.getOptimizationModels();
		for(int i=0;i<oModel.size();i++){
			addOptimizationModel((NolOptimizeModel)oModel.elementAt(i),false);
		}

		int sc = project.getNumberOfSimulations();
		for(int i=0;i<sc;i++){
			addSimulation(project.getSimulation(i),false);
		}

		int opc = project.getNumberOfOptimizations();
		for(int i=0;i<opc;i++){
			addOptimization(project.getOptimization(i),false);
		}
		
/*		int gopc = project.getNumberOfGenOptimizations();
		for(int i=0;i<gopc;i++){
			addGenOptimization(project.getGenOptimization(i),false);
		}
*/		
		treeModel = new DefaultTreeModel(topNode);
		treeModel.addTreeModelListener(new ProjectTreeModelListener());

		projectJTree = new JTree(treeModel);
		projectJTree.getSelectionModel().setSelectionMode(TreeSelectionModel.SINGLE_TREE_SELECTION);

        // Set the icon for leaf nodes.
//        projectTree.setCellRenderer(new projectTreeCellRenderer());
		projectJTree.setCellRenderer(new DefaultTreeCellRenderer());
	
		// set the spacing between rows
		projectJTree.setRowHeight(20);  // -- looks good to me?

		// Listen for when the selection changes.
		projectJTree.addMouseListener(actionListener);

		rootPopUp = new JPopupMenu();
		JMenuItem popUpItem = new JMenuItem(mainFrame.getResourceString("renameMenu"));
		popUpItem.setActionCommand("Rename...");
		popUpItem.addActionListener(actionListener);
		rootPopUp.add(popUpItem);


		nodePopUp = new JPopupMenu();
		popUpItem = new JMenuItem(mainFrame.getResourceString(newMenuString));
		popUpItem.setActionCommand("New...");
		popUpItem.addActionListener(actionListener);
		nodePopUp.add(popUpItem);

		leafPopUp = new JPopupMenu();
		popUpItem = new JMenuItem(mainFrame.getResourceString(gotoMenuString));
		popUpItem.setActionCommand("Go To...");
		popUpItem.addActionListener(actionListener);
		leafPopUp.add(popUpItem);
		popUpItem = new JMenuItem(mainFrame.getResourceString(deleteMenuString));
		popUpItem.setActionCommand("Delete");
		popUpItem.addActionListener(actionListener);
		leafPopUp.add(popUpItem);

		projectJTree.add(rootPopUp);
		projectJTree.add(nodePopUp);
		projectJTree.add(leafPopUp);

		mainFrame.getProjectTreePane().setViewportView(projectJTree);
		mainFrame.getProjectTreePane().validate();
	}

	public void changeProjectName(String newName){
		ProjectTreeNodeObj userObject = (ProjectTreeNodeObj)topNode.getUserObject();
		userObject.name = newName;
		projectJTree.validate();
		projectJTree.repaint(0l);
	}

	public void addDataSeries(DataSeries ds,boolean show){
		int dCount = dataSeriesNode.getChildCount();
		for(int i=0;i<dCount;i++){
			DefaultMutableTreeNode node = 
				(DefaultMutableTreeNode)dataSeriesNode.getChildAt(i);
			ProjectTreeNodeObj userObject = (ProjectTreeNodeObj)node.getUserObject();
			if(ds.equals(userObject.dataSeries)){
				return;
			}
		}
		addObject(dataSeriesNode,new ProjectTreeNodeObj(ds),show);
		projectJTree.validate();
		projectJTree.repaint(0l);
	}

	public void changeDataSeriesName(DataSeries ds,boolean show){
		int dCount = dataSeriesNode.getChildCount();
		for(int i=0;i<dCount;i++){
			DefaultMutableTreeNode node = (DefaultMutableTreeNode)dataSeriesNode.getChildAt(i);
			ProjectTreeNodeObj userObject = (ProjectTreeNodeObj)node.getUserObject();
			if(ds.equals(userObject.dataSeries)){
				userObject.name = ds.getDataSource().getName()+"."+ds.getName();
				if (show) {
						projectJTree.scrollPathToVisible(new TreePath(node.getPath()));
				}
				projectJTree.validate();
				projectJTree.repaint(0l);
				return;
			}
		}
	}

	public void addFileFormat(DataSeriesFileFormat ft,boolean show){
		int fCount = fileformatNode.getChildCount();
		for(int i=0;i<fCount;i++){
			DefaultMutableTreeNode node = 
				(DefaultMutableTreeNode)fileformatNode.getChildAt(i);
			ProjectTreeNodeObj userObject = (ProjectTreeNodeObj)node.getUserObject();
			if(ft.equals(userObject.format)){
				return;
			}
		}
		addObject(fileformatNode,new ProjectTreeNodeObj(ft),show);
		projectJTree.validate();
		projectJTree.repaint(0l);
	}

	public void changeFileFormatName(DataSeriesFileFormat ft,boolean show){
		int fCount = fileformatNode.getChildCount();
		for(int i=0;i<fCount;i++){
			DefaultMutableTreeNode node = 
				(DefaultMutableTreeNode)fileformatNode.getChildAt(i);
			ProjectTreeNodeObj userObject = (ProjectTreeNodeObj)node.getUserObject();
			if(ft.equals(userObject.format)){
				userObject.name = ft.getName();
				if (show) {
						projectJTree.scrollPathToVisible(new TreePath(node.getPath()));
				}
				projectJTree.validate();
				projectJTree.repaint(0l);
				return;
			}
		}
	}

	public void addPreprocessor(Preprocessor prep, boolean show){
		Project2 project = mainFrame.getProject();
		int dCount = preprocessorNode.getChildCount();
		for(int i=0;i<dCount;i++){
			DefaultMutableTreeNode node = 
				(DefaultMutableTreeNode)preprocessorNode.getChildAt(i);
			ProjectTreeNodeObj userObject = (ProjectTreeNodeObj)node.getUserObject();
			if(prep.equals(userObject.preprocessor)) 
				return;
		}
		addObject(preprocessorNode,new ProjectTreeNodeObj(prep),show);
		Vector processedData = prep.getDataSeries();
		for(int i=0;i<processedData.size();i++){
			DataSeries ds = (DataSeries)processedData.elementAt(i);
			addDataSeries(ds,true);
		}

		projectJTree.validate();
		projectJTree.repaint(0l);
	}

	public void changePreprocessorName(Preprocessor prep,boolean show){
		int dCount = preprocessorNode.getChildCount();
		for(int i=0;i<dCount;i++){
			DefaultMutableTreeNode node = 
				(DefaultMutableTreeNode)preprocessorNode.getChildAt(i);
			ProjectTreeNodeObj userObject = (ProjectTreeNodeObj)node.getUserObject();
			if(prep.equals(userObject.preprocessor)){
				userObject.name = prep.getName();
				if (show) {
						projectJTree.scrollPathToVisible(new TreePath(node.getPath()));
				}
				projectJTree.validate();
				projectJTree.repaint(0l);
				return;
			}
		}
	}

	public void addPredictiveModel(NolModel2 model,boolean show){
		int pCount = predictiveModelNode.getChildCount();
		for(int i=0;i<pCount;i++){
			DefaultMutableTreeNode node = 
				(DefaultMutableTreeNode)predictiveModelNode.getChildAt(i);
			ProjectTreeNodeObj userObject = (ProjectTreeNodeObj)node.getUserObject();
			if(model.equals(userObject.predictiveModel)) 
				return;
		}
		addObject(predictiveModelNode,new ProjectTreeNodeObj(model),show);
		projectJTree.validate();
		projectJTree.repaint(0l);
	}

	public void changePredictiveModelName(NolModel2 model,boolean show){
		int pCount = predictiveModelNode.getChildCount();
		for(int i=0;i<pCount;i++){
			DefaultMutableTreeNode node = 
				(DefaultMutableTreeNode)predictiveModelNode.getChildAt(i);
			ProjectTreeNodeObj userObject = (ProjectTreeNodeObj)node.getUserObject();
			if(model.equals(userObject.predictiveModel)){
				userObject.name = model.getName();
				if (show) {
						projectJTree.scrollPathToVisible(new TreePath(node.getPath()));
				}
				projectJTree.validate();
				projectJTree.repaint(0l);
				return;
			}
		}
	}

	public void addOptimizationModel(NolOptimizeModel model, boolean show){
		int oCount = optimizationModelNode.getChildCount();
		for(int i=0;i<oCount;i++){
			DefaultMutableTreeNode node = 
				(DefaultMutableTreeNode)optimizationModelNode.getChildAt(i);
			ProjectTreeNodeObj userObject = (ProjectTreeNodeObj)node.getUserObject();
			if(model.equals(userObject.optimizeModel)) 
				return;
		}
		addObject(optimizationModelNode,new ProjectTreeNodeObj(model),show);
		projectJTree.validate();
		projectJTree.repaint(0l);
	}

	public void changeOptimizationModelName(NolOptimizeModel model,boolean show){
		int oCount = optimizationModelNode.getChildCount();
		for(int i=0;i<oCount;i++){
			DefaultMutableTreeNode node = 
				(DefaultMutableTreeNode)optimizationModelNode.getChildAt(i);
			ProjectTreeNodeObj userObject = (ProjectTreeNodeObj)node.getUserObject();
			if(model.equals(userObject.optimizeModel)){
				userObject.name = model.getName();
				if (show) {
						projectJTree.scrollPathToVisible(new TreePath(node.getPath()));
				}
				projectJTree.validate();
				projectJTree.repaint(0l);
				return;
			}
		}
	}

	public void addSimulation(ResponseSurfaceSimulation sim, boolean show){
		Project2 project = mainFrame.getProject();
		int sCount = simulationNode.getChildCount();
		for(int i=0;i<sCount;i++){
			DefaultMutableTreeNode node = 
				(DefaultMutableTreeNode)simulationNode.getChildAt(i);
			ProjectTreeNodeObj userObject = (ProjectTreeNodeObj)node.getUserObject();
			if(sim.equals(userObject.simulation)) 
				return;
		}
		addObject(simulationNode,new ProjectTreeNodeObj(sim),show);
		if(DEBUG.debugFlag) {
			System.out.println("	addSimulation addDataSeries ");
		}
		addDataSeries(sim.getInputData(),false);
		addDataSeries(sim.getOutputData(),false);
	
		projectJTree.validate();
		projectJTree.repaint(0l);
	}

	public void changeSimulationName(ResponseSurfaceSimulation sim,boolean show){
		int sCount = simulationNode.getChildCount();
		for(int i=0;i<sCount;i++){
			DefaultMutableTreeNode node = 
				(DefaultMutableTreeNode)simulationNode.getChildAt(i);
			ProjectTreeNodeObj userObject = (ProjectTreeNodeObj)node.getUserObject();
			if(sim.equals(userObject.simulation)){
				userObject.name = sim.getName();
				if (show) {
						projectJTree.scrollPathToVisible(new TreePath(node.getPath()));
				}
				projectJTree.validate();
				projectJTree.repaint(0l);
				return;
			}
		}
	}

	public void addOptimization(NolOptimization opt, boolean show){
		Project2 project = mainFrame.getProject();
		int oCount = optimizationNode.getChildCount();
		for(int i=0;i<oCount;i++){
			DefaultMutableTreeNode node = 
				(DefaultMutableTreeNode)optimizationNode.getChildAt(i);
			ProjectTreeNodeObj userObject = (ProjectTreeNodeObj)node.getUserObject();
			if(opt.equals(userObject.optimization)) 
				return;
		}
		addObject(optimizationNode,new ProjectTreeNodeObj(opt),show);

		Vector optData = opt.getDataSeries();
		for(int i=0;i<optData.size();i++){
			addDataSeries((DataSeries)optData.elementAt(i),false);
		}
		projectJTree.validate();
		projectJTree.repaint(0l);
	}

/*	public void addGenOptimization(NolGenOptimization opt, boolean show){
		Project2 project = mainFrame.getProject();
		int oCount = genOptimizationNode.getChildCount();
		for(int i=0;i<oCount;i++){
			DefaultMutableTreeNode node = 
				(DefaultMutableTreeNode)genOptimizationNode.getChildAt(i);
			ProjectTreeNodeObj userObject = (ProjectTreeNodeObj)node.getUserObject();
			if(opt==userObject.genOptimization) return;
		}
		addObject(genOptimizationNode,new ProjectTreeNodeObj(opt),show);
		projectTree.validate();
		projectTree.repaint(0l);
	}
  */

	public void addLabel(NolLabel lab, boolean show){
		int lCount = labelNode.getChildCount();
		for(int i=0;i<lCount;i++){
			DefaultMutableTreeNode node = 
				(DefaultMutableTreeNode)labelNode.getChildAt(i);
			ProjectTreeNodeObj userObject = (ProjectTreeNodeObj)node.getUserObject();
			if(lab.equals(userObject.nolLabel)) 
				return;
		}
		addObject(labelNode,new ProjectTreeNodeObj(lab),show);
		projectJTree.validate();
		projectJTree.repaint(0l);
	}

	public void changeLabelName(NolLabel lab, boolean show){
		int lCount = labelNode.getChildCount();
		for(int i=0;i<lCount;i++){
			DefaultMutableTreeNode node = 
				(DefaultMutableTreeNode)labelNode.getChildAt(i);
			ProjectTreeNodeObj userObject = (ProjectTreeNodeObj)node.getUserObject();
			if(lab.equals(userObject.nolLabel)){
				userObject.name = lab.getName();
				if (show) {
						projectJTree.scrollPathToVisible(new TreePath(node.getPath()));
				}
				projectJTree.validate();
				projectJTree.repaint(0l);
				return;
			}
		}
	}

	public void changeOptimizationName(NolOptimization opt,boolean show){
		int oCount = optimizationNode.getChildCount();
		for(int i=0;i<oCount;i++){
			DefaultMutableTreeNode node = 
				(DefaultMutableTreeNode)optimizationNode.getChildAt(i);
			ProjectTreeNodeObj userObject = (ProjectTreeNodeObj)node.getUserObject();
			if(opt.equals(userObject.optimization)){
				userObject.name = opt.getName();
				if (show) {
						projectJTree.scrollPathToVisible(new TreePath(node.getPath()));
				}
				projectJTree.validate();
				projectJTree.repaint(0l);
				return;
			}
		}
	}

// add bpn, ann, rbfn, and rho for version 4.2 gchen 2003

	public void addBpnModel(NolBpnModel model,boolean show){
		int pCount = bpnModelNode.getChildCount();
		for(int i=0;i<pCount;i++){
			DefaultMutableTreeNode node = 
				(DefaultMutableTreeNode)bpnModelNode.getChildAt(i);
			ProjectTreeNodeObj userObject = (ProjectTreeNodeObj)node.getUserObject();
			if(model.equals(userObject.bpnModel)) 
				return;
		}
		addObject(bpnModelNode,new ProjectTreeNodeObj(model),show);
		projectJTree.validate();
		projectJTree.repaint(0l);
	}

	public void changeBpnModelName(NolBpnModel model,boolean show){
		int pCount = bpnModelNode.getChildCount();
		for(int i=0;i<pCount;i++){
			DefaultMutableTreeNode node = 
				(DefaultMutableTreeNode)bpnModelNode.getChildAt(i);
			ProjectTreeNodeObj userObject = (ProjectTreeNodeObj)node.getUserObject();
			if(model.equals(userObject.bpnModel)){
				userObject.name = model.getName();
				if (show) {
					projectJTree.scrollPathToVisible(new TreePath(node.getPath()));
				}
				projectJTree.validate();
				projectJTree.repaint(0l);
				return;
			}
		}
	}

	
	public void addAnnModel(NolAnnModel model,boolean show){
		int pCount = annModelNode.getChildCount();
		for(int i=0;i<pCount;i++){
			DefaultMutableTreeNode node = 
				(DefaultMutableTreeNode)annModelNode.getChildAt(i);
			ProjectTreeNodeObj userObject = (ProjectTreeNodeObj)node.getUserObject();
			if(model.equals(userObject.annModel)) 
				return;
		}
		addObject(annModelNode,new ProjectTreeNodeObj(model),show);
		projectJTree.validate();
		projectJTree.repaint(0l);
	}

	public void changeAnnModelName(NolAnnModel model,boolean show){
		int pCount = annModelNode.getChildCount();
		for(int i=0;i<pCount;i++){
			DefaultMutableTreeNode node = 
				(DefaultMutableTreeNode)annModelNode.getChildAt(i);
			ProjectTreeNodeObj userObject = (ProjectTreeNodeObj)node.getUserObject();
			if(model.equals(userObject.annModel)){
				userObject.name = model.getName();
				if (show) {
					projectJTree.scrollPathToVisible(new TreePath(node.getPath()));
				}
				projectJTree.validate();
				projectJTree.repaint(0l);
				return;
			}
		}
	}

	
	public void addRbfnModel(NolRbfnModel model,boolean show){
		int pCount = rbfnModelNode.getChildCount();
		for(int i=0;i<pCount;i++){
			DefaultMutableTreeNode node = 
				(DefaultMutableTreeNode)rbfnModelNode.getChildAt(i);
			ProjectTreeNodeObj userObject = (ProjectTreeNodeObj)node.getUserObject();
			if(model.equals(userObject.rbfnModel)) 
				return;
		}
		addObject(rbfnModelNode,new ProjectTreeNodeObj(model),show);
		projectJTree.validate();
		projectJTree.repaint(0l);
	}

	public void changeRbfnModelName(NolRbfnModel model,boolean show){
		int pCount = rbfnModelNode.getChildCount();
		for(int i=0;i<pCount;i++){
			DefaultMutableTreeNode node = 
				(DefaultMutableTreeNode)rbfnModelNode.getChildAt(i);
			ProjectTreeNodeObj userObject = (ProjectTreeNodeObj)node.getUserObject();
			if(model.equals(userObject.rbfnModel)){
				userObject.name = model.getName();
				if (show) {
					projectJTree.scrollPathToVisible(new TreePath(node.getPath()));
				}
				projectJTree.validate();
				projectJTree.repaint(0l);
				return;
			}
		}
	}

	
	public void addRhoModel(NolRhoModel model,boolean show){
		int pCount = rhoModelNode.getChildCount();
		for(int i=0;i<pCount;i++){
			DefaultMutableTreeNode node = 
				(DefaultMutableTreeNode)rhoModelNode.getChildAt(i);
			ProjectTreeNodeObj userObject = (ProjectTreeNodeObj)node.getUserObject();
			if(model.equals(userObject.rhoModel)) 
				return;
		}
		addObject(rhoModelNode,new ProjectTreeNodeObj(model),show);
		projectJTree.validate();
		projectJTree.repaint(0l);
	}

	public void changeRhoModelName(NolRhoModel model,boolean show){
		int pCount = rhoModelNode.getChildCount();
		for(int i=0;i<pCount;i++){
			DefaultMutableTreeNode node = 
				(DefaultMutableTreeNode)rhoModelNode.getChildAt(i);
			ProjectTreeNodeObj userObject = (ProjectTreeNodeObj)node.getUserObject();
			if(model.equals(userObject.rhoModel)){
				userObject.name = model.getName();
				if (show) {
					projectJTree.scrollPathToVisible(new TreePath(node.getPath()));
				}
				projectJTree.validate();
				projectJTree.repaint(0l);
				return;
			}
		}
	}

	public void addPlsModel(NolPlsModel model,boolean show){
		int pCount = plsModelNode.getChildCount();
		for(int i=0;i<pCount;i++){
			DefaultMutableTreeNode node = 
				(DefaultMutableTreeNode)plsModelNode.getChildAt(i);
			ProjectTreeNodeObj userObject = (ProjectTreeNodeObj)node.getUserObject();
			if(model.equals(userObject.plsModel)) 
				return;
		}
		addObject(plsModelNode,new ProjectTreeNodeObj(model),show);
		projectJTree.validate();
		projectJTree.repaint(0l);
	}

	public void changePlsModelName(NolPlsModel model,boolean show){
		int pCount = plsModelNode.getChildCount();
		for(int i=0;i<pCount;i++){
			DefaultMutableTreeNode node = 
				(DefaultMutableTreeNode)plsModelNode.getChildAt(i);
			ProjectTreeNodeObj userObject = (ProjectTreeNodeObj)node.getUserObject();
			if(model.equals(userObject.plsModel)){
				userObject.name = model.getName();
				if (show) {
					projectJTree.scrollPathToVisible(new TreePath(node.getPath()));
				}
				projectJTree.validate();
				projectJTree.repaint(0l);
				return;
			}
		}
	}

	public void addPcaModel(NolPcaModel model,boolean show){
		int pCount = pcaModelNode.getChildCount();
		for(int i=0;i<pCount;i++){
			DefaultMutableTreeNode node = 
				(DefaultMutableTreeNode)pcaModelNode.getChildAt(i);
			ProjectTreeNodeObj userObject = (ProjectTreeNodeObj)node.getUserObject();
			if(model.equals(userObject.pcaModel)) 
				return;
		}
		addObject(pcaModelNode,new ProjectTreeNodeObj(model),show);
		projectJTree.validate();
		projectJTree.repaint(0l);
	}

	public void changePcaModelName(NolPcaModel model,boolean show){
		int pCount = pcaModelNode.getChildCount();
		for(int i=0;i<pCount;i++){
			DefaultMutableTreeNode node = 
				(DefaultMutableTreeNode)pcaModelNode.getChildAt(i);
			ProjectTreeNodeObj userObject = (ProjectTreeNodeObj)node.getUserObject();
			if(model.equals(userObject.pcaModel)){
				userObject.name = model.getName();
				if (show) {
					projectJTree.scrollPathToVisible(new TreePath(node.getPath()));
				}
				projectJTree.validate();
				projectJTree.repaint(0l);
				return;
			}
		}
	}

// end 4.2r0 modification
	public JTree getProjectTree(){
		return projectJTree;
	}

	class ControlAction extends AbstractAction implements MouseListener,Runnable {
		int positionFlag ;
		private String command;
		private Object source;
		private int clickCount;
		private int mod;
		private int ex;
		private int ey;
		private boolean processAction;
		private boolean processMouse;
		ControlAction() { 
			super("controlAction");
			positionFlag = 0;
		}
		@Override
		public void actionPerformed(ActionEvent e) {
		// handle all actions outside of the main UI thread, otherwise the UI hangs
			command = e.getActionCommand ();
			source = e.getSource ();
			processAction=true; // so run() knows this is a command
			new Thread (this).start ();
		}
		@Override
		public void mouseClicked(MouseEvent e){
			clickCount =  e.getClickCount();
			mod = e.getModifiers();
			ex = e.getX();
			ey = e.getY();
			processMouse = true;
			new Thread (this).start ();
		}
        @Override
		public void run() {
			if(processAction) {
				runActionPerformed();
			}else if(processMouse) {
				runMouseClicked();
			}
		}
		private void runActionPerformed() {
			processAction = false;
			if(command.equals("New...")) {
				if(positionFlag==10){
					mainFrame.importActionPerformed();
				}else if(positionFlag==30){
					mainFrame.newlabelActionPerformed();
				}else if(positionFlag==40){
					try {
						mainFrame.newpreprocessorActionPerformed();
					} catch (Exception e) {
						System.err.println("Exception: "+e.getMessage());
						e.printStackTrace();
					}
				}else if(positionFlag==60){
					mainFrame.newpredictmodelActionPerformed();
				}else if(positionFlag==70){
					mainFrame.newoptimizemodelActionPerformed();
				}else if(positionFlag==80){
					mainFrame.newsimulationActionPerformed();
				}else if(positionFlag==90){
					mainFrame.newoptimizationActionPerformed();
				}else if(positionFlag==100){
					mainFrame.newbpnmodelActionPerformed();
				}else if(positionFlag==110){
					mainFrame.newannmodelActionPerformed();
				}else if(positionFlag==120){
					mainFrame.newrbfnmodelActionPerformed();
				}else if(positionFlag==130){
					mainFrame.newrhomodelActionPerformed();
				}else if(positionFlag==140){
					mainFrame.newplsmodelActionPerformed();
				}else if(positionFlag==150){
					mainFrame.newpcamodelActionPerformed();
//				}else if(positionFlag==140){
//					mainFrame.newgenoptimizationActionPerformed();
				}
			}else if(command.equals("Go To...")) {				
				DefaultMutableTreeNode node = (DefaultMutableTreeNode)
					projectJTree.getSelectionPath().getLastPathComponent();
				ProjectTreeNodeObj userObject = (ProjectTreeNodeObj)node.getUserObject();
				if(positionFlag==11){
					if(userObject.dataSeries != null){
						mainFrame.showDataSeriesWKSP(userObject.dataSeries);
					}
				}else if(positionFlag==31){
					if(userObject.nolLabel != null){
						mainFrame.showLabelWKSP(userObject.nolLabel);
					}
				}else if(positionFlag==21){
					if(userObject.format != null){
						mainFrame.showFileFormatWKSP(userObject.format);
					}
				}else if(positionFlag==41){
					if(userObject.preprocessor != null){
						mainFrame.showPreprocessorWKSP(userObject.preprocessor);
					}
				}else if(positionFlag==61){
					if(userObject.predictiveModel != null){
						mainFrame.showPredictiveModelWKSP(userObject.predictiveModel);
					}
				}else if(positionFlag==71){
					if(userObject.optimizeModel != null){
						mainFrame.showOptimizeModelWKSP(userObject.optimizeModel);
					}
				}else if(positionFlag==81){
					if(userObject.simulation != null){
						mainFrame.showSimulationWKSP(userObject.simulation);
					}
				}else if(positionFlag==91){
					if(userObject.optimization != null){
						mainFrame.showOptimizationWKSP(userObject.optimization);
					}
				}else if(positionFlag==101){
					if(userObject.bpnModel != null){
						mainFrame.showClassicModelWKSP(userObject.bpnModel);
					}
				}else if(positionFlag==111){
					if(userObject.annModel != null){
						mainFrame.showClassicModelWKSP(userObject.annModel);
					}
				}else if(positionFlag==121){
					if(userObject.rbfnModel != null){
						mainFrame.showClassicModelWKSP(userObject.rbfnModel);
					}
				}else if(positionFlag==131){
					if(userObject.rhoModel != null){
						mainFrame.showRhoModelWKSP(userObject.rhoModel);
					}
				}else if(positionFlag==141){
					if(userObject.plsModel != null){
						mainFrame.showPlsModelWKSP(userObject.plsModel);
					}
				}else if(positionFlag==151){
					if(userObject.pcaModel != null){
						mainFrame.showPcaModelWKSP(userObject.pcaModel);
					}
/*				}else if(positionFlag==141){
					if(userObject.genOptimization != null){
						mainFrame.showGenOptimizationWKSP(userObject.genOptimization);
					}
*/				}
			}else if(command.equals("Delete")) {
				DefaultMutableTreeNode node = (DefaultMutableTreeNode)
					projectJTree.getSelectionPath().getLastPathComponent();
				ProjectTreeNodeObj userObject = (ProjectTreeNodeObj)node.getUserObject();
				if(positionFlag==11){
					if(userObject.dataSeries != null){
						if(userObject.dataSeries.getDataSource() instanceof RawDataSource){
							mainFrame.removeRawDataDataSeries(userObject.dataSeries);
						}
					}
				}else if(positionFlag==31){
					if(userObject.nolLabel != null){
						mainFrame.removeLabel(userObject.nolLabel);
					}
				}else if(positionFlag==21){
					if(userObject.format != null){
						mainFrame.removeFileFormat(userObject.format);
					}
				}else if(positionFlag==41){
					if(userObject.preprocessor != null){
						mainFrame.removePreprocessor(userObject.preprocessor);
					}
				}else if(positionFlag==61){
					if(userObject.predictiveModel != null){
						mainFrame.removeModel(userObject.predictiveModel);
					}
				}else if(positionFlag==71){
					if(userObject.optimizeModel != null){
						mainFrame.removeModel(userObject.optimizeModel);
					}
				}else if(positionFlag==81){
					if(userObject.simulation != null){
						mainFrame.removeSimulation(userObject.simulation);
					}
				}else if(positionFlag==91){
					if(userObject.optimization != null){
						mainFrame.removeOptimization(userObject.optimization);
					}
				}else if(positionFlag==101){
					if(userObject.bpnModel != null){
						mainFrame.removeModel(userObject.bpnModel);
					}
				}else if(positionFlag==111){
					if(userObject.annModel != null){
						mainFrame.removeModel(userObject.annModel);
					}
				}else if(positionFlag==121){
					if(userObject.rbfnModel != null){
						mainFrame.removeModel(userObject.rbfnModel);
					}
				}else if(positionFlag==131){
					if(userObject.rhoModel != null){
						mainFrame.removeModel(userObject.rhoModel);
					}
				}else if(positionFlag==141){
					if(userObject.plsModel != null){
						mainFrame.removeModel(userObject.plsModel);
					}
				}else if(positionFlag==151){
					if(userObject.pcaModel != null){
						mainFrame.removeModel(userObject.pcaModel);
					}
/*				}else if(positionFlag==141){
					if(userObject.genOptimization != null){
						mainFrame.removeGenOptimization(userObject.genOptimization);
					}
*/				}
			}else if(command.equals("Rename...")) {
				mainFrame.renameActionPerformed();
			}
		}
      
		public void runMouseClicked(){
			processMouse = false;
			if(projectJTree.isSelectionEmpty()){
				return;
			}
			DefaultMutableTreeNode node = (DefaultMutableTreeNode)
				projectJTree.getSelectionPath().getLastPathComponent();
			ProjectTreeNodeObj userObject = (ProjectTreeNodeObj)node.getUserObject();
			int flag = 	userObject.getFlag();
			if (DEBUG.debugFlag) {
				System.out.println("flag="+flag);
			}
			if(clickCount == 1){
				if(mod == 4){
					if(flag	== 0){
						positionFlag = 0;
						rootPopUp.show(projectJTree, ex, ey);
						rootPopUp.pack();
						rootPopUp.setVisible(true);
					}else if(flag == 1){
						if(userObject.dataSeries != null){
							positionFlag = 11;
							leafPopUp.show(projectJTree, ex, ey);
							leafPopUp.pack();
							leafPopUp.setVisible(true);
						}else{
							positionFlag = 10;
							nodePopUp.show(projectJTree, ex, ey);
							nodePopUp.pack();
							nodePopUp.setVisible(true);						
						}
					}else if(flag == 2){
						if(userObject.format != null){
							positionFlag = 21;
							leafPopUp.show(projectJTree, ex, ey);
							leafPopUp.pack();
							leafPopUp.setVisible(true);
						}else{
/*							positionFlag = 20;
							nodePopUp.show(projectTree, ex, ey);
							nodePopUp.pack();
							nodePopUp.setVisible(true);						
*/						}
					}else if(flag == 3){
						if(userObject.nolLabel != null){
							positionFlag = 31;
							leafPopUp.show(projectJTree, ex, ey);
							leafPopUp.pack();
							leafPopUp.setVisible(true);
						}else{
							positionFlag = 30;
							nodePopUp.show(projectJTree, ex, ey);
							nodePopUp.pack();
							nodePopUp.setVisible(true);						
						}
					}else if(flag == 4){
						if(userObject.preprocessor != null){
							positionFlag = 41;
							leafPopUp.show(projectJTree, ex, ey);
							leafPopUp.pack();
							leafPopUp.setVisible(true);
						}else{
							positionFlag = 40;
							nodePopUp.show(projectJTree, ex, ey);
							nodePopUp.pack();
							nodePopUp.setVisible(true);						
						}
					}else if(flag == 6){
						if(userObject.predictiveModel != null){
							positionFlag = 61;
							leafPopUp.show(projectJTree, ex, ey);
							leafPopUp.pack();
							leafPopUp.setVisible(true);
						}else{
							positionFlag = 60;
							nodePopUp.show(projectJTree, ex, ey);
							nodePopUp.pack();
							nodePopUp.setVisible(true);						
						}
					}else if(flag == 10){
						if(userObject.bpnModel != null){
							positionFlag = 101;
							leafPopUp.show(projectJTree, ex, ey);
							leafPopUp.pack();
							leafPopUp.setVisible(true);
						}else{
							positionFlag = 100;
							nodePopUp.show(projectJTree, ex, ey);
							nodePopUp.pack();
							nodePopUp.setVisible(true);						
						}
					}else if(flag == 11){
						if(userObject.annModel != null){
							positionFlag = 111;
							leafPopUp.show(projectJTree, ex, ey);
							leafPopUp.pack();
							leafPopUp.setVisible(true);
						}else{
							positionFlag = 110;
							nodePopUp.show(projectJTree, ex, ey);
							nodePopUp.pack();
							nodePopUp.setVisible(true);						
						}
					}else if(flag == 12){
						if(userObject.rbfnModel != null){
							positionFlag = 121;
							leafPopUp.show(projectJTree, ex, ey);
							leafPopUp.pack();
							leafPopUp.setVisible(true);
						}else{
							positionFlag = 120;
							nodePopUp.show(projectJTree, ex, ey);
							nodePopUp.pack();
							nodePopUp.setVisible(true);						
						}
					}else if(flag == 13){
						if(userObject.rhoModel != null){
							positionFlag = 131;
							leafPopUp.show(projectJTree, ex, ey);
							leafPopUp.pack();
							leafPopUp.setVisible(true);
						}else{
							positionFlag = 130;
							nodePopUp.show(projectJTree, ex, ey);
							nodePopUp.pack();
							nodePopUp.setVisible(true);						
						}

					}else if(flag == 14){
						if(userObject.plsModel != null){
							positionFlag = 141;
							leafPopUp.show(projectJTree, ex, ey);
							leafPopUp.pack();
							leafPopUp.setVisible(true);
						}else{
							positionFlag = 140;
							nodePopUp.show(projectJTree, ex, ey);
							nodePopUp.pack();
							nodePopUp.setVisible(true);						
						}
					}else if(flag == 15){
						if(userObject.pcaModel != null){
							positionFlag = 151;
							leafPopUp.show(projectJTree, ex, ey);
							leafPopUp.pack();
							leafPopUp.setVisible(true);
						}else{
							positionFlag = 150;
							nodePopUp.show(projectJTree, ex, ey);
							nodePopUp.pack();
							nodePopUp.setVisible(true);						
						}


/*					}else if(flag == 14){
						if(userObject.genOptimization != null){
							positionFlag = 141;
							leafPopUp.show(projectTree, ex, ey);
							leafPopUp.pack();
							leafPopUp.setVisible(true);
						}else{
							positionFlag = 140;
							nodePopUp.show(projectTree, ex, ey);
							nodePopUp.pack();
							nodePopUp.setVisible(true);						
						}

*/					}else if(flag == 7){
						if(userObject.optimizeModel != null){
							positionFlag = 71;
							leafPopUp.show(projectJTree, ex, ey);
							leafPopUp.pack();
							leafPopUp.setVisible(true);
						}else{
							positionFlag = 70;
							nodePopUp.show(projectJTree, ex, ey);
							nodePopUp.pack();
							nodePopUp.setVisible(true);						
						}
					}else if(flag == 8){
						if(userObject.simulation != null){
							positionFlag = 81;
							leafPopUp.show(projectJTree, ex, ey);
							leafPopUp.pack();
							leafPopUp.setVisible(true);
						}else{
							positionFlag = 80;
							nodePopUp.show(projectJTree, ex, ey);
							nodePopUp.pack();
							nodePopUp.setVisible(true);						
						}
					}else if(flag == 9){
						if(userObject.optimization != null){
							positionFlag = 91;
							leafPopUp.show(projectJTree, ex, ey);
							leafPopUp.pack();
							leafPopUp.setVisible(true);
						}else{
							positionFlag = 90;
							nodePopUp.show(projectJTree, ex, ey);
							nodePopUp.pack();
							nodePopUp.setVisible(true);						
						}
					}
				}
			}else if(clickCount == 2){
				if(flag	== 1){
					if(userObject.dataSeries != null){
						mainFrame.showDataSeriesWKSP(userObject.dataSeries);
					}
				}else if(flag == 2){
					if(userObject.format != null){
						mainFrame.showFileFormatWKSP(userObject.format);
					}
				}else if(flag == 3){
					if(userObject.nolLabel != null){
						mainFrame.showLabelWKSP(userObject.nolLabel);
					}
				}else if(flag == 4){
					if(userObject.preprocessor != null){
						mainFrame.showPreprocessorWKSP(userObject.preprocessor);
					}
				}else if(flag == 6){
					if(userObject.predictiveModel != null){
						mainFrame.showPredictiveModelWKSP(userObject.predictiveModel);
					}
				}else if(flag == 7){
					if(userObject.optimizeModel != null){
						mainFrame.showOptimizeModelWKSP(userObject.optimizeModel);
					}
				}else if(flag == 8){
					if(userObject.simulation != null){
						mainFrame.showSimulationWKSP(userObject.simulation);
					}
				}else if(flag == 9){
					if(userObject.optimization != null){
						mainFrame.showOptimizationWKSP(userObject.optimization);
					}
				}else if(flag == 10){
					if(userObject.bpnModel != null){
						mainFrame.showClassicModelWKSP(userObject.bpnModel);
					}
				}else if(flag == 11){
					if(userObject.annModel != null){
						mainFrame.showClassicModelWKSP(userObject.annModel);
					}
				}else if(flag == 12){
					if(userObject.rbfnModel != null){
						mainFrame.showClassicModelWKSP(userObject.rbfnModel);
					}
				}else if(flag == 13){
					if(userObject.rhoModel != null){
						mainFrame.showRhoModelWKSP((NolRhoModel)userObject.rhoModel);
					}
				}else if(flag == 14){
					if(userObject.plsModel != null){
						mainFrame.showPlsModelWKSP((NolPlsModel)userObject.plsModel);
					}
				}else if(flag == 15){
					if(userObject.pcaModel != null){
						mainFrame.showPcaModelWKSP((NolPcaModel)userObject.pcaModel);
					}
				}
			}
		}
		@Override
		public void mousePressed(MouseEvent e){}
		@Override
		public void mouseReleased(MouseEvent e){}
		@Override
		public void mouseEntered(MouseEvent e){}
		@Override
		public void mouseExited(MouseEvent e){}	
	}


		/** Add child to the selected parent node. */
	public DefaultMutableTreeNode addObject(final DefaultMutableTreeNode parent,
			final Object child, 
			final boolean shouldBeVisible) {
		DefaultMutableTreeNode parentNode = parent;
		DefaultMutableTreeNode childNode = 
						new DefaultMutableTreeNode(child);
		if (parentNode == null) {
				parentNode = topNode;
		}
		treeModel.insertNodeInto(childNode, parentNode, 
														 parentNode.getChildCount());

		// Make sure the user can see the lovely new node.
		if (shouldBeVisible) {
				projectJTree.scrollPathToVisible(new TreePath(childNode.getPath()));
		}
		return childNode;
	}


	 /**
	 * ProjectTreeNodeObj
	 * @version     1.0 August 20, 1998
	 * @author      Gang Chen
	 **/
    
	class ProjectTreeNodeObj {
		protected int flag; //0:project 1:dataseries 2:var 3:label 4:case 5:model
		protected String name;
		protected DataSeries dataSeries;
		protected Preprocessor preprocessor;
		protected NolLabel nolLabel;
		protected NolModel2 predictiveModel;
		protected NolOptimizeModel optimizeModel;
		protected ResponseSurfaceSimulation simulation;
		protected NolOptimization optimization;
		protected DataSeriesFileFormat format;

		protected NolBpnModel bpnModel;
		protected NolAnnModel annModel;
		protected NolRbfnModel rbfnModel;
		protected NolRhoModel rhoModel;
		protected NolPlsModel plsModel;
		protected NolPcaModel pcaModel;
//		protected NolGenOptimization genOptimization;

		public ProjectTreeNodeObj(String n) {
			name = n;
			flag = 0;
			dataSeries = null;
			preprocessor = null;
			nolLabel = null;
	    }

		public ProjectTreeNodeObj(String n, int f) {
			this(n);
			flag = f;
		}

        public ProjectTreeNodeObj(DataSeries ds) {
            this(ds.getDataSource().getName()+"."+ds.getName());
			dataSeries = ds;
			flag = 1;
       }

        public ProjectTreeNodeObj(DataSeriesFileFormat ft) {
            this(ft.getName());
			format = ft;
			flag = 2;
       }

        public ProjectTreeNodeObj(NolLabel lab) {
            this(lab.getName());
			nolLabel = lab;
			flag = 3;
       }

        public ProjectTreeNodeObj(Preprocessor prep) {
            this(prep.getName());
			preprocessor = prep;
			flag = 4;
       }

        public ProjectTreeNodeObj(NolModel2 model) {
            this(model.getName());
			predictiveModel = model;
			flag = 6;
       }

        public ProjectTreeNodeObj(NolOptimizeModel model) {
            this(model.getName());
			optimizeModel = model;
			flag = 7;
       }
        
		public ProjectTreeNodeObj( ResponseSurfaceSimulation simulation) {
            this(simulation.getName());
			this.simulation = simulation;
			flag = 8;
       }
							  
		public ProjectTreeNodeObj( NolOptimization optimization) {
            this(optimization.getName());
			this.optimization = optimization;
			flag = 9;
		}
							  
		public ProjectTreeNodeObj(NolBpnModel model) {
            this(model.getName());
			this.bpnModel = model;
			flag = 10;
		}
							  
		public ProjectTreeNodeObj(NolAnnModel model) {
            this(model.getName());
			this.annModel = model;
			flag = 11;
		}
							  
		public ProjectTreeNodeObj(NolRbfnModel model) {
            this(model.getName());
			this.rbfnModel = model;
			flag = 12;
		}
							  
		public ProjectTreeNodeObj(NolRhoModel model) {
            this(model.getName());
			this.rhoModel = model;
			flag = 13;
		}
		public ProjectTreeNodeObj(NolPlsModel model) {
            this(model.getName());
			this.plsModel = model;
			flag = 14;
		}
		public ProjectTreeNodeObj(NolPcaModel model) {
            this(model.getName());
			this.pcaModel = model;
			flag = 15;
		}
							  
/*		public ProjectTreeNodeObj( NolGenOptimization genOptimization) {
            this(genOptimization.getName());
			this.genOptimization = genOptimization;
			flag = 14;
		}
*/							  
		public int getFlag(){
			return flag;
		}

    @Override
    public String toString() {
        return name;
    }
  }

	class projectTreeCellRenderer extends JLabel implements TreeCellRenderer {
    /** Is the value currently selected. */
		boolean selected;

		public projectTreeCellRenderer() {
			setHorizontalAlignment(JLabel.LEFT);
		}

     /**
       * Configures the renderer based on the passed in components.
       * The value is set from messaging value with toString().
       * The foreground color is set based on the selection and the icon
       * is set based on on leaf and expanded.
       */
     
		@Override
		public Component getTreeCellRendererComponent(JTree tree, Object  value, 
			boolean selected, boolean expanded, boolean leaf, int row, 
			boolean hasFocus){

			String stringValue = tree.convertValueToText(value, selected, expanded, 
				leaf, row, hasFocus);
			setText(stringValue);
			
			ProjectTreeNodeObj userObject = 
				(ProjectTreeNodeObj)((DefaultMutableTreeNode)value).getUserObject();

			int flag = userObject.getFlag();

			if(flag == 0){
				setIcon(UIManager.getIcon("Tree.closedIcon"));
			}else if(flag == 1){
				setIcon(UIManager.getIcon("Tree.leafIcon"));
			}
//0:project 1:dataseries 2:var 3:label 4:case 5:model
			
			if(selected) {
				setBackground(java.awt.SystemColor.activeCaption);
				setForeground(java.awt.SystemColor.activeCaptionText);
			}else {  // set all other objects to that of the plain leaf icon
				setBackground(projectJTree.getBackground());
				setForeground(Color.black);
			}
			this.selected = selected;
			return this;
		}
     /**
       * Paints the value.  The background is filled based on selected.
       */

		@Override
		public void paint(Graphics g) {
			Color bColor;
			bColor = getBackground();
			if(bColor != null) {
				Icon currentI = getIcon();
				g.setColor(bColor);
				if(currentI != null && getText() != null) {
					int offset = (currentI.getIconWidth() + getIconTextGap());
					g.fillRect(offset, 0, getWidth() - 1 - offset, getHeight() - 1);
				} else {
					g.fillRect(0, 0, getWidth()-1, getHeight()-1);
				}
			}
			super.paint(g);
		}
	}

	class ProjectTreeModelListener implements TreeModelListener {
		@Override
		public void treeNodesChanged(TreeModelEvent e) {
				DefaultMutableTreeNode node;
				node = (DefaultMutableTreeNode)
								 (e.getTreePath().getLastPathComponent());

				/*
				 * If the event lists children, then the changed
				 * node is the child of the node we've already
				 * gotten.  Otherwise, the changed node and the
				 * specified node are the same.
				 */
				try {
						int index = e.getChildIndices()[0];
						node = (DefaultMutableTreeNode)
									 (node.getChildAt(index));
				} catch (NullPointerException exc) {}

				System.out.println("The user has finished editing the node.");
				System.out.println("New value: " + node.getUserObject());
		}
		@Override
		public void treeNodesInserted(TreeModelEvent e) {
		}
		@Override
		public void treeNodesRemoved(TreeModelEvent e) {
		}
		@Override
		public void treeStructureChanged(TreeModelEvent e) {
		}
	}
	@Override
	public void LabelCategoryAdded(RawDataEvent e) {}
	@Override
	public void LabelCategoryRemoved(RawDataEvent e){}
	@Override
	public void DataPointsLabeled(RawDataEvent e){}
	@Override
	public void LabelOrderChanged(RawDataEvent e){}
	@Override
	public void LabelNameChanged(RawDataEvent e){}
	@Override
	public void LabelColorChanged(RawDataEvent e){}
	@Override
	public void DataSeriesAdded(RawDataEvent e){
		DataSeries ds = e.getDataSeries();
		addDataSeries(ds,true);
	}
	@Override
	public void DataSeriesRemoved(RawDataEvent e){
	
	}
	
}

