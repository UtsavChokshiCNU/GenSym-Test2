Rem Rebuilds Array Classes from overrides generated from ArraySpecialImpls
Rem All user classes subclasses from any G2-ARRAY class must be regenerated
Rem assumes a G2 at localhost 1111 - make sure it has NO kb loaded
SET CLASSDIR=%SRCBOX%\java\com\gensym\classes
del /Q %CLASSDIR%\*array*.class
del /Q %CLASSDIR%\*array*.ovr
java com.gensym.util.OverrideAnalyzer %CLASSDIR%\G2ArraySpecialImpl.java %CLASSDIR%\G2Array.ovr
java com.gensym.util.OverrideAnalyzer %CLASSDIR%\ItemArraySpecialImpl.java %CLASSDIR%\ItemArray.ovr
java com.gensym.util.OverrideAnalyzer %CLASSDIR%\ValueArraySpecialImpl.java %CLASSDIR%\ValueArray.ovr
java com.gensym.util.OverrideAnalyzer %CLASSDIR%\SymbolArraySpecialImpl.java %CLASSDIR%\SymbolArray.ovr
java com.gensym.util.OverrideAnalyzer %CLASSDIR%\TextArraySpecialImpl.java %CLASSDIR%\TextArray.ovr
java com.gensym.util.OverrideAnalyzer %CLASSDIR%\TruthValueArraySpecialImpl.java %CLASSDIR%\TruthValueArray.ovr
java com.gensym.util.OverrideAnalyzer %CLASSDIR%\QuantityArraySpecialImpl.java %CLASSDIR%\QuantityArray.ovr
java com.gensym.util.OverrideAnalyzer %CLASSDIR%\FloatArraySpecialImpl.java %CLASSDIR%\FloatArray.ovr
java com.gensym.util.OverrideAnalyzer %CLASSDIR%\IntegerArraySpecialImpl.java %CLASSDIR%\IntegerArray.ovr
java com.gensym.util.DownloadInterfaces -stubs -class G2-ARRAY
java com.gensym.util.DownloadInterfaces -stubs -class ITEM-ARRAY
java com.gensym.util.DownloadInterfaces -stubs -class VALUE-ARRAY
java com.gensym.util.DownloadInterfaces -stubs -class SYMBOL-ARRAY
java com.gensym.util.DownloadInterfaces -stubs -class TEXT-ARRAY
java com.gensym.util.DownloadInterfaces -stubs -class TRUTH-VALUE-ARRAY
java com.gensym.util.DownloadInterfaces -stubs -class QUANTITY-ARRAY
java com.gensym.util.DownloadInterfaces -stubs -class FLOAT-ARRAY
java com.gensym.util.DownloadInterfaces -stubs -class INTEGER-ARRAY