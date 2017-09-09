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
echo "platform = intelnt, rs6000, sparcsol, linux, or hp9000s700"
exit 1

execute:

if (-d /home/mhd/trees/$platform-G2) then
echo "error: directory /home/mhd/trees/$platform-G2 already exists -- please remove it"
exit 1
endif
if (! -d /home) mkdir /home
if (! -d /home/mhd) mkdir /home/mhd
if (! -d /home/mhd/trees) mkdir /home/mhd/trees
if (! -d /home/mhd/trees/$platform-G2) mkdir /home/mhd/trees/$platform-G2
if (! -d /home/mhd/trees/$platform-G2/g2) mkdir /home/mhd/trees/$platform-G2/g2
if (! -d /home/mhd/trees/$platform-G2/protools) mkdir /home/mhd/trees/$platform-G2/protools
if (! -d /home/mhd/trees/$platform-G2/doc) mkdir /home/mhd/trees/$platform-G2/doc
if (! -d /home/mhd/trees/$platform-G2/doc/g2) mkdir /home/mhd/trees/$platform-G2/doc/g2
if (! -d /home/mhd/trees/$platform-G2/doc/g2/starterkit) mkdir /home/mhd/trees/$platform-G2/doc/g2/starterkit
if (! -d /home/mhd/trees/$platform-G2/doc/g2/starterkit/html) mkdir /home/mhd/trees/$platform-G2/doc/g2/starterkit/html
if (! -d /home/mhd/trees/$platform-G2/doc/g2/g2) mkdir /home/mhd/trees/$platform-G2/doc/g2/g2
if (! -d /home/mhd/trees/$platform-G2/doc/g2/g2/html) mkdir /home/mhd/trees/$platform-G2/doc/g2/g2/html
if (! -d /home/mhd/trees/$platform-G2/doc/g2/utilities) mkdir /home/mhd/trees/$platform-G2/doc/g2/utilities
if (! -d /home/mhd/trees/$platform-G2/doc/g2/utilities/html) mkdir /home/mhd/trees/$platform-G2/doc/g2/utilities/html
if (! -d /home/mhd/trees/$platform-G2/doc/javalink) mkdir /home/mhd/trees/$platform-G2/doc/javalink
if (! -d /home/mhd/trees/$platform-G2/doc/tw2) mkdir /home/mhd/trees/$platform-G2/doc/tw2
if (! -d /home/mhd/trees/$platform-G2/doc/bridges) mkdir /home/mhd/trees/$platform-G2/doc/bridges
if (! -d /home/mhd/trees/$platform-G2/doc/bridges/activexlink) mkdir /home/mhd/trees/$platform-G2/doc/bridges/activexlink
if (! -d /home/mhd/trees/$platform-G2/doc/bridges/corbalink) mkdir /home/mhd/trees/$platform-G2/doc/bridges/corbalink
if (! -d /home/mhd/trees/$platform-G2/doc/bridges/oracle) mkdir /home/mhd/trees/$platform-G2/doc/bridges/oracle
if (! -d /home/mhd/trees/$platform-G2/doc/bridges/sybase) mkdir /home/mhd/trees/$platform-G2/doc/bridges/sybase
if (! -d /home/mhd/trees/$platform-G2/doc/bridges/opclink) mkdir /home/mhd/trees/$platform-G2/doc/bridges/opclink
if (! -d /home/mhd/trees/$platform-G2/doc/bridges/odbc) mkdir /home/mhd/trees/$platform-G2/doc/bridges/odbc
if (! -d /home/mhd/trees/$platform-G2/g2/ext) mkdir /home/mhd/trees/$platform-G2/g2/ext
if (! -d /home/mhd/trees/$platform-G2/g2/kbs) mkdir /home/mhd/trees/$platform-G2/g2/kbs
if (! -d /home/mhd/trees/$platform-G2/g2/fonts) mkdir /home/mhd/trees/$platform-G2/g2/fonts
if (! -d /home/mhd/trees/$platform-G2/tw2) mkdir /home/mhd/trees/$platform-G2/tw2
if (! -d /home/mhd/trees/$platform-G2/gsi) mkdir /home/mhd/trees/$platform-G2/gsi
if (! -d /home/mhd/trees/$platform-G2/gda) mkdir /home/mhd/trees/$platform-G2/gda
if (! -d /home/mhd/trees/$platform-G2/gw) mkdir /home/mhd/trees/$platform-G2/gw
if (! -d /home/mhd/trees/$platform-G2/javalink) mkdir /home/mhd/trees/$platform-G2/javalink
if (! -d /home/mhd/trees/$platform-G2/javalink/classes) mkdir /home/mhd/trees/$platform-G2/javalink/classes
if (! -d /home/mhd/trees/$platform-G2/activexlink) mkdir /home/mhd/trees/$platform-G2/activexlink
if (! -d /home/mhd/trees/$platform-G2/activexlink/demos) mkdir /home/mhd/trees/$platform-G2/activexlink/demos
if (! -d /home/mhd/trees/$platform-G2/corbalink) mkdir /home/mhd/trees/$platform-G2/corbalink
if (! -d /home/mhd/trees/$platform-G2/opclink) mkdir /home/mhd/trees/$platform-G2/opclink
if (! -d /home/mhd/trees/$platform-G2/oracle) mkdir /home/mhd/trees/$platform-G2/oracle
if (! -d /home/mhd/trees/$platform-G2/sybase) mkdir /home/mhd/trees/$platform-G2/sybase
if (! -d /home/mhd/trees/$platform-G2/odbc) mkdir /home/mhd/trees/$platform-G2/odbc

cd /tmp
if ($platform == intelnt) then
cp -p /home/development/installers/release-files/watermark.txt /home/mhd/trees/$platform-G2
endif

cp -p /home/development/installers/release-files/g2-development-1-v5-oct1-mar25-2002.ok /home/mhd/trees/$platform-G2/g2

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/watermark.txt /home/mhd/trees/$platform-G2
endif

cp -p /home/development/installers/release-files/g2-development-1-v5-jul1-dec25-2001.ok /home/mhd/trees/$platform-G2/g2

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/watermark.txt /home/mhd/trees/$platform-G2
endif

cp -p /home/development/installers/release-files/g2-development-1-v5-apr1-sep25-2001.ok /home/mhd/trees/$platform-G2/g2

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/watermark.txt /home/mhd/trees/$platform-G2
endif

cp -p /home/development/installers/release-files/g2-development-1-v5-jan1-jun25-2001.ok /home/mhd/trees/$platform-G2/g2

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/watermark.txt /home/mhd/trees/$platform-G2
endif

cp -p /home/development/installers/release-files/g2-development-1-v5-oct1-mar25-2001.ok /home/mhd/trees/$platform-G2/g2

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/watermark.txt /home/mhd/trees/$platform-G2
endif

cp -p /home/development/installers/release-files/g2-development-1-v5-jul1-dec25-2000.ok /home/mhd/trees/$platform-G2/g2

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/watermark.txt /home/mhd/trees/$platform-G2
endif

cp -p /home/development/installers/release-files/g2-development-32-v5.ok /home/mhd/trees/$platform-G2/g2

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/watermark.txt /home/mhd/trees/$platform-G2
endif

cp -p /home/development/installers/release-files/g2-development-28-v5.ok /home/mhd/trees/$platform-G2/g2

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/watermark.txt /home/mhd/trees/$platform-G2
endif

cp -p /home/development/installers/release-files/g2-development-24-v5.ok /home/mhd/trees/$platform-G2/g2

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/watermark.txt /home/mhd/trees/$platform-G2
endif

cp -p /home/development/installers/release-files/g2-development-20-v5.ok /home/mhd/trees/$platform-G2/g2

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/watermark.txt /home/mhd/trees/$platform-G2
endif

cp -p /home/development/installers/release-files/g2-development-16-v5.ok /home/mhd/trees/$platform-G2/g2

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/watermark.txt /home/mhd/trees/$platform-G2
endif

cp -p /home/development/installers/release-files/g2-development-12-v5.ok /home/mhd/trees/$platform-G2/g2

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/watermark.txt /home/mhd/trees/$platform-G2
endif

cp -p /home/development/installers/release-files/g2-development-10-v5.ok /home/mhd/trees/$platform-G2/g2

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/watermark.txt /home/mhd/trees/$platform-G2
endif

cp -p /home/development/installers/release-files/g2-development-9-v5.ok /home/mhd/trees/$platform-G2/g2

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/watermark.txt /home/mhd/trees/$platform-G2
endif

cp -p /home/development/installers/release-files/g2-development-8-v5.ok /home/mhd/trees/$platform-G2/g2

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/watermark.txt /home/mhd/trees/$platform-G2
endif

cp -p /home/development/installers/release-files/g2-development-7-v5.ok /home/mhd/trees/$platform-G2/g2

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/watermark.txt /home/mhd/trees/$platform-G2
endif

cp -p /home/development/installers/release-files/g2-development-6-v5.ok /home/mhd/trees/$platform-G2/g2

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/watermark.txt /home/mhd/trees/$platform-G2
endif

cp -p /home/development/installers/release-files/g2-development-5-v5.ok /home/mhd/trees/$platform-G2/g2

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/watermark.txt /home/mhd/trees/$platform-G2
endif

cp -p /home/development/installers/release-files/g2-development-4-v5.ok /home/mhd/trees/$platform-G2/g2

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/watermark.txt /home/mhd/trees/$platform-G2
endif

cp -p /home/development/installers/release-files/g2-development-3-v5.ok /home/mhd/trees/$platform-G2/g2

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/watermark.txt /home/mhd/trees/$platform-G2
endif

cp -p /home/development/installers/release-files/g2-development-2-v5.ok /home/mhd/trees/$platform-G2/g2

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/watermark.txt /home/mhd/trees/$platform-G2
endif

cp -p /home/development/installers/release-files/g2-development-1-v5.ok /home/mhd/trees/$platform-G2/g2

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/watermark.txt /home/mhd/trees/$platform-G2
endif

tar xf /gensym/st/ab/eship/indep/protools-51r0/tape/protools-51r0.tar
cd indep/protools/
cp -pr ./* /home/mhd/trees/$platform-G2/protools
cd ../..
rm -rf indep

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/watermark.txt /home/mhd/trees/$platform-G2
endif

tar xf /gensym/st/ab/eship/indep/g2stkdoc-51r7/tape/g2stkdoc-51r7.tar
cd indep/g2stkdoc/
cp -pr ./* /home/mhd/trees/$platform-G2/doc/g2/starterkit/html
cd ../..
rm -rf indep

tar xf /gensym/st/ab/eship/indep/g2doc-50r3/tape/g2doc-50r3.tar
cd indep/g2doc/
cp -pr ./* /home/mhd/trees/$platform-G2/doc/g2/g2/html
cd ../..
rm -rf indep

tar xf /gensym/st/ab/eship/indep/g2utldoc-50r1/tape/g2utldoc-50r1.tar
cd indep/g2utldoc/
cp -pr ./* /home/mhd/trees/$platform-G2/doc/g2/utilities/html
cd ../..
rm -rf indep

tar xf /gensym/st/ab/eship/indep/jvldoc-11r0/tape/jvldoc-11r0.tar
cd indep/jvldoc/
cp -pr ./* /home/mhd/trees/$platform-G2/doc/javalink
cd ../..
rm -rf indep

tar xf /gensym/st/ab/eship/indep/tw2doc-11r0/tape/tw2doc-11r0.tar
cd indep/tw2doc/
cp -pr ./* /home/mhd/trees/$platform-G2/doc/tw2
cd ../..
rm -rf indep

if ($platform == intelnt) then
tar xf /gensym/st/ab/eship/dep/$platform/axl-10r1-CF05/tape/axl-10r1-CF05.tar
cd $platform/axl/
cp -pr docs/* /home/mhd/trees/$platform-G2/doc/bridges/activexlink
cd ../..
rm -rf $platform
endif

tar xf /gensym/st/ab/eship/indep/corbalinkdoc-10r1/tape/corbalinkdoc-10r1.tar
cd indep/corbalinkdoc/
cp -pr ./* /home/mhd/trees/$platform-G2/doc/bridges/corbalink
cd ../..
rm -rf indep

tar xf /gensym/st/ab/eship/indep/g2stkpdf-51r7/tape/g2stkpdf-51r7.tar
cd indep/g2stkpdf/
cp -pr ./* /home/mhd/trees/$platform-G2/doc/g2/starterkit
cd ../..
rm -rf indep

tar xf /gensym/st/ab/eship/indep/g2ps-50r3-pdf/tape/g2ps-50r3-pdf.tar
cd indep/g2ps/
cp -pr ./* /home/mhd/trees/$platform-G2/doc/g2/g2
cd ../..
rm -rf indep

tar xf /gensym/st/ab/eship/indep/g2utlps-50r1-pdf/tape/g2utlps-50r1-pdf.tar
cd indep/g2utlps/
cp -pr ./* /home/mhd/trees/$platform-G2/doc/g2/utilities
cd ../..
rm -rf indep

tar xf /gensym/st/ab/eship/indep/g2oradoc-60r4/tape/g2oradoc-60r4.tar
cd indep/g2oradoc/
cp -pr ./* /home/mhd/trees/$platform-G2/doc/bridges/oracle
cd ../..
rm -rf indep

tar xf /gensym/st/ab/eship/indep/g2sybdoc-60r4/tape/g2sybdoc-60r4.tar
cd indep/g2sybdoc/
cp -pr ./* /home/mhd/trees/$platform-G2/doc/bridges/sybase
cd ../..
rm -rf indep

tar xf /gensym/st/ab/eship/indep/opclinkdoc-10r0/tape/opclinkdoc-10r0.tar
cd indep/opclinkdoc/
cp -pr ./* /home/mhd/trees/$platform-G2/doc/bridges/opclink
cd ../..
rm -rf indep

tar xf /gensym/st/ab/eship/indep/g2odbcdoc-60r4/tape/g2odbcdoc-60r4.tar
cd indep/g2odbcdoc/
cp -pr ./* /home/mhd/trees/$platform-G2/doc/bridges/odbc
cd ../..
rm -rf indep

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/watermark.txt /home/mhd/trees/$platform-G2
endif

if ($platform == intelnt) then
tar xf /gensym/st/ab/eship/dep/$platform/g2-51r7/tape/g2-51r7.tar $platform/g2/g2.exe  
cd $platform/g2/
cp -pr ./* /home/mhd/trees/$platform-G2/g2
cd ../..
rm -rf $platform
endif

if ($platform == sparcsol || $platform == rs6000 || $platform == hp9000s700 || $platform == linux) then
tar xf /gensym/st/ab/eship/dep/$platform/g2-51r7/tape/g2-51r7.tar $platform/g2/g2  
cd $platform/g2/
cp -pr ./* /home/mhd/trees/$platform-G2/g2
cd ../..
rm -rf $platform
endif

if ($platform == intelnt) then
tar xf /gensym/st/ab/eship/dep/$platform/g2-51r7/tape/g2-51r7.tar $platform/g2/g2passwd.exe  
cd $platform/g2/
cp -pr ./* /home/mhd/trees/$platform-G2/g2
cd ../..
rm -rf $platform
endif

if ($platform == sparcsol || $platform == rs6000 || $platform == hp9000s700 || $platform == linux) then
tar xf /gensym/st/ab/eship/dep/$platform/g2-51r7/tape/g2-51r7.tar $platform/g2/g2passwd  
cd $platform/g2/
cp -pr ./* /home/mhd/trees/$platform-G2/g2
cd ../..
rm -rf $platform
endif

tar xf /gensym/st/ab/eship/dep/$platform/g2-51r7/tape/g2-51r7.tar $platform/g2/index.dic  
cd $platform/g2/
cp -pr ./* /home/mhd/trees/$platform-G2/g2
cd ../..
rm -rf $platform

tar xf /gensym/st/ab/eship/dep/$platform/g2-51r7/tape/g2-51r7.tar $platform/g2/kojin.dic  
cd $platform/g2/
cp -pr ./* /home/mhd/trees/$platform-G2/g2
cd ../..
rm -rf $platform

tar xf /gensym/st/ab/eship/dep/$platform/g2-51r7/tape/g2-51r7.tar $platform/g2/main.dic  
cd $platform/g2/
cp -pr ./* /home/mhd/trees/$platform-G2/g2
cd ../..
rm -rf $platform

tar xf /gensym/st/ab/eship/dep/$platform/g2-51r7/tape/g2-51r7.tar
cd $platform/g2/
cp -pr ext/* /home/mhd/trees/$platform-G2/g2/ext
cd ../..
rm -rf $platform

if ($platform == intelnt) then
tar xf /gensym/st/ab/eship/dep/$platform/g2-51r7/tape/g2-51r7.tar $platform/g2/gen16ut.dll  
cd $platform/g2/
cp -pr ./* /home/mhd/trees/$platform-G2/g2
cd ../..
rm -rf $platform
endif

if ($platform == intelnt) then
tar xf /gensym/st/ab/eship/dep/$platform/g2-51r7/tape/g2-51r7.tar $platform/g2/gen32.dll  
cd $platform/g2/
cp -pr ./* /home/mhd/trees/$platform-G2/g2
cd ../..
rm -rf $platform
endif

if ($platform == intelnt) then
tar xf /gensym/st/ab/eship/dep/$platform/g2-51r7/tape/g2-51r7.tar $platform/g2/gen32ut.dll  
cd $platform/g2/
cp -pr ./* /home/mhd/trees/$platform-G2/g2
cd ../..
rm -rf $platform
endif

if ($platform == intelnt) then
tar xf /gensym/st/ab/eship/dep/$platform/g2-51r7/tape/g2-51r7.tar $platform/g2/g2.ok  
cd $platform/g2/
cp -pr ./* /home/mhd/trees/$platform-G2/g2
cd ../..
rm -rf $platform
endif

tar xf /gensym/st/ab/eship/indep/kbs-51r7/tape/kbs-51r7.tar
cd indep/kbs/
chmod a+w ./*.* ./*/*.*
cp -pr ./* /home/mhd/trees/$platform-G2/g2/kbs
cd ../..
rm -rf indep

tar xf /gensym/st/ab/eship/indep/fonts-51r7/tape/fonts-51r7.tar
cd indep/fonts/
chmod a+w ./*.* ./*/*.*
cp -pr ./* /home/mhd/trees/$platform-G2/g2/fonts
cd ../..
rm -rf indep

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/watermark.txt /home/mhd/trees/$platform-G2
endif

if ($platform == intelnt) then
tar xf /gensym/st/ab/eship/dep/$platform/tw-51r7/tape/tw-51r7.tar $platform/tw/tw.exe  
cd $platform/tw/
cp -pr ./* /home/mhd/trees/$platform-G2/g2
cd ../..
rm -rf $platform
endif

if ($platform == sparcsol || $platform == rs6000 || $platform == hp9000s700 || $platform == linux) then
tar xf /gensym/st/ab/eship/dep/$platform/tw-51r7/tape/tw-51r7.tar $platform/tw/tw  
cd $platform/tw/
cp -pr ./* /home/mhd/trees/$platform-G2/g2
cd ../..
rm -rf $platform
endif

if ($platform == intelnt) then
tar xf /gensym/st/ab/eship/dep/$platform/tw-51r7/tape/tw-51r7.tar $platform/tw/nptwplug.dll  
cd $platform/tw/
cp -pr ./* /home/mhd/trees/$platform-G2/g2
cd ../..
rm -rf $platform
endif

if ($platform == intelnt) then
tar xf /gensym/st/ab/eship/dep/$platform/tw-51r7/tape/tw-51r7.tar $platform/tw/gen16ut.dll  
cd $platform/tw/
cp -pr ./* /home/mhd/trees/$platform-G2/g2
cd ../..
rm -rf $platform
endif

if ($platform == intelnt) then
tar xf /gensym/st/ab/eship/dep/$platform/tw-51r7/tape/tw-51r7.tar $platform/tw/gen32.dll  
cd $platform/tw/
cp -pr ./* /home/mhd/trees/$platform-G2/g2
cd ../..
rm -rf $platform
endif

if ($platform == intelnt) then
tar xf /gensym/st/ab/eship/dep/$platform/tw-51r7/tape/tw-51r7.tar $platform/tw/gen32ut.dll  
cd $platform/tw/
cp -pr ./* /home/mhd/trees/$platform-G2/g2
cd ../..
rm -rf $platform
endif

tar xf /gensym/st/ab/eship/indep/fonts-51r7/tape/fonts-51r7.tar
cd indep/fonts/
chmod a+w ./*.* ./*/*.*
cp -pr ./* /home/mhd/trees/$platform-G2/g2/fonts
cd ../..
rm -rf indep

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/watermark.txt /home/mhd/trees/$platform-G2
endif

if ($platform != intelnt && $platform != rs6000) then
tar xf /gensym/st/ab/eship/dep/$platform/tw2-11r0-EXEC/tape/tw2-11r0-EXEC.tar
cd $platform/tw2/
cp -pr ./* /home/mhd/trees/$platform-G2/tw2
cd ../..
rm -rf $platform
endif

if ($platform == intelnt) then
tar xf /gensym/st/ab/eship/dep/$platform/tw2-11r0b/tape/tw2-11r0b.tar
cd $platform/tw2/
rm -rf components/bin/unInstall.bat
rm -rf components/bin/unInstaller.bat
cp -pr components/* /home/mhd/trees/$platform-G2/tw2
cd ../..
rm -rf $platform
endif

if ($platform == rs6000) then
tar xf /gensym/st/ab/eship/dep/$platform/tw2-11b0-EXEC/tape/tw2-11b0-EXEC.tar
cd $platform/tw2/
cp -pr ./* /home/mhd/trees/$platform-G2/tw2
cd ../..
rm -rf $platform
endif

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/watermark.txt /home/mhd/trees/$platform-G2
endif

tar xf /gensym/st/ab/eship/dep/$platform/gsi-51r7/tape/gsi-51r7.tar
cd $platform/gsi/
cp -pr ./* /home/mhd/trees/$platform-G2/gsi
cd ../..
rm -rf $platform

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/watermark.txt /home/mhd/trees/$platform-G2
endif

tar xf /gensym/st/ab/eship/indep/gda-40r1/tape/gda-40r1.tar
cd indep/gda/
cp -pr ./* /home/mhd/trees/$platform-G2/gda
cd ../..
rm -rf indep

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/watermark.txt /home/mhd/trees/$platform-G2
endif

tar xf /gensym/st/ab/eship/dep/$platform/gw-10r2-CG21/tape/gw-10r2-CG21.tar
cd $platform/gw/
cp -pr ./* /home/mhd/trees/$platform-G2/gw
cd ../..
rm -rf $platform

cp -p /home/development/installers/release-files/gw-gsi.ok /home/mhd/trees/$platform-G2/gw

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/gsi.ok /home/mhd/trees/$platform-G2/gw
endif

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/watermark.txt /home/mhd/trees/$platform-G2
endif

if ($platform != intelnt && $platform != rs6000) then
tar xf /gensym/st/ab/eship/dep/$platform/jvl-11r0-EXEC/tape/jvl-11r0-EXEC.tar
cd $platform/jvl/
cp -pr ./* /home/mhd/trees/$platform-G2/javalink
cd ../..
rm -rf $platform
endif

if ($platform == intelnt) then
tar xf /gensym/st/ab/eship/dep/$platform/jvl-11r0/tape/jvl-11r0.tar
cd $platform/jvl/
cp -pr components/* /home/mhd/trees/$platform-G2/javalink
cd ../..
rm -rf $platform
endif

if ($platform == rs6000) then
tar xf /gensym/st/ab/eship/dep/$platform/jvl-11b0-EXEC/tape/jvl-11b0-EXEC.tar
cd $platform/jvl/
cp -pr ./* /home/mhd/trees/$platform-G2/javalink
cd ../..
rm -rf $platform
endif

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/.com.gensym.properties /home/mhd/trees/$platform-G2/javalink/classes
endif

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/watermark.txt /home/mhd/trees/$platform-G2
endif

if ($platform == intelnt) then
tar xf /gensym/st/ab/eship/dep/$platform/axl-10r1-CF05/tape/axl-10r1-CF05.tar $platform/axl/G2Com.dll  
cd $platform/axl/
cp -pr ./* /home/mhd/trees/$platform-G2/activexlink
cd ../..
rm -rf $platform
endif

if ($platform == intelnt) then
tar xf /gensym/st/ab/eship/dep/$platform/axl-10r1-CF05/tape/axl-10r1-CF05.tar $platform/axl/gsi.dll  
cd $platform/axl/
cp -pr ./* /home/mhd/trees/$platform-G2/activexlink
cd ../..
rm -rf $platform
endif

if ($platform == intelnt) then
tar xf /gensym/st/ab/eship/dep/$platform/axl-10r1-CF05/tape/axl-10r1-CF05.tar $platform/axl/ReadMe.htm  
cd $platform/axl/
cp -pr ./* /home/mhd/trees/$platform-G2/activexlink
cd ../..
rm -rf $platform
endif

if ($platform == intelnt) then
tar xf /gensym/st/ab/eship/dep/$platform/axl-10r1-CF05/tape/axl-10r1-CF05.tar $platform/axl/g2com.kb  
cd $platform/axl/
cp -pr ./* /home/mhd/trees/$platform-G2/activexlink
cd ../..
rm -rf $platform
endif

if ($platform == intelnt) then
tar xf /gensym/st/ab/eship/dep/$platform/axl-10r1-CF05/tape/axl-10r1-CF05.tar
cd $platform/axl/
cp -pr demos/* /home/mhd/trees/$platform-G2/activexlink/demos
cd ../..
rm -rf $platform
endif

if ($platform == intelnt) then
tar xf /gensym/st/ab/eship/dep/$platform/axl-10r1-CF05/tape/axl-10r1-CF05.tar $platform/axl/runme.bat  
cd $platform/axl/
cp -pr ./* /home/mhd/trees/$platform-G2/activexlink
cd ../..
rm -rf $platform
endif

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/watermark.txt /home/mhd/trees/$platform-G2
endif

if ($platform != rs6000) then
tar xf /gensym/st/ab/eship/dep/$platform/corbalink-10r1-CD24/tape/corbalink-10r1-CD24.tar
cd $platform/corbalink/
cp -pr ./* /home/mhd/trees/$platform-G2/corbalink
cd ../..
rm -rf $platform
endif

if ($platform == rs6000) then
tar xf /gensym/st/ab/eship/dep/$platform/corbalink-10r1-CJ12/tape/corbalink-10r1-CJ12.tar
cd $platform/corbalink/
cp -pr ./* /home/mhd/trees/$platform-G2/corbalink
cd ../..
rm -rf $platform
endif

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/watermark.txt /home/mhd/trees/$platform-G2
endif

if ($platform == intelnt) then
tar xf /gensym/st/ab/eship/dep/$platform/opclink-10r0/tape/opclink-10r0.tar
cd $platform/opclink/
cp -pr ./* /home/mhd/trees/$platform-G2/opclink
cd ../..
rm -rf $platform
endif

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/opclink-gsi.ok /home/mhd/trees/$platform-G2/opclink
endif

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/gsi.ok /home/mhd/trees/$platform-G2/opclink
endif

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/watermark.txt /home/mhd/trees/$platform-G2
endif

if ($platform != rs6000) then
tar xf /gensym/st/ab/eship/dep/$platform/g2oracle-60r4-N23-8/tape/g2oracle-60r4-N23-8.tar
cd $platform/g2oracle/
cp -pr ./* /home/mhd/trees/$platform-G2/oracle
cd ../..
rm -rf $platform
endif

if ($platform == rs6000) then
tar xf /gensym/st/ab/eship/dep/$platform/g2oracle-60r4/tape/g2oracle-60r4.tar
cd $platform/g2oracle/
cp -pr ./* /home/mhd/trees/$platform-G2/oracle
cd ../..
rm -rf $platform
endif

cp -p /home/development/installers/release-files/oracle-gsi.ok /home/mhd/trees/$platform-G2/oracle

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/gsi.ok /home/mhd/trees/$platform-G2/oracle
endif

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/watermark.txt /home/mhd/trees/$platform-G2
endif

tar xf /gensym/st/ab/eship/dep/$platform/g2sybase-60r4/tape/g2sybase-60r4.tar
cd $platform/g2sybase/
cp -pr ./* /home/mhd/trees/$platform-G2/sybase
cd ../..
rm -rf $platform

cp -p /home/development/installers/release-files/sybase-gsi.ok /home/mhd/trees/$platform-G2/sybase

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/gsi.ok /home/mhd/trees/$platform-G2/sybase
endif

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/watermark.txt /home/mhd/trees/$platform-G2
endif

if ($platform == intelnt) then
tar xf /gensym/st/ab/eship/dep/$platform/g2odbc-60r4/tape/g2odbc-60r4.tar
cd $platform/g2odbc/
cp -pr ./* /home/mhd/trees/$platform-G2/odbc
cd ../..
rm -rf $platform
endif

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/odbc-gsi.ok /home/mhd/trees/$platform-G2/odbc
endif

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/gsi.ok /home/mhd/trees/$platform-G2/odbc
endif

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/watermark.txt /home/mhd/trees/$platform-G2
endif

cp -p /home/development/installers/release-files/g2-package-readme.txt /home/mhd/trees/$platform-G2

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/readme.txt /home/mhd/trees/$platform-G2
endif

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/watermark.txt /home/mhd/trees/$platform-G2
endif

cp -p /home/development/installers/release-files/g2-deployment-4-v5.ok /home/mhd/trees/$platform-G2/g2

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/watermark.txt /home/mhd/trees/$platform-G2
endif

cp -p /home/development/installers/release-files/g2-deployment-8-v5.ok /home/mhd/trees/$platform-G2/g2

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/watermark.txt /home/mhd/trees/$platform-G2
endif

cp -p /home/development/installers/release-files/g2-deployment-12-v5.ok /home/mhd/trees/$platform-G2/g2

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/watermark.txt /home/mhd/trees/$platform-G2
endif

cp -p /home/development/installers/release-files/g2-deployment-16-v5.ok /home/mhd/trees/$platform-G2/g2

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/watermark.txt /home/mhd/trees/$platform-G2
endif

cp -p /home/development/installers/release-files/g2-deployment-20-v5.ok /home/mhd/trees/$platform-G2/g2

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/watermark.txt /home/mhd/trees/$platform-G2
endif

cp -p /home/development/installers/release-files/g2-deployment-24-v5.ok /home/mhd/trees/$platform-G2/g2

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/watermark.txt /home/mhd/trees/$platform-G2
endif

cp -p /home/development/installers/release-files/g2-deployment-28-v5.ok /home/mhd/trees/$platform-G2/g2

if ($platform == intelnt) then
cp -p /home/development/installers/release-files/watermark.txt /home/mhd/trees/$platform-G2
endif

cp -p /home/development/installers/release-files/g2-deployment-32-v5.ok /home/mhd/trees/$platform-G2/g2

# and a final collection of files we didn't want
find /home/mhd/trees/$platform-G2 -name contents.txt -exec rm \{\} \;
