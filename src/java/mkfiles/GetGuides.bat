:GetGuides.bat
:AUTHOR: sjw
:DATE CREATED: 4/28/99

cd %SRCBOX%

: REMOVE OLD GUIDES
rd /S/Q %SRCBOX%\java\products\javalink\common\docs\guides\*
rd /S/Q %SRCBOX%\java\products\javalink\common\docs\guides\*

: INSTALL NEW GUIDES 
rsh sdev4 "mkdir /bt/t2/java/products/javalink/common/docs/guides; cd /home/docs/tw2t/10r2/gensym/Javalink/docs/guides; cp -r * /bt/t2/java/products/javalink/common/docs/guides"
rsh sdev4 "mkdir /bt/t2/java/products/sequoia/common/docs/guides; cd /home/docs/tw2t/10r2/gensym/Telewindows2Toolkit/ActiveX/docs/Guides; cp -r * /bt/t2/java/products/sequoia/common/docs/guides;cd /home/docs/tw2t/10r2/gensym/Telewindows2Toolkit/Java/docs/guides; cp -r * /bt/t2/java/products/sequoia/common/docs/guides; cd /home/docs/tw2t/10r2/gensym/Telewindows2Toolkit; cp * /bt/t2/java/products/sequoia/common/docs/guides"

: REMOVE ACTIVEX GUIDES
cd %SRCBOX%\java\products\javalink\common\docs\guides 
rm ActiveXDevGuide
