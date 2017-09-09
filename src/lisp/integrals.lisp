;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Application Toolkit Authorization





;;;; Encoding Schema

;;; Let:

;;; 	Q1,Q2 = X(package-name)		(1)
;;;	Q3,Q4 = Y(package-name)		(2)
;;;  	Q5,Q6 = Z(machine-id)		(3)
			
;;;	C1,C2 = R(Q1,Q2,Q5,Q6)		(4)
;;;	C3    = S(Q3,Q4,Q5,Q6,C1,C2)	(5)

;;; The Ci are the authorizing codes for a module. They are determined
;;; by the package-name and the machine id.

;;; The Qi and the Ci are fixnums on all platforms. package-name and
;;; machine-id are arbitrary strings. Functions X,Y and Z are insensitive
;;; to case of letters, and to the presence of non-alphanumeric characters.

;;; The five functions are "obscure" in the sense that no reasonable collection
;;; of examples is useful for computing the function for new arguments.

;;; The Gensym proprietary authorizing module computes the Ci given the
;;; package-name and the machine-id using the five equations above.

;;; The package-specific authorizing module, which may be given to the
;;; author of the module who is not Gensym, computes the Ci from the last
;;; three equations only. It requires a small accompanying file containing
;;; Q1-4 for a particular package, which it reads initially.  






;;;; New Randomizing Function

;;; Intended as a higher speed version of the authorization randomizer.

;;; Given an 8 X 8 bit matrix, alternate two steps.
;;; Step one is to do a table replacement based on a 256 word array, same
;;; as before.

;;;; Step 2 is to swap pairs of the lower order bits, thus generating
;;;; new configurations.


;;;; Array churning

;;; The heart of the obscure function computation is array churning.
;;; It is performed on an array of 8 8-bit bytes. It uses a random
;;; permutation of the numbers 0-255 as a key. The function churn-array
;;; takes as arguments an array of 8 bytes, a key which is an array of
;;; length 256 containing a permutation of 0 - 255, and an index of how
;;; many churns to perform. The entire work is performed in local variables,
;;; and returned to the byte array when complete to optimize use of registers.
;;; The algorithm can be read from the code.





;;; The following macros are used only to generate open code in churn-array.
;;; They reference local variables of churn-array.


;;; Move the 8 bytes from churn-array into local variables. 

(defmacro churn-set-locals ()
  `(progn
     ,@(loop for i from 0 to 7
	    for local in '(x0 x1 x2 x3 x4 x5 x6 x7)
	    collect
	      `(setq ,local (svref churn-array ,i)))))


;;; Move the 8 bytes from the local variables into churn-array when done.

(defmacro churn-set-array ()
  `(progn
     ,@(loop for i from 0 to 7
	    for local in '(x0 x1 x2 x3 x4 x5 x6 x7)
	    collect
	      `(setf (svref churn-array ,i) ,local))))


;;; Replace each byte by substitution into the key.

(defmacro churn-subst-macro ()
  `(progn
     ,@(loop for local in '(x0 x1 x2 x3 x4 x5 x6 x7)
	     collect
	       `(setq ,local (svref churn-key ,local)))))


;;; Rotate the low order 4 bits of each local variable into the
;;; low order 4 bits of the preceeding variable in cyclic order.

(defmacro churn-rotate-down-macro ()
  `(progn
     (setq temp1 x0)
     ,@(loop for (x y . nil) on '(x0 x1 x2 x3 x4 x5 x6 x7)
	     collect
	       (if y
		   `(setq ,x (logior (logand ,y 15) (logand ,x 240)))
		   `(setq ,x (logior (logand temp1 15) (logand ,x 240)))))))


;;; Swap the 4 low order bits of pairs of variables. The swaped pairs
;;; are V(i) and V(i+4), for i = 0 to 3.

(defmacro churn-swap-fours-macro ()
  `(progn
     ,@(loop for x in '(x0 x1 x2 x3)
	    for y in '(x4 x5 x6 x7)
	    nconc
	      `((setq temp1 (logand ,x 15))
		(setq temp2 (logand ,y 15))
		(setq ,x (logior (logand ,x 240) temp2))
		(setq ,y (logior (logand ,y 240) temp1))))))



(defun churn-array (churn-array churn-key n)
  (let (temp1 temp2 x0 x1 x2 x3 x4 x5 x6 x7)
    (churn-set-locals)

    (loop for i from 1 to n doing
      (churn-subst-macro)
      (churn-rotate-down-macro)
      (churn-subst-macro)
      (churn-swap-fours-macro)
      )

    (churn-set-array)
    ))




(defvar churn-key-2	
	(make-array
	  256
	  ':initial-contents
	  '(222 90 199 253 194 190 128 147 21 170 193 96 137 237 155 94 217
		192 60 104 72 215 66 34 226 207 53 27 55 15 167 68 92 112 154
		120 173 88 214 143 107 103 101 176 234 49 13 70 240 206 37 54
		135 113 85 117 65 87 4 1 178 81 188 238 195 245 247 127 71 16
		203 11 38 138 131 191 144 31 205 225 59 244 221 114 133 184 91
		56 69 51 61 9 116 89 145 224 179 142 229 2 146 241 228 20 249
		8 77 150 148 45 130 18 102 110 201 32 74 212 251 230 95 48 5
		149 171 250 220 33 98 63 163 209 182 47 42 23 242 126 177 216
		189 52 26 152 75 86 58 172 162 187 223 0 3 43 22 30 29 28 106
		183 218 67 44 159 174 122 7 39 151 24 211 200 10 252 83 14 82
		158 134 115 125 80 186 99 169 236 123 41 141 73 118 124 19 227
		129 185 97 50 121 213 139 153 204 119 105 64 246 132 208 25
		232 161 111 198 231 248 202 17 157 79 62 168 197 180 239 36
		136 235 243 219 254 175 156 166 160 40 93 6 84 109 108 181 196
		140 57 46 35 210 255 100 76 233 164 78 12 165)))





(defvar churn-box (make-array 8))




(defmacro load-randoms-into-churn-array ()
  `(progn
     ,@(loop for i from 0
	     for random in '(r0 r1 r2 r3 r4 r5 r6 r7) collect
	     `(setf (svref array ,i) ,random))))




;; WARNING! DANGER WILL ROBINSON! This has the same name as a G2 function.  And
;; some of the macros differ slightly but have the same name, or have a
;; different name but are the same or only differ slightly.  This takes narrow
;; (Lisp) strings, unlike its G2 counterpart, which takes wide strings! This
;; means that you have to make sure this is loaded/compiled AFTER all of G2.
;; NOTE 2: It is also crucial to note that the G2 module SEQUENCES2, which
;; contains the near-duplicate code, is not part of the ls (licensing-server)
;; system, so any change must provide this code for that system.  (MHD 6/11/97)

(defun implant-string-into-array (string array r0 r1 r2 r3 r4 r5 r6 r7)
  (load-randoms-into-churn-array)

  (loop with j = 0
	for i from 0 to (- (length string) 1)
	for weight = (digit-char-p (char string i) 36) doing
    (when weight
      (setf (svref array (mod j 8))
	    (logxor (svref array (mod j 8)) weight))
      (incf j))))






(defun churn-z (machine-id)
  (let ((array churn-box))

    (implant-string-into-array machine-id array 
			       9 184 41 90 71 250 97 167)

    (churn-array array churn-key-2 5)

    (values
      (logxor (svref array 1)
	      (ash (svref array 2) 5)
	      (ash (svref array 3) 11))
      (logxor (svref array 4)
	      (ash (svref array 5) 5)
	      (ash (svref array 6) 11)))))




(defun churn-r (q1 q2 q3 q4 start-date end-date)
  (let ((array churn-box))    
    (setf (svref array 0)
	  (logxor 83
		  (logand q1 77)
		  (logand start-date 77)))
    (setf (svref array 1)
	  (logxor 211
		  (logand (ash q1 -8) 77)
		  (ash q1 -13)
		  (logand (ash start-date -8) 77)))
    (setf (svref array 2)
	  (logxor 219
		  (logand q2 77)
		  (logand (ash start-date -13) 77)))
    (setf (svref array 3)
	  (logxor 63
		  (logand (ash q2 -8) 77)
		  (ash q1 -13)
		  (logand end-date 77)))    
    (setf (svref array 4)
	  (logxor 143
		  (logand q3 77)
		  (logand (ash end-date -8) 77)))
    (setf (svref array 5)
	  (logxor 30
		  (logand (ash q1 -8) 77)
		  (ash q3 -13)
		  (logand (ash end-date -13) 77)))    
    (setf (svref array 6)
	  (logxor 241
		  (logand q4 77)))
    (setf (svref array 7)
	  (logxor 253
		  (logand (ash q4 -8) 77)
		  (ash q1 -13)))    
    (churn-array array churn-key-2 5)    
    (values
      (logxor (svref array 1)
	      (ash (svref array 2) 5)
	      (ash (svref array 3) 11))
      (logxor (svref array 4)
	      (ash (svref array 5) 5)
	      (ash (svref array 6) 11)))))




(defun churn-s (q1 q2 q3 q4 c1 c2 start-date end-date)
  (let ((array churn-box))    
    (setf (svref array 0)
	  (logxor 89
		  (logand q1 77)
		  (logand c1 77)
		  (logand start-date 77)))
    (setf (svref array 1)
	  (logxor 195
		  (logand (ash q1 -8) 77)
		  (ash q1 -13)
		  (logand (ash c1 -8) 77)
		  (logand (ash start-date -8) 77)))
    (setf (svref array 2)
	  (logxor 4
		  (logand q2 77)
		  (logand (ash c1 -13) 77)
		  (logand (ash start-date -13) 77)))
    (setf (svref array 3)
	  (logxor 193
		  (logand (ash q2 -8) 77)
		  (ash q1 -13)
		  (logand c2 77)
		  (logand end-date 77)))    
    (setf (svref array 4)
	  (logxor 18
		  (logand q3 77)
		  (logand (ash c2 -8) 77)
		  (logand (ash end-date -8) 77)))
    (setf (svref array 5)
	  (logxor 158
		  (logand (ash q1 -8) 77)
		  (ash q3 -13)
		  (logand (ash c2 -13) 77)
		  (logand (ash end-date -13) 77)))    
    (setf (svref array 6)
	  (logxor 119
		  (logand q4 77)))
    (setf (svref array 7)
	  (logxor 105
		  (logand (ash q4 -8) 77)
		  (ash q1 -13)))    
    (churn-array array churn-key-2 5)    

    (logxor (svref array 3)
	    (ash (svref array 4) 5)
	    (ash (svref array 5) 11))))


;;; The general authorizing function owned only by Gensym.

;(defun make-package-ok (package-name machine-id)
;  (let (q1 q2 q3 q4 q5 q6 c1 c2 c3)
;    (multiple-value-setq (q1 q2)
;      (churn-x package-name))
;    (multiple-value-setq (q3 q4)
;      (churn-y package-name))
;    (multiple-value-setq (q5 q6)
;      (churn-z machine-id))

;    (multiple-value-setq (c1 c2)
;      (churn-r q1 q2 q5 q6))
;    (setq c3 (churn-s q3 q4 q5 q6 c1 c2))

;    (values c1 c2 c3)))

;; The function that can be given to VARs. Note that churn-x
;; and churn-key-1 are not included.
;; The dates are in universal dates, defined in numbers.lisp.
;; Qn is a fixnum that is computed by ML and is stored in
;; a file the authorization program.  That file enumerates the
;; known packages.

(defun make-particular-package-ok (machine-id q1 q2 q3 q4 start-date end-date)
  (let (q5 q6 c1 c2 c3)
    (multiple-value-setq (q5 q6)
      (churn-z machine-id))
    
    (multiple-value-setq (c1 c2)
      (churn-r q1 q2 q5 q6
	       (or start-date 0)
	       (or end-date 0)))
    (setq c3 (churn-s q3 q4 q5 q6 c1 c2 (or start-date 0) (or end-date 0)))
    
    (values c1 c2 c3)))




;; Following Material not to be included in auhorization program.

(defvar churn-key-1	
	(make-array
	  256
	  ':initial-contents
	  '(165 192 60 104 72 215 66 34 226 207 53 27 55 15 167 68 92 112 154
		120 173 88 214 143 107 103 101 176 234 49 13 70 240 206 37 54
		158 134 115 125 80 186 99 169 236 123 41 141 73 118 124 19 227
		135 113 85 117 65 87 4 1 178 81 188 238 195 245 247 127 71 16
		203 11 38 138 131 191 144 31 205 225 59 244 221 114 133 184 91
		56 69 51 61 9 116 89 145 224 179 142 229 2 146 241 228 20 249
		8 77 150 148 45 130 18 102 110 201 32 74 212 251 230 95 48 5
		149 171 250 220 33 98 63 163 209 182 47 42 23 242 126 177 216
		189 52 26 152 75 86 58 172 162 187 223 0 3 43 22 30 29 28 106
		183 218 67 44 159 174 122 7 39 151 24 211 200 10 252 83 14 82
		129 185 97 50 121 213 139 153 204 119 105 64 246 132 208 25
		232 161 111 198 231 248 202 17 157 79 62 168 197 180 239 36
		136 235 243 219 254 175 156 166 160 40 93 6 84 109 108 181 196
		222 90 199 253 194 190 128 147 21 170 193 96 137 237 155 94 217
		140 57 46 35 210 255 100 76 233 164 78 12)))


(defun churn-x (package-name)
  (let ((array churn-box))

    (implant-string-into-array package-name array
			       171 23 221 225 204 37 208 167)

    (churn-array array churn-key-1 5)

    (values
      (logxor (svref array 1)
	      (ash (svref array 2) 5)
	      (ash (svref array 3) 11))
      (logxor (svref array 4)
	      (ash (svref array 5) 5)
	      (ash (svref array 6) 11)))))




(defun churn-y (package-name)
  (let ((array churn-box))

    (implant-string-into-array package-name array 
			       155 87 96 155 224 43 4 175)

    (churn-array array churn-key-2 5)

    (values
      (logxor (svref array 1)
	      (ash (svref array 2) 5)
	      (ash (svref array 3) 11))
      (logxor (svref array 4)
	      (ash (svref array 5) 5)
	      (ash (svref array 6) 11)))))




(defvar assigned-package-names
	'("gensym-gmm"

	  ;; GDA - "Gensym Diagnostic Assistant"
	  ;;   (aka "GDA Version 1" since Version 2 (GDA2) came out
	  ;;   in 1994; see "gensym-gda2" below)
	  ;; Company: Gensym. Mark Kramer
	  "gensym-gda"

	  "gensym-dsp"
	  "orsi-pms" "orsi-exad"
	  "johnson-jps"

	  ;; 11/4/92 - LISE - "Lafarge Informatique Systeme Expert"
	  ;; Company: Ciments Lafarge, France. (MHD 11/4/92)
	  "lafarge-lise"

          ;; 11/19/92 - BASIC - Gensym G2 Basic Course
          ;; Company: Gensym, Cambridge. Michael Levin.  (MHD 11/19/92)
          "gensym-basic"
          ;; 11/19/92 - INTERMEDIATE - Gensym G2 Intermediate Course
          ;; Company: Gensym, Cambridge. Michael Levin.  (MHD 11/19/92)
          "gensym-intermediate"
          ;; 11/19/92 - INTERMEDIATE - Gensym G2 Intermediate Course
          ;; Company: Gensym, Cambridge. Michael Levin.  (MHD 11/19/92)


          ;; 12/11/92 - NL - Gensym NeurOnLine
          ;; Company: Gensym, Cambridge. Mark Kramer.  (MHD 12/11/92)
          "gensym-nol"
          ;; 12/11/92 - EM - Gensym Energy Manager
          ;; Company: Gensym, Cambridge. Andreas Hofmann  (MHD 12/11/92)
          "gensym-em"
          ;; 12/14/92 - HD - Gensym Help Desk
          ;; Company: Gensym, Cambridge. Troy Heindel.  (MHD 12/14/92)
          "gensym-hd"


	  ;; 3/29/93 - FNET - ESIA Flownet
	  ;; Company: ESIA
	  "esia-fnet"

	  ;; 3/29/93 - SPARKS - Coopers & Lybrand SPARKS
	  ;; Company: Coopers & Lybrand
	  "cl-sparks"

	  ;; 5/19/93 - GMQ - Gensym's G2 Message Queues
	  ;; Company: Gensym, Cambridge.  Eric Finch.  (MHD)
	  "gensym-gmq"


	  ;; 7/2/93 (MHD) - GPO - Gensym's Parallel Optimizer
	  ;; Company: Gensym, Cambridge.  Howard Rosenoff.  
	  "gensym-po"

	  ;; 8/2/93 (MHD) - SECUREXP - ORSI's SECUREXP
	  ;; Company: ORSI   
	  "orsi-securexp"

	  ;; 10/8/93 (MHD) - BDS - Biotech Design Simulator
	  ;; Company: Life Sciences    
	  "lsc-bds"

	  ;; 3/7/94 (MHD) - BPR - Business Process Reengineering (BPR)
	  ;; Company: Gensym
	  ;;
	  ;; 6/10/94 (MHD) - This is obsolete! Replaced by
	  ;; ReThink; see below.
	  "gensym-bpr"

	  ;; 3/7/94 (MHD) - OPA - OPerator's Assistant
	  ;; Company: Gensym  (MHD)
	  ;; Last Known Contact: Greg Stanley 
	  "gensym-opa"

	  ;; 6/10/94 (MHD) - Gensym STK1 - Scheduling Toolkit 1 (GST1)
	  ;; Company: Gensym
	  ;; Last Known Contact: Bill Morrow (Marketing: Jeff Bodenstab)
	  "gensym-stk1"

	  ;; 6/10/94 (MHD) - Gensym STK2 - Scheduling Toolkit 2 (GST2)
	  ;; Company: Gensym
	  ;; Last Known Contact: Bill Morrow (Marketing: Jeff Bodenstab)
	  "gensym-stk2"

	  ;; 6/10/94 (MHD) - Gensym-ReThink
	  ;; Company: Gensym
	  ;; Long Name: ReThink
	  ;; Last Known Contact: Tom Foley
	  "gensym-rethink"

	  ;; 6/23/94 (MHD) - EASE SPT
	  ;; Company: EASE Software Engineering GmbH
	  ;; Long Name: Schematic Programming Tool
	  ;; Short Name: SPT
	  ;; Last Known Contact: Jean-Marie Foret
	  "ease-spt"

	  ;; Registration Date (Person): 8/1/94 (MHD)
	  ;; Package Name: HBS-CUA
	  ;; Company: HBS Computers
	  ;; Long Name: Crude Unit Advisor
	  ;; Short Name: CUA
	  ;; Last Known Contact: Joe Harrington
	  "hbs-cua"

	  ;; Registration Date (Person): 8/1/94 (MHD)
	  ;; Package Name: HBS-APMD
	  ;; Company: HBS Computers
	  ;; Long Name: Advanced Process Monitor & Diagnostics
	  ;; Short Name: APMD
	  ;; Last Known Contact: Joe Harrington
	  "hbs-apmd"

	  ;; Registration Date (Person): 8/3/94 (MHD)
	  ;; Package Name: SIMCON-GMB
	  ;; Company: ABB Simcon Inc.
	  ;; Long Name: SIMCON Graphical Model Builder
	  ;; Short Name: GMB
	  ;; Last Known Contact: none
	  "simcon-gmb"

	  ;; Registration Date (Person): 12/5/94 (MHD)
	  ;; Package Name: GENSYM-GDA2
	  ;; Company: Gensym
	  ;; Long Name: Gensym Diagnostic Assistant (Version 2)
	  ;; Short Name: GDA2
	  ;; Last Known Contact: Mark Kramer
	  "gensym-gda2"

	  ;; Registration Date (Person): 5/16/95 (MHD)
	  ;; Package Name: GENSYM-GSPC
	  ;; Company: Gensym
	  ;; Long Name: G2 Statistical Process Control Package
	  ;; Short Name: GSPC
	  ;; Last Known Contact: Jere Beasley
	  "gensym-gspc"

	  ;; Registration Date (Person): 5/30/95 (MHD)
	  ;; Package Name: GENSYM-BAYES-ONLINE
	  ;; Company: Gensym
	  ;; Long Name: Bayes' Rule Network Modeling Package
	  ;; Short Name: Bayes On-Line
	  ;; Last Known Contact: Jere Beasley
	  "gensym-bayes-online"

	  ;; Registration Date (Person): 5/30/95 (MHD)
	  ;; Package Name: GENSYM-SPACE-PLANNER
	  ;; Company: Gensym
	  ;; Long Name: 2-D and 3-D Spacial Layout Package
	  ;; Short Name: Gensym Space Planner
	  ;; Last Known Contact: Jere Beasley
	  "gensym-space-planner"

	  ;; Registration Date (Person): 7/27/95 (MHD)
	  ;; Package Name: GENSYM-VB-BRIDGE
	  ;; Company: Gensym
	  ;; Long Name: Gensym Visual Basic Bridge
	  ;; Short Name: Gensym VB Bridge
	  ;; Last Known Contact: John Joyce
	  "gensym-vb-bridge"

	  ;; See products.lisp
	  "gensym-gas"))

(defun supply-codes-for-package (package-name)
  (let (q1 q2 q3 q4)
    (multiple-value-setq (q1 q2)
      (churn-x package-name))
    (multiple-value-setq (q3 q4)
      (churn-y package-name))
    ;; make sure there's no conflict:
    (loop for assigned-package-name in assigned-package-names
	  unless (string-equal assigned-package-name package-name)
	    do (multiple-value-bind (x1 x2)
		   (churn-x assigned-package-name)
		 (multiple-value-bind (y1 y2)
		     (churn-y assigned-package-name)
		   (when (or (= q1 x1) (= q2 x2) (= q3 y1) (= q4 y2))
		     (error "~a conflicts with an existing, assigned package name: ~a; ~
                             Please choose a different name for ~a."
			    package-name assigned-package-name
			    package-name)))))
    (values q1 q2 q3 q4)))





(defun print-all-assigned-codes ()
  (loop for package-name in assigned-package-names do
	(multiple-value-bind (q1 q2 q3 q4)
	    (supply-codes-for-package package-name)
	  (terpri)
	  (format t "~a     ~d   ~d   ~d   ~d~%" package-name q1 q2 q3 q4))))






;;; Test Stuff

;(defun test1 (string n)
;  (implant-string-into-array string churn-box 
;			     71 23 221 225 204 37 208 167)
;  (loop for i from 1 to n
;	do
;    (churn-array churn-box churn-key-1 1)
;    (print (concatenate'list churn-box))))



;(defun test2 (function)
;  (do-symbols (symbol 'ab)
;    (multiple-value-bind (x y)
;	(funcall function (symbol-name symbol))
;      (if (or (not (fixnump x))
;	      (not (fixnump y)))
;	  (cerror "continue" "not fixnum"))
;      (format t "~a   ~d   ~d~%" symbol x y)))))



;(defun test3 (function)
;  (let ((array (make-array 10)))
;    (loop for i from 0 to 9 do (setf (svref array i) 0))

;    (do-symbols (symbol 'ab)
;      (multiple-value-bind (x y)
;	  (funcall function (symbol-name symbol))
;	(incf (svref array (ceiling (log (+ x 1) 10))))
;	(incf (svref array (ceiling (log (+ y 1) 10))))
;	(when (or (< x 100) (< y 100)) (format t "~a   ~d   ~d~%" symbol x y))
;	))      

;    (concatenate'list array)

;    ))



;(defun test4 ()
;  (let ((array (make-array 10))
;	(odd? t) previous-symbol)
;    (loop for i from 0 to 9 do (setf (svref array i) 0))

;    (do-symbols (symbol 'ab)
;      (cond
;	(odd?
;	 (setq odd? nil)
;	 (setq previous-symbol symbol))
;	(t
;	 (setq odd? t)
;	 (multiple-value-bind (c1 c2 c3)
;	     (make-package-ok (symbol-name previous-symbol)
;			      (symbol-name symbol))
;	   (incf (svref array (ceiling (log (+ c1 1) 10))))
;	   (incf (svref array (ceiling (log (+ c2 1) 10))))
;	   (incf (svref array (ceiling (log (+ c3 1) 10))))
;	   (when (or (< c1 100) (< c2 100) (< c3 100))
;	     (format t "~a  ~a  ~d  ~d  ~d~%" previous-symbol symbol c1 c2 c3))))))

;    (concatenate'list array)))


;(defun make-random-string (max-length)
;  (let ((num (random (expt 36 max-length))))
;    (format nil "~36r" num)))




;(defun test5 (n)
;  (let ((array (make-array 10)))

;    (loop for i from 0 to 9 do (setf (svref array i) 0))

;    (loop for i from 1 to n
;	  for s1 = (make-random-string 6)
;	  for s2 = (make-random-string 6)
;	  doing
;      (multiple-value-bind (c1 c2 c3)
;	  (make-package-ok  s1 s2)
	
;	(incf (svref array (ceiling (log (+ c1 1) 10))))
;	(incf (svref array (ceiling (log (+ c2 1) 10))))
;	(incf (svref array (ceiling (log (+ c3 1) 10))))
;	(when (or (< c1 100) (< c2 100) (< c3 100))
;	  (format t "~a  ~a  ~d  ~d  ~d~%" s1 s2 c1 c2 c3))))

;    (concatenate'list array)))




;;; How to make authorizing program:

;;; This entire file should be included. The only function to interface
;;; to is (make-particular-package-ok machine-id q1 q2 q3 q4).

;;; A package authorization is issued for a particular package, and a particular
;;; machine id. The machine id is a string, and is insensitive to case and
;;; the presence of non-alpha-numerics. This is the same as for the
;;; G2 authorizing software. 

;;; There is no provision for inputing a package name. Instead, 4 numbers
;;; which are determined from the package name are provided. Thus even if you own
;;; this software, you cannot authorize other than for packages for which you have
;;; these codes.

;;; I suggest that the prgram that embeds this should read a fixed file as it
;;; initializes itself. This will consist of any number of lines each having
;;; a package-name followed by 4 numbers. The program will offer the user a
;;; multiple choice of the packages that it is able to authorize, and prompt for
;;; a machine-id. It will then supply the code numbers for that package name,
;;; and the machine-id to make-particular-package-ok. The three values are the
;;; authorizing codes for the package on that machine.

;;; The four numbers that authorize the authorizer will be given out by development
;;; department as packages are developed. The management of Gensym can
;;; decide whether it wishes to entrust binary versions of this program to particular
;;; VARS, or whether their customers will have to call Gensym for authorization,
;;; which will require a careful liason betwen Dorothy and the VAR.





;;;; Automatic OK File Generation

(defparameter code-block (make-array 8))



(defparameter
  block3
  #(12 78 164 233 76 100 255 210 35 46 57 140 217 94 155 237 137 96 193 170 21 147 128 190
       194 253 199 90 222 196 181 108 109 84 6 93 40 160 166 156 175 254 219 243 235 136
       36 239 180 197 168 62 79 157 17 202 248 231 198 111 161 232 25 208 132 246 64 105
       119 204 153 139 213 121 50 97 185 129 82 14 83 252 10 200 211 24 151 39 7 122 174
       159 44 67 218 183 106 28 29 30 22 43 3 0 223 187 162 172 58 86 75 152 26 52 189 216
       177 126 242 23 42 47 182 209 163 63 98 33 220 250 171 149 5 48 95 230 251 212 74 32
       201 110 102 18 130 45 148 150 77 8 249 20 228 241 146 2 229 142 179 224 145 89 116
       9 61 51 69 56 91 184 133 114 221 244 59 225 205 31 144 191 131 138 38 11 203 16 71
       127 247 245 195 238 188 81 178 1 4 87 65 117 85 113 135 227 19 124 118 73 141
       41 123 236 169 99 186 80 125 115 134 158 54 37 206 240 70 13 49 234 176 101 103 107
       143 214 88 173 120 154 112 92 68 167 15 55 27 53 207 226 34 66 215 72 104 60
       192 165))

(defparameter
  block4				; permuted for version 4
  #(12 78 164 233 76 100 255 210 35 46 57 140 217 94 155 237
      137 96 193 170 21 147 128 190
      194 253 199 90 222 196 181 108 109 84 6 93 40 160 166
      156 175 254 219 243 235 136
      36 239 180 197 168 62 79 157 17 202 248 231 198 111
      161 232 25 208 132 246 64 105
      119 204 153 139 213 121 50 97 185 129 82 14 83 252 10
      200 211 24 151 39 7 122 174
      159 44 67 218 183 106 28 29 30 22 43 3 0 223 187 162 172
      58 86 75 152 26 52 189 216
      177 126 242 23 42 47 182 209 163 63 98 33 220 250 171 149 5
      48 95 230 251 212 
      201 110 102 18 130 45 148 150 77 8 249 20 228 241 146
      2 229 142 179 224 145 89 116
      9 61 51 69 56 91 184 133 114 221 244 59 225 205
      31 144 191 131 138 38 11 203 16 71 74 32
      127 247 245 195 238 188 81 178 1 4 87 65 117 85 113
      135 227 19 124 118 73 141
      41 123 236 169 99 186 80 125 115 134 158 54 37 206 240 70
      13 49 234 176 101 103 107
      143 214 88 173 120 154 112 92 68 167 15 55 27 53 207 226
      34 66 215 72 104 60
      192 165))

(defmacro transpose-code-block ()
  (let ((r-var-list '(r0 r1 r2 r3 r4 r5 r6 r7))
	(s-var-list '(s0 s1 s2 s3 s4 s5 s6 s7)))
    
    `(let*
       ,(nconc
	  (loop for r-var in r-var-list
		   for i from 0
		   collecting `(,r-var (svref code-block ,i)))
	  (loop for s-var in s-var-list
		   collecting `(,s-var 0)))

       ,@(loop for i from 0 to 7
	       for r-var in r-var-list
	       nconcing
		 (loop for j from 0 to 7
		       for s-var in s-var-list
		       nconcing
			 `((if (/= 0 (logand ,r-var ,(ash 1 j)))
			       (setq ,s-var (logior ,s-var ,(ash 1 i)))))))

       ,@(loop for k from 0 to 7
	       for s-var in s-var-list
	       collecting
		 `(setf (svref code-block ,k) ,s-var)))))


(defmacro replace-code-block ()
  '(loop for i from 0 to 7 do
     (setf (svref code-block i)
	   (svref
	    (keytab)
	    ;; replacement for this is above:   (MHD/DDM 6/5/97)
	    ;; (And note: this depends on the binding of keytab1 done in check-kbs.)
;	    (if ok-file-generation-doing-pass-for-version-4-p
;		block4
;		block3)	    
	    (svref code-block i)))))



(defmacro encode-code-block ()
  '(loop for i from 1 to 5 do
     (replace-code-block)
     (transpose-code-block)))

;;; Given block3 which is a key, and code-block which is a scratchpad, and does
;;; not have to be in any state, encode-whole-array takes any array of byte size
;;; integers and returns 4 fixnums which are the result, and a checksum, the
;;; fifth code.

;;; To make use of this, take any number of keys which are strings, concatenate
;;; them and normalize the result. Take this bignum and fill an array of
;;; appropriate size with its bytes.

;;; New? is t for use new algorithm.
;;; product code is a fixnum, default is 0.
;;; expiration-date? is nil or a universal-date.

(defun encode-whole-array
    (array new? product-code expiration-date?
	   number-of-processes?
	   maximum-number-of-concurrent-floating-telewindows-allowed
	   maximum-t2s-allowed)
  (macrolet ((extract-byte (fixnum byte-position)
	       ;; Cloned from sequences2.lisp
	       (if (typep byte-position 'fixnum)
		   `(logandf (ashf ,fixnum ,(*f -8 byte-position)) 255)
		   `(logandf (ashf ,fixnum (*f -8 ,byte-position)) 255))))
    (loop with size = (length array)
	  with bunch-count = (- (ceiling size 8) 1)
	  for i from 1 to bunch-count
	  initially (loop for i from 0 to 7 do
		      (setf (svref code-block i) (svref array i)))
	  do
      (encode-code-block)
      (loop for k from 0 to 7
	    for offset
		= (* 8 (if new? i bunch-count))
	    for j = (+ k offset) do
	(setf (svref code-block k)
	      (logxor (svref code-block k)
		      (if (< j size)
			  (svref array j)
			  j))))
	  finally
	    
	    (when new?
	      (setf (svref code-block 7)
		    (logxor (svref code-block 7) (extract-byte product-code 0)))
	      (setf (svref code-block 6)
		    (logxor (svref code-block 6) (extract-byte product-code 1)))
	      
	      (when expiration-date?
		(setf (svref code-block 5)
		      (logxor (svref code-block 5) (extract-byte expiration-date? 0)))	    
		(setf (svref code-block 4)
		      (logxor (svref code-block 4) (extract-byte expiration-date? 1))))

	      (when number-of-processes?
		(setf (svref code-block 3)
		      (logxor (svref code-block 3) number-of-processes?)))

	      (setf (svref code-block 2)
		    (logxor (svref code-block 2)
			    maximum-number-of-concurrent-floating-telewindows-allowed))

	      ;; exact (pasted) copy of what's in numbers
	      (unless (= maximum-t2s-allowed 0) ; default
		(setf (svref code-block 1)
		      (logxor (svref code-block 1)
			      (extract-byte maximum-t2s-allowed 0)))
		;; the max is 2^16-1, so we need both bytes to get it all
		(setf (svref code-block 0)
		      (logxor (svref code-block 0)
			    (extract-byte maximum-t2s-allowed 1)))))

	    (encode-code-block)
	    (return
	      (values (+ (svref code-block 0) (* 256 (svref code-block 1)))
		      (+ (svref code-block 2) (* 256 (svref code-block 3)))
		      (+ (svref code-block 4) (* 256 (svref code-block 5)))
		      (+ (svref code-block 6) (* 256 (svref code-block 7))))))))

;; from check-kbs.lisp
(defvar ok-file-generation-doing-pass-for-version-4-p nil)

(defun y17
    (key-string products converted-expiration-date?
		number-of-processes?
		maximum-number-of-concurrent-floating-telewindows-allowed
		maximum-number-of-concurrent-floating-tw2-allowed)
  (declare (special
	     ;; In modules sequences1.lisp
	     chaining-refresh-list
	     new-modulus))
  (macrolet ((calling-g2-function ((function . args))
	       `(,function ,@args))
	     (inner-multiply-in-g2 (&rest args)
	       `(inner-multiply ,@args)))
    ;; The above macros just formalize the interface, which
    ;; requires some G2 functions.
    (let* ((modulus new-modulus)
	   (key-string-with-finger
	     (if ok-file-generation-doing-pass-for-version-4-p
		 (concatenate 'string key-string chaining-refresh-list)
		 key-string))
	   (modularized-key (calling-g2-function
			      (modulo-string-hash-of-lisp-string
				key-string-with-finger modulus)))
	   (array (calling-g2-function
		    (make-array-from-lisp-strings
		      key-string
		      chaining-refresh-list)))
	   (product-code (calling-g2-function
			   (compute-product-code-function
			     products))))
      (multiple-value-bind (c1 c2 c3 c4)
	  (encode-whole-array 
	    array t product-code converted-expiration-date? number-of-processes?
	    maximum-number-of-concurrent-floating-telewindows-allowed
	    maximum-number-of-concurrent-floating-tw2-allowed)
	(values c1 c2 c3 c4
		(let ((c1x
			(if (>=f c1 100)
			    c1
			    (+f 394 (*f 185 c1))))
		      (c2x
			(if (>=f c2 100)
			    c2
			    (+f 260 (*f 165 c2))))
		      (c3x
			(if (>=f c3 100)
			    c3
			    (+f 111 (*f 64 c3))))
		      (c4x
			(if (>=f c4 100)
			    c4
			    (+f 973 (*f 469 c4)))))
		  (mod
		    (logxorf
		      (inner-multiply-in-g2 modularized-key c3x)
		      (inner-multiply-in-g2 c1x product-code)
		      (inner-multiply-in-g2 c2x c4x)
		      (inner-multiply-in-g2
			(or converted-expiration-date? 0)
			(or converted-expiration-date? 0))
		      (if number-of-processes?
			  (inner-multiply-in-g2 c3x number-of-processes?)
			  0)
		      (if number-of-processes?
			  (inner-multiply-in-g2 c4x (ashf number-of-processes? 8))
			  0)
		      (inner-multiply-in-g2
			c1x
			maximum-number-of-concurrent-floating-telewindows-allowed)
		      (inner-multiply-in-g2
			c2x
			(ashf maximum-number-of-concurrent-floating-telewindows-allowed
			      8))
		      (inner-multiply
			c3x
			maximum-number-of-concurrent-floating-tw2-allowed)
		      (inner-multiply
			c4x
			(ash maximum-number-of-concurrent-floating-tw2-allowed
			     12)))
		    modulus)))))))




;;; Find-ok-for-this-machine is a TI-Explorer, Development-only function
;;; that returns the OK opject for this machine in the current KB, if there
;;; is one.

#+obsolete
(defun find-ok-for-this-machine ()
  (loop with id-for-this-machine-as-string?
	  = (get-local-machine-id-as-text-string)
	with normalized-id-for-this-machine-as-string?
	  = (if id-for-this-machine-as-string?
		(normalize-key id-for-this-machine-as-string?))
	initially
	  (when (null normalized-id-for-this-machine-as-string?)
	    (return nil))
	for ok being each class-instance of 'ok
	as machine-id-for-ok? = (machine-id ok)
	as normalized-id?
	   = (if machine-id-for-ok? (normalize-key machine-id-for-ok?))
	when (and normalized-id?
		  (= normalized-id?
		     normalized-id-for-this-machine-as-string?))
	  return ok))
