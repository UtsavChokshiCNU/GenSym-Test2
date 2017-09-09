#!/bin/sh

. ./set_env_i386-sol.sh


# startserver -- Start a G2 server, with a module search path that contains all
# installed bundle products.

# Any G2 command line arguments may be supplied to this script, and will be
# passed along.

for dir in ${SRCBOX}/gdanol/nol/kbs ${SRCBOX}/gdanol/gda/kbs ${SRCBOX}/gdanol/gspc/kbs ${SRCBOX}/gdanol/common/kbs ${SRCBOX}/gdanol/common/kbs/utilities ${SRCBOX}/gdanol/common/demos/kbs ${SRCBOX}/gdanol/common/demos/kbs ${SRCBOX}/kbs ${SRCBOX}/kbs/tools ${SRCBOX}/kbs/sources ${SRCBOX}/kbs/src ${SRCBOX}/g2i/kbs ${SRCBOX}/g2db/kbs ${SRCBOX}/g2opc/kbs ${SRCBOX}/g2pi/kbs ${SRCBOX}/jmail/kbs ${SRCBOX}/jms/kbs ${SRCBOX}/g2/kbs/utils ${SRCBOX}/gda/kbs ${SRCBOX}/oracle/kbs ${SRCBOX}/pi/kbs ${SRCBOX}/sybase/kbs ${SRCBOX}/opcclient/kbs ${SRCBOX}/protools/kbs ${SRCBOX}/corbalink/kbs ${SRCBOX}/javalink/kbs ${JAVA_SRCBOX}/products/javalink/common/kbs ${SRCBOX}/tw2/kbs ${SRCBOX}/sockman/kbs ${SRCBOX}/jsnmp/kbs ${SRCBOX}/optegrity/kbs ${SRCBOX}/nol/kbs ${SRCBOX}/rethink/kbs ${SRCBOX}/escor/kbs ${SRCBOX}/g2i/sites/Integrity/kbs ${SRCBOX}/gw/kbs ${SRCBOX}/hla/kbs 
  do
  if [ -d ${dir} ] 
  then
    G2_MODULE_SEARCH_PATH="${G2_MODULE_SEARCH_PATH} ${dir}/"
  fi
done

export G2_MODULE_SEARCH_PATH

$G2EXEC $* -kb $SRCBOX/g2i/sites/Integrity/kbs/integrity-dev.kb -copy-logbook-on-console -integrity-auto-build $SRCBOX/g2i


