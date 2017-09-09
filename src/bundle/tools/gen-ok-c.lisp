(in-package "BUNDLE")


;;; `Obfuscate-ok-line' is makes an obfuscated copy of line.
;;; `deobfuscate-ok-line' reverses the result of obfuscate-ok-line. They are
;;; implemented by XOR'ing each character with a constant bit pattern.

(defconstant xor-key #2r1010101010)

(defun obfuscate-ok-line (line)
  (do* ((length (length line))
	(i 0 (+ i 1))
	(new-line (make-string length))
	char-code)
       ((= i length)
	new-line)
    (setq char-code (char-code (char line i)))
    (setf (char new-line i)
	  (code-char (logxor char-code xor-key)))))

(defun deobfuscate-ok-line (line)
  (obfuscate-ok-line line))



;;; The special variable `emitted-ok-lines' is used to hold the list of emitted
;;; lines for an OK file.  Each entry should be obfuscated.  `Emit-ok-line'
;;; emits a line to this list.

(defvar emitted-ok-lines)

(defun emit-ok-line (line)
  (setq emitted-ok-lines (nconc emitted-ok-lines (list (obfuscate-ok-line line)))))

(defvar bundle-ok-lines
  '((g2-development
     (					; temporary prototype OK file
      "-- Gensym private -- please do not use this, and do not keep this on your computer"
      "begin g2-ok-file"
      ""
      "file-format-version: 2;"
      ""
      "begin machine"
      "  name: Gensym;"
      "  machine-id: \"Site: Gensym Corporate Internal\";"
      "  authorized-products: ( online jl );"
      "  expiration-date?: (from 31 may 2000 to 31 may 2001);"
      "  authorization: ( 21766 16026 46626 11271 644189 );"
      "  make-g2-secure?: false;"
      "  authorized-kb-packages: ();"
      "  number-of-processes-authorized: 10;"
      "  maximum-number-of-concurrent-floating-telewindows-allowed: 20;"
      "  maximum-number-of-concurrent-floating-tw2-allowed: 20;"
      "end machine"
      ""
      "begin user"
      "  -- To require users to log in, change"
      "  -- line above to make-g2-secure?: true."
      "  -- Then add user entries here."
      "end user"
      "end g2-ok-file"))))


(defun make-bundle-ok-lines (bundle-name)
  (let ((emitted-ok-lines '())
	(lines (second (assoc bundle-name bundle-ok-lines))))
    (when (null lines)
      (error "No OK file information for bundle ~a" bundle-name)) 
    (dolist (line lines)
      (emit-ok-line line))
    emitted-ok-lines))


(defun emit-deobfuscating-c-code ()
  (format t "~%~%#define XOR_KEY ~d"
	  xor-key)
  (format t "~%void deobfuscate_and_write_line (char *line, FILE *stream)
{
  char *t;
  for (t = line; *t; t++)
     putc ((char)(((int)*t) ^ XOR_KEY), stream);
  fprintf (stream, \"\\n\");
}")
  (format t "~%#undef XOR_KEY~%~%"))



;;; `Emit-ok-line-using-c-escapes' write to standard output ("emits") line as a
;;; C string constant.  The beginning and ending quotes are always emitted at
;;; the beginning and the end. Escapes are used for Return (\r), linefee (\n),
;;; tab (\t), backslash (\\), single quote (\'), and double-quote (\").  Ascii
;;; printing characters are written literally.  All other characters that are
;;; non-ascii-printing characters are written as 3-digit octal escapes.  This
;;; returns no useful value.

(defconstant max-ascii-printable 126)	; ~
(defconstant min-ascii-printable 32)	; space

(defconstant c-octal-escape-ctl-str
  "~3,'0o")	; arg: integer [0..255]; outputs 3-wide, 0-padded

(defun emit-ok-line-using-c-escapes (line)
  (write-char #\")  
  (do ((i 0 (+ i 1))
       (length (length line))
       char)
      ((= i length))
    (setq char (char line i))
    (case char
      (#\return
       (format t "\\r"))
      (#\linefeed
       (format t "\\n"))
      (#\tab
       (format t "\\t"))
      (#\\
       (format t "\\\\"))
      (#\'
       (format t "\\'"))
      (#\"
       (format t "\\\""))
      (t (let ((char-code (char-code char)))
	   (cond
	     ((or (> char-code max-ascii-printable)
		  (< char-code min-ascii-printable))
	      (write-char #\\)
	      (format t c-octal-escape-ctl-str char-code))
	     (t
	      (write-char char)))))))
    (write-char #\")
    nil)
  
  



;;; Emit-ok-lines-as-c-code writes standard output ("emits") code that defines a
;;; c variable that holds an array of strings corresponding to ok-lines,
;;; ok-lines, a list of emitted OK lines.  The c variable name is based on
;;; bundle-name transformed as follows: (a) the suffix _ok_lines is appended;
;;; (b) it has the same spelling as bundle-name, except that all alphabetic
;;; characters are lowercase, and hyphens (-) are changed to underscores (_).
;;; For example, E-SCOR -> e_scor_ok_lines, G2 -> g2_ok_lines, etc.  It is an
;;; error to call this with a bundle name that would not result in a legal c
;;; identifier under above transformation.  Note: ok-lines should normally be
;;; the result of a call to make-bundle-ok-lines.

(defun emit-ok-lines-as-c-code (bundle-name ok-lines)
  (format t "~%#define ~a ~d" (make-n-ok-lines-identifier bundle-name) (length ok-lines))
  (format t "~%char *~a[] = {"
	  (make-ok-lines-identifier bundle-name))
  (let ((first-time-p t))
    (dolist (line ok-lines)
      (if first-time-p
	  (setq first-time-p nil)
	  (format t ",~%  "))
      (emit-ok-line-using-c-escapes line)))
  (format t "};~%"))

(defun usual-bundle-c-name (bundle-name)
  (substitute #\_ #\- (symbol-name bundle-name)))

(defun make-n-ok-lines-identifier (bundle-name)
  (format nil "N_~a_OK_LINES" (usual-bundle-c-name bundle-name)))

(defun make-ok-lines-identifier (bundle-name)
  (format nil "~(~a~)_ok_lines" (usual-bundle-c-name bundle-name)))

(defun make-ok-lines-emitter-identifier (bundle-name)
  (format nil "emit_~(~a~)_ok_lines" (usual-bundle-c-name bundle-name)))

(defun make-ok-file-emitter-identifier (bundle-name)
  (format nil "emit_~(~a~)_ok_file" (usual-bundle-c-name bundle-name)))

(defun emit-ok-file-emitter-as-c-code (bundle-name)
  (format t "~%void ~a (FILE *stream)~%"
	  (make-ok-lines-emitter-identifier bundle-name))
  (format t "~%{")
  (format t "~%  int i;")
  (format t "~%  for (i = 0; i < ~a; i++) {" (make-n-ok-lines-identifier bundle-name))
  (format t "~%    deobfuscate_and_write_line (~a [i], stream);" (make-ok-lines-identifier bundle-name))
  (format t "~%    }")
  (format t "~%}"))





(defun emit-ok-gen.c (file-name bundle-name)
  (with-open-file (*standard-output* file-name :direction :output)
    (format t "~%/* Autogenerated OK file emitter for bundle ~a */" bundle-name)
    (format t "~%#include <stdio.h>~%")
    (let ((ok-lines (make-bundle-ok-lines bundle-name)))
      (emit-ok-lines-as-c-code bundle-name ok-lines))
    (emit-deobfuscating-c-code)
    (emit-ok-file-emitter-as-c-code bundle-name)
    (format t "~%void ~a (char *file_name)" (make-ok-file-emitter-identifier bundle-name))
    (format t "~%{")
    (format t "~%  FILE *stream;")
    ;; ok to overwrite existing file?!
    (format t "~%  if (stream = fopen(file_name, \"w\")) ")
    (format t "~%    ~a (stream);" (make-ok-lines-emitter-identifier bundle-name))
    ;; else error? exit?!
    (format t "~%}")
    (format t "~%")

    ;; testmain
    (format t "
#ifdef TESTMAIN
int main (arc, argv)
{
  ~a (\"testmain-g2.ok\");
}
#endif ~%"
	    (make-ok-file-emitter-identifier bundle-name))))
  

                                

;; MHD, 8/1/00: Tested with
;; (progn (cd "/bt/mhd/bundle/tools/") (load (compile-file "gen-ok-c.lisp")) (in-package "BUNDLE"))
;; (emit-ok-gen.c "g2-development-ok.c" 'g2-development)
;; Then, in shell:
;; gcc -g -DTESTMAIN g2-development-ok.c
;; a.out
;; Then look at testmain-g2.ok to see if it's got the contents implied by
;; (assoc 'g2-development bundle-ok-lines)
