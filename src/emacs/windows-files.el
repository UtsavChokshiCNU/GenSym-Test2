;; windows-files.el

;;; This file contains specific information about files expected to be available
;;; on your Windows box.  It assumes you have K: mapped to /home/intelnt-mount.


;; `grep-for-lisp-symbol' aka "meta shift g"
(defconst grep-for-lisp-symbol "K:/gensym/scripts/grep-for-lisp-symbol")


;; The location of `gensym-lazy-lock-19-12'.  This is operating all the time as
;; we use xemacs.
(defconst gensym-lazy-lock-19-12 (format "%sgensym-lazy-lock" ab-emacs-directory))
                ; Yet another version, patched for 19.12.


;; These platform-specific constants are ill-defined here, because if this file
;; is being loaded, we know we are not on these platforms.
(defconst lucid-ultra-executable nil)
(defconst chestnut-ultra-executable nil)
(defconst lucid-solaris-executable nil)
(defconst lucid-sun4-executable nil)


;; `ilisp-directory' -- haven't gotten ilisp to run on Xemacs 21 yet
(defconst ilisp-directory
    (if xemacs-21-0-p
        nil
        (format "%silisp-5.6" ab-emacs-directory)))
(defconst gensym-lucid-50-init-file (format "%sgensym-lucid-50.lisp" ab-emacs-directory))
(defconst gensym-lucid-42-init-file (format "%sgensym-lucid-42.lisp" ab-emacs-directory))
(defconst default-ilisp-init-file gensym-lucid-42-init-file)

;; `Common Lisp init files' -- both get loaded, even though they're the same
(defconst clisp-42-init-file (format "%s/clisp.lisp" ilisp-directory))
(defconst clisp-50-init-file (format "%s/clisp.lisp" ilisp-directory))

;; LEP is an alternative to ilisp.  RH used it briefly, and maybe CSS too, but
;; we don't actively have it working, nor do we have it on Windows.
(defconst lep-init-master-liquid50 "/home/lucid/liquid50/common/lcl/5-0/elisp/lep/user-init-master")
(defconst lep-init-master-lucid41 "/home/lucid/lucid4/misc/lep/user-init-master")

;; Our one Allegro 5.0 license is still active, and currently installed on
;; jv's laptop in this location:
(defconst gensym-acl-location "C:\Program Files\acl501\lisp.exe")
;; ... though, note, I haven't run it inside emacs yet, and it almost surely
;; requires additional command-line arguments to do so.  The shortcut uses:
;;   -I lisp.dxl -f excl::start-emacs-lisp-interface  -jv, 8/7/07

;; run-cmulisp doesn't exist and clisp isn't installed on any platform I know
;; of, but, hey, maybe later.  -jv, 8/7/07
(defconst default-cmulisp-program "K:/gensym/scripts/run-cmulisp")


;; `tw-for-helpesk' is invoked via the emacs Gensym -> Helpdesk menu choice
(defconst tw-for-helpdesk "K:/gensym/ut/tw-test/tw")


;; The `ab-repository-commitlog' is not directly accessible from Windows.
;; Here's where it is, though.
(defconst ab-repository-commitlog "sdev5:/gensym/ab-repos/CVSROOT/commitlog")


;; The file for `ab-build-machines' is checked into CVS and therefore could be
;; obtained from any up-to-date sandbox, really.
(defconst ab-build-machines "K:/bt/ab/build/bt-machines.dat")


;; The `ab log files' live only in K:/bt/ab.
(defconst ab-build-summary-log "K:/bt/ab/logs/build-summary.log")
(defconst ab-regression-summary-log "K:/bt/ab/logs/regression-summary.log")
(defconst ab-build-check-log "K:/bt/ab/logs/build-check.log")


;; The `et log files' live only in K:/bt/et.
(defconst et-build-summary-log "K:/bt/et/logs/build-summary.log")
(defconst et-regression-summary-log "K:/bt/et/logs/regression-summary.log")
(defconst et-build-check-detail-log "K:/bt/et/logs/build-check-detail.log")


;; The `er log files' live only in K:/bt/er.  And yes, we do still run the
;; eternal recompile, though as of 8/7/07, it had been broken for a long
;; time and nobody noticed.
(defconst file-for-g2-eternal-recompile "K:/bt/er/logs/g2lucid-w.log")
(defconst file-for-tw-eternal-recompile "K:/bt/er/logs/twlucid-w.log")
(defconst file-for-gsi-eternal-recompile "K:/bt/er/logs/gsilucid-w.log")


;; `machine-type' -- if this file is loaded, we know we're "intelnt"
(defconst machine-type "intelnt")


;; ab-9oct95 stuff
(defconst ab9-repository-commitlog "sdev5:/gensym/ab-9oct95-repos/CVSROOT/commitlog")
(defconst ab9-build-summary-log "K:/bt/ab-9oct95/logs/build-summary.log")
(defconst ab9-regression-summary-log "K:/bt/ab-9oct95/logs/regression-summary.log")
(defconst ab9-build-check-log "K:/bt/ab-9oct95/logs/build-check.log")


;; these are hard-coded here because they "know" about K:/bt; but maybe
;; even if we want to isolate that hard-coding here, we could let the users
;; (run-debuggable-image) know how to make up the path from that.
(defconst format-string-for-et-debuggable "K:/bt/et/dst/%s/%s/o/%s")
(defconst format-string-for-ab-debuggable "K:/bt/ab/dst/%s/%s/o/%s")


;; we don't have gid for Windows
(defconst gid-executable nil)


;; ps-print may not actually be used, and almost certainly has never been tested
;; on Windows at Gensym; nevertheless, here's where the file is.
(defconst ps-print-location (format "%sps-print" ab-emacs-directory))


;; I guess you could actually get these on Windows, if you wanted.
(defconst madlab-weather-file "K:/gensym/homedirs/fmw/weather/forecast")
(defconst madlab-temperature-file "K:/gensym/homedirs/fmw/weather/temperature")


;; paths are surely wrong
(defconst spell-elc-filename "/usr/local/lib/emacs/18.58/lisp/spell.elc")
(defconst rn-server-filename "/usr/local/lib/rn/server")

;; the following scripts don't (any longer?) exist, but in theory they'd be in
;; K:/gensym/scripts if they did.  Each of these alleged scripts is,
;; in fact, referred to in other el files.
(defconst clman-script "K:/gensym/scripts/clman")
(defconst g2comp-script "K:/gensym/scripts/g2comp")
