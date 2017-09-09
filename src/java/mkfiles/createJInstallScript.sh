#!/bin/csh -f

setenv SCRIPT_FILE $1
setenv ROOT_DIR $2
setenv OUTPUT_FILE $3
setenv UNIX_WRAPPER $4
setenv APPLICATION_NAME "$5"
setenv DEFAULT_DIR $6

setenv YEAR `date '+%Y'`

echo "[General]">${SCRIPT_FILE}
echo "OutputFile=${OUTPUT_FILE}">>${SCRIPT_FILE}
echo "Copyright=Copyright (C) ${YEAR}. All rights reserved.">>${SCRIPT_FILE}
echo "BuildNumber=1.0 Beta 2">>${SCRIPT_FILE}
echo "CompanyURL=www.gensym.com">>${SCRIPT_FILE}
echo "ApplicationName=${APPLICATION_NAME}">>${SCRIPT_FILE}
echo "UnixWrapper=${UNIX_WRAPPER}">>${SCRIPT_FILE}
echo "CompanyName=Gensym Corporation">>${SCRIPT_FILE}
echo "[Welcome]">>${SCRIPT_FILE}
echo "[CheckVM]">>${SCRIPT_FILE}
echo "VMUrl=http://www.javasoft.com">>${SCRIPT_FILE}
echo "VMId1=Sun 1.1 All OS">>${SCRIPT_FILE}
echo "[Target]">>${SCRIPT_FILE}
echo "DefaultDir=${DEFAULT_DIR}">>${SCRIPT_FILE}
echo "[Extract]">>${SCRIPT_FILE}
echo "RootDir=${ROOT_DIR}">>${SCRIPT_FILE}
echo "TextSuffix=.txt .java ">>${SCRIPT_FILE}
echo "IgnoreSuffix=.bak .save ~ ">>${SCRIPT_FILE}
echo "[ChangePermissions]">>${SCRIPT_FILE}
echo "RootClass=extensions.permissions.ChangePermissions">>${SCRIPT_FILE}
