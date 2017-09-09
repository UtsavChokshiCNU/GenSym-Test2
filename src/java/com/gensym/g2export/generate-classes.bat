set HOST=%1
set PORT=%2
del *.class
del *.ser
rem
rem Make sure Local download is compiled
javac ../jgi/download/local/DownloadLocalClasses.java
rem
javac G2__*Base*.java *Array*.java *List*.java BlockSpecial*Impl.java LocalClassFriendAccess.java G2ClassManager.java DefinitionSpecial*Impl.java RootSpecial*Impl.java KbWorkspaceSpecial*Impl.java
java com.gensym.jgi.download.local.DownloadLocalClasses -force -host %HOST% -port %PORT% -classes KB-WORKSPACE CONNECTION
javac EntitySpecial*Impl.java ConnectionSpecialImpl.java
del Entity.class Connection.class
rem Do Export Stubs
rem ---------------------------
java com.gensym.jgi.download.local.DownloadLocalClasses -stubs -force -host %HOST% -port %PORT% -classes OBJECT KB-WORKSPACE CONNECTION CLASS-DEFINITION OBJECT-DEFINITION DEFAULT-JUNCTION
rem Same classes but G2 Proxies
rem ---------------------------
java com.gensym.jgi.download.local.DownloadLocalClasses -stubs -proxy -host %HOST% -port %PORT% -classes OBJECT KB-WORKSPACE CONNECTION CLASS-DEFINITION OBJECT-DEFINITION DEFAULT-JUNCTION
rem Do export Arrays and Lists
rem ---------------------------
java com.gensym.jgi.download.local.DownloadLocalClasses -stubs -force -host %HOST% -port %PORT% -classes G2-LIST SYMBOL-LIST INTEGER-LIST FLOAT-LIST TEXT-LIST ITEM-LIST TRUTH-VALUE-LIST SYMBOL-ARRAY INTEGER-ARRAY FLOAT-ARRAY TEXT-ARRAY ITEM-ARRAY TRUTH-VALUE-ARRAY
rem Do export Arrays and Lists G2 proxies
rem -------------------------------------
java com.gensym.jgi.download.local.DownloadLocalClasses -proxy -stubs -force -host %HOST% -port %PORT% -classes G2-LIST SYMBOL-LIST INTEGER-LIST FLOAT-LIST TEXT-LIST ITEM-LIST TRUTH-VALUE-LIST SYMBOL-ARRAY INTEGER-ARRAY FLOAT-ARRAY TEXT-ARRAY ITEM-ARRAY TRUTH-VALUE-ARRAY
