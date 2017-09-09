
copy k:\gensym\bridges\intelnt\G2Com-unsigned.dll k:\gensym\bridges\intelnt\G2Com.dll
signcode -spc mycredentials.spc -v myprivatekey.pvk -n ActiveXLink -i http://www.gensym.com -t http://timestamp.verisign.com/scripts/timstamp.dll k:\gensym\bridges\intelnt\G2Com.dll
rem pause
