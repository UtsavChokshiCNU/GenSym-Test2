#!/bin/csh
# This script generates a given number of evaluation license 
# keys for Netsleuth for the given platform (intelnt or sparcsol).


if ($#argv < 3) goto usage


set how_many=$1
# check for positive, reasonable integer!

set platform=$2
if (($platform != intelnt) && ($platform != sparcsol)) then
  echo "bad platform: $platform"
  goto usage
endif

set type=$3

if (($type != eval) && ($type != 500) && ($type != 1000) && ($type != 2000) && ($type != 5000) && ($type != 10000) && ($type != unlimited)) then
  # unlimited is not available through this script; not requested by NS team
  echo "bad type: $type"
  goto usage
endif


# Variable Setup

# codes.h:        #define INTELNT_CODE  0
# codes.h:        #define SPARCSOL_CODE 1
if ($platform == intelnt) set system_id=0
if ($platform == sparcsol) set system_id=1
# netsleuth.fam:  index: 5
set family_id=5
# netsleuth.fam:  bundle: NetSleuth / id: 51
set bundle_id=51
# netsleuth.fam:  component: NetSleuth (required) / index: 1
# netsleuth.fam:  component: Evaluation Authorization, 10,000-Device Limit (required) / index: 2
# netsleuth.fam:  components: 500, 1000, 2000, 5000, 10000, unlimited / indexes: 3, 4, 5, 6, 7, 8, 9
switch ($type)
 case eval:
  set component_indices=(1 2)
  breaksw
 case 500:
  set component_indices=(1 3)
  breaksw
 case 1000:
  set component_indices=(1 4)
  breaksw
 case 2000:
  set component_indices=(1 5)
  breaksw
 case 5000:
  set component_indices=(1 6)
  breaksw
 case 10000:
  set component_indices=(1 7)
  breaksw
 case unlimited:
  set component_indices=(1 8)
  breaksw
 default:
  echo "bad type: $type"
  goto usage
  breaksw
endsw

goto execute

# Execute

usage:
echo "usage: $0 how_many platform type"
echo "how_many = a positive integer"
echo "platform = intelnt or sparcsol"
echo "type = eval, 500, 1000, 2000, 5000, 10000, or unlimited"
exit 1

execute: 
echo "# Netsleuth Batch License Keys: $how_many keys"
echo "# Platform: $platform"
echo "# Authorization type: $type"
echo "# by `echo $user` on `date`"
echo ""

repeat $how_many ./createkey_and_pause.sh $system_id $family_id $bundle_id $component_indices





