package com.gensym.nols.main;

/**
 *		Gensym NolMainFrame Class
 *		This class is extended from JFrame.class
 *		Modified 11/12/97 by Gchen
 */

import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.net.*;
import java.nio.charset.Charset;
import java.util.*;
import java.lang.reflect.*;
import java.awt.print.*;
import java.text.*;
import java.util.zip.*;

import javax.swing.*;
import javax.swing.event.*;

import com.gensym.math.datafit.ClassicModel;
import com.gensym.math.matrix.*;
import com.gensym.math.MathException;
import com.gensym.nols.data.*;
import com.gensym.nols.dlg.*;
import com.gensym.nols.wksp.*;
import com.gensym.nols.chart.line.*;
import com.gensym.nols.chart.scatter.*;
import com.gensym.nols.chart.bar.*; // bbush, 9-9-98
import com.gensym.nols.deploy.NolG2Gateway;

import com.gensym.DEBUG;

public class NolMainFrame extends JFrame {

    protected JLayeredPane editor = null;
    protected Hashtable commands = null;
    protected Hashtable allCommands = null;
    protected Hashtable menuItems = null;
    protected JMenu windowMenu;
	protected JMenuBar menubar = null;				 
    protected JToolBar toolbar = null;
    protected Hashtable toolbarItems = null;
    protected JPanel status = null;
    protected JTextField progress = null;
    protected static volatile ResourceBundle nolResources= null;	  //Temp for development Gchen 4/21/99
    protected static final ResourceBundle MAIN_RESOURCES = 
        ResourceBundle.getBundle("com.gensym.nols.main.NolMainFrame", Locale.getDefault());
	private Container nativeContainer;
	private Cursor outerCursor;

	protected ProjectTree projectTree;
	protected JScrollPane projectTreePane; //Temp  Gchen 9/8/98

	protected JComboBox labelStatus;
	private boolean labelStatusFire;
	private Component gp;  // the frame's glass pane 

	protected JToggleButton selectStatus;
	protected JButton logoButton;
	protected static volatile ImageIcon	defaultLogo;
	protected JTextField connectionStatus;


	protected MainFrameAction mainAction;
	
    private int interCount = 0;
    private int actionHoldCount = 0;
	protected Project2 project = null;
	protected Class versionManagerClass = null;
	protected Object versionManager = null;
 
	protected NolInternalFrame activeInternalFrame = null;

	protected Vector defaultActions;
    protected Vector internalFrameStack;
	protected ObjectLoaderThread objectLoader;

    public static volatile ImageIcon    gensymLogo;
	
    public static volatile String rootDirectory;
    public static volatile String miscDirectory;
    public static volatile String projectDirectory;
    public static volatile File currentDirectory;

	
	private SimpleDateFormat dateFormat;	
	private SimpleDateFormat timeFormat;

	private int optNMAX = 10000;

	protected NolG2Gateway g2Gateway;

	/**
     * Suffix applied to the key used in resource file
     * lookups for an image.
     */
    protected static final String imageSuffix = "Image";

    /**
     * Suffix applied to the key used in resource file
     * lookups for a label.
     */
    protected static final String labelSuffix = "Label";

    /**
     * Suffix applied to the key used in resource file
     * lookups for an action.
     */
    protected static final String actionSuffix = "Action";

    /**
     * Suffix applied to the key used in resource file
     * lookups for tooltip text.
     */
    protected static final String tipSuffix = "Tooltip";

    protected static final String newAction  = "new";
    protected static final String openAction = "open";
    protected static final String closeAction = "close";
    protected static final String renameAction = "rename";
    protected static final String importAction = "import";
    protected static final String importG2Action = "importG2";
    protected static final String importNetAction = "importNet";
    protected static final String exportAction = "export";
    protected static final String saveAction = "save";
    protected static final String saveasAction = "saveas";
    protected static final String printAction = "print";

    protected static final String preferenceAction = "preference";
    protected static final String connectG2Action = "connectg2";
    protected static final String disconnectG2Action = "disconnectg2";
    
	protected static final String exitAction = "exit";

    protected static final String undoAction = "undo";
    protected static final String redoAction = "redo";
    protected static final String findAction = "find";
    protected static final String replaceAction = "replace";
    protected static final String labelingAction = "labeling";

    protected static final String spreadsheetAction = "spreadsheet";
    protected static final String linechartAction = "linechart";
    protected static final String xymapAction = "xymap";
    protected static final String projectmapAction = "projectmap";
    protected static final String histogramAction = "histogram";
    protected static final String toolbarsAction = "toolbars";

    protected static final String newdataseriesAction = "newdataseries";
    protected static final String newlabelAction = "newlabel";
    protected static final String newpreprocessorAction = "newpreprocessor";
    protected static final String newpredictmodelAction = "newpredictmodel";
    protected static final String newbpnmodelAction = "newbpnmodel";
    protected static final String newannmodelAction = "newannmodel";
    protected static final String newrhomodelAction = "newrhomodel";
    protected static final String newrbfnmodelAction = "newrbfnmodel";
    protected static final String newplsmodelAction = "newplsmodel";
    protected static final String newpcamodelAction = "newpcamodel";
    protected static final String newoptimizemodelAction = "newoptimizemodel";
    protected static final String newsimulationAction = "newsimulation";
    protected static final String newoptimizationAction = "newoptimization";
    protected static final String newgenoptimizationAction = "newgenoptimization";
 
	protected static final String gotodataseriesAction = "gotodataseries";
	protected static final String gotolabelAction = "gotolabel";
    protected static final String gotopreprocessorAction = "gotopreprocessor";
    protected static final String gotopredictmodelAction = "gotopredictmodel";
    protected static final String gotobpnmodelAction = "gotobpnmodel";
    protected static final String gotoannmodelAction = "gotoannmodel";
    protected static final String gotorbfnmodelAction = "gotorbfnmodel";
    protected static final String gotorhomodelAction = "gotorhomodel";
    protected static final String gotoplsmodelAction = "gotoplsmodel";
    protected static final String gotopcamodelAction = "gotopcamodel";
    protected static final String gotooptimizemodelAction = "gotooptimizemodel";
    protected static final String gotosimulationAction = "gotosimulation";
    protected static final String gotooptimizationAction = "gotooptimization";
    protected static final String gotogenoptimizationAction = "gotogenoptimization";
	
	protected static final String deletedataseriesAction = "deletedataseries";
	protected static final String deletelabelAction = "deletelabel";
    protected static final String deletepreprocessorAction = "deletepreprocessor";
	protected static final String deletepredictmodelAction = "deletepredictmodel";
	protected static final String deletebpnmodelAction = "deletebpnmodel";
	protected static final String deleteannmodelAction = "deleteannmodel";
	protected static final String deleterbfnmodelAction = "deleterbfnmodel";
	protected static final String deleterhomodelAction = "deleterhomodel";
	protected static final String deleteplsmodelAction = "deleteplsmodel";
	protected static final String deletepcamodelAction = "deletepcamodel";
    protected static final String deleteoptimizemodelAction = "deleteoptimizemodel";
    protected static final String deletesimulationAction = "deletesimulation";
    protected static final String deleteoptimizationAction = "deleteoptimization";
    protected static final String deletegenoptimizationAction = "deletegenoptimization";
	
	protected static final String cascadeAction = "cascade";
    protected static final String horizontalAction = "horizontal";
    protected static final String verticalAction = "vertical";
    protected static final String windowsAction = "windows";
    protected static final String closewindowsAction = "closewindows";
    protected static final String memoryAction = "memory";
	protected static final String aboutAction = "about";

	protected static final String contentsAction = "contents";
    protected static final String projectwinAction = "projectwin";
    protected static final String consoleAction = "console";
 
 	protected static final String labelToggleLabel = "labelToggleLabel";
	protected static final String unlabelToggleLabel = "unlabelToggleLabel";
	protected static final String labelToggleTip = "labelToggleTip";
	protected static final String unlabelToggleTip = "unlabelToggleTip";
	protected static final String labelComboTip = "labelComboTip";
	
	private static final String OK = "OkButtonLabel";
	private static final String YES = "YesButtonLabel";
	private static final String NO = "NoButtonLabel";
	private static final String CANCEL = "CancelButtonLabel";
	private static final String NOVALIDAUTHORIZATION = "MainFrame_NoValidAuthorization";
	private static final String CANNOTLOADFILE = "MainFrame_CanNotLoadFile";
	private static final String CANNOTLOADDATAFROM = "MainFrame_CanNotLoadDataFrom";
	private static final String CANNOTLOADDATAERROR = "MainFrame_CanNotLoadDataError";

	

	private static final String NODATAMATCHMODEL = "MainFrame_NoDataMatchModel";
	private static final String INVALIDDATACHOICE = "MainFrame_InvalidDataChoice";
	private static final String NOVALIDATIONDATA = "MainFrame_NoValidationData";
	private static final String CANCELLOADINGPROJECT = "MainFrame_CancelLoadingProject";
	private static final String DONELOADINGPROJECT = "MainFrame_DoneLoadingProject";
	private static final String SAMENAMEEXISTINGDATA = "MainFrame_SameNameExistingData";
	private static final String DOUSEEXISTINGFORMAT = "MainFrame_DoUseExistingFormat";
	private static final String IMPORTDATA = "MainFrame_ImportData";
	private static final String PREPAREDATAWKSP = "MainFrame_PreparedDataWksp";
	private static final String DONEIMPORTDATA = "MainFrame_DoneImportData";
	private static final String CANCELLOADINGDATA = "MainFrame_CancelLoadingData";
	private static final String MUSTDELETEDATASOURCE = "MainFrame_MustDeleteDataSource";
	private static final String MUSTCLOSEALLFORTHIS = "MainFrame_MustCloseAllForThis";
	private static final String CANNOTREMOVEDATA = "MainFrame_CanNotRemoveData";
	private static final String DODELETEDATA = "MainFrame_DoDeleteData";
	private static final String DATASERIES = "MainFrame_DataSeries";
	private static final String ISREMOVED = "MainFrame_IsRemoved";
	private static final String WRONGURLFORMAT = "MainFrame_WrongURLFormat";
	private static final String APPENDDATA = "MainFrame_AppendData";
	private static final String DONEAPPENDDATA = "MainFrame_DoneAppendData";
	private static final String SAVEDATA = "MainFrame_SaveData";
	private static final String DONESAVEDATA = "MainFrame_DoneSaveData";
	private static final String ACTIONNOTALLOWED = "MainFrame_ActionNotAllowed";
	private static final String SAVEABORTED = "MainFrame_SaveAborted";
	private static final String SAVEPROJECT = "MainFrame_SaveProject";
	private static final String DONESAVEPROJECT = "MainFrame_DoneSaveProject";
	private static final String DOSAVEPROJECT = "MainFrame_DoSaveProject";
	private static final String DODISCARDPROJECT = "MainFrame_DoDiscardProject";
	private static final String DONENEWPROJECT = "MainFrame_DoNewProject";
	private static final String LOADPROJECT = "MainFrame_LoadProject";
	private static final String CANNOTDELETEPREPROCESSOR = "MainFrame_CanNotDeletePreprocessor";
	private static final String DODELETEPREPROCESSOR = "MainFrame_DoDeletePreprocessor";
	private static final String PREPROCESSOR = "MainFrame_Preprocessor";
	private static final String DONECLOSEPROJECT = "MainFrame_DoneCloseProject";
	private static final String LOADDATAINSPREADSHEET = "MainFrame_LoadDataInSpreadSheet";
	private static final String LOADDATAINLINECHART = "MainFrame_LoadDataInLineChart";
	private static final String LOADDATAINXYCHART = "MainFrame_LoadDataInXYChart";
	private static final String CANNOTDISPLYPROJECTION = "MainFrame_CanNotDisplayProjection";
	private static final String LOADDATAINPROJECTCHART = "MainFrame_LoadDataInProjectionChart";
	private static final String CANNOTDELETELABEL = "MainFrame_CanNotDeleteLabel";
	private static final String DODELETELABEL = "MainFrame_DoDeleteLabel";
	private static final String LABEL = "MainFrame_Label";
	private static final String MUSTSELECTDATA = "MainFrame_MustSelectData";
	private static final String HAVESAMENAMEPREPROCESSOR = "MainFrame_HaveSameNamePreprocessor";
	private static final String CANCELNEWPREPROCESSOR = "MainFrame_CancelNewPreprocessor";
	private static final String DONENEWPREPROCESSOR = "MainFrame_DoneNewPreprocessor";
	private static final String NOVARIABLEFORPREPROCESSOR = "MainFrame_NoVariableForPreprocessor";
	private static final String CANNOTREMOVEMODELWITHSIMULATION = "MainFrame_CanNotRemoveModelWithSimulation";
	private static final String CANNOTREMOVEMODELWITHOPTIMIZATION = "MainFrame_CanNotRemoveModelWithOptimization";
	private static final String DODELETEMODEL = "MainFrame_DoDeleteModel";
	private static final String PREMODEL = "MainFrame_PredictModel";
	private static final String NOPREPROCESSORFORMODEL = "MainFrame_NoPreprocessorForModel";
	private static final String CANCELNEWMODEL = "MainFrame_CancelNewModel";
	private static final String DODELETESIMULATION = "MainFrame_DoDeleteSimulation";
	private static final String SIMULATION = "MainFrame_Simulation";
	private static final String NOMODELFORSIMULATION = "MainFrame_NoModelForSimulation";
	private static final String DODELETEOPTIMIZATION = "MainFrame_DoDeleteOptimization";
	private static final String OPTIMIZATION = "MainFrame_Opitmization";
	private static final String NOMODELFOROPTIMIZATION = "MainFrame_NoModelForOpimization";
	private static final String DODELETEFILEFORMAT = "MainFrame_DoDeleteFileFormat";
	private static final String FILEFORMAT = "MainFrame_FileFormat";
	private static final String EXITSTUDIO = "MainFrame_ExitStudio";
	private static final String G2DISCONNECTED = "G2_disconnected";
	private static final String G2DISCONNECTINGSTARTED = "G2_disconnecting_started";


	private static final String NONMONOTONICDATA = "MainFrame_NonMonitonicData";
	
	
	public static final Dimension hpad10 = new Dimension(10,1);
    public static final Dimension hpad5 = new Dimension(5,1);

    public static final Dimension vpad5 = new Dimension(1,5);
	public static final Dimension vpad15 = new Dimension(1,15);
    public static final Dimension vpad20 = new Dimension(1,20);
    public static final Dimension vpad25 = new Dimension(1,25);
    public static final Dimension vpad50 = new Dimension(1,50);
    public static final Dimension vpad40 = new Dimension(1,40);
    public static final Dimension vpad100 = new Dimension(1,100);
    public static final Dimension vpad200 = new Dimension(1,200);
    public static final Dimension vpad150 = new Dimension(1,150);
    public static final Dimension vpad300 = new Dimension(1,300);
    public static final Dimension vpad500 = new Dimension(1,500);

    public static final Dimension pad5020 = new Dimension(50,20);
    public static final Dimension pad3020 = new Dimension(30,20);

	private boolean defaultProjectName;

	private boolean isConnectedWithG2;
	private boolean blockMainAction;

	private boolean menuFlag_hasDataSeries;
	private boolean menuFlag_hasPreprocessor;
	private boolean menuFlag_hasPredictiveModel;
	private boolean menuFlag_hasBpnModel;
	private boolean menuFlag_hasAnnModel;
	private boolean menuFlag_hasRbfnModel;
	private boolean menuFlag_hasRhoModel;
	private boolean menuFlag_hasPlsModel;
	private boolean menuFlag_hasPcaModel;
	private boolean menuFlag_hasOptimizationModel;
	private boolean menuFlag_hasLabel;
	private boolean menuFlag_hasSimulation;
	private boolean menuFlag_hasOptimization;
	private boolean menuFlag_hasGenOptimization;

	private FileDialog fileDialog = null;
	private JFileChooser fileChooser = null;
	private NolNewLabelWizard newLabelWizard = null; 
	private NolXYChoiceDialog xyChoiceDialog = null;
	private NolTripleChoiceDialog tripleChoiceDialog = null;
	private NolDoubleChoiceDialog doubleChoiceDialog = null;
	private NolSingleChoiceDialog singleChoiceDialog = null;
	private NolWindowsChoiceDialog windowsChoiceDialog= null;
	private NolNewPreprocessorWizard newPreprocessorWizard = null;
	private NolConfirmDialog confirmDialog = null;
	private NolNewPredictiveModelWizard newPredictiveModelWizard = null;
	private NolNewBpnModelWizard newBpnModelWizard = null;
	private NolNewAnnModelWizard newAnnModelWizard = null;
	private NolNewRbfnModelWizard newRbfnModelWizard = null;
	private NolNewRhoModelWizard newRhoModelWizard = null;
	private NolNewPlsModelWizard newPlsModelWizard = null;
	private NolNewPcaModelWizard newPcaModelWizard = null;
	private NolTrainDialog trainDialog = null;
	private NolBpnTrainDialog bpnTrainDialog = null;
	private NolRbfnTrainDialog rbfnTrainDialog = null;
	private NolRhoTrainDialog rhoTrainDialog = null;

	private NolNewOptimizeModelWizard newOptimizeModelWizard = null;
	private NolNewSimulationWizard newSimulationWizard;
	private NolNewOptimizationWizard newOptimizationWizard;
	private NolNewGenOptimizationWizard newGenOptimizationWizard;
	private NolAboutDialog aboutDialog = null;
	private NolDataSeriesInputWizard dataSeriesInputWizard = null;
	private NolReplaceDialog replaceDialog = null;
	private NolPreferenceDialog preferenceDialog = null;
	private NolConnectG2Dialog connectG2Dialog = null;
	private NolModelValidateChoiceDialog modelValidateChoiceDialog;
	private NolURLImportDialog URLImportDialog = null;

	private boolean blockButtonAction;

    static {   
        try {
            nolResources = ResourceBundle.getBundle("com.gensym.nols.main.NolStringResources", Locale.getDefault());
        } catch (MissingResourceException mre) {
            System.err.println("NolStringResources.properties not found");
            System.exit(1);
        }
    }
    
	private boolean isDemoVersion = false;
	public static volatile NolMainFrame mainFrame;
	
	public NolMainFrame() {
	  mainFrame = this;
		project = new Project2();
		try {
			versionManagerClass = Class.forName("com.gensym.nols.data.VersionManager");
			versionManager = versionManagerClass.newInstance();
			Method method = versionManagerClass.getMethod("setProject",new Class[] {project.getClass()});
			method.invoke(versionManager,new Object[] {project});
		} catch (Exception ex) {
			System.out.println("ex="+ex.toString());
			isDemoVersion = true;
			versionManagerClass = null;
			versionManager = null;
		}  
		if(((VersionManager)versionManager).isEvaluationCopy()){
			isDemoVersion = true;
		}
		setTitle(MAIN_RESOURCES.getString("Title"));
		setBackground(Color.lightGray);
        URL url = this.getClass().getResource("logo-small-0.jpg");
        defaultLogo = new ImageIcon(url);
        url = this.getClass().getResource("framelogo.jpg");
        gensymLogo = new ImageIcon(url);
		setIconImage(gensymLogo.getImage());

		projectTree = new ProjectTree(this);
// initialize whole action array
		initializeMenuFlag();
		initializeAction();
		project.getRawDataSource().addListener(mainAction);
		project.getRawDataSource().addListener(projectTree);
		project.addProjectListener(mainAction);

		JPanel nolMainPanel = new JPanel();
		nolMainPanel.setBorder(BorderFactory.createEtchedBorder());
		nolMainPanel.setLayout(new BorderLayout());

	// create the menu system and layout
		menuItems = new Hashtable();
		menubar = createMenubar();
		toolbarItems = new Hashtable();

		nolMainPanel.add("North", menubar);
		nolMainPanel.add("Center", getCenterPane());
		nolMainPanel.add("South", createStatusbar());
		setContentPane(nolMainPanel);

		setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);

		pack();
		setSize(1024, 760);
		internalFrameStack = new Vector();

		isConnectedWithG2 = false;
		blockMainAction = false;
		defaultProjectName = true;

		blockButtonAction = false;

// create the action array
		defaultActions = new Vector();
		commands = new Hashtable();
		modifyDefaultAction();

		String tempDir = System.getProperties().getProperty("user.dir");
		if (tempDir.endsWith("\\bin")){
			String newDir =  tempDir;
			newDir = newDir.replaceAll("bin", "projects");
//System.out.println("newDir = "+newDir);
//System.out.println("tempdir = "+tempDir);
			currentDirectory = new File(newDir);
			if (currentDirectory.isDirectory()){
				miscDirectory = new String(newDir);
				projectDirectory = new String(newDir);
				rootDirectory = new String(tempDir);
			}else{
				miscDirectory = System.getProperties().getProperty("user.dir");
				projectDirectory = System.getProperties().getProperty("user.dir");
				rootDirectory = System.getProperties().getProperty("user.dir");
				currentDirectory = new File(miscDirectory);
			}
		}else{
			miscDirectory = System.getProperties().getProperty("user.dir");
			projectDirectory = System.getProperties().getProperty("user.dir");
			rootDirectory = System.getProperties().getProperty("user.dir");
			currentDirectory = new File(miscDirectory);
		}
// Set the properties for tooltips

		ToolTipManager.sharedInstance().setDismissDelay(1000000);

		gp = getGlassPane(); // MK added 2/6/99 to support wait cursor
		gp.addMouseListener(new MouseAdapter(){});
		Container parent = this;
	    while (! ((parent instanceof Panel) ||
			(parent instanceof ScrollPane) ||
			(parent instanceof Window)))
			parent = parent.getParent();
	    nativeContainer = parent;
		if(isDemoVersion) {
			if(showYesNoDialog(getNolResourceString(NOVALIDAUTHORIZATION),2)!=1)
				System.exit(0);

			LicenseFrame lf = new LicenseFrame(this,"License Agreement");
			String licenseText = new String();
			File licenseFile;
			char[] buff = new char[50000];
			
			FileInputStream inStream = null;
			InputStreamReader reader = null;
			try {
				licenseFile = new File("demolicense.txt");
				inStream = new FileInputStream(licenseFile);	
				reader = new InputStreamReader(inStream, Charset.defaultCharset());
				int nch;
				while ((nch = reader.read(buff, 0, buff.length)) != -1) {
					licenseText = licenseText + new String(buff, 0, nch);
				}
			} catch (java.io.IOException ex) {
				showOKDialog(getNolResourceString(CANNOTLOADFILE)+": demoLicense.txt");
//				showOKDialog("Could not load file"+": demoLicense.txt");
				System.exit(0);
			}finally{
				closeSilently(reader);
				closeSilently(inStream);
			}
			lf.setMessage(licenseText);
			lf.setBounds(200,200,555, 450);
			lf.setVisible(true);
			if(lf.getConfirmed()){
				lf.dispose();
				return;
			}else{
				System.exit(0);
			}		
		}
// Test file format readability and writebility
		File ffmt = new File("fileformat.fmt");	
		if(ffmt.exists()){
			if(!ffmt.canWrite()){
				showOKDialog(getNolResourceString("MainFrame_CanNotWriteFileFormat"));				
			}
		}
		SimpleDateFormat settingsDF = NolSettings.getSettings().getDateFormat();
		SimpleDateFormat settingsTF = NolSettings.getSettings().getTimeFormat();
		if (settingsDF != null && settingsTF != null){
			dateFormat = settingsDF;
			timeFormat = settingsTF;
			setDateTimeFormat(settingsDF, settingsTF);
		} else {
			dateFormat = new SimpleDateFormat("MM/dd/yy");	
			timeFormat = new SimpleDateFormat("H:mm:ss");
		}
	}
	
	private void closeSilently(Closeable obj){
		  try {
		      if (obj != null) 
		    	  obj.close();
	      } catch (IOException e) {
	    	  System.err.println("Non-Fatal exception: Error while closing stream : " + e.toString());
	    	  e.printStackTrace();
	      } 
	}

	private void setWaitCursor(boolean p) {
		if(p) {
			gp.setVisible(true);
			gp.setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));
			// force immediate change of cursor (workaround for needing to jiggle the mouse)
			outerCursor = nativeContainer.getCursor();
			nativeContainer.setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));
		} else {
			gp.setVisible(false);
			gp.setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
			// force immediate change of cursor (workaround for needing to jiggle the mouse)
			if(outerCursor!=null){
				nativeContainer.setCursor(outerCursor);
			}
		}
	}

	private JPanel getCenterPane(){
		JPanel centerPanel = new JPanel(new BorderLayout());
		JScrollPane scroller = new JScrollPane(getEditor());
		centerPanel.add("North",createToolbar());
		JSplitPane projectCententPane = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT);
		projectCententPane.add(getProjectTreePane());
		projectCententPane.add(scroller);
		centerPanel.add("Center", projectCententPane);
		return centerPanel;
	}

	protected JScrollPane getProjectTreePane(){
		if(projectTreePane == null){
			projectTreePane = new JScrollPane(projectTree.getProjectTree());
			projectTreePane.setMinimumSize(vpad20);
		}
		return projectTreePane;
	}

	private void initializeMenuFlag(){
		menuFlag_hasDataSeries = false;
		menuFlag_hasPreprocessor = false;
		menuFlag_hasPredictiveModel = false;
		menuFlag_hasBpnModel = false;
		menuFlag_hasAnnModel = false;
		menuFlag_hasRbfnModel = false;
		menuFlag_hasRhoModel = false;
		menuFlag_hasPlsModel = false;
		menuFlag_hasPcaModel = false;
		menuFlag_hasOptimizationModel = false;
		menuFlag_hasLabel = false;
		menuFlag_hasSimulation = false;
		menuFlag_hasOptimization = false;
		menuFlag_hasGenOptimization = false;

	}
	
	private void initializeAction(){		
		allCommands = new Hashtable();
		mainAction  = new MainFrameAction();
		objectLoader = new ObjectLoaderThread(this);

		Action action; 
		
		action = new NewAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new OpenAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new CloseAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new RenameAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new SaveAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new SaveasAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new ExitAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new UndoAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new RedoAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new ReplaceAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new LabelingAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action= new ImportAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action= new ImportG2Action();
		allCommands.put(action.getValue(Action.NAME), action);

		action= new ImportNetAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action= new ExportAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new NewLabelAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new NewDataSeriesAction();
		allCommands.put(action.getValue(Action.NAME), action);
		 
		action = new NewPreprocessorAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new NewPredictModelAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new NewBpnModelAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new NewAnnModelAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new NewRbfnModelAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new NewRhoModelAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new NewPlsModelAction();
		allCommands.put(action.getValue(Action.NAME), action);
		
		action = new NewPcaModelAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new NewOptimizeModelAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new NewSimulationAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new NewOptimizationAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new NewGenOptimizationAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new GotoDataSeriesAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new GotoLabelAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new GotoPreprocessorAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new GotoPredictModelAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new GotoBpnModelAction();
		allCommands.put(action.getValue(Action.NAME), action);
		action = new GotoAnnModelAction();
		allCommands.put(action.getValue(Action.NAME), action);
		action = new GotoRbfnModelAction();
		allCommands.put(action.getValue(Action.NAME), action);
		action = new GotoRhoModelAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new GotoPlsModelAction();
		allCommands.put(action.getValue(Action.NAME), action);
		action = new GotoPcaModelAction();
		allCommands.put(action.getValue(Action.NAME), action);
		
		action = new GotoOptimizeModelAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new GotoSimulationAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new GotoOptimizationAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new GotoGenOptimizationAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new DeleteDataSeriesAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new DeleteLabelAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new DeletePreprocessorAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new DeletePredictModelAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new DeleteBpnModelAction();
		allCommands.put(action.getValue(Action.NAME), action);
		action = new DeleteAnnModelAction();
		allCommands.put(action.getValue(Action.NAME), action);
		action = new DeleteRbfnModelAction();
		allCommands.put(action.getValue(Action.NAME), action);
		action = new DeleteRhoModelAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new DeletePlsModelAction();
		allCommands.put(action.getValue(Action.NAME), action);
		action = new DeletePcaModelAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new DeleteOptimizeModelAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new DeleteSimulationAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new DeleteOptimizationAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new DeleteGenOptimizationAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new SpreadSheetAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new LineChartAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new ProjectmapAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new XYMapAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new HistogramAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new AboutAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new CascadeAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new HorizontalAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new VerticalAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new WindowsAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new CloseWindowsAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new PrintAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new PreferenceAction();
		allCommands.put(action.getValue(Action.NAME), action);

		action = new ConnectG2Action();
		allCommands.put(action.getValue(Action.NAME), action);
		
		action = new DisconnectG2Action();
		allCommands.put(action.getValue(Action.NAME), action);
		
		action = new MemoryAction();
		allCommands.put(action.getValue(Action.NAME), action);
	}

    /**
     * Fetch the list of actions supported by this
     * editor.  It is implemented to return the list
     * of actions supported by the embedded JLayeredPane
     * augmented with the actions defined locally.
     */
	public Action[] getActions() {
		Action[] actions = new Action[defaultActions.size()];
		for(int i=0;i<defaultActions.size();i++){
			actions[i] = (Action)defaultActions.elementAt(i);
		}
		return actions;
	}

    /** 
     * Fetch the editor contained in this panel
     */
    public JLayeredPane getEditor() {
		if(editor == null){
			editor =  new JDesktopPane();     //Changed for 1.2.2 gchen 2.1.2000 
			editor.setOpaque(true);
			editor.setBackground(Color.gray);
		}
		return editor;
    }

	/** 
	 * Return the status of connection to g2. 
	 */
	public boolean isConnectedWithG2(){
		return isConnectedWithG2;
	}

	/** 
	 * Set the status of connection to g2. 
	 */
	public void setConnectedWithG2(boolean flag){
		isConnectedWithG2 = flag;
	}

    /**
     * To shutdown when run as an application.
     */
	@Override
	public void processWindowEvent(WindowEvent e) {
		if(blockButtonAction){
			return;
		}
		if(!(e.getID()==WindowEvent.WINDOW_CLOSING)){
			return;
		}
		if(isConnectedWithG2){
			// stay running, only kill window
			NolMainFrame.this.dispose();	
		} else {	
			if(showYesNoDialog(getNolResourceString(EXITSTUDIO),2)!=1){
				return;
			}
//			if(showYesNoDialog("Exit NeurOn-Line Studio?",2)!=1) return;  
			else{
				System.exit(0);
			}
		}
	} 

    /** Find the hosting frame, for the file-chooser dialog. */
    protected JFrame getFrame() {
		return this;
    }

    /** Find the hosting project. */
    public Project2 getProject() {
		return project;
    }

    /**
     * This is the hook through which all menu items are
     * created.  It registers the result with the menuitem
     * hashtable so that it can be fetched with getMenuItem().
     * @see #getMenuItem
     */
    protected JMenuItem createMenuItem(String cmd) {
		JMenuItem mi = new JMenuItem(getResourceString(cmd + labelSuffix));
        URL url = getResource(cmd + imageSuffix);
		if (url != null) {
			mi.setHorizontalTextPosition(JButton.RIGHT);
			mi.setIcon(new ImageIcon(url));
		}
		String astr = getResourceString(cmd + actionSuffix);
		if (astr == null) {
			astr = cmd;
		}
		mi.setActionCommand(astr);
		menuItems.put(astr, mi);
		return mi;
    }

    /**
     * Fetch the menu item that was created for the given
     * command.
     * @param cmd  Name of the action.
     * @returns item created for the given command or null
     *  if one wasn't created.
     */
    protected JMenuItem getMenuItem(String cmd) {
		return (JMenuItem) menuItems.get(cmd);
    }
    protected JButton getToolbarItem(String cmd) {
		return (JButton) toolbarItems.get(cmd);
    }

    protected Action getAction(String cmd) {
		return (Action) commands.get(cmd);
    }

    public String getResourceString(String nm) {
		String str;
		try {
			str = MAIN_RESOURCES.getString(nm);
		} catch (MissingResourceException mre) {
			str = null;
		}
		return str;
    }

    public String getNolResourceString(String nm) {
		String str;
		try {
			str = nolResources.getString(nm);
		} catch (MissingResourceException mre) {
			str = null;
		}
		return str;
    }

    public URL getResource(String key) {
		String name = getResourceString(key);
		if (name != null) {
			URL url = this.getClass().getResource(name);
			return url;
		}
		return null;
    }

    protected Container getToolbar() {
		return toolbar;
    }

    protected JMenuBar getMenubar() {
		return menubar;
    }

    /**
     * Create a status bar
     */
    protected JPanel createStatusbar() {
		status = new JPanel(new GridLayout());
		progress = new JTextField();
		progress.setText("Ready:");
		progress.setEditable(false);
		status.add(progress);
		return status;
    }

    /**
     * Create the toolbar.  By default this reads the 
     * resource file for the definition of the toolbar.
     */
    protected JPanel createToolbar() {

		JPanel 	tool = new JPanel(new BorderLayout());
		toolbar = new JToolBar();
		toolbar.setFloatable(false);
		toolbar.setAlignmentX(LEFT_ALIGNMENT);
		String[] toolKeys = tokenize(getResourceString("toolbar"));

		for (int i = 0; i < toolKeys.length; i++) {
		    if (toolKeys[i].equals("-")) {
				toolbar.add(Box.createHorizontalStrut(5));
		    } else {
				toolbar.add(createToolbarButton(toolKeys[i]));
			}
		}

		Dimension dim = new Dimension(120,20);
		labelStatus = new JComboBox();
		labelStatus.addActionListener(mainAction);
		labelStatus.setToolTipText(getResourceString(labelComboTip));
		labelStatus.setMinimumSize(dim);
		labelStatus.setPreferredSize(dim); 
		labelStatus.setMaximumSize(dim); 

		URL url = getResource("newlabelImage");
		selectStatus = new JToggleButton(new ImageIcon(url),true){
			@Override
			public float getAlignmentY() { return 0.5f; }
		};
        selectStatus.setMargin(new Insets(1,1,1,1));
		selectStatus.setToolTipText(getResourceString(labelToggleTip));
		url = getResource("unlabelImage");
        selectStatus.setSelectedIcon(new ImageIcon(url));
		selectStatus.setSelected(false);
		selectStatus.addActionListener(mainAction);



		connectionStatus = new JTextField();
		connectionStatus.setMinimumSize(dim);
		connectionStatus.setPreferredSize(dim); 
		connectionStatus.setMaximumSize(dim); 
		connectionStatus.setToolTipText(getResourceString("g2connectionTip"));

		toolbar.add(Box.createHorizontalStrut(20));
		toolbar.add(labelStatus);
		toolbar.add(Box.createHorizontalStrut(5));
		toolbar.add(selectStatus);
		toolbar.add(Box.createHorizontalStrut(5));
		toolbar.add(connectionStatus);
		toolbar.add(Box.createHorizontalGlue());

		tool.add("West",toolbar);
		logoButton = new JButton(defaultLogo){
			@Override
			public float getAlignmentY() { return 0.5f; }
			@Override
			public Dimension getPreferredSize() { return new Dimension(30,24); }
		};
		logoButton.setAlignmentX(RIGHT_ALIGNMENT);
		logoButton.setToolTipText(MAIN_RESOURCES.getString("aboutLabel"));
		logoButton.addActionListener(mainAction);
		tool.add("East",logoButton);

		return tool;
    }

    /**
     * Create a button to go inside of the toolbar.  By default this
     * will load an image resource.  The image filename is relative to
     * the classpath (including the '.' directory if its a part of the
     * classpath), and may either be in a JAR file or a separate file.
     * 
     * @param key The key in the resource file to serve as the basis
     *  of lookups.
     */
    protected JButton createToolbarButton(String key) {
//		System.out.println("createToolbarButton key+imageSuffix="+(key+imageSuffix));
		URL url = getResource(key + imageSuffix);
//		System.out.println("createToolbarButton url="+url);
        JButton b = new JButton(new ImageIcon(url)) {
            @Override
			public float getAlignmentY() { return 0.5f; }
		};
        b.setRequestFocusEnabled(false);
        b.setMargin(new Insets(1,1,1,1));

		String astr = getResourceString(key + actionSuffix);
		if (astr == null) {
		    astr = key;
		}
		b.setActionCommand(astr);
		b.setToolTipText(getTooltip(key));
		toolbarItems.put(astr, b);
        return b;
    }
    
    private String getTooltip(String key){
    	return getResourceString(key + tipSuffix);
    }

    /**
     * Take the given string and chop it up into a series
     * of strings on whitespace boundries.  This is useful
     * for trying to get an array of strings out of the
     * resource file.
     */
    protected String[] tokenize(String input) {
		Vector v = new Vector();
		StringTokenizer t = new StringTokenizer(input);
		String cmd[];

		while (t.hasMoreTokens())
			v.addElement(t.nextToken());
		cmd = new String[v.size()];
		for (int i = 0; i < cmd.length; i++)
			cmd[i] = (String) v.elementAt(i);

		return cmd;
    }

    /**
     * Create the menubar for the app.  By default this pulls the
     * definition of the menu from the associated resource file. 
     */
    protected JMenuBar createMenubar() {
		JMenuItem mi;
		JMenuBar mb = new JMenuBar();
		String[] menuKeys = tokenize(getResourceString("menubar"));
		for (int i = 0; i < menuKeys.length; i++) {
			if(menuKeys[i].equals("window")){
				windowMenu = createMenu(menuKeys[i]);
				if (windowMenu != null) {
					mb.add(windowMenu);
				}
			}else{
				JMenu m = createMenu(menuKeys[i]);
				if (m != null) {
					mb.add(m);
				}
			}
		}
		return mb;
    }

    /**
     * Create a menu for the app.  By default this pulls the
     * definition of the menu from the associated resource file.
     */
    protected JMenu createMenu(String key) {
		String[] itemKeys = tokenize(getResourceString(key));
		JMenu menu = new JMenu(getResourceString(key + "Label"));
		for (int i = 0; i < itemKeys.length; i++) {
//			System.out.println("createmenu itemkey="+itemKeys[i]);
		   if (itemKeys[i].equals("-")) {
			menu.addSeparator();
		    } else {
				String[] subItemKeys = tokenize(getResourceString(itemKeys[i]));
				if(subItemKeys.length == 0){
					JMenuItem mi = createMenuItem(itemKeys[i]);
					menu.add(mi);
				}else{
					JMenu me = createMenu(itemKeys[i]);
					menu.add(me);
				}
		    }
		}
		return menu;
    }

    /**Refresh the menu bar for active menu.*/
	private void refreshMenu(){
		for (Enumeration enu = menuItems.elements() ; enu.hasMoreElements() ;) {
			JMenuItem mi = (JMenuItem)enu.nextElement();
			String astr = mi.getActionCommand();
			Action a = getAction(astr);
			if (a != null) {
				mi.removeActionListener(a);
				mi.addActionListener(a);
				mi.setEnabled(true);
			} else {
				mi.setEnabled(false);
			}
		}	
		refreshMenuDynamicTooltips();
	}

	private void refreshMenuDynamicTooltips(){
		JMenuItem saveActionItem = (JMenuItem) menuItems.get(saveAction);
		if (saveActionItem.isEnabled()){
			saveActionItem.setToolTipText(getTooltip(saveAction));
		} else {
			saveActionItem.setToolTipText(getTooltip(saveAction + "Disabled"));
		}
		JMenuItem saveasActionItem = (JMenuItem) menuItems.get(saveasAction);
		if (saveasActionItem.isEnabled()){
			saveasActionItem.setToolTipText(getTooltip(saveAction));
		} else {
			saveasActionItem.setToolTipText(getTooltip(saveAction + "Disabled"));
		}
		JMenuItem newActionItem = (JMenuItem) menuItems.get(newAction);
		if (menuFlag_hasDataSeries){
			newActionItem.setToolTipText(getTooltip(newAction));
		} else {
			newActionItem.setToolTipText(getTooltip(newAction + "Discard"));
		}
	}
	
    /**Refresh the tool bar for active menu.*/
	private void refreshToolbar(){
		for (Enumeration enu = toolbarItems.elements() ; enu.hasMoreElements() ;) {
			Component Obj = (Component)enu.nextElement();
			if(Obj instanceof JButton){
				JButton b = (JButton) Obj;
				String astr = b.getActionCommand();
				Action a = getAction(astr);
				if (a != null) {
					b.removeActionListener(a);
					b.addActionListener(a);
					b.setEnabled(true);
				} else {
					b.setEnabled(false);
				}
			}
		}	
		refreshToolbarDynamicTooltips();
	}

	private void refreshToolbarDynamicTooltips(){
		JButton saveActionItem = (JButton) toolbarItems.get(saveAction);
		if (saveActionItem.isEnabled()){
			saveActionItem.setToolTipText(getTooltip(saveAction));
		} else {
			saveActionItem.setToolTipText(getTooltip(saveAction + "Disabled"));
		}
		JButton newActionItem = (JButton) toolbarItems.get(newAction);
		if (menuFlag_hasDataSeries){
			newActionItem.setToolTipText(getTooltip(newAction));
		} else {
			newActionItem.setToolTipText(getTooltip(newAction + "Discard"));
		}
	}
	
	public void addWindowMenuItem(NolInternalFrame internalFrame){
		if(!internalFrameStack.contains(internalFrame)){
			internalFrameStack.addElement(internalFrame);
			refreshWindowMenu();
		}	
	}

	private void removeWindowMenuItem(NolInternalFrame internalFrame){
		if(internalFrameStack.contains(internalFrame)){
			internalFrameStack.removeElement(internalFrame);
			refreshWindowMenu();
		}	
	}

	private void refreshWindowMenu(){
		if (windowMenu == null){
			return;
		}
		Vector deletedMenuItem = new Vector();
		Component[] comps = windowMenu.getMenuComponents();  // MK 2/22/99 -- get all at once, don't iterate, the components are constantly changing
		for(int j=0;j<comps.length;j++){
			if(comps[j] instanceof JCheckBoxMenuItem) {
				deletedMenuItem.addElement(comps[j]);
			}
		}
		for(int i=0;i<deletedMenuItem.size();i++){
			JCheckBoxMenuItem me = (JCheckBoxMenuItem)deletedMenuItem.elementAt(i);
			windowMenu.remove(me);
		}
		//System.out.println("menu frame stack size="+windowMenu.getItemCount());
		for(int i=0;i<internalFrameStack.size();i++){
			NolInternalFrame iframe = (NolInternalFrame)internalFrameStack.elementAt(i);
			String frameTitle = iframe.getTitle();
			JCheckBoxMenuItem mi = new JCheckBoxMenuItem(frameTitle);
			mi.addActionListener(mainAction);
			windowMenu.insert(mi,windowMenu.getItemCount()-1);			
			if(iframe.equals(activeInternalFrame)){
				mi.setSelected(true);
			}else{
				mi.setSelected(false);
			}
		}

		if(!internalFrameStack.isEmpty()){
			if(!defaultActions.contains(allCommands.get(cascadeAction))){
				defaultActions.addElement(allCommands.get(cascadeAction));
			}
			if(!defaultActions.contains(allCommands.get(horizontalAction))){
				defaultActions.addElement(allCommands.get(horizontalAction));
			}
			if(!defaultActions.contains(allCommands.get(verticalAction))){
				defaultActions.addElement(allCommands.get(verticalAction));
			}
		}else{
			defaultActions.removeElement(allCommands.get(cascadeAction));
			defaultActions.removeElement(allCommands.get(horizontalAction));
			defaultActions.removeElement(allCommands.get(verticalAction));
		}
		commands.clear();
		Action[] actions = getActions();
		for (int i = 0; i < actions.length; i++) {
			Action a = actions[i];
			commands.put(a.getValue(Action.NAME), a);
		}
		refreshMenu();
	}

	private void modifyDefaultAction(){
		defaultActions.removeAllElements();
		defaultActions.addElement(allCommands.get(openAction));
		defaultActions.addElement(allCommands.get(renameAction));
		defaultActions.addElement(allCommands.get(exitAction));
		defaultActions.addElement(allCommands.get(importAction));
		defaultActions.addElement(allCommands.get(newdataseriesAction));
		defaultActions.addElement(allCommands.get(importNetAction));
		defaultActions.addElement(allCommands.get(aboutAction));
		defaultActions.addElement(allCommands.get(windowsAction));		
		defaultActions.addElement(allCommands.get(closewindowsAction));		
		defaultActions.addElement(allCommands.get(printAction));
		defaultActions.addElement(allCommands.get(preferenceAction));
		defaultActions.addElement(allCommands.get(newAction));
		defaultActions.addElement(allCommands.get(memoryAction));


		if(isConnectedWithG2) { 
			defaultActions.addElement(allCommands.get(importG2Action));
			defaultActions.addElement(allCommands.get(disconnectG2Action));
		}else{
			defaultActions.addElement(allCommands.get(connectG2Action));
		}

		if(menuFlag_hasDataSeries){
			defaultActions.addElement(allCommands.get(closeAction));
			defaultActions.addElement(allCommands.get(newlabelAction));
			defaultActions.addElement(allCommands.get(newpreprocessorAction));
			defaultActions.addElement(allCommands.get(spreadsheetAction));
			defaultActions.addElement(allCommands.get(linechartAction));
			defaultActions.addElement(allCommands.get(saveAction));
			defaultActions.addElement(allCommands.get(saveasAction));
			defaultActions.addElement(allCommands.get(exportAction));
			defaultActions.addElement(allCommands.get(xymapAction));
			defaultActions.addElement(allCommands.get(projectmapAction));
			defaultActions.addElement(allCommands.get(histogramAction));
			defaultActions.addElement(allCommands.get(undoAction));
			defaultActions.addElement(allCommands.get(undoAction));
			defaultActions.addElement(allCommands.get(replaceAction));
			defaultActions.addElement(allCommands.get(gotodataseriesAction));
			defaultActions.addElement(allCommands.get(deletedataseriesAction));
		}

		if(menuFlag_hasPreprocessor){
			defaultActions.addElement(allCommands.get(newpredictmodelAction));
			defaultActions.addElement(allCommands.get(newbpnmodelAction));
			defaultActions.addElement(allCommands.get(newannmodelAction));
			defaultActions.addElement(allCommands.get(newrbfnmodelAction));
			defaultActions.addElement(allCommands.get(newrhomodelAction));
			defaultActions.addElement(allCommands.get(newplsmodelAction));
			defaultActions.addElement(allCommands.get(newpcamodelAction));
			defaultActions.addElement(allCommands.get(newoptimizemodelAction));
			defaultActions.addElement(allCommands.get(gotopreprocessorAction));
			defaultActions.addElement(allCommands.get(deletepreprocessorAction));
		}

		if(menuFlag_hasPredictiveModel ){			
			defaultActions.addElement(allCommands.get(gotopredictmodelAction));
			defaultActions.addElement(allCommands.get(deletepredictmodelAction));
			defaultActions.addElement(allCommands.get(newsimulationAction));
			defaultActions.addElement(allCommands.get(newgenoptimizationAction));
		}

		if(menuFlag_hasBpnModel ){			
			defaultActions.addElement(allCommands.get(gotobpnmodelAction));
			defaultActions.addElement(allCommands.get(deletebpnmodelAction));
			defaultActions.addElement(allCommands.get(newsimulationAction));
		}

		if(menuFlag_hasAnnModel){
			defaultActions.addElement(allCommands.get(newsimulationAction));
			defaultActions.addElement(allCommands.get(gotoannmodelAction));
			defaultActions.addElement(allCommands.get(deleteannmodelAction));
		}

		if(menuFlag_hasRbfnModel){
			defaultActions.addElement(allCommands.get(newsimulationAction));
			defaultActions.addElement(allCommands.get(gotorbfnmodelAction));
			defaultActions.addElement(allCommands.get(deleterbfnmodelAction));
		}

		if(menuFlag_hasRhoModel){
			defaultActions.addElement(allCommands.get(gotorhomodelAction));
			defaultActions.addElement(allCommands.get(deleterhomodelAction));
		}

		if(menuFlag_hasPlsModel){
			defaultActions.addElement(allCommands.get(gotoplsmodelAction));
			defaultActions.addElement(allCommands.get(deleteplsmodelAction));
		}

		if(menuFlag_hasPcaModel){
			defaultActions.addElement(allCommands.get(gotopcamodelAction));
			defaultActions.addElement(allCommands.get(deletepcamodelAction));
		}

		if(menuFlag_hasOptimizationModel){
			defaultActions.addElement(allCommands.get(newsimulationAction));
			defaultActions.addElement(allCommands.get(newoptimizationAction));
			defaultActions.addElement(allCommands.get(gotooptimizemodelAction));
			defaultActions.addElement(allCommands.get(deleteoptimizemodelAction));
		}

		if(menuFlag_hasLabel){
			defaultActions.addElement(allCommands.get(gotolabelAction));
			defaultActions.addElement(allCommands.get(deletelabelAction));
		}
		
		if(menuFlag_hasLabel && menuFlag_hasDataSeries){
			defaultActions.addElement(allCommands.get(labelingAction));
		}
		
		if(menuFlag_hasSimulation){
			defaultActions.addElement(allCommands.get(gotosimulationAction));
			defaultActions.addElement(allCommands.get(deletesimulationAction));
		}
		if(menuFlag_hasOptimization){
			defaultActions.addElement(allCommands.get(gotooptimizationAction));
			defaultActions.addElement(allCommands.get(deleteoptimizationAction));
		}
		
		if(menuFlag_hasGenOptimization){
			defaultActions.addElement(allCommands.get(gotogenoptimizationAction));
			defaultActions.addElement(allCommands.get(deletegenoptimizationAction));
		}
		
		commands.clear();
		Action[] actions = getActions();
//System.out.println("actions.length="+actions.length);
		for (int i = 0; i < actions.length; i++) {
		    Action a = actions[i];
		    commands.put(a.getValue(Action.NAME), a);
		}
		refreshMenu();
		refreshToolbar();
	}
					   
	/** Get the projectTree.*/
	public ProjectTree getProjectTree(){
		return projectTree;
	}


	public void printComponent(NolInternalFrame component) {
		RepaintManager.currentManager(component).setDoubleBufferingEnabled(false);

		//Changed for 1.2.2 gchen 2.2.2000
		PrinterJob printJob = PrinterJob.getPrinterJob();
		printJob.setPageable(component);
		if (printJob.printDialog()) {
			try {
			printJob.print();
			} catch(PrinterException ex){
				ex.printStackTrace();
			}
		}


/*		PrintJob printJob = component.getToolkit().getPrintJob(this, 
									   "Printing Active Window", 
										null);
		if (printJob != null) {
			Graphics graphics = printJob.getGraphics();
			if (graphics != null) {
				component.print(graphics);
				graphics.dispose();
			}
			printJob.end();
		}
*/
		RepaintManager.currentManager(component).setDoubleBufferingEnabled(true);
	}

	/** Create or get the NolDataSeriesInputWizard. */
	private NolDataSeriesInputWizard getInputWizard(){
		if(dataSeriesInputWizard == null){			
			JFrame frame = getFrame();		
			dataSeriesInputWizard = new NolDataSeriesInputWizard(frame,"Import Data Series");
			dataSeriesInputWizard.setBounds(0,0,650,400);
		}
		return dataSeriesInputWizard;
	}

	/** Create or get the NolNewLabelWizard.*/ 
	private NolNewLabelWizard getNewLabelWizard(){
		if(newLabelWizard == null){			
			JFrame frame = getFrame();		
			newLabelWizard = new NolNewLabelWizard(frame,"Create New Label");
			newLabelWizard.setBounds(200,100,380,350);
		}
		return newLabelWizard;
	}

	/** Create or get the NolNewPreprocessorWizard. */
	private NolNewPreprocessorWizard getNewPreprocessorWizard(){
		if(newPreprocessorWizard == null){			
			JFrame frame = getFrame();		
			newPreprocessorWizard = new NolNewPreprocessorWizard(frame);
		}
		return newPreprocessorWizard;
	}

	/** Create or get the NolNewPredictiveModelWizard. */
	private NolNewPredictiveModelWizard getNewPredictiveModelWizard(){
		if(newPredictiveModelWizard == null){			
			newPredictiveModelWizard = new NolNewPredictiveModelWizard(this);
		}
		return newPredictiveModelWizard;
	}

	/** Create or get the NolNewBpnModelWizard. */
	private NolNewBpnModelWizard getNewBpnModelWizard(){
		if(newBpnModelWizard == null){			
			newBpnModelWizard = new NolNewBpnModelWizard(this);
		}
		return newBpnModelWizard;
	}
	
	/** Create or get the NolNewAnnModelWizard. */
	private NolNewAnnModelWizard getNewAnnModelWizard(){
		if(newAnnModelWizard == null){			
			newAnnModelWizard = new NolNewAnnModelWizard(this);
		}
		return newAnnModelWizard;
	}

	/** Create or get the NolNewRbfnModelWizard. */
	private NolNewRbfnModelWizard getNewRbfnModelWizard(){
		if(newRbfnModelWizard == null){			
			newRbfnModelWizard = new NolNewRbfnModelWizard(this);
		}
		return newRbfnModelWizard;
	}

	/** Create or get the NolNewRhoModelWizard. */
	private NolNewRhoModelWizard getNewRhoModelWizard(){
		if(newRhoModelWizard == null){			
			newRhoModelWizard = new NolNewRhoModelWizard(this);
		}
		return newRhoModelWizard;
	}

	/** Create or get the NolNewPlsModelWizard. */
	private NolNewPlsModelWizard getNewPlsModelWizard(){
		if(newPlsModelWizard == null){			
			newPlsModelWizard = new NolNewPlsModelWizard(this);
		}
		return newPlsModelWizard;
	}


	/** Create or get the NolNewPcaModelWizard. */
	private NolNewPcaModelWizard getNewPcaModelWizard(){
		if(newPcaModelWizard == null){			
			newPcaModelWizard = new NolNewPcaModelWizard(this);
		}
		return newPcaModelWizard;
	}


	/** Create or get the NolNewOptimizeModelWizard.  */
	private NolNewOptimizeModelWizard getNewOptimizeModelWizard(){
		if(newOptimizeModelWizard == null){			
			newOptimizeModelWizard = new NolNewOptimizeModelWizard(this);
		}
		return newOptimizeModelWizard;
	}

	/** Create or get the NolNewSimulationWizard.*/ 
	private NolNewSimulationWizard getNewSimulationWizard(){
		if(newSimulationWizard == null){			
			newSimulationWizard = new NolNewSimulationWizard(this);
		}
		return newSimulationWizard;
	}

	/* Create or get the NolNewObjectiveWizard.
	private NolNewObjectiveWizard getNewObjectiveWizard(){
		if(newObjectiveWizard == null){			
			newObjectiveWizard = new NolNewObjectiveWizard(this);
		}
		return newObjectiveWizard;
	}
	  */
	/** Create or get the NolNewOptimizationWizard.*/ 
	private NolNewOptimizationWizard getNewOptimizationWizard(){
		if(newOptimizationWizard == null){			
			newOptimizationWizard = new NolNewOptimizationWizard(this);
		}
		return newOptimizationWizard;
	}
	
	/** Create or get the NolNewGenOptimizationWizard.*/ 
	private NolNewGenOptimizationWizard getNewGenOptimizationWizard(){
		if(newGenOptimizationWizard == null){			
			newGenOptimizationWizard = new NolNewGenOptimizationWizard(this);
		}
		return newGenOptimizationWizard;
	}
	
	public void showOKDialog(String text) {
		NolConfirmDialog dialog = getConfirmDialog();
		String[] buttonLabels = {getNolResourceString(OK)};
		dialog.setContent("Information Dialog", buttonLabels, text,"info.gif");
		dialog.setFocus(1);
		dialog.setVisible(true);
	}

	public int showYesNoDialog(String text, int focus) {
		NolConfirmDialog dialog = getConfirmDialog();
		String[] buttonLabels = {getNolResourceString(YES),getNolResourceString(NO)};
		dialog.setContent("Question Dialog", buttonLabels, text,"question.gif");
		dialog.setFocus(focus);
		dialog.setVisible(true);
		return dialog.getResult();
	}

	public int showYesNoCancelDialog(String text, int focus) {
		NolConfirmDialog dialog = getConfirmDialog();
		String[] buttonLabels = {getNolResourceString(YES),getNolResourceString(NO),getNolResourceString(CANCEL)};
		dialog.setContent("Question Dialog", buttonLabels, text,"question.gif");
		dialog.setFocus(focus);
		dialog.setVisible(true);
		return dialog.getResult();
	}

	public int showCustomDialog(String title, String text, String[] buttonLabels, String gif, int focus) {
		NolConfirmDialog dialog = getConfirmDialog();
		dialog.setContent(title, buttonLabels, text, gif);
		dialog.setFocus(focus);
		dialog.setVisible(true);
		return dialog.getResult();
	}

	/** Create or get the NolConfirmDialog. */
	private NolConfirmDialog getConfirmDialog() {
		if(confirmDialog == null){
			JFrame frame = getFrame();
			String label = "Question?";
			String[] buttonLabels = {getNolResourceString(YES),getNolResourceString(NO)};
			confirmDialog = new NolConfirmDialog(frame,"Confirmation Dialog",buttonLabels,label,"question.gif");
		}
		return confirmDialog;
	}


	/** Create or get the NolChoiceDialog. */
	private NolXYChoiceDialog getXYChoiceDialog(){  // modified by bbush, 10-1-98
		if(xyChoiceDialog == null){
			JFrame frame = getFrame();
			xyChoiceDialog = new NolXYChoiceDialog
				(frame,"Select Dialog","Choice 1:", "Choice 2:", "Choice 3:", 
				new Vector(),new Vector(), new Vector(), 
				new Vector(),new Vector(), new Vector(), 
				false);
		}
		return xyChoiceDialog;
	}

	/** Create or get the NolChoiceDialog. */
	private NolTripleChoiceDialog getTripleChoiceDialog(){  // modified by bbush, 10-1-98
		if(tripleChoiceDialog == null){
			JFrame frame = getFrame();
			tripleChoiceDialog = new NolTripleChoiceDialog
				(frame,"Select Dialog","Choice 1:", "Choice 2:", "Choice 3:", new Vector(),
			new Vector(), new Vector(), false);
		}
		return tripleChoiceDialog;
	}

	/** Create or get the NolDoubleChoiceDialog. */
	private NolDoubleChoiceDialog getDoubleChoiceDialog(){  // modified by bbush, 10-1-98
		if(doubleChoiceDialog == null){
			JFrame frame = getFrame();
			doubleChoiceDialog = new NolDoubleChoiceDialog
				(frame,"Select Dialog","Choice 1:", "Choice 2:", new Vector(),
			new Vector(), false);
		}
		return doubleChoiceDialog;
	}

	/** Create or get the NolChoiceDialog. */
	private NolSingleChoiceDialog getSingleChoiceDialog(){  // modified by bbush, 10-1-98
		if(singleChoiceDialog == null){
			JFrame frame = getFrame();
			singleChoiceDialog = new NolSingleChoiceDialog
				(frame,"Select Dialog","Choice 1:", new Vector(), false);
		}
		return singleChoiceDialog;
	}

	/** Create or get the NolWindowsChoiceDialog. */
	private NolWindowsChoiceDialog getWindowsChoiceDialog(){  
		if(windowsChoiceDialog == null){
			JFrame frame = getFrame();
			windowsChoiceDialog = new NolWindowsChoiceDialog
				(frame, new Vector(), false);
		}
		return windowsChoiceDialog;
	}

	/** Create or get the NolTrainDialog.*/ 
	public NolTrainDialog getTrainDialog(){
		if(trainDialog == null){
			JFrame frame = getFrame();
			trainDialog = new NolTrainDialog(frame,"Train A Model");
			trainDialog.setBounds(200,100,370,350);
		}
		return trainDialog;
	}

	/** Create or get the NolBpnTrainDialog.*/ 
	public NolBpnTrainDialog getBpnTrainDialog(){
		if(bpnTrainDialog == null){
			JFrame frame = getFrame();
			bpnTrainDialog = new NolBpnTrainDialog(frame,"Train A Model");
			bpnTrainDialog.setBounds(200,100,420,350);
		}
		return bpnTrainDialog;
	}

	/** Create or get the NolRbfnTrainDialog.*/ 
	public NolRbfnTrainDialog getRbfnTrainDialog(){
		if(rbfnTrainDialog == null){
			JFrame frame = getFrame();
			rbfnTrainDialog = new NolRbfnTrainDialog(frame,"Train A Model");
			rbfnTrainDialog.setBounds(200,100,370,250);
		}
		return rbfnTrainDialog;
	}

	/** Create or get the NolRhoTrainDialog.*/ 
	public NolRhoTrainDialog getRhoTrainDialog(){
		if(rhoTrainDialog == null){
			JFrame frame = getFrame();
			rhoTrainDialog = new NolRhoTrainDialog(frame,"Train A Model");
			rhoTrainDialog.setBounds(200,100,370,250);
		}
		return rhoTrainDialog;
	}

  	/** Create or get the NolReplaceDialog. */
	private NolReplaceDialog getReplaceDialog(){
		if(replaceDialog == null){			
			JFrame frame = getFrame();		
			replaceDialog = new NolReplaceDialog(frame,"Search & Replace");
		}
		return replaceDialog;
	}

  	/** Create or get the NolPreferenceDialog. */
	private NolPreferenceDialog getPreferenceDialog(){
		if(preferenceDialog == null){			
			JFrame frame = getFrame();		
			preferenceDialog = new NolPreferenceDialog(frame,"Preferences");
		}
		return preferenceDialog;
	}

  	/** Create or get the NolConnectG2Dialog. */
	private NolConnectG2Dialog getConnectG2Dialog(){
		if(connectG2Dialog == null){			
			JFrame frame = getFrame();		
			connectG2Dialog = new NolConnectG2Dialog(frame,"Connect G2");
		}
		return connectG2Dialog;
	}

  	/** Create or get the NolModelValidateChoiceDialog. */
	private NolModelValidateChoiceDialog getModelValidateChoiceDialog(){
		if(modelValidateChoiceDialog == null){			
			JFrame frame = getFrame();		
			modelValidateChoiceDialog = new NolModelValidateChoiceDialog(frame,"Choose the validation data series");
		}
		return modelValidateChoiceDialog;
	}

  	/** Create or get the NolURLImportDialog. */
	private NolURLImportDialog getURLImportDialog(){
		if(URLImportDialog == null){			
			String[] buttonLabels = {"Load","Cancel"};
			URLImportDialog = new NolURLImportDialog((JFrame)this, "Load File From URL",
			buttonLabels, "URL:","import2.gif");
		}
		return URLImportDialog;
	}

	/** Create or get the NolAboutDialog.  */
	private NolAboutDialog getAboutDialog(){
		if(aboutDialog==null){
			JFrame frame = getFrame();
			aboutDialog= new NolAboutDialog(frame,"About Gensym NeurOn-Line");
		}
		return aboutDialog;
	}

/** Propagate the changing of the data series name.*/
	public void changeDataSeriesName(DataSeries ds){
		int n = internalFrameStack.size();
		boolean inUse = false;
		for(int i=0;i<n;i++){
			NolInternalFrame iframe = (NolInternalFrame)internalFrameStack.elementAt(i);
			if(iframe instanceof NolVariableWKSP ){
				Variable varObj0 = ((NolVariableWKSP)iframe).getVariable();	
				if(varObj0.getDataSeries().getName().equals(ds.getName())){
					((NolVariableWKSP)iframe).refreshTitle();
				}
			}else if(iframe instanceof NolDataSeriesWKSP ){
				DataSeries oldDs = ((NolDataSeriesWKSP)iframe).getDataSeries();
				if(oldDs.getName().equals(ds.getName())) {
					((NolDataSeriesWKSP)iframe).refreshNameField();
				}
			}else if(iframe instanceof NolSpreadsheet ){
				DataSeries oldDs = ((NolSpreadsheet)iframe).getDataSeries();
				if(oldDs.getName().equals(ds.getName())) {
					((NolSpreadsheet)iframe).refreshTitle();
				}
			}else if(iframe instanceof NolProjectionChartFrame ){
				((NolProjectionChartFrame)iframe).refreshDataSeriesName(ds);	
			}else if(iframe instanceof NolXYChartFrame ){
				((NolXYChartFrame)iframe).refreshDataSeriesName(ds);	
			}else if(iframe instanceof NolVarChartFrame ){
				((NolVarChartFrame)iframe).refreshDataSeriesName(ds);	
			}else if(iframe instanceof NolHistogramFrame ){
				((NolHistogramFrame)iframe).refreshDataSeriesName(ds);	
			}
		}
		projectTree.changeDataSeriesName(ds,true); //Gchen 10.1 This should go throught the raw data event
	}

/** Show the data series workspace given the data series.*/
	public void showDataSeriesWKSP(DataSeries ds){		
		if(activeInternalFrame == null) {
		    activeInternalFrame = new NolDataSeriesWKSP(this,ds);
		    activeInternalFrame.setClosable(true);
		    activeInternalFrame.setMaximizable(false);
		    activeInternalFrame.setIconifiable(true);
			activeInternalFrame.setResizable(true);
			interCount++;
			activeInternalFrame.setBounds(20*interCount, 20*interCount, 600, 420);
			if(interCount > 10)
                interCount = 0;
		    getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER);  	
		}else{
			JLayeredPane pane = getEditor();
			Component[] internalFrames = pane.getComponentsInLayer(JLayeredPane.DEFAULT_LAYER.intValue());
			boolean found = false;
			for(int i=0;i<internalFrames.length;i++){
				if(internalFrames[i] instanceof NolDataSeriesWKSP ){
					DataSeries oldDs = ((NolDataSeriesWKSP)internalFrames[i]).getDataSeries();
					if(oldDs.equals(ds)){
						activeInternalFrame = (NolDataSeriesWKSP)internalFrames[i];
						found = true;
						break;
					}
				}
			}		
			if(!found){
				activeInternalFrame = new NolDataSeriesWKSP(this,ds);
				activeInternalFrame.setClosable(true);
				activeInternalFrame.setMaximizable(false);
				activeInternalFrame.setIconifiable(true);
				activeInternalFrame.setResizable(true);
				interCount++;
				activeInternalFrame.setBounds(20*interCount, 20*interCount, 600,420);
				if(interCount > 10)
					interCount = 0;
				getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER); 
			}
		}
        try { 
			activeInternalFrame.setSelected(true); 
		} catch (java.beans.PropertyVetoException e2) {
			System.err.println("Non-Fatal exception: " + e2.getMessage());
			e2.printStackTrace();
		}
        getEditor().moveToFront(activeInternalFrame);
		activeInternalFrame.validate();
		activeInternalFrame.removeInternalFrameListener(mainAction);
		activeInternalFrame.addInternalFrameListener(mainAction);
		addWindowMenuItem(activeInternalFrame);
		progress.setText("Ready:");
		progress.validate();
		progress.repaint(0l);
	}

 /** Show the data series workspace given the data series.*/
	public void showVariableStatistics(DataSeries ds){		
		if(activeInternalFrame == null) {
		    activeInternalFrame = new NolVariableStatisticsWKSP(this,ds);
		    activeInternalFrame.setClosable(true);
		    activeInternalFrame.setMaximizable(false);
		    activeInternalFrame.setIconifiable(true);
			activeInternalFrame.setResizable(true);
			interCount++;
			activeInternalFrame.setBounds(20*interCount, 20*interCount, 600, 400);
			if(interCount > 10)
                interCount = 0;
		    getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER);  	
		}else{
			JLayeredPane pane = getEditor();
			Component[] internalFrames = pane.getComponentsInLayer(JLayeredPane.DEFAULT_LAYER.intValue());
			boolean found = false;
			for(int i=0;i<internalFrames.length;i++){
				if(internalFrames[i] instanceof NolVariableStatisticsWKSP ){
					DataSeries oldDs = ((NolVariableStatisticsWKSP)internalFrames[i]).getDataSeries();
					if(oldDs.equals(ds)){
						activeInternalFrame = (NolVariableStatisticsWKSP)internalFrames[i];
						found = true;
						break;
					}
				}
			}		
			if(!found){
				activeInternalFrame = new NolVariableStatisticsWKSP(this,ds);
				activeInternalFrame.setClosable(true);
				activeInternalFrame.setMaximizable(false);
				activeInternalFrame.setIconifiable(true);
				activeInternalFrame.setResizable(true);
				interCount++;
				activeInternalFrame.setBounds(20*interCount, 20*interCount, 600,400);
				if(interCount > 10)
					interCount = 0;
				getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER); 
			}
		}
        try { 
			activeInternalFrame.setSelected(true); 
		} catch (java.beans.PropertyVetoException e2) {
			System.err.println("Non-Fatal exception: " + e2.getMessage());
			e2.printStackTrace();
		}
        getEditor().moveToFront(activeInternalFrame);
		activeInternalFrame.validate();
		activeInternalFrame.removeInternalFrameListener(mainAction);
		activeInternalFrame.addInternalFrameListener(mainAction);
		addWindowMenuItem(activeInternalFrame);
		progress.setText("Ready:");
		progress.validate();
		progress.repaint(0l);
	}


/** Propagate the changing of the variable name.*/
	public void changeVariableName(Variable varObj){
		int n = internalFrameStack.size();
		boolean inUse = false;
		for(int i=0;i<n;i++){
			NolInternalFrame iframe = (NolInternalFrame)internalFrameStack.elementAt(i);
			if(iframe instanceof NolDataSeriesWKSP ){
				DataSeries oldDs = ((NolDataSeriesWKSP)iframe).getDataSeries();
				if(oldDs.getVarObjects().contains(varObj)) {
					((NolDataSeriesWKSP)iframe).refreshVarTable();
				}
			}else if(iframe instanceof NolSpreadsheet ){
				DataSeries oldDs = ((NolSpreadsheet)iframe).getDataSeries();
				if(oldDs.getVarObjects().contains(varObj)) {
					((NolSpreadsheet)iframe).refreshTitle();
				}
			}else if(iframe instanceof NolProjectionChartFrame ){
				((NolProjectionChartFrame)iframe).refreshVariableName(varObj);	
			}else if(iframe instanceof NolXYChartFrame ){
				((NolXYChartFrame)iframe).refreshVariableName(varObj);	
			}else if(iframe instanceof NolVarChartFrame ){
				((NolVarChartFrame)iframe).refreshVariableName(varObj);	
			}else if(iframe instanceof NolHistogramFrame ){
				((NolHistogramFrame)iframe).refreshVariableName(varObj);	
			}
		}
	}
	public void showVariableWKSP(Variable varObj){		
		if(activeInternalFrame == null) {
		    activeInternalFrame = new NolVariableWKSP(this,varObj);
		    activeInternalFrame.setClosable(true);
		    activeInternalFrame.setMaximizable(false);
		    activeInternalFrame.setIconifiable(true);
			activeInternalFrame.setResizable(true);
			interCount++;
			activeInternalFrame.setBounds(20*interCount, 20*interCount, 500, 300);
			if(interCount > 10)
                interCount = 0;
		    getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER);  	
		}else{
			JLayeredPane pane = getEditor();
			Component[] internalFrames = pane.getComponentsInLayer(JLayeredPane.DEFAULT_LAYER.intValue());
			boolean found = false;
			for(int i=0;i<internalFrames.length;i++){
				if(internalFrames[i] instanceof NolVariableWKSP ){
					Variable varObj0 = ((NolVariableWKSP)internalFrames[i]).
						getVariable();	
					if(varObj0.equals(varObj)){
						activeInternalFrame = (NolVariableWKSP)internalFrames[i];
						found = true;
						break;
					}
				}
			}
			if(!found){
				activeInternalFrame = new NolVariableWKSP(this,varObj);
				activeInternalFrame.setClosable(true);
				activeInternalFrame.setMaximizable(false);
				activeInternalFrame.setIconifiable(true);
				activeInternalFrame.setResizable(true);
				interCount++;
				activeInternalFrame.setBounds(20*interCount, 20*interCount, 500, 300);
				if(interCount > 10)
					interCount = 0;
				getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER); 
			}
		}
        try { 
			activeInternalFrame.setSelected(true); 
		} catch (java.beans.PropertyVetoException e2) {
			System.err.println("Non-Fatal exception: " + e2.getMessage());
			e2.printStackTrace();
		}
        getEditor().moveToFront(activeInternalFrame);
		activeInternalFrame.validate();
		activeInternalFrame.removeInternalFrameListener(mainAction);
		activeInternalFrame.addInternalFrameListener(mainAction);
		addWindowMenuItem(activeInternalFrame);
		progress.setText("Ready:");
		progress.validate();
		progress.repaint(0l);
	}

/** Show the foramt workspace given the format.*/
	public void showFileFormatWKSP(DataSeriesFileFormat ft){		
		if(activeInternalFrame == null) {
		    activeInternalFrame = new NolFileFormatWKSP(this,ft);
		    activeInternalFrame.setClosable(true);
		    activeInternalFrame.setMaximizable(false);
		    activeInternalFrame.setIconifiable(true);
			activeInternalFrame.setResizable(true);
			interCount++;
			activeInternalFrame.setBounds(20*interCount, 20*interCount, 430, 350);
			if(interCount > 10)
                interCount = 0;
		    getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER);  	
		}else{
			JLayeredPane pane = getEditor();
			Component[] internalFrames = pane.getComponentsInLayer(JLayeredPane.DEFAULT_LAYER.intValue());
			boolean found = false;
			for(int i=0;i<internalFrames.length;i++){
				if(internalFrames[i] instanceof NolFileFormatWKSP ){
					DataSeriesFileFormat ft1 = ((NolFileFormatWKSP)internalFrames[i]).getDataFormat();
					if(ft1.equals(ft)){
						activeInternalFrame = (NolFileFormatWKSP)internalFrames[i];
						found = true;
						break;
					}
				}
			}		
			if(!found){
				activeInternalFrame = new NolFileFormatWKSP(this,ft);
				activeInternalFrame.setClosable(true);
				activeInternalFrame.setMaximizable(false);
				activeInternalFrame.setIconifiable(true);
				activeInternalFrame.setResizable(true);
				interCount++;
				activeInternalFrame.setBounds(20*interCount, 20*interCount, 430,350);
				if(interCount > 10)
					interCount = 0;
				getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER); 
			}
		}
        try { 
			activeInternalFrame.setSelected(true); 
		} catch (java.beans.PropertyVetoException e2) {
			System.err.println("Non-Fatal exception: " + e2.getMessage());
			e2.printStackTrace();
		}
        getEditor().moveToFront(activeInternalFrame);
		activeInternalFrame.validate();
		activeInternalFrame.removeInternalFrameListener(mainAction);
		activeInternalFrame.addInternalFrameListener(mainAction);
		addWindowMenuItem(activeInternalFrame);
		progress.setText("Ready:");
		progress.validate();
		progress.repaint(0l);
	}

/** Show the data series workspace given the data series.*/
	public void showLabelWKSP(NolLabel lab){
		if(activeInternalFrame == null) {
		    activeInternalFrame = new NolLabelWKSP(this,lab);
		    activeInternalFrame.setClosable(true);
		    activeInternalFrame.setMaximizable(false);
		    activeInternalFrame.setIconifiable(true);
			activeInternalFrame.setResizable(true);
			interCount++;
			activeInternalFrame.setBounds(20*interCount, 20*interCount, 300, 200);
			if(interCount > 10)
                interCount = 0;
		    getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER);  	
		}else{
			JLayeredPane pane = getEditor();
			Component[] internalFrames = pane.getComponentsInLayer(JLayeredPane.DEFAULT_LAYER.intValue());
			boolean found = false;
			for(int i=0;i<internalFrames.length;i++){
				if(internalFrames[i] instanceof NolLabelWKSP ){
					NolLabel lab0 = ((NolLabelWKSP)internalFrames[i]).
						getLabel();
					if( lab0.equals(lab)){
						activeInternalFrame = (NolLabelWKSP)internalFrames[i];
						found = true;
						break;
					}
				}
			}
			if(!found){
				activeInternalFrame = new NolLabelWKSP(this,lab);
				activeInternalFrame.setClosable(true);
				activeInternalFrame.setMaximizable(false);
				activeInternalFrame.setIconifiable(true);
				activeInternalFrame.setResizable(true);
				interCount++;
				activeInternalFrame.setBounds(20*interCount, 20*interCount, 300, 200);
				if(interCount > 10)
					interCount = 0;
				getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER); 
			}
		}
        try { 
			activeInternalFrame.setSelected(true); 
		} catch (java.beans.PropertyVetoException e2) {
			System.err.println("Non-Fatal exception: " + e2.getMessage());
			e2.printStackTrace();
		}
        getEditor().moveToFront(activeInternalFrame);
		activeInternalFrame.validate();
		activeInternalFrame.removeInternalFrameListener(mainAction);
		activeInternalFrame.addInternalFrameListener(mainAction);
		addWindowMenuItem(activeInternalFrame);
		progress.setText("Ready:");
		progress.validate();
		progress.repaint(0l);
	}

	public void showPreprocessorWKSP(Preprocessor prep){
		
		if(activeInternalFrame == null) {
		    activeInternalFrame = new NolPreprocessorWKSP(this,prep);
		    activeInternalFrame.setClosable(true);
		    activeInternalFrame.setMaximizable(false);
		    activeInternalFrame.setIconifiable(true);
			activeInternalFrame.setResizable(true);
			interCount++;
			activeInternalFrame.setBounds(20*interCount, 20*interCount, 550, 350);
			if(interCount > 10)
                interCount = 0;
		    getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER);  	
		}else{
			JLayeredPane pane = getEditor();
			Component[] internalFrames = pane.getComponentsInLayer(JLayeredPane.DEFAULT_LAYER.intValue());
			boolean found = false;
			for(int i=0;i<internalFrames.length;i++){
				if(internalFrames[i] instanceof NolPreprocessorWKSP ){
					Preprocessor prep0 = ((NolPreprocessorWKSP)internalFrames[i]).
						getPreprocessor();
					if(prep.equals(prep0)){
						activeInternalFrame = (NolPreprocessorWKSP)internalFrames[i];
						found = true;
						break;
					}
				}
			}
			if(!found){
				activeInternalFrame = new NolPreprocessorWKSP(this,prep);
				activeInternalFrame.setClosable(true);
				activeInternalFrame.setMaximizable(false);
				activeInternalFrame.setIconifiable(true);
				activeInternalFrame.setResizable(true);
				interCount++;
				activeInternalFrame.setBounds(20*interCount, 20*interCount, 550,350);
				if(interCount > 10)
					interCount = 0;
				getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER); 
			}
		}
        try { 
			activeInternalFrame.setSelected(true); 
		} catch (java.beans.PropertyVetoException e2) {
			System.err.println("Non-Fatal exception: " + e2.getMessage());
			e2.printStackTrace();
		}
        getEditor().moveToFront(activeInternalFrame);
		activeInternalFrame.validate();
		activeInternalFrame.removeInternalFrameListener(mainAction);
		activeInternalFrame.addInternalFrameListener(mainAction);
		addWindowMenuItem(activeInternalFrame);
		progress.setText("Ready:");
		progress.validate();
		progress.repaint(0l);
	}

	public void showClassicModelPredVsActWKSP(NolModel2 model){

		progress.setText("Status: Calculating predicted versus actual");
		if(activeInternalFrame == null) {
			activeInternalFrame = new NolClassicModelPredVsActWKSP(this,model);
		    activeInternalFrame.setClosable(true);
		    activeInternalFrame.setMaximizable(false);
		    activeInternalFrame.setIconifiable(true);
			activeInternalFrame.setResizable(true);
			interCount++;
			activeInternalFrame.setBounds(20*interCount, 20*interCount, 650, 550);
			if(interCount > 10)
                interCount = 0;
		    getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER);  	
		}else{
			JLayeredPane pane = getEditor();
			Component[] internalFrames = pane.getComponentsInLayer(JLayeredPane.DEFAULT_LAYER.intValue());
			boolean found = false;
			for(int i=0;i<internalFrames.length;i++){
				if(internalFrames[i] instanceof NolClassicModelPredVsActWKSP ){
					NolModel2 model1 = ((NolClassicModelPredVsActWKSP)internalFrames[i]).getModel();
					if(model1.equals(model)){
						activeInternalFrame = (NolClassicModelPredVsActWKSP)internalFrames[i];
						found = true;
						break;
					}
				}
			}
			if(!found){
				activeInternalFrame = new NolClassicModelPredVsActWKSP(this,model);
				activeInternalFrame.setClosable(true);
				activeInternalFrame.setMaximizable(false);
				activeInternalFrame.setIconifiable(true);
				activeInternalFrame.setResizable(true);
				interCount++;
				activeInternalFrame.setBounds(20*interCount, 20*interCount, 650,550);
				if(interCount > 10){
					interCount = 0;
				}
				getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER); 
			}
		}
        try { 
			activeInternalFrame.setSelected(true); 
		} catch (java.beans.PropertyVetoException e2) {
			System.err.println("Non-Fatal exception: " + e2.getMessage());
			e2.printStackTrace();
		}
        getEditor().moveToFront(activeInternalFrame);
		activeInternalFrame.validate();
		activeInternalFrame.setBounds(20*interCount, 20*interCount, 651,550);
		activeInternalFrame.validate();									
		activeInternalFrame.repaint(0l);
		activeInternalFrame.setBounds(20*interCount, 20*interCount,650,550);
		activeInternalFrame.validate();
		activeInternalFrame.repaint(0l);
		activeInternalFrame.removeInternalFrameListener(mainAction);
		activeInternalFrame.addInternalFrameListener(mainAction);
		addWindowMenuItem(activeInternalFrame);
		progress.setText("Ready:");
		progress.validate();
		progress.repaint(0l);

	}

	public void showModelPredVsActWKSP(NolModel2 model){
		progress.setText("Status: Calculating predicted versus actual");
		if(activeInternalFrame == null) {
			activeInternalFrame = new NolModelPredVsActWKSP(this,model);
		    activeInternalFrame.setClosable(true);
		    activeInternalFrame.setMaximizable(false);
		    activeInternalFrame.setIconifiable(true);
			activeInternalFrame.setResizable(true);
			interCount++;
			activeInternalFrame.setBounds(20*interCount, 20*interCount, 700, 590);
			if(interCount > 10)
                interCount = 0;
		    getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER);  	
		}else{
			JLayeredPane pane = getEditor();
			Component[] internalFrames = pane.getComponentsInLayer(JLayeredPane.DEFAULT_LAYER.intValue());
			boolean found = false;
			for(int i=0;i<internalFrames.length;i++){
				if(internalFrames[i] instanceof NolModelPredVsActWKSP ){
					NolModel2 model1 = ((NolModelPredVsActWKSP)internalFrames[i]).
						getModel();
					if(model1.equals(model)){
						activeInternalFrame = (NolModelPredVsActWKSP)internalFrames[i];
						found = true;
						break;
					}
				}
			}
			if(!found){
				activeInternalFrame = new NolModelPredVsActWKSP(this,model);
				activeInternalFrame.setClosable(true);
				activeInternalFrame.setMaximizable(false);
				activeInternalFrame.setIconifiable(true);
				activeInternalFrame.setResizable(true);
				interCount++;
				activeInternalFrame.setBounds(20*interCount, 20*interCount, 700,590);
				if(interCount > 10){
					interCount = 0;
				}
				getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER); 
			}
		}
        try { 
			activeInternalFrame.setSelected(true); 
		} catch (java.beans.PropertyVetoException e2) {
			System.err.println("Non-Fatal exception: " + e2.getMessage());
			e2.printStackTrace();
		}
        getEditor().moveToFront(activeInternalFrame);
		activeInternalFrame.validate();
		activeInternalFrame.setBounds(20*interCount, 20*interCount, 701,590);
		activeInternalFrame.validate();
		activeInternalFrame.repaint(0l);
		int hh = 580;
		if(model instanceof NolOptimizeModel){
			if(((NolOptimizeModel)model).getStateModel() != null){
				hh = 590;
			}
		}
		activeInternalFrame.setBounds(20*interCount, 20*interCount,700,hh);
		activeInternalFrame.validate();
		activeInternalFrame.repaint(0l);
		activeInternalFrame.removeInternalFrameListener(mainAction);
		activeInternalFrame.addInternalFrameListener(mainAction);
		addWindowMenuItem(activeInternalFrame);
		progress.setText("Ready:");
		progress.validate();
		progress.repaint(0l);

	}

	public void showRecursivePredVsActWKSP(NolModel2 model){
		progress.setText("Status: Calculating predicted versus actual");
		if(activeInternalFrame == null) {
			activeInternalFrame = new NolRecusivePredVsActWKSP(this,model);
		    activeInternalFrame.setClosable(true);
		    activeInternalFrame.setMaximizable(false);
		    activeInternalFrame.setIconifiable(true);
			activeInternalFrame.setResizable(true);
			interCount++;
			activeInternalFrame.setBounds(20*interCount, 20*interCount, 570, 470);
			if(interCount > 10)
                interCount = 0;
		    getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER);  	
		}else{
			JLayeredPane pane = getEditor();
			Component[] internalFrames = pane.getComponentsInLayer(JLayeredPane.DEFAULT_LAYER.intValue());
			boolean found = false;
			for(int i=0;i<internalFrames.length;i++){
				if(internalFrames[i] instanceof NolRecusivePredVsActWKSP ){
					NolModel2 model1 = ((NolRecusivePredVsActWKSP)internalFrames[i]).
						getModel();
					if(model1.equals(model)){
						activeInternalFrame = (NolRecusivePredVsActWKSP)internalFrames[i];
						found = true;
						break;
					}
				}
			}
			if(!found){
				activeInternalFrame = new NolRecusivePredVsActWKSP(this,model);
				activeInternalFrame.setClosable(true);
				activeInternalFrame.setMaximizable(false);
				activeInternalFrame.setIconifiable(true);
				activeInternalFrame.setResizable(true);
				interCount++;
				activeInternalFrame.setBounds(20*interCount, 20*interCount, 570,470);
				if(interCount > 10){
					interCount = 0;
				}
				getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER); 
			}
		}
        try { 
			activeInternalFrame.setSelected(true); 
		} catch (java.beans.PropertyVetoException e2) {
			System.err.println("Non-Fatal exception: " + e2.getMessage());
			e2.printStackTrace();
		}
        getEditor().moveToFront(activeInternalFrame);
		activeInternalFrame.validate();
		activeInternalFrame.setBounds(20*interCount, 20*interCount, 851,471);
		activeInternalFrame.validate();
		activeInternalFrame.repaint(0l);
		int hh = 470;
		activeInternalFrame.setBounds(20*interCount, 20*interCount,550,hh);
		activeInternalFrame.validate();
		activeInternalFrame.repaint(0l);
		activeInternalFrame.removeInternalFrameListener(mainAction);
		activeInternalFrame.addInternalFrameListener(mainAction);
		addWindowMenuItem(activeInternalFrame);
		progress.setText("Ready:");
		progress.validate();
		progress.repaint(0l);

	}

	public void showModelSensitivityWKSP(NolModel2 model,int flag){
		if(activeInternalFrame == null) {
			if(flag == 0){
				activeInternalFrame = new NolLocalSensitivityWKSP(this,model);
			}else if(flag == 1){
				activeInternalFrame = new NolSensitivityWKSP(this,model);
			}
		    activeInternalFrame.setClosable(true);
		    activeInternalFrame.setMaximizable(false);
		    activeInternalFrame.setIconifiable(true);
			activeInternalFrame.setResizable(true);
			interCount++;
			if(interCount > 10)
                interCount = 0;
		    getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER);  	
		}else{
			JLayeredPane pane = getEditor();
			Component[] internalFrames = pane.getComponentsInLayer(JLayeredPane.DEFAULT_LAYER.intValue());
			boolean found = false;
			for(int i=0;i<internalFrames.length;i++){
				NolModel2 model1 = null;
				if(flag == 0){
					if(internalFrames[i] instanceof NolLocalSensitivityWKSP ){
						model1 = ((NolLocalSensitivityWKSP)internalFrames[i]).getModel();
					}
				}else{
					if(internalFrames[i] instanceof NolSensitivityWKSP ){
						model1 = ((NolSensitivityWKSP)internalFrames[i]).getModel();
					}
				}
				if(model1 != null){
					if(model1.equals(model)){
						activeInternalFrame = (NolInternalFrame)internalFrames[i];
						found = true;
						break;
					}
				}
			}
			if(!found){
				if(flag == 0){
					activeInternalFrame = new NolLocalSensitivityWKSP(this,model);
				}else if(flag == 1){
					activeInternalFrame = new NolSensitivityWKSP(this,model);
				}
				activeInternalFrame.setClosable(true);
				activeInternalFrame.setMaximizable(false);
				activeInternalFrame.setIconifiable(true);
				activeInternalFrame.setResizable(true);
				interCount++;
				if(interCount > 10)
					interCount = 0;
				getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER); 
			}
		}
        try { 
			activeInternalFrame.setSelected(true); 
		} catch (java.beans.PropertyVetoException e2) {
			System.err.println("Non-Fatal exception: " + e2.getMessage());
			e2.printStackTrace();
		}
        getEditor().moveToFront(activeInternalFrame);
		activeInternalFrame.validate();
		activeInternalFrame.setBounds(20*interCount, 20*interCount, 501, 351);
		activeInternalFrame.validate();
		activeInternalFrame.repaint(0l);
		activeInternalFrame.setBounds(20*interCount, 20*interCount, 500, 400);
		activeInternalFrame.validate();
		activeInternalFrame.repaint(0l);
		activeInternalFrame.removeInternalFrameListener(mainAction);
		activeInternalFrame.addInternalFrameListener(mainAction);
		addWindowMenuItem(activeInternalFrame);
		progress.setText("Ready:");
		progress.validate();
		progress.repaint(0l);

	}

	private Vector getValidateDataSeries(NolModel2 model){
		Vector inputVarNames = new Vector();
		Vector inputVars = new Vector();
		if(model instanceof NolOptimizeModel){
			Vector manis = ((NolOptimizeModel)model).getManipulate();
			Vector exogs = ((NolOptimizeModel)model).getExogenous();
			Vector outs = ((NolOptimizeModel)model).getOutputs();
			Vector states = ((NolOptimizeModel)model).getState();
			for(int i=0;i<manis.size();i++){
				inputVarNames.addElement(manis.elementAt(i));
			}
			for(int i=0;i<exogs.size();i++){
				inputVarNames.addElement(exogs.elementAt(i));
			}
			for(int i=0;i<outs.size();i++){
				inputVarNames.addElement(outs.elementAt(i));
			}
			for(int i=0;i<states.size();i++){
				inputVarNames.addElement(states.elementAt(i));
			}
		}else{
			Vector ins = model.getInputs();
			Vector outs = model.getOutputs();
			for(int i=0;i<ins.size();i++){
				inputVarNames.addElement(ins.elementAt(i));
			}
			for(int i=0;i<outs.size();i++){
				inputVarNames.addElement(outs.elementAt(i));
			}

		}
		Preprocessor prep = model.getPreprocessor();
		Vector originalVarNames = prep.getOriginalVarNames(inputVarNames);		
		for(int i=0;i<originalVarNames.size();i++){
			String varName = (String)originalVarNames.elementAt(i);
			Variable varObj = prep.getVariableFromVariableName(varName);
			inputVars.addElement(varObj);
		}

		Vector ddss = new Vector();
		for(int i=0;i<inputVars.size();i++){
			Variable varObj = (Variable)inputVars.elementAt(i);
			DataSeries ds = varObj.getDataSeries();
			if(!ddss.contains(ds)){
				ddss.addElement(ds);
			}
		}
		int n = ddss.size();
		RawDataSource rawData = project.getRawDataSource();
		Vector rawDss = rawData.getDataSeries();
		boolean hasValidateData = false;
		Vector availableDs = new Vector(n);
		for(int i=0;i<n;i++){
			int c=0;
			DataSeries ds1 = (DataSeries)ddss.elementAt(i);
			Vector avaiDs = new Vector();
			for(int j=0;j<rawDss.size();j++){
				DataSeries rds = (DataSeries)rawDss.elementAt(j);
				if(ds1.getName().equals(rds.getName())){
					avaiDs.addElement(rds);
				}else{
					if(ds1.getHasTimeStamps() == rds.getHasTimeStamps()){
						Vector varObjs1 = ds1.getVarObjects();
						Vector varObjs2 = rds.getVarObjects();
						boolean match = true;
						for(int k=0;k<varObjs1.size();k++){							
							Variable varObj = (Variable)varObjs1.elementAt(k);
							String varName1 = varObj.toString();
							if(inputVars.contains(varObj)){
								boolean found = false;
								for(int l=0;l<varObjs2.size();l++){
 									String varName2 = varObjs2.elementAt(l).toString();
									if(varName1.equals(varName2)){
									   found = true;
									   break;
									}
								}
								if(!found){
								   match = false;
								   break;
								}
							}
						}
						if(match){
							avaiDs.addElement(rds);
							hasValidateData = true;
						}
					}
				}
			}
			availableDs.addElement(avaiDs);
		}
		if(!hasValidateData){
			showOKDialog(getNolResourceString(NODATAMATCHMODEL));
//			showOKDialog("No data series matches inputs to this model.");
			return null;
		}

		getModelValidateChoiceDialog().setContent(ddss,availableDs);
		getModelValidateChoiceDialog().setBounds(200, 200, 420, 300);
		getModelValidateChoiceDialog().setVisible(true);
		
		if(!getModelValidateChoiceDialog().getResult()){
			return null;
		}

		if(!getModelValidateChoiceDialog().hasValidData()){
			showOKDialog(getNolResourceString(INVALIDDATACHOICE));
//			showOKDialog("Invalid choice of data series.");
			return null;
		}

		return getModelValidateChoiceDialog().getValidateDataSeries();
	}

	private void showInternalFrame(NolInternalFrame interFrame){
		activeInternalFrame = interFrame;
		activeInternalFrame.setClosable(true);
        activeInternalFrame.setMaximizable(false);
        activeInternalFrame.setIconifiable(true);
        activeInternalFrame.setResizable(true);
        getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER);  
		interCount++;
		activeInternalFrame.setBounds(20*interCount, 20*interCount, 620, 460);
		if(interCount > 10)
               interCount = 0;
        try { 
			activeInternalFrame.setSelected(true); 
		} catch (java.beans.PropertyVetoException e2) {
			System.err.println("Non-Fatal exception: " + e2.getMessage());
			e2.printStackTrace();
		}
        getEditor().moveToFront(activeInternalFrame);
		activeInternalFrame.validate();
		activeInternalFrame.setBounds(20*interCount, 20*interCount, 851,471);
		activeInternalFrame.validate();
		activeInternalFrame.repaint(0l);
		activeInternalFrame.setBounds(20*interCount, 20*interCount, 680,620);
		activeInternalFrame.validate();
		activeInternalFrame.repaint(0l);
		activeInternalFrame.removeInternalFrameListener(mainAction);
		activeInternalFrame.addInternalFrameListener(mainAction);

		
		progress.setText("Ready:");
		progress.validate();
		progress.repaint(0l);
		addWindowMenuItem(activeInternalFrame);
	}

	public void showModelValidationWKSP(NolModel2 model){
		Vector validateDataSeries = getValidateDataSeries(model);
		if(validateDataSeries == null){
			return;
		}
		NolValidateModelWKSP validateWKSP = new NolValidateModelWKSP(this,model,validateDataSeries);
		if(!validateWKSP.isValidValidation()){
			showOKDialog(getNolResourceString(NOVALIDATIONDATA));
//			showOKDialog("No valid data for validation.");
			return;
		}
		showInternalFrame(validateWKSP);
	}

	public void showPredictiveModelWKSP(NolModel2 model){
		
		if(activeInternalFrame == null) {
		    activeInternalFrame = new NolModelWKSP(this,model);
		    activeInternalFrame.setClosable(true);
		    activeInternalFrame.setMaximizable(false);
		    activeInternalFrame.setIconifiable(true);
			activeInternalFrame.setResizable(true);
			interCount++;
			activeInternalFrame.setBounds(20*interCount, 20*interCount, 500, 350);
			if(interCount > 10)
                interCount = 0;
		    getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER);  	
		}else{
			JLayeredPane pane = getEditor();
			Component[] internalFrames = pane.getComponentsInLayer(JLayeredPane.DEFAULT_LAYER.intValue());
			boolean found = false;
			for(int i=0;i<internalFrames.length;i++){
				if(internalFrames[i] instanceof NolModelWKSP ){
					NolModel2 model0 = ((NolModelWKSP)internalFrames[i]).
						getModel();
					if(model.equals(model0)){
						activeInternalFrame = (NolModelWKSP)internalFrames[i];
						found = true;
						break;
					}
				}
			}
			if(!found){
				activeInternalFrame = new NolModelWKSP(this,model);
				activeInternalFrame.setClosable(true);
				activeInternalFrame.setMaximizable(false);
				activeInternalFrame.setIconifiable(true);
				activeInternalFrame.setResizable(true);
				interCount++;
				activeInternalFrame.setBounds(20*interCount, 20*interCount, 500,350);
				if(interCount > 10)
					interCount = 0;
				getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER); 
			}
		}
        try { 
			activeInternalFrame.setSelected(true); 
		} catch (java.beans.PropertyVetoException e2) {
			System.err.println("Non-Fatal exception: " + e2.getMessage());
			e2.printStackTrace();
		}
        getEditor().moveToFront(activeInternalFrame);
		activeInternalFrame.validate();
		activeInternalFrame.removeInternalFrameListener(mainAction);
		activeInternalFrame.addInternalFrameListener(mainAction);
		addWindowMenuItem(activeInternalFrame);
		progress.setText("Ready:");
		progress.validate();
		progress.repaint(0l);
	}
	
	
	public void showClassicModelWKSP(NolModel2 model){
		
		if(activeInternalFrame == null) {
		    activeInternalFrame = new NolClassicModelWKSP(this,model);
		    activeInternalFrame.setClosable(true);
		    activeInternalFrame.setMaximizable(false);
		    activeInternalFrame.setIconifiable(true);
			activeInternalFrame.setResizable(true);
			interCount++;
			activeInternalFrame.setBounds(20*interCount, 20*interCount, 500, 350);
			if(interCount > 10)
                interCount = 0;
		    getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER);  	
		}else{
			JLayeredPane pane = getEditor();
			Component[] internalFrames = pane.getComponentsInLayer(JLayeredPane.DEFAULT_LAYER.intValue());
			boolean found = false;
			for(int i=0;i<internalFrames.length;i++){
				if(internalFrames[i] instanceof NolClassicModelWKSP ){
					NolModel2 model0 = ((NolClassicModelWKSP)internalFrames[i]).
						getModel();
					if(model.equals(model0)){
						activeInternalFrame = (NolClassicModelWKSP)internalFrames[i];
						found = true;
						break;
					}
				}
			}
			if(!found){
				activeInternalFrame = new NolClassicModelWKSP(this,model);
				activeInternalFrame.setClosable(true);
				activeInternalFrame.setMaximizable(false);
				activeInternalFrame.setIconifiable(true);
				activeInternalFrame.setResizable(true);
				interCount++;
				activeInternalFrame.setBounds(20*interCount, 20*interCount, 500,350);
				if(interCount > 10)
					interCount = 0;
				getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER); 
			}
		}
        try { 
			activeInternalFrame.setSelected(true); 
		} catch (java.beans.PropertyVetoException e2) {
			System.err.println("Non-Fatal exception: " + e2.getMessage());
			e2.printStackTrace();
		}
        getEditor().moveToFront(activeInternalFrame);
		activeInternalFrame.validate();
		activeInternalFrame.removeInternalFrameListener(mainAction);
		activeInternalFrame.addInternalFrameListener(mainAction);
		addWindowMenuItem(activeInternalFrame);
		progress.setText("Ready:");
		progress.validate();
		progress.repaint(0l);
	}

	public void showVariableValueWKSP(NolRhoModel model){
		
		if(activeInternalFrame == null) {
		    activeInternalFrame = new NolVariableValueTableWKSP(this,model);
		    activeInternalFrame.setClosable(true);
		    activeInternalFrame.setMaximizable(false);
		    activeInternalFrame.setIconifiable(true);
			activeInternalFrame.setResizable(true);
			interCount++;
			activeInternalFrame.setBounds(20*interCount, 20*interCount, 350, 400);
			if(interCount > 10)
                interCount = 0;
		    getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER);  	
		}else{
			JLayeredPane pane = getEditor();
			Component[] internalFrames = pane.getComponentsInLayer(JLayeredPane.DEFAULT_LAYER.intValue());
			boolean found = false;
			for(int i=0;i<internalFrames.length;i++){
				if(internalFrames[i] instanceof NolVariableValueTableWKSP ){
					NolRhoModel model0 = ((NolVariableValueTableWKSP)internalFrames[i]).getModel();
					if(model.equals(model0)){
						activeInternalFrame = (NolVariableValueTableWKSP)internalFrames[i];
						found = true;
						break;
					}
				}
			}
			if(!found){
				activeInternalFrame = new NolVariableValueTableWKSP(this,model);
				activeInternalFrame.setClosable(true);
				activeInternalFrame.setMaximizable(false);
				activeInternalFrame.setIconifiable(true);
				activeInternalFrame.setResizable(true);
				interCount++;
				activeInternalFrame.setBounds(20*interCount, 20*interCount, 350,400);
				if(interCount > 10)
					interCount = 0;
				getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER); 
			}
		}
        try { 
			activeInternalFrame.setSelected(true); 
		} catch (java.beans.PropertyVetoException e2) {
			System.err.println("Non-Fatal exception: " + e2.getMessage());
			e2.printStackTrace();
		}
        getEditor().moveToFront(activeInternalFrame);
		activeInternalFrame.validate();
		activeInternalFrame.removeInternalFrameListener(mainAction);
		activeInternalFrame.addInternalFrameListener(mainAction);
		addWindowMenuItem(activeInternalFrame);
		progress.setText("Ready:");
		progress.validate();
		progress.repaint(0l);
	}

	public void showOutputHistogramWKSP(double[] values, String title){

		if(activeInternalFrame == null) {
		    activeInternalFrame = new NolOutputHistogramFrame(this,values,title);
		    activeInternalFrame.setClosable(true);
		    activeInternalFrame.setMaximizable(false);
		    activeInternalFrame.setIconifiable(true);
			activeInternalFrame.setResizable(true);
			interCount++;
			activeInternalFrame.setBounds(20*interCount, 20*interCount, 600, 380);
			if(interCount > 10)
                interCount = 0;
		    getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER);  	
		}else{
			JLayeredPane pane = getEditor();
			Component[] internalFrames = pane.getComponentsInLayer(JLayeredPane.DEFAULT_LAYER.intValue());
			boolean found = false;
			for(int i=0;i<internalFrames.length;i++){
				if(internalFrames[i] instanceof NolOutputHistogramFrame ){
					String title0 = ((NolOutputHistogramFrame)internalFrames[i]).getTitle();
					if(title.equals(title0)){
						activeInternalFrame = (NolOutputHistogramFrame)internalFrames[i];
						found = true;
						break;
					}
				}
			}
			if(!found){
				activeInternalFrame = new NolOutputHistogramFrame(this,values,title);
				activeInternalFrame.setClosable(true);
				activeInternalFrame.setMaximizable(false);
				activeInternalFrame.setIconifiable(true);
				activeInternalFrame.setResizable(true);
				interCount++;
				activeInternalFrame.setBounds(20*interCount, 20*interCount, 600,380);
				if(interCount > 10)
					interCount = 0;
				getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER); 
			}
		}
        try { 
			activeInternalFrame.setSelected(true); 
		} catch (java.beans.PropertyVetoException e2) {
			System.err.println("Non-Fatal exception: " + e2.getMessage());
			e2.printStackTrace();
		}
        getEditor().moveToFront(activeInternalFrame);
		activeInternalFrame.validate();
		activeInternalFrame.removeInternalFrameListener(mainAction);
		activeInternalFrame.addInternalFrameListener(mainAction);

		activeInternalFrame.setBounds(20*interCount, 20*interCount, 601, 381);
		activeInternalFrame.validate();
		activeInternalFrame.setBounds(20*interCount, 20*interCount, 600, 380);
		
		addWindowMenuItem(activeInternalFrame);
		progress.setText("Ready:");
		progress.validate();
		progress.repaint(0l);
	}

	public void showRhoModelWKSP(NolRhoModel model){
		
		if(activeInternalFrame == null) {
		    activeInternalFrame = new NolRhoModelWKSP(this,model);
		    activeInternalFrame.setClosable(true);
		    activeInternalFrame.setMaximizable(false);
		    activeInternalFrame.setIconifiable(true);
			activeInternalFrame.setResizable(true);
			interCount++;
			activeInternalFrame.setBounds(20*interCount, 20*interCount, 500, 350);
			if(interCount > 10)
                interCount = 0;
		    getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER);  	
		}else{
			JLayeredPane pane = getEditor();
			Component[] internalFrames = pane.getComponentsInLayer(JLayeredPane.DEFAULT_LAYER.intValue());
			boolean found = false;
			for(int i=0;i<internalFrames.length;i++){
				if(internalFrames[i] instanceof NolRhoModelWKSP ){
					NolModel2 model0 = ((NolRhoModelWKSP)internalFrames[i]).
						getModel();
					if(model.equals(model0)){
						activeInternalFrame = (NolRhoModelWKSP)internalFrames[i];
						found = true;
						break;
					}
				}
			}
			if(!found){
				activeInternalFrame = new NolRhoModelWKSP(this,model);
				activeInternalFrame.setClosable(true);
				activeInternalFrame.setMaximizable(false);
				activeInternalFrame.setIconifiable(true);
				activeInternalFrame.setResizable(true);
				interCount++;
				activeInternalFrame.setBounds(20*interCount, 20*interCount, 500,350);
				if(interCount > 10)
					interCount = 0;
				getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER); 
			}
		}
        try { 
			activeInternalFrame.setSelected(true); 
		} catch (java.beans.PropertyVetoException e2) {
			System.err.println("Non-Fatal exception: " + e2.getMessage());
			e2.printStackTrace();
		}
        getEditor().moveToFront(activeInternalFrame);
		activeInternalFrame.validate();
		activeInternalFrame.removeInternalFrameListener(mainAction);
		activeInternalFrame.addInternalFrameListener(mainAction);
		addWindowMenuItem(activeInternalFrame);
		progress.setText("Ready:");
		progress.validate();
		progress.repaint(0l);
	}

	public void showPlsModelWKSP(NolPlsModel model){
		if(activeInternalFrame == null) {
		    activeInternalFrame = new NolPlsModelWKSP(this,model);
		    activeInternalFrame.setClosable(true);
		    activeInternalFrame.setMaximizable(false);
		    activeInternalFrame.setIconifiable(true);
			activeInternalFrame.setResizable(true);
			interCount++;
			activeInternalFrame.setBounds(20*interCount, 20*interCount, 500, 350);
			if(interCount > 10)
                interCount = 0;
		    getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER);  	
		}else{
			JLayeredPane pane = getEditor();
			Component[] internalFrames = pane.getComponentsInLayer(JLayeredPane.DEFAULT_LAYER.intValue());
			boolean found = false;
			for(int i=0;i<internalFrames.length;i++){
				if(internalFrames[i] instanceof NolPlsModelWKSP ){
					NolModel2 model0 = ((NolPlsModelWKSP)internalFrames[i]).
						getModel();
					if(model.equals(model0)){
						activeInternalFrame = (NolPlsModelWKSP)internalFrames[i];
						found = true;
						break;
					}
				}
			}
			if(!found){
				activeInternalFrame = new NolPlsModelWKSP(this,model);
				activeInternalFrame.setClosable(true);
				activeInternalFrame.setMaximizable(false);
				activeInternalFrame.setIconifiable(true);
				activeInternalFrame.setResizable(true);
				interCount++;
				activeInternalFrame.setBounds(20*interCount, 20*interCount, 500,350);
				if(interCount > 10)
					interCount = 0;
				getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER); 
			}
		}
        try { 
			activeInternalFrame.setSelected(true); 
		} catch (java.beans.PropertyVetoException e2) {
			System.err.println("Non-Fatal exception: " + e2.getMessage());
			e2.printStackTrace();
		}
        getEditor().moveToFront(activeInternalFrame);
		activeInternalFrame.validate();
		activeInternalFrame.removeInternalFrameListener(mainAction);
		activeInternalFrame.addInternalFrameListener(mainAction);
		addWindowMenuItem(activeInternalFrame);
		progress.setText("Ready:");
		progress.validate();
		progress.repaint(0l);
	}

	public void showPcaModelWKSP(NolPcaModel model){
		if(activeInternalFrame == null) {
		    activeInternalFrame = new NolPcaModelWKSP(this,model);
		    activeInternalFrame.setClosable(true);
		    activeInternalFrame.setMaximizable(false);
		    activeInternalFrame.setIconifiable(true);
			activeInternalFrame.setResizable(true);
			interCount++;
			activeInternalFrame.setBounds(20*interCount, 20*interCount, 500, 350);
			if(interCount > 10)
                interCount = 0;
		    getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER);  	
		}else{
			JLayeredPane pane = getEditor();
			Component[] internalFrames = pane.getComponentsInLayer(JLayeredPane.DEFAULT_LAYER.intValue());
			boolean found = false;
			for(int i=0;i<internalFrames.length;i++){
				if(internalFrames[i] instanceof NolPcaModelWKSP ){
					NolPcaModel model0 = ((NolPcaModelWKSP)internalFrames[i]).
						getModel();
					if(model.equals(model0)){
						activeInternalFrame = (NolPcaModelWKSP)internalFrames[i];
						found = true;
						break;
					}
				}
			}
			if(!found){
				activeInternalFrame = new NolPcaModelWKSP(this,model);
				activeInternalFrame.setClosable(true);
				activeInternalFrame.setMaximizable(false);
				activeInternalFrame.setIconifiable(true);
				activeInternalFrame.setResizable(true);
				interCount++;
				activeInternalFrame.setBounds(20*interCount, 20*interCount, 500,350);
				if(interCount > 10)
					interCount = 0;
				getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER); 
			}
		}
        try { 
			activeInternalFrame.setSelected(true); 
		} catch (java.beans.PropertyVetoException e2) {
			System.err.println("Non-Fatal exception: " + e2.getMessage());
			e2.printStackTrace();
		}
        getEditor().moveToFront(activeInternalFrame);
		activeInternalFrame.validate();
		activeInternalFrame.removeInternalFrameListener(mainAction);
		activeInternalFrame.addInternalFrameListener(mainAction);
		addWindowMenuItem(activeInternalFrame);
		progress.setText("Ready:");
		progress.validate();
		progress.repaint(0l);
	}

	public void showOptimizeModelWKSP(NolOptimizeModel model){
		
		if(activeInternalFrame == null) {
		    activeInternalFrame = new NolModelWKSP(this,model);
		    activeInternalFrame.setClosable(true);
		    activeInternalFrame.setMaximizable(false);
		    activeInternalFrame.setIconifiable(true);
			activeInternalFrame.setResizable(true);
			interCount++;
			activeInternalFrame.setBounds(20*interCount, 20*interCount, 500, 350);
			if(interCount > 10)
                interCount = 0;
		    getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER);  	
		}else{
			JLayeredPane pane = getEditor();
			Component[] internalFrames = pane.getComponentsInLayer(JLayeredPane.DEFAULT_LAYER.intValue());
			boolean found = false;
			for(int i=0;i<internalFrames.length;i++){
				if(internalFrames[i] instanceof NolModelWKSP ){
					NolModel2 model0 = ((NolModelWKSP)internalFrames[i]).
						getModel();
					if(model.equals(model0)){
						activeInternalFrame = (NolModelWKSP)internalFrames[i];
						found = true;
						break;
					}
				}
			}
			if(!found){
				activeInternalFrame = new NolModelWKSP(this,model);
				activeInternalFrame.setClosable(true);
				activeInternalFrame.setMaximizable(false);
				activeInternalFrame.setIconifiable(true);
				activeInternalFrame.setResizable(true);
				interCount++;
				activeInternalFrame.setBounds(20*interCount, 20*interCount, 500,350);
				if(interCount > 10)
					interCount = 0;
				getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER); 
			}
		}
        try { 
			activeInternalFrame.setSelected(true); 
		} catch (java.beans.PropertyVetoException e2) {
			System.err.println("Non-Fatal exception: " + e2.getMessage());
			e2.printStackTrace();
		}
        getEditor().moveToFront(activeInternalFrame);
		activeInternalFrame.validate();
		activeInternalFrame.removeInternalFrameListener(mainAction);
		activeInternalFrame.addInternalFrameListener(mainAction);
		addWindowMenuItem(activeInternalFrame);
		progress.setText("Ready:");
		progress.validate();
		progress.repaint(0l);
	}

	public void showSimulationWKSP(ResponseSurfaceSimulation sim){
		
		if(activeInternalFrame == null) {
		    activeInternalFrame = new NolResponseSurfaceSimulationWKSP(this,sim);
			activeInternalFrame.setClosable(true);
		    activeInternalFrame.setMaximizable(false);
		    activeInternalFrame.setIconifiable(true);
			activeInternalFrame.setResizable(true);
			interCount++;
			activeInternalFrame.setBounds(20*interCount, 20*interCount, 500, 350);
			if(interCount > 10)
                interCount = 0;
		    getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER);  	
		}else{
			JLayeredPane pane = getEditor();
			Component[] internalFrames = pane.getComponentsInLayer(JLayeredPane.DEFAULT_LAYER.intValue());
			boolean found = false;
			for(int i=0;i<internalFrames.length;i++){
				if(internalFrames[i] instanceof NolResponseSurfaceSimulationWKSP ){
					ResponseSurfaceSimulation sim0 = ((NolResponseSurfaceSimulationWKSP)internalFrames[i]).
						getSimulation();
					if(sim0.equals(sim)){
						activeInternalFrame = (NolResponseSurfaceSimulationWKSP)internalFrames[i];
						found = true;
						break;
					}
				}
			}
			if(!found){
			    activeInternalFrame = new NolResponseSurfaceSimulationWKSP(this,sim);
				activeInternalFrame.setClosable(true);
				activeInternalFrame.setMaximizable(false);
				activeInternalFrame.setIconifiable(true);
				activeInternalFrame.setResizable(true);
				interCount++;
				activeInternalFrame.setBounds(20*interCount, 20*interCount, 500,350);
				if(interCount > 10)
					interCount = 0;
				getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER); 
			}
		}
        try { 
			activeInternalFrame.setSelected(true); 
		} catch (java.beans.PropertyVetoException e2) {
			System.err.println("Non-Fatal exception: " + e2.getMessage());
			e2.printStackTrace();
		}
        getEditor().moveToFront(activeInternalFrame);
		activeInternalFrame.validate();
		activeInternalFrame.removeInternalFrameListener(mainAction);
		activeInternalFrame.addInternalFrameListener(mainAction);
		addWindowMenuItem(activeInternalFrame);
		progress.setText("Ready:");
		progress.validate();
		progress.repaint(0l);
	}

/*	public void showObjectiveWKSP(int objectiveIndex){
//		Objective obj = project.getSimulation(objectiveIndex);
		
		if(activeInternalFrame == null) {
			activeInternalFrame = new NolObjectiveWKSP(this,objectiveIndex);
			activeInternalFrame.setClosable(true);
		    activeInternalFrame.setMaximizable(false);
		    activeInternalFrame.setIconifiable(true);
			activeInternalFrame.setResizable(true);
			interCount++;
			activeInternalFrame.setBounds(20*interCount, 20*interCount, 500, 350);
			if(interCount > 10)
                interCount = 0;
		    getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER);  	
		}else{
			JLayeredPane pane = getEditor();
			Component[] internalFrames = pane.getComponentsInLayer(JLayeredPane.DEFAULT_LAYER.intValue());
			boolean found = false;
			for(int i=0;i<internalFrames.length;i++){
				if(internalFrames[i] instanceof NolObjectiveWKSP ){
					int oindex = ((NolObjectiveWKSP)internalFrames[i]).
						getObjectiveIndex();
					if(oindex == objectiveIndex){
						activeInternalFrame = (NolObjectiveWKSP)internalFrames[i];
						found = true;
						break;
					}
				}
			}
			if(!found){
				activeInternalFrame = new NolObjectiveWKSP(this,objectiveIndex);
				activeInternalFrame.setClosable(true);
				activeInternalFrame.setMaximizable(false);
				activeInternalFrame.setIconifiable(true);
				activeInternalFrame.setResizable(true);
				interCount++;
				activeInternalFrame.setBounds(20*interCount, 20*interCount, 500,350);
				if(interCount > 10)
					interCount = 0;
				getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER); 
			}
		}
        getEditor().moveToFront(activeInternalFrame);
		activeInternalFrame.validate();
		activeInternalFrame.removeInternalFrameListener(mainAction);
		activeInternalFrame.addInternalFrameListener(mainAction);
		addWindowMenuItem(activeInternalFrame);
	}

*/
	public void showOptimizationWKSP(NolOptimization optimization){
		
		if(activeInternalFrame == null) {
			activeInternalFrame = new NolOptimizationWKSP(this,optimization);
			activeInternalFrame.setClosable(true);
		    activeInternalFrame.setMaximizable(false);
		    activeInternalFrame.setIconifiable(true);
			activeInternalFrame.setResizable(true);
			interCount++;
			activeInternalFrame.setBounds(20*interCount, 20*interCount, 550,450);
			if(interCount > 10)
                interCount = 0;
		    getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER);  	
		}else{
			JLayeredPane pane = getEditor();
			Component[] internalFrames = pane.getComponentsInLayer(JLayeredPane.DEFAULT_LAYER.intValue());
			boolean found = false;
			for(int i=0;i<internalFrames.length;i++){
				if(internalFrames[i] instanceof NolOptimizationWKSP ){
					NolOptimization optimization0 = ((NolOptimizationWKSP)internalFrames[i]).
						getOptimization();
					if(optimization0.equals(optimization)){
						activeInternalFrame = (NolOptimizationWKSP)internalFrames[i];
						found = true;
						break;
					}
				}
			}
			if(!found){
				activeInternalFrame = new NolOptimizationWKSP(this,optimization);
				activeInternalFrame.setClosable(true);
				activeInternalFrame.setMaximizable(false);
				activeInternalFrame.setIconifiable(true);
				activeInternalFrame.setResizable(true);
				interCount++;
				activeInternalFrame.setBounds(20*interCount, 20*interCount, 550,450);
				if(interCount > 10)
					interCount = 0;
				getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER); 
			}
		}
        try { 
			activeInternalFrame.setSelected(true); 
		} catch (java.beans.PropertyVetoException e2) {
			System.err.println("Non-Fatal exception: " + e2.getMessage());
			e2.printStackTrace();
		}
        getEditor().moveToFront(activeInternalFrame);
		activeInternalFrame.validate();
		activeInternalFrame.removeInternalFrameListener(mainAction);
		activeInternalFrame.addInternalFrameListener(mainAction);
//		((NolOptimizationWKSP)activeInternalFrame).refreshVarSliders();
		addWindowMenuItem(activeInternalFrame);
		progress.setText("Ready:");
		progress.validate();
		progress.repaint(0l);
	}

	public void showGenOptimizationWKSP(NolGenOptimization optimization){
		
		if(activeInternalFrame == null) {
			activeInternalFrame = new NolGenOptimizationWKSP(this,optimization);
			activeInternalFrame.setClosable(true);
		    activeInternalFrame.setMaximizable(false);
		    activeInternalFrame.setIconifiable(true);
			activeInternalFrame.setResizable(true);
			interCount++;
			activeInternalFrame.setBounds(20*interCount, 20*interCount, 550,450);
			if(interCount > 10)
                interCount = 0;
		    getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER);  	
		}else{
			JLayeredPane pane = getEditor();
			Component[] internalFrames = pane.getComponentsInLayer(JLayeredPane.DEFAULT_LAYER.intValue());
			boolean found = false;
			for(int i=0;i<internalFrames.length;i++){
				if(internalFrames[i] instanceof NolGenOptimizationWKSP ){
					NolGenOptimization optimization0 = ((NolGenOptimizationWKSP)internalFrames[i]).
						getOptimization();
					if(optimization0.equals(optimization)){
						activeInternalFrame = (NolGenOptimizationWKSP)internalFrames[i];
						found = true;
						break;
					}
				}
			}
			if(!found){
				activeInternalFrame = new NolGenOptimizationWKSP(this,optimization);
				activeInternalFrame.setClosable(true);
				activeInternalFrame.setMaximizable(false);
				activeInternalFrame.setIconifiable(true);
				activeInternalFrame.setResizable(true);
				interCount++;
				activeInternalFrame.setBounds(20*interCount, 20*interCount, 550,450);
				if(interCount > 10)
					interCount = 0;
				getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER); 
			}
		}
        try { 
			activeInternalFrame.setSelected(true); 
		} catch (java.beans.PropertyVetoException e2) {
			System.err.println("Non-Fatal exception: " + e2.getMessage());
			e2.printStackTrace();
		}
        getEditor().moveToFront(activeInternalFrame);
		activeInternalFrame.validate();
		activeInternalFrame.removeInternalFrameListener(mainAction);
		activeInternalFrame.addInternalFrameListener(mainAction);
//		((NolGenOptimizationWKSP)activeInternalFrame).refreshVarSliders();
		addWindowMenuItem(activeInternalFrame);
		progress.setText("Ready:");
		progress.validate();
		progress.repaint(0l);
	}

	public void showFormulaListWKSP(Preprocessor prep){
		if(activeInternalFrame == null) {
		    activeInternalFrame = new NolFormulaListWKSP(this,prep);
		    activeInternalFrame.setClosable(true);
		    activeInternalFrame.setMaximizable(false);
		    activeInternalFrame.setIconifiable(true);
			activeInternalFrame.setResizable(true);
			interCount++;
			activeInternalFrame.setBounds(20*interCount, 20*interCount, 600, 350);
			if(interCount > 10)
                interCount = 0;
		    getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER);  	
		}else{
			JLayeredPane pane = getEditor();
			Component[] internalFrames = pane.getComponentsInLayer(JLayeredPane.DEFAULT_LAYER.intValue());
			boolean found = false;
			for(int i=0;i<internalFrames.length;i++){
				if(internalFrames[i] instanceof NolFormulaListWKSP ){
					Preprocessor prep0 = ((NolFormulaListWKSP)internalFrames[i]).
						getPreprocessor();
					if(prep.equals(prep0)){
						activeInternalFrame = (NolFormulaListWKSP)internalFrames[i];
						found = true;
						break;
					}
				}
			}
			if(!found){
				activeInternalFrame = new NolFormulaListWKSP(this,prep);
				activeInternalFrame.setClosable(true);
				activeInternalFrame.setMaximizable(false);
				activeInternalFrame.setIconifiable(true);
				activeInternalFrame.setResizable(true);
				interCount++;
				activeInternalFrame.setBounds(20*interCount, 20*interCount, 600,350);
				if(interCount > 10)
					interCount = 0;
				getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER); 
			}
		}
        try { 
			activeInternalFrame.setSelected(true); 
		} catch (java.beans.PropertyVetoException e2) {
			System.err.println("Non-Fatal exception: " + e2.getMessage());
			e2.printStackTrace();		
		}
        getEditor().moveToFront(activeInternalFrame);
		activeInternalFrame.validate();
		activeInternalFrame.removeInternalFrameListener(mainAction);
		activeInternalFrame.addInternalFrameListener(mainAction);
		addWindowMenuItem(activeInternalFrame);
		progress.setText("Ready:");
		progress.validate();
		progress.repaint(0l);
	}

	private void clearAllInternalFrame(){
		Vector iframeVector;
		synchronized (this) {
			iframeVector = (Vector) internalFrameStack.clone();
		}
		for(int i=0;i<iframeVector.size();i++){
			NolInternalFrame inFrame = (NolInternalFrame)iframeVector.elementAt(i);
			try{
				inFrame.setClosed(true);
			}catch(java.beans.PropertyVetoException evt){
				System.err.println("Non-Fatal exception: " + evt.getMessage());
				evt.printStackTrace();
			}
		}
		iframeVector.removeAllElements();
		iframeVector = null;
	}
	
	private void removeFrameFromListener(NolInternalFrame inFrame){

		RawDataSource rds = project.getRawDataSource(); // SOURCE LEVEL - only one data source
		int p = project.getNumberOfPreprocessors();
		if(inFrame instanceof NolSpreadsheet ){
			((NolSpreadsheet)inFrame).removeListeners();
/*			NolTableDataModel dataModel=((NolSpreadsheet)inFrame).getDataModel();
			rds.removeListener(dataModel);
			for(int i = 0; i < p; i++) { // SOURCE LEVEL
				Preprocessor pre = project.getPreprocessorByIndex(i);
				pre.removeListener(dataModel);
			}
*/	
		}else if(inFrame instanceof NolProjectionChartFrame ){
			((NolProjectionChartFrame)inFrame).removeListeners();
		}else if(inFrame instanceof NolXYChartFrame ){
			((NolXYChartFrame)inFrame).removeListeners();
		}else if(inFrame instanceof NolVarChartFrame ){
			((NolVarChartFrame)inFrame).removeListeners();
		}else if(inFrame instanceof NolHistogramFrame ){
		}
	}

// --- action implementations -----------------------------------
	
	class MainFrameAction extends AbstractAction implements 
		InternalFrameListener, RawDataSourceListener,ProjectListener,Runnable {
		private String command;
		private Object source;
		MainFrameAction() {super("main");}
		@Override
		public void actionPerformed(ActionEvent e) {
			// handle all actions outside of the main UI thread, otherwise the UI hangs
			if(blockMainAction){
				return; 
			}
			command = e.getActionCommand ();
			source = e.getSource ();
			new Thread (this).start();
		}

		@Override
		public void run () {
			if(source.equals(labelStatus)){
				labelStatusFire = true;
				int ord = labelStatus.getSelectedIndex();
				if(ord == 0){
					return;
				}
				blockMainAction = true;
//				//         setWaitCursor(true);
				labelStatus.insertItemAt(labelStatus.getSelectedItem(),0);
				labelStatus.removeItemAt(ord+1);
				labelStatus.setSelectedIndex(0);

				Vector origLabels = project.getLabels();
				int lc = origLabels.size();
				int[] orders = new int[lc];
				for(int i=0;i<lc;i++){
					NolLabel lab = (NolLabel)origLabels.elementAt(i);
					for(int j=0;j<lc;j++){
						String labelName = (String)labelStatus.getItemAt(j);
						if(lab.getName().equals(labelName)){
							orders[i] = j;
							break;
						}
					}
				}
//				for(int i=0;i<lc;i++){
//					System.out.println("labelStatus change order orders["+i+"]="+orders[i]);
//				}
				project.changeLabelOrder(orders);
				blockMainAction = false;
				labelStatusFire = false;
				//         //         setWaitCursor(false);
//				for(int i=0;i<lc;i++){
//					NolLabel lab = (NolLabel)origLabels.elementAt(i);
//					setLabelOrder(orders[i]);
//				}

			}else if(source.equals(selectStatus)){
				if(selectStatus.isSelected()){
					project.getRawDataSource().setSelectStatus(false);
				}else{
					project.getRawDataSource().setSelectStatus(true);
				}
			}else if(source.equals(logoButton)){
				getAboutDialog().setVisible(true);
			}else{
				int n = internalFrameStack.size();
				for(int i=0;i<n;i++){
					NolInternalFrame iframe = (NolInternalFrame)internalFrameStack.elementAt(i);
					String frameTitle = iframe.getTitle();
					if(command.equals(frameTitle)){
						activeInternalFrame = iframe;
						break;
					}
				}
				blockMainAction = true;
				//         //         setWaitCursor(true);
				try { 
					activeInternalFrame.setSelected(true); 
				} catch (java.beans.PropertyVetoException e2) {
					System.err.println("Non-Fatal exception: " + e2.getMessage());
					e2.printStackTrace();
				}
		        getEditor().moveToFront(activeInternalFrame);
				blockMainAction = false;
				//         setWaitCursor(false);
			}
		}

		@Override
		public void internalFrameOpened(InternalFrameEvent e){}
		@Override
		public void internalFrameClosing(InternalFrameEvent e){}
		@Override
		public void internalFrameClosed(InternalFrameEvent e){
			blockMainAction = false;
			if(e.getSource() instanceof NolInternalFrame){
				NolInternalFrame iframe = (NolInternalFrame)e.getSource();
				removeWindowMenuItem(iframe);
				removeFrameFromListener(iframe);
//				iframe.dispose();
				iframe = null;
				getEditor().repaint(0l);
				getEditor().validate();
			}
		}
		@Override
		public void internalFrameIconified(InternalFrameEvent e){}
		@Override
		public void internalFrameDeiconified(InternalFrameEvent e){}
		@Override
		public void internalFrameActivated(InternalFrameEvent e){
			if(blockMainAction){
				blockMainAction = false;
				return;
			}
			int n = internalFrameStack.size();
			for(int i=0;i<n;i++){
				NolInternalFrame iframe = (NolInternalFrame)internalFrameStack.elementAt(i);
				if(e.getSource().equals(iframe)){
					activeInternalFrame = iframe;
					break;
				}
			}
			refreshWindowMenu();
		}
		@Override
		public void internalFrameDeactivated(InternalFrameEvent e){}
		@Override
		public void LabelCategoryAdded(RawDataEvent e) {
			blockMainAction = true;
			if(DEBUG.debugFlag){
				System.out.println("mainframe label added");
			}
			int lc = project.getNumberOfLabels();
			if(lc==0){
				return;
			}
			if(!labelStatusFire){
				NolLabel[] labels = new NolLabel[lc];
				Vector origLabels = project.getLabels();
				for(int i=0;i<lc;i++){
					NolLabel lab = (NolLabel)origLabels.elementAt(i);
					int index = lab.getLabelOrder();
					labels[index] = lab;
				}
				labelStatus.removeAllItems();
				for(int i=0;i<lc;i++){
					labelStatus.addItem(labels[i].getName());
				}
			}
			blockMainAction = false;
		}

		@Override
		public void LabelCategoryRemoved(RawDataEvent e){
			if(DEBUG.debugFlag){
				System.out.println("mainframe label remove");
			}
			blockMainAction = true;
			int lc = project.getNumberOfLabels();
			if(lc==0){
				labelStatus.removeAllItems();
				projectTree.setProject(); //Gchen 10.1 This should go throught the raw data event
				return;
			}
			if(!labelStatusFire){
				NolLabel[] labels = new NolLabel[lc];
				Vector origLabels = project.getLabels();
				for(int i=0;i<lc;i++){
					NolLabel lab = (NolLabel)origLabels.elementAt(i);
					int index = lab.getLabelOrder();
					labels[index] = lab;
				}
				labelStatus.removeAllItems();
				for(int i=0;i<lc;i++){
					labelStatus.addItem(labels[i].getName());
				}
			}
			blockMainAction = false;
			projectTree.setProject(); //Gchen 10.1 This should go throught the raw data event
		}
		@Override
		public void LabelOrderChanged(RawDataEvent e) {}
		@Override
		public void DataPointsLabeled(RawDataEvent e) {
			setUndo();
		}
		@Override
		public void LabelColorChanged(RawDataEvent e) {}
		@Override
		public void LabelNameChanged(RawDataEvent e) {
			blockMainAction = true;
			int lc = project.getNumberOfLabels();
			if(lc==0){
				return;
			}
			if(!labelStatusFire){
				NolLabel[] labels = new NolLabel[lc];
				Vector origLabels = project.getLabels();
				for(int i=0;i<lc;i++){
					NolLabel lab = (NolLabel)origLabels.elementAt(i);
					int index = lab.getLabelOrder();
					labels[index] = lab;
				}
				labelStatus.removeAllItems();
				for(int i=0;i<lc;i++){
					labelStatus.addItem(labels[i].getName());
				}
			}
			blockMainAction = false;
			NolLabel lab = (NolLabel)e.getEventObject();
			projectTree.changeLabelName(lab,false); //Gchen 10.1 This should go throught the raw data event
		}

		@Override
		public void DataSeriesAdded(RawDataEvent e) {
			if(DEBUG.debugFlag){
				System.out.println("get RawDataEvent DataSeriesAdded update the tree.");
			}
	//		projectTree.addDataSeries(0,project.getDataSeriesNumber(data.getName()));
	//		Temp change the whole tree to get around the dynamic tree bug Gchen 9/9/98
//			projectTree.setProject();	//The  tree shoud be changed by raw data event should 
		}
		@Override
		public void DataSeriesRemoved(RawDataEvent e) {
			projectTree.setProject(); //Gchen 10.1 This should go throught the raw data event
		}

		@Override
		public void DataFileFormatSetted(ProjectEvent e) {
			projectTree.setProject(); //Gchen 10.1 This should go throught the raw data event
		}

		@Override
		public void DataFileFormatRemoved(ProjectEvent e){
			projectTree.setProject(); //Gchen 10.1 This should go throught the raw data event
		}
	}

	public void failLoadProject(String message){
		showOKDialog(message);
		progress.setText("Status: "+ getNolResourceString(CANCELLOADINGPROJECT));
//		"Canceled loading project.");
		progress.validate();
		progress.repaint(0l);
	}

	public void finishOpenProject(Project2 p){
		try {
			Method method = versionManagerClass.getMethod("setProject",new Class[] {p.getClass()});
			method.invoke(versionManager,new Object[] {p});
		} catch (NoSuchMethodException e) {
			// here ONLY when you first launch nolstudio, if demo, then continue
		} catch (IllegalAccessException e) {
			// here ONLY when you first launch nolstudio, if demo, then continue
		} catch (IllegalArgumentException e) {
			// here ONLY when you first launch nolstudio, if demo, then continue
		} catch (InvocationTargetException e) {
			// here ONLY when you first launch nolstudio, if demo, then continue
		} catch (RuntimeException e) {
			// here ONLY when you first launch nolstudio, if demo, then continue
		}
		project = p;
		project.initDataTreeForTransientField();

//project.initializeHardBounds();
		if(DEBUG.debugFlag){
			if(project == null){
				System.out.println("project null");
			}
		}

		progress.setText("Status: "+ getNolResourceString(DONELOADINGPROJECT));
//		progress.setText("Status: Done loading project!");
		actionHoldCount = actionHoldCount-1;
		if(actionHoldCount <=0){
			actionHoldCount = 0;
//			logoButton.setIcon(defaultLogo);
		}

		initializeMenuFlag();
		
		if(project.getRawDataSource().getNumberOfDataSeries()>0)
			menuFlag_hasDataSeries = true;
		if(project.getNumberOfPreprocessors()>0)
			menuFlag_hasPreprocessor = true;
		if(!project.getPredictiveModels().isEmpty())
			menuFlag_hasPredictiveModel = true;
		if(!project.getBpnModels().isEmpty())
			menuFlag_hasBpnModel = true;
		if(!project.getAnnModels().isEmpty())
			menuFlag_hasAnnModel = true;
		if(!project.getRbfnModels().isEmpty())
			menuFlag_hasRbfnModel = true;
		if(!project.getRhoModels().isEmpty())
			menuFlag_hasRhoModel = true;
		
		if(!project.getPlsModels().isEmpty())
			menuFlag_hasPlsModel = true;
		if(!project.getPcaModels().isEmpty())
			menuFlag_hasPcaModel = true;

		if(!project.getOptimizationModels().isEmpty())
			menuFlag_hasOptimizationModel = true;
		if(!project.getLabels().isEmpty())
			menuFlag_hasLabel = true;
		if(!project.getSimulations().isEmpty())
			menuFlag_hasSimulation = true;
		if(!project.getOptimizations().isEmpty())
			menuFlag_hasOptimization = true;

		int lc = project.getNumberOfLabels();
		if(lc!=0){
			if(!labelStatusFire){
				blockMainAction = true;
				NolLabel[] labels = new NolLabel[lc];
				Vector origLabels = project.getLabels();
				for(int i=0;i<lc;i++){
					NolLabel lab = (NolLabel)origLabels.elementAt(i);
					int index = lab.getLabelOrder();
					labels[index] = lab;
				}
				labelStatus.removeAllItems();
				for(int i=0;i<lc;i++){
					labelStatus.addItem(labels[i].getName());
				}
				blockMainAction = false;
			}
		}
		project.getRawDataSource().addListener(mainAction);
		project.getRawDataSource().addListener(projectTree);
		project.addProjectListener(mainAction);

		if(project.getRawDataSource().getSelectStatus()){
			selectStatus.setSelected(false);
		}else{
			selectStatus.setSelected(true);
		}

		projectTree.setProject();
		clearAllInternalFrame();

		defaultProjectName = false;
		modifyDefaultAction();
		mergeCustomFormats();
		progress.validate();
		progress.repaint(0l);
		Toolkit.getDefaultToolkit().beep();
	}

	public void importActionPerformed(){
		
		//Changed for 1.2.2 gchen 2.2.2000
		if (fileChooser == null) {
			fileChooser = new JFileChooser();
		}
		fileChooser.setDialogTitle("Import Data Series");
		NolFileFilter filter0 = new NolFileFilter(
		new String[] {"csv"}, "Excel Text Files"
		);
		NolFileFilter filter1 = new NolFileFilter(
		new String[] {"ds"}, "ASCII Data Series Files"
		);
		NolFileFilter filter2 = new NolFileFilter(
		new String[] {"bds"}, "Binary Data Series Files"
		);
		NolFileFilter filter3 = new NolFileFilter(
		new String[] {"dat"}, "ASCII Data Matrix Files"
		);
		fileChooser.resetChoosableFileFilters();
		fileChooser.addChoosableFileFilter(filter0);
		fileChooser.addChoosableFileFilter(filter1);
		fileChooser.addChoosableFileFilter(filter2);
		fileChooser.addChoosableFileFilter(filter3);
//		fileChooser.setFileFilter(filter1);
		fileChooser.setFileFilter(null);
		fileChooser.setAcceptAllFileFilterUsed(true);
		fileChooser.setDialogType(JFileChooser.OPEN_DIALOG);

		File tmpCurrentDirectory = new File(miscDirectory);
		currentDirectory = tmpCurrentDirectory;
		if(tmpCurrentDirectory.exists()) {
			fileChooser.setCurrentDirectory(tmpCurrentDirectory);
		}

		int retval = fileChooser.showOpenDialog(this);

		fileChooser.setFileFilter(null);
		fileChooser.removeChoosableFileFilter(filter0);
		fileChooser.removeChoosableFileFilter(filter1);
		fileChooser.removeChoosableFileFilter(filter2);
		fileChooser.removeChoosableFileFilter(filter3);

		if(retval == JFileChooser.CANCEL_OPTION){
			return;
		}

		tmpCurrentDirectory = fileChooser.getSelectedFile();
		if(tmpCurrentDirectory == null){
			return;
		}

		String file = tmpCurrentDirectory.getName();
		String selectedMiscDirectory = tmpCurrentDirectory.getParent();

		if(DEBUG.debugFlag){
			System.out.println("file="+file);
			System.out.println("miscDirectory="+selectedMiscDirectory);
		}
 
		File testTheSourceFile = new File(selectedMiscDirectory,file);
		if (!testTheSourceFile.exists() || !testTheSourceFile.isFile())	{
//			showOKDialog("Failed to load dataseries from "+file+". Error:No such file or it is not a valid file.");
			showOKDialog(getNolResourceString(CANNOTLOADDATAFROM)+" "+file+
				getNolResourceString(CANNOTLOADDATAERROR));
			progress.setText("Status: "+ getNolResourceString(CANNOTLOADFILE));
			progress.validate();
			progress.repaint(0l);
			//         setWaitCursor(false);
			return;
		}
					
	//End change for 1.2.2 gchen 2.2.2000

		int dotInd = file.indexOf(".");
		int fflag = 0;
		String suf  = "";
		String dsName  = "";
		if(dotInd != -1){
			suf = file.substring(dotInd);
			dsName = file.substring(0,dotInd);
		} else {
			dsName = new String(file);
		}
		if(project.getRawDataSource().getDataSeries(dsName) != null){		
			showOKDialog(getNolResourceString(SAMENAMEEXISTINGDATA));
//			showOKDialog("Cannot load data series. There is an existing data series with the same name.");
			return;
		}
		if(suf.equals(".ds"))
			fflag = 0;
		else if(suf.equals(".bds"))
			fflag = 1;
		else if(suf.equals(".dat"))
			fflag = 2;
		else{
			fflag = 3;
		}		
		// try to start reading
		Thread loadthread = new Thread(objectLoader);
		int prior = loadthread.getPriority()-3;
		if(prior <Thread.MIN_PRIORITY){
			prior = Thread.MIN_PRIORITY;
		}
		loadthread.setPriority(prior);

		objectLoader.setType(fflag);
		objectLoader.setFileName(file);
		objectLoader.setDirName(selectedMiscDirectory);
		String comment = "";
		if(fflag == 3){
			int fc = project.getNumberOfDataSeriesFileFormat();
			DataSeriesFileFormat format = null;
			if(fc==0){
				getInputWizard().resetData();
				getInputWizard().setFile(selectedMiscDirectory, file);
//				if(!getInputWizard().isOK()) {
//					showOKDialog("File not found");
//					return;
//				}
				getInputWizard().setBounds(100,100,600,440);
				getInputWizard().setVisible(true);
				if(getInputWizard().isOK()){
					format=getInputWizard().getDataSeriesFileFormat();
					if(DEBUG.debugFlag){
						System.out.println("format="+format.toStringForTest());
						System.out.println("format="+format.getName());
					}
					if(!format.getName().equals("")){
						String fmComment=getInputWizard().getDataSeriesFileFormatComment();
						if(fmComment != null)
							format.setComment(fmComment);
						project.setDataSeriesFileFormat(format);
					}
					dsName=getInputWizard().getDataSeriesName();
					comment=getInputWizard().getDataSeriesComment();
				} else return;
			}else{
//				if(showYesNoDialog("Do you want to use an existing format?",2)!=1){
				int result = showYesNoCancelDialog(getNolResourceString(DOUSEEXISTINGFORMAT),2);
//				int result = showYesNoCancelDialog("Do you want to use an existing format?",2);
				if(result == 2){ // NO
					getInputWizard().resetData();
					getInputWizard().setFile(selectedMiscDirectory, file);
					getInputWizard().setBounds(100,100,600,440);
					getInputWizard().setVisible(true);
					if(getInputWizard().isOK()){
						format=getInputWizard().getDataSeriesFileFormat();
						if(DEBUG.debugFlag){
							System.out.println("format="+format.toStringForTest());
						}
						if(!format.getName().equals("")){
							String fmComment=getInputWizard().getDataSeriesFileFormatComment();
							if(fmComment != null)
								format.setComment(fmComment);
							project.setDataSeriesFileFormat(format);
						}
						dsName=getInputWizard().getDataSeriesName();
						comment=getInputWizard().getDataSeriesComment();
					}else{
						return;
					}
				}else if(result == 1){  //YES
					int cf = project.getNumberOfDataSeriesFileFormat();
					Vector formats = project.getDataSeriesFileFormats();
					getSingleChoiceDialog().setContent
						("Select Data Format for "+dsName, "Data Formats:", formats, false);
					getSingleChoiceDialog().pack();
					getSingleChoiceDialog().setBounds(200, 200, 320, 300);
					getSingleChoiceDialog().setVisible(true);
					if(!getSingleChoiceDialog().getResult()){
						return;
					}
					format = (DataSeriesFileFormat)getSingleChoiceDialog().getSelectedItem();
				}else{ // CANCEL
					return;
				}
			}
			if(format == null){
			//	System.out.println("no format");
				return;
			}else{
				objectLoader.setFileFormat(format);
				objectLoader.setObjName(dsName);
				objectLoader.setObjComment(comment);
			}
		}
		progress.setText("Status: "+ getNolResourceString(IMPORTDATA));
//		progress.setText("Status: Importing data series, please wait!");
		progress.validate();
		progress.repaint(0l);
		actionHoldCount = actionHoldCount+1;
		loadthread.start();
	}

	public void finishAddDataSeries(DataSeries data){
		project.addDataSeries(data);
		menuFlag_hasDataSeries = true;
		modifyDefaultAction();
		progress.setText("Status: "+ getNolResourceString(PREPAREDATAWKSP));
//		progress.setText("Status: Preparing data series workspace");
		actionHoldCount = actionHoldCount-1;
		if(actionHoldCount <=0){
			actionHoldCount = 0;
//			logoButton.setIcon(defaultLogo);
		}
		progress.validate();
		progress.repaint(0l);
		showDataSeriesWKSP(data);
		progress.setText("Status: "+ getNolResourceString(DONEIMPORTDATA)+" ["+data.getName()+"]!");
//		progress.setText("Status: Done importing data series ["+data.getName()+"]!");
		Toolkit.getDefaultToolkit().beep();
		checkDataSeriesTimeStamps(data);
    }

	public void failLoadDataSeries(String message){
		showOKDialog(message);
		progress.setText("Status: "+getNolResourceString(CANCELLOADINGDATA));
//		Canceled loading data series!");
		progress.validate();
		progress.repaint(0l);
	}

	public void removeRawDataDataSeries(final DataSeries ds){
		DataSeries datasetBean = ds;
		if(!(datasetBean.getDataSource() instanceof RawDataSource)) {
			// MK changed silent return to OK dialog 5/9/99
//			showOKDialog("To remove this data series, you must delete its source (preprocessor, simulation, etc).");
			showOKDialog(getNolResourceString(MUSTDELETEDATASOURCE));
			return;
		}
		int n = internalFrameStack.size();
		Vector varObjs = datasetBean.getVarObjects();
		NolDataSeriesWKSP dataSeriesWKSP = null;
		boolean inUse = false;
		for(int i=0;i<n;i++){
			NolInternalFrame iframe = (NolInternalFrame)internalFrameStack.elementAt(i);
			if(iframe instanceof NolVariableWKSP ){
				Variable varObj0 = ((NolVariableWKSP)iframe).getVariable();	
				if(varObjs.contains(varObj0)){
					inUse = true;
					break;
				}
			}else if(iframe instanceof NolDataSeriesWKSP ){
				DataSeries oldDs = ((NolDataSeriesWKSP)iframe).getDataSeries();
				if(oldDs.equals(datasetBean) ) {
					dataSeriesWKSP = (NolDataSeriesWKSP)iframe;
				}
			}else if(iframe instanceof NolSpreadsheet ){
				DataSeries oldDs = ((NolSpreadsheet)iframe).getDataSeries();
				if(oldDs.equals(datasetBean)){
					inUse = true;
					break;
				}
			}else if(iframe instanceof NolXYChartFrame ){
				Vector oldVarObjs = ((NolXYChartFrame)iframe).getVariables();	
				for(int j=0;j<oldVarObjs.size();j++){
					Variable var = (Variable)oldVarObjs.elementAt(j);
					if(varObjs.contains(var)){
						inUse = true;
						break;						
					}
				}
				if(inUse)
					break;
			}else if(iframe instanceof NolVarChartFrame ){
				Vector oldVarObjs = ((NolVarChartFrame)iframe).getVariables();	
				for(int j=0;j<oldVarObjs.size();j++){
					Variable var = (Variable)oldVarObjs.elementAt(j);
					if(varObjs.contains(var)){
						inUse = true;
						break;						
					}
				}
				if(inUse)
					break;
			}else if(iframe instanceof NolHistogramFrame ){
				Vector oldVarObjs = ((NolHistogramFrame)iframe).getVariables();	
				for(int j=0;j<oldVarObjs.size();j++){
					Variable var = (Variable)oldVarObjs.elementAt(j);
					if(varObjs.contains(var)){
						inUse = true;
						break;						
					}
				}
				if(inUse)
					break;
			}

		}
		if(inUse){
			// MK improved message 5/7/99
			showOKDialog(getNolResourceString(MUSTCLOSEALLFORTHIS));
//			showOKDialog("You must close all spreadsheet, charts, and workspaces involving this item before it can be deleted.");
			return;
		}


		Vector pdata = project.getProcessedData();
		for(int i=0;i<pdata.size();i++){
			DataSeries oldds = (DataSeries)pdata.elementAt(i);
			if(oldds.getName().equals(datasetBean.getName())){
				inUse = true;
				break;						
			}
		}
		if(inUse){
			showOKDialog(getNolResourceString(CANNOTREMOVEDATA));
//			showOKDialog("Can't remove this data series.  It is required by a preprocessor.");
			return;
		}

		if(showYesNoDialog(getNolResourceString(DODELETEDATA),1)!=1){
			return;						
		}
//		if(showYesNoDialog("Do you wish to delete this data series?",1)!=1) return;						

		RawDataSource rawData = project.getRawDataSource();
		rawData.removeDataSeries(datasetBean);

		if(dataSeriesWKSP !=null){
			try{
				dataSeriesWKSP.setClosed(true);
			}catch(java.beans.PropertyVetoException evt){
				System.err.println("Non-Fatal exception: " + evt.getMessage());
				evt.printStackTrace();
			}
		}
		
		if(rawData.getNumberOfDataSeries() > 0){
			menuFlag_hasDataSeries = true;
		}else{
			menuFlag_hasDataSeries = false;			
		}
		modifyDefaultAction();

		progress.setText("Status: "+getNolResourceString(DATASERIES)+" ["+datasetBean.getName()+"] "+getNolResourceString(ISREMOVED));
		actionHoldCount = actionHoldCount-1;
		if(actionHoldCount <=0){
			actionHoldCount = 0;
		}
		datasetBean = null;
		progress.validate();
		progress.repaint(0l);
		Toolkit.getDefaultToolkit().beep();
    }
    /**Import action implementation.  Made runnable to support wait cursor*/
  class ImportAction extends AbstractAction implements Runnable {
		ImportAction() {super(importAction);}
		@Override
		public void actionPerformed(ActionEvent e) {
			if(blockButtonAction){
				return;
			}
			blockButtonAction = true;
			// handle all actions outside of the main UI thread, otherwise the UI hangs
			new Thread (this).start();
		}
		@Override
		public void run() {
			//         setWaitCursor(true);
			blockButtonAction = false;
			importActionPerformed();
			//         setWaitCursor(false);
		}
	}


    /**Import action implementation	*/
    class ImportG2Action extends AbstractAction implements Runnable {
		ImportG2Action() {super(importG2Action);	}
		@Override
		public void actionPerformed(ActionEvent e) {
			if(blockButtonAction){
				return;
			}
			blockButtonAction = true;
			new Thread (this).start();
		}
		@Override
		public void run() {
			//         setWaitCursor(true);
			blockButtonAction = false;
			importG2ActionPerformed();
			//         setWaitCursor(false);
		}
	}

 	public void importG2ActionPerformed(){
		Vector dataTypes = new Vector();
		Vector displayDataNames = new Vector();
		Vector amatrixFlag = new Vector();
		Vector setFlag = new Vector();
		Vector amatrixDisplayNames = new Vector();
		Vector setDisplayNames = new Vector();
		try{
			Vector dataNames = g2Gateway.getDataSetNamesFromG2();
			Vector amatrixNames = (Vector) dataNames.elementAt(0);
			if (!amatrixNames.isEmpty() ) {
				dataTypes.addElement("NOLS-MATRIX");
				for (int i =0; i< amatrixNames.size() / 2 ;i++){
					amatrixFlag.addElement(amatrixNames.elementAt(i*2));	
					amatrixDisplayNames.addElement(amatrixNames.elementAt(i*2+1));	
				}
				displayDataNames.addElement(amatrixDisplayNames);
			}
			Vector setNames = (Vector) dataNames.elementAt(1);
			if (!setNames.isEmpty()) {
				dataTypes.addElement("GNNE-DATA-SET");
				for (int i =0; i< setNames.size() / 2 ;i++){
					setFlag.addElement(setNames.elementAt(i*2));	
					setDisplayNames.addElement(setNames.elementAt(i*2+1));	
				}
				displayDataNames.addElement(setDisplayNames);
			}
		}catch(Exception e){
			showOKDialog("Wrong URL format.e"+e.toString());
			return;
		}
		if(!dataTypes.isEmpty()){
			getDoubleChoiceDialog().setContent
				("Select Data Series From G2", "Data Type:", "Data Series:",
				dataTypes, displayDataNames, false);
			getDoubleChoiceDialog().pack();
			getDoubleChoiceDialog().setBounds(200, 200, 320, 300);
			getDoubleChoiceDialog().setVisible(true);
		}else{
			showOKDialog("No Data Available in G2 for Importing!");
		}
		if(!getDoubleChoiceDialog().getResult()){
			return;
		}
		String dsName = (String)getDoubleChoiceDialog().getSelectedItem();
		String type = (String)getDoubleChoiceDialog().getChoice1SelectedItem();
		boolean isName = true;
		String flag = "name";
		if ("NOLS-MATRIX".equals(type)){
			int index = amatrixDisplayNames.indexOf(dsName);
			flag = (String)amatrixFlag.elementAt(index);
		}else if("GNNE-DATA-SET".equals(type)){
			int index = setDisplayNames.indexOf(dsName);
			flag = (String)setFlag.elementAt(index);
		}
		if ("name".equals(flag))	{
			isName = true;
		}else if("uuid".equals(flag)){
			isName = false;
		}
		try{ 
			g2Gateway.getDataSetFromG2(type, dsName,isName);
		}catch(Exception e){
			showOKDialog("Wrong URL format.e"+e.toString());
			return;
		}
	}
 	public void importNetActionPerformed(){
		getURLImportDialog().setBounds(200,200,300,100);
		getURLImportDialog().setVisible(true);
		if(!getURLImportDialog().getResult()){
			return;
		}
		
		String urlString = getURLImportDialog().getURL();

		String file = "";
		URL url = null;
		try{
			url = new URL(urlString);
			file = url.getFile();
		}catch(MalformedURLException e){
			showOKDialog(getNolResourceString(WRONGURLFORMAT));
//			showOKDialog("Wrong URL format.");
			return;
		}
		if(DEBUG.debugFlag)
			System.out.println("net file="+ file);

/*		try{
			BufferedReader in = new BufferedReader(
                                new InputStreamReader(url.openStream()));

            String inputLine;

                while ((inputLine = in.readLine()) != null)
                    System.out.println(inputLine);

                in.close();

		}catch(IOException evt){}
  */
		
		int dotInd = file.indexOf(".");
		int fflag = 0;
		String suf  = "";
		String dsName  = "";
		if(dotInd != -1){
			suf = file.substring(dotInd);
			dsName = file.substring(0,dotInd);
		} else {
			dsName = new String(file);
		}
		if(project.getRawDataSource().getDataSeries(dsName) != null){		
//			showOKDialog("Cannot load data series. There is an existing data series with the same name.");
			showOKDialog(getNolResourceString(SAMENAMEEXISTINGDATA));
			return;
		}
		if(suf.equals(".ds"))
			fflag = 20;
		else if(suf.equals(".bds"))
			fflag = 21;
		else if(suf.equals(".dat"))
			fflag = 22;
		else{		
			fflag = 23;
		}		

	// try to start reading
		Thread loadthread = new Thread(objectLoader);
		int prior = loadthread.getPriority()-3;
		if(prior <Thread.MIN_PRIORITY){
			prior = Thread.MIN_PRIORITY;
		}
		loadthread.setPriority(prior);

		objectLoader.setType(fflag);
		objectLoader.setURL(url);
		String comment = "";
		if(fflag == 23){
			int fc = project.getNumberOfDataSeriesFileFormat();
			DataSeriesFileFormat format = null;
			if(fc==0){
				getInputWizard().resetData();
				getInputWizard().setURL(url);
				getInputWizard().setBounds(100,100,600,440);
				getInputWizard().setVisible(true);
				if(getInputWizard().isOK()){
					format=getInputWizard().getDataSeriesFileFormat();
					if(DEBUG.debugFlag){
						System.out.println("format="+format.toStringForTest());
						System.out.println("format="+format.getName());
					}
					if(!format.getName().equals("")){
						String fmComment=getInputWizard().getDataSeriesFileFormatComment();
						if(fmComment != null)
							format.setComment(fmComment);
						project.setDataSeriesFileFormat(format);
					}
					dsName=getInputWizard().getDataSeriesName();
					comment=getInputWizard().getDataSeriesComment();
				} else return;
			}else{
				int result = showYesNoCancelDialog(getNolResourceString(DOUSEEXISTINGFORMAT),2);
//				int result = showYesNoCancelDialog("Do you want to use an existing format?",2);
				if(result == 2){
					getInputWizard().resetData();
					getInputWizard().setURL(url);
					getInputWizard().setBounds(100,100,600,440);
					getInputWizard().setVisible(true);
					if(getInputWizard().isOK()){
						format=getInputWizard().getDataSeriesFileFormat();
						if(DEBUG.debugFlag){
							System.out.println("format="+format.toStringForTest());
						}
						if(!format.getName().equals("")){
							String fmComment=getInputWizard().getDataSeriesFileFormatComment();
							if(fmComment != null)
								format.setComment(fmComment);
							project.setDataSeriesFileFormat(format);
						}
						dsName=getInputWizard().getDataSeriesName();
						comment=getInputWizard().getDataSeriesComment();
					}else{
						return;
					}
				}else if(result == 1){
					int cf = project.getNumberOfDataSeriesFileFormat();
					Vector formats = project.getDataSeriesFileFormats();
					getSingleChoiceDialog().setContent
						("Select Data Format for "+dsName, "Data Formats:", formats, false);
					getSingleChoiceDialog().pack();
					getSingleChoiceDialog().setBounds(200, 200, 320, 300);
					getSingleChoiceDialog().setVisible(true);
					if(!getSingleChoiceDialog().getResult()){
						return;
					}
					format = (DataSeriesFileFormat)getSingleChoiceDialog().getSelectedItem();
				}else{
					return;
				}
			}
			if(format == null){
				System.out.println("no format");
				return;
			}else{
				objectLoader.setFileFormat(format);
				objectLoader.setObjName(dsName);
				objectLoader.setObjComment(comment);
			}
		}
		progress.setText("Status: "+ getNolResourceString(IMPORTDATA));
//		progress.setText("Status: Importing data series, please wait!");
		progress.validate();
		progress.repaint(0l);
		actionHoldCount = actionHoldCount+1;
		loadthread.start();
	}


	/**Create new preprocessor action implementation */
    class NewPreprocessorAction extends AbstractAction implements Runnable {
		NewPreprocessorAction() {	super(newpreprocessorAction);}
		@Override
		public void actionPerformed(ActionEvent e) {
			
			if(blockButtonAction){
				return;
			}
			blockButtonAction = true;
			new Thread (this).start();}
		@Override
		public void run() {
			//         setWaitCursor(true);
			try {
				newpreprocessorActionPerformed();
			} catch (Exception e) {
				System.err.println("Exception: "+e.getMessage());
				e.printStackTrace();
			}
			blockButtonAction = false;
			//         setWaitCursor(false);
		}
    }


   /**Import action implementation	*/
    class ImportNetAction extends AbstractAction implements Runnable {
		ImportNetAction() {super(importNetAction);	}
		@Override
		public void actionPerformed(ActionEvent e) {
			if(blockButtonAction){
				return;
			}
			blockButtonAction = true;
			new Thread (this).start();}
		@Override
		public void run() {
			//         setWaitCursor(true);
			blockButtonAction = false;
			importNetActionPerformed();
			//         setWaitCursor(false);
	   }
	}

	public void appendDataSeries(DataSeries ds){
/*		Frame frame = getFrame();
		if (fileDialog == null) {
			fileDialog = new FileDialog(frame);
		}
		fileDialog.setMode(FileDialog.LOAD);
		fileDialog.setTitle("Append Data Series: "+ds.getName());
		fileDialog.setDirectory(miscDirectory);
		fileDialog.setLocation(200,200);
		fileDialog.show();

		String file = fileDialog.getFile();
		if (file == null) return;
		miscDirectory = fileDialog.getDirectory();

*/		
//Changed for 1.2.2 gchen 2.2.2000
		if (fileChooser == null) {
			fileChooser = new JFileChooser();
		}
		fileChooser.setDialogTitle("Append Data Series: "+ds.getName());
		NolFileFilter filter1 = new NolFileFilter(
		new String[] {"ds"}, "ASCII Data Series Files"
		);
		NolFileFilter filter2 = new NolFileFilter(
		new String[] {"bds"}, "Binary Data Series Files"
		);
		fileChooser.addChoosableFileFilter(filter1);
		fileChooser.addChoosableFileFilter(filter2);
		fileChooser.setFileFilter(filter1);
		fileChooser.setDialogType(JFileChooser.OPEN_DIALOG);
		File tmpCurrentDirectory = new File(miscDirectory);
		currentDirectory = tmpCurrentDirectory;
		if(tmpCurrentDirectory.exists()) {
			fileChooser.setCurrentDirectory(tmpCurrentDirectory);
		}

		int retval = fileChooser.showOpenDialog(this);

		fileChooser.setFileFilter(null);
		fileChooser.removeChoosableFileFilter(filter1);
		fileChooser.removeChoosableFileFilter(filter2);

		if(retval == JFileChooser.CANCEL_OPTION){
			return;
		}

		tmpCurrentDirectory = fileChooser.getSelectedFile();
		if(tmpCurrentDirectory == null){
			return;
		}

		String file = tmpCurrentDirectory.getName();
		String selectedMiscDirectory = tmpCurrentDirectory.getParent();

		if(DEBUG.debugFlag){
			System.out.println("file="+file);
			System.out.println("miscDirectory="+selectedMiscDirectory);
		}

	//End change for 1.2.2 gchen 2.2.2000
		
		int dotInd = file.indexOf(".");
		int fflag = 0;
		String suf  = "";
		String dsName  = "";
		if(dotInd != -1){
			suf = file.substring(dotInd);
			dsName = file.substring(0,dotInd);
		}else{
			dsName = new String(file);
		}
		
		if(suf.equals(".ds"))
			fflag = 0;
		else if(suf.equals(".bds"))
			fflag = 1;
		else if(suf.equals(".dat"))
			fflag = 2;
		else{
			fflag = 3;
		}		

		// try to start reading

		if(objectLoader == null){
			System.out.println("no loader 1");
		}
		Thread loadthread = new Thread(objectLoader);
		int prior = Thread.currentThread().getPriority()-1;
		if(prior <Thread.MIN_PRIORITY) {
			prior = Thread.MIN_PRIORITY;
		}
		loadthread.setPriority(prior);
		
		objectLoader.setType(fflag+10);
		objectLoader.setFileName(file);
		objectLoader.setDirName(selectedMiscDirectory);
		objectLoader.setAppendedDataSeries(ds);
		String comment = "";
		if(fflag == 3){
			int fc = project.getNumberOfDataSeriesFileFormat();
			DataSeriesFileFormat format = null;
			if(fc==0){
				getInputWizard().resetData();
				getInputWizard().setFile(selectedMiscDirectory, file);
				getInputWizard().setBounds(100,100,600,440);
				getInputWizard().setVisible(true);
				if(getInputWizard().isOK()){
					format=getInputWizard().getDataSeriesFileFormat();
					if(DEBUG.debugFlag){
						System.out.println("format="+format.toStringForTest());
					}
					if(!format.getName().equals("")){
						String fmComment=getInputWizard().getDataSeriesFileFormatComment();
						if(fmComment != null)
							format.setComment(fmComment);
						project.setDataSeriesFileFormat(format);
					}
					dsName=getInputWizard().getDataSeriesName();
					comment=getInputWizard().getDataSeriesComment();
				}else{
					return;
				}
			} else {
				int result = showYesNoCancelDialog(getNolResourceString(DOUSEEXISTINGFORMAT),2);
//				int result = showYesNoCancelDialog("Do you want to use an existing format?",2);
//				if(showYesNoDialog("Do you want to use an existing format?",2)!=1){
				if(result == 2){
					getInputWizard().resetData();
					getInputWizard().setFile(selectedMiscDirectory, file);
					getInputWizard().setBounds(100,100,600,440);
					getInputWizard().setVisible(true);
					if(getInputWizard().isOK()){
						format=getInputWizard().getDataSeriesFileFormat();
						if(DEBUG.debugFlag){
							System.out.println("format="+format.toStringForTest());
						}
						if(!format.getName().equals("")){
							String fmComment=getInputWizard().getDataSeriesFileFormatComment();
							if(fmComment != null)
								format.setComment(fmComment);
							project.setDataSeriesFileFormat(format);
						}
						dsName=getInputWizard().getDataSeriesName();
						comment=getInputWizard().getDataSeriesComment();
					}else{
						return;
					}
				}else if(result == 1){
					int cf = project.getNumberOfDataSeriesFileFormat();
					Vector formats = project.getDataSeriesFileFormats();
					getSingleChoiceDialog().setContent
						("Select Data Format", "Data Formats:", formats, false);
					getSingleChoiceDialog().pack();
					getSingleChoiceDialog().setBounds(200, 200, 320, 300);
					getSingleChoiceDialog().setVisible(true);
					if(!getSingleChoiceDialog().getResult()){
						return;
					}
					format = (DataSeriesFileFormat)getSingleChoiceDialog().getSelectedItem();
				}else{
					return;
				}
			}
			if(format.getName()==null || format.getName().equals("")){
				System.out.println("no format");
				return;
			}else{
				objectLoader.setFileFormat(format);
				objectLoader.setObjName(dsName);
				objectLoader.setObjComment(comment);
			}
		}
		progress.setText("Status: "+ getNolResourceString(APPENDDATA));
//		progress.setText("Status: Append data series, please wait!");
		progress.validate();
		progress.repaint(0l);
		actionHoldCount = actionHoldCount+1;
		loadthread.start();

	}

	public void finishAppendDataSeries(DataSeries data){
		actionHoldCount = actionHoldCount-1;
		if(actionHoldCount <=0){
			actionHoldCount = 0;
			logoButton.setIcon(defaultLogo);
		}
		int n = internalFrameStack.size();
		for(int i=0;i<n;i++){
			NolInternalFrame iframe = (NolInternalFrame)internalFrameStack.elementAt(i);
			if(iframe instanceof NolDataSeriesWKSP ){
				DataSeries oldDs = ((NolDataSeriesWKSP)iframe).getDataSeries();
				if(oldDs.equals(data )) {
					NolDataSeriesWKSP dataSeriesWKSP = (NolDataSeriesWKSP)iframe;
					dataSeriesWKSP.initDataDisplay();
					dataSeriesWKSP.updateDataPane();

				}
			}
		}

		progress.setText("Status: "+ getNolResourceString(DONEAPPENDDATA)+" ["+data.getName()+"]!");
//		progress.setText("Status: Done appending data series ["+data.getName()+"]!");
		progress.validate();		
		progress.repaint(0l);
		Toolkit.getDefaultToolkit().beep();
	}


/** Export action implementation  */
    class ExportAction extends AbstractAction implements Runnable {
		ExportAction() {super(exportAction);}
		@Override
		public void actionPerformed(ActionEvent e) {
			if(blockButtonAction){
				return;
			}
			blockButtonAction = true;
			new Thread (this).start();}
        @Override
		public void run() {
			if(project == null || !menuFlag_hasDataSeries){
				blockButtonAction = false;
				return;
			}
			// since the project is not null, there must be data, so let's add it.
			//         setWaitCursor(true);
			blockButtonAction = false;
			DataSeries ds = getSelectedDataSeriesFromChoiceDialog(false);
			if(ds != null) {
				exportActionPerformed(ds);
			}
			//         setWaitCursor(false);
		}
    }
							 
	public void exportActionPerformed(DataSeries ds){
		if (isConnectedWithG2){
			NolDataExportFormatSelectDialog selectDialog = new NolDataExportFormatSelectDialog(this, getNolResourceString("DataSeries_ExportSelection"));
			selectDialog.setBounds(200,200,300,150);
			selectDialog.setVisible(true);
			selectDialog.setFocus();
			if(selectDialog.getResult() == -1) {
				return;
			}
			if(selectDialog.getSelection() == 1){ 

				Vector dataTypes = new Vector();
				Vector displayDataNames = new Vector();
				Vector amatrixFlag = new Vector();
				Vector setFlag = new Vector();
				Vector amatrixDisplayNames = new Vector();
				Vector setDisplayNames = new Vector();
				try{
					Vector dataNames = g2Gateway.getAllNamedDataSetNamesFromG2();
					Vector amatrixNames = (Vector) dataNames.elementAt(0);
					if (!amatrixNames.isEmpty()) {
						dataTypes.addElement("NOLS-MATRIX");
						for (int i =0; i< amatrixNames.size() / 2 ;i++){
							amatrixFlag.addElement(amatrixNames.elementAt(i*2));	
							amatrixDisplayNames.addElement(amatrixNames.elementAt(i*2+1));	
						}
						displayDataNames.addElement(amatrixDisplayNames);
					}
					Vector setNames = (Vector) dataNames.elementAt(1);
					if (!setNames.isEmpty()) {
						dataTypes.addElement("GNNE-DATA-SET");
						for (int i =0; i< setNames.size() / 2 ;i++){
							setFlag.addElement(setNames.elementAt(i*2));	
							setDisplayNames.addElement(setNames.elementAt(i*2+1));	
						}
						displayDataNames.addElement(setDisplayNames);
					}
				}catch(Exception e){
					showOKDialog("Wrong URL format.e"+e.toString());
					return;
				}
				if(!dataTypes.isEmpty()){
					getDoubleChoiceDialog().setContent
						("Select Data Series From G2", "Data Type:", "Data Series:",
						dataTypes, displayDataNames, false);
					getDoubleChoiceDialog().pack();
					getDoubleChoiceDialog().setBounds(200, 200, 320, 300);
					getDoubleChoiceDialog().setVisible(true);
				}else{
					showOKDialog("No Data Object Available in G2 for Exporting!");
				}
				if(!getDoubleChoiceDialog().getResult()){
					return;
				}
				String dsName = (String)getDoubleChoiceDialog().getSelectedItem();
				String type = (String)getDoubleChoiceDialog().getChoice1SelectedItem();
				boolean isName = true;
				String flag = "name";
				if ("NOLS-MATRIX".equals(type)){
					int index = amatrixDisplayNames.indexOf(dsName);
					flag = (String)amatrixFlag.elementAt(index);
				}else if("GNNE-DATA-SET".equals(type)){
					int index = setDisplayNames.indexOf(dsName);
					flag = (String)setFlag.elementAt(index);
				}
				if ("name".equals(flag))	{
					isName = true;
				}else if("uuid".equals(flag)){
					isName = false;
				}

				try{ 
					if ("NOLS-MATRIX".equals(type)){
						g2Gateway.exportDataMatrixToG2(ds, type, dsName,isName);
					}else if("GNNE-DATA-SET".equals(type)){
						NolDataSeriesVarClassificationDialog classificDialog = new NolDataSeriesVarClassificationDialog(this, ds);
						classificDialog.setBounds(200,200,500,500);
						classificDialog.setVisible(true);
						int result = classificDialog.getResult();
						if (result == -1){
							progress.setText("Status: "+getNolResourceString(CANCELLOADINGDATA));
							if(actionHoldCount <=0){
								actionHoldCount = 0;
								logoButton.setIcon(defaultLogo);
							}
							progress.validate();
							progress.repaint(0l);
							Toolkit.getDefaultToolkit().beep();
							return;
						}
						Vector usedNames = classificDialog.getUsedVarNames();
						Vector outputNames = classificDialog.getOutputVarNames();
						g2Gateway.exportDataSetToG2(ds, dsName,isName,usedNames,outputNames);
					}
				}catch(Exception e){
					showOKDialog("Wrong URL format.e"+e.toString());
					return;
				}
				return;
			}
		}
//Changed for 1.2.2 gchen 2.2.2000
		
		if (fileChooser == null) {
			fileChooser = new JFileChooser();
		}
		fileChooser.setDialogTitle("Export Data Series As");
		NolFileFilter filter1 = new NolFileFilter(
			new String[] {"bds"}, "Binary Data Series Files"
		);
		NolFileFilter filter2 = new NolFileFilter(
			new String[] {"ds"}, "Preformated ASCII Files"
		);
		NolFileFilter filter3 = new NolFileFilter(
			new String[] {"csv"}, "Comma Separated ASCII Files"
		);
		NolFileFilter filter4 = new NolFileFilter(
			new String[] {"txt"}, "Tab Separated ASCII Files"
		);
		NolFileFilter filter5 = new NolFileFilter(
			new String[] {"dat"}, "Matrix Data ASCII Files"
		);
		NolFileFilter filter6 = new NolFileFilter(
			new String[] {"set"}, "GNNE Data Set ASCII Files"
		);
		fileChooser.resetChoosableFileFilters();
		fileChooser.addChoosableFileFilter(filter1);
		fileChooser.addChoosableFileFilter(filter2);
		fileChooser.addChoosableFileFilter(filter3);
		fileChooser.addChoosableFileFilter(filter4);
		fileChooser.addChoosableFileFilter(filter5);
		fileChooser.addChoosableFileFilter(filter6);
		fileChooser.setFileFilter(filter1);
		fileChooser.setDialogType(JFileChooser.SAVE_DIALOG);

		File tmpCurrentDirectory = currentDirectory;
		if(tmpCurrentDirectory.exists()) {
			fileChooser.setCurrentDirectory(tmpCurrentDirectory);
		}
		tmpCurrentDirectory = new File(ds.getName()+".bds");
		fileChooser.setSelectedFile(tmpCurrentDirectory);
		

		int retval = fileChooser.showSaveDialog(NolMainFrame.this);

		String defaultExt = ".bds";
		javax.swing.filechooser.FileFilter activeFilter = fileChooser.getFileFilter();
		if (activeFilter != null){
			if (activeFilter.equals(filter2)){
				defaultExt = ".ds";
			}else if (activeFilter.equals(filter3)){
				defaultExt = ".csv";
			}else if (activeFilter.equals(filter4)){
				defaultExt = ".txt";
			}else if (activeFilter.equals(filter5)){
				defaultExt = ".dat";
			}else if (activeFilter.equals(filter6)){
				defaultExt = ".set";
			}
		}				 

		fileChooser.setFileFilter(null);
		fileChooser.removeChoosableFileFilter(filter1);
		fileChooser.removeChoosableFileFilter(filter2);
		fileChooser.removeChoosableFileFilter(filter3);
		fileChooser.removeChoosableFileFilter(filter4);
		fileChooser.removeChoosableFileFilter(filter5);
		fileChooser.removeChoosableFileFilter(filter6);

		if(retval == JFileChooser.CANCEL_OPTION) {
			return;
		}

		tmpCurrentDirectory = fileChooser.getSelectedFile();
		currentDirectory = tmpCurrentDirectory;
		if(tmpCurrentDirectory == null){
			return;
		}

		String file = tmpCurrentDirectory.getName();
		String selectedMiscDirectory = tmpCurrentDirectory.getParent();

		if(DEBUG.debugFlag){
			System.out.println("file="+file);
			System.out.println("miscDirectory="+selectedMiscDirectory);
		}

//Changed for 1.2.2 gchen 2.2.2000
		
		progress.setText("Status: "+ getNolResourceString(SAVEDATA));
//		logoButton.setIcon(runningLogo);
		progress.validate();
		progress.repaint(0l);

	    // try to start writing
		int dotInd = file.indexOf(".");
		int type = 0; // bds=0; ds=1; csv=2; txt=3. 
		if(dotInd == -1){
			file = file+defaultExt;
			if(defaultExt.equals(".bds")){
				type = 0;
			}else if(defaultExt.equals(".ds")){
				type = 1;
			}else if(defaultExt.equals(".csv")){
				type = 2;
			}else if(defaultExt.equals(".txt")){
				type = 3;
			}else if(defaultExt.equals(".dat")){
				type = 4;
			}else if(defaultExt.equals(".set")){
				type = 5;
			}
		}else{
			String suff = file.substring(dotInd);
			if(suff.equals(".ds")){
				type = 1;
			}else if(suff.equals(".bds")){
				type = 0;
			}else if(suff.equals(".csv")){
				type = 2;
			}else if(suff.equals(".txt")){
				type = 3;
			}else if(suff.equals(".dat")){
				type = 4;
			}else if(suff.equals(".set")){
				type = 5;
			}else {
				file = file.substring(0,dotInd)+".bds";
				type = 0;
			}
		}

		if(type == 0){
			VersionManagerForDataSeries versionForData = new VersionManagerForDataSeries();
			versionForData.setDataSeries(ds);
			versionForData.saveToFile(selectedMiscDirectory,file);
		}else if (type == 5){
			NolDataSeriesVarClassificationDialog classificDialog = new NolDataSeriesVarClassificationDialog(this, ds);
			classificDialog.setBounds(200,200,500,500);
			classificDialog.setVisible(true);
			int result = classificDialog.getResult();
			if (result == -1){
				progress.setText("Status: "+getNolResourceString(CANCELLOADINGDATA));
				if(actionHoldCount <=0){
					actionHoldCount = 0;
					logoButton.setIcon(defaultLogo);
				}
				progress.validate();
				progress.repaint(0l);
				Toolkit.getDefaultToolkit().beep();
				return;
			}
			Vector usedNames = classificDialog.getUsedVarNames();
			Vector outputNames = classificDialog.getOutputVarNames();
			ds.saveGNNEDataSet(selectedMiscDirectory,file,usedNames,outputNames);
		}else{
			ds.saveAscii(selectedMiscDirectory,file,type,dateFormat,timeFormat);
		}
		progress.setText("Status: "+ getNolResourceString(DONESAVEDATA));
//		progress.setText("Status: Done outputing data!");
		if(actionHoldCount <=0){
			actionHoldCount = 0;
			logoButton.setIcon(defaultLogo);
		}
		progress.validate();
		progress.repaint(0l);
		Toolkit.getDefaultToolkit().beep();
	}


	public Vector[] classifyInputOutput(DataSeries ds)throws MathException{
		NolDataSeriesVarClassificationDialog classificDialog = new NolDataSeriesVarClassificationDialog(this, ds);
		classificDialog.setBounds(200,200,500,500);
		classificDialog.setVisible(true);
		int result = classificDialog.getResult();
		if (result == -1){
			progress.setText("Status: "+getNolResourceString(CANCELLOADINGDATA));
			if(actionHoldCount <=0){
				actionHoldCount = 0;
				logoButton.setIcon(defaultLogo);
			}
			progress.validate();
			progress.repaint(0l);
			Toolkit.getDefaultToolkit().beep();
			return new Vector[0];
		}
		Vector usedNames = classificDialog.getUsedVarNames();
		Vector outputNames = classificDialog.getOutputVarNames();
		Vector[] results = new Vector[2];
		results[0] = usedNames;
		results[1] = outputNames;
		return results;
	}

    /**Save action implementation */
    class SaveAction extends AbstractAction implements Runnable {
		SaveAction() {	super(saveAction);}
		@Override
		public void actionPerformed(ActionEvent e) {
			
			if(blockButtonAction){
				return;
			}
			blockButtonAction = true;
			new Thread (this).start();}
        @Override
		public void run() {
			if(versionManager==null || isDemoVersion) {
				blockButtonAction = false;
				showOKDialog(getNolResourceString(ACTIONNOTALLOWED));
//				showOKDialog("This action is not allowed without a valid authorization");
				progress.setText("Status: "+getNolResourceString(SAVEABORTED));
//				Save aborted!");
				return;
			}

			//         setWaitCursor(true);
			if(defaultProjectName){
				blockButtonAction = false;
				Action a = getAction(saveasAction);
				ActionEvent evt = new ActionEvent(this, 0,"");
//				a.actionPerformed(evt);
				((SaveasAction)a).run();
				defaultProjectName = false;
			} else {
				progress.setText("Status: "+ getNolResourceString(SAVEPROJECT));
		//		progress.setText("Status: Saving out project, please wait!");
				progress.validate();
				progress.repaint(0l);

				String file = project.getName()+".prj";
				mergeCustomFormats();
				saveProjectActionPerformed(file);
				if(actionHoldCount <=0){
					actionHoldCount = 0;
					logoButton.setIcon(defaultLogo);
				}
				progress.validate();
				progress.repaint(0l);
				blockButtonAction = false;
			}
			//         setWaitCursor(false );
		}
    }

	public void saveProjectActionPerformed(String file){
		// added by Brian O. Bush, May 14, 1999 modify by gchen 5.19
		File origFile = new File(projectDirectory, file);
		File backupFile = new File(projectDirectory, file + "~");
		if(origFile.exists()){
		   	if(backupFile.exists()){
				if(backupFile.delete()){
					origFile.renameTo(backupFile);
				}
			}else{
				origFile.renameTo(backupFile);
			}
		}
		try {
			Method method = versionManagerClass.getMethod("saveToFile",new Class[] {projectDirectory.getClass(), file.getClass()});
			method.invoke(versionManager,new Object[] {projectDirectory,file});
			progress.setText("Status: "+ getNolResourceString(DONESAVEPROJECT));
		} catch (NoSuchMethodException ee) {
			// should never end up here
		} catch (IllegalAccessException ee) {
			// should never end up here
		} catch (IllegalArgumentException ee) {
			// should never end up here
		} catch (InvocationTargetException ee) {
			// should never end up here
		} catch (RuntimeException ee) {
			// should never end up here
		}
    }

	/**
	 * Merge custom formats between project and application settings
	 */
	public void mergeCustomFormats(){
		HashSet<String> customDateFormatsSet = new HashSet<String>();
		customDateFormatsSet.addAll(NolSettings.getSettings().getCustomDateFormatsVector());
		customDateFormatsSet.addAll(getProject().getCustomDateFormats());
		Vector<String> customDateFormats = new Vector<String>(customDateFormatsSet);
		getProject().setCustomDateFormats(customDateFormats);
		NolSettings.getSettings().setCustomDateFormatsVector(customDateFormats);
		
		HashSet<String> customDateTimeFormatsSet = new HashSet<String>();
		customDateTimeFormatsSet.addAll(NolSettings.getSettings().getCustomDateTimeFormatsVector());
		customDateTimeFormatsSet.addAll(getProject().getCustomDateTimeFormats());
		Vector<String> customDateTimeFormats = new Vector<String>(customDateTimeFormatsSet);
		getProject().setCustomDateTimeFormats(customDateTimeFormats);
		NolSettings.getSettings().setCustomDateTimeFormatsVector(customDateTimeFormats);
		
		HashSet<String> customTimeFormatsSet = new HashSet<String>();
		customTimeFormatsSet.addAll(NolSettings.getSettings().getCustomTimeFormatsVector());
		customTimeFormatsSet.addAll(getProject().getCustomTimeFormats());
		Vector<String> customTimeFormats = new Vector<String>(customTimeFormatsSet);
		getProject().setCustomTimeFormats(customTimeFormats);
		NolSettings.getSettings().setCustomTimeFormatsVector(customTimeFormats);
		
		NolSettings.save();
	}

/**Open Actions */
    class NewAction extends AbstractAction implements Runnable {
		NewAction() {super(newAction);}
		@Override
		public void actionPerformed(ActionEvent e) {
			if(blockButtonAction){
				return;
			}
			blockButtonAction = true;
			new Thread (this).start();}
        @Override
		public void run() {
			blockButtonAction = false;
			int nds = project.getRawDataSource().getNumberOfDataSeries();
			if(nds>0){
				int result = showYesNoCancelDialog(getNolResourceString(DOSAVEPROJECT),1);
//				int result = showYesNoCancelDialog("Do you want to save the current project?",1);
				if(result==3){
					return;
				}else if(result==1){
					Action a = getAction(saveasAction);
					ActionEvent evt = new ActionEvent(this, 0,"");
//					a.actionPerformed(evt);
					((SaveasAction)a).run();
				}						
			} else {
				int result = showYesNoDialog(getNolResourceString(DODISCARDPROJECT),1);
				if (result == 2){
					return;
				}
			}
			//         setWaitCursor(true);
			project = new Project2();
			try {
				Method method = versionManagerClass.getMethod("setProject",new Class[] {project.getClass()});
				method.invoke(versionManager,new Object[] {project});
			} catch (NoSuchMethodException e) {
				// no damage if this fails because of lack of authorization, this is just setting a pointer in the version manager class
			} catch (IllegalAccessException e) {
				// no damage if this fails because of lack of authorization, this is just setting a pointer in the version manager class
			} catch (IllegalArgumentException e) {
				// no damage if this fails because of lack of authorization, this is just setting a pointer in the version manager class
			} catch (InvocationTargetException e) {
				// no damage if this fails because of lack of authorization, this is just setting a pointer in the version manager class
			} catch (RuntimeException e) {
				// no damage if this fails because of lack of authorization, this is just setting a pointer in the version manager class
			}
			
			project.getRawDataSource().addListener(mainAction);
			project.getRawDataSource().addListener(projectTree);
			project.addProjectListener(mainAction);
			initializeMenuFlag();
			defaultProjectName = true;
			modifyDefaultAction();
			blockMainAction = true;
			labelStatus.removeAllItems();
			blockMainAction = false;
			projectTree.setProject();
			clearAllInternalFrame();
			progress.setText("Status: "+ getNolResourceString(DONENEWPROJECT));
			progress.validate();
			progress.repaint(0l);
			Toolkit.getDefaultToolkit().beep();
			//         setWaitCursor(false);
		}
	}



/**Open Actions */
    class OpenAction extends AbstractAction implements Runnable {
		OpenAction() {super(openAction);}
		@Override
		public void actionPerformed(ActionEvent e) {
			
			if(blockButtonAction){
				return;
			}
			blockButtonAction = true;
			new Thread (this).start();}
        @Override
		public void run() {
			blockButtonAction = false;
			
			if(!isDemoVersion) {
				int nds = project.getRawDataSource().getNumberOfDataSeries();
				if(nds>0){
					int result = showYesNoCancelDialog(getNolResourceString(DOSAVEPROJECT),1);
	//				int result = showYesNoCancelDialog("Do you want to save the current project?",1);	
					if(result==3){
						return;
					}
					if(result==1){
						Action a = getAction(saveasAction);
						ActionEvent evt = new ActionEvent(this, 0,"");
						((SaveasAction)a).run();
					}						
				}
			}
		//Changed for 1.2.2 gchen 2.2.2000
			if (fileChooser == null) {
				fileChooser = new JFileChooser();
			}
			fileChooser.setDialogTitle("Open New Project");
			NolFileFilter filter1 = new NolFileFilter(
			new String[] {"prj"}, "Binary Project Files"
			);
			fileChooser.addChoosableFileFilter(filter1);
			fileChooser.setFileFilter(filter1);
			if(currentDirectory.exists()) {
				fileChooser.setCurrentDirectory(currentDirectory);
			}
			int retval = fileChooser.showOpenDialog(NolMainFrame.this);
			fileChooser.setFileFilter(null);
			fileChooser.removeChoosableFileFilter(filter1);

			if(retval == JFileChooser.CANCEL_OPTION){
				return;
			}

			File currentDir = fileChooser.getSelectedFile();
			if(currentDir == null) 
				return;

			String file = currentDir.getName();
			projectDirectory = currentDir.getParent();

			if(DEBUG.debugFlag){
				System.out.println("file="+file);
				System.out.println("projectDirectory="+miscDirectory);
			}

		
			progress.setText("Status: "+ getNolResourceString(LOADPROJECT));
			progress.validate();
			progress.repaint(0l);
		    // try to start reading
			int dotInd = file.indexOf(".");
			String projectName;
			if(dotInd == -1) {
				projectName = file;
			} else {
				projectName = file.substring(0,dotInd);
			}

			// make a backup copy of the file to file~ before we load it...
			// by Brian O. Bush, May 13, 1999
/*			String newLine = System.getProperty("line.separator");
			File backupFileName = new File(projectDirectory, (file + "~"));
			FileWriter fw = null;
			FileReader fr = null;
			BufferedReader br = null;
			BufferedWriter bw = null;
            try {
				fr = new FileReader(fileName);
				fw = new FileWriter(backupFileName);
				br = new BufferedReader(fr);
				bw = new BufferedWriter(fw);

				// Determine the size of the buffer to allocate
				int fileLength = (int) fileName.length();
				char charBuff[] = new char[fileLength];
				while (br.read(charBuff,0,fileLength) != -1) {
					bw.write(charBuff,0,fileLength);
				}
			} catch(FileNotFoundException fnfe) {
				System.err.println(file + " does not exist!");
			} catch(IOException ioe) {
				System.err.println("Error reading/writing files!");
			}
            finally {
				try {
					if (br != null)	br.close();
					if (bw != null)	bw.close();
				} catch(IOException ioe){}
			}
*/
			// end backup code
			openProjectActionPerformed(file);
		}
	}

	public void openProjectActionPerformed(String file){
			Thread loadthread = new Thread(objectLoader);
			int prior = loadthread.getPriority()-3;
			if(prior <Thread.MIN_PRIORITY){
				prior = Thread.MIN_PRIORITY;
			}
			loadthread.setPriority(prior);
			objectLoader.setType(100);
			objectLoader.setFileName(file);
			objectLoader.setDirName(projectDirectory);
			actionHoldCount = actionHoldCount+1;
			loadthread.start();
    }
    
	public void removePreprocessor(final Preprocessor prep){
		Preprocessor preprocessorBean = prep;
		int n = internalFrameStack.size();
		NolPreprocessorWKSP preprocessorWKSP = null;
		boolean inUse = false;
		for(int i=0;i<n;i++){
			NolInternalFrame iframe = (NolInternalFrame)internalFrameStack.elementAt(i);
			if(iframe instanceof NolVariableWKSP ){
				Variable varObj0 = ((NolVariableWKSP)iframe).getVariable();	
				if(varObj0.getDataSeries().getDataSource().equals(preprocessorBean)){
					inUse = true;
					break;
				}
			}else if(iframe instanceof NolPreprocessorWKSP ){
				Preprocessor prep0 = ((NolPreprocessorWKSP)iframe).getPreprocessor();
				if(prep0.equals(preprocessorBean)){
					preprocessorWKSP = (NolPreprocessorWKSP)iframe;
				}
			}else if(iframe instanceof NolFormulaListWKSP ){
				Preprocessor prep0 = ((NolFormulaListWKSP)iframe).getPreprocessor();
				if(prep0.equals(preprocessorBean)){
					inUse = true;
					break;
				}
			}else if(iframe instanceof NolDataSeriesWKSP ){
				DataSeries oldDs = ((NolDataSeriesWKSP)iframe).getDataSeries();
				if(oldDs.getDataSource().equals(preprocessorBean)){
					inUse = true;
					break;
				}
			}else if(iframe instanceof NolSpreadsheet ){
				DataSeries oldDs = ((NolSpreadsheet)iframe).getDataSeries();
				if(oldDs.getDataSource().equals(preprocessorBean)){
					inUse = true;
					break;
				}
			}else if(iframe instanceof NolXYChartFrame ){
				Vector oldVarObjs = ((NolXYChartFrame)iframe).getVariables();	
				for(int j=0;j<oldVarObjs.size();j++){
					Variable var = (Variable)oldVarObjs.elementAt(j);
					if(var.getDataSeries().getDataSource().equals(preprocessorBean)){
						inUse = true;
						break;						
					}
				}
				if(inUse)
					break;
			}else if(iframe instanceof NolVarChartFrame ){
				Vector oldVarObjs = ((NolVarChartFrame)iframe).getVariables();	
				for(int j=0;j<oldVarObjs.size();j++){
					Variable var = (Variable)oldVarObjs.elementAt(j);
					if(var.getDataSeries().getDataSource().equals(preprocessorBean)){
						inUse = true;
						break;						
					}
				}
				if(inUse)
					break;
			}else if(iframe instanceof NolHistogramFrame ){
				Vector oldVarObjs = ((NolHistogramFrame)iframe).getVariables();	
				for(int j=0;j<oldVarObjs.size();j++){
					Variable var = (Variable)oldVarObjs.elementAt(j);
					if(var.getDataSeries().getDataSource().equals(preprocessorBean)){
						inUse = true;
						break;						
					}
				}
				if(inUse)
					break;
			}

		}
		if(inUse){
			showOKDialog(getNolResourceString(MUSTCLOSEALLFORTHIS));
//			showOKDialog("You must close all spreadsheet, charts, and workspaces involving this item before it can be deleted.");
			return;
		}

		Vector pmodels = project.getPredictiveModels();
		int np = pmodels.size();
		Vector omodels = project.getOptimizationModels();
		int no = omodels.size();

		for(int i=0;i<pmodels.size();i++){
			NolModel2 model = (NolModel2)pmodels.elementAt(i);
			if(model.getPreprocessor().equals(preprocessorBean)){
				inUse = true;
				break;	
			}
		}
		for(int i=0;i<omodels.size();i++){
			NolModel2 model = (NolModel2)omodels.elementAt(i);
			if(model.getPreprocessor().equals(preprocessorBean)){
				inUse = true;
				break;	
			}
		}
 		if(inUse){
			showOKDialog(getNolResourceString(CANNOTDELETEPREPROCESSOR));
//			showOKDialog("Cannot delete this preprocessor.  It is required by a model.");
			return;
		}
		// If here, the preprocessor can be deleted
		if(showYesNoDialog(getNolResourceString(DODELETEPREPROCESSOR),1)!=1){
			return;
		}
//		if(showYesNoDialog("Do you wish to delete this preprocessor?",1)!=1) return;
//****gchen 11.20		RawDataSource rawData = project.getRawDataSource();
		project.removePreprocessor(preprocessorBean);
		if(preprocessorWKSP !=null){
			try{
				preprocessorWKSP.setClosed(true);
			}catch(java.beans.PropertyVetoException evt){
				System.err.println("Non-Fatal exception: " + evt.getMessage());
				evt.printStackTrace();			
			}
		}
		
		if(project.getNumberOfPreprocessors() > 0){
			menuFlag_hasPreprocessor = true;
		}else{
			menuFlag_hasPreprocessor = false;			
		}
		modifyDefaultAction();

		projectTree.setProject();
		progress.setText("Status: "+getNolResourceString(PREPROCESSOR)+" ["+preprocessorBean.getName()+"] "+getNolResourceString(ISREMOVED));
		actionHoldCount = actionHoldCount-1;
		if(actionHoldCount <=0){
			actionHoldCount = 0;
		}
		preprocessorBean = null;
		progress.validate();
		progress.repaint(0l);
		Toolkit.getDefaultToolkit().beep();
    }

/**Close Actions */
    class CloseAction extends AbstractAction {
		CloseAction() {super(closeAction);}
        @Override
		public void actionPerformed(ActionEvent e) {
			project = new Project2();
			try {
				Method method = versionManagerClass.getMethod("setProject",new Class[] {project.getClass()});
				method.invoke(versionManager,new Object[] {project});
			} catch (NoSuchMethodException ee) {
				// in demo mode, allow new (empty) project to be created to replace old one
			} catch (IllegalAccessException ee) {
				// in demo mode, allow new (empty) project to be created to replace old one
			} catch (IllegalArgumentException ee) {
				// in demo mode, allow new (empty) project to be created to replace old one
			} catch (InvocationTargetException ee) {
				// in demo mode, allow new (empty) project to be created to replace old one
			} catch (RuntimeException ee) {
				// in demo mode, allow new (empty) project to be created to replace old one
			}
			project.getRawDataSource().addListener(mainAction);
			project.getRawDataSource().addListener(projectTree);
			project.addProjectListener(mainAction);
			initializeMenuFlag();
			defaultProjectName = true;
			modifyDefaultAction();
			blockMainAction = true;
			labelStatus.removeAllItems();
			blockMainAction = false;
			projectTree.setProject();
			clearAllInternalFrame();
			progress.setText("Status: "+getNolResourceString(DONECLOSEPROJECT));
			progress.validate();
			progress.repaint(0l);
			Toolkit.getDefaultToolkit().beep();
		}
    }
/**Rename Actions */
    class RenameAction extends AbstractAction {
		RenameAction() {super(renameAction);}
        @Override
		public void actionPerformed(ActionEvent e) {
			renameActionPerformed();
		}
    }
    
	public void renameActionPerformed(){
		NolTextInput dialog = new NolTextInput(getFrame(), ((NolMainFrame)getFrame()).getNolResourceString("newNameTitleLabel"),"");
		dialog.setText(project.getName());
		dialog.setBounds(200,200,300,110);
		dialog.setVisible(true);
		if(!dialog.getResult()){
			return;
		}
		String newName = dialog.getText();
		if (!"".equals(newName)) {
			project.setName(newName);
			projectTree.changeProjectName(newName);	 
		}
	}

/**Save as action implementation 	*/
    class SaveasAction extends AbstractAction implements Runnable {
		SaveasAction() {super(saveasAction);}
		@Override
		public void actionPerformed(ActionEvent e) {
			if(blockButtonAction){
				return;
			}
			blockButtonAction = true;
			new Thread (this).start();
		}
        @Override
		public void run() {
			if(versionManager==null || isDemoVersion) {
				blockButtonAction = false;
				showOKDialog(getNolResourceString(ACTIONNOTALLOWED));
				return;
			}
			if (fileChooser == null) {
				fileChooser = new JFileChooser();
			}
			fileChooser.setDialogTitle("Save Project As");
			NolFileFilter filter1 = new NolFileFilter(
			new String[] {"prj"}, "Binary Project Files"
			);
			fileChooser.addChoosableFileFilter(filter1);
			fileChooser.setFileFilter(filter1);
			fileChooser.setDialogType(JFileChooser.SAVE_DIALOG);

			File tmpCurrentDirectory = new File(projectDirectory);
			fileChooser.setCurrentDirectory(tmpCurrentDirectory);
			fileChooser.setSelectedFile(new File(project.getName()+".prj"));
			int retval = fileChooser.showSaveDialog(NolMainFrame.this);

			fileChooser.setFileFilter(null);
			fileChooser.removeChoosableFileFilter(filter1);

			if(retval == JFileChooser.CANCEL_OPTION){
				blockButtonAction = false;
				return;
			}
			tmpCurrentDirectory = fileChooser.getSelectedFile();
			currentDirectory = tmpCurrentDirectory;
			if(tmpCurrentDirectory == null){
				blockButtonAction = false;
				return;
			}

			String file = tmpCurrentDirectory.getName();
			String selectedProjectDirectory = tmpCurrentDirectory.getParent();
			projectDirectory = selectedProjectDirectory;

			//         setWaitCursor(true);
			progress.setText("Status: "+getNolResourceString(SAVEPROJECT));
			progress.validate();
			progress.repaint(0l);
			mergeCustomFormats();
			// added by Brian O. Bush, May 14, 1999 modify by gchen 5.19
			File origFile = new File(selectedProjectDirectory, file);
			File backupFile = new File(selectedProjectDirectory, file + "~");
		   	if(origFile.exists()){
		   		if(backupFile.exists()){
					if(backupFile.delete()){
						origFile.renameTo(backupFile);
					}
				}else{
					origFile.renameTo(backupFile);
				}
			}
			
		// try to start reading
			int dotInd = file.indexOf(".");
			String pName = new String(file);
			if(dotInd == -1){
				file = file+".prj";
			}
			else pName = pName.substring(0,dotInd);
			project.setName(pName);
			try {
				Method method = versionManagerClass.getMethod("saveToFile",new Class[] {selectedProjectDirectory.getClass(), file.getClass()});
				method.invoke(versionManager,new Object[] {selectedProjectDirectory, file});
			} catch (NoSuchMethodException e) {
				// should never end up here
			} catch (IllegalAccessException ee) {
				// should never end up here
			} catch (IllegalArgumentException e) {
				// should never end up here
			} catch (InvocationTargetException e) {
				// should never end up here
			} catch (RuntimeException e) {
				// should never end up here
			}
			defaultProjectName = false;
			progress.setText("Status: "+getNolResourceString(DONESAVEPROJECT));
			if(actionHoldCount <=0){
				actionHoldCount = 0;
				logoButton.setIcon(defaultLogo);
			}
			progress.validate();
			progress.repaint(0l);
			projectTree.changeProjectName(pName);	 
			blockButtonAction = false;
			//         setWaitCursor(false);
		}
    }


  /** Exit with confirm  */
    class ExitAction extends AbstractAction {
		ExitAction() {super(exitAction);}
        @Override
		public void actionPerformed(ActionEvent e) {
			if(showYesNoDialog(getNolResourceString(EXITSTUDIO),2)!=1){
				return;
			}
			else{
				System.exit(0);
			}
		}
    }

 /** Undo Actions */	
    class UndoAction extends AbstractAction implements Runnable {
		UndoAction() {super(undoAction);}
		@Override
		public void actionPerformed(ActionEvent e) {new Thread (this).start();}
        @Override
		public void run() {
			//         setWaitCursor(true);
			project.getRawDataSource().undoLabeling();
			if(!defaultActions.contains(allCommands.get(redoAction)))
				defaultActions.addElement(allCommands.get(redoAction));
			if(defaultActions.contains(allCommands.get(undoAction)))
				defaultActions.removeElement(allCommands.get(undoAction));
			commands.clear();
			Action[] actions = getActions();
			for (int i = 0; i < actions.length; i++) {
			    Action a = actions[i];
			    commands.put(a.getValue(Action.NAME), a);
			}
			refreshMenu();
			refreshToolbar();
			//         setWaitCursor(false);
		}
	}

   /**Redo Actions */	
    class RedoAction extends AbstractAction implements Runnable {
		RedoAction() {super(redoAction);}
		@Override
		public void actionPerformed(ActionEvent e) {new Thread (this).start();}
        @Override
		public void run() {
			//         setWaitCursor(true);
			project.getRawDataSource().redoLabeling();
			setUndo();
			//         setWaitCursor(false);
		}
	}

	public void setUndo(){
		if(!defaultActions.contains(allCommands.get(undoAction)))
			defaultActions.addElement(allCommands.get(undoAction));
		if(defaultActions.contains(allCommands.get(redoAction)))
			defaultActions.removeElement(allCommands.get(redoAction));
		commands.clear();
		Action[] actions = getActions();
		for (int i = 0; i < actions.length; i++) {
		    Action a = actions[i];
		    commands.put(a.getValue(Action.NAME), a);
		}
		refreshMenu();
		refreshToolbar();
	}

	public void replaceActionPerformed(){
		getReplaceDialog().resetData();
		getReplaceDialog().setVisible(true);
	}

  /** Really lame implementation of an ReplaceAction command */
    class ReplaceAction extends AbstractAction implements Runnable {
		ReplaceAction() {super(replaceAction);}
		@Override
		public void actionPerformed(ActionEvent e) {
			
			if(blockButtonAction){
				return;
			}
			blockButtonAction = true;
			new Thread (this).start();}
        @Override
		public void run() {
//			//         setWaitCursor(true);
			replaceActionPerformed();
			blockButtonAction = false;
//			//         setWaitCursor(false);
		}
    }

	private void labelingActionPerformed(){
 		if(activeInternalFrame == null) {
		    activeInternalFrame = new NolLabelingWKSP(this);
		    activeInternalFrame.setClosable(true);
		    activeInternalFrame.setMaximizable(false);
		    activeInternalFrame.setIconifiable(true);
			activeInternalFrame.setResizable(true);
			interCount++;
			activeInternalFrame.setBounds(20*interCount, 20*interCount, 650, 300);
			if(interCount > 10)
                interCount = 0;
		    getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER);  	
		}else{
			JLayeredPane pane = getEditor();
			Component[] internalFrames = pane.getComponentsInLayer(JLayeredPane.DEFAULT_LAYER.intValue());
			boolean found = false;
			for(int i=0;i<internalFrames.length;i++){
				if(internalFrames[i] instanceof NolLabelingWKSP ){
					activeInternalFrame = (NolLabelingWKSP)internalFrames[i];
					found = true;
					break;
				}
			}
			if(!found){
				activeInternalFrame = new NolLabelingWKSP(this);
				activeInternalFrame.setClosable(true);
				activeInternalFrame.setMaximizable(false);
				activeInternalFrame.setIconifiable(true);
				activeInternalFrame.setResizable(true);
				interCount++;
				activeInternalFrame.setBounds(20*interCount, 20*interCount, 650,300);
				if(interCount > 10)
					interCount = 0;
				getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER); 
			}
		}
        try { 
			activeInternalFrame.setSelected(true); 
		} catch (java.beans.PropertyVetoException e2) {
			System.err.println("Non-Fatal exception: " + e2.getMessage());
			e2.printStackTrace();
		}
        getEditor().moveToFront(activeInternalFrame);
		activeInternalFrame.validate();
		activeInternalFrame.removeInternalFrameListener(mainAction);
		activeInternalFrame.addInternalFrameListener(mainAction);
		addWindowMenuItem(activeInternalFrame);
		progress.setText("Ready:");
		progress.validate();
		progress.repaint(0l);
	}

  /** Using a frame to systematically label data */
    class LabelingAction extends AbstractAction {
		LabelingAction() {super(labelingAction);}
        @Override
		public void actionPerformed(ActionEvent e) {
			labelingActionPerformed();
		}
	}

	public void spreadsheetActionPerformed(){
		if(project == null){
			return;
		}
		// since the project is not null, there must be data, so let's add it.
		if(!menuFlag_hasDataSeries)
			return;
		DataSeries ds = getSelectedDataSeriesFromChoiceDialog(false);
		if(ds != null)
			spreadsheetActionPerformed(ds);
	}


/** Show the spread sheet for one dataseries.*/
	public void spreadsheetActionPerformed(DataSeries ds){
		progress.setText("Status: "+ getNolResourceString(LOADDATAINSPREADSHEET));
//		progress.setText("Status: Loading data into spread sheet, please wait!");
//		logoButton.setIcon(runningLogo);
		progress.validate();
		progress.repaint(0l);
		activeInternalFrame = new NolSpreadsheet(ds);   
		((NolSpreadsheet)activeInternalFrame).getDataModel().setDateFormat(dateFormat);
		((NolSpreadsheet)activeInternalFrame).getDataModel().setTimeFormat(timeFormat);
		activeInternalFrame.setClosable(true);
        activeInternalFrame.setMaximizable(false);
        activeInternalFrame.setIconifiable(true);
        activeInternalFrame.setResizable(true);
        getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER);  
		interCount++;
		activeInternalFrame.setBounds(20*interCount, 20*interCount, 600, 450);
		if(interCount > 10)
               interCount = 0;
        try { 
			activeInternalFrame.setSelected(true); 
		} catch (java.beans.PropertyVetoException e2) {
			System.err.println("Non-Fatal exception: " + e2.getMessage());
			e2.printStackTrace();		
		}
        getEditor().moveToFront(activeInternalFrame);
		activeInternalFrame.addInternalFrameListener(mainAction);
		if(actionHoldCount <=0){
			actionHoldCount = 0;
			logoButton.setIcon(defaultLogo);
		}
		progress.setText("Ready:");
		progress.validate();
		progress.repaint(0l);
		addWindowMenuItem(activeInternalFrame);
  }

  /** Open SpreadSheet action implementation  */
    class SpreadSheetAction extends AbstractAction implements Runnable {
		SpreadSheetAction() {super(spreadsheetAction);}
		@Override
		public void actionPerformed(ActionEvent e) {
			
			if(blockButtonAction){
				return;
			}
			blockButtonAction = true;
			new Thread (this).start();}
		@Override
		public void run() {
			//         setWaitCursor(true);
			spreadsheetActionPerformed();
			blockButtonAction = false;
			//         setWaitCursor(false);
		}
    }

	private DataSeries getSelectedDataSeriesFromChoiceDialog(boolean careForSingleVariable){
		Vector dataSourceNames = new Vector();
		Vector seriesNames = new Vector();
		RawDataSource rds = project.getRawDataSource(); // SOURCE LEVEL - only one data source
		Vector sNames = new Vector();
		for(int j = 0; j < rds.getNumberOfDataSeries(); j++) { // SERIES level
			DataSeries ds = rds.getDataSeries(j);
			if(careForSingleVariable){
				if(ds.getColumn()>1){
					sNames.addElement(ds);
				}
			}else{
				sNames.addElement(ds);
			}
		}
		if(!sNames.isEmpty()){
			dataSourceNames.addElement(rds);
			seriesNames.addElement(sNames);
		}

		// SOURCE: Preprocessors
		for(int i = 0; i < project.getNumberOfPreprocessors(); i++) { // SOURCE LEVEL
			Preprocessor prep = project.getPreprocessorByIndex(i);
			Vector sNames2 = new Vector();
			Vector pds = project.getProcessedDataByPreprocessor(prep);
			if(!pds.isEmpty()){
				for(int j=0;j<pds.size();j++){
					DataSeries ds = (DataSeries)pds.elementAt(j);
					if(careForSingleVariable){
						if(ds.getColumn()>1){
							sNames2.addElement(ds);
						}
					}else{
						sNames2.addElement(ds);
					}
				}
			}
			if(!sNames2.isEmpty()){
				dataSourceNames.addElement(prep);
				seriesNames.addElement(sNames2);
			}
		}

		for(int i = 0; i < project.getNumberOfSimulations(); i++) {
			ResponseSurfaceSimulation sim = project.getSimulation(i);
			Vector sNames3 = new Vector();
			for(int j = 0; j < sim.getNumberOfDataSeries(); j++) { // SERIES level
				DataSeries ds = sim.getDataSeries(j);
				if(careForSingleVariable){
					if(ds.getColumn()>1)
						sNames3.addElement(ds);
				}else{
					sNames3.addElement(ds);
				}
			}
			if(!sNames3.isEmpty()){
				dataSourceNames.addElement(sim);
				seriesNames.addElement(sNames3);
			}
		}

		for(int i = 0; i < project.getNumberOfOptimizations(); i++) {
			NolOptimization opt = project.getOptimization(i);
			Vector oNames3 = new Vector();
			for(int j = 0; j < opt.getNumberOfDataSeries(); j++) { // SERIES level
				DataSeries ds = opt.getDataSeries(j);
				if(careForSingleVariable){
					if(ds.getColumn()>1)
						oNames3.addElement(ds);
				}else{
					oNames3.addElement(ds);
				}
			}
			if(!oNames3.isEmpty()){
				dataSourceNames.addElement(opt);
				seriesNames.addElement(oNames3);
			}
		}

		if(dataSourceNames.isEmpty()) 
			return null;
		getDoubleChoiceDialog().setContent
			("Select Data Series", "Data Source:", "Data Series:",
			dataSourceNames, seriesNames, false);
		getDoubleChoiceDialog().pack();
		getDoubleChoiceDialog().setBounds(200, 200, 320, 300);
		getDoubleChoiceDialog().setVisible(true);
		if(!getDoubleChoiceDialog().getResult()){
			return null;
		}
		return (DataSeries)getDoubleChoiceDialog().getSelectedItem();
	}

	private void prepareVariableSelection(Vector dataSourceNames,
		Vector seriesNames,Vector varNames){

		dataSourceNames.removeAllElements();
		seriesNames.removeAllElements();
		varNames.removeAllElements();

		// SOURCE: Raw Data
		RawDataSource rds = project.getRawDataSource(); // SOURCE LEVEL - only one data source
		dataSourceNames.addElement(rds);
		Vector sNames = new Vector();
		Vector vvNames = new Vector();
		for(int j = 0; j < rds.getNumberOfDataSeries(); j++) { // SERIES level
			DataSeries ds = rds.getDataSeries(j);
			sNames.addElement(ds);
			Vector vNames = new Vector();
			for(int k = 0; k < ds.getColumn(); k++) { // VARIABLE level
				Variable var = ds.getVarByIndex(k);
				vNames.addElement(var);
			}
			vvNames.addElement(vNames);
		}
		varNames.addElement(vvNames);
		seriesNames.addElement(sNames);

		// SOURCE: Preprocessors
		for(int i = 0; i < project.getNumberOfPreprocessors(); i++) { // SOURCE LEVEL
			Preprocessor pre = project.getPreprocessorByIndex(i);
			Vector pds = project.getProcessedDataByPreprocessor(pre);
			if(!pds.isEmpty()){
				Vector sNames2 = new Vector();
				Vector vvNames2 = new Vector();		
				for(int j=0;j<pds.size();j++){
					DataSeries ds = (DataSeries)pds.elementAt(j);
					sNames2.addElement(ds);
					Vector vNames = new Vector();
					for(int k = 0; k < ds.getColumn(); k++) { // VARIABLE level
						Variable var = ds.getVarByIndex(k);
						vNames.addElement(var);
					}
					vvNames2.addElement(vNames);
				}
				varNames.addElement(vvNames2);
				seriesNames.addElement(sNames2);
				dataSourceNames.addElement(pre);
			}
		}

		// SOURCE: Simulations
		for(int i = 0; i < project.getNumberOfSimulations(); i++) {
			ResponseSurfaceSimulation sim = project.getSimulation(i);
			dataSourceNames.addElement(sim);
			Vector sNames3 = new Vector();
			Vector vvNames3 = new Vector();
			for(int j = 0; j < sim.getNumberOfDataSeries(); j++) { // SERIES level
				DataSeries ds = sim.getDataSeries(j);
				sNames3.addElement(ds);
				Vector vNames = new Vector();
				for(int k = 0; k < ds.getColumn(); k++) { // VARIABLE level
					Variable var = ds.getVarByIndex(k);
					vNames.addElement(var);
				}
				vvNames3.addElement(vNames);
			}
			varNames.addElement(vvNames3);
			seriesNames.addElement(sNames3);
		}

		// SOURCE: Optimization
		for(int i = 0; i < project.getNumberOfOptimizations(); i++) {
			NolOptimization opt = project.getOptimization(i);
			dataSourceNames.addElement(opt);
			Vector sNames3 = new Vector();
			Vector vvNames3 = new Vector();
			for(int j = 0; j < opt.getNumberOfDataSeries(); j++) { // SERIES level
				DataSeries ds = opt.getDataSeries(j);
				sNames3.addElement(ds);
				Vector vNames = new Vector();
				for(int k = 0; k < ds.getColumn(); k++) { // VARIABLE level
					Variable var = ds.getVarByIndex(k);
					vNames.addElement(var);
				}
				vvNames3.addElement(vNames);
			}
			varNames.addElement(vvNames3);
			seriesNames.addElement(sNames3);
		}

	}


/** */
	public void lineChartActionPerformed(){
		if(project == null){
			return;
		}
		// since the project is not null, there must be data, so let's add it.
		if(!menuFlag_hasDataSeries)
			return;

		Vector dataSourceNames = new Vector();
		Vector seriesNames = new Vector();
		Vector varNames = new Vector();

		prepareVariableSelection(dataSourceNames,seriesNames,varNames);

		// set the dialog content
		getTripleChoiceDialog().setContent
			("Select Variables", "Data Source:", "Data Series:", "Variable:",
			dataSourceNames, seriesNames, varNames, true);
		getTripleChoiceDialog().pack();
		getTripleChoiceDialog().setBounds(200, 200, 320, 300);
		getTripleChoiceDialog().setVisible(true);

		if(!getTripleChoiceDialog().getResult()){
			this.repaint(0l);
			this.validate();
			return;
		}
		lineChartActionPerformed(getTripleChoiceDialog().getSelectedItems());
	}

	// modified by bbush, 10-8-98
	public void lineChartActionPerformed(Vector varObjects){
		progress.setText("Status: "+ getNolResourceString(LOADDATAINLINECHART));
//		progress.setText("Status: Loading data into line chart, please wait!");
		activeInternalFrame = new NolVarChartFrame(this, varObjects);   
		activeInternalFrame.setClosable(true);
        activeInternalFrame.setMaximizable(false);
        activeInternalFrame.setIconifiable(true);
        activeInternalFrame.setResizable(true);
		getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER);
		activeInternalFrame.setBounds(100, 10, 800,390);
        try { 
			activeInternalFrame.setSelected(true); 
		} catch (java.beans.PropertyVetoException e2) {
			System.err.println("Non-Fatal exception: " + e2.getMessage());
			e2.printStackTrace();		
		}
        getEditor().moveToFront(activeInternalFrame);
		interCount++;
		activeInternalFrame.setBounds(20*interCount, 20*interCount, 700,400);
		if(interCount > 10)
            interCount = 0;
		activeInternalFrame.validate();
		activeInternalFrame.addInternalFrameListener(mainAction);

		if(actionHoldCount <=0){
			actionHoldCount = 0;
			logoButton.setIcon(defaultLogo);
		}
		progress.setText("Ready:");
		progress.validate();
		progress.repaint(0l);
		addWindowMenuItem(activeInternalFrame);
	}

    /**Open line chart action implementation */  
    class LineChartAction extends AbstractAction implements Runnable {
		LineChartAction() {	super(linechartAction);	}
		@Override
		public void actionPerformed(ActionEvent e) {
			
			if(blockButtonAction){
				return;
			}
			blockButtonAction = true;
			new Thread (this).start();}
        @Override
		public void run() {
			//         setWaitCursor(true);
			lineChartActionPerformed();
			blockButtonAction = false;
			//         setWaitCursor(false);
		}
    }

 	public void xymapActionPerformed(){
		if(project == null) {
			return;
		}
		// since the project is not null, there must be data, so let's add it.
		if(!menuFlag_hasDataSeries)
			return;
		Vector dataSourceNames = new Vector();
		Vector seriesNames = new Vector();
		Vector varNames = new Vector();

		prepareVariableSelection(dataSourceNames,seriesNames,varNames);

		// set the dialog content
		getXYChoiceDialog().setContent
			("Select Variables", "Data Source:", "Data Series:", "Variable:",
			dataSourceNames, seriesNames, varNames, 
			dataSourceNames, seriesNames, varNames, 
			false);

		getXYChoiceDialog().pack();
		getXYChoiceDialog().setBounds(200, 200, 520, 300);
		getXYChoiceDialog().setVisible(true);

		if(!getXYChoiceDialog().getResult()){
			return;
		}
		xymapActionPerformed((Variable)getXYChoiceDialog().getXSelectedItem(), (Variable)getXYChoiceDialog().getYSelectedItem());
	}

 	public void xymapActionPerformed(Variable varObj1, Variable varObj2){
		progress.setText("Status: "+ getNolResourceString(LOADDATAINXYCHART));
//		progress.setText("Status: Loading data into X-Y chart, please wait!");

		DataSeries ds1 = varObj1.getDataSeries();
		DataSeries ds2 = varObj2.getDataSeries();
		if(ds1.getRow() != ds2.getRow()) {
			String title1 = "\"" + varObj1.getDataSource().getName() + "." + ds1.getName() + "." + varObj1.getName() + "\"";
			String title2 = "\"" + varObj2.getDataSource().getName() + "." + ds2.getName() + "." + varObj2.getName() + "\"" ;
			String label = "Variables: " + title1 + " and " + title2 + "are not of equal length!";
			showOKDialog(label);
			return;
		}
		activeInternalFrame = new NolXYChartFrame(this, varObj1, varObj2);   
		activeInternalFrame.setClosable(true);
        activeInternalFrame.setMaximizable(false);
        activeInternalFrame.setIconifiable(true);
        activeInternalFrame.setResizable(true);
		getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER);
		activeInternalFrame.setBounds(100, 10, 600,390);
        try { 
			activeInternalFrame.setSelected(true); 
		} catch (java.beans.PropertyVetoException e2) {
			System.err.println("Non-Fatal exception: " + e2.getMessage());
			e2.printStackTrace();		
		}
        getEditor().moveToFront(activeInternalFrame);
		interCount++;
		activeInternalFrame.setBounds(20*interCount, 20*interCount, 600,400);
		if(interCount > 10)
            interCount = 0;
		activeInternalFrame.validate();
		activeInternalFrame.addInternalFrameListener(mainAction);

		if(actionHoldCount <=0){
			actionHoldCount = 0;
			logoButton.setIcon(defaultLogo);
		}
		progress.setText("Ready:");
		progress.validate();
		progress.repaint(0l);
		addWindowMenuItem(activeInternalFrame);

	}

    /**Open xy chart action implementation	*/
    class XYMapAction extends AbstractAction implements Runnable {
		XYMapAction() {super(xymapAction);}
		@Override
		public void actionPerformed(ActionEvent e) {
			
			if(blockButtonAction){
				return;
			}
			blockButtonAction = true;
			new Thread (this).start();}
        @Override
		public void run() {
			//         setWaitCursor(true);
			xymapActionPerformed();
			blockButtonAction = false;
			//         setWaitCursor(false);
		}
    }
									 
 	public void projectmapActionPerformed(){
		if(project == null){
			return;
		}
		// since the project is not null, there must be data, so let's add it.
		if(!menuFlag_hasDataSeries){
			return;
		}
		DataSeries ds = getSelectedDataSeriesFromChoiceDialog(true);
		if (ds==null){
			return;
		}
		if(ds.getColumn() > 1){
			projectmapActionPerformed(ds);
		}else {
			showOKDialog(getNolResourceString(CANNOTDISPLYPROJECTION));
		}
//		else showOKDialog("Cannot display Projection Plot: Not enough variables.");
	}

 	public void projectmapActionPerformed(DataSeries ds) {
		progress.setText("Status: "+ getNolResourceString(LOADDATAINPROJECTCHART));
//		progress.setText("Status: Loading data into projection chart, please wait!");
		try {
			activeInternalFrame = new NolProjectionChartFrame(this,ds); 
		} catch (ProjectionException pe) {
			showOKDialog(pe.getMessage());
			progress.setText("Ready:");
			return;
		} catch (MathException me){
			System.err.println("Exception: "+me.getMessage());
			me.printStackTrace();
		}
        activeInternalFrame.setClosable(true);
        activeInternalFrame.setMaximizable(false);
        activeInternalFrame.setIconifiable(true);
        activeInternalFrame.setResizable(true);
		getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER);
		activeInternalFrame.setBounds(50, 10, 640,440);
        try { 
			activeInternalFrame.setSelected(true); 
		} catch (java.beans.PropertyVetoException e2) {
			System.err.println("Non-Fatal exception: " + e2.getMessage());
			e2.printStackTrace();		
		}
        getEditor().moveToFront(activeInternalFrame);
		activeInternalFrame.setBounds(50, 10, 660,480);
		activeInternalFrame.validate();
		activeInternalFrame.addInternalFrameListener(mainAction);

		if(actionHoldCount <=0){
			actionHoldCount = 0;
			logoButton.setIcon(defaultLogo);
		}
		progress.setText("Ready:");
		progress.validate();
		progress.repaint(0l);
		addWindowMenuItem(activeInternalFrame);
	}

    /**Open chart action implementation	*/
    class ProjectmapAction extends AbstractAction implements Runnable {
		ProjectmapAction() {super(projectmapAction);}
        @Override
		public void actionPerformed(ActionEvent e) {
			
			if(blockButtonAction){
				return;
			}
			blockButtonAction = true;
			new Thread (this).start();}
		@Override
		public void run () {
			//         setWaitCursor(true);
			projectmapActionPerformed();
			blockButtonAction = false;
			//         setWaitCursor(false);
		}
    }

   	public void histogramActionPerformed(){
		if(project == null || !menuFlag_hasDataSeries) {
			return;
		}
		// since the project is not null, there must be data, so let's add it.
		Vector dataSourceNames = new Vector();
		Vector seriesNames = new Vector();
		Vector varNames = new Vector();
		prepareVariableSelection(dataSourceNames,seriesNames,varNames);
		// set the dialog content
		getTripleChoiceDialog().setContent
			("Select Variables", "Data Source:", "Data Series:", "Variable:",
			dataSourceNames, seriesNames, varNames, false);
		getTripleChoiceDialog().pack();
		getTripleChoiceDialog().setBounds(200, 200, 320, 300);
		getTripleChoiceDialog().setVisible(true);

		if(!getTripleChoiceDialog().getResult()){
			this.repaint(0l);
			this.validate();
			return;
		}
		histogramActionPerformed((Variable)getTripleChoiceDialog().getSelectedItem());
	}

	public void histogramActionPerformed(Variable varObj){

		activeInternalFrame = new NolHistogramFrame(this,varObj);   
		activeInternalFrame.setClosable(true);
		activeInternalFrame.setMaximizable(false);
		activeInternalFrame.setIconifiable(true);
		activeInternalFrame.setResizable(true);
		interCount++;
		int h = 380;
		int w = 600;
		activeInternalFrame.setBounds(20*interCount, 20*interCount, w, h);
		int prevousCount = interCount;
		if(interCount > 10)
			interCount = 0;
		getEditor().add(activeInternalFrame, JLayeredPane.DEFAULT_LAYER);  
        try { 
			activeInternalFrame.setSelected(true); 
		} catch (java.beans.PropertyVetoException e2) {
			System.err.println("Non-Fatal exception: " + e2.getMessage());
			e2.printStackTrace();		
		}
        getEditor().moveToFront(activeInternalFrame);
		activeInternalFrame.addInternalFrameListener(mainAction);
		activeInternalFrame.setBounds(20*prevousCount, 20*prevousCount, w+1, h+1);
		activeInternalFrame.validate();
		activeInternalFrame.setBounds(20*prevousCount, 20*prevousCount, w, h);

		if(actionHoldCount <=0){
			actionHoldCount = 0;
			logoButton.setIcon(defaultLogo);
		}
		progress.setText("Ready:");
		progress.validate();
		progress.repaint(0l);
		addWindowMenuItem(activeInternalFrame);					
	}

  /**Open histogram action implementation */
    class HistogramAction extends AbstractAction implements Runnable {
		HistogramAction() {super(histogramAction);}
		@Override
		public void actionPerformed(ActionEvent e) {
			
			if(blockButtonAction) {
				return;
			}
			blockButtonAction = true;
			new Thread (this).start();}
        @Override
		public void run() {
			//         setWaitCursor(true);
			histogramActionPerformed();
			blockButtonAction = false;
			//         setWaitCursor(false);
		}
    }

/** Performance the create new label action.	*/
 	public void newlabelActionPerformed(){
		if(project == null){
			return;
		}
		getNewLabelWizard().refresh();
		getNewLabelWizard().setVisible(true);
		getNewLabelWizard().setFocus();
		if(getNewLabelWizard().isOK()){
			String labelName = getNewLabelWizard().getLabelName();
			String comment = getNewLabelWizard().getLabelComment();
			Color labelColor = getNewLabelWizard().getLabelColor();
			if(DEBUG.debugFlag){
				System.out.println("newlabelActionPerformed labelName="+labelName);
			}
			if(labelName.equals("")){
				return;
			}
			if(project.getLabelIndex(labelName)<0){
				if(DEBUG.debugFlag){
					System.out.println("newlabelActionPerformed="+project.getLabelIndex(labelName));
				}
				project.addLabelCategory(labelName,comment,labelColor);
				NolLabel lab = project.getLabel(project.getLabelIndex(labelName));
				projectTree.addLabel(lab,true); //Changed for dynamic display gchen 2.29.2002
			}
			menuFlag_hasLabel = true;
			modifyDefaultAction();
		}
	}

    /**New label action implementation */
    class NewLabelAction extends AbstractAction implements Runnable {
		NewLabelAction() {super(newlabelAction);}
		@Override
		public void actionPerformed(ActionEvent e) {
			
			if(blockButtonAction){
				return;
			}
			blockButtonAction = true;
			new Thread (this).start();}
        @Override
		public void run() {
			//         setWaitCursor(true);
			newlabelActionPerformed();
			blockButtonAction = false;
			//         setWaitCursor(false);
		}
    }

     /**Import action implementation	*/
    class NewDataSeriesAction extends AbstractAction implements Runnable {
		NewDataSeriesAction() {super(newdataseriesAction);	}
		@Override
		public void actionPerformed(ActionEvent e) {
			
			if(blockButtonAction){
				return;
			}
			blockButtonAction = true;
			new Thread (this).start();}
		@Override
		public void run() {
			//         setWaitCursor(true);
			blockButtonAction = false;
			importActionPerformed();
			//         setWaitCursor(false);
	   }
	}


	public void removeLabel(final NolLabel lab){
		NolLabel labelBean = lab;
		int n = internalFrameStack.size();
		NolLabelWKSP labelWKSP = null;
		for(int i=0;i<n;i++){
			NolInternalFrame iframe = (NolInternalFrame)internalFrameStack.elementAt(i);
			if(iframe instanceof NolLabelWKSP ){
				NolLabel lab0 = ((NolLabelWKSP)iframe).getLabel();
				if(lab0.equals(labelBean)){
					labelWKSP=(NolLabelWKSP)iframe;
				}
			}
		}
		boolean inUse = false;
		int pc = project.getNumberOfPreprocessors();
//		if(pc>0) inUse = true; //Temp gchen 10/18/98
		for(int i=0;i<pc;i++){
			Preprocessor prep = project.getPreprocessorByIndex(i);
			if(prep.getViewFilter().hasLabel(labelBean)){				
				inUse = true;
				break;
			}
		}
		if(inUse){
			showOKDialog(getNolResourceString(CANNOTDELETELABEL));
//			showOKDialog("Can't delete this label.  It is in use.");
			return;
		}
		if(showYesNoDialog(getNolResourceString(DODELETELABEL),1)!=1){
			return;
		}
//		if(showYesNoDialog("Do you wish to delete this label?",1)!=1) return;
		if(labelWKSP !=null){
			try{
				labelWKSP.setClosed(true);
			} catch(java.beans.PropertyVetoException evt){
				System.err.println("Non-Fatal exception: " + evt.getMessage());
				evt.printStackTrace();			
			}
		}
		
		project.removeLabelCategory(labelBean);
		if(!project.getLabels().isEmpty()){
			menuFlag_hasLabel = true;
		}else{
			menuFlag_hasLabel = false;			
		}
		modifyDefaultAction();

		progress.setText("Status: "+getNolResourceString(LABEL)+" ["+labelBean.getName()+"] "+getNolResourceString(ISREMOVED));
//		progress.setText("Status: Label ["+lab.getName()+"] is removed!");
		labelBean = null;
		progress.validate();
		progress.repaint(0l);
		Toolkit.getDefaultToolkit().beep();
	}

	public void newpreprocessorActionPerformed() throws MathException {
		int nds = project.getRawDataSource().getNumberOfDataSeries();
		if(nds<=0){	
			showOKDialog(getNolResourceString(MUSTSELECTDATA));
			return;
		}
		getNewPreprocessorWizard().setBounds(200, 200, 500,500);
		getNewPreprocessorWizard().resetData();
		getNewPreprocessorWizard().setVisible(true);

		Preprocessor preprocessor = null;
		if(getNewPreprocessorWizard().isOK()){
			if(DEBUG.debugFlag){
				System.out.println("now create new preprocessor "+getNewPreprocessorWizard().isOK());
			}
			preprocessor = getNewPreprocessorWizard().getPreprocessor();
			progress.setText("Status: "+ getNolResourceString(DONENEWPREPROCESSOR));
//Changed for dynamic display Gchen 5.29.2002
			projectTree.addPreprocessor(preprocessor,true);
			menuFlag_hasPreprocessor = true;
		}else {
			progress.setText("Status: "+ getNolResourceString(CANCELNEWPREPROCESSOR));
			Toolkit.getDefaultToolkit().beep();
			return;
		}
		modifyDefaultAction();
		progress.validate();
		progress.repaint(0l);
		if(preprocessor != null)
			showPreprocessorWKSP(preprocessor);
		Toolkit.getDefaultToolkit().beep();
	}
	
	public void removeClassicModel(final NolModel2 model){
		int n = internalFrameStack.size();
		NolInternalFrame modelWKSP = null;
		boolean inUse = false;
		Vector sims = project.getSimulations();
		for(int i=0;i<sims.size();i++){
			ResponseSurfaceSimulation sim = (ResponseSurfaceSimulation)sims.elementAt(i);
			if(sim.getModel().equals(model)){
				inUse = true;
				break;						
			}
		}
		if(inUse){
			showOKDialog(getNolResourceString(CANNOTREMOVEMODELWITHSIMULATION));
			return;
		}

		if(showYesNoDialog(getNolResourceString(DODELETEMODEL),1)!=1){
			return;
		}

		for(int i=0;i<n;i++){
			NolInternalFrame iframe = (NolInternalFrame)internalFrameStack.elementAt(i);
			if(iframe instanceof NolClassicModelWKSP ){
				NolModel2 model0 = ((NolClassicModelWKSP)iframe).getModel();
				if(model0.equals(model)) {
					modelWKSP = (NolInternalFrame)iframe;
				}
			}
			if(iframe instanceof NolRhoModelWKSP ){
				NolModel2 model0 = ((NolRhoModelWKSP)iframe).getModel();
				if(model0.equals(model)) {
					modelWKSP = (NolInternalFrame)iframe;
				}
			}
		}
		if(modelWKSP !=null){
			try{
				modelWKSP.setClosed(true);
			}catch(java.beans.PropertyVetoException evt){
				System.err.println("Non-Fatal exception: " + evt.getMessage());
				evt.printStackTrace();
			}
		}

		if(model instanceof NolAnnModel){
			project.deleteAnnModel((NolAnnModel)model);
		}else if(model instanceof NolBpnModel){
			project.deleteBpnModel((NolBpnModel)model);
		}else if(model instanceof NolRhoModel){
			project.deleteRhoModel((NolRhoModel)model);
		}else if(model instanceof NolRbfnModel){
			project.deleteRbfnModel((NolRbfnModel)model);
		}
		
		if(!project.getBpnModels().isEmpty()){
			menuFlag_hasBpnModel = true;
		}else{
			menuFlag_hasBpnModel = false;			
		}
		if(!project.getAnnModels().isEmpty()){
			menuFlag_hasAnnModel = true;
		}else{
			menuFlag_hasAnnModel = false;
		}
		if(!project.getRbfnModels().isEmpty()){
			menuFlag_hasRbfnModel = true;
		}else{
			menuFlag_hasRbfnModel = false;
		}
		if(!project.getRhoModels().isEmpty()){
			menuFlag_hasRhoModel = true;
		}else{
			menuFlag_hasRhoModel = false;
		}
		modifyDefaultAction();

		projectTree.setProject();
		progress.setText("Status: "+getNolResourceString(PREMODEL)+" ["+model.getName()+"] "+getNolResourceString(ISREMOVED));
//		progress.setText("Status: Predictive model ["+model.getName()+"] is removed!");
		actionHoldCount = actionHoldCount-1;
		if(actionHoldCount <=0){
			actionHoldCount = 0;
//			logoButton.setIcon(defaultLogo);
		}
		progress.validate();
		progress.repaint(0l);
		Toolkit.getDefaultToolkit().beep();
	}

	public void removeModel(final NolModel2 model){
		NolModel2 modelBean = model;
		if(modelBean instanceof ClassicModel){
			removeClassicModel(modelBean);
			return;
		}

		if(DEBUG.debugFlag){
			System.out.println("removeModel");
		}
		int n = internalFrameStack.size();
		NolInternalFrame modelWKSP = null;
		boolean inUse = false;
		for(int i=0;i<n;i++){
			NolInternalFrame iframe = (NolInternalFrame)internalFrameStack.elementAt(i);
			if(iframe instanceof NolModelWKSP ){
				NolModel2 model0 = ((NolModelWKSP)iframe).getModel();
				if(model0.equals(modelBean )) {
					modelWKSP = iframe;
				}
			}else if(iframe instanceof NolPlsModelWKSP ){
				NolModel2 model0 = ((NolPlsModelWKSP)iframe).getModel();
				if(model0.equals(modelBean) ) {
					modelWKSP = iframe;
				}
			}else if(iframe instanceof NolPcaModelWKSP ){
				NolModel2 model0 = ((NolPcaModelWKSP)iframe).getModel();
				if(model0.equals(modelBean) ) {
					modelWKSP = iframe;
				}
			}
		}
		if(DEBUG.debugFlag){
			if(modelWKSP == null) {
				System.out.println("not find modelWKSP");
			}else {
				System.out.println("find modelWKSP");
			}
		}
		Vector sims = project.getSimulations();
		for(int i=0;i<sims.size();i++){
			ResponseSurfaceSimulation sim = (ResponseSurfaceSimulation)sims.elementAt(i);
			if(sim.getModel().equals(modelBean)){
				inUse = true;
				break;						
			}
		}
		if(inUse){
			showOKDialog(getNolResourceString(CANNOTREMOVEMODELWITHSIMULATION));
//			showOKDialog("Can't remove this model.  It is required by a simulation.");
			return;
		}

		Vector opts = project.getOptimizations();
		for(int i=0;i<opts.size();i++){
			NolOptimization opt = (NolOptimization)opts.elementAt(i);
			if(opt.getModel().equals(modelBean)){
				inUse = true;
				break;						
			}
		}
		if(inUse){
			showOKDialog(getNolResourceString(CANNOTREMOVEMODELWITHOPTIMIZATION));
//			showOKDialog("Can't remove this model.  It is required by an optimization.");
			return;
		}

		if(showYesNoDialog(getNolResourceString(DODELETEMODEL),1)!=1) {
			return;
		}
//		if(showYesNoDialog("Do you wish to delete this model?",1)!=1) return;

		if(modelWKSP !=null){
			try{
				modelWKSP.setClosed(true);
			}catch(java.beans.PropertyVetoException evt){
				System.err.println("Non-Fatal exception: " + evt.getMessage());
				evt.printStackTrace();
			}
		}

		if(modelBean instanceof NolOptimizeModel){
			project.deleteOptimizationModel((NolOptimizeModel)modelBean);
		}else if(modelBean instanceof NolPlsModel){
			project.deletePlsModel((NolPlsModel)modelBean);
		}else if(modelBean instanceof NolPcaModel){
			project.deletePcaModel((NolPcaModel)modelBean);
		}else{
			project.deletePredictiveModel(modelBean);
		}
		
		if(!project.getPredictiveModels().isEmpty()){
			menuFlag_hasPredictiveModel = true;
		}else{
			menuFlag_hasPredictiveModel = false;			
		}

		if(!project.getBpnModels().isEmpty()){
			menuFlag_hasBpnModel = true;
		}else{
			menuFlag_hasBpnModel = false;			
		}
		if(!project.getAnnModels().isEmpty()){
			menuFlag_hasAnnModel = true;
		}else{
			menuFlag_hasAnnModel = false;			
		}
		if(!project.getRbfnModels().isEmpty()){
			menuFlag_hasRbfnModel = true;
		}else{
			menuFlag_hasRbfnModel = false;			
		}
		if(!project.getRhoModels().isEmpty()){
			menuFlag_hasRhoModel = true;
		}else{
			menuFlag_hasRhoModel = false;			
		}
		
		if(!project.getPlsModels().isEmpty()){
			menuFlag_hasPlsModel = true;
		}else{
			menuFlag_hasPlsModel = false;			
		}

		if(!project.getPcaModels().isEmpty()){
			menuFlag_hasPcaModel = true;
		}else{
			menuFlag_hasPcaModel = false;			
		}

		if(!project.getOptimizationModels().isEmpty()){
			menuFlag_hasOptimizationModel = true;
		}else{
			menuFlag_hasOptimizationModel = false;
		}
		modifyDefaultAction();

		projectTree.setProject();
		progress.setText("Status: "+getNolResourceString(PREMODEL)+" ["+modelBean.getName()+"] "+getNolResourceString(ISREMOVED));
//		progress.setText("Status: Predictive model ["+model.getName()+"] is removed!");
		actionHoldCount = actionHoldCount-1;
		if(actionHoldCount <=0){
			actionHoldCount = 0;
//			logoButton.setIcon(defaultLogo);
		}
		modelBean = null;
		progress.validate();
		progress.repaint(0l);
		Toolkit.getDefaultToolkit().beep();
	}

	public void newpredictmodelActionPerformed(){
		int nc = project.getNumberOfPreprocessors();
		if(nc<=0){	
			showOKDialog(getNolResourceString(NOPREPROCESSORFORMODEL));
//			showOKDialog("No preprocessor to create model!");
			return;
		}
		getNewPredictiveModelWizard().setBounds(200, 200, 470, 400);
		getNewPredictiveModelWizard().resetData();
		getNewPredictiveModelWizard().setVisible(true);

		if(getNewPredictiveModelWizard().isOK()){
			NolModel2 model = getNewPredictiveModelWizard().getModel();
			if(model != null){
				project.addPredictiveModel(model);
				projectTree.addPredictiveModel(model,true);	  //Changed for dynamic display Gchen 2.29.2002
				menuFlag_hasPredictiveModel = true;
				getTrainDialog().setModel(model);
				getTrainDialog().setVisible(true);				
			}
//			else{  inform the null situation.!!!!!!!!!
		}
		modifyDefaultAction();
		progress.validate();
		progress.repaint(0l);
		this.validate();
		Toolkit.getDefaultToolkit().beep();
	}
	/**Create new predict model  action implementation 	 */
    class NewPredictModelAction extends AbstractAction implements Runnable {
		NewPredictModelAction() {	super(newpredictmodelAction);}
		@Override
		public void actionPerformed(ActionEvent e) {
			
			if(blockButtonAction){
				return;
			}
			blockButtonAction = true;
			new Thread (this).start();}
        @Override
		public void run() {
			newpredictmodelActionPerformed();
			blockButtonAction = false;
		}
    }

	public void newbpnmodelActionPerformed(){
		int nc = project.getNumberOfPreprocessors();
		if(nc<=0){	
			showOKDialog(getNolResourceString(NOPREPROCESSORFORMODEL));
			return;
		}
		getNewBpnModelWizard().setBounds(200, 200, 470, 400);
		getNewBpnModelWizard().resetData();
		getNewBpnModelWizard().setVisible(true);

		if(getNewBpnModelWizard().isOK()){
			NolBpnModel model = getNewBpnModelWizard().getModel();
			if(model != null){
				project.addBpnModel(model);
				projectTree.addBpnModel(model,true);	
				menuFlag_hasBpnModel = true;
				getBpnTrainDialog().setBpnModel(model);
				getBpnTrainDialog().setVisible(true);				

			}
		}
		modifyDefaultAction();
		progress.validate();
		progress.repaint(0l);
		this.validate();
		Toolkit.getDefaultToolkit().beep();
	}

	/**Create new bpn model  action implementation 	 */
    class NewBpnModelAction extends AbstractAction implements Runnable {
		NewBpnModelAction() {	super(newbpnmodelAction);}
		@Override
		public void actionPerformed(ActionEvent e) {
			
			if(blockButtonAction){
				return;
			}
			blockButtonAction = true;
			new Thread (this).start();
		}
        @Override
		public void run() {
			newbpnmodelActionPerformed();
			blockButtonAction = false;
		}
    }

	public void newannmodelActionPerformed(){
		int nc = project.getNumberOfPreprocessors();
		if(nc<=0){	
			showOKDialog(getNolResourceString(NOPREPROCESSORFORMODEL));
			return;
		}
		getNewAnnModelWizard().setBounds(200, 200, 470, 430);
		getNewAnnModelWizard().resetData();
		getNewAnnModelWizard().setVisible(true);

		if(getNewAnnModelWizard().isOK()){
			NolAnnModel model = getNewAnnModelWizard().getModel();
			if(model != null){
				project.addAnnModel(model);
				projectTree.addAnnModel(model,true);
				menuFlag_hasAnnModel = true;
				getBpnTrainDialog().setBpnModel(model);
				getBpnTrainDialog().setVisible(true);				
			}
		}
		modifyDefaultAction();
		progress.validate();
		progress.repaint(0l);
		this.validate();
		Toolkit.getDefaultToolkit().beep();
	}

	/**Create new Ann model  action implementation 	 */
    class NewAnnModelAction extends AbstractAction implements Runnable {
		NewAnnModelAction() {	super(newannmodelAction);}
		@Override
		public void actionPerformed(ActionEvent e) {
			if(blockButtonAction){
				return;
			}
			blockButtonAction = true;
			new Thread (this).start();
		}
        @Override
		public void run() {
			newannmodelActionPerformed();
			blockButtonAction = false;
		}
    }


	public void newrbfnmodelActionPerformed(){
		int nc = project.getNumberOfPreprocessors();
		if(nc<=0){	
			showOKDialog(getNolResourceString(NOPREPROCESSORFORMODEL));
			return;
		}
		getNewRbfnModelWizard().setBounds(200, 200, 470, 450);
		getNewRbfnModelWizard().resetData();
		getNewRbfnModelWizard().setVisible(true);

		if(getNewRbfnModelWizard().isOK()){
			NolRbfnModel model = getNewRbfnModelWizard().getModel();
			if(model != null){
				project.addRbfnModel(model);
				projectTree.addRbfnModel(model,true);	 
				menuFlag_hasRbfnModel = true;
				getRbfnTrainDialog().setRbfnModel(model);
				getRbfnTrainDialog().setVisible(true);				

			}
		}
		modifyDefaultAction();
		progress.validate();
		progress.repaint(0l);
		this.validate();
		Toolkit.getDefaultToolkit().beep();
	}

	/**Create new rbfn model  action implementation 	 */
    class NewRbfnModelAction extends AbstractAction implements Runnable {
		NewRbfnModelAction() {	super(newrbfnmodelAction);}
		@Override
		public void actionPerformed(ActionEvent e) {
			if(blockButtonAction){
				return;
			}
			blockButtonAction = true;
			new Thread (this).start();
		}
        @Override
		public void run() {
			newrbfnmodelActionPerformed();
			blockButtonAction = false;
		}
    }


	public void newrhomodelActionPerformed(){
		int nc = project.getNumberOfPreprocessors();
		if(nc<=0){	
			showOKDialog(getNolResourceString(NOPREPROCESSORFORMODEL));
			return;
		}
		getNewRhoModelWizard().setBounds(200, 200, 470, 400);
		getNewRhoModelWizard().resetData();
		getNewRhoModelWizard().setVisible(true);

		if(getNewRhoModelWizard().isOK()){
			NolRhoModel model = getNewRhoModelWizard().getModel();
			if(model != null){
				project.addRhoModel(model);
				projectTree.addRhoModel(model,true);	 
				menuFlag_hasRhoModel = true;
				getRhoTrainDialog().setRhoModel(model);
				getRhoTrainDialog().setVisible(true);				

			}
		}
		modifyDefaultAction();
		progress.validate();
		progress.repaint(0l);
		this.validate();
		Toolkit.getDefaultToolkit().beep();

	}

	/**Create new rho model  action implementation 	 */
    class NewRhoModelAction extends AbstractAction implements Runnable {
		NewRhoModelAction() {	super(newrhomodelAction);}
		@Override
		public void actionPerformed(ActionEvent e) {
			if(blockButtonAction) {
				return;
			}
			blockButtonAction = true;
			new Thread (this).start();
		}
        @Override
		public void run() {
			newrhomodelActionPerformed();
			blockButtonAction = false;
		}
    }

	public void newplsmodelActionPerformed(){
		int nc = project.getNumberOfPreprocessors();
		if(nc<=0){	
			showOKDialog(getNolResourceString(NOPREPROCESSORFORMODEL));
			return;
		}
		getNewPlsModelWizard().setBounds(200, 200, 470, 480);
		getNewPlsModelWizard().resetData();
		getNewPlsModelWizard().setVisible(true);

		if(getNewPlsModelWizard().isOK()){
			NolPlsModel model = getNewPlsModelWizard().getModel();
			if(model != null){
				project.addPlsModel(model);
				projectTree.addPlsModel(model,true);	 
				menuFlag_hasPlsModel = true;
			}
		}
		modifyDefaultAction();
		progress.validate();
		progress.repaint(0l);
		this.validate();
		Toolkit.getDefaultToolkit().beep();
	}

	/**Create new rho model  action implementation 	 */
    class NewPlsModelAction extends AbstractAction implements Runnable {
		NewPlsModelAction() {	super(newplsmodelAction);}
		@Override
		public void actionPerformed(ActionEvent e) {
			if(blockButtonAction) {
				return;
			}
			blockButtonAction = true;
			new Thread (this).start();
		}
        @Override
		public void run() {
			newplsmodelActionPerformed();
			blockButtonAction = false;
		}
    }

	public void newpcamodelActionPerformed(){
		int nc = project.getNumberOfPreprocessors();
		if(nc<=0){	
			showOKDialog(getNolResourceString(NOPREPROCESSORFORMODEL));
			return;
		}
		getNewPcaModelWizard().setBounds(200, 200, 470, 500);
		getNewPcaModelWizard().resetData();
		getNewPcaModelWizard().setVisible(true);

		if(getNewPcaModelWizard().isOK()){
			NolPcaModel model = getNewPcaModelWizard().getModel();
			if(model != null){
				project.addPcaModel(model);
				projectTree.addPcaModel(model,true);	 
				menuFlag_hasPlsModel = true;
			}
		}
		modifyDefaultAction();
		progress.validate();
		progress.repaint(0l);
		this.validate();
		Toolkit.getDefaultToolkit().beep();
	}

	/**Create new rho model  action implementation 	 */
    class NewPcaModelAction extends AbstractAction implements Runnable {
		NewPcaModelAction() {	super(newpcamodelAction);}
		@Override
		public void actionPerformed(ActionEvent e) {
			if(blockButtonAction){
				return;
			}
			blockButtonAction = true;
			new Thread (this).start();
		}
        @Override
		public void run() {
			newpcamodelActionPerformed();
			blockButtonAction = false;
		}
    }



	public void newoptimizemodelActionPerformed(){

		int nc = project.getNumberOfPreprocessors();
		if(nc<1){	
			showOKDialog(getNolResourceString(NOPREPROCESSORFORMODEL));
//			showOKDialog("No preprocessor to create model!");
			return;
		}
		getNewOptimizeModelWizard().setBounds(200, 200, 550, 400);
		getNewOptimizeModelWizard().resetData();
		getNewOptimizeModelWizard().setVisible(true);

		if(getNewOptimizeModelWizard().isOK()){
			NolOptimizeModel model = getNewOptimizeModelWizard().getModel();
			if(DEBUG.debugFlag){
				System.out.println("main model="+model.parametersToString());
			}
			if(model != null){
				project.addOptimizationModel(model);
				projectTree.addOptimizationModel(model,true); //Changed for dynamic display Gchen 5.29.2002
				menuFlag_hasOptimizationModel = true;
				getTrainDialog().setModel(model);
				getTrainDialog().setVisible(true);				
			}else{
				progress.setText("Status: "+ getNolResourceString(CANCELNEWMODEL));
//				progress.setText("Status: Canceled Creating Model.");
				progress.validate();
				progress.repaint(0l);
			}
		}
		modifyDefaultAction();
		progress.validate();
		progress.repaint(0l);
		this.validate();
		Toolkit.getDefaultToolkit().beep();
	}

	/**Create new optimization model  action implementation  */
    class NewOptimizeModelAction extends AbstractAction implements Runnable {
		NewOptimizeModelAction() {	super(newoptimizemodelAction);}
		@Override
		public void actionPerformed(ActionEvent e) {
			
			if(blockButtonAction) {
				return;
			}
			blockButtonAction = true;
			new Thread (this).start();}
        @Override
		public void run() {
			//         setWaitCursor(true);
			newoptimizemodelActionPerformed();
			blockButtonAction = false;
			//         setWaitCursor(false);
		}
    }

	public void removeSimulation(final ResponseSurfaceSimulation simulation){
		ResponseSurfaceSimulation simulationBean = simulation;
		int n = internalFrameStack.size();
		NolResponseSurfaceSimulationWKSP simulationWKSP = null;
		boolean inUse = false;
		for(int i=0;i<n;i++){
			NolInternalFrame iframe = (NolInternalFrame)internalFrameStack.elementAt(i);
			if(iframe instanceof NolResponseSurfaceSimulationWKSP ){
				ResponseSurfaceSimulation sim0 =
					((NolResponseSurfaceSimulationWKSP)iframe).getSimulation();
				if(simulationBean.equals(sim0) ) {
					simulationWKSP = (NolResponseSurfaceSimulationWKSP)iframe;
				}
			}else if(iframe instanceof NolVariableWKSP ){
				Variable varObj0 = ((NolVariableWKSP)iframe).getVariable();	
				if(varObj0.getDataSeries().getDataSource().equals(simulationBean)){
					inUse = true;
					break;
				}
			}else if(iframe instanceof NolDataSeriesWKSP ){
				DataSeries oldDs = ((NolDataSeriesWKSP)iframe).getDataSeries();
				if(oldDs.getDataSource().equals(simulationBean)){
					inUse = true;
					break;
				}
			}else if(iframe instanceof NolSpreadsheet ){
				DataSeries oldDs = ((NolSpreadsheet)iframe).getDataSeries();
				if(oldDs.getDataSource().equals(simulationBean)){
					inUse = true;
					break;
				}
			}else if(iframe instanceof NolXYChartFrame ){
				Vector oldVarObjs = ((NolXYChartFrame)iframe).getVariables();	
				for(int j=0;j<oldVarObjs.size();j++){
					Variable var = (Variable)oldVarObjs.elementAt(j);
					if(var.getDataSeries().getDataSource().equals(simulationBean)){
						inUse = true;
						break;						
					}
				}
				if(inUse)
					break;
			}else if(iframe instanceof NolVarChartFrame ){
				Vector oldVarObjs = ((NolVarChartFrame)iframe).getVariables();	
				for(int j=0;j<oldVarObjs.size();j++){
					Variable var = (Variable)oldVarObjs.elementAt(j);
					if(var.getDataSeries().getDataSource().equals(simulationBean)){
						inUse = true;
						break;						
					}
				}
				if(inUse)
					break;
			}else if(iframe instanceof NolHistogramFrame ){
				Vector oldVarObjs = ((NolHistogramFrame)iframe).getVariables();	
				for(int j=0;j<oldVarObjs.size();j++){
					Variable var = (Variable)oldVarObjs.elementAt(j);
					if(var.getDataSeries().getDataSource().equals(simulationBean)){
						inUse = true;
						break;						
					}
				}
				if(inUse){
					break;
				}
			}

		}
		if(inUse){
			showOKDialog(getNolResourceString(MUSTCLOSEALLFORTHIS));
//			showOKDialog("You must close all spreadsheet, charts, and workspaces involving this item before it can be deleted.");
			return;
		}
		if(showYesNoDialog(getNolResourceString(DODELETESIMULATION),1)!=1){
			return;
		}
//		if(showYesNoDialog("Do you wish to delete this simulation?",1)!=1) return;								
		if(simulationWKSP !=null){
			try{
				simulationWKSP.setClosed(true);
			}catch(java.beans.PropertyVetoException evt){
				System.err.println("Non-Fatal exception: " + evt.getMessage());
				evt.printStackTrace();			
			}
		}
		
		project.deleteSimulation(simulationBean);

		if(project.getNumberOfSimulations() > 0){
			menuFlag_hasSimulation = true;
		}else{
			menuFlag_hasSimulation = false;			
		}
		modifyDefaultAction();

		projectTree.setProject();
		progress.setText("Status: "+getNolResourceString(SIMULATION)+" ["+simulationBean.getName()+"] "+getNolResourceString(ISREMOVED));
//		progress.setText("Status: Simulation ["+simulation.getName()+"] is removed!");
		actionHoldCount = actionHoldCount-1;
		if(actionHoldCount <=0){
			actionHoldCount = 0;
//			logoButton.setIcon(defaultLogo);
		}
		simulationBean = null;
		progress.validate();
		progress.repaint(0l);
		Toolkit.getDefaultToolkit().beep();
    }

	public void newsimulationActionPerformed(){
		Vector pmodels = project.getPredictiveModels();
		int np = pmodels.size();
		Vector omodels = project.getOptimizationModels();
		int no = omodels.size();
		Vector bmodels = project.getBpnModels();
		int nb = bmodels.size();
		Vector amodels = project.getAnnModels();
		int na = amodels.size();
		Vector rmodels = project.getRbfnModels();
		int nr = rmodels.size();
		boolean condition = no<=0 && np<=0 && nb<=0;
		if(condition && na<=0 && nr<=0){	
			showOKDialog(getNolResourceString(NOMODELFORSIMULATION));
//			showOKDialog("No model to create simulation!");
			return;
		}
		getNewSimulationWizard().setBounds(200, 200, 390, 350);
		getNewSimulationWizard().resetData();
		getNewSimulationWizard().setVisible(true);

		if(getNewSimulationWizard().isOK()){
			ResponseSurfaceSimulation sim = getNewSimulationWizard().getSimulation();
			showSimulationWKSP(sim);
			menuFlag_hasSimulation = true;
			modifyDefaultAction();
			projectTree.addSimulation(sim,true); //Temp code Gchen 9/9/98
		}
		this.validate();
		Toolkit.getDefaultToolkit().beep();
	}

	/**Create new optimization model  action implementation */
    class NewSimulationAction extends AbstractAction implements Runnable {
		NewSimulationAction() {	super(newsimulationAction);}
		@Override
		public void actionPerformed(ActionEvent e) {
			
			if(blockButtonAction){
				return;
			}
			blockButtonAction = true;
			new Thread (this).start();}
        @Override
		public void run() {
			//         setWaitCursor(true);
			newsimulationActionPerformed();
			blockButtonAction = false;
			//         setWaitCursor(false);
		}
    }

 	public void removeOptimization(final NolOptimization optimization){
 		NolOptimization optimizationBean = optimization;
 		int n = internalFrameStack.size();
		NolOptimizationWKSP optimizationWKSP = null;
		boolean inUse = false;
		for(int i=0;i<n;i++){
			NolInternalFrame iframe = (NolInternalFrame)internalFrameStack.elementAt(i);
			if(iframe instanceof NolOptimizationWKSP ){
				NolOptimization opt0 =
					((NolOptimizationWKSP)iframe).getOptimization();
				if(optimizationBean.equals(opt0)) {
					optimizationWKSP = (NolOptimizationWKSP)iframe;
				}
			}
		}
		if(showYesNoDialog(getNolResourceString(DODELETEOPTIMIZATION),1)!=1){
			return;
		}
//		if(showYesNoDialog("Do you wish to delete this optimization?",1)!=1) return;
		if(optimizationWKSP !=null){
			try{
				optimizationWKSP.setClosed(true);
			}catch(java.beans.PropertyVetoException evt){
				System.err.println("Non-Fatal exception: " + evt.getMessage());
				evt.printStackTrace();			
			}
		}
		
		project.deleteOptimization(optimizationBean);

		if(project.getNumberOfOptimizations() > 0){
			menuFlag_hasOptimization = true;
		}else{
			menuFlag_hasOptimization = false;			
		}
		modifyDefaultAction();

		projectTree.setProject();
		progress.setText("Status: "+getNolResourceString(OPTIMIZATION)+" ["+optimizationBean.getName()+"] "+getNolResourceString(ISREMOVED));
//		progress.setText("Status: Optimization ["+optimization.getName()+"] is removed!");
		actionHoldCount = actionHoldCount-1;
		if(actionHoldCount <=0){
			actionHoldCount = 0;
//			logoButton.setIcon(defaultLogo);
		}
		optimizationBean = null;
		progress.validate();
		progress.repaint(0l);
		Toolkit.getDefaultToolkit().beep();
    }

	public void newoptimizationActionPerformed(){
		int nop = project.getNumberOfOptimizationModels();
		if(nop<=0){	
//			showOKDialog("No optimization model to create optimization!");
			showOKDialog(getNolResourceString(NOMODELFOROPTIMIZATION));
			return;
		}
		getNewOptimizationWizard().setBounds(200, 200, 430, 350);
		getNewOptimizationWizard().resetData();
		getNewOptimizationWizard().setVisible(true);

		if(getNewOptimizationWizard().isOK()){
			NolOptimization optObj = getNewOptimizationWizard().getOptimization();
			optObj.setMaxIteration(optNMAX);
			showOptimizationWKSP(optObj);
			projectTree.addOptimization(optObj,true); //Changed for dynamic display Gchen 5.29.2002
			menuFlag_hasOptimization = true;
			modifyDefaultAction();
		}
		this.validate();
		Toolkit.getDefaultToolkit().beep();
	}

/**Create new optimization model action implementation 	*/
    class NewOptimizationAction extends AbstractAction implements Runnable {
		NewOptimizationAction() { super(newoptimizationAction);}
		@Override
		public void actionPerformed(ActionEvent e) {
			
			if(blockButtonAction) {
				return;
			}
			blockButtonAction = true;
			new Thread (this).start();}
        @Override
		public void run() {
			//         setWaitCursor(true);
			newoptimizationActionPerformed();
			blockButtonAction = false;
			//         setWaitCursor(false);
		}
    }


	public void newgenoptimizationActionPerformed(){
		getNewGenOptimizationWizard().setBounds(200, 200, 450, 450);
		getNewGenOptimizationWizard().resetData();
		getNewGenOptimizationWizard().setVisible(true);

		if(getNewGenOptimizationWizard().isOK()){
			NolGenOptimization optObj = getNewGenOptimizationWizard().getOptimization();
			showGenOptimizationWKSP(optObj);
//			projectTree.addGenOptimization(optObj,true); //Changed for dynamic display Gchen 5.29.2002
			menuFlag_hasGenOptimization = true;
			modifyDefaultAction();
		}
		this.validate();
		Toolkit.getDefaultToolkit().beep();
	}

/**Create new general optimization model action implementation 	*/
    class NewGenOptimizationAction extends AbstractAction implements Runnable {
		NewGenOptimizationAction() { super(newgenoptimizationAction);}
		@Override
		public void actionPerformed(ActionEvent e) {
			if(blockButtonAction) {
				return;
			}
			blockButtonAction = true;
			new Thread (this).start();}
        @Override
		public void run() {
			//         setWaitCursor(true);
			newgenoptimizationActionPerformed();
			blockButtonAction = false;
			//         setWaitCursor(false);
		}
    }

/**Goto data series action implementation */
    class GotoDataSeriesAction extends AbstractAction implements Runnable {
		GotoDataSeriesAction() {super(gotodataseriesAction);}
		@Override
		public void actionPerformed(ActionEvent e) {new Thread (this).start ();}
        @Override
		public void run() {
			if(project == null || !menuFlag_hasDataSeries) {
				return;
			}
			//         setWaitCursor(true);
			DataSeries ds = getSelectedDataSeriesFromChoiceDialog(false);
			if(ds != null) {
				showDataSeriesWKSP(ds);
			}
			//         setWaitCursor(false);
		}
    }

/**Goto label action implementation */
    class GotoLabelAction extends AbstractAction implements Runnable {
		GotoLabelAction() {super(gotolabelAction);}
		@Override
		public void actionPerformed(ActionEvent e) {new Thread (this).start();}
        @Override
		public void run() {
			Vector labels = project.getLabels();
			getSingleChoiceDialog().setContent
				("Select Label", "Label:", labels, false);
			getSingleChoiceDialog().pack();
			getSingleChoiceDialog().setBounds(200, 200, 320, 300);
			getSingleChoiceDialog().setVisible(true);
			if(!getSingleChoiceDialog().getResult()) {
				return;
			}
			//         setWaitCursor(true);
			NolLabel lab = (NolLabel)getSingleChoiceDialog().getSelectedItem();
			showLabelWKSP(lab);
			//         setWaitCursor(false);
		}
    }

/**Goto Preprocessor action implementation */
    class GotoPreprocessorAction extends AbstractAction implements Runnable {
		GotoPreprocessorAction() {super(gotopreprocessorAction);}
		@Override
		public void actionPerformed(ActionEvent e) {new Thread (this).start();}
        @Override
		public void run() {
			Vector preps = project.getPreprocessors();
			getSingleChoiceDialog().setContent
				("Select Preprocessor", "Preprocessor:", preps, false);
			getSingleChoiceDialog().pack();
			getSingleChoiceDialog().setBounds(200, 200, 320, 300);
			getSingleChoiceDialog().setVisible(true);
			if(!getSingleChoiceDialog().getResult()) {
				return;
			}
			//         setWaitCursor(true);
			Preprocessor prep = (Preprocessor)getSingleChoiceDialog().getSelectedItem();
			showPreprocessorWKSP(prep);
			//         setWaitCursor(false);
		}
    }

/**Goto PredictModel action implementation */
    class GotoPredictModelAction extends AbstractAction implements Runnable {
		GotoPredictModelAction() {super(gotopredictmodelAction);}
		@Override
		public void actionPerformed(ActionEvent e) {new Thread (this).start();}
        @Override
		public void run() {
			Vector models = project.getPredictiveModels();
			getSingleChoiceDialog().setContent
				("Select Predictive Model", "Predictive Model:", models, false);
			getSingleChoiceDialog().pack();
			getSingleChoiceDialog().setBounds(200, 200, 320, 300);
			getSingleChoiceDialog().setVisible(true);
			if(!getSingleChoiceDialog().getResult()){
				return;
			}
			//         setWaitCursor(true);
			NolModel2 model = (NolModel2)getSingleChoiceDialog().getSelectedItem();
			showPredictiveModelWKSP(model);
			//         setWaitCursor(false);
		}
    }

/**Goto BpnModel action implementation */
    class GotoBpnModelAction extends AbstractAction implements Runnable {
		GotoBpnModelAction() {super(gotobpnmodelAction);}
		@Override
		public void actionPerformed(ActionEvent e) {new Thread (this).start();}
        @Override
		public void run() {
			Vector models = project.getBpnModels();
			getSingleChoiceDialog().setContent
				("Select Backpropagation Net", "Backpropagation Net:", models, false);
			getSingleChoiceDialog().pack();
			getSingleChoiceDialog().setBounds(200, 200, 320, 300);
			getSingleChoiceDialog().setVisible(true);
			if(!getSingleChoiceDialog().getResult()) {
				return;
			}
			//         setWaitCursor(true);
			NolBpnModel model = (NolBpnModel)getSingleChoiceDialog().getSelectedItem();
			showClassicModelWKSP(model);
			//         setWaitCursor(false);
		}
    }

/**Goto AnnModel action implementation */
    class GotoAnnModelAction extends AbstractAction implements Runnable {
		GotoAnnModelAction() {super(gotoannmodelAction);}
		@Override
		public void actionPerformed(ActionEvent e) {new Thread (this).start();}
        @Override
		public void run() {
			Vector models = project.getAnnModels();
			getSingleChoiceDialog().setContent
				("Select Autoassociated Net", "Autoassociated Net:", models, false);
			getSingleChoiceDialog().pack();
			getSingleChoiceDialog().setBounds(200, 200, 320, 300);
			getSingleChoiceDialog().setVisible(true);
			if(!getSingleChoiceDialog().getResult()) {
				return;
			}
			//         setWaitCursor(true);
			NolAnnModel model = (NolAnnModel)getSingleChoiceDialog().getSelectedItem();
			showClassicModelWKSP(model);
			//         setWaitCursor(false);
		}
    }

/**Goto RbfnModel action implementation */
    class GotoRbfnModelAction extends AbstractAction implements Runnable {
		GotoRbfnModelAction() {super(gotorbfnmodelAction);}
		@Override
		public void actionPerformed(ActionEvent e) {new Thread (this).start();}
        @Override
		public void run() {
			Vector models = project.getRbfnModels();
			getSingleChoiceDialog().setContent
				("Select Radial Basis Net", "Radial Basis Net:", models, false);
			getSingleChoiceDialog().pack();
			getSingleChoiceDialog().setBounds(200, 200, 320, 300);
			getSingleChoiceDialog().setVisible(true);
			if(!getSingleChoiceDialog().getResult()) {
				return;
			}
			//         setWaitCursor(true);
			NolRbfnModel model = (NolRbfnModel)getSingleChoiceDialog().getSelectedItem();
			showClassicModelWKSP(model);
			//         setWaitCursor(false);
		}
    }

/**Goto RhoModel action implementation */
    class GotoRhoModelAction extends AbstractAction implements Runnable {
		GotoRhoModelAction() {super(gotorhomodelAction);}
		@Override
		public void actionPerformed(ActionEvent e) {new Thread (this).start();}
        @Override
		public void run() {
			Vector models = project.getRhoModels();
			getSingleChoiceDialog().setContent
				("Select Rho Net", "Rho Net:", models, false);
			getSingleChoiceDialog().pack();
			getSingleChoiceDialog().setBounds(200, 200, 320, 300);
			getSingleChoiceDialog().setVisible(true);
			if(!getSingleChoiceDialog().getResult()){
				return;
			}
			//         setWaitCursor(true);
			NolRhoModel model = (NolRhoModel)getSingleChoiceDialog().getSelectedItem();
			showRhoModelWKSP(model);
			//         setWaitCursor(false);
		}
    }

/**Goto PlsModel action implementation */
    class GotoPlsModelAction extends AbstractAction implements Runnable {
		GotoPlsModelAction() {super(gotoplsmodelAction);}
		@Override
		public void actionPerformed(ActionEvent e) {new Thread (this).start();}
        @Override
		public void run() {
			Vector models = project.getPlsModels();
			getSingleChoiceDialog().setContent
				("Select Pls Net", "Pls Net:", models, false);
			getSingleChoiceDialog().pack();
			getSingleChoiceDialog().setBounds(200, 200, 320, 300);
			getSingleChoiceDialog().setVisible(true);
			if(!getSingleChoiceDialog().getResult()){
				return;
			}
			//         setWaitCursor(true);
			NolPlsModel model = (NolPlsModel)getSingleChoiceDialog().getSelectedItem();
			showPlsModelWKSP(model);
			//         setWaitCursor(false);
		}
    }

/**Goto PcaModel action implementation */
    class GotoPcaModelAction extends AbstractAction implements Runnable {
		GotoPcaModelAction() {super(gotopcamodelAction);}
		@Override
		public void actionPerformed(ActionEvent e) {new Thread (this).start();}
        @Override
		public void run() {
			Vector models = project.getPcaModels();
			getSingleChoiceDialog().setContent
				("Select Pca Net", "Pca Net:", models, false);
			getSingleChoiceDialog().pack();
			getSingleChoiceDialog().setBounds(200, 200, 320, 300);
			getSingleChoiceDialog().setVisible(true);
			if(!getSingleChoiceDialog().getResult()){
				return;
			}
			//         setWaitCursor(true);
			NolPcaModel model = (NolPcaModel)getSingleChoiceDialog().getSelectedItem();
			showPcaModelWKSP(model);
			//         setWaitCursor(false);
		}
    }

/**Goto OptimizeModel action implementation */
    class GotoOptimizeModelAction extends AbstractAction implements Runnable {
		GotoOptimizeModelAction() {super(gotooptimizemodelAction);}
		@Override
		public void actionPerformed(ActionEvent e) {new Thread (this).start();}
        @Override
		public void run() {
			Vector models = project.getOptimizationModels();
			getSingleChoiceDialog().setContent
				("Select Optimization Model", "Optimization Model:", models, false);
			getSingleChoiceDialog().pack();
			getSingleChoiceDialog().setBounds(200, 200, 320, 300);
			getSingleChoiceDialog().setVisible(true);
			if(!getSingleChoiceDialog().getResult()) {
				return;
			}
			//         setWaitCursor(true);
			NolOptimizeModel model = (NolOptimizeModel)getSingleChoiceDialog().getSelectedItem();
			showOptimizeModelWKSP(model);
			//         setWaitCursor(false);
		}
    }

/**Goto Simulation action implementation */
    class GotoSimulationAction extends AbstractAction implements Runnable {
		GotoSimulationAction() {super(gotosimulationAction);}
		@Override
		public void actionPerformed(ActionEvent e) {new Thread (this).start();}
        @Override
		public void run() {
			Vector sims = project.getSimulations();
			getSingleChoiceDialog().setContent
				("Select Simulation", "Simulation:", sims, false);
			getSingleChoiceDialog().pack();
			getSingleChoiceDialog().setBounds(200, 200, 320, 300);
			getSingleChoiceDialog().setVisible(true);
			if(!getSingleChoiceDialog().getResult()){
				return;
			}
			//         setWaitCursor(true);
			ResponseSurfaceSimulation sim = (ResponseSurfaceSimulation)getSingleChoiceDialog().getSelectedItem();
			showSimulationWKSP(sim);
			//         setWaitCursor(false);
		}
    }

/**Goto Optimization action implementation */
    class GotoOptimizationAction extends AbstractAction implements Runnable {
		GotoOptimizationAction() {super(gotooptimizationAction);}
		@Override
		public void actionPerformed(ActionEvent e) {new Thread (this).start();}
        @Override
		public void run() {
			Vector opts = project.getOptimizations();
			getSingleChoiceDialog().setContent
				("Select Optimization", "Optimization:", opts, false);
			getSingleChoiceDialog().pack();
			getSingleChoiceDialog().setBounds(200, 200, 320, 300);
			getSingleChoiceDialog().setVisible(true);
			if(!getSingleChoiceDialog().getResult()){
				return;
			}
			//         setWaitCursor(true);
			NolOptimization opt = (NolOptimization)getSingleChoiceDialog().getSelectedItem();
			showOptimizationWKSP(opt);
			//         setWaitCursor(false);
		}
    }

/**Goto Optimization action implementation */
    class GotoGenOptimizationAction extends AbstractAction implements Runnable {
		GotoGenOptimizationAction() {super(gotogenoptimizationAction);}
		@Override
		public void actionPerformed(ActionEvent e) {new Thread (this).start();}
        @Override
		public void run() {
		}
    }

/**Delete label action implementation */
    class DeleteLabelAction extends AbstractAction implements Runnable {
		DeleteLabelAction() {super(deletelabelAction);}
		@Override
		public void actionPerformed(ActionEvent e) {new Thread (this).start();}
        @Override
		public void run() {
			Vector labels = project.getLabels();
			getSingleChoiceDialog().setContent
				("Select Label", "Label:", labels, false);
			getSingleChoiceDialog().pack();
			getSingleChoiceDialog().setBounds(200, 200, 320, 300);
			getSingleChoiceDialog().setVisible(true);
			if(!getSingleChoiceDialog().getResult()){
				return;
			}
			//         setWaitCursor(true);
			NolLabel lab = (NolLabel)getSingleChoiceDialog().getSelectedItem();
			removeLabel(lab);
			//         setWaitCursor(false);
		}
    }

/**Delete data series action implementation */
    class DeleteDataSeriesAction extends AbstractAction implements Runnable {
		DeleteDataSeriesAction() {super(deletedataseriesAction);}
		@Override
		public void actionPerformed(ActionEvent e) {new Thread (this).start();}
        @Override
		public void run() {
			Vector datas = project.getRawDataSource().getDataSeries();
			getSingleChoiceDialog().setContent
				("Select Data Series", "DataSeries:", datas, false);
			getSingleChoiceDialog().pack();
			getSingleChoiceDialog().setBounds(200, 200, 320, 300);
			getSingleChoiceDialog().setVisible(true);
			if(!getSingleChoiceDialog().getResult()){
				return;
			}
			//         setWaitCursor(true);
			DataSeries ds = (DataSeries)getSingleChoiceDialog().getSelectedItem();
			removeRawDataDataSeries(ds);
			//         setWaitCursor(false);
		}
    }

 /**Delete Preprocessor action implementation */
    class DeletePreprocessorAction extends AbstractAction implements Runnable {
		DeletePreprocessorAction() {super(deletepreprocessorAction);}
		@Override
		public void actionPerformed(ActionEvent e) {new Thread (this).start();}
        @Override
		public void run() {
			Vector preps = project.getPreprocessors();
			getSingleChoiceDialog().setContent
				("Select Preprocessor", "Preprocessor:", preps, false);
			getSingleChoiceDialog().pack();
			getSingleChoiceDialog().setBounds(200, 200, 320, 300);
			getSingleChoiceDialog().setVisible(true);
			if(!getSingleChoiceDialog().getResult()){
				return;
			}
			//         setWaitCursor(true);
			Preprocessor prep = (Preprocessor)getSingleChoiceDialog().getSelectedItem();
			removePreprocessor(prep);
			//         setWaitCursor(false);
		}
    }

/**Delete PredictModel action implementation */
    class DeletePredictModelAction extends AbstractAction implements Runnable {
		DeletePredictModelAction() {super(deletepredictmodelAction);}
		@Override
		public void actionPerformed(ActionEvent e) {new Thread (this).start();}
        @Override
		public void run() {
			Vector models = project.getPredictiveModels();
			getSingleChoiceDialog().setContent
				("Select Predictive Model", "Predictive Model:", models, false);
			getSingleChoiceDialog().pack();
			getSingleChoiceDialog().setBounds(200, 200, 320, 300);
			getSingleChoiceDialog().setVisible(true);
			if(!getSingleChoiceDialog().getResult()){
				return;
			}
			//         setWaitCursor(true);
			NolModel2 model = (NolModel2)getSingleChoiceDialog().getSelectedItem();
			removeModel(model);
			//         setWaitCursor(false);
		}
    }

/**Delete BpnModel action implementation */
    class DeleteBpnModelAction extends AbstractAction implements Runnable {
		DeleteBpnModelAction() {super(deletebpnmodelAction);}
		@Override
		public void actionPerformed(ActionEvent e) {new Thread (this).start();}
        @Override
		public void run() {
			Vector models = project.getBpnModels();
			getSingleChoiceDialog().setContent
				("Select Backpropagation Net", "Backpropagation Net:", models, false);
			getSingleChoiceDialog().pack();
			getSingleChoiceDialog().setBounds(200, 200, 320, 300);
			getSingleChoiceDialog().setVisible(true);
			if(!getSingleChoiceDialog().getResult()){
				return;
			}
			//         setWaitCursor(true);
			NolBpnModel model = (NolBpnModel)getSingleChoiceDialog().getSelectedItem();
			removeModel(model);
			//         setWaitCursor(false);
		}
    }

/**Delete AnnModel action implementation */
    class DeleteAnnModelAction extends AbstractAction implements Runnable {
		DeleteAnnModelAction() {super(deleteannmodelAction);}
		@Override
		public void actionPerformed(ActionEvent e) {new Thread (this).start();}
        @Override
		public void run() {
			Vector models = project.getAnnModels();
			getSingleChoiceDialog().setContent
				("Select Autoassociated Net", "Autoassociated Net:", models, false);
			getSingleChoiceDialog().pack();
			getSingleChoiceDialog().setBounds(200, 200, 320, 300);
			getSingleChoiceDialog().setVisible(true);
			if(!getSingleChoiceDialog().getResult()){
				return;
			}
			//         setWaitCursor(true);
			NolAnnModel model = (NolAnnModel)getSingleChoiceDialog().getSelectedItem();
			removeModel(model);
			//         setWaitCursor(false);
		}
    }


/**Delete RbfnModel action implementation */
    class DeleteRbfnModelAction extends AbstractAction implements Runnable {
		DeleteRbfnModelAction() {super(deleterbfnmodelAction);}
		@Override
		public void actionPerformed(ActionEvent e) {new Thread (this).start();}
        @Override
		public void run() {
			Vector models = project.getRbfnModels();
			getSingleChoiceDialog().setContent
				("Select Radial Basis Net", "Radial Basis Net:", models, false);
			getSingleChoiceDialog().pack();
			getSingleChoiceDialog().setBounds(200, 200, 320, 300);
			getSingleChoiceDialog().setVisible(true);
			if(!getSingleChoiceDialog().getResult()){
				return;
			}
			//         setWaitCursor(true);
			NolRbfnModel model = (NolRbfnModel)getSingleChoiceDialog().getSelectedItem();
			removeModel(model);
			//         setWaitCursor(false);
		}
    }


/**Delete RhoModel action implementation */
    class DeleteRhoModelAction extends AbstractAction implements Runnable {
		DeleteRhoModelAction() {super(deleterhomodelAction);}
		@Override
		public void actionPerformed(ActionEvent e) {new Thread (this).start();}
        @Override
		public void run() {
			Vector models = project.getRhoModels();
			getSingleChoiceDialog().setContent
				("Select Rho Net", "Rho Net:", models, false);
			getSingleChoiceDialog().pack();
			getSingleChoiceDialog().setBounds(200, 200, 320, 300);
			getSingleChoiceDialog().setVisible(true);
			if(!getSingleChoiceDialog().getResult()){
				return;
			}
			//         setWaitCursor(true);
			NolRhoModel model = (NolRhoModel)getSingleChoiceDialog().getSelectedItem();
			removeModel(model);
			//         setWaitCursor(false);
		}
    }

/**Delete PlsModel action implementation */
    class DeletePlsModelAction extends AbstractAction implements Runnable {
		DeletePlsModelAction() {super(deleteplsmodelAction);}
		@Override
		public void actionPerformed(ActionEvent e) {new Thread (this).start();}
        @Override
		public void run() {
			Vector models = project.getPlsModels();
			getSingleChoiceDialog().setContent
				("Select Pls Net", "Pls Net:", models, false);
			getSingleChoiceDialog().pack();
			getSingleChoiceDialog().setBounds(200, 200, 320, 300);
			getSingleChoiceDialog().setVisible(true);
			if(!getSingleChoiceDialog().getResult()){
				return;
			}
			//         setWaitCursor(true);
			NolPlsModel model = (NolPlsModel)getSingleChoiceDialog().getSelectedItem();
			removeModel(model);
			//         setWaitCursor(false);
		}
    }

/**Delete PcaModel action implementation */
    class DeletePcaModelAction extends AbstractAction implements Runnable {
		DeletePcaModelAction() {super(deletepcamodelAction);}
		@Override
		public void actionPerformed(ActionEvent e) {new Thread (this).start();}
        @Override
		public void run() {
			Vector models = project.getPcaModels();
			getSingleChoiceDialog().setContent
				("Select Pca Net", "Pca Net:", models, false);
			getSingleChoiceDialog().pack();
			getSingleChoiceDialog().setBounds(200, 200, 320, 300);
			getSingleChoiceDialog().setVisible(true);
			if(!getSingleChoiceDialog().getResult()){
				return;
			}
			//         setWaitCursor(true);
			NolPcaModel model = (NolPcaModel)getSingleChoiceDialog().getSelectedItem();
			removeModel(model);
			//         setWaitCursor(false);
		}
    }

/**Delete OptimizeModel action implementation */
    class DeleteOptimizeModelAction extends AbstractAction implements Runnable {
		DeleteOptimizeModelAction() {super(deleteoptimizemodelAction);}
		@Override
		public void actionPerformed(ActionEvent e) {new Thread (this).start();}
        @Override
		public void run() {
			Vector models = project.getOptimizationModels();
			getSingleChoiceDialog().setContent
				("Select Optimization Model", "Optimization Model:", models, false);
			getSingleChoiceDialog().pack();
			getSingleChoiceDialog().setBounds(200, 200, 320, 300);
			getSingleChoiceDialog().setVisible(true);
			if(!getSingleChoiceDialog().getResult()){
				return;
			}
			//         setWaitCursor(true);
			NolOptimizeModel model = (NolOptimizeModel)getSingleChoiceDialog().getSelectedItem();
			removeModel(model);
			//         setWaitCursor(false);
		}
    }

/**Delete Simulation action implementation */
    class DeleteSimulationAction extends AbstractAction implements Runnable {
		DeleteSimulationAction() {super(deletesimulationAction);}
		@Override
		public void actionPerformed(ActionEvent e) {new Thread (this).start();}
        @Override
		public void run() {
			Vector sims = project.getSimulations();
			getSingleChoiceDialog().setContent
				("Select Simulation", "Simulation:", sims, false);
			getSingleChoiceDialog().pack();
			getSingleChoiceDialog().setBounds(200, 200, 320, 300);
			getSingleChoiceDialog().setVisible(true);
			if(!getSingleChoiceDialog().getResult()){
				return;
			}
			//         setWaitCursor(true);
			ResponseSurfaceSimulation sim = (ResponseSurfaceSimulation)getSingleChoiceDialog().getSelectedItem();
			removeSimulation(sim);
			//         setWaitCursor(false);
		}
    }

/**Delete Optimization action implementation */
    class DeleteOptimizationAction extends AbstractAction implements Runnable {
		DeleteOptimizationAction() {super(deleteoptimizationAction);}
		@Override
		public void actionPerformed(ActionEvent e) {new Thread (this).start();}
        @Override
		public void run() {
			Vector opts = project.getOptimizations();
			getSingleChoiceDialog().setContent
				("Select Optimization", "Optimization:", opts, false);
			getSingleChoiceDialog().pack();
			getSingleChoiceDialog().setBounds(200, 200, 320, 300);
			getSingleChoiceDialog().setVisible(true);
			if(!getSingleChoiceDialog().getResult()){
				return;
			}
			//         setWaitCursor(true);
			NolOptimization opt = (NolOptimization)getSingleChoiceDialog().getSelectedItem();
			removeOptimization(opt);
			//         setWaitCursor(false);
		}
    }

/**Delete a general Optimization action implementation */
    class DeleteGenOptimizationAction extends AbstractAction implements Runnable {
		DeleteGenOptimizationAction() {super(deletegenoptimizationAction);}
		@Override
		public void actionPerformed(ActionEvent e) {new Thread (this).start();}
        @Override
		public void run() {
			Vector opts = project.getGenOptimizations();
			getSingleChoiceDialog().setContent
				("Select Optimization", "Optimization:", opts, false);
			getSingleChoiceDialog().pack();
			getSingleChoiceDialog().setBounds(200, 200, 320, 300);
			getSingleChoiceDialog().setVisible(true);
			if(!getSingleChoiceDialog().getResult()){
				return;
			}
			NolGenOptimization opt = (NolGenOptimization)getSingleChoiceDialog().getSelectedItem();
			removeGenOptimization(opt);
		}
    }

 	public void removeGenOptimization(final NolGenOptimization optimization){
 		NolGenOptimization optimizationBean = optimization;
		int n = internalFrameStack.size();
		NolGenOptimizationWKSP optimizationWKSP = null;
		boolean inUse = false;
		for(int i=0;i<n;i++){
			NolInternalFrame iframe = (NolInternalFrame)internalFrameStack.elementAt(i);
			if(iframe instanceof NolGenOptimizationWKSP ){
				NolGenOptimization opt0 =
					((NolGenOptimizationWKSP)iframe).getOptimization();
				if(optimizationBean.equals(opt0) ) {
					optimizationWKSP = (NolGenOptimizationWKSP)iframe;
				}
			}
		}
		if(showYesNoDialog(getNolResourceString(DODELETEOPTIMIZATION),1)!=1) {
			return;
		}
		if(optimizationWKSP !=null){
			try{
				optimizationWKSP.setClosed(true);
			}catch(java.beans.PropertyVetoException evt){
				System.err.println("Non-Fatal exception: " + evt.getMessage());
				evt.printStackTrace();			
			}
		}
		
		project.deleteGenOptimization(optimizationBean);

		if(project.getNumberOfGenOptimizations() > 0){
			menuFlag_hasGenOptimization = true;
		}else{
			menuFlag_hasGenOptimization = false;			
		}
		modifyDefaultAction();

		projectTree.setProject();
		progress.setText("Status: "+getNolResourceString(OPTIMIZATION)+" ["+optimizationBean.getName()+"] "+getNolResourceString(ISREMOVED));
		actionHoldCount = actionHoldCount-1;
		if(actionHoldCount <=0){
			actionHoldCount = 0;
		}
		optimizationBean = null;
		progress.validate();
		progress.repaint(0l);
		Toolkit.getDefaultToolkit().beep();
    }

	public void removeFileFormat(final DataSeriesFileFormat format){
		DataSeriesFileFormat formatBean = format;
		int n = internalFrameStack.size();
		NolFileFormatWKSP fileFormatWKSP = null;
		for(int i=0;i<n;i++){
			NolInternalFrame iframe = (NolInternalFrame)internalFrameStack.elementAt(i);
			if(iframe instanceof NolFileFormatWKSP ){
				DataSeriesFileFormat f0 = ((NolFileFormatWKSP)iframe).getDataFormat();
				if(f0.equals(formatBean)){
					fileFormatWKSP=(NolFileFormatWKSP)iframe;
				}
			}
		}
		if(showYesNoDialog(getNolResourceString(DODELETEFILEFORMAT),1)!=1){
			return;
		}
//		if(showYesNoDialog("Do you wish to delete this file format?",1)!=1) return;
		if(fileFormatWKSP !=null){
			try{
				fileFormatWKSP.setClosed(true);
			} catch(java.beans.PropertyVetoException evt){
				System.err.println("Non-Fatal exception: " + evt.getMessage());
				evt.printStackTrace();			
			}
		}
		project.removeDataSeriesFileFormat(formatBean);
		progress.setText("Status: "+getNolResourceString(FILEFORMAT)+" ["+formatBean.getName()+"] "+getNolResourceString(ISREMOVED));
//		progress.setText("Status: File format["+format.getName()+"] is removed!");
		formatBean = null;
		progress.validate();
		progress.repaint(0l);
		Toolkit.getDefaultToolkit().beep();
	}

/** About Actions */  	
    class AboutAction extends AbstractAction {
		AboutAction() {super(aboutAction);}
        @Override
		public void actionPerformed(ActionEvent e) {
			getAboutDialog().setVisible(true);
		}
	}

/** cascade Actions */	
    class CascadeAction extends AbstractAction {
		CascadeAction() {super(cascadeAction);}
        @Override
		public void actionPerformed(ActionEvent e) {
			interCount = 0;
			JLayeredPane pane = getEditor();
			Component[] internalFrames = pane.getComponentsInLayer(JLayeredPane.DEFAULT_LAYER.intValue());
			Dimension dim = pane.getSize();
			int w = dim.width*3/4;
			int h = dim.height*3/4;
			for(int i=internalFrames.length-1;i>=0;i--){
				if(internalFrames[i] instanceof NolInternalFrame ){
					interCount++;
					internalFrames[i].setBounds(20*interCount, 20*interCount,w,h);
					if(interCount > 10)
						interCount = 0;
				}
			}
			getEditor().validate();
		}
	}

/** horizontal Actions */	
    class HorizontalAction extends AbstractAction {
		HorizontalAction() {super(horizontalAction);}
        @Override
		public void actionPerformed(ActionEvent e) {
			JLayeredPane pane = getEditor();
			Component[] internalFrames = pane.getComponentsInLayer(JLayeredPane.DEFAULT_LAYER.intValue());
			int n = internalFrames.length;
			if(n<1) {
				return;
			}
			Dimension dim = pane.getSize();
			int h = dim.height/n;
			for(int i=0;i<n;i++){
				internalFrames[i].setBounds(0,h*i,dim.width,h);
			}
			getEditor().validate();
		}
	}

/** vertical Actions */	
    class VerticalAction extends AbstractAction {
		VerticalAction() {super(verticalAction);}
        @Override
		public void actionPerformed(ActionEvent e) {
			JLayeredPane pane = getEditor();
			Component[] internalFrames = pane.getComponentsInLayer(JLayeredPane.DEFAULT_LAYER.intValue());
			int n = internalFrames.length;
			if(n<1) {
				return;
			}
			Dimension dim = pane.getSize();
			int w = dim.width/n;
			for(int i=0;i<n;i++){
				internalFrames[i].setBounds(w*i,0,w,dim.height);
			}
			getEditor().validate();
		}
	}

   /** windows Actions */	
    class WindowsAction extends AbstractAction {
		WindowsAction() {super(windowsAction);}
        @Override
		public void actionPerformed(ActionEvent e) {
			Component[] internalFrames = getEditor().getComponentsInLayer(JLayeredPane.DEFAULT_LAYER.intValue());		
			Vector contents = new Vector();
			for(int i=0;i<internalFrames.length;i++){
				if(internalFrames[i] instanceof NolInternalFrame){
					NolInternalFrame iframe = (NolInternalFrame)internalFrames[i];
					String frameTitle = iframe.getTitle();
					contents.addElement(frameTitle);
				}
			}
			getWindowsChoiceDialog().setContent
				(contents, false);
			getWindowsChoiceDialog().pack();
			getWindowsChoiceDialog().setBounds(200, 200, 320, 200);
			getWindowsChoiceDialog().setVisible(true);
			int winIndex = getWindowsChoiceDialog().getSelectedIndex();
			if(getWindowsChoiceDialog().getResult() == -1){
				return;
			}		
			if(winIndex == -1){
				return;
			}
			activeInternalFrame = (NolInternalFrame)internalFrames[winIndex];
			blockMainAction = true;
			if(getWindowsChoiceDialog().getResult() == 1){
				try { 
					activeInternalFrame.setSelected(true); 
				} catch (java.beans.PropertyVetoException e2) {
					System.err.println("Non-Fatal exception: " + e2.getMessage());
					e2.printStackTrace();
				}
				getEditor().moveToFront(activeInternalFrame);
				activeInternalFrame.validate();
				activeInternalFrame.removeInternalFrameListener(mainAction);
				activeInternalFrame.addInternalFrameListener(mainAction);
			}else if(getWindowsChoiceDialog().getResult() == 2){
				try{
					activeInternalFrame.setClosed(true);
				}catch(java.beans.PropertyVetoException evt){
					System.err.println("Non-Fatal exception: " + evt.getMessage());
					evt.printStackTrace();
				}
			}
			refreshWindowMenu();
		}
	}
    
	class CloseWindowsAction extends AbstractAction {
		CloseWindowsAction() {super(closewindowsAction);}
        @Override
		public void actionPerformed(ActionEvent e) {
			clearAllInternalFrame();
		}
	}

     class PrintAction extends AbstractAction {

		PrintAction() {super(printAction);}
        @Override
		public void actionPerformed(ActionEvent e) {
			Component[] internalFrames = getEditor().getComponentsInLayer(JLayeredPane.DEFAULT_LAYER.intValue());		
			if(internalFrames.length == 0){
				return;
			}
			for(int i=0;i<internalFrames.length;i++){
				if(internalFrames[i] instanceof NolInternalFrame){
					NolInternalFrame iframe = (NolInternalFrame)internalFrames[i];
					if(iframe.isSelected()){
						activeInternalFrame = iframe;
						break;
					}
				}
			}
			printComponent(activeInternalFrame);
		}
	}

	 
	 class MemoryAction extends AbstractAction {

		MemoryAction() {super(memoryAction);}
        @Override
		public void actionPerformed(ActionEvent e) {
			Matrix.showPoolStatus();
		}
	}
	 


  /** Set the globle preference */
    class PreferenceAction extends AbstractAction implements Runnable {
		PreferenceAction() {super(preferenceAction);}
		@Override
		public void actionPerformed(ActionEvent e) {
			
			if(blockButtonAction){
				return;
			}
			blockButtonAction = true;
			new Thread (this).start();}
        @Override
		public void run() {
			//         setWaitCursor(true);
			preferenceActionPerformed();
			blockButtonAction = false;
			//         setWaitCursor(false);
		}
    }

 	public void preferenceActionPerformed(){
		getPreferenceDialog().resetData(dateFormat,timeFormat,optNMAX);
		getPreferenceDialog().setVisible(true);
	}


  /** Connect to G2 */
    class ConnectG2Action extends AbstractAction implements Runnable {
		ConnectG2Action() {super(connectG2Action);}
		@Override
		public void actionPerformed(ActionEvent e) {
			
			if(blockButtonAction){
				return;
			}
			blockButtonAction = true;
			new Thread (this).start();}
        @Override
		public void run() {
			//         setWaitCursor(true);
			connectG2ActionPerformed();
			blockButtonAction = false;
			//         setWaitCursor(false);
		}
    }

  /** Disconnect to G2 */
    class DisconnectG2Action extends AbstractAction implements Runnable {
		DisconnectG2Action() {super(disconnectG2Action);}
		@Override
		public void actionPerformed(ActionEvent e) {
			
			if(blockButtonAction){
				return;
			}
			blockButtonAction = true;
			new Thread (this).start();}
        @Override
		public void run() {
			//         setWaitCursor(true);
			disconnectG2ActionPerformed();
			blockButtonAction = false;
			//         setWaitCursor(false);
		}
    }

 	public void disconnectG2ActionPerformed(){
 		setProgressText(getNolResourceString(G2DISCONNECTINGSTARTED));
 		try{
			g2Gateway.closeG2Connection();
		}catch(Exception ex){}
 		setProgressText(getNolResourceString(G2DISCONNECTED));
	}
	public void disconnectedG2(){
		g2Gateway = null;
		setConnectedWithG2(false);
		connectionStatus.setText("");
		modifyDefaultAction();
	}

 	public void connectG2ActionPerformed(){
		getConnectG2Dialog().setVisible(true);
		if(getConnectG2Dialog().getOkStatus()){
			String[] args = getConnectG2Dialog().getArgs();
			connectG2(args);
		}
	}

	public void connectG2(String[] args){
		if(g2Gateway == null){
			g2Gateway = new NolG2Gateway(this,args);
			int flag = g2Gateway.getConnectionStatus();
			if(flag == 1){
				connectionStatus.setText(args[1]+":"+args[3]);
				setConnectedWithG2(true);
			}else{
				setConnectedWithG2(false);
				connectionStatus.setText("Can't connect");
			}
		}else{
			int flag = g2Gateway.getConnectionStatus();
			if(flag == 1){
				setConnectedWithG2(true);
				connectionStatus.setText(args[1]+":"+args[3]);
			}else{
				g2Gateway.clear();
				g2Gateway = null;
				g2Gateway = new NolG2Gateway(this,args);
				flag = g2Gateway.getConnectionStatus();
				if(flag == 1){
					connectionStatus.setText(args[1]+":"+args[3]);
					setConnectedWithG2(true);
				}else{
					setConnectedWithG2(false);
					connectionStatus.setText("Can't connect");
				}
			}
		}
		modifyDefaultAction();
	}


	public void exportStringAction(String fileName, Object data){
		if (fileChooser == null) {
			fileChooser = new JFileChooser();
		}
		if(data instanceof String)
			fileChooser.setDialogTitle("Export Text File As");
		else
			fileChooser.setDialogTitle("Export Object As");

		fileChooser.setDialogType(JFileChooser.SAVE_DIALOG);

		File tmpCurrentDirectory = currentDirectory;
		if(tmpCurrentDirectory.exists()) {
			fileChooser.setCurrentDirectory(tmpCurrentDirectory);
		}
		if(data instanceof String){
		  tmpCurrentDirectory = new File(fileName+".txt");
		}else if(data instanceof NolModelParameter){
		  tmpCurrentDirectory = new File(fileName+".mp");
		}
		fileChooser.setSelectedFile(tmpCurrentDirectory);
		int retval = fileChooser.showSaveDialog(NolMainFrame.this);
		if(retval == JFileChooser.CANCEL_OPTION){
			return;
		}

		tmpCurrentDirectory = fileChooser.getSelectedFile();
		currentDirectory = tmpCurrentDirectory;
		if(tmpCurrentDirectory == null) {
			return;
		}

		String file = tmpCurrentDirectory.getName();
		String selectedMiscDirectory = tmpCurrentDirectory.getParent();

		if(DEBUG.debugFlag){
			System.out.println("file="+file);
			System.out.println("miscDirectory="+selectedMiscDirectory);
		}

		
		progress.setText("Status: "+ getNolResourceString(SAVEDATA));
		progress.validate();
		progress.repaint(0l);

		File targetFile = new File(selectedMiscDirectory,file);


		if(data instanceof String){
			String dataString = (String)data;
			FileOutputStream outStream = null;
			Writer streamWriter = null;
			BufferedWriter target = null;
			try { 
				outStream = new FileOutputStream(targetFile);
				streamWriter = new OutputStreamWriter(outStream, Charset.defaultCharset());
				target = new BufferedWriter(streamWriter);

				target.write(dataString,0,dataString.length());
				target.flush();
			}catch (IOException e){
				System.err.println("Non-Fatal exception: " + e.getMessage());
				e.printStackTrace();
			}
			finally {
				closeSilently(target);
				closeSilently(streamWriter);
				closeSilently(outStream);
			}
			
		}else{
			try {					
        // Create the necessary output streams to save the data.
				FileOutputStream fos = new FileOutputStream(targetFile); // Save to file
				GZIPOutputStream gzos = new GZIPOutputStream(fos);     // Compresse
				ObjectOutputStream out = new ObjectOutputStream(gzos); // Save object
				out.writeObject(data);      // Write the entire Vector of scribbles
				out.flush();                 // Always flush the output.
				out.close();                 // And close the stream.
			}catch (IOException e){
				System.err.println("Non-Fatal exception: " + e.getMessage());
				e.printStackTrace();
			}
		}
		progress.setText("Status: "+ getNolResourceString(DONESAVEDATA));
		if(actionHoldCount <=0){
			actionHoldCount = 0;
			logoButton.setIcon(defaultLogo);
		}
		progress.validate();
		progress.repaint(0l);
		Toolkit.getDefaultToolkit().beep();
	}


	public SimpleDateFormat getDateFormat(){
		return dateFormat;	
	}
	public void setDateFormat(SimpleDateFormat f){
		dateFormat = f;	
	}
	public SimpleDateFormat getTimeFormat(){
		return timeFormat;	
	}
	public void setTimeFormat(SimpleDateFormat f){
		timeFormat = f;	
	}

	public int getOptimizationNMAX(){
		return optNMAX;	
	}
	public void setOptimizationNMAX(int v){
		optNMAX = v;	
	}
	


	public void setDateTimeFormat(SimpleDateFormat df,SimpleDateFormat tf){
		dateFormat = df;	
		timeFormat = tf;	
		int n = internalFrameStack.size();
		for(int i=0;i<n;i++){
			NolInternalFrame iframe = (NolInternalFrame)internalFrameStack.elementAt(i);
			if(iframe instanceof NolSpreadsheet ){
				((NolSpreadsheet)iframe).getDataModel().setDateFormat(dateFormat);
				((NolSpreadsheet)iframe).getDataModel().setTimeFormat(timeFormat);
			}
		}
	}

	public void checkDataSeriesTimeStamps(DataSeries data){
		if(data.getHasTimeStamps()){
			long[] timeStamps = data.getTimeStamps();
			if(timeStamps.length>1){
				for(int i=1;i<timeStamps.length;i++){
					if(timeStamps[i]<timeStamps[i-1]){
						showOKDialog(getNolResourceString(NONMONOTONICDATA));
						break;
					}
				}
			}
		}
    }
   /** Set the root directory for the application. Normally the root is set from startup.*/
	public void setRootDirectory(String dir){
		File dirFile = new File(dir);
		if(dirFile.isDirectory()) { 
			rootDirectory = dir;
			System.setProperty("user.dir", dir);
			String newDir =  dir+"\\projects";
			File direct = new File(newDir);
			String selectedDirectory;
			if (direct.isDirectory()){
			  selectedDirectory = new String(newDir);
			}else{
			  selectedDirectory = dir;
			}
			miscDirectory = selectedDirectory;
			projectDirectory = selectedDirectory;
			currentDirectory = new File(selectedDirectory);
			project.setProjectDirectory(selectedDirectory);
			project.loadFileFormat(selectedDirectory);
			projectTree.setProject();
			clearAllInternalFrame();

			defaultProjectName = false;
			modifyDefaultAction();

			progress.validate();
			progress.repaint(0l);
			Toolkit.getDefaultToolkit().beep();
		}
	}
   /** Get the root directory for the application.*/
	public String getRootDirectory(){
		return 	rootDirectory;
	}

   /** Set the project directory for the application.*/
	public void setProjectDirectory(String dir){
		projectDirectory = dir;
	}

   /** Get the project directory for the application.*/
	public String getProjectDirectory(){
		return projectDirectory;
	}

	/** Show the validation frame for a predicitve model with a extra set of validation data. */
	public void showModelValidationWKSPGivenDataseries(NolModel2 model, Vector validateDataSeries){
		if(validateDataSeries == null){
			return;
		}
		NolValidateModelWKSP validateWKSP = new NolValidateModelWKSP(this,model,validateDataSeries);
		if(!validateWKSP.isValidValidation()){
			showOKDialog(getNolResourceString(NOVALIDATIONDATA));
			return;
		}
		showInternalFrame(validateWKSP);
	}
	public boolean isDemoVersion(){
		return isDemoVersion;
	}

	//** update the model property dialog when finishing training the model*/

	public void finishTrainingModel(NolModel2 model){
		JLayeredPane pane = getEditor();
		Component[] internalFrames = pane.getComponentsInLayer(JLayeredPane.DEFAULT_LAYER.intValue());
		boolean found = false;
System.out.println("try to updata model"+model.getName());
		for(int i=0;i<internalFrames.length;i++){
			if(internalFrames[i] instanceof NolModelWKSP ){
System.out.println("Find a NolModelWKSP");
				NolModel2 model0 = ((NolModelWKSP)internalFrames[i]).
					getModel();
				if(model.equals(model0)){
					System.out.println("Find the wksp and updateing");
					NolModelWKSP mWKSP  = (NolModelWKSP)internalFrames[i];
					mWKSP.initDataDisplay();
					break;
				}
			}
		}
		progress.validate();		
		progress.repaint(0l);
		Toolkit.getDefaultToolkit().beep();
	}

	public static void setNolResources(ResourceBundle resources) {
		nolResources = resources;
	}

	/**
	 * Set text to progress bar
	 * @param text
	 */
	public void setProgressText(String text){
		progress.setText(text);
		progress.validate();
		progress.repaint(0l);
	}
}

