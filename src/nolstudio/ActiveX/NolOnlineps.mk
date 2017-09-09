
NolOnlineps.dll: dlldata.obj NolOnline_p.obj NolOnline_i.obj
	link /dll /out:NolOnlineps.dll /def:NolOnlineps.def /entry:DllMain dlldata.obj NolOnline_p.obj NolOnline_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del NolOnlineps.dll
	@del NolOnlineps.lib
	@del NolOnlineps.exp
	@del dlldata.obj
	@del NolOnline_p.obj
	@del NolOnline_i.obj
