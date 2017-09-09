#!/bin/csh
# This script was generated to create the tar hierarchy which will be used to
# deploy in the bundle for UNIX platforms
if ($#argv < 1) then
  goto usage
endif

if ($1 == "-v") then
  set verbose = 1
  shift
endif

set platform = $1
if ($platform == "") then
  goto usage
endif

goto execute

usage:
echo "usage: $0 [-v] platform"
echo "platform = intelnt, rs6000, sparcsol, linux, linux64, alphaosf, or hp9000s700"
exit 1

execute:

if (-d /g2/bundles/g2/2011/tree/$platform-g2) then
echo "error: directory /g2/bundles/g2/2011/tree/$platform-g2 already exists -- please remove it"
exit 1
endif
if (! -d /g2) mkdir /g2
if (! -d /g2/bundles) mkdir /g2/bundles
if (! -d /g2/bundles/g2) mkdir /g2/bundles/g2
if (! -d /g2/bundles/g2/2011) mkdir /g2/bundles/g2/2011
if (! -d /g2/bundles/g2/2011/tree) mkdir /g2/bundles/g2/2011/tree
if (! -d /g2/bundles/g2/2011/tree/$platform-g2) mkdir /g2/bundles/g2/2011/tree/$platform-g2
if (! -d /g2/bundles/g2/2011/tree/$platform-g2/g2) mkdir /g2/bundles/g2/2011/tree/$platform-g2/g2
if (! -d /g2/bundles/g2/2011/tree/$platform-g2/g2/ext) mkdir /g2/bundles/g2/2011/tree/$platform-g2/g2/ext
if (! -d /g2/bundles/g2/2011/tree/$platform-g2/g2/kbs) mkdir /g2/bundles/g2/2011/tree/$platform-g2/g2/kbs
if (! -d /g2/bundles/g2/2011/tree/$platform-g2/g2/fonts) mkdir /g2/bundles/g2/2011/tree/$platform-g2/g2/fonts
if (! -d /g2/bundles/g2/2011/tree/$platform-g2/gw) mkdir /g2/bundles/g2/2011/tree/$platform-g2/gw
if (! -d /g2/bundles/g2/2011/tree/$platform-g2/gw/kbs) mkdir /g2/bundles/g2/2011/tree/$platform-g2/gw/kbs
if (! -d /g2/bundles/g2/2011/tree/$platform-g2/g2/examples) mkdir /g2/bundles/g2/2011/tree/$platform-g2/g2/examples
if (! -d /g2/bundles/g2/2011/tree/$platform-g2/gsi) mkdir /g2/bundles/g2/2011/tree/$platform-g2/gsi
if (! -d /g2/bundles/g2/2011/tree/$platform-g2/javalink) mkdir /g2/bundles/g2/2011/tree/$platform-g2/javalink
if (! -d /g2/bundles/g2/2011/tree/$platform-g2/javalink/classes) mkdir /g2/bundles/g2/2011/tree/$platform-g2/javalink/classes
if (! -d /g2/bundles/g2/2011/tree/$platform-g2/doc) mkdir /g2/bundles/g2/2011/tree/$platform-g2/doc
if (! -d /g2/bundles/g2/2011/tree/$platform-g2/doc/javalink) mkdir /g2/bundles/g2/2011/tree/$platform-g2/doc/javalink
if (! -d /g2/bundles/g2/2011/tree/$platform-g2/corbalink) mkdir /g2/bundles/g2/2011/tree/$platform-g2/corbalink
if (! -d /g2/bundles/g2/2011/tree/$platform-g2/oracle) mkdir /g2/bundles/g2/2011/tree/$platform-g2/oracle
if (! -d /g2/bundles/g2/2011/tree/$platform-g2/oracle/bin) mkdir /g2/bundles/g2/2011/tree/$platform-g2/oracle/bin
if (! -d /g2/bundles/g2/2011/tree/$platform-g2/jdbc) mkdir /g2/bundles/g2/2011/tree/$platform-g2/jdbc
if (! -d /g2/bundles/g2/2011/tree/$platform-g2/doc/bridges) mkdir /g2/bundles/g2/2011/tree/$platform-g2/doc/bridges
if (! -d /g2/bundles/g2/2011/tree/$platform-g2/doc/bridges/jdbc) mkdir /g2/bundles/g2/2011/tree/$platform-g2/doc/bridges/jdbc
if (! -d /g2/bundles/g2/2011/tree/$platform-g2/jre) mkdir /g2/bundles/g2/2011/tree/$platform-g2/jre
if (! -d /g2/bundles/g2/2011/tree/$platform-g2/jmail) mkdir /g2/bundles/g2/2011/tree/$platform-g2/jmail
if (! -d /g2/bundles/g2/2011/tree/$platform-g2/doc/bridges/jmail) mkdir /g2/bundles/g2/2011/tree/$platform-g2/doc/bridges/jmail
if (! -d /g2/bundles/g2/2011/tree/$platform-g2/jms) mkdir /g2/bundles/g2/2011/tree/$platform-g2/jms
if (! -d /g2/bundles/g2/2011/tree/$platform-g2/g2i) mkdir /g2/bundles/g2/2011/tree/$platform-g2/g2i
if (! -d /g2/bundles/g2/2011/tree/$platform-g2/g2i/kbs) mkdir /g2/bundles/g2/2011/tree/$platform-g2/g2i/kbs
if (! -d /g2/bundles/g2/2011/tree/$platform-g2/doc/bridges/jms) mkdir /g2/bundles/g2/2011/tree/$platform-g2/doc/bridges/jms
if (! -d /g2/bundles/g2/2011/tree/$platform-g2/sockman) mkdir /g2/bundles/g2/2011/tree/$platform-g2/sockman
if (! -d /g2/bundles/g2/2011/tree/$platform-g2/doc/bridges/sockman) mkdir /g2/bundles/g2/2011/tree/$platform-g2/doc/bridges/sockman
if (! -d /g2/bundles/g2/2011/tree/$platform-g2/jsnmp) mkdir /g2/bundles/g2/2011/tree/$platform-g2/jsnmp
if (! -d /g2/bundles/g2/2011/tree/$platform-g2/hla) mkdir /g2/bundles/g2/2011/tree/$platform-g2/hla

cd /tmp
if ($platform == intelnt) then
cp -p $SRCBOX/bundle/ok/watermark.txt /g2/bundles/g2/2011/tree/$platform-g2
endif

if ($platform == intelnt) then
tar xf /g2/stage/eship/dep/$platform/g2-2011/tape/g2-2011.tar "$platform/g2/g2.exe" "$platform/g2/g2passwd.exe" 
cd $platform/g2/
mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/g2
cd ../..
rm -rf $platform
endif

if ($platform != intelnt) then
tar xf /g2/stage/eship/dep/$platform/g2-2011/tape/g2-2011.tar "$platform/g2/g2" "$platform/g2/g2passwd" 
cd $platform/g2/
mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/g2
cd ../..
rm -rf $platform
endif

tar xf /g2/stage/eship/dep/$platform/g2-2011/tape/g2-2011.tar "$platform/g2/index.dic" "$platform/g2/kojin.dic" "$platform/g2/main.dic" 
cd $platform/g2/
mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/g2
cd ../..
rm -rf $platform

tar xf /g2/stage/eship/dep/$platform/g2-2011/tape/g2-2011.tar 
cd $platform/g2/
(cd ext ; mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/g2/ext)
cd ../..
rm -rf $platform

tar xf /g2/stage/eship/dep/$platform/g2-2011/tape/g2-2011.tar "$platform/g2/g2.ok" 
cd $platform/g2/
mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/g2
cd ../..
rm -rf $platform

tar xf /g2/stage/eship/indep/kbs-2011/tape/kbs-2011.tar 
cd indep/kbs/
chmod a+w ./*.* ./*/*.*
mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/g2/kbs
cd ../..
rm -rf indep

tar xf /g2/stage/eship/indep/fonts-2011/tape/fonts-2011.tar 
cd indep/fonts/
chmod a+w ./*.* ./*/*.*
mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/g2/fonts
cd ../..
rm -rf indep

if ($platform != intelnt) then
tar xf /g2/stage/eship/indep/demos-2011/tape/demos-2011.tar "indep/demos/startserver" 
cd indep/demos/
mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/g2
cd ../..
rm -rf indep
endif

tar xf /g2/stage/eship/dep/$platform/gw-2011/tape/gw-2011.tar "$platform/gw/kbs/gwex3.kb" "$platform/gw/kbs/gwex2.kb" "$platform/gw/kbs/gwex1.kb" "$platform/gw/kbs/gwlow.kb" 
cd $platform/gw/
(cd kbs ; mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/gw/kbs)
cd ../..
rm -rf $platform

if ($platform == intelnt) then
tar xf /g2/stage/eship/dep/$platform/tw-2011/tape/tw-2011.tar "$platform/tw/tw.exe" 
cd $platform/tw/
mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/g2
cd ../..
rm -rf $platform
endif

if ($platform != intelnt) then
tar xf /g2/stage/eship/dep/$platform/tw-2011/tape/tw-2011.tar "$platform/tw/tw" 
cd $platform/tw/
mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/g2
cd ../..
rm -rf $platform
endif

if ($platform == intelnt) then
tar xf /g2/stage/eship/dep/$platform/tw-2011-NG/tape/tw-2011-NG.tar "$platform/tw/twng.exe" 
cd $platform/tw/
mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/g2
cd ../..
rm -rf $platform
endif

if ($platform == intelnt) then
tar xf /g2/stage/eship/dep/$platform/tw-2011/tape/tw-2011.tar "$platform/tw/win2000/gdiplus.dll" 
cd $platform/tw/
(cd win2000 ; mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/g2)
cd ../..
rm -rf $platform
endif

if ($platform == intelnt) then
tar xf /g2/stage/eship/dep/$platform/twax-2011/tape/twax-2011.tar "$platform/twax/TwControl.cab" "$platform/twax/unregisterTwControl.bat" "$platform/twax/TwControl.ocx" "$platform/twax/install.html" "$platform/twax/registerTwControl.bat" 
cd $platform/twax/
mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/g2
cd ../..
rm -rf $platform
endif

if ($platform == intelnt) then
tar xf /g2/stage/eship/dep/$platform/twax-2011/tape/twax-2011.tar 
cd $platform/twax/
(cd examples ; mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/g2/examples)
cd ../..
rm -rf $platform
endif

if ($platform == intelnt) then
tar xf /g2/stage/eship/dep/$platform/workspace-view-2011/tape/workspace-view-2011.tar "$platform/workspace-view/WSView.frm" "$platform/workspace-view/WSView.frx" "$platform/workspace-view/WorkspaceView.ocx" "$platform/workspace-view/WorkspaceViewDemo.exe" "$platform/workspace-view/WorkspaceViewDemo.vbp" "$platform/workspace-view/WorkspaceViewDemo.vbw" "$platform/workspace-view/registerWSV.bat" "$platform/workspace-view/unregisterWSV.bat" "$platform/workspace-view/wsvdemo.kb" "$platform/workspace-view/wsview.html" 
cd $platform/workspace-view/
mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/g2
cd ../..
rm -rf $platform
endif

if ($platform != intelnt) then
tar xf /g2/stage/eship/dep/$platform/gsi-2011/tape/gsi-2011.tar 
cd $platform/gsi/
mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/gsi
cd ../..
rm -rf $platform
endif

tar xf /g2/stage/eship/dep/$platform/gw-2011/tape/gw-2011.tar 
cd $platform/gw/
mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/gw
cd ../..
rm -rf $platform

cp -p $SRCBOX/bundle/ok/gw-gsi-v8.obf /g2/bundles/g2/2011/tree/$platform-g2/gw
$SRCBOX/bundle/c/$MACHINE/obfuscator -d -F /g2/bundles/g2/2011/tree/$platform-g2/gw/gw-gsi-v8.obf -k known_seed
$SRCBOX/bundle/c/$MACHINE/obfuscator -F /g2/bundles/g2/2011/tree/$platform-g2/gw/gw-gsi-v8.obf -k dfbbb4c1-d0ff-484f-8184-3b2a47ed7bf3

if ($platform == intelnt) then
tar xf /g2/stage/eship/dep/$platform/gw-2011/tape/gw-2011.tar "$platform/gw/run-gw.bat" 
cd $platform/gw/
mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/gw
cd ../..
rm -rf $platform
endif

if ($platform == intelnt) then
cp -p $SRCBOX/bundle/ok/gsi.ok /g2/bundles/g2/2011/tree/$platform-g2/gw
endif

if ($platform != intelnt) then
tar xf /g2/stage/eship/dep/$platform/jvl-2011/tape/jvl-2011.tar 
cd $platform/jvl/
mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/javalink
cd ../..
rm -rf $platform
endif

if ($platform == intelnt) then
tar xf /g2/stage/eship/dep/$platform/jvl-2011/tape/jvl-2011.tar 
cd $platform/jvl/
mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/javalink
cd ../..
rm -rf $platform
endif

tar xf /g2/stage/eship/indep/g2pkgreadme-2011/tape/g2pkgreadme-2011.tar "indep/g2pkgreadme/readme-javalink.html" 
cd indep/g2pkgreadme/
mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/javalink
cd ../..
rm -rf indep

if ($platform == intelnt) then
tar xf /g2/stage/eship/dep/$platform/jvl-2011/tape/jvl-2011.tar "$platform/jvl/bin/.com.gensym.properties" 
cd $platform/jvl/
(cd bin ; mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/javalink/classes)
cd ../..
rm -rf $platform
endif

tar xf /g2/stage/eship/indep/jvl-javadoc-2011/tape/jvl-javadoc-2011.tar 
cd indep/jvl-javadoc/
mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/doc/javalink
cd ../..
rm -rf indep

if ($platform != alphaosf) then
tar xf /g2/stage/eship/dep/$platform/corbalink-2011/tape/corbalink-2011.tar 
cd $platform/corbalink/
mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/corbalink
cd ../..
rm -rf $platform
endif

tar xf /g2/stage/eship/dep/$platform/g2oracle-2011/tape/g2oracle-2011.tar 
cd $platform/g2oracle/
mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/oracle
cd ../..
rm -rf $platform

cp -p $SRCBOX/bundle/ok/oracle-gsi-v8.obf /g2/bundles/g2/2011/tree/$platform-g2/oracle
$SRCBOX/bundle/c/$MACHINE/obfuscator -d -F /g2/bundles/g2/2011/tree/$platform-g2/oracle/oracle-gsi-v8.obf -k known_seed
$SRCBOX/bundle/c/$MACHINE/obfuscator -F /g2/bundles/g2/2011/tree/$platform-g2/oracle/oracle-gsi-v8.obf -k dfbbb4c1-d0ff-484f-8184-3b2a47ed7bf3

if ($platform == intelnt) then
tar xf /g2/stage/eship/dep/$platform/g2oracle-2011/tape/g2oracle-2011.tar "$platform/g2oracle/bin/run-g2-ora7.bat" 
cd $platform/g2oracle/
(cd bin ; mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/oracle/bin)
cd ../..
rm -rf $platform
endif

if ($platform == intelnt) then
tar xf /g2/stage/eship/dep/$platform/g2oracle-2011/tape/g2oracle-2011.tar "$platform/g2oracle/bin/run-g2-ora80.bat" 
cd $platform/g2oracle/
(cd bin ; mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/oracle/bin)
cd ../..
rm -rf $platform
endif

if ($platform == intelnt) then
tar xf /g2/stage/eship/dep/$platform/g2oracle-2011/tape/g2oracle-2011.tar "$platform/g2oracle/bin/run-g2-ora81.bat" 
cd $platform/g2oracle/
(cd bin ; mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/oracle/bin)
cd ../..
rm -rf $platform
endif

if ($platform == intelnt) then
tar xf /g2/stage/eship/dep/$platform/g2oracle-2011/tape/g2oracle-2011.tar "$platform/g2oracle/bin/run-g2-ora90.bat" 
cd $platform/g2oracle/
(cd bin ; mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/oracle/bin)
cd ../..
rm -rf $platform
endif

if ($platform == intelnt) then
tar xf /g2/stage/eship/dep/$platform/g2oracle-2011/tape/g2oracle-2011.tar "$platform/g2oracle/bin/run-g2-ora92.bat" 
cd $platform/g2oracle/
(cd bin ; mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/oracle/bin)
cd ../..
rm -rf $platform
endif

if ($platform == intelnt) then
tar xf /g2/stage/eship/dep/$platform/g2oracle-2011/tape/g2oracle-2011.tar "$platform/g2oracle/bin/run-g2-ora10.bat" 
cd $platform/g2oracle/
(cd bin ; mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/oracle/bin)
cd ../..
rm -rf $platform
endif

if ($platform == intelnt) then
cp -p $SRCBOX/bundle/ok/gsi.ok /g2/bundles/g2/2011/tree/$platform-g2/oracle
endif

tar xf /g2/stage/eship/indep/g2pkgreadme-2011/tape/g2pkgreadme-2011.tar "indep/g2pkgreadme/readme-g2.html" 
cd indep/g2pkgreadme/
mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2
cd ../..
rm -rf indep

if ($platform == intelnt) then
tar xf /g2/stage/eship/dep/$platform/jdbc-2011/tape/jdbc-2011.tar 
cd $platform/jdbc/
mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/jdbc
cd ../..
rm -rf $platform
endif

if ($platform != intelnt) then
tar xf /g2/stage/eship/dep/$platform/jdbc-2011/tape/jdbc-2011.tar 
cd $platform/jdbc/
mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/jdbc
cd ../..
rm -rf $platform
endif

tar xf /g2/stage/eship/indep/jdbcdoc-2011/tape/jdbcdoc-2011.tar 
cd indep/jdbcdoc/
mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/doc/bridges/jdbc
cd ../..
rm -rf indep

if ($platform == intelnt || $platform == sparcsol || $platform == hp9000s700 || $platform == linux || $platform == linux64) then
tar xf /g2/stage/eship/dep/$platform/jre-16r26_03/tape/jre-16r26_03.tar 
cd $platform/jre/
mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/jre
cd ../..
rm -rf $platform
endif

if ($platform == rs6000) then
tar xf /g2/stage/eship/dep/$platform/jre-14r1/tape/jre-14r1.tar 
cd $platform/jre/
mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/jre
cd ../..
rm -rf $platform
endif

if ($platform == hpia64) then
tar xf /g2/stage/eship/dep/$platform/jre-14r2_09/tape/jre-14r2_09.tar 
cd $platform/jre/
mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/jre
cd ../..
rm -rf $platform
endif

if ($platform == intelnt) then
tar xf /g2/stage/eship/dep/$platform/jmail-23r1/tape/jmail-23r1.tar 
cd $platform/jmail/
mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/jmail
cd ../..
rm -rf $platform
endif

if ($platform != intelnt) then
tar xf /g2/stage/eship/dep/$platform/jmail-23r1/tape/jmail-23r1.tar 
cd $platform/jmail/
mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/jmail
cd ../..
rm -rf $platform
endif

tar xf /g2/stage/eship/indep/jmaildoc-23r0/tape/jmaildoc-23r0.tar 
cd indep/jmaildoc/
mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/doc/bridges/jmail
cd ../..
rm -rf indep

if ($platform == intelnt) then
tar xf /g2/stage/eship/dep/$platform/jms-23r1/tape/jms-23r1.tar 
cd $platform/jms/
mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/jms
cd ../..
rm -rf $platform
endif

if ($platform == linux || $platform == linux64) then
tar xf /g2/stage/eship/dep/$platform/jms-23r1/tape/jms-23r1.tar 
cd $platform/jms/
mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/jms
cd ../..
rm -rf $platform
endif

if ($platform == hp9000s700 || $platform == hpia64) then
tar xf /g2/stage/eship/dep/$platform/jms-23r1/tape/jms-23r1.tar 
cd $platform/jms/
mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/jms
cd ../..
rm -rf $platform
endif

tar xf /g2/stage/eship/indep/g2i-23r1/tape/g2i-23r1.tar "indep/g2i/kbs/grtl.kb" "indep/g2i/kbs/gerr.kb" 
cd indep/g2i/
chmod a+w ./*.* ./*/*.*
(cd kbs ; mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/g2i/kbs)
cd ../..
rm -rf indep

if ($platform == intelnt || $platform == hp9000s700 || $platform == hpia64 || $platform == linux || $platform == linux64) then
tar xf /g2/stage/eship/indep/jmsdoc-23r0/tape/jmsdoc-23r0.tar 
cd indep/jmsdoc/
mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/doc/bridges/jms
cd ../..
rm -rf indep
endif

if ($platform == intelnt) then
tar xf /g2/stage/eship/dep/$platform/sockman-42r1/tape/sockman-42r1.tar 
cd $platform/sockman/
mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/sockman
cd ../..
rm -rf $platform
endif

if ($platform != intelnt) then
tar xf /g2/stage/eship/dep/$platform/sockman-42r1/tape/sockman-42r1.tar 
cd $platform/sockman/
mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/sockman
cd ../..
rm -rf $platform
endif

tar xf /g2/stage/eship/indep/sockmandoc-42r0/tape/sockmandoc-42r0.tar 
cd indep/sockmandoc/
mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/doc/bridges/sockman
cd ../..
rm -rf indep

if ($platform == intelnt) then
tar xf /g2/stage/eship/dep/$platform/g2snmpgn-40r0/tape/g2snmpgn-40r0.tar 
cd $platform/g2snmpgn/
mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/jsnmp
cd ../..
rm -rf $platform
endif

if ($platform == sparcsol || $platform == hp9000s700 || $platform == hpia64) then
tar xf /g2/stage/eship/dep/$platform/g2snmpgn-40r0/tape/g2snmpgn-40r0.tar 
cd $platform/g2snmpgn/
mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/jsnmp
cd ../..
rm -rf $platform
endif

if ($platform == linux || $platform == linux64) then
tar xf /g2/stage/eship/dep/$platform/g2snmpgn-40r0/tape/g2snmpgn-40r0.tar 
cd $platform/g2snmpgn/
mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/jsnmp
cd ../..
rm -rf $platform
endif

if ($platform == intelnt) then
tar xf /g2/stage/eship/dep/$platform/hla-20r1/tape/hla-20r1.tar 
cd $platform/hla/
mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/hla
cd ../..
rm -rf $platform
endif

if ($platform == alphaosf) then
tar xf /g2/stage/eship/dep/$platform/jre-14r2-4p2/tape/jre-14r2-4p2.tar 
cd $platform/jre/
mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/jre
cd ../..
rm -rf $platform
endif

if ($platform == intelnt) then
tar xf /g2/stage/eship/indep/g2winhelp-2011/tape/g2winhelp-2011.tar "indep/g2winhelp/ActiveXLinkHelp.chm" "indep/g2winhelp/BPMSHelp.chm" "indep/g2winhelp/BRMSHelp.chm" "indep/g2winhelp/DownloadInterfacesHelp.chm" "indep/g2winhelp/G2-CORBALinkHelp.chm" "indep/g2winhelp/G2-DatabaseBridgeHelp.chm" "indep/g2winhelp/G2-HLAHelp.chm" "indep/g2winhelp/G2-JMSBridgeHelp.chm" "indep/g2winhelp/G2-JMailBridgeHelp.chm" "indep/g2winhelp/G2-JSockManHelp.chm" "indep/g2winhelp/G2-ODBCBridgeHelp.chm" "indep/g2winhelp/G2-OPCClientHelp.chm" "indep/g2winhelp/G2-OracleBridgeHelp.chm" "indep/g2winhelp/G2-PIBridgeHelp.chm" "indep/g2winhelp/G2-SNMPBridgeHelp.chm" "indep/g2winhelp/G2-SybaseBridgeHelp.chm" "indep/g2winhelp/G2-WebLinkHelp.chm" "indep/g2winhelp/G2BeanBuilderHelp.chm" "indep/g2winhelp/G2Bridges.html" "indep/g2winhelp/G2BundleReleaseNotesHelp.chm" "indep/g2winhelp/G2ClassReferenceHelp.chm" "indep/g2winhelp/G2Core.html" "indep/g2winhelp/G2DevUtilities.html" "indep/g2winhelp/G2DevelopersGuideHelp.chm" "indep/g2winhelp/G2GatewayHelp.chm" "indep/g2winhelp/G2JavaLink.html" "indep/g2winhelp/G2JavaLinkHelp.chm" "indep/g2winhelp/G2LanguageReferenceHelp.chm" "indep/g2winhelp/G2ProToolsHelp.chm" "indep/g2winhelp/G2ReferenceManualHelp.chm" "indep/g2winhelp/G2SystemProceduresHelp.chm" "indep/g2winhelp/G2SystemProceduresReferenceCardHelp.chm" "indep/g2winhelp/G2Utilities.html" "indep/g2winhelp/GDDHelp.chm" "indep/g2winhelp/GDIHelp.chm" "indep/g2winhelp/GDPMHelp.chm" "indep/g2winhelp/GDSMHelp.chm" "indep/g2winhelp/GDUHelp.chm" "indep/g2winhelp/GEDPHelp.chm" "indep/g2winhelp/GERRHelp.chm" "indep/g2winhelp/GEUCHelp.chm" "indep/g2winhelp/GEVMHelp.chm" "indep/g2winhelp/GFRHelp.chm" "indep/g2winhelp/GMSHelp.chm" "indep/g2winhelp/GOLDDevelopersGuideHelp.chm" "indep/g2winhelp/GOLDHelp.chm" "indep/g2winhelp/GRLBHelp.chm" "indep/g2winhelp/GRPEHelp.chm" "indep/g2winhelp/GRTLHelp.chm" "indep/g2winhelp/GUIDEHelp.chm" "indep/g2winhelp/GUIDEUILHelp.chm" "indep/g2winhelp/GWEBHelp.chm" "indep/g2winhelp/GXLHelp.chm" "indep/g2winhelp/GettingStarted.html" "indep/g2winhelp/GettingStartedWithG2Help.chm" "indep/g2winhelp/Master.chm" "indep/g2winhelp/Master.html" "indep/g2winhelp/Master2.html" "indep/g2winhelp/Master3.html" "indep/g2winhelp/TelewindowsHelp.chm" 
cd indep/g2winhelp/
mv -f `ls -A` /g2/bundles/g2/2011/tree/$platform-g2/g2
cd ../..
rm -rf indep
endif

# and a final collection of files we didn't want
find /g2/bundles/g2/2011/tree/$platform-g2 -name contents.txt -exec rm \{\} \;
