CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

#project name
PROJECT(libcprim)

#head file path
INCLUDE_DIRECTORIES(../specific/intelnt ../jpeg/c ../common/c/include)
#source directory

SET(SRC_LIST 
./c/backtrac.c
./c/clipboard.c
./c/contain.c
./c/cprim.c
./c/cprocess.c
./c/cstreams.c
./c/ctime.c
./c/dialogs.c
./c/dtoa.c
./c/event.c
./c/events.c
./c/filedlg.cpp
./c/g2gpubridge.c
./c/g2longint.c
./c/g2ptrs.c
./c/g2signal.c
./c/g_fmt.c
./c/graphics.c
./c/icmp.c
./c/images.c
./c/jit_support.c
./c/ldap.c
./c/md5_all.c
./c/mdi.c
./c/menus.c
./c/msinits.c
./c/msmain.c
./c/networks.c
./c/nsleep.c
./c/ntevent.c
./c/packaging.c
./c/process.c
./c/resizer.c
./c/sckevent.c
./c/sspi.c
./c/tcp.c
./c/trace.c
./c/twpro.c
./c/w32_dyndlg.cpp
./c/windows.c
./c/cppflags.h
./c/cprim.h
./c/ddrsc.h
./c/dtoa.h
./c/dyndlgs.h
./c/eventfns.h
./c/filedlg.h
./c/g2longint.h
./c/graphics.h
./c/icmp.h
./c/lispicp.h
./c/md5_all.h
./c/msincls.h
./c/netevent.h
./c/networks.h
./c/resizer.h
./c/ssl.h
./c/trace.h
./c/TypeSafeMsgMap.h)

ADD_LIBRARY(libcprim ${SRC_LIST})



