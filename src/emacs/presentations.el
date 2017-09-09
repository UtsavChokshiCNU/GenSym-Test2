;; -*- Mode: emacs-lisp -*-

;; Mouse-sensitive printed representations for Ilisp.
;;  -fmw, 9/26/93

;; The highlighting color can be changed with (set-face-background (find-face 'highlight) "palegreen")
;; It could event be different for different classes of objects.

;; Todo: make "..." sensitive? Enumerate them by their text position in the buffer?

;;  See the doc for popup-menu for the format of this list.

;;  Generate this menu by grepping the lisp source for def-emacs-mouse-command
(defconst ilisp-mouse-default-menu
  '("Lisp Command:"
    ["Select" ilisp-mouse-select t ""]
    ["Describe" ilisp-mouse-describe t ""]
    ["Outline Subblocks" ilisp-mouse-outline t ""]))

(defconst ilisp-mouse-help-text "Left: Select;  Middle: Describe;  Right: Menu")

;; Bindings for menu commands.
(defun ilisp-mouse-select ()
  (interactive)
  (ilisp-mouse-command 'select))

(defun ilisp-mouse-describe ()
  (interactive)
  (ilisp-mouse-command 'describe))

(defun ilisp-mouse-outline ()
  (interactive)
  (ilisp-mouse-command 'outline))



(defun ilisp-mouse-get-menu-for-object (text)
  "Given the printed representation of a gensym object, return an appropriate popup menu."
  (cond ((string-match "#<image-plane" text) ; For example.
	 ilisp-mouse-default-menu)
	(t
	 ilisp-mouse-default-menu)))


;; I've setup Ilisp to call this automatically every time a new lisp is started.

(defun enable-presentations ()
  "Rebind the three mouse buttons to act on Gensym objects found in the ilisp buffer."
  (interactive)
  (setq mode-motion-hook 'highlight-gensym-object)
  (define-key ilisp-mode-map 'button1 'ilisp-mouse-select-object-maybe)
  (define-key ilisp-mode-map 'button2 'ilisp-mouse-describe-object-maybe)
  (define-key ilisp-mode-map 'button3 'ilisp-mouse-menu))

(defun disable-presentations ()
  (interactive)
  (setq mode-motion-hook nil)
  (define-key ilisp-mode-map 'button1 'mouse-track)
  (define-key ilisp-mode-map 'button2 'x-set-point-and-insert-selection)
  (define-key ilisp-mode-map 'button3 nil))



(defconst gensym-object-start-regexp "#<")
(defconst gensym-object-end-regexp "@[0-9]+>")
(defconst gensym-object-pattern (format "\\(%s\\)\\|%s" gensym-object-start-regexp gensym-object-end-regexp))
(defvar gensym-object-max-length 150)	; For moby slot-description printer.

;; Look for Gensym structures, printed as #<xxx @nnn>.

;; Does not handle nested objects.
(defun delimit-gensym-object-fast ()
  "Return the start and end points of the gensym object surrounding point, or NIL if none."
  (let ((center (point))
	(start nil)
	(end nil))
    (save-excursion
      (forward-char 2)
      (cond ((null (re-search-backward gensym-object-start-regexp (- center gensym-object-max-length) t))
	     nil)
	    (t
	     (setq start (match-beginning 0))
	     (cond ((and (re-search-forward gensym-object-end-regexp (+ center gensym-object-max-length) t)
			 (< center (setq end (match-end 0))))
		    (cons start end))
		   (t
		nil)))))))


;; Tries to handle nested objects.
(defun delimit-gensym-object ()
  "Return the start and end points of the gensym object surrounding point, or NIL if none."
  (let* ((center (point))
	 (start nil)
	 (end nil)
	 (min (max 0 (- center gensym-object-max-length)))
	 (max (min (point-max) (+ center gensym-object-max-length)))
	 (count 1))
    (condition-case ()
	(progn
	  (save-excursion
	    ;; If we're in the midst of a match now, nudge point past it.
	    (cond ((looking-at gensym-object-start-regexp)
		   (forward-char 2))
		  ((save-excursion
		     (backward-char 1)
		     (looking-at gensym-object-start-regexp))
		   (forward-char 1)))
	    (while (> count 0)
	      (if (null (re-search-backward gensym-object-pattern min t))
		  (setq count -1)
		  (cond ((match-beginning 1)
			 (setq count (- count 1)))
			(t
			 (setq count (+ count 1))))))
	    (cond ((>= count 0)
		   (setq start (point))
		   (setq count 1)
		   (forward-char 1)
		   (while (> count 0)
		     (if (null (re-search-forward gensym-object-pattern max t))
			 (setq count -1)
			 (cond ((match-beginning 1)
				(setq count (+ count 1)))
			       (t
				(setq count (- count 1))))))
		   (if (>= count 0)
		       (setq end (point))))))

	  (if (and start end
		   (<= start center)
		   (< center end))
	      (cons start end)))
      (error nil))))


;; There won't always be the :c and :a mnemonics.
(defconst debugger-proceed-option-regexp "^..  [0-9]: ")

;; :C  0: Return from Break
;; :A  1: Abort to Lisp Top Level

(defun delimit-debugger-proceed-option ()
  nil)
      


(defsubst ilisp-mouse-highlight-internal (event backward forward help)
  ;; Help is the mouse-doc line.
  (mode-motion-highlight-internal event backward forward)
  (if (and mode-motion-extent (extent-buffer mode-motion-extent)
	   (extent-property mode-motion-extent 'highlight))
      (set-extent-property mode-motion-extent 'help-echo help)))


;; new ops on symbols: meta-middle is a menu of callers.
;; Want the meta ops in lisp mode, too.

(defun highlight-gensym-object (event)
  "To be used as a value for mode-motion-hook."
  (cond ((= 2 (event-modifier-bits event)) ; Meta bit.
	 (mode-motion-highlight-common-lisp-symbol event))

	((= 1 (event-modifier-bits event)) ; Control bit.
	 )

	((= 0 (event-modifier-bits event)) ; No bits.
	 (let (spot)
	   (ilisp-mouse-highlight-internal
	     event
	     (function (lambda ()
	       (setq spot (delimit-gensym-object))
	       (if spot
		   (goto-char (car spot))
		   (goto-char 1))))
	     (function (lambda ()
	       (if spot
		   (goto-char (cdr spot))
		   (goto-char 1))))
	     ilisp-mouse-help-text)))))



(defun mode-motion-highlight-common-lisp-symbol (event)
  (let (spot)
    (ilisp-mouse-highlight-internal
      event
      (function (lambda ()
	(setq spot (ab-delimit-common-lisp-symbol))
	(if spot (goto-char (car spot)) (goto-char 1))))
      (function (lambda ()
	(if spot (goto-char (cdr spot)) (goto-char 1))))
      "meta+Left: Edit Definition;  Middle: Edit Caller;  Right: Menu")))

;; Menu is ilisp-mouse-symbol-menu, in gensym-ilisp.




(defun highlight-for-lisp-mode (event)
  "To be used as a value for mode-motion-hook."
  (cond ((= 2 (event-modifier-bits event)) ; meta key
	 ;; Want something better: this highlights, eg, "#<foobar" as a symbol.
	 (mode-motion-highlight-common-lisp-symbol event))
	(t
	 (clear-mode-motion-extent))))


(add-hook 'lisp-mode-hook
	  '(lambda () (setq mode-motion-hook 'highlight-for-lisp-mode)))



;; Call this when the buffer is scrolled.  Actually, we want
;; to get the current mouse position and maybe highlight
;; something new.
(defun clear-mode-motion-extent ()
  (if (and mode-motion-extent (extent-buffer mode-motion-extent)
	   (not (eq (extent-start-position mode-motion-extent)
		    (extent-end-position mode-motion-extent))))
      (progn
	(set-extent-endpoints mode-motion-extent 1 1)
	(set-extent-property mode-motion-extent 'help-echo nil))))


;; Contains the object on which the popup-menu acts.
(defvar ilisp-mouse-cached-object nil)

;; The text of the Gensym object at point, or nil.
(defun ilisp-mouse-get-object (&optional decache)
  (if decache (setq ilisp-mouse-cached-object nil))
  (cond (ilisp-mouse-cached-object
	 (prog1
	     ilisp-mouse-cached-object
	   (setq ilisp-mouse-cached-object nil)))
	(t
	 (let ((spot (delimit-gensym-object)))
	   (if spot
	       (buffer-substring (car spot) (cdr spot)))))))
	 

(defun ilisp-mouse-echo (fmt &optional arg1 arg2)
  (end-of-buffer)
  (insert (format fmt arg1 arg2))
  (end-of-buffer)
  (set-marker (process-mark (get-buffer-process (current-buffer))) (point)))


(defun ilisp-mouse-quotify-string (string)
  "Quote any characters in STRING that may confuse the lisp."
  (apply (function concat)
	 (mapcar (function
		   (lambda (char)
		     (if (or (= char ?\")
			     (= char ?\\))
			 (vector ?\\ char)
		       (vector char))))
		 string)))

(defun ilisp-mouse-at-prompt-p ()
  (save-excursion
    (goto-char (point-max))
    (beginning-of-line)
    (and (looking-at comint-prompt-regexp)
	 (eql (match-end 0) (point-max)))))


(defun ilisp-mouse-get-object-id (string)
  ;; Given a string like #<... @id>, pull out the id as an integer.
  (if (string-match "#<.*@\\([0-9]+\\)>\\'" string)
      (substring string (match-beginning 1) (match-end 1))))


;; The form to print, given an id, which evals to the object in lucid.
(defconst ilisp-mouse-get-object-command  "(@ %s)")

;; For faster feedback, we echo the string to the buffer now, while lucid is thinking.
;; The object is just the entire text of its preinted representation, scarfed up from 
;; the buffer.
(defun ilisp-mouse-command (command &optional object)
  (interactive)
  (let ((object (or object (ilisp-mouse-get-object))))
    (cond ((null object))
	  ((or (ilisp-mouse-at-prompt-p)
	       (not (eq command 'select)))
	   (ilisp-mouse-echo "; %s %s\n" command object)
	   (ilisp-mouse-send "(ilisp-mouse-command '%s \"%s\")"
			     command
			     (ilisp-mouse-quotify-string object)))
	  (t
	   ;; Select command, not at prompt: insert form which evals to the
	   ;; object.
	   (end-of-buffer)
	   (if (/= (preceding-char) ? )
	       (insert " "))
	   (insert (format ilisp-mouse-get-object-command (ilisp-mouse-get-object-id object)))
	   (end-of-buffer)))))


(defun ilisp-mouse-send (fmt &optional arg1 arg2)
  (ilisp-send (format fmt arg1 arg2) nil nil t))

 

;; Bindings for mouse buttons.
(defun ilisp-mouse-select-object-maybe (event)
  "Only if there is an ilisp-extent under us."
  (interactive "@e")
  (mouse-set-point event)
  (let ((object (ilisp-mouse-get-object t)))
    (if object
	(ilisp-mouse-command 'select object)
	;; Mouse-track is the default binding of button1.
	(mouse-set-point event)
	(call-interactively 'mouse-track event))))

(defun ilisp-mouse-describe-object-maybe (event)
  "Only if there is an ilisp-extent under us."
  (interactive "@e")
  (mouse-set-point event)
  (let ((object (ilisp-mouse-get-object t)))
    (if object
	(ilisp-mouse-command 'describe object)
	;; 'x-set-point-and-insert-selection is the default binding of button2.
	(mouse-set-point event)
	(call-interactively 'x-set-point-and-insert-selection event))))


(defun ilisp-mouse-menu (event)
  (interactive "e")
  (save-excursion
    (mouse-set-point event)
    (setq ilisp-mouse-cached-object (ilisp-mouse-get-object t)))
;; To include the object string in the menu labels:
;    (setcar (cdr ilisp-mouse-menu) (cdr ilisp-mouse-cached-object))
;    (aset (car (cdr ilisp-mouse-menu)) 3 (format " %s" (cdr ilisp-mouse-cached-object)))
;    (aset (car (cdr (cdr ilisp-mouse-menu))) 3 (format " %s" (cdr ilisp-mouse-cached-object)))
  ;; Vary the menu depending on the Class of the object (assuming the class is part of the printed rep.).
  (if ilisp-mouse-cached-object
      (popup-menu (ilisp-mouse-get-menu-for-object ilisp-mouse-cached-object))
      ;; No default binding.
      (beep)))


;;; The "lisp" menu in the menu bar.

(defconst ilisp-menu-name "G2")

(defconst ilisp-mode-menu
  '("Lisp/G2 commands"
;;    ["Goto Lucid Buffer" lucid t]	; Useless, since the menu is not there unless we're there.
    ["Launch G2" (g2 "(launch-ab)\n") t]
    "-----"
;;    ["Describe" (g2 "(d ") t]
;;    ["Inspect" (g2 "(i ") t]
    ["Pretty Print *" (g2 "(pp)\n") t]
;;    ["Symbol Plist" (g2 "(sp ") t]
    ["Show * History" (g2 "(show-*-history)\n") t]
    ["Show Output History" (g2 "(show-output-history)\n") t]
;;    ["Latest Instance" (g2 "(ci '") t]

    ;; Debugger
    "-----"
    ["Trace" (g2 "(trace ") t]
    ["Breakon" (g2 "(breakon '") t]
    ["Unbreakon" (g2 "(unbreakon '") t]
    ["Show Dynamic Extents" (g2 "(dx)\n") t]

   ;; Looking at Lattice
    "-----"
    ["Who Calls" (g2 "(who-calls '") t]
    ["Who Is Called" (g2 "(who-is-called '") t]
    ["Outline Call Graph" (g2 "(outline-call-graph '") t]
    ["Outline Inverse Call Graph" (g2 "(outline-inverse-call-graph '") t]
    ["Outline Drawing" (g2 "(outline-drawing ") t]
    ["Outline Subblocks" (g2 "(outline-subblocks ") t]
    ["Outline Type Description" (g2 "(outline-type-description ") t]
    ["Get Outline Node" (g2 "(gon ") t]

   ;; Misc
    "-----"
    ["Most Recent Defun Name" (g2 "most-recent-defun-name\n") t]
    ["Workstation Context Stack" (g2 "(dcs)\n") t]
    ["Apropos" (g2 "(apr ") t]
    ["Post Mortem Checkpoints" (g2 "(print-post-mortem-checkpoints)\n") t]

   ;; Memory Problems
    "-----"
    ["Compare Memory Allocation" (g2 "(compare-memory-allocation)\n") t]
    ["Memory" (g2 "(memory)\n") t]
    ["G2 Memory Usage" (g2 "(g2-memory-usage)\n") t]
    ["Object Pool Meters" (g2 "(object-pool-meters)\n") t]))


(defun g2 (string)
  "Send string to lucid.  Interrupt lucid if necessary."
  (cond ((eq major-mode 'ilisp-mode)
	 (goto-char (point-max))
	 (let* ((execute (string-match "\n$" string))
		(end (match-end 0)))
	   (cond ((not execute)
		  (insert string))
		 ((ilisp-mouse-at-prompt-p)
		  (insert (substring string 0 (1- end)))
		  (call-interactively 'return-ilisp))
		 (t
		  ;; How to send and get output into ilisp buffer?
		  (beep)))))))



(defun ilisp-install-menubar ()
  (if (and current-menubar (not (assoc ilisp-menu-name current-menubar)))
      (let ((menu (if (eq major-mode 'ilisp-mode)
		      ilisp-mode-menu)))
	(cond (menu
	       (set-buffer-menubar (copy-sequence current-menubar))
	       (add-menu nil ilisp-menu-name (cdr menu)))))))


(defun ilisp-clear-menubar ()
  (let ((menubar (save-excursion
		   (set-buffer "*scratch*")
		   (copy-sequence current-menubar))))
    (set-buffer-menubar menubar)))

(add-hook 'ilisp-mode-hook 'ilisp-install-menubar)

(provide 'presentations)
