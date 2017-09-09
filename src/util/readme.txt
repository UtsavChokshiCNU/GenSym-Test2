             Contents of util Directory
             --------------------------

This file describes the current contents of this directory.  It has been
added after the culmination of a major cleanup effort in which the
contents of the directory were moved to a variety of other cvs modules
(build, scripts, tools, oldies, helpers, disktools).  The files
that remain should ultimately be moved or removed.  The remaining
files and their reasons for being here are as follows:

Used by java builds:
-------------------
-- These should be relocated to a new module named "jbuild", which can then
   be meaningfully tied to a CVS tag or branch.

EtagsGenerator.java
UpdateJavaSandbox.bat
add-for-java-compile
build-ax2jbeans.bat
javac-if-necessary
javac-if-necessary.bat
jmake
jmake-module
jmake.bat
makeTw2ActiveX.bat
queue-javac-requests
reg-sandbox-tw2-ax-beans.bat
runmakejntw
runmakejntw.bat
tag-a-java-dir.bat
unreg-sandbox-tw2-ax-beans.bat

Now in development/scripts:
--------------------------
-- These need to be duplicated for now because they are referenced by
   older makefiles in gen/mfiles.  They can eventually be removed.
   They can be removed now if older versions are always built in a
   sandbox with an older util directory checked out into it.
   (unfortunately util was not CVS tagged appropriately, making this
   less likely and more difficult.)

errsweep
errsweep.bat
errsweep.com
runmake
runmake.bat
runmake.com
decw-share.opt  -- in scripts/vms
run-command-with-timeout

Now in /gensym/tools or replaced by scripts found there:
--------------------------------------------------------
-- These simply contain or print a message that points users to the
   new files in /gensym/tools.  These files can be removed by June, 2000
   at the latest.

promote-dependent-package
promote-package
promote-product
promoting-packages.text
remove-dependent-package
remove-package
remove-product

Must remain (for now)
---------------------
-- The following three files are used by regression testing kbs, I think.
   The hardcoded references to them would have to be changed.  This would
   have to be backpropagated to previous versions of the tests.

submit_bridge.com
bridge_run.com  -- also in [gensym.bin]
sum-ps  -- needed by the draw01 regression test

-- The following three files are used when setting the current sandbox.
   Hopefully someone will take ownership of this poorly documented set of
   scripts and move them to an appropriate place, probably
   /home/development/scripts.

sbrunmake
check-buildroot
set-up-environment

-- Others

readme.txt -- This file
g2smoke/   -- This is the leftover empty directory.  It can vanish with util.
