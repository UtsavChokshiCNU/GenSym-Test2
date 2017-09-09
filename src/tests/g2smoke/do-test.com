$!   This script mimics the Unix shell script do-test, which contains extensive
$! comments.
$!   Unfortunately, it is not easy to monitor the execution of a VMS process
$! and time out if an interval is exceeded, so g2 execution can cause this
$! command file to hang indefinitely.
$ 
$!   ! Default values for command line arguments. SRCBOX is a global symbol.
$    g2image    == "$''DSTBOX'.g2.test]g2.exe"
$    modpath     = "''SRCBOX'.kbs]"
$    ok          = "projects:[ab]g2v5.ok"
$    g2display   = " "
$    smoke_error = 0
$
$    define/nolog smoke$source 'SRCBOX'.tests.g2smoke]
$
$    n = 0
$    args     = "''p1' ''p2' ''p3' ''p4' ''p5' ''p6' ''p7' ''p8' ''p9'"
$    LOOP:
$        arg = f$element(n," ",args)
$        if arg .eqs. "" .or. arg .eqs. " "
$        then
$            goto END_LOOP
$        endif
$        if arg .eqs."-DISPLAY"
$        then
$            n = n + 1
$            g2display = "-DISPLAY " + f$element(n," ",args)
$        endif
$        if arg .eqs."-G2"
$        then
$            n = n + 1
$            g2image    == "$" + f$element(n," ",args)
$        endif
$	 if arg .eqs. "-MODPATH"
$        then
$	     n = n + 1
$	     modpath = f$element(n," ",args)
$	 endif
$        if arg .eqs. "-OK"
$        then
$            n = n + 1
$            ok = f$element(n," ",args)
$        endif
$        n = n + 1
$        goto LOOP
$    END_LOOP:
$
$!   ! Change working directory to g2 test directory.
$    set def 'DSTBOX'.g2.test]
$
$    copy smoke$source:smoke1.kb []
$
$!   ! Run g2 with smoke1.kb.  Note that unlike on the Unix systems, g2 will
$!   ! never time out.
$    write sys$output "LOG: running g2 with smoke1.kb"
$    g2image    -module_search_path 'modpath -ok 'ok -kb smoke1.kb 'g2display -start
$
$    if f$search("[]smoke2.kb") .nes. "" 
$    then    
$        write sys$output "LOG: running g2 with smoke2.kb"
$        g2image    -module_search_path 'modpath -ok 'ok -kb smoke2.kb 'g2display -start
$    else
$        write sys$output "smoke test error: smoke1.kb failed to write smoke2.kb"
$        smoke_error = 1
$        goto WRAPUP
$    endif
$
$!   ! The diff command returns $status and $severity. $severity is 1 for
$!   ! identical contents.
$    diff smoke.out smoke$source:vmsexpected.out
$
$    if $severity .ne. 1 
$    then 
$        write sys$output "smoke test error: g2 output differed from expected output"
$        smoke_error = 1
$    endif
$
$ WRAPUP:
$    if  f$search("[]smoke.out") .nes. "" then delete []smoke.out;*
$    if  f$search("[]smoke1.kb") .nes. "" then delete []smoke1.kb;*
$    if  f$search("[]smoke2.kb") .nes. "" then delete []smoke2.kb;*
$
$    if smoke_error
$    then
$        write sys$output "Smoke Test Failed"
$    else
$        write sys$output "Smoke Test Passed"
$    endif
$
$    exit
