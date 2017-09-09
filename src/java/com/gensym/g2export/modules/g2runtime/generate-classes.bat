set HOST=%1
set PORT=%2
del *.class
del *.ser
javac G2rtMessageSpecialImpl.java 
java com.gensym.jgi.download.local.DownloadLocalClasses -stubs -force -host %HOST% -port %PORT% -classes G2RT-RUNTIME G2RT-MESSAGE G2RT-OBJECT-PROXY G2RT-REMOTE-RUNTIME G2RT-REPLY-SET G2RT-MESSAGE-HANDLER G2RT-DISTRIBUTED-OBJECT G2RT-BASIC-MESSAGE
javac G2rtMessageSpecial_G2Proxy_Impl.java G2rtDistributedObjectSpecial_G2Proxy_Impl.java
java com.gensym.jgi.download.local.DownloadLocalClasses -proxy -stubs -force -host %HOST% -port %PORT% -classes G2RT-RUNTIME G2RT-MESSAGE G2RT-OBJECT-PROXY G2RT-REMOTE-RUNTIME G2RT-REPLY-SET G2RT-MESSAGE-HANDLER G2RT-DISTRIBUTED-OBJECT G2RT-MOBILITY-LISTENER G2RT-MOBILITY-EVENT G2RT-BASIC-MESSAGE

