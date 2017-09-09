g++ -c -Dlinux -DBUILD_CODE=\"$BLDCOD\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o linux/builder.o     builder.cpp
g++ -c -Dlinux -DBUILD_CODE=\"$BLDCOD\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o linux/code_tokens.o code_tokens.cpp
g++ -c -Dlinux -DBUILD_CODE=\"$BLDCOD\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o linux/connections.o connections.cpp
g++ -c -Dlinux -DBUILD_CODE=\"$BLDCOD\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o linux/download_ir.o download_ir.cpp
g++ -c -Dlinux -DBUILD_CODE=\"$BLDCOD\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o linux/encoding.o    encoding.cpp
g++ -c -Dlinux -DBUILD_CODE=\"$BLDCOD\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o linux/G2Container.o G2Container.cpp
g++ -c -Dlinux -DBUILD_CODE=\"$BLDCOD\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o linux/G2CorbaContainer.o G2CorbaContainer.cpp
g++ -c -Dlinux -DBUILD_CODE=\"$BLDCOD\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o linux/g2item.o      g2item.cpp
g++ -c -Dlinux -DBUILD_CODE=\"$BLDCOD\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o linux/g2string.o    g2string.cpp
g++ -c -Dlinux -DBUILD_CODE=\"$BLDCOD\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o linux/gsi_compile_idl.o gsi_compile_idl.cpp
g++ -c -Dlinux -DBUILD_CODE=\"$BLDCOD\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o linux/gsi_fcns.o    gsi_fcns.cpp
g++ -c -Dlinux -DBUILD_CODE=\"$BLDCOD\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o linux/iiop.o        iiop.cpp
g++ -c -Dlinux -DBUILD_CODE=\"$BLDCOD\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o linux/init_context.o init_context.cpp
g++ -c -Dlinux -DBUILD_CODE=\"$BLDCOD\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o linux/ior.o         ior.cpp
g++ -c -Dlinux -DBUILD_CODE=\"$BLDCOD\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o linux/lex_1.o       lex_1.cpp
g++ -c -Dlinux -DBUILD_CODE=\"$BLDCOD\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o linux/locator.o     locator.cpp
g++ -c -Dlinux -DBUILD_CODE=\"$BLDCOD\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o linux/orbtype.o     orbtype.cpp
g++ -c -Dlinux -DBUILD_CODE=\"$BLDCOD\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o linux/parse.o       parse.cpp
g++ -c -Dlinux -DBUILD_CODE=\"$BLDCOD\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o linux/parse_tree_node.o parse_tree_node.cpp
g++ -c -Dlinux -DBUILD_CODE=\"$BLDCOD\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o linux/pause.o       pause.cpp
g++ -c -Dlinux -DBUILD_CODE=\"$BLDCOD\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o linux/recv_req.o    recv_req.cpp
g++ -c -Dlinux -DBUILD_CODE=\"$BLDCOD\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o linux/reg_obj.o     reg_obj.cpp
g++ -c -Dlinux -DBUILD_CODE=\"$BLDCOD\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o linux/reg_proxy.o   reg_proxy.cpp
g++ -c -Dlinux -DBUILD_CODE=\"$BLDCOD\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o linux/send_req.o    send_req.cpp
g++ -c -Dlinux -DBUILD_CODE=\"$BLDCOD\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o linux/shutdown_context.o shutdown_context.cpp
g++ -c -Dlinux -DBUILD_CODE=\"$BLDCOD\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o linux/sockbase.o    sockbase.cpp
g++ -c -Dlinux -DBUILD_CODE=\"$BLDCOD\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o linux/token.o       token.cpp
g++ -c -Dlinux -DBUILD_CODE=\"$BLDCOD\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o linux/utils.o       utils.cpp
gcc -c -Dlinux -DBUILD_CODE=\"$BLDCOD\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o linux/ytab.o        ytab.c
g++ -c -Dlinux -DBUILD_CODE=\"$BLDCOD\" -DCORBALINK_VER=\"1_0R4\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o linux/startup.o     startup.cpp
g++ -L/usr/local/lib -L$GSIDIR -o linux/g2-corba \
                                         linux/builder.o          linux/code_tokens.o linux/connections.o      \
                                         linux/download_ir.o      linux/encoding.o    linux/G2Container.o      \
                                         linux/G2CorbaContainer.o linux/g2item.o      linux/g2string.o         \
                                         linux/gsi_compile_idl.o  linux/gsi_fcns.o    linux/iiop.o             \
                                         linux/init_context.o     linux/ior.o         linux/lex_1.o            \
                                         linux/locator.o          linux/orbtype.o     linux/parse.o            \
                                         linux/parse_tree_node.o  linux/pause.o       linux/recv_req.o         \
                                         linux/reg_obj.o          linux/reg_proxy.o   linux/send_req.o         \
                                         linux/shutdown_context.o linux/sockbase.o    linux/startup.o          \
 linux/token.o linux/utils.o linux/ytab.o $GSIDIR/gsi_misc.o $GSIDIR/libgsi.a -ltcp    \
 $GSIDIR/librtl.a -lnsl -lm -ltcp -ldl
