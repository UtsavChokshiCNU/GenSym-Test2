1. Build G2, TWNG, JavaLink and G2SNMP
2. Start G2SNMP
3. Load gsnmp-performance-demo.kb
4. Make sure you have net-snmp-5.5 build and installed:
	- Open the net-snmp-5.5\win32\win32.dsw using vs6.0 and build the release
		version as following: libagent, libhelpers, libnetsnmptrapd, libsnmp,
		netsnmpmibs, snmptrapgenerator
	- run the install-net-snmp.bat in net-snmp-5.5\win32, and it will install
		net-snmp in C:\usr\net-snmp
5.	Push the start, the measurement starts and the snmptrapgenerator.exe starts
	too, after measurement, the snmptrapgenerator.exe will stop regardless of
	the amount of the traps haven’t sent yet.
6.	The traps per second value will be shown on kb workspace.
