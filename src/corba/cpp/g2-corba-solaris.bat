set GSIDIR=/gensym/ut/gsi-70r0
g++ -c -Dsparcsol -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o solaris/builder.o     builder.cpp
g++ -c -Dsparcsol -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o solaris/code_tokens.o code_tokens.cpp
g++ -c -Dsparcsol -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o solaris/connections.o connections.cpp
g++ -c -Dsparcsol -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o solaris/download_ir.o download_ir.cpp
g++ -c -Dsparcsol -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o solaris/encoding.o    encoding.cpp
g++ -c -Dsparcsol -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o solaris/G2Container.o G2Container.cpp
g++ -c -Dsparcsol -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o solaris/G2CorbaContainer.o G2CorbaContainer.cpp
g++ -c -Dsparcsol -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o solaris/g2item.o      g2item.cpp
g++ -c -Dsparcsol -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o solaris/g2string.o    g2string.cpp
g++ -c -Dsparcsol -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o solaris/gsi_compile_idl.o gsi_compile_idl.cpp
g++ -c -Dsparcsol -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o solaris/gsi_fcns.o    gsi_fcns.cpp
g++ -c -Dsparcsol -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o solaris/iiop.o        iiop.cpp
g++ -c -Dsparcsol -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o solaris/init_context.o init_context.cpp
g++ -c -Dsparcsol -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o solaris/ior.o         ior.cpp
g++ -c -Dsparcsol -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o solaris/lex_1.o       lex_1.cpp
g++ -c -Dsparcsol -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o solaris/locator.o     locator.cpp
g++ -c -Dsparcsol -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o solaris/orbtype.o     orbtype.cpp
g++ -c -Dsparcsol -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o solaris/parse.o       parse.cpp
g++ -c -Dsparcsol -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o solaris/parse_tree_node.o parse_tree_node.cpp
g++ -c -Dsparcsol -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o solaris/pause.o       pause.cpp
g++ -c -Dsparcsol -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o solaris/recv_req.o    recv_req.cpp
g++ -c -Dsparcsol -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o solaris/reg_obj.o     reg_obj.cpp
g++ -c -Dsparcsol -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o solaris/reg_proxy.o   reg_proxy.cpp
g++ -c -Dsparcsol -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o solaris/send_req.o    send_req.cpp
g++ -c -Dsparcsol -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o solaris/shutdown_context.o shutdown_context.cpp
g++ -c -Dsparcsol -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o solaris/sockbase.o    sockbase.cpp
g++ -c -Dsparcsol -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o solaris/token.o       token.cpp
g++ -c -Dsparcsol -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o solaris/utils.o       utils.cpp
gcc -c -Dsparcsol -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o solaris/ytab.o        ytab.c
g++ -c -Dsparcsol -DBUILD_CODE=\"FB27\" -DCORBALINK_VER=\"1_0R2\" -I. -I$GSIDIR -I/usr/local/lib/g++-include -o solaris/startup.o     startup.cpp
g++ -L/usr/local/lib -L$GSIDIR -o solaris/g2-corba \
                                         solaris/builder.o          solaris/code_tokens.o solaris/connections.o      \
                                         solaris/download_ir.o      solaris/encoding.o    solaris/G2Container.o      \
                                         solaris/G2CorbaContainer.o solaris/g2item.o      solaris/g2string.o         \
                                         solaris/gsi_compile_idl.o  solaris/gsi_fcns.o    solaris/iiop.o             \
                                         solaris/init_context.o     solaris/ior.o         solaris/lex_1.o            \
                                         solaris/locator.o          solaris/orbtype.o     solaris/parse.o            \
                                         solaris/parse_tree_node.o  solaris/pause.o       solaris/recv_req.o         \
                                         solaris/reg_obj.o          solaris/reg_proxy.o   solaris/send_req.o         \
                                         solaris/shutdown_context.o solaris/sockbase.o    solaris/startup.o          \
 solaris/token.o solaris/utils.o solaris/ytab.o $GSIDIR/gsi_misc.o $GSIDIR/libgsi.a -ltcp    \
 $GSIDIR/librtl.a -lsocket -lnsl -lm -ltcp -ldl
