package com.gensym.nols.dlg;

import java.awt.*;
import java.awt.event.*;
import java.util.*;

import javax.swing.*;
import javax.swing.border.*;

import com.gensym.nols.main.NolMainFrame;
import com.gensym.nols.main.NolSettings;

public class NolCustomDateInput  extends JDialog{
  private JFrame parent;
  private NolMainFrame frame;
  private JTextField inputField;
  private ButtonGroup radioGroup;
  private boolean isOk;
  private ControlAction actionListener;
  private KeyAction keyListener;
  private DefaultListModel keysModel;
  private DefaultListModel custFormatsModel;
  private NolList keysContents;
  private NolList custFormatsContents;
  private JScrollPane keys;
  private JScrollPane custFormats;
  private static String[] timeFormats = {
    "h       hour in am/pm (1-12)",
    "H       hour in day (0-23)",
    "k       hour in day (1-24)",
    "K       hour in am/pm (0-11)",
    "m       minute in hour",
    "s       second in minute",
    "S       millisecond",
    "a       am/pm marker",
    "z       time zone"
  };
  private static String[] dateFormats = {
    "G       era designator",
    "y       year (number)",
    "M       month in year (text or number)",
    "D       day in year (number)",
    "d       day in month (number)",
    "E       day in week (text)",
    "F       day of week in month (number)",
    "w       week in year (number)",
    "W       week in month (number)"};
  private static Vector dateTimeFormatsVector;
  private static Vector timeFormatsVector;
  private static Vector dateFormatsVector;
  private Vector customDateFormatsVector;
  private Vector customTimeFormatsVector;
  private Vector customDateTimeFormatsVector;
   
	private static final String INFOLABEL = "CustomDateInput_InforLabel";
	private static final String FORMAT_TYPE = "CustomDateInput_FormatType";
	private static final String DATE_TIME = "CustomDateInput_DateTime";
	private static final String DATE = "CustomDateInput_Date";
	private static final String TIME = "CustomDateInput_Time";
	private static final String FORMAT_PATTERN = "CustomDateInput_FormatPattern";
	private static final String AVAILABLE_FORMAT_KEYS = "CustomDateInput_AvailableFormatKeys";
	private static final String CURRENT_CUSTOM_FORMATS = "CustomDateInput_CurrentCustomFormats";
	private static final String REMOVE_FORMAT = "CustomDateInput_RemoveFormat";
	private static final String OK = "OkButtonLabel";
	private static final String CANCEL = "CancelButtonLabel";

	
static {
	timeFormatsVector = new Vector();
    for (int i=0; i<timeFormats.length; i++){
      timeFormatsVector.addElement(timeFormats[i]);
    }
	dateFormatsVector = new Vector();
    for (int i=0; i<dateFormats.length; i++){
      dateFormatsVector.addElement(dateFormats[i]);
    }
    dateTimeFormatsVector = new Vector();
    for (int i=0; i<dateFormats.length; i++){
      dateTimeFormatsVector.addElement(dateFormats[i]);
    }
    for (int i=0; i<timeFormats.length; i++){
      dateTimeFormatsVector.addElement(timeFormats[i]);
    }	  
  }

  public NolCustomDateInput (JFrame dw, String title) {
    super(dw, title, true);
    frame = (NolMainFrame)dw;
    actionListener = new ControlAction();
    keyListener = new KeyAction();
    initializeData();
    initializeLayout();
  }
  
  public void initializeData() {
    //initialize the time and date vectors
    //System.out.println("initializing Data");
    customTimeFormatsVector = NolSettings.getSettings().getCustomTimeFormatsVector();
    //for(int i=0;i<customTimeFormatsVector.size();i++) System.out.println("customTime: i "+i+" element "+customTimeFormatsVector.elementAt(i));
    customDateFormatsVector = NolSettings.getSettings().getCustomDateFormatsVector();
    //for(int i=0;i<customDateFormatsVector.size();i++) System.out.println("customDate: i "+i+" element "+customDateFormatsVector.elementAt(i));
    customDateTimeFormatsVector = NolSettings.getSettings().getCustomDateTimeFormatsVector();
    //for(int i=0;i<customDateTimeFormatsVector.size();i++) System.out.println("customDateTime: i "+i+" element "+customDateTimeFormatsVector.elementAt(i));
    //create the NolLists and ListModels for the scrollpanes
    keysModel = new DefaultListModel();
    custFormatsModel = new DefaultListModel();
    //initialize the data for the scroll pane contents
    keysContents = new NolList(keysModel);
    keysContents.addElements(dateTimeFormatsVector);
    custFormatsContents = new NolList(custFormatsModel);
    custFormatsContents.addElements(customDateTimeFormatsVector);
  }

  public void initializeLayout() {		
    // workspace is the total area of the dialog
    JPanel workSpace = new JPanel(new BorderLayout());
    workSpace.setBorder(new EmptyBorder(10,10,5,10));
    setContentPane(workSpace);

    JPanel northPane = new JPanel(new GridLayout(3,1));
    northPane.add(getInfoPane());
    northPane.add(getFormatStyle());
    northPane.add(getFormatInput());
    
    workSpace.add("North", northPane);
    workSpace.add("Center", getPatterns());
    
    JPanel southPane = new JPanel(new BorderLayout());
    southPane.add("East", getButtons());
    workSpace.add("South", southPane);
    pack();
  }

    
  public JPanel getInfoPane(){
    // infoPane contains the general info and directions
    JPanel infoPane = new JPanel(new GridLayout());
    String s = frame.getNolResourceString(INFOLABEL);
		
//		"Select the format type - Date, Time, or Date & Time, \n" +
//      "then type in the new format pattern";
    JTextArea infoLabel = new JTextArea(s);
	infoLabel.setEditable(false);
	infoLabel.setLineWrap(true);
	infoLabel.setWrapStyleWord(true);
	infoLabel.setBackground(infoPane.getBackground());
    infoPane.add(infoLabel);
    return infoPane;
  }

  public JPanel getFormatStyle(){

    // format style - radio buttons to select Date, Time, or
    //    Date & Time
    JPanel formatStyle = new JPanel(new BorderLayout());
    formatStyle.setBorder(BorderFactory.
			  createTitledBorder(frame.getNolResourceString(FORMAT_TYPE)+":"));
	formatStyle.setBackground(getContentPane().getBackground());
    
    JPanel radioPane = new JPanel(new GridLayout(1,3));
	radioPane.setBackground(getContentPane().getBackground());
    radioPane.setBorder(new EmptyBorder(5,50,5,5));

    radioGroup = new ButtonGroup();
    
    JRadioButton dateTime = new JRadioButton(frame.getNolResourceString(DATE_TIME), true);
    dateTime.setActionCommand("DateTime");
    dateTime.addActionListener(actionListener);
    radioGroup.add(dateTime);
    radioPane.add(dateTime);
    
    JRadioButton date = new JRadioButton(frame.getNolResourceString(DATE));
//    JRadioButton date = new JRadioButton("Date");
    date.setActionCommand("Date");
    date.addActionListener(actionListener);
    radioGroup.add(date);
    radioPane.add(date);

    JRadioButton time = new JRadioButton(frame.getNolResourceString(TIME));
//    JRadioButton time = new JRadioButton("Time");
    time.setActionCommand("Time");
    time.addActionListener(actionListener);
    radioGroup.add(time);
    radioPane.add(time);

    formatStyle.add("Center", radioPane);
    return formatStyle;
  }


  public JPanel getFormatInput() {
    // Format input box and the help scroll area
    JPanel formatInput = new JPanel(new GridLayout(0,1));
    formatInput.setBorder(BorderFactory.
			  createTitledBorder(frame.getNolResourceString(FORMAT_PATTERN)+":"));
	formatInput.setBackground(getContentPane().getBackground());
    
    //inside panel to hold the input box and scroll areas
    JPanel inputPane = new JPanel(new GridLayout(0,1));
    inputPane.setBorder(new EmptyBorder(5,0,5,5));
	inputPane.setBackground(getContentPane().getBackground());
    
    inputField = new JTextField();
    inputField.setBounds(10,40,170,25);
    inputField.setVisible(true);
    inputField.addKeyListener(keyListener);
    inputPane.add(inputField);

    formatInput.add(inputPane);

    return formatInput;
  }

  public JPanel getPatterns(){
    //pane to hold the scroll panes and the labels
    JPanel patterns = new JPanel (new BorderLayout());
	patterns.setBackground(getContentPane().getBackground());
    
    //labels pane
    JPanel labels = new JPanel (new GridLayout(1,2,10,5));
	labels.setBackground(getContentPane().getBackground());
    labels.setBorder(new EmptyBorder(20,0,10,0));

    //label for available format keys
    JLabel keysLabel = new JLabel(frame.getNolResourceString(AVAILABLE_FORMAT_KEYS)+":");
//    JLabel keysLabel = new JLabel("Available Format Keys:");
    keysLabel.setVisible(true);
	keysLabel.setBackground(labels.getBackground());
    labels.add(keysLabel);
    
    //label for available custom formats
    JLabel customLabel = new JLabel(frame.getNolResourceString(CURRENT_CUSTOM_FORMATS)+":");
//   JLabel customLabel = new JLabel("Current Custom Formats:");
    customLabel.setVisible(true);
	customLabel.setBackground(labels.getBackground());
    labels.add(customLabel);

    patterns.add("North", labels);

    //Scroll areas Pane
    JPanel scrolls = new JPanel(new GridLayout(1,2,10,5));
 	scrolls.setBackground(getContentPane().getBackground());
    scrolls.setBorder(new EmptyBorder(0,0,10,0));
    
    //Scroll pane to hold a Jlist with the formats
    //Jlist is initialized to all date and time formats
    keys = new JScrollPane(keysContents);
    keysContents.addMouseListener((MouseListener)actionListener);
    keys.setBounds(10,10,100,100);
    keys.setBorder(BorderFactory.createLoweredBevelBorder());
    scrolls.add(keys);
    
    //scroll pane with a list of available custom formats
    custFormats = new JScrollPane(custFormatsContents);
    custFormatsContents.addMouseListener((MouseListener)actionListener);
    custFormats.setBounds(10,10,100,100);
    custFormats.setBorder(BorderFactory.createLoweredBevelBorder());
    scrolls.add(custFormats);

    patterns.add("Center", scrolls);
    
    return patterns;
  }
   
  public JPanel getButtons(){

    //panel that contains the OK, Cancel buttons
    JPanel buttons = new JPanel(new BorderLayout());

    JPanel rmButton = new JPanel(new GridLayout(1,1));
    rmButton.setBorder(new EmptyBorder(0,0,10,0));
    JButton butRemove = new JButton(frame.getNolResourceString(REMOVE_FORMAT));
//    JButton butRemove = new JButton("Remove Format");
    butRemove.setActionCommand("remove");
    butRemove.addActionListener(actionListener);
    butRemove.setBounds(10,90,80,25);
    rmButton.add(butRemove);

    // to make buttons smaller, add an inner Pane
    JPanel smButtons = new JPanel(new GridLayout(1,2));

    JButton butOK = new JButton(frame.getNolResourceString(OK));
//    JButton butOK = new JButton("OK");
    butOK.setActionCommand("OK");
    butOK.addActionListener(actionListener);
    butOK.setBounds(10,90,80,25);
    smButtons.add(butOK);

    JButton butCancel = new JButton(frame.getNolResourceString(CANCEL));
//    JButton butCancel = new JButton("Cancel");
    butCancel.setActionCommand("Cancel");
    butCancel.addActionListener(actionListener);
    butCancel.setBounds(10,90,80,25);
    smButtons.add(butCancel);

    buttons.add("Center",rmButton);
    buttons.add("South", smButtons);
    return buttons;
  }

  public boolean getResult(){
    return isOk;
  }
  
  public Vector getCustomDateFormats(){
    return customDateFormatsVector;
  }

  public Vector getCustomTimeFormats(){
    return customTimeFormatsVector;
  }

  public Vector getCustomDateTimeFormats(){
    return customDateTimeFormatsVector;
  }
 
  private void addFormat(){
    String n = inputField.getText();
    if(n == null){
    } else if(n.equals("")){
    } else {
		  //if non-empty, add the format to the list, 
		  // and clear the inputField
		if(!(custFormatsModel.contains(n))){
			custFormatsModel.addElement(n);
			inputField.setText("");
			//check which format type is selected
			// then add the new format to its appropriate vector
			if("Date".equals(radioGroup.getSelection().getActionCommand())){
				customDateFormatsVector.addElement(n);
				NolSettings.getSettings().setCustomDateFormatsVector(customDateFormatsVector);
				NolSettings.save();
			} else if ("Time".equals(radioGroup.getSelection().getActionCommand())){
				customTimeFormatsVector.addElement(n);
				NolSettings.getSettings().setCustomTimeFormatsVector(customTimeFormatsVector);
				NolSettings.save();
			} else if ("DateTime".equals(radioGroup.getSelection().getActionCommand())){
				customDateTimeFormatsVector.addElement(n);
				NolSettings.getSettings().setCustomDateTimeFormatsVector(customDateTimeFormatsVector);
				NolSettings.save();
			}
		}
      
    }
  }

  /**
   * Control action implementation
   */
  class ControlAction extends AbstractAction implements MouseListener{
    
    ControlAction() {
      super("controlAction");
    }
    
    @Override
    public void actionPerformed(ActionEvent e) {
      
      String command = e.getActionCommand();
      if(command.equals("Date")){
		//change the contents of the scrollpane to show 
		// the date keys and custom formats only
		keysModel.removeAllElements();
		keysContents.addElements(dateFormatsVector);
		
		custFormatsModel.removeAllElements();
		custFormatsContents.addElements(customDateFormatsVector);
      }
      else if (command.equals("Time")){
		//change the contents of the scrollpanes to show
		// the time keys and custome formats only
		keysModel.removeAllElements();
		keysContents.addElements(timeFormatsVector);

		custFormatsModel.removeAllElements();
		custFormatsContents.addElements(customTimeFormatsVector);
      }
      else if (command.equals("DateTime")){
		//change the contents of the scrollpanes to show
		// the time and date keys and custom formats
		keysModel.removeAllElements();
		keysContents.addElements(dateTimeFormatsVector);

		custFormatsModel.removeAllElements();
		custFormatsContents.addElements(customDateTimeFormatsVector);
      }
      else if(command.equals ("remove")){
		//remove the selected custom format from the list
		String[] buttons = new String[] {"Yes", "No", "Cancel"};
		NolConfirmDialog confirm = new NolConfirmDialog
		  (frame,"Confirm Format Removal", buttons, 
		  "Remove selected custom format?", "question.gif");
		confirm.setBounds(200,200,350,130);
		confirm.setVisible(true);
		int result = confirm.getResult();
		if(result == 1){
		  int index = custFormatsContents.getSelectedIndex();
		  String element = (String)custFormatsModel.elementAt(index);

		  custFormatsModel.removeElementAt(index);

		  if("Date".equals(radioGroup.getSelection().getActionCommand())){
			   if(customDateFormatsVector.contains(element))
				 customDateFormatsVector.removeElement(element);
			 } else if ("Time".equals(radioGroup.getSelection().getActionCommand())){
			   if(customTimeFormatsVector.contains(element))
				 customTimeFormatsVector.removeElement(element);
			 } else if("DateTime".equals(radioGroup.getSelection().getActionCommand())){
			   if(customDateTimeFormatsVector.contains(element))
				 customDateTimeFormatsVector.removeElement(element);
			 }
		}
      } 
	  else if(command.equals("OK")){
		isOk = true;
		addFormat();
		NolCustomDateInput.this.dispose();
	  } else if(command.equals("Cancel")){
		isOk = false;
		NolCustomDateInput.this.dispose();
	  } 
     }
	
      @Override
    public void mousePressed(MouseEvent m) {}
      @Override
    public void mouseEntered(MouseEvent m) {}
      @Override
    public void mouseExited(MouseEvent m) {}
      @Override
    public void mouseReleased(MouseEvent m) {}
      public void mouseDragged(MouseEvent m) {}
      public void mouseMoved(MouseEvent m) {}
      @Override
    public void mouseClicked(MouseEvent m) {
	int clickCount =  m.getClickCount();
	if(m.getSource().equals(keysContents)){
	  if(clickCount == 2) {
	    //if double-click, get the current text, and add
	    // the first character of the selected element
	    inputField.setText(inputField.getText() +
			       ((String)(keysContents.getSelectedValue())).charAt(0));
	  }
	}
	if(m.getSource().equals(custFormatsContents)){
	  if(clickCount == 2) {
	    // if double-click, put up in the input box
	    inputField.setText((String)(custFormatsContents.getSelectedValue()));
	  }
	}
      }
     
  }

 class KeyAction implements KeyListener {
   //if return is pressed in the textfield,
   // check if text is present. If yes, add to the 
   // customFormats list

   @Override
  public void keyReleased(KeyEvent e){}
   @Override
  public void keyPressed(KeyEvent e){}
   @Override
  public void keyTyped(KeyEvent e){
     int code = e.getKeyChar();
     if (code == 13){
       addFormat();
     }
   }
   
   
 }
      
    
}

