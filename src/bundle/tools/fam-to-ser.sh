#!/bin/csh

if ( ! $?SRCBOX ) then
  echo "ERROR: Variable SRCBOX must be set (e.g., by running the sandbox command)."
  goto usage
endif


goto gooduse

usage:
echo 'usage: fam-to-ser'
exit 1


gooduse:

if !($?MACHINE) then
  set MACHINE=`/usr/local/bin/machine`
endif

foreach family (`ls $SRCBOX/tools/datafiles/families/*.fam`)
 $SRCBOX/bundle/c/$MACHINE/serialize-family-file $family >$family.ser


 # now for some cheap positive feedback, show the part of the fourth 
 # line of each .ser file.  The output lines look like these:
 #
 #   "e-SCOR" "2.1b0" 1  ( intelnt )
 #   "G2 Deployment" "5.1r7" 1  ( intelnt sparcsol aix hpux linux alphaosf )
 echo $family.ser
 head -4 $family.ser | tail -1 | tail +2c
end

