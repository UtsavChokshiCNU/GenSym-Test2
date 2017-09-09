;;;; Filename utilties


(defun pathname-name (pathname)
  (if (string-match "\\." pathname)
      (substring pathname 0 (1- (match-end 0)))
      pathname))


(defun pathname-type (pathname)
  (if (string-match "\\." pathname)
      (substring pathname (match-end 0))
      pathname))
;; Use file-name-nondirectory first?

(defun uudecode ()
  "UUdecode current buffer into /tmp/. Optionally find the resulting file."
  (interactive)
  (let ((tmp "/tmp/uu")
	(filename nil))
    (save-excursion
      (goto-char (point-min))
      (re-search-forward "^begin [0-7][0-7][0-7] \\([/.a-zA-Z0-9_-]*\\)$")
      (setq filename (file-name-nondirectory
		       (buffer-substring (match-beginning 1) (match-end 1))))
      ;; Ignore any directory component of the filename.
      (forward-line 1)
      (beginning-of-line)
      (let ((start (point)))
	(re-search-forward "^end")
	(forward-line 1)
	(if (file-exists-p tmp)
	    (delete-file tmp))
	(write-string (format "begin 666 %s\n" filename) tmp)
	(write-region start (point) tmp t)
	(quick-shell-command (format "cd /tmp/ ; uudecode <%s >/dev/null" tmp))))

    (display-image (format "/tmp/%s" filename))))


(defun quick-shell-command (command)
  ;; Run command and wait for it to complete. But don't show any output.
  (let ((buffer (get-buffer-create "*Shell Command Output*")))
    (call-process shell-file-name nil buffer nil "-c" command)))


(defun write-string (string filename &optional append)
  ;; Kludgey feature.
  (write-region string nil filename append))


;; Used by cvs update for warnings.

(defun unsaved-lisp-buffers-p ()
  (let ((buffers (buffer-list))
	(buffer nil)
	(answer nil))
    (while (setq buffer (car buffers))
      (setq buffers (cdr buffers))
      (if (and (buffer-modified-p buffer)
	       (buffer-file-name buffer)
	       (string-match ".lisp" (buffer-file-name buffer)))
	  (progn (formatd buffer)
		 (setq answer t))))
    answer))



;;;; Filename operations



(defvar gensym-filename-keymap (let ((map (make-sparse-keymap)))
				 (define-key map 'button3 'post-file-menu)
				 map))

(defconst pop-up-file-menu
  '("File Menu:"
    ["Find File" (find-file filename) t ""]
    ["Find URL" (find-url filename) t ""]
    ["Dired" (dired filename) t ""]
    ["Show Image" (display-image filename t) t ""]
    ["Send Mail" (compose-mail-to filename) t ""]
    ["Load KB" (run-g2-kb filename) t ""]))





;; Filter: string must either begin with a slash or ~, or be a URL, and contain
;; a slash and some letters.
(defsubst looks-like-a-filename-p (string)
  (and (or (string-match "\\`[/~]" string)
	   (url-p string))
       (string-match "[a-zA-Z]" string)))
       

;; Allow :%=& for URL's.
;; Eg http://tiger.census.gov/cgi-bin/mapbrowse?lat=42.391&lon=-71.139&wid=.08&ht=.04
;; Eg, <URL:mailto:fmw@gensym.com>

(defsubst find-beginning-of-filename ()
  (re-search-backward "[^?@&~/:%=&*A-Za-z0-9---_.$#+,]+")
  (forward-char 1))

(defsubst find-end-of-filename ()
  (re-search-forward "[?@&~/:%=&*A-Za-z0-9---_.$#+,]+"))


(defun delimit-filename-at-point ()
  (let ((start nil)
	(end nil))
    (find-beginning-of-filename)
    (while (looking-at "[ \t\n\"]")	; Skip leading whitespace.
      (forward-char 1))
    (if (looking-at "url:")		; Skip leading URL:
	(forward-char 4))
    (setq start (point))

    ;; Trim various trailing punctuation.
    (find-end-of-filename)
    (if (memq (preceding-char) '(34 ?* ?@ ?, ?. ?:))
	(backward-char 1))
    (setq end (point))

    (let ((string (buffer-substring start end)))
      (if (looks-like-a-filename-p string)
	  (cons start end)))))


(defun filename-at-point-1 ()
  ;; Low-level routine: does not save excursion.
  (let ((pos (delimit-filename-at-point)))
    (if pos
	(buffer-substring (car pos) (cdr pos)))))

(defun filename-at-point ()
  (interactive)
  (save-excursion
    (filename-at-point-1)))


(defun mode-motion-highlight-filename (event)
  "Highlight filename at event"
  (let (pos)
    (ilisp-mouse-highlight-internal	; Allows the doc line.
      event
      (function
	(lambda ()
	  (setq pos (delimit-filename-at-point))
	  (if pos (goto-char (car pos)))))
      (function
	(lambda ()
	  (if pos (goto-char (cdr pos)))))
      "Right: file menu")

    ;; If the extent is non-empty, give it the keymap.
    (if (and (extentp mode-motion-extent)
	     (extent-buffer mode-motion-extent))
	(set-extent-property mode-motion-extent 'keymap
			     (if (extent-property mode-motion-extent 'highlight)
				 gensym-filename-keymap
				 nil)))))

;; Ought to do this in every view-mode.
(defun file-mode ()
  "Turn on filename operations in this buffer."
  (interactive)
  (setq mode-motion-hook 'mode-motion-highlight-filename))


(defun image-pathname-p (pathname)
  (let ((type (pathname-type pathname)))
    (or (string-equal type "jpg")
	(string-equal type "jpeg")
	(string-equal type "gif")
	(string-equal type "xbm"))))


(defun compose-mail-to (url)
  (if (url-is-mail-p url)
      (progn
	(rmail-compose)
	(insert (url-is-mail-p url))
	(forward-line 1))))


(defun post-file-menu (event)
  (interactive "e")
  (save-window-excursion
    (save-excursion
      (mouse-set-point event)
      (let ((filename (filename-at-point-1)))
	(cond ((null filename)
	       (beep))
	      ((and (not (string-match "\\*" filename))
		    (not (url-p filename))
		    (not (file-exists-p filename)))
	       (beep))
	      (t
	       (let* ((menu pop-up-file-menu)
		      (mail-p (url-is-mail-p filename))
		      (url-p (url-p filename))
		      (dir-p (and (not url-p)
				  (or (file-directory-p filename)
				      (string-match "\\*" filename))))
		      (image-p (image-pathname-p filename))
		      (kb-p (string-equal (pathname-type filename) "kb")))
		 ;; Stuff args into menu commands.
		 (while menu
		   (let ((item (car menu)))
		     (cond ((vectorp item)
			    (let* ((fun (car (aref item 1)))
				   (argspot (cdr (aref item 1)))
				   (active-p (cond (mail-p
						    (eq fun 'compose-mail-to))
						   (url-p
						    (eq fun 'find-url))
						   (dir-p
						    (eq fun 'dired))
						   (image-p
						    (eq fun 'display-image))
						   (kb-p
						    (eq fun 'run-g2-kb))
						   (t
						    (eq fun 'find-file)))))
			      (if argspot
				  (setcar argspot filename))
			      (aset item 2 active-p)))))
		   (setq menu (cdr menu)))

		 (popup-menu pop-up-file-menu))))))))


(defun display-image (filename &optional no-confirm)
  "Display image files, edit other files."
  (interactive "fFilename: ")
  (cond ((string-match "\\*" filename)	; Looks like a wildcard.
	 (dired filename))
	((not (file-exists-p filename))
	 (error "File %s not found!" filename))
	((image-pathname-p filename)
	 (if (or no-confirm (y-or-n-p (format "View the image %s? " filename)))
	     (progn
	       (message "")
	       (quick-shell-command (format "xv %s &" filename)))))
	((or no-confirm (y-or-n-p (format "Get the file %s? " filename)))
	 (find-file filename))))


;; Too bad this can't connect to an existing G2.
(defun run-g2-kb (filename)
  (shell-command (format "nohup /gensym/ut/dev/g2-latest/g2 -kb %s &" filename)))




;;;; Diff mode


(defun diff-mode ()
  "Enable diff-mode operations in current buffer, which should contain cvs diff(1) output"
  (interactive)
  (kill-all-local-variables)
  (use-local-map diff-mode-map)

  (setq mode-name "Diff"
	major-mode 'diff-mode
	mode-motion-hook 'mode-motion-highlight-diff-output
	buffer-read-only t)

  (run-hooks 'diff-mode-hook))


(if (not (assoc "\\.diff$" auto-mode-alist))
    (setq auto-mode-alist (cons '("\\.diff$" . diff-mode)
				auto-mode-alist)))


(defconst diff-mode-map
    (let ((map (make-sparse-keymap)))
      (define-simple-view-mode-bindings map)
      (define-key map '(control \.) 'find-diff-at-point)
      (define-key map 'button2 'find-diff-at-mouse)
      (define-key map 'button3 'post-diff-menu)
      map))

(defconst pop-up-diff-menu
  '("Diff Menu:"
    ["Find Diff in New File" find-diff-in-new-file t ""]
;    ["Find Diff in Old File" find-diff-in-old-file t ""]
    ))

    



;;; CVS Diff output look like:
;;; RCS file: /gensym/ab-repos/lisp/edit1.lisp,v
;;; retrieving revision 1.58
;;; diff -r1.58 edit1.lisp
;;; 10a20,30
;;; 10c20,30
;;; 10,20d30
;;; The number after the comma is optional.

(defconst gensym-diff-regexp "^\\([0-9,]*\\)\\([acd]\\)\\([0-9,]*\\)$")

(defconst diff-filename-regexp "^diff .*-r\\([0-9.]*\\) \\(.*\\)$")


(defun delimit-diff-output-at-point ()
  (let (start)
    (beginning-of-line)
    (setq start (point))
    (cond ((looking-at "^[0-9,]*[acd][0-9,]*$")
	   (end-of-line)
	   (cons start (point)))
	  (t
	   nil))))

(defun diff-output-at-point ()
  (let ((pos (delimit-diff-output-at-point)))
    (if pos
	(buffer-substring (car pos) (cdr pos)))))


(defun mode-motion-highlight-diff-output (event)
  "Highlight filename at event"
  (let (pos)
    (ilisp-mouse-highlight-internal	; Allows the doc line.
      event
      (function (lambda () (setq pos (delimit-diff-output-at-point))
			(if pos (goto-char (car pos)))))
      (function (lambda () (if pos (goto-char (cdr pos)))))
      "Middle: Highlight Diff, Right: menu")

    ;; If the extent is non-empty, give it the keymap.
    (if (and (extentp mode-motion-extent)
	     (extent-buffer mode-motion-extent))
	(set-extent-property mode-motion-extent 'keymap
			     (if (extent-property mode-motion-extent 'highlight)
				 diff-mode-map
				 nil)))))

(defun parse-diff-range (string)
  (if (string-match "\\([0-9]*\\),\\([0-9]*\\)" string)
      (cons (read (substring string (match-beginning 1) (match-end 1)))
	    (read (substring string (match-beginning 2) (match-end 2))))
      (cons (read string) (read string))))

	    

(defun post-diff-menu (event)
  (interactive "e")
    (save-window-excursion
      (save-excursion
	(mouse-set-point event)
	(popup-menu pop-up-diff-menu))))


;; Bound to mouse-middle.
(defun find-diff-at-mouse (event)
  (interactive "e")
  (mouse-set-point event)
  (find-diff-in-new-file))


(defun find-diff-at-point ()
  "In the newer file"
  (interactive)
  (find-diff-in-new-file))


(defun find-diff-in-old-file ()
  (find-diff nil))

(defun find-diff-in-new-file ()
  (find-diff t))


(defun find-diff (&optional new-file-p)
  "Goto the file position to which the diff line at point refers as filename-2"
  (interactive)
  (let (range-1 op range-2 rev-1 filename-1 filename-2)
    (save-excursion
      (beginning-of-line)
      (cond ((re-search-forward gensym-diff-regexp nil t)
	     (setq range-1 (buffer-substring (match-beginning 1) (match-end 1))
		   op (buffer-substring (match-beginning 2) (match-end 2))
		   range-2 (buffer-substring (match-beginning 3) (match-end 3)))

	     (setq range-1 (parse-diff-range range-1))
	     (setq range-2 (parse-diff-range range-2))

	     ;; Figure out the filename and rev to which we are comparing.
	     (cond ((re-search-backward diff-filename-regexp nil t)
		    (setq rev-1 (buffer-substring (match-beginning 1) (match-end 1)))
		    (setq filename-2 (buffer-substring (match-beginning 2) (match-end 2)))
		    (setq filename-1 filename-2))

		   ((string-match ".diff" (buffer-name))
		    ;; Guess the file from the name of the diff file.
		    (let ((filename (substring (buffer-name)
					       0
					       (match-beginning 0))))
		      (if (file-exists-p filename)
			  (setq filename-1 filename
				filename-2 filename))))))))


    ;; Use cvs-show to get old file filename-1 with rev-1.
    ;; cvs-show filename-1 rev-1

    (cond ((and range-2 filename-2)
	   (let ((many (max (1+ (- (cdr range-2) (car range-2)))
			    (if range-1 (1+ (- (cdr range-1) (car range-1))) 0))))
	     (find-file-other-window filename-2)
	     (goto-line (car range-2))
	     (recenter 5)		; Show 5 lines of context before the diff.
	     (if (not (equal op "d"))	; Just set point for deletions
		 (progn (push-mark)
			(goto-line (1+ (cdr range-2)))
			(exchange-point-and-mark)
			(if xemacs-p
			    (zmacs-activate-region))))
	     (cond ((equal op "a")
		    (message "Added %d line%s" many (if (> many 1) "s" "")))
		   ((equal op "c")
		    (message "Changed %d line%s" many (if (> many 1) "s" "")))
		   (t
		    (message "Deleted %d line%s here" many (if (> many 1) "s" ""))))))
	  (t
	   (beep)))))


(defun highlight-next-diff ()
  (interactive)
  (end-of-line)
  (re-search-forward gensym-diff-regexp)
  (find-diff))

(define-key diff-mode-map 'kp_enter 'highlight-next-diff)
