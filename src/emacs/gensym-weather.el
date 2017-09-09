;;;; Weather Report

(load "time")

(defconst ab-temperature-pathname "/home/ab/g2/weather/temperature")
(defconst ab-weather-pathname     "/home/ab/g2/weather/forecast")
(defconst ab-temperature-update-interval 3) ; minutes

(defvar ab-temperature "??")		; Cached
(defvar ab-temperature-count 0)

(defun read-file-as-string (pathname)
  (cond ((not (file-exists-p pathname))
	 "")
	((not (file-exists-p "/bin/cat"))
	 )
	(t
	 (with-output-to-string
	     (call-process "/bin/cat" nil standard-output nil pathname)))))

;; TODO: Need to look at file-write-date to see if temp is old.
(defun ab-update-temperature ()
  (let ((new (read-file-as-string ab-temperature-pathname)))
    (cond ((string-match "\\`\\([0-9-]+\\)" new)
	   (setq ab-temperature (substring new (match-beginning 1) (match-end 1))))
	  (t
	    ))))

(defun ab-temperature-hook ()
  (if (= ab-temperature-count 0)
      (ab-update-temperature))
  (setq ab-temperature-count (mod (1+ ab-temperature-count) ab-temperature-update-interval))
  (let ((var (if xemacs-p 'string 'display-time-string)))
    (set var (concat (symbol-value var) " " ab-temperature "°F"))))

(add-hook 'display-time-hook 'ab-temperature-hook)

(defun weather-report ()
  "The current conditions at Hanscom field."
  (interactive)
  (let ((string (read-file-as-string ab-weather-pathname)))
    (cond ((fboundp 'ilisp-display-output-in-typeout-window)
	   (ilisp-display-output-in-typeout-window string))
	  (t
	   (with-output-to-temp-buffer "*weather_report*"
	     (princ string))))))

(or xemacs-p
    (and fsf-emacs-p
	 (>= emacs-major-version 20))
    (standard-display-european 1))	; Only needed in emacs ca 19.29

(setq display-time-day-and-date t)
(display-time)
