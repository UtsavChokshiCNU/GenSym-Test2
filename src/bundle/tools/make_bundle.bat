@echo off

if NOT "%1" == "" goto run_build
echo "Mandatory std|ent parameter is missed"
exit 1

:run_build

call make_bundle_stage %1
call make_bundle_installer %1 4qVxCM3T*@
