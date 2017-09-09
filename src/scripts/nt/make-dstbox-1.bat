@rem internal batch file used by make-dstbox.bat.  You should not call this directly.

for %%d in (o opt opt-intc qa tape test) do mkdir %DSTBOX%\%1\%%d
