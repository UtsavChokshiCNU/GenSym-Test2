
@echo "G2-OPC test started"

start %SRCBOX%\g2opc\cpp\Release\g2opc.exe

%G2EXE%\g2.exe -kb TestCase326.kb -start

@echo "G2-OPC test finished"
@pause