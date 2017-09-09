#/bin/sh
CFLAGS="-D__MINGW32__ -D__MSVCRT__ -D__MSVCRT_VERSION__=0x700 -D_WIN32_WINNT=0x0502";export CFLAGS
rm -rf usr
echo "Warnings about system header pragmas being ignored can themselves be ignored."
h-to-ffi.sh /usr/include/w32api/GL/gl.h
h-to-ffi.sh /usr/include/w32api/GL/glu.h
exit 0
