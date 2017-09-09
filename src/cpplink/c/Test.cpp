#include "Test.h"


static Option sOptions[] = { OPTION_SUPPRESS_OUTPUT, OPTION_STRING_CHECK};
static OptionsArray sOptionsArray = OptionsArray(sOptions, 2);

static char* sStartArgs[] = {"-nolistener", "-nolistener"};
static StartArgsArray sStartArgsArray = StartArgsArray(sStartArgs, 2);


static void usage() 
{
  cout << "cpplinktest <host> <port>" << endl << endl;
}

int main(int argc, char* argv[])
{
  char *host;
  char *port;

  if (argc < 3) {
    usage();   
    return 1;
  }

  host = argv[1]; 
  port = argv[2];  

  cout << "cpplinktest using, Host: " << host << " Port: "
    << port << endl;

  Link *link = Link::getInstance();

  link->setOptions(&sOptionsArray);
  link->setStartArgs(&sStartArgsArray);

  link->setTcpPort(6000);
  link->setLocalCallRPCName("CppLink-Call");
  link->setLocalStartRPCName("CppLink-Call");
  link->start();

  if (link->getStatus() != LINK_RUNNING) {
    cout << "Failed to start GSI!" << endl;
    return 2;
  }

  try {
    AttributeArray attrs = AttributeArray(5);
    attrs[0].setAttrName("Attr1");
    attrs[0].setSymbol("HELLO");
    attrs[1].setAttrName("Attr2");
    attrs[1].setString("Hello World");
    attrs[2].setAttrName("Attr3");
    attrs[2].setBoolean(false);
    attrs[3].setAttrName("Attr4");
    attrs[3].setInteger(10),
    attrs[4].setAttrName("Attr5");
    attrs[4].setFloat(1.0);


    ItemArray elements = ItemArray(7);
    elements[0].setSymbol("HELLO");
    elements[1].setString("Hello World");
    elements[2].setBoolean(false);
    elements[3].setInteger(100);
    elements[4].setFloat(1.0);
    elements[5].setFloat(1.0);
    elements[6].setType(STRUCTURE_TYPE);
    elements[6].setAttrs(&attrs);

    ItemArray itemArray = ItemArray(1);
    itemArray[0].setElements(&elements, SEQUENCE_TYPE);
   
    Session *session = 
      new Session((SessionCallback *) new BaseSessionHandler());

    session->connect(
      "",
      "GSI-INTERFACE",
      host,
      port,
      ""); 

    // Test simple start
    session->start("CALLME", &itemArray);
    
    // Test simple call
    ItemArray *result = session->call("GETRESULT");

    cout << "Received from G2:" << endl << endl;
    cout << *result << endl;

    // Test simple disconnect
    session->disconnect();
  }
  catch(SessionException &exc)
  {
    cout << "cpplinktest error, Code: " << exc.getErrorCode() << " Message: "
    << exc.getMessage() << endl;
    return 1;
  }
    
   cout.flush();
   cout << "cpplinktest completed successfully" << endl;
   return 0;
}