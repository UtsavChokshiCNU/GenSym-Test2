package com.gensym.demos.g2studiosample;

import com.gensym.demos.g2studiosample.commands.BrowserCommands;
import com.gensym.demos.g2studiosample.commands.PreferencesCommands;
import com.gensym.demos.g2studiosample.commands.NavigationCommands;
import com.gensym.wksp.PaletteCommands;
import com.gensym.wksp.CreationCommands;
import com.gensym.wksp.SystemMenuChoiceCommands;
import com.gensym.uitools.inspect.InspectSessionCommands;
import com.gensym.shell.commands.ConnectionCommands;
import com.gensym.shell.commands.ExitCommands;
import com.gensym.shell.commands.CondensedG2StateCommands;
import com.gensym.shell.commands.TopLevelSystemTablesCommands;
import com.gensym.shell.commands.WorkspaceCommands;
import com.gensym.shell.commands.EditCommands;
import com.gensym.shell.commands.ViewCommands;
import com.gensym.shell.commands.ComponentVisibilityCommands;
import com.gensym.demos.g2studiosample.commands.PackagePreparationCommands;
import com.gensym.demos.g2studiosample.commands.DebuggingCommands;
import com.gensym.shell.commands.ProjectCommands;
import com.gensym.demos.g2studiosample.commands.HelpCommands;
import com.gensym.shell.commands.WorkspaceInstanceCommands;
import com.gensym.shell.commands.ZoomCommands;
import com.gensym.shell.commands.ModuleCommands;
import com.gensym.shell.commands.AlignmentCommands;
import com.gensym.shell.commands.OrderCommands;
import com.gensym.shell.commands.NudgeCommands;
import com.gensym.shell.commands.G2Commands;
import com.gensym.shell.commands.ItemCommands;
import com.gensym.shell.commands.WorkspaceAnnotationCommands;
import com.gensym.demos.g2studiosample.commands.NavigationCommands;
import com.gensym.ui.Command;
import com.gensym.mdi.MDIFrame;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.message.Resource;
import com.gensym.mdi.MDIListener;
import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeEvent;
import com.gensym.shell.commands.RotateCommands;
import com.gensym.mdi.MDIEvent;
import com.gensym.mdi.MDIDocument;
import com.gensym.shell.util.WorkspaceDocument;

public class G2StudioCommands {
  private DebuggingCommands debuggingCommands;
  private CondensedG2StateCommands stateCommand;
  private TopLevelSystemTablesCommands topLevelSystemTablesCommands;
  private HelpCommands helpCommand;
  private BrowserCommands browserCommands;
  private ViewCommands viewCommand;
  private ProjectCommands projectCommands;
  private ZoomCommands zoomHandler;
  private AlignmentCommands alignmentCommands;
  private ComponentVisibilityCommands frameCommands;
  private ComponentVisibilityCommands compVisibilityCommands;
  private CreationCommands creationCommands;
  private PaletteCommands paletteCommands;
  private PackagePreparationCommands packagePreparationCommands;
  private InspectSessionCommands inspectSessionCommands;
  private WorkspaceInstanceCommands workspaceInstanceCommands;
  private WorkspaceAnnotationCommands workspaceAnnotationCommands;
  private PreferencesCommands preferencesCommands;
  private NudgeCommands nudgeCommands; 
  private OrderCommands orderCommands;
  private ModuleCommands moduleCommands;
  private ConnectionCommands cxnCommand;
  private G2Commands g2Commands;
  private EditCommands editCommand;
  private WorkspaceCommands wkspCommand;
  private NavigationCommands navigationCommands;
  private ExitCommands exitCommands;
  private Command tilingCommand;
  private RotateCommands rotateCommands;
  private ItemCommands itemCommands;

  public G2StudioCommands(Shell shell) {
    MDIFrame frame = (MDIFrame) shell.getCurrentFrame();
    ConnectionManager cxnMgr = shell.getConnectionManager();
 
    browserCommands = new BrowserCommands(frame, cxnMgr);      
    tilingCommand = frame.getManager().getTilingCommand();      
    moduleCommands = new ModuleCommands(frame, cxnMgr);
    zoomHandler = new ZoomCommands(frame);
    stateCommand = new CondensedG2StateCommands (cxnMgr);    
    nudgeCommands = new NudgeCommands(frame);
    orderCommands = new OrderCommands (frame);
    alignmentCommands = new AlignmentCommands(frame);
    navigationCommands = new NavigationCommands(shell); 
   inspectSessionCommands=new InspectSessionCommands(frame, cxnMgr);    
    workspaceAnnotationCommands = new WorkspaceAnnotationCommands(frame);
    wkspCommand = new WorkspaceCommands(frame, cxnMgr);
    cxnCommand = new ConnectionCommands(shell);
    g2Commands = new G2Commands(cxnMgr);
    workspaceInstanceCommands = new WorkspaceInstanceCommands(frame);
    preferencesCommands = new PreferencesCommands(shell);
    editCommand = new EditCommands(frame);
    helpCommand = new HelpCommands(frame);
    viewCommand = new ViewCommands(shell);
    viewCommand.setMDIMode(true);
    projectCommands = new ProjectCommands(frame, cxnMgr);
    packagePreparationCommands = new PackagePreparationCommands(frame, cxnMgr);
    debuggingCommands = new DebuggingCommands(cxnMgr);
    paletteCommands = new PaletteCommands(cxnMgr);
    creationCommands = new CreationCommands();
    itemCommands = new ItemCommands(frame);
    compVisibilityCommands = new ComponentVisibilityCommands();
    frameCommands = new ComponentVisibilityCommands();
    exitCommands = new ExitCommands(frame, cxnMgr);
    itemCommands = new ItemCommands(frame);
    rotateCommands = new RotateCommands(frame);
    creationCommands = new CreationCommands();
    initMDIListeners(frame);    
  }

  public void setOrderCommands(OrderCommands orderCommands){
    this.orderCommands = orderCommands;
  }

  public RotateCommands getRotateCommands(){
    return rotateCommands;
  }

  public void setRotateCommands(RotateCommands rotateCommands){
    this.rotateCommands = rotateCommands;
  }
  
  public Command getTilingCommand(){
    return tilingCommand;
  }

  public void setTilingCommand(Command tilingCommand){
    this.tilingCommand = tilingCommand;
  }
  
  public ExitCommands getExitCommands(){
    return exitCommands;
  }

  public void setExitCommands(ExitCommands exitCommands){
    this.exitCommands = exitCommands;
  }
  
  public DebuggingCommands getDebuggingCommands(){
    return debuggingCommands;
  }

  public void setDebuggingCommands(DebuggingCommands debuggingCommands){
    this.debuggingCommands = debuggingCommands;
  }  

  public CondensedG2StateCommands getCondensedG2StateCommands(){
    return stateCommand;
  }

  public void setCondensedG2StateCommands(CondensedG2StateCommands stateCommand){
    this.stateCommand = stateCommand;
  }  

  public TopLevelSystemTablesCommands getTopLevelSystemTablesCommands(){
    return topLevelSystemTablesCommands;
  }

  public void setTopLevelSystemTablesCommands(TopLevelSystemTablesCommands topLevelSystemTablesCommands){
    this.topLevelSystemTablesCommands = topLevelSystemTablesCommands;
  }   

  public HelpCommands getHelpCommands(){
    return helpCommand;
  }

  public void setHelpCommands(HelpCommands helpCommand){
    this.helpCommand = helpCommand;
  }   

  public BrowserCommands getBrowserCommands(){
    return browserCommands;
  }

  public void setBrowserCommands(BrowserCommands browserCommands){
    this.browserCommands = browserCommands;
  }   

  public ViewCommands getViewCommands(){
    return viewCommand;
  }

  public void setViewCommands(ViewCommands viewCommand){
    this.viewCommand = viewCommand;
  }   

  public ProjectCommands getProjectCommands(){
    return projectCommands;
  }

  public void setProjectCommands(ProjectCommands projectCommands){
    this.projectCommands = projectCommands;
  }   

  public ZoomCommands getZoomCommands(){
    return zoomHandler;
  }

  public void setZoomCommands(ZoomCommands zoomHandler){
    this.zoomHandler = zoomHandler;
  }   

  public AlignmentCommands getAlignmentCommands(){
    return alignmentCommands;
  }

  public void setAlignmentCommands(AlignmentCommands alignmentCommands){
    this.alignmentCommands = alignmentCommands;
  }

  public NudgeCommands getNudgeCommands(){
    return nudgeCommands;
  }

  public void setNudgeCommands(NudgeCommands nudgeCommands){
    this.nudgeCommands = nudgeCommands;
  }

  public OrderCommands getOrderCommands(){
    return orderCommands;
  }

  public ModuleCommands getModuleCommands(){
    return moduleCommands;
  }

  public void setModuleCommands(ModuleCommands moduleCommands){
    this.moduleCommands = moduleCommands;
  }

  public ConnectionCommands getConnectionCommands(){
    return cxnCommand;
  }

  public void setConnectionCommands(ConnectionCommands cxnCommand){
    this.cxnCommand = cxnCommand;
  }

  public G2Commands getG2Commands(){
    return g2Commands;
  }

  public void setG2Commands(G2Commands g2Commands){
    this.g2Commands = g2Commands;
  }

  public EditCommands getEditCommands(){
    return editCommand;
  }

  public void setEditCommands(EditCommands editCommand){
    this.editCommand = editCommand;
  }

  public PreferencesCommands getPreferencesCommands(){
    return preferencesCommands;
  }

  public void setPreferencesCommands(PreferencesCommands preferencesCommands){
    this.preferencesCommands = preferencesCommands;
  }  

  public WorkspaceCommands getWorkspaceCommands(){
    return wkspCommand;
  }

  public void setWorkspaceCommands(WorkspaceCommands wkspCommand){
    this.wkspCommand = wkspCommand;
  }

  public NavigationCommands getNavigationCommands(){
    return navigationCommands;
  }

  public void setNavigationCommands(NavigationCommands navigationCommands){
    this.navigationCommands = navigationCommands;
  }
  
  public WorkspaceAnnotationCommands getWorkspaceAnnotationCommands(){
    return workspaceAnnotationCommands;
  }

  public void setWorkspaceAnnotationCommands(WorkspaceAnnotationCommands workspaceAnnotationCommands){
    this.workspaceAnnotationCommands = workspaceAnnotationCommands;
  }
   
  public WorkspaceInstanceCommands getWorkspaceInstanceCommands(){
    return workspaceInstanceCommands;
  }

  public void setWorkspaceInstanceCommands(WorkspaceInstanceCommands workspaceInstanceCommands){
    this.workspaceInstanceCommands = workspaceInstanceCommands;
  }  

  public InspectSessionCommands getInspectSessionCommands(){
    return inspectSessionCommands;
  }

  public void setInspectSessionCommands(InspectSessionCommands inspectSessionCommands){
    this.inspectSessionCommands = inspectSessionCommands;
  } 

  public PackagePreparationCommands getPackagePreparationCommands(){
    return packagePreparationCommands;
  }

  public void setPackagePreparationCommands(PackagePreparationCommands packagePreparationCommands){
    this.packagePreparationCommands = packagePreparationCommands;
  } 

  public PaletteCommands getPaletteCommands(){
    return paletteCommands;
  }

  public void setPaletteCommands(PaletteCommands paletteCommands){
    this.paletteCommands = paletteCommands;
  } 

  public CreationCommands getCreationCommands(){
    return creationCommands;
  }

  public void setCreationCommands(CreationCommands creationCommands){
    this.creationCommands = creationCommands;
  }

  public ItemCommands getItemCommands(){
    return itemCommands;
  }

  public void setItemCommands(ItemCommands itemCommands){
    this.itemCommands = itemCommands;
  }   

  public ComponentVisibilityCommands getComponentVisibilityCommands(){
    return compVisibilityCommands;
  }

  public ComponentVisibilityCommands getFrameVisibilityCommands() {
    return frameCommands;
  }
  
  public void setComponentVisibilityCommands(ComponentVisibilityCommands compVisibilityCommands){
    this.compVisibilityCommands = compVisibilityCommands;
  }

  public void setFrameVisibilityCommands(ComponentVisibilityCommands frameCommands) {
    this.frameCommands = frameCommands;
  }
  
  private void initMDIListeners(MDIFrame frame) {
    DocumentListener docListener = new DocumentListener();
    frame.getManager().addMDIListener(docListener);
    MDIDocument[] docs = frame.getManager().getDocuments();
    for (int i=0; i<docs.length; i++){
      if (docs[i] instanceof WorkspaceDocument)
	docs[i].addPropertyChangeListener(docListener);
    }
    MDIDocument activeDocument = frame.getManager().getActiveDocument();
    if (activeDocument instanceof WorkspaceDocument)
      creationCommands.setWorkspaceView(((WorkspaceDocument)activeDocument).getWorkspaceView());    
  }
  
  class DocumentListener implements MDIListener, PropertyChangeListener {
    @Override
    public void documentAdded(MDIEvent event) {
      MDIDocument document = (MDIDocument)event.getDocument();
      if (document instanceof WorkspaceDocument) {
	WorkspaceDocument wkspDoc = (WorkspaceDocument)document;
	wkspDoc.addPropertyChangeListener(this);
	creationCommands.setWorkspaceView(wkspDoc.getWorkspaceView());
      }
    }
    
    @Override
    public void propertyChange(PropertyChangeEvent e) {
      WorkspaceDocument document = (WorkspaceDocument)e.getSource();
      if (e.getPropertyName().equals(WorkspaceDocument.IS_SELECTED_PROPERTY)){
	Boolean selected = (Boolean)e.getNewValue();
	if (selected.booleanValue())
	  creationCommands.setWorkspaceView(document.getWorkspaceView());
	else
	  creationCommands.setWorkspaceView(null);
      } else if (e.getPropertyName().equals(WorkspaceDocument.IS_CLOSED_PROPERTY)){
	document.removePropertyChangeListener(this);
	creationCommands.setWorkspaceView(null);
      } else if (document.isClosed()) {
	document.removePropertyChangeListener(this);
	creationCommands.setWorkspaceView(null);
      }
    }
  }
  
}

   




