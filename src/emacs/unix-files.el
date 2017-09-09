;; unix-files.el

;;; This file contains specific information about files available on our
;;; Unix filesystem.


;; `grep-for-lisp-symbol' aka "meta shift g"
(defconst grep-for-lisp-symbol "/home/development/scripts/grep-for-lisp-symbol")


;; The location of `gensym-lazy-lock-19-12'.  This is operating all the time as
;; we use xemacs.
(defconst gensym-lazy-lock-19-12 (format "%sgensym-lazy-lock" ab-emacs-directory))
                ; Yet another version, patched for 19.12.


;; `lucid' and `chestnut' executables
;; what you get when you do M-x lucid on a Sparc Ultra
(defconst lucid-ultra-executable "/home/lucid/liquid50/lisp-clos-50")
;; what you get when you do M-x chestnut on a Sparc Ultra
(defconst chestnut-ultra-executable "/home/development/chestnut/trans-32b3c")
;; It would be unusual for anyone to run Lucid on a non-Ultra box, but it is
;; still supported and should still work.  We do not support running chestnut
;; on anything besides an Ultra, though.
(defconst lucid-solaris-executable "/home/lucid/liquid50/lisp-clos-50")
(defconst lucid-sun4-executable "/home/lucid/lucid41/lisp-clos-411")


;; `ilisp-directory' -- haven't gotten ilisp to run on Xemacs 21 yet
(defconst ilisp-directory
    (if xemacs-21-0-p
        nil
        (format "%silisp" scriptsbox)))
(defconst gensym-lucid-50-init-file (format "%sgensym-lucid-50.lisp" ab-emacs-directory))
(defconst gensym-lucid-42-init-file (format "%sgensym-lucid-42.lisp" ab-emacs-directory))
(defconst default-ilisp-init-file gensym-lucid-42-init-file)

;; `Common Lisp init files' -- both get loaded, even though they're the same
(defconst clisp-42-init-file (format "%s/clisp.lisp" ilisp-directory))
(defconst clisp-50-init-file (format "%s/clisp.lisp" ilisp-directory))

;; LEP is an alternative to ilisp.  RH used it briefly, and maybe CSS too, but
;; we don't actively have it working.
(defconst lep-init-master-liquid50 "/home/lucid/liquid50/common/lcl/5-0/elisp/lep/user-init-master")
(defconst lep-init-master-lucid41 "/home/lucid/lucid4/misc/lep/user-init-master")

;; we no longer have an active Allegro license on Unix, though the binaries are
;; still there on herb.
(defconst gensym-acl-location "/usr/local/acl61/alisp")  ; ANSI version of Allegro; currently on evaluation. -mhd, 2/5/02

;; run-cmulisp doesn't exist and clisp isn't installed on any platform I know
;; of, but, hey, maybe later.  -jv, 8/7/07
(defconst default-cmulisp-program "/home/development/scripts/run-cmulisp")


;; `tw-for-helpesk' is invoked via the emacs Gensym -> Helpdesk menu choice
(defconst tw-for-helpdesk "/gensym/ut/tw-test/tw")


;; The `ab-repository-commitlog' has long since become far too large for me (jv)
;; to try to open it in xemacs, but others may be braver than I.
(defconst ab-repository-commitlog "/gensym/ab-repos/CVSROOT/commitlog")


;; The file for `ab-build-machines' is checked into CVS and therefore could be
;; obtained from any up-to-date sandbox, really.
(defconst ab-build-machines "/bt/ab/build/bt-machines.dat")


;; The `ab log files' live only in /bt/ab.
(defconst ab-build-summary-log "/bt/ab/logs/build-summary.log")
(defconst ab-regression-summary-log "/bt/ab/logs/regression-summary.log")
(defconst ab-build-check-log "/bt/ab/logs/build-check.log")


;; The `et log files' live only in /bt/et.
(defconst et-build-summary-log "/bt/et/logs/build-summary.log")
(defconst et-regression-summary-log "/bt/et/logs/regression-summary.log")
(defconst et-build-check-detail-log "/bt/et/logs/build-check-detail.log")


;; The `er log files' live only in /bt/er.  And yes, we do still run the
;; eternal recompile, though as of 8/7/07, it had been broken for a long
;; time and nobody noticed.
(defconst file-for-g2-eternal-recompile "/bt/er/logs/g2lucid-w.log")
(defconst file-for-tw-eternal-recompile "/bt/er/logs/twlucid-w.log")
(defconst file-for-gsi-eternal-recompile "/bt/er/logs/gsilucid-w.log")


;; `machine-type' -- currently only used by the gdb functionality, but could
;; have greater general usage.
(defconst machine-type (getenv "MACHINE"))


;; ab-9oct95 stuff; all still there and "active" in the sense that an ab-9oct95
;; build would cause these files to be properly updated (and that we can still
;; do ab-9oct95 builds), but we haven't done one since 4/30/99.  -jv, 8/7/07
(defconst ab9-repository-commitlog "/gensym/ab-9oct95-repos/CVSROOT/commitlog")
(defconst ab9-build-summary-log "/bt/ab-9oct95/logs/build-summary.log")
(defconst ab9-regression-summary-log "/bt/ab-9oct95/logs/regression-summary.log")
(defconst ab9-build-check-log "/bt/ab-9oct95/logs/build-check.log")

;; these are hard-coded here because they "know" about /gensym/bt; but maybe
;; even if we want to isolate that hard-coding here, we could let the users
;; (run-debuggable-image) know how to make up the path from that.
(defconst format-string-for-et-debuggable "/gensym/bt/et/dst/%s/%s/o/%s")
(defconst format-string-for-ab-debuggable "/gensym/bt/ab/dst/%s/%s/o/%s")

;; used by function C-grep in gensym-c-mode.el
(defconst gid-executable "/home/ab/bin/gid")

;; We used to add a menu-item to the File menu using ps-print, under XEmacs
;; 19.11.  We no longer do that, so does that make ps-print completely unused?
;; -jv, 11/20/07
(defconst ps-print-location (format "%sps-print" ab-emacs-directory))

;; This had the wrong value previously ("current-forecast" instead of
;; "forecast"); but these are not currently used by other .el files.
;; gensym-weather.el defines its own constants which supposedly live in /home/ab
;; but aren't actually there.
(defconst madlab-weather-file "/home/fmw/weather/forecast")
(defconst madlab-temperature-file "/home/fmw/weather/temperature")

;; do not exist on burlington
(defconst spell-elc-filename "/usr/local/lib/emacs/18.58/lisp/spell.elc")
(defconst rn-server-filename "/usr/local/lib/rn/server")

;; the following scripts don't (any longer?) exist, but in theory they'd be in
;; /home/development/scripts if they did.  Each of these alleged scripts is,
;; in fact, referred to in other el files.
(defconst clman-script "/home/development/scripts/clman")
(defconst g2comp-script "/home/development/scripts/g2comp")


;; Try to compensate for gross Sun automounting.
(setq directory-abbrev-alist
      (append '(("\\`/tmp_mnt/home/" . "/home/")
                ("\\`/gensym/sandboxes3/" . "/bt/"))
              directory-abbrev-alist))
