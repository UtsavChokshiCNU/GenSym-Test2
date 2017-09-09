Rem Rebuilds List Classes from overrides generated from ListSpecialImpls
Rem All user classes subclasses from any G2-LIST class must be regenerated
Rem assumes a G2 at localhost 1111 - make sure it has NO kb loaded
SET CLASSDIR=%SRCBOX%\java\com\gensym\classes
del /Q %CLASSDIR%\*list*.class
del /Q %CLASSDIR%\*list*.ovr
java com.gensym.util.OverrideAnalyzer %CLASSDIR%\G2ListSpecialImpl.java %CLASSDIR%\G2List.ovr
java com.gensym.util.OverrideAnalyzer %CLASSDIR%\ItemListSpecialImpl.java %CLASSDIR%\ItemList.ovr
java com.gensym.util.OverrideAnalyzer %CLASSDIR%\ValueListSpecialImpl.java %CLASSDIR%\ValueList.ovr
java com.gensym.util.DownloadInterfaces -stubs -class G2-LIST
java com.gensym.util.DownloadInterfaces -stubs -class ITEM-LIST
java com.gensym.util.DownloadInterfaces -stubs -class VALUE-LIST
java com.gensym.util.DownloadInterfaces -stubs -class SYMBOL-LIST
java com.gensym.util.DownloadInterfaces -stubs -class TEXT-LIST
java com.gensym.util.DownloadInterfaces -stubs -class TRUTH-VALUE-LIST
java com.gensym.util.DownloadInterfaces -stubs -class QUANTITY-LIST
java com.gensym.util.DownloadInterfaces -stubs -class FLOAT-LIST
java com.gensym.util.DownloadInterfaces -stubs -class INTEGER-LIST