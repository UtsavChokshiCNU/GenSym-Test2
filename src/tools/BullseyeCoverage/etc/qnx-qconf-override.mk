# $Revision: 9892 $ $Date: 2009-04-15 10:09:13 -0700 (Wed, 15 Apr 2009) $
# Copyright (c) Bullseye Testing Technology

# QNX Momentics

# NTO X86 target 
CC_nto_x86_gcc = covc $(QNX_HOST)/usr/bin/ntox86-gcc$(gcc_ver_suffix) 
LD_nto_x86_gcc = covc $(QNX_HOST)/usr/bin/ntox86-gcc$(gcc_ver_suffix) 

CC_nto_x86_gcc_qcc = covc $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)gcc_ntox86 -c
LD_nto_x86_gcc_qcc = covc $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)gcc_ntox86

CC_nto_x86_icc = covc icc -c
LD_nto_x86_icc = covc icc

CC_nto_x86_icc_qcc = covc $(QNX_HOST)/usr/bin/qcc -Vicc_ntox86 -c
LD_nto_x86_icc_qcc = covc $(QNX_HOST)/usr/bin/qcc -Vicc_ntox86

# NTO PPC target 
CC_nto_ppc_gcc = covc $(QNX_HOST)/usr/bin/ntoppc-gcc$(gcc_ver_suffix) -c
LD_nto_ppc_gcc = covc $(QNX_HOST)/usr/bin/ntoppc-gcc$(gcc_ver_suffix) 

CC_nto_ppc_gcc_qcc = covc $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)gcc_ntoppc -c
LD_nto_ppc_gcc_qcc = covc $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)gcc_ntoppc

# NTO MIPS target
CC_nto_mips_gcc = covc $(QNX_HOST)/usr/bin/ntomips-gcc$(gcc_ver_suffix) -c
LD_nto_mips_gcc = covc $(QNX_HOST)/usr/bin/ntomips-gcc$(gcc_ver_suffix) 

CC_nto_mips_gcc_qcc = covc $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)gcc_ntomips -c
LD_nto_mips_gcc_qcc = covc $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)gcc_ntomips

# NTO ARM target
CC_nto_arm_gcc = covc $(QNX_HOST)/usr/bin/ntoarm-gcc$(gcc_ver_suffix) -c
LD_nto_arm_gcc = covc $(QNX_HOST)/usr/bin/ntoarm-gcc$(gcc_ver_suffix) 

CC_nto_arm_gcc_qcc = covc $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)gcc_ntoarm -c
LD_nto_arm_gcc_qcc = covc $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)gcc_ntoarm

# NTO SH target
CC_nto_sh_gcc = covc $(QNX_HOST)/usr/bin/ntosh-gcc$(gcc_ver_suffix) -c
LD_nto_sh_gcc = covc $(QNX_HOST)/usr/bin/ntosh-gcc$(gcc_ver_suffix) 

CC_nto_sh_gcc_qcc = covc $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)gcc_ntosh -c
LD_nto_sh_gcc_qcc = covc $(QNX_HOST)/usr/bin/qcc -V$(gcc_ver_string)gcc_ntosh
