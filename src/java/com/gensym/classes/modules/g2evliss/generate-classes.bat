set HOST=%1
set PORT=%2
del *.class
java com.gensym.jgi.download.DownloadInterfaces -stubs -host %HOST% -port %PORT% -classes G2-EVENT-LISTENER-SUPPORT G2-EVENT-OBJECT