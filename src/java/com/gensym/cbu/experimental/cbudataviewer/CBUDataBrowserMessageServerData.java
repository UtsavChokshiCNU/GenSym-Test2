public class CBUDataBrowserMessageServerData implements CBUDataBrowserData {

  private Message message;
  private Hashtable dataCache;
  
  public CBUDataBrowserMessageServerData(Message message) {
    this.message = message;
  }
  
  public Object getPropertyValue(String attributeName) {
    //check data cached first
    if ("TargetId".equals(attributeName)) {
      return message.getTargetId();
    } else { //etc...
    }
    /*defaultTableModel.addColumn("SenderId");
    defaultTableModel.addColumn("Event Type");
    defaultTableModel.addColumn("Main Text");
    defaultTableModel.addColumn("Additional Text");
    defaultTableModel.addColumn("Priority");
    defaultTableModel.addColumn("Publication Date");p
    defaultTableModel.addColumn("Acknowledger");
    defaultTableModel.addColumn("Acknowledgement Date");*/
  }

  
}
