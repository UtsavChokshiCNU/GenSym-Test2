;;; -*- mode: lisp; package: bundle -*-

(in-package "BUNDLE")

;;; Copyright (c) 2012-2013 Versata Software Inc.
;;; All Rights Reserved.

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; CREATEKEY - an interactive, non-GUI, for creating license keys
;;; (for G2 and Integrity Bundles only)

;;; Jeffrey P. Golden, Mark H. David

;;; The only external entry point to the code in this file is
;;; (run-createkey-dialog).

;;; Usage: createkey <system_id> <family_id> <bundle_id> <component_indices...>

(defvar families
  '("G2" "Integrity"))

;;; The same order as in bundle/c/codes.h --binghe, 2011/09/15
(defvar g2-systems
  '("Windows x86" "SPARC Solaris" "AIX (RS6000)" "PA-RISC HP-UX"
    "Linux x86" "Compaq Tru64 UNIX" "Itanium HP-UX" "Linux x86_64" "Windows x64"))

(defvar g2-bundles
  '("G2 deployment" "G2 development" "Temporary (G2 development)"))

(defvar g2-optional-bridges
  '("Corbalink Bridge"		; 10 (component ID from tools/datafiles/families/g2-2011.fam)
    "OPC Client Bridge"		; 11
    "PI Bridge"			; 12
    "Oracle Bridge"		; 13
    "Sybase Bridge"		; 14
    "ODBC Bridge"		; 15
    "ODBC UNICODE Bridge"	; 16
    "SymScale / MS SQL Bridge"	; 17
    "JDBC Bridge"))		; 18

(defvar number-of-bridges (length g2-optional-bridges))

(defvar deployment-number-of-clients 
  '(4 8 12 16 20 24 28 32))

(defvar development-number-of-clients 
  '(1 2 3 4 5 6 7 8 9 10 12 16 20 24 28 32))

(defvar temporary-authorizations
  '("July 1, 2000 to Dec. 25, 2000" "Oct. 1, 2000 to Mar. 25, 2001"
    "Jan. 1, 2001 to June 25, 2001" "Apr. 1, 2001 to Sep. 25, 2001" 
    "July 1, 2001 to Dec. 25, 2001" "Oct. 1, 2001 to Mar. 25, 2002"))

(defvar common-g2-components
  '(1 2 3 4 5 6 7 8))

(defvar automatic-deployment-g2-components
  '(14))

(defvar automatic-development-g2-components
  '(19 20 21))

(defvar integrity-packages
  '("Integrity Core Development" "Integrity Discover Development"
    "Integrity Premium Development" "Integrity Reasoner Development"
    "Integrity Core Deployment" "Integrity Discover Deployment"
    "Integrity Premium Deployment" "Integrity Reasoner Deployment"))

(defvar integrity-optional-bridges
  '("Java Generic SNMP Bridge" "G2 SNMP HPOV Bridge (sparcsol)"
    "G2 SNMP HPOV Bridge (HPUX)" "G2 SNMP Netview"))

(defvar common-integrity-components
  '(1 2 3 4 5 6 7 8))

(defvar automatic-integrity-components
  '(13))

(defvar *is-family-g2-p* nil)

(defun createkey ()
  (let (selections system_id family_id acceptablep)

    ;; Selecting Family
    (terpri)
    (terpri)
    (loop until acceptablep do 
      (princ "Type a number to select Family:")
      (terpri)
      (princ "1. G2  2. Integrity")
      (terpri)
      (terpri)
      (setq family_id (createkey-read))
      (cond ((or (not (integerp family_id))
		 (< family_id 1)
		 (> family_id 2))
	     (princ "Family as entered is not an acceptable integer.")
	     (format t "~%Please try again!~2%"))
	    (t (setq acceptablep t))))

    (format t "~%You selected ~a.~%" (elt families (1- family_id)))
    
    ;; Selecting System
    (setq acceptablep nil)
    (terpri)
    (loop until acceptablep do 
      (princ "Type a number to select System:")
      (terpri)
      (princ "1. Windows x86  2. SPARC Solaris  3. AIX (RS6000)  4. PA-RISC HP-UX")
      (terpri)
      (princ "5. Linux x86  6. Compqa Tru64 UNIX  7. Linux x86_64")
      (terpri)
      (princ "8. Itanium HP-UX  9. Windows x64")
      (terpri)
      (terpri)
      (setq system_id (createkey-read))
      (cond ((or (not (integerp system_id))
		 (< system_id 1)
		 (> system_id 9))
	     (princ "System as entered is not an acceptable integer.")
	     (format t "~%Please try again!~2%"))
	    (t (setq acceptablep t))))

    (format t "~%You selected ~a.~%" (elt g2-systems (1- system_id)))

    (push (elt g2-systems (1- system_id)) selections)
    (push (elt families (1- family_id)) selections)

    (if (= family_id 2) (setq family_id 4))
    (when (= family_id 1)
      (setq family_id 219) ; jump to G2 2011 (see tools/datafiles/families/family-id.dat)
      (setq *is-family-g2-p* t))

    (if *is-family-g2-p*
	(createkey-g2-family selections family_id system_id)
        (createkey-integrity-family selections family_id system_id))))

(defun createkey-g2-family (selections family_id system_id)
  (let (bundle_id bridge_id_list acceptablep)

    ;; Selecting Bundle
    (terpri)
    (loop until acceptablep do 
      (format t "Type a number to select Bundle:")
      (format t "~%1. G2 deployment   2. G2 development~%~
                   3. Temporary (G2 development)~2%")
      (setq bundle_id (createkey-read))
      (cond ((or (not (integerp bundle_id))
		 (< bundle_id 1)
		 (> bundle_id 3))
	     (princ "Bundle as entered is not an acceptable integer.")
	     (format t "~%Please try again!~2%"))
	    (t (setq acceptablep t))))
    
    (format t "~%You selected ~a.~%" (elt g2-bundles (1- bundle_id)))
    (push (elt g2-bundles (1- bundle_id)) selections)

    ;; Selecting Bridges for G2
    (setq acceptablep nil)
    (loop until acceptablep do 
      (format t "~%On a single line, type one or more numbers each~%~
                 separated by a space to select Bridges for the bundle.~%~
                 The standard selection is one or two numbers, e.g. 1 3~%~
                 (Select one number for two deployments of the same bridge.)~%~
                 Type 0 to select no bridges.~%~
                 Type 6 to select all five bridges.~%")
      (format t "~%0. None~%~
                   1. Corbalink Bridge   2. OPC Client Bridge   3. PI Bridge~%~
                   4. Oracle Bridge   5. Sybase Bridge~%~
                   6. ODBC Bridge     7. ODBC UNICODE Bridge~%~
                   8. MS SQL Bridge   9. JDBC Bridge. 10. All~2%")
      (setq bridge_id_list (createkey-read-seq))
      (cond ((or (null bridge_id_list)
		 (and (or (member 0 bridge_id_list)
			  (member (1+ number-of-bridges) bridge_id_list))
		      (cdr bridge_id_list))
		 (dolist (bridge_id bridge_id_list)
		   (if (or (< bridge_id 0) (> bridge_id (1+ number-of-bridges)))
		       (return t)))
		 (not (equal bridge_id_list
			     (remove-duplicates bridge_id_list))))
	     (princ "The Bridges as entered are not acceptable.")
	     (format t "~%Please try again!~2%"))
	    ((and (/= (length bridge_id_list) 2)
                  (or (/= (length bridge_id_list) 1)
                      (member 0 bridge_id_list)
		      (member (1+ number-of-bridges) bridge_id_list)))
	     (format t "~%You selected ~d bridge~:p which is non-standard.~%~
                        One or two bridges is standard."
		     (cond ((equal bridge_id_list '(0)) 0)
			   ((equal bridge_id_list (list (1+ number-of-bridges))) number-of-bridges)
			   (t (length bridge_id_list))))
	     (if (y-or-n-p "Is this OK?")
		 (setq acceptablep t)
		 (format t "~%Please try again!~%")))
	    (t (setq acceptablep t))))
      
    (cond ((equal bridge_id_list '(0))
	   (format t "~%You selected no bridges.~%")
	   (setq bridge_id_list nil))
	  ((equal bridge_id_list (list (1+ number-of-bridges)))
	   (setq bridge_id_list (loop for i from 1 upto number-of-bridges collect i))))

    (when bridge_id_list 
      (format t "~%You selected the following bridges:~%")
      (dolist (bridge_id bridge_id_list)
	(format t " ~a~%" (elt g2-optional-bridges (1- bridge_id)))
	(push (elt g2-optional-bridges (1- bridge_id)) selections)))

    (createkey-temporary-check 
      selections family_id system_id bundle_id bridge_id_list)))

(defun createkey-integrity-family (selections family_id system_id)
  (let (bundle_id bridge_id_list acceptablep)

    ;; Selecting the Integrity Package
    (terpri)
    (loop until acceptablep do 
      (princ "Type a number to select Package:")
      (format t "~%1. Integrity Core Development      2. Integrity Discover Development~%~
                   3. Integrity Premium Development   4. Integrity Reasoner Development~%~
                   5. Integrity Core Deployment       6. Integrity Discover Deployment~%~
                   7. Integrity Premium Deployment    8. Integrity Reasoner Deployment")
      (terpri)
      (terpri)
      (setq bundle_id (createkey-read))
      (cond ((or (not (integerp bundle_id))
		 (< bundle_id 1)
		 (> bundle_id 8))
	     (princ "Package as entered is not an acceptable integer.")
	     (format t "~%Please try again!~2%"))
	    (t (setq acceptablep t))))
    
    (format t "~%You selected ~a.~%" (elt integrity-packages
					  (1- bundle_id)))
    (push (elt integrity-packages (1- bundle_id)) selections)

    ;; Selecting Bridges for Integrity
    (setq acceptablep nil)
    (loop until acceptablep do 
      (format t "~%On a single line, type one or more numbers each~%~
                 separated by a space to select Bridges for the bundle.~%~
                 The standard selection is one or two numbers, e.g. 1 3~%~
                 (Select one number for two deployments of the same bridge.)~%~
                 Type 0 to select no bridges.~%~
                 Type 5 to select all four bridges.~%")
      (format t "0. None~%~
                 1. Java Generic SNMP Bridge~%~
                 2. G2 SNMP HPOV Bridge (sparcsol)~%~
                 3. G2 SNMP HPOV Bridge (HPUX)~%~
                 4. G2 SNMP Netview~%~
                 5. All~2%")
      (setq bridge_id_list (createkey-read-seq))
      (cond ((or (null bridge_id_list)
		 (and (or (member 0 bridge_id_list)
			  (member 5 bridge_id_list))
		      (cdr bridge_id_list))
		 (dolist (bridge_id bridge_id_list)
		   (if (or (< bridge_id 0) (> bridge_id 5))
		       (return t)))
		 (not (equal bridge_id_list
			     (remove-duplicates bridge_id_list))))
	     (princ "The Bridges as entered are not acceptable.")
	     (format t "~%Please try again!~2%"))
	    ((and (/= (length bridge_id_list) 2)
                  (or (/= (length bridge_id_list) 1)
                      (member 0 bridge_id_list)))
	     (format t "~%You selected ~d bridge~:p which is non-standard.~%~
                        One or two bridges is standard."
		     (cond ((equal bridge_id_list '(0)) 0)
			   ((equal bridge_id_list '(5)) 4)
			   (t (length bridge_id_list))))
	     (if (y-or-n-p "Is this OK?")
		 (setq acceptablep t)
		 (format t "~%Please try again!~%")))
	    (t (setq acceptablep t))))
      
    (cond ((equal bridge_id_list '(0))
	   (format t "~%You selected no bridges.~%")
	   (setq bridge_id_list nil))
	  ((equal bridge_id_list '(5))
	   (setq bridge_id_list '(1 2 3 4))))

    (when bridge_id_list 
      (format t "~%You selected the following bridges:~%")
      (dolist (bridge_id bridge_id_list)
	(format t " ~a~%" (elt integrity-optional-bridges (1- bridge_id)))
	(push (elt integrity-optional-bridges (1- bridge_id)) selections)))
    
    (createkey-temporary-check 
      selections family_id system_id bundle_id bridge_id_list)))

(defun createkey-temporary-check
    (selections family_id system_id bundle_id bridge_id_list)

    ;; Selecting number of Clients or temporary authorization 
    ;; (which means one client).
    (if (and *is-family-g2-p* (= bundle_id 3))
	(createkey-temporary-authorization 
	  selections family_id system_id 2 bridge_id_list)
	(createkey-number-of-clients 
	  selections family_id system_id bundle_id bridge_id_list)))

(defun createkey-number-of-clients 
    (selections family_id system_id bundle_id bridge_id_list)
  (let (client_id
	acceptablep
	(deploymentp (or (and *is-family-g2-p* (= bundle_id 1))
			 (and (= family_id 4) (>= bundle_id 5)))))

    ;; Selecting number of Clients
    (terpri)
    (loop until acceptablep do 
      (format t "Type one of the following numbers to select the number~%~
                 of clients.  ~d is standard for ~a.~2%"
              (if deploymentp 4 1)
              (if deploymentp "deployment" "development"))
      (if deploymentp 
	  (format t "4 8 12 16 20 24 28 32~2%")
	  (format t "1 2 3 4 5 6 7 8 9 10 12 16 20 24 28 32~2%"))
      (setq client_id (createkey-read-seq))
      (cond ((or (not (listp client_id))
		 (rest client_id)
		 (not (integerp (setq client_id (first client_id))))
		 (not (member client_id 
			      (if deploymentp 
				  deployment-number-of-clients 
				  development-number-of-clients))))
	     (princ "Number of clients as entered is not an acceptable integer.")
	     (format t "~%Please try again!~2%"))
	    (t (setq acceptablep t))))
    
    (format t "~%You selected ~d client~:p.~%" client_id)
    
    (push (format nil "~d client~:p" client_id) selections)

    (terpri)
    (values (1- system_id)
	    family_id 
	    (if *is-family-g2-p* bundle_id (+ bundle_id 40))
	    (mapcar #'(lambda (bridge_id) (+ bridge_id 8))
		    bridge_id_list)
	    (if deploymentp 
		(+ (if *is-family-g2-p* 15 14)
		   (position client_id deployment-number-of-clients))
		(+ (if *is-family-g2-p* 17 14)
		   (position client_id development-number-of-clients)))
	    (nreverse selections))))

(defun createkey-temporary-authorization 
    (selections family_id system_id bundle_id bridge_id_list)
  (let (client_id acceptablep)

    ;; Selecting temporary authorization (which means one client).
    (terpri)
    (loop until acceptablep do 
      (format t "Type one of the following numbers to select the~%~
                 temporary authorization:~%")
      (format t "~%1. July 1, 2000 to Dec. 25, 2000~%~
                   2. Oct. 1, 2000 to Mar. 25, 2001~%~
                   3. Jan. 1, 2001 to June 25, 2001~%~
                   4. Apr. 1, 2001 to Sep. 25, 2001~%~
                   5. July 1, 2001 to Dec. 25, 2001~%~
                   6. Oct. 1, 2001 to Mar. 25, 2002~2%")
      (setq client_id (createkey-read))
      (cond ((or (not (integerp client_id))
		 (< client_id 1)
		 (> client_id 6))
	     (princ "Temporary authorization as entered is not an acceptable integer.")
	     (format t "~%Please try again!~2%"))
	    (t (setq acceptablep t))))

    (format t "~%You selected ~a~%" (elt temporary-authorizations (1- client_id)))
    
    (push (elt temporary-authorizations (1- client_id)) selections)

    (terpri)
    (values (1- system_id)
	    family_id 
	    bundle_id 
	    (mapcar #'(lambda (bridge_id) (+ bridge_id 8))
		    bridge_id_list)
	    (+ client_id 32)
	    (nreverse selections))))

(defun createkey-read ()
  (let ((string (read-line)))
    (if (and (= (length string) 1)
	     (digit-char-p (char string 0)))
	(read-from-string string)
	nil)))

(defun createkey-read-seq ()
  ;; createkey-read-seq reads a line of integers each separated
  ;; by one or more spaces and returns a list of those integers.
  ;; nil is immediately returned for bad input.
  (let* ((string (read-line)) (length (length string))
	 (pos 0) integer list)
    (loop while (> length pos) do
      (let ((char (char string pos)))
	(cond ((digit-char-p (char string pos))
	       (multiple-value-setq (integer pos)
		 (read-from-string string nil nil :start pos))
	       (push integer list))
	      ((char= char #\Space)
	       (incf pos))
	      (t (return-from createkey-read-seq nil)))))
    (nreverse list)))

(defun run-createkey-dialog ()
  (loop do (run-createkey-dialog-1 nil)
	unless (y-or-n-p "~%Create another key?")
	  do (format t "~%Thanks, goodbye.~%")
	     (quit)))

(defun run-createkey-dialog-1 (debuggingp)
  (multiple-value-bind
      (system_id family_id bundle_id bridge-list client_number selections)
      (createkey)
    (format t "~%You selected:~%")
    (loop for i from 0 below (length selections) do
      (format t " ~a~%" (elt selections i)))
    (terpri)
    (when (y-or-n-p "Is this OK?")
      (let ((command-line
	      (with-output-to-string (stream)
		(format stream "$SRCBOX/bundle/c/$MACHINE/createkey ~d ~d ~d"
			system_id family_id bundle_id)
		(dolist (x (cond (*is-family-g2-p*
                                  common-g2-components)
                                 (t common-integrity-components)))
		  (format stream " ~d" x))

		(dolist (x bridge-list)
		  (format stream " ~d" x))
		
		(if *is-family-g2-p*
		    (dolist (x (case bundle_id 
				 (1 automatic-deployment-g2-components)
				 (2 automatic-development-g2-components)))
		      (format stream " ~d" x))
		    (dolist (x automatic-integrity-components)
		      (format stream " ~d" x)))

		(format stream " ~d" client_number))))
	
	(cond (debuggingp
	       (print command-line)
	       (when (y-or-n-p "Is this OK?")
		 (shell command-line)
		 (format t "~%OK")
		 'done))
	      (t
	       (shell command-line)
	       (format t "~%OK")
	       'done))))))
