;//+----------------------------------------------------------------------------
;//
;//  Copyright (C) 1986-2017 Gensym Corporation
;//
;//  File:      G2AgentMessages.mc 
;//
;//  Contents:  Events and Errors for G2 Agent
;//
;//-----------------------------------------------------------------------------

SeverityNames=(Success=0x0
               Informational=0x1
               Warning=0x2
               Error=0x3
              )
FacilityNames=(System=0x0
	Runtime=0x2
	Io=0x4
	) 

FacilityNames=(Interface=0x04)

Messageid=1
Facility=System
Severity=Error
SymbolicName=G2_BAD_OPERATION
Language=English
Incorrect operation or command.
.

Messageid=2
Facility=System
Severity=Error
SymbolicName=G2_SYSTEM_ERROR
Language=English
G2 Error: %1. Description: %2
.

Messageid=3
Facility=Runtime
Severity=Error
SymbolicName=G2_ERROR
Language=English
%1
.

Messageid=4
Facility=Runtime
Severity=Warning
SymbolicName=G2_WARNING
Language=English
%1
.

Messageid=5
Facility=Runtime
Severity=Informational
SymbolicName=G2_INFORMATION
Language=English
%1
.
