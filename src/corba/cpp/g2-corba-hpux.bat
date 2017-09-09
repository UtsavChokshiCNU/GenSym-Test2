set GSIDIR=/gensym/ut/gsi-70r0
g++ -c -Dhp900s700 -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/opt/gcc/include/g++ -o hp/builder.o          builder.cpp
g++ -c -Dhp900s700 -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/opt/gcc/include/g++ -o hp/code_tokens.o      code_tokens.cpp
g++ -c -Dhp900s700 -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/opt/gcc/include/g++ -o hp/connections.o      connections.cpp
g++ -c -Dhp900s700 -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/opt/gcc/include/g++ -o hp/download_ir.o      download_ir.cpp
g++ -c -Dhp900s700 -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/opt/gcc/include/g++ -o hp/encoding.o         encoding.cpp
g++ -c -Dhp900s700 -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/opt/gcc/include/g++ -o hp/G2Container.o      G2Container.cpp
g++ -c -Dhp900s700 -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/opt/gcc/include/g++ -o hp/G2CorbaContainer.o G2CorbaContainer.cpp
g++ -c -Dhp900s700 -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/opt/gcc/include/g++ -o hp/g2item.o           g2item.cpp
g++ -c -Dhp900s700 -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/opt/gcc/include/g++ -o hp/g2string.o         g2string.cpp
g++ -c -Dhp900s700 -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/opt/gcc/include/g++ -o hp/gsi_compile_idl.o  gsi_compile_idl.cpp
g++ -c -Dhp900s700 -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/opt/gcc/include/g++ -o hp/gsi_fcns.o         gsi_fcns.cpp
g++ -c -Dhp900s700 -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/opt/gcc/include/g++ -o hp/iiop.o             iiop.cpp
g++ -c -Dhp900s700 -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/opt/gcc/include/g++ -o hp/init_context.o     init_context.cpp
g++ -c -Dhp900s700 -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/opt/gcc/include/g++ -o hp/ior.o              ior.cpp
g++ -c -Dhp900s700 -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/opt/gcc/include/g++ -o hp/lex_1.o            lex_1.cpp
g++ -c -Dhp900s700 -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/opt/gcc/include/g++ -o hp/locator.o          locator.cpp
g++ -c -Dhp900s700 -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/opt/gcc/include/g++ -o hp/orbtype.o          orbtype.cpp
g++ -c -Dhp900s700 -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/opt/gcc/include/g++ -o hp/parse.o            parse.cpp
g++ -c -Dhp900s700 -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/opt/gcc/include/g++ -o hp/parse_tree_node.o  parse_tree_node.cpp
g++ -c -Dhp900s700 -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/opt/gcc/include/g++ -o hp/pause.o            pause.cpp
g++ -c -Dhp900s700 -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/opt/gcc/include/g++ -o hp/recv_req.o         recv_req.cpp
g++ -c -Dhp900s700 -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/opt/gcc/include/g++ -o hp/reg_obj.o          reg_obj.cpp
g++ -c -Dhp900s700 -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/opt/gcc/include/g++ -o hp/reg_proxy.o        reg_proxy.cpp
g++ -c -Dhp900s700 -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/opt/gcc/include/g++ -o hp/send_req.o         send_req.cpp
g++ -c -Dhp900s700 -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/opt/gcc/include/g++ -o hp/shutdown_context.o shutdown_context.cpp
g++ -c -Dhp900s700 -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/opt/gcc/include/g++ -o hp/sockbase.o         sockbase.cpp
g++ -c -Dhp900s700 -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/opt/gcc/include/g++ -o hp/token.o            token.cpp
g++ -c -Dhp900s700 -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/opt/gcc/include/g++ -o hp/utils.o            utils.cpp
gcc -c -Dhp900s700 -DBUILD_CODE=\"FB27\" -I. -I$GSIDIR -I/opt/gcc/include/g++ -o hp/ytab.o             ytab.c
g++ -c -Dhp900s700 -DBUILD_CODE=\"FB27\" -DCORBALINK_VER=\"1_0R2\" -I. -I$GSIDIR -I/opt/gcc/include/g++ -o hp/startup.o          startup.cpp
g++ -L/usr/local/lib -o hp/g2-corba hp/builder.o hp/code_tokens.o hp/connections.o hp/download_ir.o hp/encoding.o \
  hp/G2Container.o hp/G2CorbaContainer.o hp/g2item.o hp/g2string.o hp/gsi_compile_idl.o hp/gsi_fcns.o hp/iiop.o   \
  hp/init_context.o hp/ior.o hp/lex_1.o hp/locator.o hp/orbtype.o hp/parse.o hp/parse_tree_node.o hp/pause.o      \
  hp/recv_req.o hp/reg_obj.o hp/reg_proxy.o hp/send_req.o hp/shutdown_context.o hp/sockbase.o hp/startup.o        \
  hp/token.o hp/utils.o hp/ytab.o $GSIDIR/gsi_misc.o $GSIDIR/libgsi.a                     \
  $GSIDIR/libtcp.a $GSIDIR/librtl.a -I/opt/gcc/include/g++
