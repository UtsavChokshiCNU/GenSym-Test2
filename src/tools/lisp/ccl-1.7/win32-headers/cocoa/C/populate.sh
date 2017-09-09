#!/bin/sh
rm -rf Developer
H_TO_FFI=/Developer/Cocotron/1.0/Windows/i386/gcc-4.3.1/bin/h-to-ffi.sh
COCOTRON_FRAMEWORKS=/Developer/Cocotron/1.0/Windows/i386/Frameworks/
CFLAGS=" -D__COCOTRON__ -DWINDOWS";export CFLAGS

${H_TO_FFI} -F${COCOTRON_FRAMEWORKS} ${COCOTRON_FRAMEWORKS}/Cocoa.framework/Headers/Cocoa.h 
${H_TO_FFI} -F${COCOTRON_FRAMEWORKS} ${COCOTRON_FRAMEWORKS}/OpenGL.framework/Headers/OpenGL.h
${H_TO_FFI} -F${COCOTRON_FRAMEWORKS} ${COCOTRON_FRAMEWORKS}/objc.framework/Headers/objc-runtime.h
${H_TO_FFI} -F${COCOTRON_FRAMEWORKS} ${COCOTRON_FRAMEWORKS}/objc.framework/Headers/message.h
${H_TO_FFI} -F${COCOTRON_FRAMEWORKS} ${COCOTRON_FRAMEWORKS}/objc.framework/Headers/Protocol.h

